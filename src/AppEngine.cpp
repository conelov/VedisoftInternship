//
// Created by dym on 22.05.2021.
//
#include "AppEngine.hpp"
#include "src/entities/Card.hpp"
#include "src/entities/Provider.hpp"
#include "src/models/ModelProviderCard.hpp"

#include "testValues/values.hpp"

struct AppEngine::Data
{
  ProviderVector _providers;
};

AppEngine::~AppEngine()= default;
AppEngine::AppEngine()
    : QObject({})
    , _p(new Data
         /// Test set
         { tstv::providers })
    , _providersModel(new ModelProviderCard(_p->_providers, this))
{}