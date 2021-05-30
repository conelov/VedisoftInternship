#include "src/DBLink/DBLink.hpp"
#include "testValues/values.hpp"
#include <QCoreApplication>

#if defined(TABLE_PROVIDER) || defined(TABLE_CARD) || defined(TABLE_LOG)
  #error "^^ redefinition"
#endif

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  DBLink dbLink;
  dbLink.insertToCache(tstv::providers);

  return EXIT_SUCCESS;
}
