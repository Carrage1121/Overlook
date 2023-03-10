#pragma once

#include <memory>

#include "Overlook/Core/PlatformDetection.h"

#ifdef OL_DEBUG
#if defined(OL_PLATFORM_WINDOWS)
#define OL_DEBUGBREAK() __debugbreak()
#elif defined(OL_PLATFORM_LINUX)
#include <signal.h>
#define OL_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define OL_ENABLE_ASSERTS
#else
#define OL_DEBUGBREAK()
#endif

#define OL_EXPAND_MACRO(x) x
#define OL_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define OL_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Overlook {

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

#include "Overlook/Core/Log.h"
#include "Overlook/Core/Assert.h"