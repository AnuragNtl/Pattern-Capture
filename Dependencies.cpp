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
    throw DependencyException(string("No provider found: ") + dlerror());
  }
  return provider;
}

void* DependencyManager :: getOpenHandle(string fileName) {
  if(openHandles.find(fileName) == openHandles.end()) {
  void *handle = dlopen(fileName.c_str(), RTLD_NOW);
  if(handle == NULL) {
    throw DependencyException("Cannot read " + fileName + string(" ") + dlerror());
  } 
  openHandles.insert(pair<string, void *>(fileName, handle));
  }
  return openHandles[fileName];
}

vector<string> DependencyManager :: getAllSupportedDependencyTypes(string fileName) {
    void *handle = getOpenHandle(fileName);
    void *listerHandle = dlsym(handle, TYPE_LISTER_METHOD_NAME);
    if(listerHandle == NULL) {
     throw DependencyException("No listing found in library " + fileName + ":" + dlerror()); 
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
  if(dependencyName == other.dependencyName) {
    return dependencyId.compare(other.dependencyId) < 0;
  } else {
    return dependencyName.compare(other.dependencyName) < 0;
  }
}


namespace PatternCapture {
  map<DependencyKey, Dependency*> dependencyTypeWiseTable;
  DependencyManager dependencyManager;
  void initialize() {
    vector<string> libList = listDirectory(PLUGINS_DIRECTORY);
    for_each(libList.begin(), libList.end(), [](string lib) {
        if(!isValidLib(lib)) {
       return;
       }
       string libPath = PLUGINS_DIRECTORY + lib;
       vector<string> supportedDependencyTypes;
       try {
        supportedDependencyTypes = dependencyManager.getAllSupportedDependencyTypes(libPath);
       } catch(DependencyException &e) {
        cout << e.what() << "\n";
       }
       for_each(supportedDependencyTypes.begin(), supportedDependencyTypes.end(), [libPath] (string dependencyName) {
        Dependency *dependency = loadDependencyFromFile(libPath, dependencyName);
        dependencyTypeWiseTable[DependencyKey(dependencyName, dependency->getId())] = dependency;
       });
        });
  }

  bool isValidLib(string libName) {
    string libExtension = LIB_EXTENSION;
    return libName.compare(libName.size() - libExtension.size(), libExtension.size(), libExtension) == 0;
  }

  Dependency* loadDependencyFromFile(string fileName, string dependencyName) {
    return dependencyManager.loadDependency<Dependency>(fileName, dependencyName);
  }

  ostream& operator<<(ostream &out, const DependencyKey &dependencyKey) {
    out << dependencyKey.dependencyName << " " << dependencyKey.dependencyId;
    return out;
  }

  Dependency* getDependency(string type, string id) {
      DependencyKey dependencyKey(type, id);
      if(dependencyTypeWiseTable.find(dependencyKey) == dependencyTypeWiseTable.end()) {
          throw DependencyException("No dependency found with id " + id);
      }
      return dependencyTypeWiseTable[dependencyKey];
  }

  bool dependencyExists(DependencyKey dependencyKey) {
      return dependencyTypeWiseTable.find(dependencyKey) != dependencyTypeWiseTable.end();
  }

};

