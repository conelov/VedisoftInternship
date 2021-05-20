//
// Created by dym on 20.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_MODELPROVIDERCARD_HPP
#define VEDISOFTINTERNSHIP_MODELPROVIDERCARD_HPP
#include "src/entities/aggregates.hpp"
#include <QAbstractListModel>

class ModelProviderCard final: public QAbstractListModel {
  Q_OBJECT

public:
  ProviderVector const &providers;

  ModelProviderCard(decltype(providers) provs, QObject *parent= nullptr)
      : QAbstractListModel(parent)
      , providers(provs)
  {}

  int rowCount(const QModelIndex &parent= QModelIndex()) const override
  {
    if (parent.isValid())
      return 0;
    return providers.count();
  }

  QVariant
  data(const QModelIndex &index, int role= Qt::DisplayRole) const override
  {
    if (!index.isValid() || role != Qt::DisplayRole)
      return QVariant();

    auto const &provider= providers[index.row()];
    qml::Provider qmlProvider{ provider.title };
    for (auto const &card : provider.linkCards) {
      /// TODO: Добавить разделители к числам
      qmlProvider.cards.push_back(QVariant::fromValue(
          qml::Card{ QStringLiteral("$") + QString::number(card.credits),
                     QString::number(card.codes_count) }));
    }
    return QVariant::fromValue(qmlProvider);
  }
};
#endif // VEDISOFTINTERNSHIP_MODELPROVIDERCARD_HPP
