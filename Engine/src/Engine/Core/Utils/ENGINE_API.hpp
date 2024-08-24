#ifdef COMPILER_MSVC
	#ifdef BUILD_SHARED_LIBS
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#endif


	//#if defined(_WIN32) && defined(_ENGINE_BUILD_DLL)
	//#define ENGINE_API __declspec(dllexport)
	//#elif defined(_WIN32) && defined(ENGINE_DLL)
	//#define ENGINE_API __declspec(dllimport)
	//#elif defined(__GNUC__) && defined(_ENGINE_BUILD_DLL)
	//#define ENGINE_API __attribute__((visibility("default")))
	//#else
	//#define ENGINE_API
	//#endif
