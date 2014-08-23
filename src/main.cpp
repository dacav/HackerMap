#include <config.h>
#include <iostream>

int main (int argc, char **argv)
{
    std::cout << "Hello, world! This is " PACKAGE_NAME " version "
        PACKAGE_VERSION << std::endl;
    return 0;
}
