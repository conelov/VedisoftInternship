//
// Created by dym on 27.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_PROPERTYGENERATOR_HPP
#define VEDISOFTINTERNSHIP_PROPERTYGENERATOR_HPP
#include <QMetaProperty>
#include <QVariant>
#include <cassert>

template<typename T, typename F= void>
class PropertyGenerator {
  using Index = decltype(std::declval<QMetaObject>().propertyOffset());
  using Gadget= T;
  using Filter= F;

private:
  Index _index;
  T &_obj;

public:
  PropertyGenerator(T &obj)
      : _index(T::staticMetaObject.propertyOffset())
      , _obj(obj)
  {}

  template<typename U= Filter>
  std::enable_if_t<std::is_same_v<U, void>, PropertyGenerator &> operator++()
  {
    ++_index;
    return *this;
  }

  template<typename U= Filter>
  std::enable_if_t<!std::is_same_v<U, void>, PropertyGenerator &> operator++()
  {
    Filter const filter;
    do {
      ++_index;
    } while (this->operator bool() &&
             !std::invoke(filter, QLatin1String{ property().name() }));
    return *this;
  }

  PropertyGenerator operator++(int)
  {
    auto ret= *this;
    this->operator++();
    return ret;
  }
  operator bool() const
  {
    return _index < T::staticMetaObject.propertyCount();
  }
  QVariant read() const
  {
    return T::staticMetaObject.property(_index).readOnGadget(&_obj);
  }
  bool write(QVariant const &val)
  {
    return T::staticMetaObject.property(_index).writeOnGadget(&_obj, val);
  }
  QMetaProperty property() const
  {
    return T::staticMetaObject.property(_index);
  }
};

#endif // VEDISOFTINTERNSHIP_PROPERTYGENERATOR_HPP
