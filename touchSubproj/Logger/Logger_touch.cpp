#include "src/ConfigLoader/ConfigLoader.hpp"
#include "src/Logger/Logger.hpp"
#include "src/PropertyGenerator.hpp"
#include <QCoreApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  auto const state= ConfigLoader::load();

  Logger::loadState(state.logger);

  LOG_Debug << "testmsg 1"
            << "testmsg 2";

  return EXIT_SUCCESS;
}
