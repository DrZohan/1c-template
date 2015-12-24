
#ifndef __ADDIN_NATIVE_H__
#define __ADDIN_NATIVE_H__


#ifndef __linux__

#define _WINDOWS
#include <wtypes.h>

#else

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#endif	// __linux__

#include <string>

#include "ComponentBase.h"
#include "AddInDefBase.h"
#include "IMemoryManager.h"
#include "AddInMemory.h"
#include "AddInConvert.h"
#include "AddInLang.h"


/*------------------------------------------------------------------------------------------*/
//	Constants
/*------------------------------------------------------------------------------------------*/
static const std::wstring gClassNames(L"CAddInNative");		// "..|OtherClass1|OtherClass2"
static const std::wstring gExtensionName(L"AddInNativeExt");


/*------------------------------------------------------------------------------------------*/
//	class CAddInNative:
/*------------------------------------------------------------------------------------------*/
class CAddInNative : public IComponentBase {
public:
	CAddInNative();
	virtual ~CAddInNative();
public:
	operator IComponentBase*() { return (IComponentBase*)(this); }
public:		// IInitDoneBase
	virtual bool ADDIN_API Init(void* pConnection);
	virtual bool ADDIN_API setMemManager(void* pMemory);
	virtual long ADDIN_API GetInfo();
	virtual void ADDIN_API Done();
public:		// ILanguageExtenderBase
	virtual bool ADDIN_API RegisterExtensionAs(WCHAR_T** wsLanguageExt);
	virtual long ADDIN_API GetNProps();
	virtual long ADDIN_API FindProp(const WCHAR_T* wsPropName);
	virtual const WCHAR_T* ADDIN_API GetPropName(long lPropNum, long lPropAlias);
	virtual bool ADDIN_API GetPropVal(const long lPropNum, tVariant* pvarPropVal);
	virtual bool ADDIN_API SetPropVal(const long lPropNum, tVariant* varPropVal);
	virtual bool ADDIN_API IsPropReadable(const long lPropNum);
	virtual bool ADDIN_API IsPropWritable(const long lPropNum);
	virtual long ADDIN_API GetNMethods();
	virtual long ADDIN_API FindMethod(const WCHAR_T* wsMethodName);
	virtual const WCHAR_T* ADDIN_API GetMethodName(const long lMethodNum, const long lMethodAlias);
	virtual long ADDIN_API GetNParams(const long lMethodNum);
	virtual bool ADDIN_API GetParamDefValue(const long lMethodNum, const long lParamNum, tVariant *pvarParamDefValue);
	virtual bool ADDIN_API HasRetVal(const long lMethodNum);
	virtual bool ADDIN_API CallAsProc(const long lMethodNum, tVariant* paParams, const long lSizeArray);
	virtual bool ADDIN_API CallAsFunc(const long lMethodNum, tVariant* pvarRetValue, tVariant* paParams, const long lSizeArray);
public:		// LocaleBase
	virtual void ADDIN_API SetLocale(const WCHAR_T* loc);
private:	// Attributes
	IAddInDefBase* iConnect;
	IAddInDefBase* iAsyncEvent;
	AddInLang<AddInProp> iProp;
	AddInLnag<AddInMeth> iMeth;
};

#endif	// __ADDIN_NATIVE_H__
