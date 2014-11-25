#pragma once

#include <tuple>

namespace qrtext {
namespace core {

/// Very useful template to determine lambda function traits like type of return value, types of arguments and so on.
/// Taken from here:
/// http://stackoverflow.com/questions/7943525/is-it-possible-to-figure-out-the-parameter-type-and-return-type-of-a-lambda
template <typename T>
struct function_traits
	: public function_traits<decltype(&T::operator())>
{
};
// For generic types, directly use the result of the signature of its 'operator()'

/// Specialization of a template for lambda functions.
template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
// we specialize for pointers to member function
{
	enum { arity = sizeof...(Args) };
	// arity is the number of arguments.

	typedef ReturnType result_type;

	template <size_t i>
	struct arg
	{
		typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
		// the i-th argument is equivalent to the i-th tuple element of a tuple
		// composed of those arguments.
	};
};

}
}
