#include "CommonUtils.h"
#include <sys/stat.h>

namespace PatternCapture {
  vector<string> listDirectory(string directory) { if(!is_directory(directory)) {
      throw exception();
    }
    vector<string> contents;
    path directoryPath(directory);
    for(auto it = directory_iterator(directoryPath); it != directory_iterator(); it++) {
      contents.push_back(it->path().filename().string());
    }
    return contents;
  }

#define BUF_LEN 1024

string getContents(istream &&in) {
    string data = "";
    char buffer[BUF_LEN];
    while(!in.eof()) {
        in.getline(buffer, BUF_LEN - 1);
        int count = in.gcount();
        buffer[count] = '\0';
        data.append(buffer);
    }
        std::ifstream *file = dynamic_cast<std::ifstream*>(&in);
    if(file != NULL) {
        file->close();
    }
    return data;
}

string readLink(string path) {
    char *buf = new char[BUF_LEN];
    int status;
    status = readlink(path.c_str(), buf, BUF_LEN - 1);
    if(status) {
        buf[status] = '\0';
    } else {
        buf[0] = '\0';
    }
    return string(buf);

}


};


