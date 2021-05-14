//
// Created by dym on 14.05.2021.
//
#include "ConfigCache.hpp"
#include "../logger/LoggerConfig.hpp"

ConfigCache::~ConfigCache()= default;
ConfigCache::ConfigCache()
    : logger(new LoggerConfig)
{}
