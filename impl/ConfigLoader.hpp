//
// Created by dym on 13.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_CONFIGLOADER_HPP
#define VEDISOFTINTERNSHIP_CONFIGLOADER_HPP
#include "Deffwd.hpp"
#include <QScopedPointer>

class ConfigLoaderBase;

template<class T>
class ConfigLoader;

template<>
class ConfigLoader<LogMsg> {
  //  pimpl pattern
  QScopedPointer<ConfigLoaderBase> base;

public:
  ~ConfigLoader();
  ConfigLoader();
  [[nodiscard]] LogMsgState state() const;
  [[nodiscard]] std::string fileName() const;
};

#endif // VEDISOFTINTERNSHIP_CONFIGLOADER_HPP
