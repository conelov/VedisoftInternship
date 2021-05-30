//
// Created by dym on 22.05.2021.
//
#include "ModelProviderCard.hpp"
#include "src/entities/Card.hpp"
#include "src/entities/Provider.hpp"

ModelProviderCard::ModelProviderCard(decltype(providers) provs, QObject *parent)
    : QAbstractListModel(parent)
    , providers(provs)
{}

int ModelProviderCard::rowCount(const QModelIndex &parent) const
{
  if (parent.isValid())
    return 0;
  return providers.count();
}
QVariant ModelProviderCard::data(const QModelIndex &index, int role) const
{
  if (!index.isValid() || role != Qt::DisplayRole)
    return QVariant();

  return QVariant::fromValue(providers[index.row()]);

  //  auto const &provider= providers[index.row()];
  //  Provider qmlProvider{ provider.title };
  //  for (auto const &card : provider.cards) {
  //    qmlProvider.cards.push_back(QVariant::fromValue(
  //        Card{ QStringLiteral("$") + QString::number(card.point),
  //                   QString::number(card.codes_count) }));
  //  }

  //  return QVariant::fromValue(qmlProvider);
}
