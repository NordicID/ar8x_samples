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
	Application specific defaults.
*/
#define APP_DEF_FLAGS	(NUR_SETUP_INVQ | NUR_SETUP_INVSESSION | NUR_SETUP_INVROUNDS | NUR_SETUP_RXDEC | NUR_SETUP_LINKFREQ | NUR_SETUP_TXMOD | NUR_SETUP_TXLEVEL)
#define DEF_Q		5
#define DEF_SESS	0
#define DEF_ROUNDS	2
#define DEF_RXDEQ	NUR_RXDECODING_M4
#define DEF_TXMOD	NUR_TXMODULATION_PRASK
#define DEF_LF		256000
#define DEF_TXLEVEL	4

/*
	Return the basic inventory parameters.
*/
int get_inventory_params(HANDLE hApi, int *Q, int *session, int *rounds)
{
	int error;	
	struct NUR_MODULESETUP setup;

	memset((void *)&setup, 0, sizeof(struct NUR_MODULESETUP));
	/* Explicitly query the parameters from the module. */
	error = NurApiGetModuleSetup(hApi, NUR_SETUP_INVQ | NUR_SETUP_INVSESSION | NUR_SETUP_INVROUNDS, &setup, sizeof(struct NUR_MODULESETUP));

	if (error == NUR_SUCCESS) {
		STORE_PARAM(Q, setup.inventoryQ);
		STORE_PARAM(session, setup.inventorySession);
		STORE_PARAM(rounds, setup.inventoryRounds);
	}
	
	return 0;
}

