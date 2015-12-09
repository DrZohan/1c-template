
#ifndef __ADDIN_CONVERT_H__
#define __ADDIN_CONVERT_H__

#if !defined(wstring) || !defined(string)
#include <string>
#endif


/*------------------------------------------------------------------------------------------*/
//	static class AddInConvert: Convert WCHAR_T <-> wstring <-> string
/*------------------------------------------------------------------------------------------*/
class AddInConvert {
public:
	static uint32_t size (const WCHAR_T* source) {
		uint32_t len = 0;
		for (const WCHAR_T* it = source; *it != 0; ++it) {
			++len;
		}

		return len;
	}
public:		// Convert WCHAR_T <-> wstring
	static WCHAR_T* WstrToWchr (WCHAR_T* dest, const std::wstring& source, uint32_t len = 0) {
		if (len == 0) {
			len = source.size() + 1;
		}
		if (dest == NULL) {
			dest = new WCHAR_T[len];
		}

		WCHAR_T* tmp = dest;
		std::wstring::const_iterator it(source.begin());

		do {
			*tmp++ = static_cast<WCHAR_T>(*it++);
		} while (it != source.end());
		*tmp = '\0';

		return dest;
	}
	static std::wstring WchrToWstr (std::wstring& dest, const WCHAR_T* source, uint32_t len = 0) {
		if (len == 0) {
			len = ::size(source);
		}
		
		const WCHAR_T* tmp = source;
		dest.clear();

		do {
			dest.push_back(static_cast<wchar_t>(*tmp++));
		} while (len-- && *tmp);

		return dest;
	}
public:		// Convert wstring <-> string
	static std::wstring StrToWstr (const std::string& dest, std::locale loc = std::locale("Russian_Russia.1251")) {
		std::wstring res;

		for (std::string::const_iterator it(dest.begin()); it != dest.end(); ++it) {
			res += std::use_facet< std::ctype<wchar_t> >(loc).widen(*it);
		}

		return res;
	}
	static std::string WstrToStr (const std::wstring& dest, std::locale loc::locale("Russian_Russia.1251")) {
		std::string res;

		for (std::wstring::const_iterator it = dest.begin(); it != dest.end(); ++it) {
			res += std::use_facet< std::ctype<wchar_t> >(loc).narrow(*it);
		}

		return res;
	}
};

#endif	// __ADDIN_CONVERT_H__
