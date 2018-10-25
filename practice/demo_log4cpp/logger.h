/*
 *  logger.h 
 *  logger
 *
 *  Created by Jevstein on 2018/10/25 17:57.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  日志优先级：NOTSET < DEBUG < INFO < NOTICE < WARN < ERROR < CRIT < ALERT < FATAL = EMERG
 */
#ifndef DISTRIBUTED_LOGGER_H_
#define DISTRIBUTED_LOGGER_H_

#include <string>
#include <log4cpp/Category.hh>

class Logger
{
public:
    bool init(const std::string& log_conf_file);
    static Logger* instance(){ return  &instance_; };

    log4cpp::Category* GetHandle()
    {
        return category_;
    }

protected:
    static Logger instance_;
    log4cpp::Category * category_;
	
};

#define LOG_DEBUG Logger::instance()->GetHandle()->debug
#define LOG_INFO  Logger::instance()->GetHandle()->info
#define LOG_NOTICE  Logger::instance()->GetHandle()->notice
#define LOG_WARN  Logger::instance()->GetHandle()->warn
#define LOG_ERROR Logger::instance()->GetHandle()->error



//#define LOG(__level) log4cpp::Category::getRoot() << log4cpp::Priority::__level << __FILE__ << " " << __LINE__ << ": "
//LOG(DEBUG) << "i am happy.";
//LOG(INFO) << "oh, you happy, we happy.";
//LOG(NOTICE) << "please do not contact me. ";
//LOG(WARN) << "i am very busy now.";
//LOG(ERROR) << "oh, what happed?";


//// 输出到std::cout
//log4cpp::Appender *appender = new log4cpp::OstreamAppender("root", &std::cout);
//// 输出到log文件
////log4cpp::Appender *appender = new log4cpp::FileAppender("root", "test.log");
//
//log4cpp::PatternLayout *patternLayout = new log4cpp::PatternLayout();
//patternLayout->setConversionPattern("%d [%p] - %m%n");
//appender->setLayout(patternLayout);
//
//log4cpp::Category &root = log4cpp::Category::getRoot();
//root.setPriority(log4cpp::Priority::NOTICE);
//root.addAppender(appender);


#endif

