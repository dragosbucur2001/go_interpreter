#include <gtest/gtest.h>
#include "../src/token.h"

// Demonstrate some basic assertions.
TEST(HelloTest2, BasicAssertions) {
    Token t{'c'};
    ASSERT_TRUE(t.getChar() == 'c');
}
