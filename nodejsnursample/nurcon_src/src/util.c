/* 
  Copyright � 2014- Nordic ID 
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

void splash(void)
{
	cls();
	_tprintf(_T("*******************\n"));
	_tprintf(_T("*** NUR CONSOLE ***\n"));	
#ifdef _WIN32
	_tprintf(_T("* Windows x86/x64 *\n"));	
#endif
#ifdef _PLAT_LINUX86
	_tprintf(_T("***  Linux x86  ***\n"));	
#endif
#ifdef _PLAT_LINUX64
	_tprintf(_T("***  Linux x64  ***\n"));	
#endif
#ifdef PLAT_RASPI
	_tprintf(_T("*** Raspberry Pi **\n"));	
#endif
#ifdef _PLAT_BBONE
	_tprintf(_T("**** Beaglebone  **\n"));	
#endif
	_tprintf(_T("*******************\n\n"));
}

void cls(void)
{
#ifdef __linux__	
	//printf("\E[H\E[2J");
	system("clear");
#else
	system("cls");
#endif
}

#define MAX_ERR_MSG_LEN	1000

/*
	Print some error information based on the API's error code.
*/
void error_message(const TCHAR *pref, int error)
{
	TCHAR *eMsg;
	eMsg = (TCHAR *)malloc(MAX_ERR_MSG_LEN * sizeof(TCHAR));
	/* Simply interprets the code */
	NurApiGetErrorMessage(error, eMsg, MAX_ERR_MSG_LEN - 1);

	_tprintf(_T("%s, code: %d.\n"), pref, error);
	_tprintf(_T("Message(%d): %s\n"), error, eMsg);

	free((void *)eMsg);
}

/* Consume some characters from the input. */
void consume_chars(void)
{
	int ch;
	do {
		ch = getchar();
	} while(ch != EOF && ch != '\n');
}

/* Query an integer value within the given range. */
int get_int_value(TCHAR *query, int *value, int minVal, int maxVal)
{
	int scanVal = 0;
	int n;

	do {
		_tprintf(_T("%s "), query);
		n = _tscanf(_T("%d"), &scanVal);		
		consume_chars();
	} while (n != 1);
	
	*value = scanVal;
	return (scanVal>=minVal && scanVal <= maxVal);
}

/* Query a string from the user. */
void query_string(TCHAR *question, TCHAR *dest)
{
	_tprintf(_T("%s "), question);
	_tscanf(_T("%s"), dest);
	consume_chars();
}

/* Get yes/no answer from the user. */
int get_yesno(TCHAR *question)
{
	int done = 0;
	TCHAR c = _T('?');

	while (!done) {
		if (question != NULL)
			_tprintf(_T("%s [y/n] "), question);
		else 
			_tprintf(_T("y = yes, n = no: "));

		if (_tscanf(_T("%c"), &c) == 1) {
			if (c==_T('y') || c==_T('n'))
				done = 1;
		}

		consume_chars();
	}
	
	return (c==_T('y')) ? ANS_YES : ANS_NO;
}

const TCHAR *yesno(int yn)
{
	return (yn == 0) ? _T("no") : _T("yes");
}

/* Decode the given Miller-value to readable format. */
const TCHAR *miller2str(int m)
{
	switch (m)
	{
		case NUR_RXDECODING_FM0:
		return _T("FM0");
		break;
		case NUR_RXDECODING_M2:
		return _T("M-2");
		break;
		case NUR_RXDECODING_M4:
		return _T("M-4");
		break;
		default: 
		break;
	}

	return _T("M-8");
}

/* Get TX modulation in readable format. */
const TCHAR *txmod2str(int mod)
{
	if (mod == NUR_TXMODULATION_ASK)
		return _T("ASK");
	return _T("PR-ASK");
}

/* Allocate a TCHAR string. */
TCHAR *allocstr(int len)
{
	if (len > 0)
		return (TCHAR *)malloc(len * sizeof(TCHAR));

	return NULL;
}

/* Convert bytes to a HEX string. */
int bytes2str(unsigned char *b, int len, TCHAR *dest, int maxLen)
{
	int needed;
	TCHAR *pt;

	if (b == NULL || dest == NULL || len < 1 || maxLen < 1)
		return 0;

	needed = 2*len + 1;
	if (maxLen < needed)
		return 0;

	pt = dest;
	while (len--) {
		pt += _stprintf(pt, _T("%02X"), *b++);
	}

	return _tcslen(dest);
}

static void begin_rand()
{
	int seed;
#ifdef __linux__
	struct timeval tv;
	if(gettimeofday(&tv, NULL) != 0)
		seed = 0xDEADBEEF;
	else
		seed = tv.tv_usec;
#else
	seed = GetTickCount();
#endif
	srand(seed);
}

WORD get_rand_word()
{
	return (WORD)(rand() & 0xFFFF);
}

int generate_words(BYTE **dest, int nWords)
{
	int len = 0;
	int i;
	WORD *tmp;
	if (dest != NULL && *dest != NULL && nWords > 0 && nWords < 32) {
		tmp = (WORD *)malloc(nWords);
		
		begin_rand();
		for (i=0;i<nWords;i++) {
			tmp[i] = get_rand_word();
		}
		
		*dest = (BYTE *)tmp;
		len = nWords * 2;
	}
	
	return len;
}

