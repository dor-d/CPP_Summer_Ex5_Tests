//
// Created by Dor Dahuki on 07/09/2020.
//

#include <fstream>
#include "Matrix.h"
#include "Filters.cpp"

/**
 * Reads the file (given by file path) to
 * the matrix which is referenced.
 * @param filePath path to some file which includes
 * matrix values (in range [0, 255]).
 * @param mat reference to matrix.
 * @return true if the operation succeeded, false otherwise.
 */
bool readFileToMatrix(const std::string &filePath, Matrix &mat)
{
    std::fstream file;
    file.open(filePath.c_str());
    if (!file.is_open())
    {
        return false;
    }
    file >> mat;
    file.close();
    return true;
}


/**
 * Writes the references matrix to the given file path.
 * @param filePath path to some file where the matrix
 * is going to be written to.
 * @param mat the matrix which to be written to the file.
 * @return true if the operation succeeded, false otherwise.
 */
bool writeMatrixToFile(const std::string &filePath, const Matrix &mat)
{
    std::ofstream file(filePath);
    if (!file.is_open())
    {
        return false;
    }
    file << mat;
    file.close();
    return true;
}


/**
 * Program's main
 * @param argc count of args
 * @param argv args values
 * @return program exit status code
 */
int main(int argc, char **argv)
{
    Matrix lena(128, 128);
    readFileToMatrix("./images/lena.out", lena);

    Matrix result;
    result = quantization(lena, 2);
    writeMatrixToFile("./resultsToCompare/lena_quant_2_levels.out", result);

    result = quantization(lena, 4);
    writeMatrixToFile("./resultsToCompare/lena_quant_4_levels.out", result);

    result = quantization(lena, 16);
    writeMatrixToFile("./resultsToCompare/lena_quant_16_levels.out", result);

    return 0;
}
