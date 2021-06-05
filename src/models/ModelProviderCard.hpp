//
// Created by dym on 20.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_MODELPROVIDERCARD_HPP
#define VEDISOFTINTERNSHIP_MODELPROVIDERCARD_HPP
#include "src/deffwd.hpp"
#include <QAbstractListModel>

class Provider;

class ModelProviderCard final: public QAbstractListModel {
  Q_OBJECT

public:
  ProviderVector const &providers;

  ModelProviderCard(decltype(providers) provs, QObject *parent= nullptr);

  int rowCount(const QModelIndex &parent= QModelIndex()) const override;

  QVariant
  data(const QModelIndex &index, int role= Qt::DisplayRole) const override;

  void changedAll();
};
Q_DECLARE_METATYPE(ModelProviderCard *)

#endif // VEDISOFTINTERNSHIP_MODELPROVIDERCARD_HPP
