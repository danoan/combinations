#include <iostream>
#include <ctime>

#include "combinations/logger/logger.h"

#include "combinations/test/lazy-recursive/execution.h"
#include "combinations/test/lazy-recursive/correcteness.h"

using namespace Combinations;

std::ofstream ofs;
std::ostream& readInput(int argc,char* argv[])
{
    if(argc>=2)
    {
        std::string outputFolder = argv[1];
        boost::filesystem::create_directories(outputFolder);

        ofs = std::ofstream(outputFolder + "/log.txt");
        return ofs;
    }else
    {
        return std::cout;
    }
}

int main(int argc, char* argv[])
{
    std::ostream& os = readInput(argc,argv);
    Logger logger(os,false);

    logger < Logger::HeaderOne < "Test Lazy Recursive" < Logger::Normal;

    time_t now = time(0);
    os << ctime(&now) << "\n";

    bool flag = true;
    try
    {
        flag = flag && Test::execution(10,3,logger);
        flag = flag && Test::execution(3,3,logger);
        flag = flag && Test::execution(0,3,logger);
        flag = flag && Test::execution(50,3,logger);

        flag = flag && Test::correcteness(logger);
    }catch(std::exception ex)
    {
        flag = false;
        ofs << ex.what() << "\n\n";
    }

    os.flush();
    assert(flag);


    return 0;
}