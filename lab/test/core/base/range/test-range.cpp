#include <iostream>
#include <vector>

#include "magLac/lab/test/core/base/range/correcteness.h"

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
  logger << Logger::HeaderOne << "Test Range" << Logger::Normal;

  time_t now = time(0);
  *os << ctime(&now) << "\n";

  bool flag = true;
  try {
    flag = flag && Test::Range::correcteness(logger);
  } catch (std::exception &ex) {
    flag = false;
    logger << "Error: " << ex.what() << "\n";
  }

  os->flush();
  if (id.createStream) delete os;
  return flag ? 0 : 1;
}