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
#include "NurApi.h"

/*
	Reader capabilities dump.
*/
void reader_caps(HANDLE hApi, int *alive)
{
	struct NUR_DEVICECAPS theCaps;
	int error;

	cls();
	_tprintf(_T("NUR device capability query\n"));

	memset((void *)&theCaps, 0, sizeof(struct NUR_DEVICECAPS));
	error = NurApiGetDeviceCaps(hApi, &theCaps);

	error_message(_T("Device capabilities"), error);

	if (error == NUR_SUCCESS) {
		_tprintf(_T("\n"));

		_tprintf(_T("%-25s : %s\n"), _T("Antenna tune support"), yesno(theCaps.flagSet1 & NUR_DC_ANTTUNE));
		_tprintf(_T("%-25s : %s\n"), _T("Channel scan support"), yesno(theCaps.flagSet1 & NUR_DC_CHSCANNER));
		_tprintf(_T("%-25s : %s\n"), _T("Beeper support"), yesno(theCaps.flagSet1 & NUR_DC_HASBEEP));
		_tprintf(_T("%-25s : %s\n"), _T("Light sensor support"), yesno(theCaps.flagSet1 & NUR_DC_HASLIGHT));
		_tprintf(_T("%-25s : %s\n"), _T("Tap sensor support"), yesno(theCaps.flagSet1 & NUR_DC_HASTAP));
		_tprintf(_T("%-25s : %s\n"), _T("Inventory+read support"), yesno(theCaps.flagSet1 & NUR_DC_INVREAD));
		
		_tprintf(_T("%-25s : %d\n"), _T("Tag buffer size (96-bit)"), theCaps.szTagBuffer);

		_tprintf(_T("%-25s : %d\n"), _T("Maximum nr of antennas"), theCaps.curCfgMaxAnt);
		_tprintf(_T("%-25s : %d\n"), _T("Maximum nr of GPIOs"), theCaps.curCfgMaxGPIO);		
		
		_tprintf(_T("%-25s : %d dBm, %d mW\n"), _T("Maximum TX level"), theCaps.maxTxdBm, theCaps.maxTxmW);
		_tprintf(_T("%-25s : %d\n"), _T("TX level steps"), theCaps.txSteps);

		_tprintf(_T("\n"));
	}
}

