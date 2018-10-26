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

#ifndef _NURCON_H_
#define _NURCON_H_	1

#include "NurOS.h"
#include "NurApi.h"
#include <stdio.h>

#define SZ_ARRAY(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#define STORE_PARAM(_ptrDest, _theParam) if (_ptrDest != NULL) *_ptrDest = _theParam

#define ANS_NO		0
#define ANS_YES		1

#ifndef __WFUNCTION__
#define __WFUNCTION__	_T(__FUNCTION__)
#endif

#define _UNUSED(_uuParam)	(void)(_uuParam)

struct NUR_API_HANDLE;
typedef void (*selhandler)(HANDLE , int *);

struct MENUDEF
{
	int sel;	// Selection from menu
	selhandler action;
	const TCHAR *text;	
};

struct ETHDEVICE
{
	int index;
	struct NUR_ETHDEV_CONFIG eth;
	struct ETHDEVICE *next;
};

struct ETHDEVICELIST
{
	int nDevices;
	struct ETHDEVICE *list;
};

extern void splash(void);

/*
	Utilities.
*/
extern int get_int_value(TCHAR *query, int *value, int minVal, int maxVal);
extern void query_string(TCHAR *question, TCHAR *dest);
extern int get_yesno(TCHAR *question);
extern const TCHAR *yesno(int yn);
extern const TCHAR *miller2str(int m);
extern const TCHAR *txmod2str(int mod);
extern TCHAR *allocstr(int len);
extern int bytes2str(unsigned char *b, int epclen, TCHAR *dest, int maxLen);

extern WORD get_rand_word(void);
/* 
	Generate a maximum of 64 random bytes and return the byte length. 
*/
extern int generate_words(BYTE **dest, int nWords);

extern void menuhandler(HANDLE hApi, struct MENUDEF *menu, int nItems, TCHAR *menuTitle);

extern void error_message(const TCHAR *pref, int error);
extern void cls(void);
extern void consume_chars(void);
extern void enter_done(void);

extern void menu_return(HANDLE hApi, int *alive);
extern void global_quit(HANDLE hApi, int *alive);
extern void print_reader_setup(HANDLE hApi, int *alive);
extern void reader_caps(HANDLE hApi, int *alive);

extern void edit_setup(HANDLE hApi, int *alive);
extern int get_inventory_params(HANDLE hApi, int *Q, int *session, int *rounds);

extern void scan_single(HANDLE hApi, int *alive);
extern int simple_inventory(HANDLE hApi, int *alive);

extern int read_tag(HANDLE hApi, TCHAR *epc, int bank, int wordAddress, int readByteCount);

extern void dump_tags(HANDLE hApi, int *alive);
extern void save_tags(HANDLE hApi, int *alive);

extern void NURAPICALLBACK ApiEventHandler(HANDLE hApi, DWORD timestamp, int type, LPVOID data, int dataLen);

extern int get_eth_devcount(void);
extern int add_eth_device(const struct NUR_ETHDEV_CONFIG *pEth);
extern void clear_ethdevlist(struct ETHDEVICELIST *pList);
extern BOOL eth_menu(struct ETHDEVICE *pResDev);

#endif

