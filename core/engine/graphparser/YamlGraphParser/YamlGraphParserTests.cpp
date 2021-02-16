#include <iostream>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/parser.h>
#include <gtest/gtest.h>

using namespace std;

TEST(YamlParser, ParserTest) {

    string yaml = R"(
hookProperties:
    - b
    - p
    - q)";
    YAML::Node doc = YAML::Load(yaml);
    ASSERT_TRUE(doc.IsMap());
    YAML::Node hookProperties = doc["hookProperties"];
    ASSERT_TRUE(hookProperties.IsDefined());
    ASSERT_TRUE(hookProperties.IsSequence());
    ASSERT_FALSE(doc["abcd"].IsDefined());
    for(YAML::Node node : hookProperties) {
        cout << node.as<string>() << "\n";
    }
}


int main(int argc, char *argv[]) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

