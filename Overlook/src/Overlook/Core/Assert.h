#pragma once

#include "Overlook/Core/Base.h"
#include "Overlook/Core/Log.h"
#include <filesystem>

#ifdef OL_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define OL_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { OL##type##ERROR(msg, __VA_ARGS__); OL_DEBUGBREAK(); } }
#define OL_INTERNAL_ASSERT_WITH_MSG(type, check, ...) OL_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define OL_INTERNAL_ASSERT_NO_MSG(type, check) OL_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", OL_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define OL_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define OL_INTERNAL_ASSERT_GET_MACRO(...) OL_EXPAND_MACRO( OL_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, OL_INTERNAL_ASSERT_WITH_MSG, OL_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define OL_ASSERT(...) OL_EXPAND_MACRO( OL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define OL_CORE_ASSERT(...) OL_EXPAND_MACRO( OL_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
#define OL_ASSERT(...)
#define OL_CORE_ASSERT(...)
#endif