#include "Dependencies.h"
#include <iostream>
#include "CommonUtils.h"
#include "core/engine/graphparser/GraphParserFactory.h"
#include "core/scheduler/Scheduler.h"
#include <fstream>


using namespace std; using namespace PatternCapture;

void processGraph(string parser, string data);

string getContents(istream &&);

void showUsage();

int main(int argc, char *argv[]) {
  /*{  cout << "__\n";
  initialize();
  for_each(dependencyTypeWiseTable.begin(), dependencyTypeWiseTable.end(), [] (pair<DependencyKey, Dependency*> entry) {
      cout << entry.first << "=" << entry.second <<"\n";
      });
  Dependency *dependency = dependencyTypeWiseTable[DependencyKey("sampleCapture", "sample capture")];
  cout << dependency->getId() <<"\n";
  cout << *((int *)(*dependency)(NULL)) <<"\n";
  */

    string spec;
    if(argc > 1) {
        spec = getContents(std::ifstream(argv[1]));
    } else {
        spec = getContents(std::move(cin));
    }
    processGraph("graphParserJson", spec);
    cout << argc << "\n";

  return 0;
}

void processGraph(string parser, string data) {

    initialize();
    GraphParserFactory graphParserFactory;
    GraphParser *graphParser = graphParserFactory.getGraphParser(parser);
    Graph *graph = graphParser->parse(data.c_str());
    Scheduler *scheduler = new Scheduler;
    scheduler->execute(*graph);
}

void showUsage() {

    cout << "PatternCapture : Extensible Data Extraction Tool\n";
    cout << "Usage PatternCapture [PipelineSpecFile]\n";

}

#define BUF_LEN 1024

string getContents(istream &&in) {
    string data = "";
    char buffer[BUF_LEN];
    while(!in.eof()) {
        in.getline(buffer, 1023);
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

