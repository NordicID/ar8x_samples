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

/// <summary>
/// Convert EPC byte array to string
/// </summary>
/// <param name="epc">The epc.</param>
/// <param name="epcLen">Length of the epc.</param>
/// <param name="epcStr">The epc string.</param>
void EpcToString(const BYTE *epc, DWORD epcLen, TCHAR *epcStr)
{
	DWORD n;
	int pos = 0;
	for (n=0; n<epcLen; n++) {
		pos += _stprintf_s(&epcStr[pos], NUR_MAX_EPC_LENGTH-pos, _T("%02x"), epc[n]);
	}
	epcStr[pos] = 0;
}

unsigned char GetBinVal(char ch)
{
	unsigned char value;
	if (ch >= '0' && ch <= '9')
            value = ch - '0';
        else if (ch >= 'A' && ch <= 'F')
            value = (ch - 'A' + 10);
        else if (ch >= 'a' && ch <= 'f')
            value = (ch - 'a' + 10);

	return value;
}

void HexStringToBin(TCHAR* str,BYTE* buf,int length)
{
	int strPtr = 0;
	int x = 0;
	if(length>62) length=62;
	for(x=0;x<length;x++)
	{
		strPtr=x*2;
		buf[x]=GetBinVal((char)(str[strPtr]));
		buf[x]<<=4;
		buf[x]+=GetBinVal((char)(str[strPtr+1]));
	}    
}

int read_tag(HANDLE hApi, TCHAR *epc, int bank, int wordAddress, int readByteCount)
{
	int error;
	BYTE buffer[128];
	BYTE ret[128];
	TCHAR readStr[128];
	DWORD epcLen=_tcslen(epc)/2;
	if(epcLen > 0)
	{	
		HexStringToBin(epc, buffer, epcLen);
		error = NurApiReadTagByEPC(hApi, 0, FALSE, buffer, epcLen, bank, wordAddress, readByteCount, ret);
		if (error != NUR_NO_ERROR)
		{
			return error;
		}
	
		EpcToString(ret, readByteCount, readStr);
		_tprintf(_T("%s"), readStr);		
	}
	else
	{
		return NUR_ERROR_INVALID_PARAMETER;
	}	
	return NUR_NO_ERROR;
}

/// <summary>
/// Performs the inventory.
/// </summary>
/// <param name="hApi">The hAPI.</param>
/// <returns></returns>
int simple_inventory(HANDLE hApi, int *alive)
{
	struct NUR_INVENTORY_RESPONSE resp;
	struct NUR_TAG_DATA tag;
	int error;
	int Q, session, rounds, count, idx;
	TCHAR epcStr[128];

	memset((void *)&resp, 0, sizeof(struct NUR_INVENTORY_RESPONSE));
	memset((void *)&tag, 0, sizeof(struct NUR_TAG_DATA));
	//cls();
	count = 0;
	Q = 0;
	session = 0;
	rounds = 0;
	if (get_inventory_params(hApi, &Q, &session, &rounds)) {
		//_tprintf(_T("Run one inventory with Q = %d, session = %d, rounds = %d:\n"), Q, session, rounds);
	}
	/* Clear tags from memory */
	NurApiClearTags(hApi);
	
	/* Command a simple inventory, ignore error, check results later. */
	error = NurApiSimpleInventory(hApi, &resp);
	//error_message(_T("Inventory result"), error);
	if (error != NUR_NO_ERROR)
	{
		// Failed
		return error;
	}

	error = NurApiFetchTags(hApi, TRUE, NULL);
	// check for "error" 0x20 (not tags found)
	if (error != NUR_NO_ERROR && error != NUR_ERROR_NO_TAG)
	{
		// Failed
		return error;
	}

	error = NurApiGetTagCount(hApi, &count);
	if (error != NUR_NO_ERROR)
	{
		// Failed
		return error;
	}
	
	for(idx=0;idx<count;idx++)
	{
		NurApiGetTagData(hApi, idx, &tag);
		EpcToString(tag.epc, tag.epcLen, epcStr);
		_tprintf(_T("%s\r\n"), epcStr);		
	}	

	return NUR_NO_ERROR;
}

