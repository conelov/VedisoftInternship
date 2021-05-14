//
// Created by dym on 14.05.2021.
//
#include "src/configLoader/ConfigCache.hpp"
#include "src/configLoader/ConfigLoader.hpp"
#include "src/logger/Logger.hpp"

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);

  LOG_Info << "before init msg from main";

  auto const config= ConfigLoader::load();
  Logger::loadState(*config->logger);

  LOG_Info << "after init msg from main";

  return EXIT_SUCCESS;
}
