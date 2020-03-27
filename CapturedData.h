#ifndef CAPTURE_DATA_H

#define CAPTURE_DATA_H

#include <string>
#include <boost/property_tree/ptree.hpp>

using namespace std;

using namespace boost::property_tree;


namespace PatternCapture {
  struct CapturedData {
    
    CapturedData(string);
    string id;
    ptree capturedData;

  };
};

#endif

