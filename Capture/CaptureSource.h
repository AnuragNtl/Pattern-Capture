#ifndef CAPTURE_SOURCE_H

#define CAPTURE_SOURCE_H

#include <boost/property_tree/ptree.hpp>
#include <functional>
#include <Dependencies.h>
#include <thread>

using namespace std;

/*
 *The dependencymanager will load all dependencies, their types and ids.
 Every first dependency is located with id and executed in seperate thread.
 Callback is assigned upon completion to pass response to next level.
 Each consumer in next level is started in new thread.
 Every item in each list in every level is started in new thread. hence threading to be done in DependencyManager
 The return value is casted as the type specified in template, and passed to next level
 In every level the direct passing of raw pointer needs to be replaced by passing of generic type
 */
namespace PatternCapture {
  template<class CapturedData>
  class CaptureSource : public Dependency {
    public:
      virtual CapturedData& capture(map<string, string> input) = 0;
      virtual string getId() const = 0;
      void* operator()(void *input);
  };
  


template<class CapturedData>
void* CaptureSource<CapturedData> :: operator()(void *input) {
  return &(capture(*(map<string, string>*) input));
}
};

#endif

