
#ifndef __ADDIN_LANGUAGE_H__
#define __ADDIN_LANGUAGE_H__


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
private:
		// Attributes
	tVariant* varValue;
};


#endif	// __ADDIN_LANGUAGE_H__
