import os
import subprocess
from pathlib import Path

from progress import ProgressBar

if not os.path.exists('temp'):
    os.makedirs('temp')
if not os.path.exists('resultsToCompare'):
    os.makedirs('resultsToCompare')

from PIL import Image
from image2file import __lists_to_lines
import filecmp
import numpy

myProgressBar = ProgressBar(nElements = 50, nIterations = 30)
progress_index = 0

ERROR_MSGS = {
    "testHighIndex": b"Index out of range.\n",
    "testInvalidAddition": b"Invalid matrix dimensions.\n",
    "testInvalidAdditionAssign": b"Invalid matrix dimensions.\n",
    "testInvalidDimMultiply": b"Invalid matrix dimensions.\n",
    "testInvalidIndex": b"Index out of range.\n",
    "testNegativeCols": b"",
    "testNegativeCoor1": b"Index out of range.\n",
    "testNegativeCoor2": b"Index out of range.\n",
    "testNegativeRows": b"",
    "testZeroDivisionAssign": b"Division by zero.\n",
    "testHighCoor": b"Index out of range.\n",
    "testHighCoor2": b"Index out of range.\n",
    "testInvalidDimMultiplyAssign": b"Invalid matrix dimensions.\n",
    "testZeroDivision": b"Division by zero.\n",
    "testInputStream": b"Error loading from input stream.\n",
    "testZeroDim": b""
}

LENA_CASES = ['lena_blur.out', 'lena_quant_16_levels.out', 'lena_quant_2_levels.out',
              'lena_quant_4_levels.out', 'lena_sobel.out']

def save(img, name):
    as_arr = numpy.asarray(img)
    fp = open(name, 'w')
    fp.writelines(__lists_to_lines(as_arr))
    fp.close()


def blackBoxTest():
    global progress_index
    print("Finally, let's try some blackbox tests.\n")
    images = Path("./images")

    for imageFile in images.iterdir():
        myProgressBar.progress(progress_index)
        progress_index += 1
        if imageFile.suffix != ".jpg" and imageFile.suffix != ".png":
            continue
        img_matrix = Image.open(str(imageFile.absolute())).convert('L').resize((128, 128))
        name = f"{imageFile.stem}-before_process.out"
        save(img_matrix, name)
        subprocess.run("g++ main.cpp Matrix.cpp -o ex4program".split())
        for option in ["quant", "blur", "sobel"]:
            command = ["./ex4program", name, option,
                       f"./resultsToCompare/{imageFile.stem}_{option}.out"]
            subprocess.run(command)

def compareToSchool():
    subprocess.run("g++ createLenaOutput.cpp Matrix.cpp -o createLena".split())
    subprocess.run("./createLena")

    for case in LENA_CASES:
        if filecmp.cmp(f"./schoolOutput/{case}", f"./resultsToCompare/{case}", shallow=False) is False:
            print(f"Your output file of {case} is not the same as the school solution")

def valgrindTest():
    print("Unittest is done, let's try valgrind...\n")
    output = subprocess.check_output("valgrind --track-origins=yes ./temp/unitTest".split(),
                                     stderr=subprocess.STDOUT)
    if b"ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)" not in output:
        print("Valgrind detected error, please run 'valgrind --track-origins=yes "
              "./temp/unitTest'\n")
    else:
        print("It seems like Valgrind did not detect any errors.\n")

def main():
    global progress_index
    p = Path("./exitTests")

    for file in p.iterdir():
        myProgressBar.progress(progress_index)
        progress_index += 1

        subprocess.run(f"g++ ./exitTests/{file.name} Matrix.cpp -o ./temp/{file.stem}".split())
        try:
            subprocess.check_output(f"./temp/{file.stem}", stderr=subprocess.PIPE, shell=True)
        except subprocess.CalledProcessError as e:
            if (e.returncode != 1):
                print(f"Case: {file.stem} - You should exit with 1 return value")
            if (e.stderr != ERROR_MSGS[file.stem]):
                print(f"Case: {file.stem} - I think you should print {ERROR_MSGS[file.stem]},"
                      f"instead of {e.stderr}")
        else:
            print(f"Case: {file.stem} - You should exit with 1 return value")

    subprocess.run("g++ ./tests.cpp ./Matrix.cpp -o ./temp/unitTest".split())

    subprocess.run("./temp/unitTest")
    valgrindTest()
    # blackBoxTest()
    compareToSchool()

if __name__ == "__main__":
    main()
