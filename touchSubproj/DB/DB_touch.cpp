#include "src/DBLink/DBLink.hpp"
#include "testValues/values.hpp"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  DBLink dbLink;
  dbLink.storeToDB(tstv::providers);



  return EXIT_SUCCESS;
}
