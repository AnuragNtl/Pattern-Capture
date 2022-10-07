#ifndef SCHEMA_GEN_H

#define SCHEMA_GEN_H

#include "./Dependencies.h"
#include "../SchedulerFactory.h"
#include "./core/engine/graphparser/schema/Schema.h"
#include "./core/engine/graphparser/schema/SchemaProperties.h"
#include <map>

namespace PatternCapture {

    struct SchedulerOptions {

        SchedulerOptions(std::vector<std::string>);

        std::vector<std::string> schedulerSupportedValues;
    };

    struct SchemaGenDetails {

        DependencyKey dependencyKey;
        Dependency *dependency;
        explicit SchemaGenDetails(DependencyKey dependencyKey, Dependency *dependency, SchedulerOptions schedulerOptions);
        SchedulerOptions schedulerOptions;
    };

    template<class E>
        class SchemaKeyGenerator {

            public:
                virtual Schema<E>* operator()(const SchemaGenDetails &schemaGenDetails) const = 0;

        };

        extern const std::map<std::string, function<Schema<SchemaContent>*(const SchemaGenDetails&)> > getSchemaNodeGenerators();

};


#endif

