#include <iostream>
#include <ctime>

#include "magLac/lab/logger/logger.h"
#include "execution.h"
#include "correcteness.h"

using namespace magLac;

struct InputData {

  std::string outputFolder;
  bool createStream;
};

InputData readInput(int argc, char *argv[]) {
  InputData id;
  if (argc >= 2) {
    id.outputFolder = argv[1];
    id.createStream = true;

    boost::filesystem::create_directories(id.outputFolder);
  } else {
    id.createStream = false;
  }

  return id;
}

int main(int argc, char *argv[]) {
  InputData id = readInput(argc, argv);

  std::ostream *os;
  if (id.createStream)
    os = new std::ofstream(id.outputFolder + "/log.txt");
  else
    os = &std::cout;

  Logger logger(*os, false);
  logger << Logger::HeaderOne << "Test Lazy Recursive" << Logger::Normal;

  time_t now = time(0);
  *os << ctime(&now) << "\n";

  bool flag = true;
  try {
    flag = flag && Test::execution(10, 3, logger);
    flag = flag && Test::execution(3, 3, logger);
    flag = flag && Test::execution(0, 3, logger);
    flag = flag && Test::execution(50, 3, logger);

    flag = flag && Test::correcteness(logger);
  } catch (std::exception &ex) {
    flag = false;
    *os << ex.what() << "\n\n";
  }

  os->flush();
  if (id.createStream) delete os;

  return flag ? 0 : 1;
}