// refer: http://www.drdobbs.com/cpp/logging-in-c/201804215

#ifndef __LOG_H__
#define __LOG_H__

#include <sstream>
#include <string>
#include <cstdio>

inline std::string NowTime();

enum TLogLevel {ERROR, WARNING, INFO, DEBUG};

class Log
{
public:
    Log();
    virtual ~Log();
    std::ostringstream& Get(TLogLevel level = INFO);
public:
    static TLogLevel& ReportingLevel();
    static std::string ToString(TLogLevel level);
    static TLogLevel FromString(const std::string& level);
protected:
    std::ostringstream os;
private:
    Log(const Log&);
    Log& operator =(const Log&);
};

inline Log::Log()
{
}

inline std::ostringstream& Log::Get(TLogLevel level)
{
    os << "- " << NowTime();
    os << " " << ToString(level) << ": ";
    os << std::string(level > DEBUG ? level - DEBUG : 0, '\t');
    return os;
}

inline Log::~Log()
{
    os << std::endl;
    fprintf(stderr, "%s", os.str().c_str());
    fflush(stderr);
}

inline TLogLevel& Log::ReportingLevel()
{
    static TLogLevel reportingLevel = DEBUG;
    return reportingLevel;
}

inline std::string Log::ToString(TLogLevel level)
{
	static const char* const buffer[] = {"ERROR", "WARNING", "INFO", "DEBUG"};
    return buffer[level];
}

inline TLogLevel Log::FromString(const std::string& level)
{
    if (level == "DEBUG")
        return DEBUG;
    if (level == "INFO")
        return INFO;
    if (level == "WARNING")
        return WARNING;
    if (level == "ERROR")
        return ERROR;
    return INFO;
}

#define LOG(level) \
    if (level > Log::ReportingLevel()) ; \
    else Log().Get(level)

#include <sys/time.h>

inline std::string NowTime()
{
    char buffer[11];
    time_t t;
    time(&t);
    tm r = {0};
    strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
    struct timeval tv;
    gettimeofday(&tv, 0);
    char result[100] = {0};
    std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000); 
    return result;
}

#endif //__LOG_H__
