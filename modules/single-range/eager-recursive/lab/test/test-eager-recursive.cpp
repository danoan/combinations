#include <iostream>
#include <ctime>

#include "combinations/logger/logger.h"

#include "execution.h"
#include "correcteness.h"

using namespace Combinations::Test;

int main(int argc, char* argv[])
{
    if(argc<2)
    {
        std::cerr << "Usage: test-eager-recursive OUTPUT_FOLDER" << std::endl;
    }

    std::string outputFolder = argv[1];
    boost::filesystem::create_directories(outputFolder);

    std::ofstream ofs(outputFolder + "/log.txt");
    Logger logger(ofs,outputFolder,false);

    time_t now = time(0);
    ofs << ctime(&now) << "\n";

    bool flag = true;
    try
    {
        flag = flag && execution(10,3,logger);
        flag = flag && execution(3,3,logger);
        flag = flag && execution(0,3,logger);
        flag = flag && execution(200,3,logger);

        flag = flag && correcteness(logger);
    }catch(std::exception ex)
    {
            flag = false;
            ofs << ex.what() << "\n\n";
    }

    ofs.flush();
    ofs.close();

    assert(flag);


    return 0;
}