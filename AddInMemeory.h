
#ifndef __ADDIN_MEMORY_H__
#define __ADDIN_MEMORY_H__


#include "IMemoryManager.h"

/*------------------------------------------------------------------------------------------*/
//  Constants
/*------------------------------------------------------------------------------------------*/
static IMemoryManager* gMemory = NULL;


/*------------------------------------------------------------------------------------------*/
//  static class AddInMemory: Allocate memory by 1C:Enterprise mechanism
/*------------------------------------------------------------------------------------------*/
class AddInMemory {
public:
	static WCHAR_T* AllocWchar (const uint32_t len) {
		if (gMemory != NULL && len > 0) {
			WCHAR_T* pWch = NULL;
			if ( gMemory->AllocMemory((void**)(&pWch), len * sizeof(WCHAR_T)) ) {
				return pWch;
			}
		}

		return NULL;
	}
	static char* AllocChar (const uint32_t len) {
		if (gMemory != NULL && len > 0) {
			char* pCh = NULL;
			if ( gMemory->AllocMemory((void**)(&pCh), len * sizeof(char)) ) {
				return pCh;
			}
		}

		return NULL;
	}
};

#endif	// __ADDIN_MEMORY_H__
