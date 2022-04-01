#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include <functional>

using namespace std;

#define PROVIDER_METHOD_NAME "getDependency"
#define TYPE_LISTER_METHOD_NAME "getDependencyTypes"

#define PLUGINS_DIRECTORY "lib/"
#define LIB_EXTENSION ".so"


namespace PatternCapture {
    class HookProperties;
  class DependencyManager {
    private:
    void* loadDependency(void *dependencyHandle, const char *dependencyName);
    map<string, void *> openHandles;

    void* getOpenHandle(string fileName);
    public:
    template<class Target>
    Target* loadDependency(string fileName, string dependencyName);
    vector<string> getAllSupportedDependencyTypes(string fileName);
  };

  class DependencyException : public exception {

    private:
      string message;
    public:
    DependencyException(string message);
    const char* what() const noexcept;
  };

  class Dependency {
      private:
          function<void(const HookProperties &)> onHookCall;
      public:
          Dependency() : onHookCall([] (const HookProperties &) { }) { }
          virtual string getId() const = 0;
          virtual void* operator()(void *input) { return NULL; }
          virtual void* operator()(void *input, map<string, string> params) {
              if(params.size() == 0)
                  return (*this)(input);
              return NULL; 
          }
          void callHook(const HookProperties &hookProperties) {
              this->onHookCall(hookProperties);
          }
          virtual ~Dependency() {}
          void setOnHookCall(function<void(const HookProperties &)> onHookCall) {
              this->onHookCall = onHookCall;
          }
          virtual set<string> getRequiredParameters() { return {}; }
  };

  /*Dependency :: Dependency() : onHookCall([] (const HookProperties &) {})   { }

  void Dependency :: setOnHookCall(function<void(const HookProperties &)> onHookCall) {
      this->onHookCall = onHookCall;
  }

  void Dependency :: callHook(const HookProperties &hookProperties) {
      this->onHookCall(hookProperties);
  }
*/
  struct DependencyKey {
    string dependencyName;
    string dependencyId;
    DependencyKey(string, string);
    bool operator<(const DependencyKey &) const;
  };
  extern map<DependencyKey, Dependency *> dependencyTypeWiseTable;
  Dependency* getDependency(string type, string id);
  void initialize();
  bool isValidLib(string libName);
  Dependency* loadDependencyFromFile(string fileName, string);
  bool dependencyExists(DependencyKey);
  ostream& operator<<(ostream &out, const DependencyKey &dependencyKey); 
};
#endif

