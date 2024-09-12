#pragma once
#include <type_traits>

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long long u64;
typedef signed long long s64;


template<typename T, T v>
struct t_constant
{
	static constexpr T value = v;
	constexpr operator T() noexcept { return value; }
	constexpr T operator()() noexcept { return value; }
};

struct t_true : t_constant<bool, true> {};
struct t_false : t_constant<bool, false> {};

template<typename A, typename B> struct is_same : t_false {};
template<typename A> struct is_same<A, A> : t_true {};
template<typename A> struct is_class : t_constant<bool, __is_class(A)> {};
template<typename A> struct is_union : t_constant<bool, __is_union(A)> {};

namespace Internal
{
	template<typename A> t_true test_ptr_conversion(const volatile A*);
	template<typename> t_false test_ptr_conversion(const volatile void*);

	template<typename B, typename D> auto test_base(int) -> decltype(test_ptr_conversion<B>(static_cast<D*>(nullptr)));
	template<typename, typename> auto test_base(...) -> t_true;
}
template<typename B, typename D> struct is_base : t_constant<bool, is_class<B>::value && is_class<D>::value && decltype(Internal::test_base<B, D>(0))::value> {};

template<class T> struct remove_reference { typedef T type; };
template<class T> struct remove_reference<T&> { typedef T type; };
template<class T> struct remove_reference<T&&> { typedef T type; };

#define THIS_TYPE() remove_reference<decltype(*this)>::type

namespace Internal { extern u32 next_id(); }
template<typename T> struct rt_type_id {
	static u32 id()
	{
		static u32 instanceId = Internal::next_id();
		return instanceId;
	}
	constexpr operator u32() { return id(); }
};

static constexpr u32 ct_hash32(const char* src, u32 length, u32 delta = 0)
{
	return length == 0 ? delta : ct_hash32(src + 1, length - 1, (*src * 0xBadDecaf) ^ delta);
}
template<class C, u32 Id> constexpr u32 c_type_id() { return Id; }
#define CT_TYPE_ID(c) c_type_id<::c, ct_hash32(#c, sizeof(#c) - 1)>()

