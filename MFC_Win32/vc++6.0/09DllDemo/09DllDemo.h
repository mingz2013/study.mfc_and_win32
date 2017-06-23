
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MY09DLLDEMO_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MY09DLLDEMO_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef MY09DLLDEMO_EXPORTS // 这里的dll工程会预定义MY09DLLDEMO_EXPORTS 宏
#define MY09DLLDEMO_API __declspec(dllexport)
#else
#define MY09DLLDEMO_API __declspec(dllimport)
#endif

// This class is exported from the 09DllDemo.dll
class MY09DLLDEMO_API CMy09DllDemo {
public:
	CMy09DllDemo(void);
	// TODO: add your methods here.
};

extern MY09DLLDEMO_API int nMy09DllDemo;

MY09DLLDEMO_API void ExportFunc(LPCTSTR pszContent);

