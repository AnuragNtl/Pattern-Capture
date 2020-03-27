#ifndef PROCESS_INFO_CAPTURE_SOURCE_H

#define PROCESS_INFO_CAPTURE_SOURCE_H

#include "../CaptureSource.h"

namespace PatternCapture {
  class ProcessInfoCaptureSource : public CaptureSource {
    public:
     CaptureData& capture();
  };
};



#endif

