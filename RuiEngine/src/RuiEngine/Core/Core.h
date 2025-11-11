#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define RE_PLATFORM_WINDOWS
	#endif // _WIN64
	#else
	#error "x86 Builds are not supported!"
#endif // _WIN32
// End of platform detection

#ifdef RE_DEBUG
	#if defined(RE_PLATFORM_WINDOWS)
		#define RE_DEBUGBREAK() __debugbreak()
	#else
	#error "Platform doesn't support debugbreak yet!"
	#endif

	#define RE_ENABLE_ASSERTS
#else
	#define RE_DEBUGBREAK()
#endif // RE_DEBUG

#ifdef RE_ENABLE_ASSERTS
	#define RE_ASSERT(x, ...) { if(!(x)) { RE_ERROR("Assertion Failed: {0}", __VA_ARGS__); RE_DEBUGBREAK(); } }
	#define RE_CORE_ASSERT(x, ...) { if(!(x)) { RE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); RE_DEBUGBREAK(); } }
#else
	#define RE_ASSERT(x, ...)
	#define RE_CORE_ASSERT(x, ...)
#endif // RE_ENABLE_ASSERTS



#ifdef RE_PLATFORM_WINDOWS
	#if RE_DYNAMIC_LINK
		#ifdef RE_BUILD_DLL
			#define RE_API __declspec(dllexport)
		#else
			#define RE_API __declspec(dllimport)
		#endif // RE_BUILD_DLL
	#else
		#define RE_API
	#endif // RE_DYNAMIC_LINK
#else
	#error RuiEngine only supports Windows!
#endif

#define BIT(x) (1 << x)
//#define RE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define RE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace RuiEngine {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#define RE_PROFILE 0

