
#ifndef __ADDIN_LANGUAGE_H__
#define __ADDIN_LANGUAGE_H__


#include "AddInMemory.h"
#if !defined(wstring) || !defined(string)
#include <string>
#endif


/*------------------------------------------------------------------------------------------*/
//  class CAddInData: Encapsulation of a tVariant type
/*------------------------------------------------------------------------------------------*/
class AddInData {
public:
		// Default constructor
	AddInData (const tVariant* pVar = NULL) : varValue(NULL) {
		varValue = new tVariant;
		if (pVar == NULL) {
			tVarInit(varValue);
		} else {
			
		}
	}
		// Copy constructor
	AddInData (const AddInData& pObj) {
		varValue = new tVariant;
		tVarInit(varValue);

		switch (TV_VT(pObj.varValue)) {
			case VTYPE_PWSTR:
				TV_VT(varValue) = TV_VT(pObj.varValue);
				TV_JOIN(varValue, wstrLen) = TV_JOIN(pObj.varValue, wstrLen);
				TV_WSTR(varValue) = new WCHAR_T[TV_JOIN(varValue, wstrLen)];
				memcpy(TV_WSTR(varValue), TV_WSTR(pObj.varValue), TV_JOIN(varValue, wstrLen) * sizeof(WCHAR_T));
				break;
			case VTYPE_PSTR:
				TV_VT(varValue) = TV_VT(pObj.varValue);
				TV_JOIN(varValue, strLen) = TV_JOIN(pObj.varValue, strLen);
				TV_STR(varValue) = new char[TV_JOIN(varValue, strLen)];
				memcpy(TV_STR(varValue), TV_STR(pObj.varValue), TV_JOIN(varValue, strLen) * sizeof(char));
				break;
			default:
				memcpy(varValue, pObj.varValue, sizeof(tVariant));
				break;
		}
	}
		// Destructor
	virtual ~AddInData() {
		switch (TV_VT(varValue)) {
			case VTYPE_PWSTR:
				delete [] TV_WSTR(varValue);
				break;
			case VTYPE_PSTR:
				delete [] TV_STR(varValue);
				break;
		}

		delete varValue;
	}
public:
	AddInData& operator= (const tVariant* pVar) {
		if (this == pVar) {
			return *this;
		}

		switch (TV_VT(varValue)) {
			case VTYPE_PWSTR:
				delete [] TV_WSTR(varValue);
				break;
			case VTYPE_PSTR:
				delete [] TV_STR(varValue);
				break;
		}

		tVarInit(varValue);

		switch (TV_VT(pVar)) {
			case VTYPE_PWSTR:
				TV_VT(varValue) = TV_VT(pVar);
				TV_JOIN(varValue, wstrLen) = TV_JOIN(pVar, wstrLen);
				TV_WSTR(varValue) = new WCHAR_T[TV_JOIN(varValue, wstrLen)];
				memcpy(TV_WSTR(varValue), TV_WSTR(pVar), TV_JOIN(varValue, wstrLen) * sizeof(WCHAR_T));
				break;
			case VTYPE_PSTR:
				TV_VT(varValue) = TV_VT(pVar);
				TV_JOIN(varValue, strLen) = TV_JOIN(pVar, strLen);
				TV_STR(varValue) = new char[TV_JOIN(varValue, strLen)];
				memcpy(TV_STR(varValue), TV_STR(pVar), TV_JOIN(varValue, strLen) * sizeof(char));
				break;
			default:
				memcpy(varValue, pVar, sizeof(tVariant));
				break;
		}
	}
public:
		// Data access functions
	TYPEVAR Type () const {
		return TV_VT(varValue);
	}
	bool SetData (const tVariant* pVar) {
		::operator=(pVar);

		return true;
	}
	bool GetData (tVariant* pVar) {
		if (pVar == NULL) {
			return false;
		}

		switch (TV_VT(varValue)) {
			case VTYPE_PWSTR:
				TV_VT(pVar) = TV_VT(varValue);
				TV_JOIN(pVar, wstrLen) = TV_JOIN(varValue, wstrLen);
				TV_WSTR(pVar) = AddInMemory::AllocWchar(TV_JOIN(pVar, wstrLen));
				memcpy(TV_WSTR(pVar), TV_WSTR(varValue), TV_JOIN(pVar, wstrLen) * sizeof(WCHAR_T));
				break;
			case VTYPE_PSTR:
				TV_VT(pVar) = TV_VT(varValue);
				TV_JOIN(pVar, strLen) = TV_JOIN(varValue, strLen);
				TV_STR(pVar) = AddInMemory::AllocChar(TV_JOIN(pVar, strLen));
				memcpy(TV_STR(pVar), TV_STR(varValue), TV_JOIN(pVar, strLen) * sizeof(char));
				break;
			default:
				memcpy(pVar, varValue, sizeof(tVariant));
				break;
		}

		return true;
	}
	bool GetWstring (std::wstring& value) {
		switch  (TV_VT(varValue)) {
			case VTYPE_PWSTR:
				value = std::wstring(TV_WSTR(varValue));
				break;
			case VTYPE_PSTR:
				value = AddInConvert::StrToWstr(std::string(TV_STR(varValue)));
				break;
			default:
				return false;
		}

		return true;
	}
	bool GetString (std::string& value) {
		switch (TV_VT(varValue)) {
			case VTYPE_PWSTR:
				value = AddInConvert::WstrToStr(std::wstring(TV_WSTR(varValue)));
				break;
			case VTYPE_PSTR:
				value = std::string(TV_STR(varValue));
				break;
			default:
				return false;
		}

		return true;
	}
	bool GetNumeric (long& value) {
		if (TV_VT(varValue) != VTYPE_I4) {
			return false;
		}

		value = TV_I4(varValue);

		return true;
	}
private:
		// Attributes
	tVariant* varValue;
};


#endif	// __ADDIN_LANGUAGE_H__
