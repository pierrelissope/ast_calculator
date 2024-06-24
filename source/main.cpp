#include <iostream>
#include <string>
#include "calculator.hpp"

int main(int ac, char **)
{
    if (ac != 1) {
        std::cout << "[USAGE] ./calculator\n";
        return EXIT_SUCCESS;
    }
    run();
    return EXIT_SUCCESS;
}
