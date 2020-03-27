#ifndef CAPTURE_SOURCE_H

#define CAPTURE_SOURCE_H

#include <boost/property_tree/ptree.hpp
using namespace std;

namespace PatternCapture {
  class CaptureSource : public Dependency {
    public:
      void captureAsync(function<void(const CaptureData &captureData)> onComplete);
      virtual CaptureData& capture() = 0;
  };
};

