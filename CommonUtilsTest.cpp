#include "CommonUtils.h"
#include <gtest/gtest.h>

using namespace std;
using namespace PatternCapture;


TEST(SampleTest, Sample) {
    vector<string> directoryContents = listDirectory(".");
    for(const auto &file : directoryContents) {
        cout << file << "\n";
    }
}

TEST(ReadLinkTest, Sample) {
    ASSERT_EQ(readLink("/etc/vtrgb"), "/etc/alternatives/vtrgb");
}

int main(int argc, char *argv[]) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

