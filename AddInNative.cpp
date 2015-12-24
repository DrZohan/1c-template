
#include "AddInNative.h"


/*------------------------------------------------------------------------------------------*/
//	Global Functions
/*------------------------------------------------------------------------------------------*/
long GetClassObject (const wchar_t* wsName, IComponentBase** pInterface) {
	if (*pInterface == NULL) {
		*pInterface = new CAddInNative();
		return (long)(*pInterface);
	}
	
	return 0;
}
//------------------------------------------------------------------------------------------
long DestroyObject (IComponentBase** pInterface) {
	if (*pInterface == NULL) {
		return -1;
	}

	delete *pInterface;
	*pInterface = 0;

	return 0;
}
//------------------------------------------------------------------------------------------
const WCHAR_T* GetClassNames () {
	static WCHAR_T* names = new WCHAR_T[gClassNames.size() + 1];

	if (names != NULL) {
		names = AddInConvert::WstrToWchr(names, gClassNames);
	}

	return names;
}
//------------------------------------------------------------------------------------------

/*------------------------------------------------------------------------------------------*/
//	Main Dll Class CAddInNative::
/*------------------------------------------------------------------------------------------*/
CAddInNative::CAddInNative () : iConnect(NULL), iAsyncEvent(NULL), iProp(), iMeth() {
	//iProp.Push(AddInProp(L"PropertyEng", L"PropertyRus", false, false));
	//iMeth.Push(AddInMeth(L"MethodEng", L"MethodRus", false, 0));
}
//------------------------------------------------------------------------------------------
CAddInNative::~CAddInNative () {
}
//------------------------------------------------------------------------------------------


/*------------------------------------------------------------------------------------------*/
//	CAddInPQ::IInitDoneBase
/*------------------------------------------------------------------------------------------*/
bool CAddInNative::Init (void* pConnection) {
	iConnect = (IAddInDefBase*)(pConnection);
	iAsyncEvent = (IAddInDefBase*)(pConnection);

	return (iConnect != NULL);
}
//------------------------------------------------------------------------------------------
bool CAddInNative::setMemManager(void* pMemory) {
	gMemory = (IMemoryManager*)(pMemory);

	return (gMemory != NULL);
}
//------------------------------------------------------------------------------------------
long CAddInNative::GetInfo () {
	return 2000; 
}
//------------------------------------------------------------------------------------------
void CAddInNative::Done () {
	iConnect = NULL;
	iAsyncEvent = NULL;
	gMemory = NULL;
}
//------------------------------------------------------------------------------------------


/*------------------------------------------------------------------------------------------*/
//	CAddInPQ::ILanguageExtenderBase
/*------------------------------------------------------------------------------------------*/
bool CAddInNative::RegisterExtensionAs (WCHAR_T** wsLanguageExt) {
	*wsLanguageExt = AddInMemory::AllocWchar(gExtensionName.size() + 1);
	if (*wsLanguageExt == NULL) return false;

	*wsLanguageExt = AddInConvert::WstrToWchr(*wsLanguageExt, gExtensionName);

	return true;
}
//------------------------------------------------------------------------------------------
long CAddInNative::GetNProps () {
	return iProp.Size();
}
//------------------------------------------------------------------------------------------
long CAddInNative::FindProp (const WCHAR_T* wsPropName) {
	return iProp.Find(wsPropName);
}
//------------------------------------------------------------------------------------------
const WCHAR_T* CAddInNative::GetPropName (long lPropNum, long lPropAlias) {
	if (lPropNum >= iProp.Size() || lPropNum < 0) {
		return NULL;
	}

	const std::wstring wstr(iProp[lPropNum].GetName(lPropAlias));
	WCHAR_T* wsRetVal = AddInMemory::AllocWchar(wstr.size() + 1);

	wsRetVal = AddInConvert::WstrToWchr(wsRetVal, wstr);

	return wsRetVal;
}
//------------------------------------------------------------------------------------------
bool CAddInNative::GetPropVal (const long lPropNum, tVariant* pvarPropVal) {
	if (lPropNum >= iProp.Size() || lPropNum < 0) {
		return false;
	}
	if (!iProp[lPropNum].IsReadable()) {
		return false;
	}

	return iProp[lPropNum].GetData(pvarPropVal);
}
//------------------------------------------------------------------------------------------
bool CAddInNative::SetPropVal (const long lPropNum, tVariant* varPropVal) {
	if (lPropNum >= iProp.Size() || lPropNum < 0) {
		return false;
	}
	if (!iProp[lPropNum].IsWritable()) {
		return false;
	}

	return iProp[lPropNum].SetData(pvarPropVal);
}
//------------------------------------------------------------------------------------------
bool CAddInNative::IsPropReadable (const long lPropNum) {
	if (lPropNum >= iProp.Size() || lPropNum < 0) {
		return false;
	}

	return iProp[lPropNum].IsReadable();
}
//------------------------------------------------------------------------------------------
bool CAddInNative::IsPropWritable (const long lPropNum) {
	if (lPropNum >= iProp.Size() || lPropNum < 0) {
		return false;
	}

	return iProp[lPropNum].IsWritable();
}
//------------------------------------------------------------------------------------------
long CAddInNative::GetNMethods () {
	return iMeth.Size();
}
//------------------------------------------------------------------------------------------
long CAddInNative::FindMethod (const WCHAR_T* wsMethodName) {
	return iMeth.Find(wsMethodName);
}
//------------------------------------------------------------------------------------------
const WCHAR_T* CAddInNative::GetMethodName (const long lMethodNum, const long lMethodAlias) {
	if (lMethodNum >= iMeth.Size() || lMethodNum < 0) {
		return NULL;
	}

	const std::wstring wstr(iMeth[lMethodNum].GetName(lMethodAlias));
	WCHAR_T* wsRetVal = AddInMemory::AllocWchar(wstr.size() + 1);

	wsRetVal = AddInConvert::WstrToWchr(wsRetVal, wstr);

	return wsRetVal;
}
//------------------------------------------------------------------------------------------
long CAddInNative::GetNParams (const long lMethodNum) {
	if (lMethodNum >= iMeth.Size() || lMethodNum < 0) {
		return 0;
	}

	return iMeth[lMethodNum].GetNParams();
}
//------------------------------------------------------------------------------------------
bool CAddInNative::GetParamDefValue (const long lMethodNum, const long lParamNum, tVariant *pvarParamDefValue) {
	TV_VT(pvarParamDefValue) = VTYPE_EMPTY;
	return false;
}
//------------------------------------------------------------------------------------------
bool CAddInNative::HasRetVal (const long lMethodNum) {
	if (lMethodNum >= iMeth.Size() || lMethodNum < 0) {
		return false;
	}

	return iMeth[lMethodNum].IsFunction();
}
//------------------------------------------------------------------------------------------
bool CAddInNative::CallAsProc (const long lMethodNum, tVariant* paParams, const long lSizeArray) {
	if (lMethodNum >= iMeth.Size() || lMethodNum < 0) {
		return false;
	}

	return true;
}
//------------------------------------------------------------------------------------------
bool CAddInNative::CallAsFunc(const long lMethodNum, tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray) {
	if (lMethodNum >= iMeth.Size() || lMethodNum < 0) {
		return false;
	}

	return true;
}
//------------------------------------------------------------------------------------------

/*------------------------------------------------------------------------------------------*/
//	CAddInPQ::LocaleBase
/*------------------------------------------------------------------------------------------*/
void CAddInNative::SetLocale (const WCHAR_T* loc) {
#ifndef __linux__
	_wsetlocale(LC_ALL, loc);
#else
/*
	int size = 0;
	char *mbstr = NULL;
	wchar_t *tmpLoc = NULL;
	convFromShortWchar(&tmpLoc, loc);
	size = wcstombs(0, tmpLoc, 0)+1;
	mbstr = new char[size];

	if (mbstr == NULL) {
		delete[] tmpLoc;
		return;
	}

	memset(mbstr, 0, size);
	size = wcstombs(mbstr, tmpLoc, wcslen(tmpLoc));
	setlocale(LC_ALL, mbstr);
	delete[] tmpLoc;
	delete[] mbstr;
*/
#endif
}
//------------------------------------------------------------------------------------------

