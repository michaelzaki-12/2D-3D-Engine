#pragma once
#include <memory>
#include <iostream>

#ifdef PR_PALTFORM_WINDOWS
#if PR_DYNAMIC_LINK
	#ifdef PR_BUILD_DLL
		#define	PIRATES_API __declspec(dllexport)	
	#else
		#define PIRATES_API __declspec(dllimport)
	#endif
#else
	#define PIRATES_API 
#endif

#else
	#error Pireates Doesnt Support Windows
#endif



#ifdef PR_ENABLE_ASSERTS
	#define PR_CLIENT_ASSERT(x, ...) {if(!(x)) {PR_CLIENT_ERROR("Assertion Faieled: {0}", __VA_ARGS__); __debugbreak();}
	#define PR_CORE_ASSERT(x, ...) {if(!(x)) {PR_CORE_ERROR("Assertion Faieled: {0}", __VA_ARGS__); __debugbreak();}
#else
	#define PR_CLIENT_ASSERT(x,...)
	#define PR_CORE_ASSERT(x,...)
#endif

#define PR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) 
#define BIT(x) (1 << x)

namespace Pirates
{

	template<typename T>
	using Scope = std::unique_ptr<T>;
	/*
	template <typename T, typename ... Args>
	constexpr Ref<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args));
	}
	*/

	template<typename T>
	using Ref = std::shared_ptr<T>;
	/*
	template <typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) 
	{
		return std::make_shared<T>(std::forward<Args>(args));
	}
	*/
}