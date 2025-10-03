#pragma once

#ifdef RE_PLATFORM_WINDOWS
	#ifdef RE_BUILD_DLL
		#define RE_API __declspec(dllexport)
	#else
		#define RE_API __declspec(dllimport)

	#endif // RE_BUILD_DLL
#else
	#error RuiEngine only supports Windows!
#endif