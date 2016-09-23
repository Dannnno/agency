#include <iostream>
#include <type_traits>
#include <vector>

#include <agency/execution/executor/vector_executor.hpp>
#include <agency/execution/executor/new_executor_traits.hpp>

int main()
{
  static_assert(agency::is_bulk_synchronous_executor<agency::vector_executor>::value,
    "vector_executor should be a bulk synchronous executor");

  static_assert(agency::is_bulk_executor<agency::vector_executor>::value,
    "vector_executor should be a bulk executor");

  static_assert(agency::detail::is_detected_exact<size_t, agency::new_executor_shape_t, agency::vector_executor>::value,
    "vector_executor should have size_t shape_type");

  static_assert(agency::detail::is_detected_exact<size_t, agency::new_executor_index_t, agency::vector_executor>::value,
    "vector_executor should have size_t index_type");

  static_assert(agency::detail::is_detected_exact<std::future<int>, agency::new_executor_future_t, agency::vector_executor, int>::value,
    "vector_executor should have std::future furture");

  agency::vector_executor exec;

  size_t shape = 10;
  
  auto result = exec.bulk_execute(
    [](size_t idx, std::vector<int>& results, std::vector<int>& shared_arg)
    {
      results[idx] = shared_arg[idx];
    },
    shape,
    [=]{ return std::vector<int>(shape); },     // results
    [=]{ return std::vector<int>(shape, 13); }  // shared_arg
  );
  
  assert(std::vector<int>(10, 13) == result);

  std::cout << "OK" << std::endl;

  return 0;
}

