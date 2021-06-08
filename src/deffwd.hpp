//
// Created by dym on 12.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_DEFFWD_HPP
#define VEDISOFTINTERNSHIP_DEFFWD_HPP

#ifdef TO_LITERAL
#    error "^^ redefinition"
#endif
#define TO_LITERAL(x) #x

#ifdef DEBUG_INIT
#    error "^^ redefinition"
#endif
#ifndef NDEBUG
#    define DEBUG_INIT(x) = x
#else
#    define DEBUG_INIT(x)
#endif

class Provider;
class Card;
class Logger;
class NetManager;
class ModelProviderCard;
class ConfigCache;
class NetManager;

class QString;
template<typename T>
class QVector;

using ProviderVector = QVector<Provider>;

#endif // VEDISOFTINTERNSHIP_DEFFWD_HPP
