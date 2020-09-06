import os
import subprocess
from pathlib import Path

from progress import ProgressBar

if not os.path.exists('temp'):
    os.makedirs('temp')
if not os.path.exists('resultsToCompare'):
    os.makedirs('resultsToCompare')

from PIL import Image
from image2file import __save_to_file


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
    "testZeroDim": ""
}

def blackBoxTest():
    images = Path("./images")
    myProgressBar = ProgressBar(nElements = 20, nIterations = 11)
    index = 0
    for imageFile in images.iterdir():
        myProgressBar.progress(index)
        index += 1
        if imageFile.suffix != ".jpg" and imageFile.suffix != ".png":
            continue
        img_matrix = Image.open(str(imageFile.absolute())).convert('L').resize((128, 128))
        __save_to_file(img_matrix)
        subprocess.run("g++ main.cpp Matrix.cpp -o ex4program".split())
        for option in ["quant", "blur", "sobel"]:
            command = ["./ex4program", "image.out", option,
                       f"./resultsToCompare/{imageFile.name}_{option}.out"]
            subprocess.run(command)
        os.remove("image.out")


def main():
    p = Path("./exitTests")

    myProgressBar = ProgressBar(nElements = 20, nIterations = 14)
    index = 0
    for file in p.iterdir():
        myProgressBar.progress(index)
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

        index += 1

    subprocess.run("g++ ./tests.cpp ./Matrix.cpp -o ./temp/unitTest".split())

    subprocess.run("./temp/unitTest")
    print("Unittest is done, let's try valgrind...")
    output = subprocess.check_output("valgrind --track-origins=yes ./temp/unitTest".split(),
                                     stderr=subprocess.STDOUT)
    if b"ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)" not in output:
        print("Valgrind detected error, please run 'valgrind --track-origins=yes ./temp/unitTest'")
    else:
        print("It seems like Valgrind did not detected any errors.")

    print("Finally, let's try some blackbox tests.")
    blackBoxTest()

if __name__ == "__main__":
    main()