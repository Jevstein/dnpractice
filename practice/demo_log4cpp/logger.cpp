/*
 *  logger.cpp 
 *  logger
 *
 *  Created by Jevstein on 2018/10/25 17:59.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 */

#include <iostream>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RemoteSyslogAppender.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include "logger.h"

Logger Logger::instance_;

bool Logger::init(const std::string& log_conf_file)
{
    try
    {
        log4cpp::PropertyConfigurator::configure(log_conf_file);
    }
    catch(log4cpp::ConfigureFailure& f)
    {
        std::cerr << " load log config file " << log_conf_file.c_str() << " failed with result : " << f.what()<< std::endl;
        return false;
    }

    category_ = &log4cpp::Category::getRoot();

    return true;
}

