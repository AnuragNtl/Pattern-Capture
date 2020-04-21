#include "CaptureSource.h"
#include <thread>

using namespace std;

namespace PatternCapture {

template<class CapturedData>
CaptureFuture<CapturedData> :: CaptureFuture() : completed(false) {}

template<class CapturedData>
bool CaptureFuture<CapturedData> :: isCompleted() {

  return completed;
}

template<class CapturedData>
CapturedData* CaptureFuture<CapturedData> :: getData() {
  return capturedData;
}

template<class CapturedData>
CaptureFuture<CapturedData>*  CaptureSource<CapturedData> :: captureAsync(function<void(const CapturedData &)> onComplete) {
  /*CaptureFuture<CapturedData> *captureFuture = new CaptureFuture<CapturedData>;
  captureFuture->capturedData = NULL;
 captureFuture->completed = false;
 thread captureThread(capture);
 captureFuture->completed = true;
*/}

template<class CapturedData>
void* CaptureSource<CapturedData> :: operator()(void *input) {
  captureAsync([] (const CapturedData& ) {});
  return NULL;
}
};

