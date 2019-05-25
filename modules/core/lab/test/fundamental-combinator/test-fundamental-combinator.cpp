#include <ctime>

#include "combinations/core/base/FundamentalCombinator.h"
#include "combinations/utils/displayUtils.h"

#include "combinations/logger/logger.h"
#include "combinations/test/fundamental-combinator/correcteness.h"
#include "combinations/test/fundamental-combinator/execution.h"

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

    logger < Logger::HeaderOne < "Test Fundamental Combinator" < Logger::Normal;

    time_t now = time(0);
    os << ctime(&now) << "\n";

    bool flag = true;
    try
    {
        flag = flag && Test::correcteness(logger);
        flag = flag && Test::execution(logger);
    }catch(std::exception ex)
    {
        flag=false;
        logger < "Error: " < ex.what() < "\n";
    }

    os.flush();
    assert(flag);

    return 0;
}