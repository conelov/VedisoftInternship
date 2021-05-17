//
// Created by dym on 18.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_UTILS_HPP
#define VEDISOFTINTERNSHIP_UTILS_HPP

template<class T, class U = T>
constexpr T exchange(T& obj, U&& new_value)
{
  T old_value = std::move(obj);
  obj = std::forward<U>(new_value);
  return old_value;
}
#endif // VEDISOFTINTERNSHIP_UTILS_HPP
