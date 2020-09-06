//
// Created by Dor Dahuki on 04/09/2020.
//

#include <sstream>
#include "../Matrix.h"

int main() {
    Matrix foo(3, 3);

    stringstream hh;
    hh << "0 1 2 3 4 5 6 7 8";
    hh >> foo;

    Matrix bar(7, 7);
    foo *= bar;

    return 0;
};
