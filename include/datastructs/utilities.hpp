#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <concepts>
#include <iostream>

namespace datastructs {
// arithmetic concept
template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

} // namespace datastructs

#endif
