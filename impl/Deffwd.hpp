//
// Created by dym on 12.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_DEFFWD_HPP
#define VEDISOFTINTERNSHIP_DEFFWD_HPP

#ifdef TO_LITERAL
  #error "^^ redefinition"
#endif
#define TO_LITERAL(x) #x

class ConfigLoader;
namespace log4cpp
{
class Category;
}

#endif // VEDISOFTINTERNSHIP_DEFFWD_HPP
