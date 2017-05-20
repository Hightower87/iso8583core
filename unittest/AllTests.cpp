#include <iostream>
#include "gtest/gtest.h"

char* applicationNameForBlueScreenAssert;

int main(int argc, char** argv) {
    applicationNameForBlueScreenAssert = argv[0];
    ::testing::InitGoogleTest(&argc, argv);
    //::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
