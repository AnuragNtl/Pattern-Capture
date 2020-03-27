#include "Dependencies.h"
#include <dlfcn.h>
#include "CommonUtils.h"

using namespace PatternCapture;


template<class Target>
Target* DependencyManager :: loadDependency(string fileName, string dependencyName) {
 void *handle = getOpenHandle(fileName);

 void *provider = loadDependency(handle, dependencyName.c_str());
 Target *target = ((Target* (*)(const char *))provider)(dependencyName.c_str( ));
return target;
   
}

void* DependencyManager :: loadDependency(void *dependencyHandle, const char*dependencyName) {
  void *provider = dlsym(dependencyHandle, PROVIDER_METHOD_NAME);
  if(provider == NULL) {
    throw DependencyException("No provider found");
  }
  return provider;
}

void* DependencyManager :: getOpenHandle(string fileName) {
  if(openHandles.find(fileName) == openHandles.end()) {
  void *handle = dlopen(fileName.c_str(), RTLD_NOW);
  openHandles.insert(pair<string, void *>(fileName, handle));
  }
  return openHandles[fileName];
}

vector<string> DependencyManager :: getAllSupportedDependencyTypes(string fileName) {
    void *handle = getOpenHandle(fileName);
    void *listerHandle = dlsym(handle, TYPE_LISTER_METHOD_NAME);
    if(listerHandle == NULL) {
     throw DependencyException("No listing found in library " + fileName); 
    }
    vector<string> (*hook)() = (vector<string>(*)()) listerHandle;
    return (*hook)();
}

DependencyException :: DependencyException(string message) {
this->message = message;
}

const char* DependencyException :: what() const noexcept {
  return message.c_str();
}

DependencyKey :: DependencyKey(string dependencyName, string dependencyId) : dependencyName(dependencyName), dependencyId(dependencyId) {}

bool DependencyKey :: operator<(const DependencyKey &other) const {
  if(dependencyName.compare(other.dependencyName) == 0) {
    return dependencyId.compare(other.dependencyId);
  } else {
    return dependencyName.compare(dependencyName);
  }
}

#define PLUGINS_DIRECTORY "libs/"
#define LIB_EXTENSION ".so"

namespace PatternCapture {
  DependencyManager dependencyManager;
  void initialize() {
    vector<string> libList = listDirectory
      (PLUGINS_DIRECTORY);
    for_each(libList.begin(), libList.end(), [](string lib) {
       if(!isValidLib(lib)) {
       return;
       }
       string libPath = PLUGINS_DIRECTORY + lib;
       vector<string> supportedDependencyTypes = dependencyManager.getAllSupportedDependencyTypes(libPath);
       for_each(supportedDependencyTypes.begin(), supportedDependencyTypes.end(), [libPath](string dependencyName)) {
        Dependency *dependency = loadDependencyFromFile(libPath, dependencyName);
        dependencyTypeWiseTable[DependencyKey(dependencyName, dependency.getId())] = dependency;
       });
        });
  }

  bool isValidLib(string libName) {
    string libExtension = LIB_EXTENSION;
    return libName.compare(libExtension, libName.size() - libExtension.size(), libExtension.size());
  }

  Dependency* loadDependencyFromFile(string fileName, string dependencyName) {
    return dependencyManager.loadDependency<Dependency>(dependenyName);
  }
};


