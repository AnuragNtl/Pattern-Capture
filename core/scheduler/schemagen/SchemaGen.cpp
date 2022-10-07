#include <functional>
#include "SchemaGen.h"

#define DEPENDENCY_TYPE_HOOKS "hooks"

namespace PatternCapture {

    SchedulerOptions :: SchedulerOptions(std::vector<std::string> schedulerSupportedValues) : schedulerSupportedValues(schedulerSupportedValues) { }

    SchemaGenDetails :: SchemaGenDetails(DependencyKey dependencyKey, Dependency *dependency, SchedulerOptions schedulerOptions) : dependencyKey(dependencyKey), dependency(dependency), schedulerOptions(schedulerOptions) { }

    EnumTypeProperties* getRepeatProperties(vector<string> supportedValues) {

            EnumTypeProperties *repeatProperties = new EnumTypeProperties;
            repeatProperties->_enum = supportedValues;
            return repeatProperties;
    }

    ObjectProperties* getGraphProperties(const SchemaGenDetails &schemaGenDetails) {

        ObjectProperties *graphProperties = new ObjectProperties;
        (*graphProperties)["repeat"] = getRepeatProperties(schemaGenDetails.schedulerOptions.schedulerSupportedValues);
        return graphProperties;

    }

    ObjectProperties* getHooksProperties(const SchemaGenDetails &schemaGenDetails) {
        ObjectProperties *hooksProperties = new ObjectProperties;
        for (Dependency *hook : filterDependenciesByType(DEPENDENCY_TYPE_HOOKS)) {
            ObjectProperties *hookProperties = new ObjectProperties;
            hookProperties->description = "Hook";
            set<string> params = hook->getRequiredParameters();
            for(string param : params) {
                auto primitiveProperties = new PrimitiveTypeProperties;
                primitiveProperties->type = STRING;
                hookProperties->properties[param] = primitiveProperties;
            }


            (*hooksProperties)[hook->getId()] = hookProperties;
        }
        return hooksProperties;
    }

    ArrayTypeProperties* getDeliversToNodesProperties(const SchemaGenDetails &) {
            ArrayTypeProperties *deliversToNodes = new ArrayTypeProperties;
            ObjectProperties *deliversToRef = new ObjectProperties;
            deliversToRef->ref = "#";
            deliversToNodes->items = deliversToRef;
            return deliversToNodes;
    }

    ObjectProperties* getInputProperties(const SchemaGenDetails &schemaGenDetails) {
        
            ObjectProperties *properties = new ObjectProperties;
            set<string> requiredParameters = schemaGenDetails.dependency->getRequiredParameters();
            for(const auto &property : requiredParameters) {

                PrimitiveTypeProperties *value = new PrimitiveTypeProperties;
                value->type = STRING;
                (*properties)[property] = value;
            }
            return properties;
    }

    const std::map<std::string, function<Schema<SchemaContent>*(const SchemaGenDetails&)> > getSchemaNodeGenerators() {
        std::map<std::string, function<Schema<SchemaContent>*(const SchemaGenDetails&)> > schemaNodeGen;
        schemaNodeGen["dependencyId"] = [] (const SchemaGenDetails &schemaGen) {
            EnumTypeProperties *options = new EnumTypeProperties { schemaGen.dependencyKey.dependencyId };
            return options;
        };
        schemaNodeGen["dependencyType"] = [] (const SchemaGenDetails &schemaGen) {
            EnumTypeProperties *options = new EnumTypeProperties { schemaGen.dependencyKey.dependencyId };
            return options;
        };

        schemaNodeGen["graphProperties"] = getGraphProperties;
        schemaNodeGen["hookProperties"] = getHooksProperties;
        schemaNodeGen["deliversToNodes"] = getDeliversToNodesProperties;
        schemaNodeGen["inputParams"] = getInputProperties;
        return schemaNodeGen;
    }
};

