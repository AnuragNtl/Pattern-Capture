#ifndef TRANSFORM_H

#define TRANSFORM_H

#include <string>
using namespace std;
#include "Dependencies.h"

namespace PatternCapture {

    template<class InputData, class TransformedData>
        class Transform : public virtual Dependency {
            public:
                virtual void* operator()(void *input, map<string, string> inputParams);
                virtual TransformedData transform(InputData inputData, map<string, string>) const = 0;
        };

    template<class InputData, class TransformedData>
        void* Transform<InputData, TransformedData> :: operator()(void *input, map<string, string> inputParams) {
            InputData *inputData = (InputData *)input;
            TransformedData *transformedData = new TransformedData;
            *transformedData = transform(*inputData, inputParams);
            return transformedData;
        }
};

#endif

