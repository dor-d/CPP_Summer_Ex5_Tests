//
// Created by Dor Dahuki on 04/09/2020.
//

#include <sstream>
#include "../Matrix.h"

int main() {
    Matrix foo(3, 3);

    std::stringstream hh;
    hh << "0 1 2 3 4 5 6 7 8";
    hh >> foo;

    foo[50] = 5;
    
    return 0;
};
