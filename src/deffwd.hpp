//
// Created by dym on 12.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_DEFFWD_HPP
#define VEDISOFTINTERNSHIP_DEFFWD_HPP

#ifdef TO_LITERAL
  #error "^^ redefinition"
#endif
#define TO_LITERAL(x) #x

#ifdef DEBUG_INITNULL
  #error "^^ redefinition"
#endif
#ifndef NDEBUG
  #define DEBUG_INITNULL(x) = x
#else
  #define DEBUG_INITNULL(x)
#endif

#ifdef DEUBG_NULLSTR
  #error "^^ redefinition"
#endif
#define DEUBG_NULLSTR "NULL_STRING"

#ifdef DEUBG_INITNULLSTR
  #error "^^ redefinition"
#endif
#define DEUBG_INITNULLSTR DEBUG_INITNULL(DEUBG_NULLSTR)

class Provider;
template<typename T>
class QVector;
using ProviderVector= QVector<Provider>;
#endif // VEDISOFTINTERNSHIP_DEFFWD_HPP
