
#ifndef __ADDIN_LANGUAGE_H__
#define __ADDIN_LANGUAGE_H__


#include "AddInMemory.h"
#if !defined(wstring) || !defined(string)
#include <string>
#endif

#if !defined(vector)
#include <vector>
#include <algorithm>
#endif


/*------------------------------------------------------------------------------------------*/
//  class CAddInData: Encapsulation of a tVariant type
/*------------------------------------------------------------------------------------------*/
class AddInData {
public:
		// Default constructor
	AddInData (const tVariant* pVar = NULL) : varValue(NULL) {
		varValue = new tVariant;
		tVarInit(varValue);

		if (pVar != NULL) {
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
	AddInData& operator= (const AddInData& pObj) {
		if (this != &pObj) {
			AddInData(pObj);
		}

		return *this;
	}
	AddInData& operator= (const tVariant* pVar) {
		switch (TV_VT(varValue)) {
			case VTYPE_PWSTR:
				delete [] TV_WSTR(varValue);
				break;
			case VTYPE_PSTR:
				delete [] TV_STR(varValue);
				break;
		}

		tVarInit(varValue);
		AddInData(pVar);

		return *this;
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


/*------------------------------------------------------------------------------------------*/
//  class CAddInBase: Base class for property and method classes
/*------------------------------------------------------------------------------------------*/
enum eAlias {
	eAliasRu = 0,
	eAliasEn
};

class AddInBase {
public:
	AddInBase (const std::wstring& eng = L"", const std::wstring& rus = L"")
		: wsNameEng(eng), wsNameRus(rus) { }
	virtual ~AddInBase () { }
public:
	const std::wstring GetName (const long alias = eAliasEn) {
		switch (alias) {
			case eAliasEn:
				return wsNameEng;
			case eAliasRu:
				return wsNameRus;
			default:
				return std::wstring();
		}
	}
private:
	std::wstring wsNameEng;
	std::wstring wsNameRus;
};

/*------------------------------------------------------------------------------------------*/
//  class CAddInProp: ILanguageExtender Property Class
/*------------------------------------------------------------------------------------------*/
class AddInProp : public AddInBase {
public:
	AddInProp (const std::wstring& eng = L"", const std::wstring& rus = L"", bool read = false, bool write = false)
		: AddInBase(eng, rus), bReadable(read), bWritable(write), data() { }
	virtual ~AddInProp () { }
public:
	bool IsReadable () const { return bReadable; }
	bool IsWritable () const { return bWritable; }

	bool SetData (const tVariant* value) { return data.SetData(value); }
	bool GetData (tVariant* value) { return data.GetData(value); }
	bool GetString (std::string& value) { return data.GetString(value); }
	bool GetNumeric (long& value) { return data.GetNumeric(value); }

private:
	bool bReadable;
	bool bWritable;
	AddInData data;
};

/*------------------------------------------------------------------------------------------*/
//  class CAddInMeth: ILanguageExtender Method Class
/*------------------------------------------------------------------------------------------*/
class AddInMeth : public AddInBase {
public:
	AddInMeth (const std::wstring& eng = L"", const std::wstring& rus = L"", bool func = false, long param = 0)
		: AddInBase(eng, rus), bFunction(func), nParam(param) { }
	virtual ~AddInMeth () { }
public:
	bool IsFunction () const { return bFunction; }
	long GetNParams () const { long nParam; }
private:
	bool bFunction;
	long nParam;
};

/*------------------------------------------------------------------------------------------*/
//  class CAddInLang: Template Container for AddInBase Classes
/*------------------------------------------------------------------------------------------*/
template<class T> class AddInLang {
public:
	AddInLang () : vArray() { }
	~AddInLang () { }
public:
	long Size () const { return vArray.size(); }
	void Push (const T& obj) { vArray.push_back(obj); }
	T& operator[] (long pos) { return vArray.at(pos); }
	const long Find (const std::wstring& name) const {
		for (std::vector<T>::const_iterator it = vArray.begin(); it != vArray.end(); ++it) {
			if (!name.compare( (static_cast<AddInBase>(*it)).GetName(eAliasEn) ) || !name.compare( (static_cast<AddInBase>(*it)).GetName(eAliasRu) )) {
				return std::distance(vArray.begin(), it);
			}
		}

		return -1;
	}
private:
	std::vector<T> vArray;
};



#endif	// __ADDIN_LANGUAGE_H__
