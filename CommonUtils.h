#ifndef COMMON_UTILS_H

#define COMMON_UTILS_H

#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <iostream>
#include <algorithm>

#include "StringSerializable.h"

using namespace std;
using namespace boost::filesystem;

#define DEPENDENCY_DECLARATION extern "C" { \
    extern Dependency* getDependency(const char *); \
    extern vector<string> getDependencyTypes(); \
}


namespace PatternCapture {
  vector<string> listDirectory(string);
  string getContents(istream &&in);
  string readLink(string path);
  bool isNumeric(string);
  bool pathExists(string);

  struct CommandOutput {
      char *error, *output;
      int errorLen, outputLen;
      CommandOutput(char *, char *, int, int);
  };

  CommandOutput* getCommandOutput(const char *input, size_t inputSize, string command, bool binary = false);

  struct BinData : public StringSerializable {
      private:
          void assign(std::string);
      public:
          char *data;
          int length;
          BinData& operator=(std::string);
          BinData();
          BinData(std::string);
          operator std::string();
  };
};
#endif

