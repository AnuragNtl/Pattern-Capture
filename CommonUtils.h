#ifndef COMMON_UTILS_H

#define COMMON_UTILS_H

#include <vector>
#include <string>
#include <boost/filesystem/path.hpp>

using namespace std;
using namespace boost::filesystem;

namespace PatternCapture {
  vector<string> listDirectory(string directory) {
    if(!is_directory(directory)) {
      throw exception;
    }
    vector<string> contents;
    path directoryPath(directory);
    for(auto it = directory_iterator(directoryPath); it != directory_iterator(); it++) {
      contents.push_back(it->path().filename().string());
    }
  }
};

#endif

