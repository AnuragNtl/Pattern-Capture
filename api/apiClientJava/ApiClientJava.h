#ifndef API_CLIENT_JAVA
#define API_CLIENT_JAVA

#include <map>
#include <string>
#include <vector>
#include "../ApiClient.h"

using namespace std;
using namespace PatternCapture;

class ApiClientJava : public ApiClient {
    public:
        ptree transfer(ptree input, map<string, string> properties); 
        string getId() const;
};

extern "C" {
    vector<string> getDependencyTypes();
    Dependency* getDependency(string);
};

#endif

