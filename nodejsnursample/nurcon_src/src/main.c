/* 
  Copyright © 2014- Nordic ID 
  NORDIC ID DEMO SOFTWARE DISCLAIMER

  You are about to use Nordic ID Demo Software ("Software"). 
  It is explicitly stated that Nordic ID does not give any kind of warranties, 
  expressed or implied, for this Software. Software is provided "as is" and with 
  all faults. Under no circumstances is Nordic ID liable for any direct, special, 
  incidental or indirect damages or for any economic consequential damages to you 
  or to any third party.

  The use of this software indicates your complete and unconditional understanding 
  of the terms of this disclaimer. 
  
  IF YOU DO NOT AGREE OF THE TERMS OF THIS DISCLAIMER, DO NOT USE THE SOFTWARE.  
*/

#include "platform.h"
#include "nurcon.h"

/*
	Local. 
*/
static void print_reader_info(HANDLE hApi, int extend);

/* Connected reader's general information: name etc. */
static void show_information(HANDLE hApi, int *alive)
{
	cls();
	print_reader_info(hApi, 1);
}

/* TBI. */
static void print_reader_caps(HANDLE hApi, int *alive)
{
	reader_caps(hApi, alive);
}

/* 
	Clear the module's internal tag storage as well as the API's tag storage. 
*/
static void clear_tags(HANDLE hApi, int *alive)
{
	int error;
	
	cls();

	error = NurApiClearTags(hApi);
	error_message(_T("Clear tags: "), error);
}

static void print_reader_info(HANDLE hApi, int extend)
{
	struct NUR_READERINFO ri;
	int i, error;
	struct NUR_ANTENNA_MAPPING map[NUR_MAX_ANTENNAS_EX];
	int nrMappings = 0;
	
	/* Populate information. */
	error = NurApiGetReaderInfo(hApi, &ri, sizeof(struct NUR_READERINFO));

	if (error == NUR_SUCCESS) {
		/* Just print out some general information. */
		_tprintf(_T("Reader information%s\n\n"), extend ? _T(":") : _T(", short:"));
		_tprintf(_T("%15s %s\n"), _T("Reader name"), ri.name);
		_tprintf(_T("%15s %d.%d-%c\n"), _T("FW version"), ri.swVerMajor, ri.swVerMinor, ri.devBuild);
		if (extend) {
			_tprintf(_T("%15s %s\n"), _T("Serial #"), ri.serial);
			_tprintf(_T("%15s %s\n"), _T("FCC ID"), ri.fccId);
			_tprintf(_T("%15s %d\n"), _T("# regions"), ri.numRegions);
			_tprintf(_T("%15s %d %s\n"), _T("# antennas"), ri.numAntennas, _T("(currently in use)"));
			_tprintf(_T("%15s %d\n"), _T("# GPIO"), ri.numGpio);
			_tprintf(_T("%15s %d\n"), _T("# sensors"), ri.numSensors);
		}
		_tprintf(_T("\n"));
	}
	else {
		error_message(_T("Reader information error"), error);
	}

//#ifdef __linux__
	error = NurApiGetAntennaMap(hApi, map, &nrMappings, NUR_MAX_ANTENNAS_EX, sizeof(struct NUR_ANTENNA_MAPPING));

	if (nrMappings > 0) {
		_tprintf(_T("Got %d antenna mappings, contents:\n\n"), nrMappings);

		for (i=0;i<nrMappings;i++)
			_tprintf(_T("Antenna ID %d = \"%s\".\n"), map[i].antennaId, map[i].name); 

		_tprintf(_T("\n"));
		NurApiEnablePhysicalAntenna(hApi,_T("AUX1"), FALSE);
		NurApiEnablePhysicalAntenna(hApi,_T("AUX2"), FALSE);
		NurApiEnablePhysicalAntenna(hApi,_T("AUX3"), FALSE);
		//NurApiEnablePhysicalAntenna(HANDLE hApi, const TCHAR *commaSeparated, BOOL disableOthers);
	}
	else {
		_tprintf(_T("Got no antenna mappings.\n"));
		error_message(_T("Antenna mappings"), error);
	}
//#endif
}


/* 
	Cleanup: disconnect + tell the API to do an internal cleanup.
*/
static void cleanup(HANDLE hApi)
{
	if (hApi == NULL || hApi == INVALID_HANDLE_VALUE)
		return;
	
	NurApiDisconnect(hApi);
	NurApiFree(hApi);
}

/* 
	Handle the command line's port name given for connection.
*/
int handle_connect(HANDLE hApi, TCHAR *portName, int baudRate, int *connError)
{
	int error = NUR_ERROR_TRANSPORT;
#ifndef __linux__
	TCHAR *tempPortName;
	int comNum;
#endif

	if (portName == NULL)
		return 0;
	
#ifdef __linux__
	error = NurApiConnectSerialPortEx(hApi, portName, baudRate);	
#else
	tempPortName = allocstr(_tcslen(portName) + 20);
	_tcscpy(tempPortName, portName);
	_tcsupr(tempPortName);

	if (_stscanf(tempPortName, _T("COM%d"), &comNum) == 1) {
		
		if (comNum < 1)
			return 0;
		if (comNum > 9) 
			_stprintf(tempPortName, _T("\\\\.\\COM%d"), comNum);
		else
			_tcscpy(tempPortName, portName);
		
		_tprintf(_T("Port to open is \"%s\".\n"), tempPortName);
		error = NurApiConnectSerialPortEx(hApi, tempPortName, baudRate);
		
		free((void *)tempPortName);
	}
	
#endif

	if (connError != NULL)
		*connError = error;
	return (error == NUR_SUCCESS);
}

void usage(TCHAR *pref)
{
	_tprintf(_T("Usage:\n\n"));
	_tprintf(_T("1. %s <port>\n"), pref);
	_tprintf(_T("- OR -\n"));
	_tprintf(_T("2. %s eth -> starts Ethernet device query.\n\n"), pref);

#ifdef __linux__
	_tprintf(_T("Examples:\%s /dev/ttyACM0\n"), pref);
	_tprintf(_T("%s /dev/tty10\n"), pref);		
#else
	_tprintf(_T("Examples:\n%s COM2\n"), pref);
	_tprintf(_T("%s COM17\n"), pref);
#endif

	_tprintf(_T("Usage: %s <port>.\n"), pref);
	_tprintf(_T("Usage: %s <port>.\n"), pref);
	
	_tprintf(_T("Usage: %s <eth>.\n"), pref);
}

#ifdef _UNICODE
int _tmain(int argc, TCHAR *argv[])
#else
int main(int argc, char *argv[])
#endif
{
	int nItems;
	int alive = 1;
	int error;
	int action = 0, bank = 0, wordAddress = 0, readByteCount = 0;
	HANDLE hApi = NULL;
	TCHAR connStr[100] = { 0 };
	
	if (argc < 3) {
		usage(argv[0]);
		return 0;
	}
	
	//nItems= SZ_ARRAY(mainMenu);
	/* Create the API 'object'. */
	hApi = (HANDLE )NurApiCreate();
	
	if (hApi == NULL || hApi == (HANDLE )-1) {
		_tprintf(_T("Fatal error: could not create the API instance.\n"));
		return 0;
	}

	error = NUR_SUCCESS;
	/* Try to connect to the port given in command line. */
	if (!handle_connect(hApi, argv[1], NUR_DEFAULT_BAUDRATE, &error)) {
		/* 
			In Linux you probably need to 'sudo' (in case you are sure that the port is present and device is connected to it). 
		*/
		_tprintf(_T("Fatal error: could not connect to %s.\n"), argv[1]);
		error_message(_T("Connection failed"), error);
		cleanup(hApi);
		return 0;		
	}
	action = atoi(argv[2]);
		
	if(action == 2) {
		if(argc < 7) {
			_tprintf(_T("Tag read: parameters missing, only %d available\n"), argc);
			return 0;
		}
		else
		{
			bank = atoi(argv[4]);
			wordAddress = atoi(argv[5]);
			readByteCount = atoi(argv[6]);		
		}
	}
	
	error = NUR_NO_ERROR;	
	//_tprintf(_T("Action %d\r\n"), action);	
	switch(action)
	{
		case 0:	
			print_reader_info(hApi, 1);
			break;
		case 1:
			error = simple_inventory(hApi, &alive);
		break;
		case 2: 
			error = read_tag(hApi, argv[3], bank, wordAddress, readByteCount);
			break;
		default:
			_tprintf(_T("Invalid operation\n"));
		break;
	}
	if(error != NUR_NO_ERROR)
	{
		_tprintf(_T("ERROR: %d performing action %d \r\n"), error, action);	
	}

	cleanup(hApi);

	return 0;
}


