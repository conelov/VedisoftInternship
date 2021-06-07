//
// Created by dym on 14.05.2021.
//

#ifndef VEDISOFTINTERNSHIP_CONFIGCACHE_HPP
#define VEDISOFTINTERNSHIP_CONFIGCACHE_HPP
#include "src/Logger/LoggerConfig.hpp"
#include "src/NetManager/NetManagerConfig.hpp"

class ConfigCache
{
public:
    LoggerConfig logger;

    NetManagerConfig netManager;
};

#endif // VEDISOFTINTERNSHIP_CONFIGCACHE_HPP
