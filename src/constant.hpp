//
// Created by dym on 08.06.2021.
//

#ifndef VEDISOFTINTERNSHIP_CONSTANT_HPP
#define VEDISOFTINTERNSHIP_CONSTANT_HPP
#include "deffwd.hpp"
#include <limits>

template<typename T>
struct null_constant{
    static constexpr auto value = std::numeric_limits<T>::max();
};

template<>
struct null_constant<QString>{
    static constexpr auto value = "NULL_STRING";
};

template<typename T>
constexpr auto null_constant_v = null_constant<T>::value;

#ifdef DEBUG_INITNULL
#    error "^^ redefinition"
#endif
#define DEBUG_INITNULL(T) DEBUG_INIT(null_constant_v<T>)

#endif // VEDISOFTINTERNSHIP_CONSTANT_HPP
