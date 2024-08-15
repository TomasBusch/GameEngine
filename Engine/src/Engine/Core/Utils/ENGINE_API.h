#ifdef COMPILER_MSVC
	#ifdef BUILD_SHARED_LIBS
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#endif