//
// Created by dym on 27.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_VALUES_HPP
#define VEDISOFTINTERNSHIP_VALUES_HPP
#ifndef NDEBUG
  #include "src/entities/Card.hpp"
  #include "src/entities/Provider.hpp"
namespace tstv
{
inline static const Card card= []
{
  Card card;
  card.featured = true;
  card.point    = 225000;
  card.credit   = 401;
  card.image_url= "someUrl";
  return card;
}();
inline static const ProviderVector providers= []
{
  ProviderVector ret;
  {
    Provider provider;
    provider.title= "Amazon.com";
    {
      Card card;
      card.point = 8500;
      card.credit= 100;
      provider.cards.push_back(std::move(card));
    }
    ret.push_back(std::move(provider));
  }
  {
    Provider provider;
    provider.title= "iTunes";
    provider.cards.push_back(card);
    {
      Card card;
      card.point = 1;
      card.credit= 0;
      provider.cards.push_back(std::move(card));
    }
    {
      Card card;
      card.point = 60;
      card.credit= 1200;
      provider.cards.push_back(std::move(card));
    }
    ret.push_back(std::move(provider));
  }
  return ret;
}();
} // namespace tstv
#endif
#endif // VEDISOFTINTERNSHIP_VALUES_HPP
