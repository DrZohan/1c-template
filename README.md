# 1c-tempalte

https://its.1c.ru/db/metod8dev#content:3221:hdoc

1. Add original tempalte files: https://its.1c.ru/db/files/1CITS/EXE/VNCOMPS/VNCOMPS.zip?country=ru
The "1c-template" directory contains a template for creating components, developed by Native API technology. The "include" directory contains header files required for external component.

2. Edit files: AddInNative.h, AddInNative.cpp dllmain.cpp. Add comments, format code to common style.

3. Interface "IInitDoneBase" basic definition. Add static variable "gMemory" - a pointer to the 1C:Enterprise memory manager interface. Add static class AddInMemory - allocate memory for return values, wich can't be trasmitted completely through the stack.

4. Replace conversion functions by static class AddInConvert. Class convert between types: WCHAR_T <-> std::wstring and std::wstring <-> std::string. Change iternal varibales type from WCHAR_T to std::wstring. Add method ILanguageExtenderBase::RegisterExtensionAs definition.

5. "AddInLang.h" definition of accessory classes for easier use in main "AddIn" class.
	* Class AddInData - incapsulate "tVariant" structure in class. Add constructors (default, copy), destructor and assigment operator. Add some data access functions. Edit default constructor, assigment operator.

6. Add "AddInMemory.h" for static class AddInMemory and two methods: "AllocWchar" and "AllocChar".
