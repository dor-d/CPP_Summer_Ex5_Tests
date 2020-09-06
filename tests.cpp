//
// Created by Dor Dahuki on 04/09/2020.
//

#include <cassert>
#include <sstream>
#include "Matrix.h"

bool testCtor()
{
    int _cols = 10;
    int _rows = 10;

    Matrix foo(_rows, _cols);

    assert(foo.getRows() == _rows);
    assert(foo.getCols() == _cols);

    for (int i = 0; i < _cols * _rows; ++i)
    {
        assert(foo[i] == 0);
    }

    return true;
}

void testDefaultCtor()
{
    Matrix foo;

    assert(foo.getCols() == 1);
    assert(foo.getRows() == 1);
    assert(foo[0] == 0);
}

void testCopyCtor()
{
    int _cols = 2;
    int _rows = 2;

    Matrix foo(_rows, _cols);

    foo[0] = 0;
    foo[1] = 1;
    foo[2] = 2;
    foo[3] = 3;

    Matrix bar(foo);
    assert(foo.getCols() == bar.getCols());
    assert(foo.getRows() == bar.getRows());
    assert(foo[0] == bar[0]);
    assert(foo[1] == bar[1]);
    assert(foo[2] == bar[2]);
    assert(foo[3] == bar[3]);
}

void testGetCols()
{
    int numOfCols = rand() % 100 + 1;

    Matrix foo(1, numOfCols);

    assert(foo.getCols() == numOfCols);
}

void testGetRows()
{
    int numOfRows = rand() % 100 + 1;

    Matrix foo(numOfRows, 1);

    assert(foo.getRows() == numOfRows);
}

void testVectorize()
{
    int size = 10;
    Matrix foo(size, size);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            foo(i, j) = i * size + j;
        }
    }

    foo.vectorize();

    assert(foo.getRows() == size * size);
    assert(foo.getCols() == 1);

    for (int i = 0; i < size * size; ++i)
    {
        assert(foo[i] == i);
    }
}

void testPrint()
{
    std::stringstream buffer;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    int size = 10;
    Matrix foo(size, size);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            foo(i, j) = i * size + j;
        }
    }

    foo.print();

    std::string result = buffer.str();
    assert(result == "0 1 2 3 4 5 6 7 8 9\n10 11 12 13 14 15 16 17 18 19\n20 21 22 23 24 25"
                           " 26 27 28 29\n30 31 32 33 34 35 36 37 38 39\n40 41 42 43 44 45 46 47 48 49\n50 51 52 53 54 55 56 57 58 59\n60 61 62 63 64 65 66 67 68 69\n70 71 72 73 74 75 76 77 78 79\n80 81 82 83 84 85 86 87 88 89\n90 91 92 93 94 95 96 97 98 99");

    std::cout.rdbuf(sbuf);
}

void testCopyAssign()
{
    int _cols = 2;
    int _rows = 2;

    Matrix foo(_rows, _cols);

    foo[0] = 0;
    foo[1] = 1;
    foo[2] = 2;
    foo[3] = 3;

    Matrix bar;
    bar = foo;
    assert(foo.getCols() == bar.getCols());
    assert(foo.getRows() == bar.getRows());
    assert(foo[0] == bar[0]);
    assert(foo[1] == bar[1]);
    assert(foo[2] == bar[2]);
    assert(foo[3] == bar[3]);
}

void testMultiplyWithAnotherMatrix()
{
    Matrix m(3, 3);
    std::stringstream ss;
    ss << "1 2 3 4 5 6 7 8 9";
    ss >> m;

    Matrix n(3, 3);
    std::stringstream hh;
    hh << "1 2 3 4 5 6 7 8 9";
    hh >> n;

    Matrix c = m * n;
    assert(c[0] == 30);
    assert(c[1] == 36);
    assert(c[2] == 42);
    assert(c[3] == 66);
    assert(c[4] == 81);
    assert(c[5] == 96);
    assert(c[6] == 102);
    assert(c[7] == 126);
    assert(c[8] == 150);
}

void testMultiplyWithScalar()
{
    int size = 10;
    Matrix foo(size, size);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            foo(i, j) = i * size + j;
        }
    }

    Matrix bar = foo * 2;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            assert(bar(i, j) == 2 * (i * size + j));
        }
    }
}

void testMultiplyWithLeftScalar()
{
    int size = 10;
    Matrix foo(size, size);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            foo(i, j) = i * size + j;
        }
    }

    Matrix bar = 2 * foo;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            assert(bar(i, j) == 2 * (i * size + j));
        }
    }
}

void testDivision()
{
    int size = 10;
    Matrix foo(size, size);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            foo(i, j) = i * size + j;
        }
    }

    Matrix bar = foo / 2;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            assert(bar(i, j) == (float)(i * size + j) / 2);
        }
    }
}

void testAddition()
{
    int size = 5;
    Matrix foo(size, size);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            foo(i, j) = i * size + j;
        }
    }

    Matrix bar(foo);

    Matrix sum = foo + bar;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            assert(sum(i, j) == 2 * (i * size + j));
        }
    }
}

void testMultiplyAssignWithMatrix()
{
    Matrix m(3, 3);
    std::stringstream ss;
    ss << "1 2 3 4 5 6 7 8 9";
    ss >> m;

    Matrix n(3, 3);
    std::stringstream hh;
    hh << "1 2 3 4 5 6 7 8 9";
    hh >> n;

    m *= n;
    assert(m[0] == 30);
    assert(m[1] == 36);
    assert(m[2] == 42);
    assert(m[3] == 66);
    assert(m[4] == 81);
    assert(m[5] == 96);
    assert(m[6] == 102);
    assert(m[7] == 126);
    assert(m[8] == 150);
}

void testMultiplyAssignWithScalar()
{
    int size = 10;
    Matrix foo(size, size);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            foo(i, j) = i * size + j;
        }
    }

    foo *= 2;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            assert(foo(i, j) == 2 * (i * size + j));
        }
    }
}

void testDivisionAssign()
{
    int size = 10;
    Matrix foo(size, size);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            foo(i, j) = i * size + j;
        }
    }

    foo /= 2;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            assert(foo(i, j) == (float)(i * size + j) / 2);
        }
    }
}

void testAdditionAssign()
{
    int size = 5;
    Matrix foo(size, size);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            foo(i, j) = i * size + j;
        }
    }

    Matrix bar(foo);

    foo += bar;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            assert(foo(i, j) == 2 * (i * size + j));
        }
    }
}

void testSubscript()
{
    int size = 3;
    Matrix n(size, size);
    std::stringstream hh;
    hh << "0 1 2 3 4 5 6 7 8";
    hh >> n;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            assert(n(i, j) == i * size + j);
        }
    }
}

void testSubscriptConst()
{
    int size = 3;
    Matrix n(size, size);
    std::stringstream hh;
    hh << "1 2 3 4 5 6 7 8 9";
    hh >> n;

    const Matrix m(n);

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            assert(m(i, j) == i * size + j);
        }
    }
}

void testSubscriptAssign()
{
    int size = 3;
    Matrix n(size, size);
    std::stringstream hh;
    hh << "1 2 3 4 5 6 7 8 9";
    hh >> n;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            n(i, j) = 100;
        }
    }

    for (int i = 0; i < 9; ++i)
    {
        assert(n[i] == 100);
    }
}

void testEquality()
{
    int size = 3;
    Matrix n(size, size);
    std::stringstream hh;
    hh << "1 2 3 4 5 6 7 8 9";
    hh >> n;

    Matrix m = n;
    assert(m == n);

    Matrix c(size, size);
    hh.clear();
    hh << "1 2 3 4 5 6 7 8 9";
    hh >> c;
    assert(c == n);

    c[3] = 99;
    assert(!(c == n));
}

void testInequality()
{
    int size = 3;
    Matrix n(size, size);
    std::stringstream hh;
    hh << "1 2 3 4 5 6 7 8 9";
    hh >> n;

    Matrix m = n;
    assert(!(m != n));

    Matrix c(size, size);
    hh.clear();
    hh << "1 2 3 4 5 6 7 8 9";
    hh >> c;
    assert(!(c != n));

    c[3] = 99;
    assert(c != n);
}

void testInputStream()
{
    int size = 3;
    Matrix n(size, size);
    std::stringstream hh;
    hh << "0 1 2 3 4 5 6 7 8";
    hh >> n;

    for (int i = 0; i < 9; ++i)
    {
        assert(n[i] == i);
    }
}

void testOutputStream()
{
    int size = 3;
    Matrix n(size, size);

    for (int i = 0; i < 9; ++i)
    {
        n[i] = i;
    }

    std::stringstream hh;
    hh << n;
    assert(hh.str() == "0 1 2\n3 4 5\n6 7 8");
}

int main() {
    testCtor();
    testDefaultCtor();
    testCopyCtor();
    testGetCols();
    testGetRows();
    testVectorize();
    testPrint();
    testCopyAssign();
    testMultiplyWithAnotherMatrix();
    testMultiplyWithScalar();
    testMultiplyWithLeftScalar();
    testDivision();
    testAddition();
    testMultiplyAssignWithMatrix();
    testMultiplyAssignWithScalar();
    testDivisionAssign();
    testAdditionAssign();
    testSubscript();
    testSubscriptAssign();
    testEquality();
    testInequality();
    testInputStream();
    testOutputStream();
    return 0;
};



