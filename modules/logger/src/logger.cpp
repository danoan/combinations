#include "combinations/logger/logger.h"

namespace Combinations
{
    Logger::Logger(std::ostream& os,bool exportObjectsFlag):os(os),
    exportObjectsFlag(exportObjectsFlag),ft(Logger::Normal)
    {}

    void Logger::startTimer()
    {

        startTime = boost::posix_time::microsec_clock::local_time();
    }

    void Logger::endTimer()
    {
        endTime  = boost::posix_time::microsec_clock::local_time();

        boost::posix_time::time_duration diff = endTime - startTime;
        *this < diff.total_seconds() < "s " < diff.total_milliseconds() < "ms " < diff.total_microseconds() < "us \n";
    }

    std::string Logger::buffer()
    {
        std::string s = ss.str();

        ss.str("");
        ss.clear();

        return s;
    }

    Logger& Logger::operator<(FormattingType ft)
    {
        this->ft = ft;
        return *this;
    }

    Logger& Logger::operator<(bool b)
    {
        std::string s = b?"True":"False";
        os << s;

        os.flush();
        return *this;
    }
}