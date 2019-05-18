#include "logger.h"

namespace Combinations
{
    namespace Test
    {
        template<class TClass>
        unsigned int Logger::length(const TClass& s)
        {
            std::stringstream temp;
            temp << s;

            return temp.str().size();
        }

        template<class TClass>
        void Logger::headerOne(const TClass& s)
        {
            unsigned int textLength = length(s);
            unsigned int tab = 10;
            unsigned int rowLength = 2*tab + textLength;

            os << "\n";

            for(int i=0;i<rowLength;++i) os << "#";
            os << "\n";

            for(int i=0;i<tab;++i) os << " ";
            os << s;
            for(int i=0;i<tab;++i) os << " ";
            os << "\n";

            for(int i=0;i<rowLength;++i) os << "#";
            os << "\n";

            os << "\n";

            os.flush();
        }

        template<class TClass>
        void Logger::headerTwo(const TClass& s)
        {
            unsigned int tab = 10;

            os << "\n";

            for(int i=0;i<tab;++i) os << "-";
            os << s;
            for(int i=0;i<tab;++i) os << "-";
            os << "\n";

            os.flush();
        }

        template<class TClass>
        void Logger::normal(const TClass& s)
        {
            os << s;
            os.flush();
        }

        template<class TClass>
        Logger& Logger::operator<(const TClass& s)
        {
            if(ft==HeaderOne) headerOne(s);
            else if(ft==HeaderTwo) headerTwo(s);
            else normal(s);

            return *this;
        }

        template<class TClass>
        Logger& Logger::operator<(const LoggableObject<TClass>& s)
        {
            //exportObject(s.object,s.name);
            return *this;
        }

        template<class TClass>
        Logger& Logger::operator-(const TClass& object)
        {
            ss << object << "-";
            return *this;
        }

        template<class TClass>
        Logger& Logger::operator^(const TClass& object)
        {
            ss << object;
            return *this;
        }
    }
}