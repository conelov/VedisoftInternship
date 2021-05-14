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
#ifndef NDEBUG
  #define DEUBG_INITNULLSTR = DEUBG_NULLSTR
#else
  #define DEUBG_INITNULLSTR
#endif

#endif // VEDISOFTINTERNSHIP_DEFFWD_HPP
