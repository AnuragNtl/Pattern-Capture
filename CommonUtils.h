#ifndef COMMON_UTILS_H

#define COMMON_UTILS_H

#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace boost::filesystem;

namespace PatternCapture {
  vector<string> listDirectory(string);
  string getContents(istream &&in);
  string readLink(string path);
};
#endif

