//
// Created by dym on 18.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_UTILS_HPP
#define VEDISOFTINTERNSHIP_UTILS_HPP
#include <utility>

template<class T, class U= T>
constexpr T exchange(T &obj, U &&new_value)
{
  T old_value= std::move(obj);
  obj        = std::forward<U>(new_value);
  return old_value;
}

template<typename F>
struct InvokeOnDestruct{
  F callback;

  InvokeOnDestruct() = delete;

  explicit InvokeOnDestruct(F && f) : callback(std::forward<F>(f)){}

  ~InvokeOnDestruct(){
    std::invoke(callback);
  }
};

#endif // VEDISOFTINTERNSHIP_UTILS_HPP
