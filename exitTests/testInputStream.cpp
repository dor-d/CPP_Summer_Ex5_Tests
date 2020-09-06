//
// Created by Dor Dahuki on 04/09/2020.
//

#include <sstream>
#include "../Matrix.h"

int main() {
    Matrix foo(3, 3);

    std::stringstream hh;
    hh >> foo;
    return 0;
};
