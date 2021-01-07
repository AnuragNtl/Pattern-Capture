#ifndef COMMON_H

#define COMMON_H

#include <map>
#include "../Dependencies.h"
#include "../core/engine/graphparser/GraphParser.h"
#include "../transform/Transform.h"
#include "../Capture/CaptureSource.h"
#include "../core/engine/hooks/Hooks.h"

using namespace std;


namespace PatternCapture {

    template<class InputData, class OutputData>
    class CommonDependency : public CaptureSource<OutputData>, public Transform<InputData, OutputData> {
        public:
            virtual void* operator()(void *input, map<string, string>);
            OutputData capture(map<string, string>);
            OutputData transform(InputData inputData, map<string, string>) const; 
            virtual OutputData getOutput(InputData input, map<string, string>) const = 0;

    };


    template<class InputData, class OutputData> OutputData CommonDependency<InputData, OutputData> :: capture(map<string, string> inputMap) {
            return getOutput(InputData(), inputMap);
        }

    template<class InputData, class OutputData>
        OutputData CommonDependency<InputData, OutputData> :: transform(InputData inputData, map<string, string> inputMap) const {
            return getOutput(inputData, inputMap);
        }

    template<class InputData, class OutputData>
       void* CommonDependency<InputData, OutputData> :: operator()(void *input, map<string, string> inputParams) { if(input == NULL) {
                return CaptureSource<OutputData>::operator()(&inputParams);
            } else {
                return Transform<InputData, OutputData>::operator()(input, inputParams);
            }
        }

};


#endif

