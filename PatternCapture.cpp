#include "Dependencies.h"
#include <iostream>
#include "CommonUtils.h"
#include "core/engine/graphparser/GraphParserFactory.h"
#include "core/scheduler/Scheduler.h"
#include <fstream>


using namespace std; using namespace PatternCapture;

void processGraph(string parser, string data);

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
    initialize();
    if(argc > 1) {
        if(string(argv[1]) != "-g") {
            spec = getContents(std::ifstream(argv[1]));
        }
        else {
            SchemaProperties schemaProperties = generateSchemaProperties();
            cout << (string)schemaProperties << "\n";
            return 0;
        }
    } else {
        spec = getContents(std::move(cin));
    }
    processGraph("graphParserYaml", spec);

  return 0;
}

void processGraph(string parser, string data) {

    GraphParserFactory graphParserFactory;
    GraphParser *graphParser = graphParserFactory.getGraphParser(parser);
    Graph *graph = graphParser->parse(data.c_str());
    Scheduler *scheduler = new Scheduler(*graph);
    scheduler->execute();
}

void showUsage() {

    cout << "PatternCapture : Extensible Data Extraction Tool\n";
    cout << "Usage PatternCapture [PipelineSpecFile]\n";

}

#define BUF_LEN 1024

