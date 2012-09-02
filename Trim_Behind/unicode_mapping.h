#ifndef UNICODE_CPLUSPLUS_MAPPING
#define UNICODE_CPLUSPLUS_MAPPING
	#ifdef UNICODE
		#define  _tstring wstring
		#define _tcout wcout
		#define _tcin wcin
		#define _tcerr wcerr
	#else
		#define  _tstring string
		#define _tcout cout
		#define _tcin cin
		#define _tcerr cerr
	#endif
#endif
