//
// Created by dym on 20.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_APPENGINE_HPP
#define VEDISOFTINTERNSHIP_APPENGINE_HPP
#include "src/models/ModelProviderCard.hpp"
#include <QObject>

class AppEngine final: public QObject {
  Q_OBJECT
  Q_PROPERTY(ModelProviderCard *pcModel READ pcModel CONSTANT)

  ProviderVector _providers;
  ModelProviderCard *const _providersModel;

public:
  Q_INVOKABLE ModelProviderCard *pcModel()
  {
    return _providersModel;
  }

  AppEngine()
      : QObject({})
      , _providersModel(new ModelProviderCard(_providers, this))
  {
    /// Test set
    {
      Provider provider;
      provider.title= "Amazon.com";
      {
        Card card;
        card.credits    = 8500;
        card.codes_count= 100;
        provider.linkCards.push_back(std::move(card));
      }
      _providers.push_back(std::move(provider));
    }
    {
      Provider provider;
      provider.title= "iTunes";
      {
        Card card;
        card.credits    = 9494939;
        card.codes_count= 0;
        provider.linkCards.push_back(std::move(card));
      }
      {
        Card card;
        card.credits    = 10032;
        card.codes_count= 7485;
        provider.linkCards.push_back(std::move(card));
      }
      _providers.push_back(std::move(provider));
    }
  }

};

#endif // VEDISOFTINTERNSHIP_APPENGINE_HPP
