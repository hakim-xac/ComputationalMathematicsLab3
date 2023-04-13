#include <iostream>
#include "InputData.h"
#include "NumericalDifferentiation.h"


int main() {
    std::setlocale(LC_ALL, "Russian");
    KHAS::NumericalDifferentiation nd{ KHAS::InputData{ 1.958, 2.672, 0.042, 0.036 }, 69 };
    nd.loop();

    return 0;
}