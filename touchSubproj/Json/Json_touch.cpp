#include "src/MarshalJson/MarshalJson.hpp"
#include "src/entities/Provider.hpp"
#include "testValues/json.hpp"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    /// TODO: file input
  QCoreApplication app(argc, argv);
  MarshalJson::deserialize(tstv::jsonDocumentSource);

  return EXIT_SUCCESS;
}
