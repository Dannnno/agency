#pragma once

#include <agency/execution_categories.hpp>
#include <agency/detail/tuple.hpp>
#include <utility>


namespace agency
{
namespace detail
{


// execution is nested, just return x
template<class ExecutionCategory1, class ExecutionCategory2, class T>
auto make_tuple_if_not_nested(nested_execution_tag<ExecutionCategory1,ExecutionCategory2>, T&& x)
  -> decltype(std::forward<T>(x))
{
  return std::forward<T>(x);
}


// execution is not nested, wrap up x in a tuple
template<class ExecutionCategory, class T>
auto make_tuple_if_not_nested(ExecutionCategory, T&& x)
  -> decltype(agency::detail::make_tuple(std::forward<T>(x)))
{
  return agency::detail::make_tuple(std::forward<T>(x));
}


template<class ExecutionCategory, class T>
auto make_tuple_if_not_nested(T&& x)
  -> decltype(make_tuple_if_not_nested(ExecutionCategory(), std::forward<T>(x)))
{
  return make_tuple_if_not_nested(ExecutionCategory(), std::forward<T>(x));
}


template<class ExecutionCategory1, class ExecutionCategory2, class T>
auto tie_if_not_nested(nested_execution_tag<ExecutionCategory1,ExecutionCategory2>, T&& x)
  -> decltype(std::forward<T>(x))
{
  return std::forward<T>(x);
}


template<class ExecutionCategory, class T>
auto tie_if_not_nested(ExecutionCategory, T&& x)
  -> decltype(agency::detail::tie(std::forward<T>(x)))
{
  return agency::detail::tie(std::forward<T>(x));
}


template<class ExecutionCategory, class T>
auto tie_if_not_nested(T&& x)
  -> decltype(tie_if_not_nested(ExecutionCategory(), std::forward<T>(x)))
{
  return tie_if_not_nested(ExecutionCategory(), std::forward<T>(x));
}


} // end detail
} // end agency

