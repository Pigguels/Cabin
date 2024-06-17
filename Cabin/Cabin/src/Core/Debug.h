#pragma once
#include <iostream>
#include <cassert>

#ifdef NDEBUG

#define ASSERT(expression)
#define ASSERT_MSG(expression, message)
#define DEBUG_MSG(v)
#define DEBUG_MSG_WARNING(v)
#define DEBUG_MSG_ERROR(v)

#else

#define ASSERT(expression) (void)((!!(expression)) || (_wassert(L"[ASSERT]", _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0))
#define ASSERT_MSG(expression, message) (void)((!!(expression)) || (_wassert(_CRT_WIDE("[ASSERT] : " message), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0))
#define DEBUG_MSG(v) std::cout << __FILE__ << ": [MSG] : " v << std::endl
#define DEBUG_MSG_WARNING(v) std::cout << __FILE__ << ": [MSG : WARNING] : " << v << std::endl
#define DEBUG_MSG_ERROR(v) std::cout << __FILE__ << ": [MSG : ERROR] : " << v << std::endl

#endif
