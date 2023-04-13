#include <iostream>
#include "InputData.h"
#include "NumericalDifferentiation.h"


int main() {
    std::setlocale(LC_ALL, "Russian");
    KHAS::NumericalDifferentiation nd{ KHAS::InputData{ 67 } };
    nd.loop();

    return 0;
}