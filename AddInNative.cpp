
#include "AddInNative.h"


uint32_t convToShortWchar(WCHAR_T** Dest, const wchar_t* Source, uint32_t len = 0);
uint32_t convFromShortWchar(wchar_t** Dest, const WCHAR_T* Source, uint32_t len = 0);
uint32_t getLenShortWcharStr(const WCHAR_T* Source);

/*------------------------------------------------------------------------------------------*/
//  Global Functions
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
	static WCHAR_T* names = NULL;
	if (names == NULL) {
		::convToShortWchar(&names, g_kClassNames);
	}

	return names;
}
//------------------------------------------------------------------------------------------

/*------------------------------------------------------------------------------------------*/
//  Main Dll Class CAddInNative::
/*------------------------------------------------------------------------------------------*/
CAddInNative::CAddInNative () {
}
//------------------------------------------------------------------------------------------
CAddInNative::~CAddInNative () {
}
//------------------------------------------------------------------------------------------


/*------------------------------------------------------------------------------------------*/
//  CAddInPQ::IInitDoneBase
/*------------------------------------------------------------------------------------------*/
bool CAddInNative::Init (void* pConnection) {
	return false;
}
//------------------------------------------------------------------------------------------
bool CAddInNative::setMemManager(void* pMemory) {
	return false;
}
//------------------------------------------------------------------------------------------
long CAddInNative::GetInfo () {
	return 2000; 
}
//------------------------------------------------------------------------------------------
void CAddInNative::Done () {
}
//------------------------------------------------------------------------------------------


/*------------------------------------------------------------------------------------------*/
// CAddInPQ::ILanguageExtenderBase
/*------------------------------------------------------------------------------------------*/
bool CAddInNative::RegisterExtensionAs (WCHAR_T** wsLanguageExt) {
	return false; 
}
//------------------------------------------------------------------------------------------
long CAddInNative::GetNProps () {
	return eLastProp;
}
//------------------------------------------------------------------------------------------
long CAddInNative::FindProp (const WCHAR_T* wsPropName) {
	return -1;
}
//------------------------------------------------------------------------------------------
const WCHAR_T* CAddInNative::GetPropName (long lPropNum, long lPropAlias) {
	return 0;
}
//------------------------------------------------------------------------------------------
bool CAddInNative::GetPropVal (const long lPropNum, tVariant* pvarPropVal) {
	return false;
}
//------------------------------------------------------------------------------------------
bool CAddInNative::SetPropVal (const long lPropNum, tVariant* varPropVal) {
	return false;
}
//------------------------------------------------------------------------------------------
bool CAddInNative::IsPropReadable (const long lPropNum) {
	return false;
}
//------------------------------------------------------------------------------------------
bool CAddInNative::IsPropWritable (const long lPropNum) {
	return false;
}
//------------------------------------------------------------------------------------------
long CAddInNative::GetNMethods () {
	return eLastMethod;
}
//------------------------------------------------------------------------------------------
long CAddInNative::FindMethod (const WCHAR_T* wsMethodName) {
	return -1;
}
//------------------------------------------------------------------------------------------
const WCHAR_T* CAddInNative::GetMethodName (const long lMethodNum, const long lMethodAlias) {
	return 0;
}
//------------------------------------------------------------------------------------------
long CAddInNative::GetNParams (const long lMethodNum) {
	return 0;
}
//------------------------------------------------------------------------------------------
bool CAddInNative::GetParamDefValue (const long lMethodNum, const long lParamNum, tVariant *pvarParamDefValue) {
	return false;
}
//------------------------------------------------------------------------------------------
bool CAddInNative::HasRetVal (const long lMethodNum) {
	return false;
}
//------------------------------------------------------------------------------------------
bool CAddInNative::CallAsProc (const long lMethodNum, tVariant* paParams, const long lSizeArray) {
	return false;
}
//------------------------------------------------------------------------------------------
bool CAddInNative::CallAsFunc(const long lMethodNum, tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray) {
	return false;
}
//------------------------------------------------------------------------------------------

/*------------------------------------------------------------------------------------------*/
// CAddInPQ::LocaleBase
/*------------------------------------------------------------------------------------------*/
void CAddInNative::SetLocale (const WCHAR_T* loc) {
#ifndef __linux__
	_wsetlocale(LC_ALL, loc);
#else
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
#endif
}
//------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------
uint32_t convToShortWchar (WCHAR_T** Dest, const wchar_t* Source, uint32_t len) {
	if (len == 0) {
		len = ::wcslen(Source) + 1;
	}

	if (*Dest == NULL) {
		*Dest = new WCHAR_T[len];
	}

	WCHAR_T* tmpShort = *Dest;
	wchar_t* tmpWChar = (wchar_t*)(Source);
	uint32_t res = 0;

	::memset(*Dest, 0, len * sizeof(WCHAR_T));
	do {
		*tmpShort++ = (WCHAR_T)(*tmpWChar++);
		++res;
	} while (len-- && *tmpWChar);

	return res;
}
//------------------------------------------------------------------------------------------
uint32_t convFromShortWchar (wchar_t** Dest, const WCHAR_T* Source, uint32_t len) {
	if (len == 0) {
		len = getLenShortWcharStr(Source) + 1;
	}

	if (*Dest == NULL) {
		*Dest = new wchar_t[len];
	}

	wchar_t* tmpWChar = *Dest;
	WCHAR_T* tmpShort = (WCHAR_T*)(Source);
	uint32_t res = 0;

	::memset(*Dest, 0, len * sizeof(wchar_t));
	do {
		*tmpWChar++ = (wchar_t)(*tmpShort++);
		++res;
	} while (len-- && *tmpShort);

	return res;
}
//------------------------------------------------------------------------------------------
uint32_t getLenShortWcharStr (const WCHAR_T* Source) {
	uint32_t res = 0;
	WCHAR_T *tmpShort = (WCHAR_T*)(Source);

	while (*tmpShort++) {
		++res;
	}

	return res;
}
//------------------------------------------------------------------------------------------
