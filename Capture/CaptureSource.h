#ifndef CAPTURE_SOURCE_H

#define CAPTURE_SOURCE_H

#include <boost/property_tree/ptree.hpp>
#include <functional>
#include <Dependencies.h>

using namespace std;


namespace PatternCapture {
  template<class CapturedData>
  class CaptureFuture {
    
    private:
      CapturedData *capturedData;
      volatile bool completed;
    public:
      CaptureFuture();
      bool isCompleted();
      CapturedData* getData();
  };

  template<class CapturedData>
  class CaptureSource : public Dependency {
    public:
      CaptureFuture<CapturedData>* captureAsync(function<void(const CapturedData &)> onComplete);
      virtual CapturedData& capture(char *input[]) = 0;
      virtual string getId() const = 0;
//      void* operator()(void *input);
  };
};

#endif

