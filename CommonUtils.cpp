#include "CommonUtils.h"

namespace PatternCapture {
  vector<string> listDirectory(string directory) {
    if(!is_directory(directory)) {
      throw exception();
    }
    vector<string> contents;
    path directoryPath(directory);
    for(auto it = directory_iterator(directoryPath); it != directory_iterator(); it++) {
      contents.push_back(it->path().filename().string());
    }
    return contents;
  }
};


