//
// Created by dym on 20.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_APPENGINE_HPP
#define VEDISOFTINTERNSHIP_APPENGINE_HPP
#include <QObject>

class ModelProviderCard;
class AppEngine final: public QObject {
  Q_OBJECT
  Q_PROPERTY(ModelProviderCard *pcModel READ pcModel CONSTANT)

  struct Data;
  QScopedPointer<Data> _p;
  ModelProviderCard *const _providersModel;

public:
  ~AppEngine() override;
  AppEngine();

  Q_INVOKABLE ModelProviderCard *pcModel()
  {
    return _providersModel;
  }
};

#endif // VEDISOFTINTERNSHIP_APPENGINE_HPP
