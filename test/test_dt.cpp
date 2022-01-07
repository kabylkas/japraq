// Synaq tester.
#include "synaq.h"

static void BasicTest()
{

}

int main() {
    synaq::Synaq test_runner;
    RUN_TEST(test_runner, BasicTest);

    return 0;
}