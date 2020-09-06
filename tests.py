from pathlib import Path
from progress import ProgressBar
import subprocess
import os
if not os.path.exists('temp'):
    os.makedirs('temp')

p = Path("./exitTests")

ERROR_MSGS = {
    "testHighIndex": b"Index out of range.\n",
    "testInvalidAddition": b"Invalid matrix dimensions.\n",
    "testInvalidAdditionAssign": b"Invalid matrix dimensions.\n",
    "testInvalidDimMultiply": b"Invalid matrix dimensions.\n",
    "testInvalidIndex": b"Index out of range.\n",
    "testNegativeCols": b"Invalid matrix dimensions.\n",
    "testNegativeCoor1": b"Index out of range.\n",
    "testNegativeCoor2": b"Index out of range.\n",
    "testNegativeRows": b"Invalid matrix dimensions.\n",
    "testZeroDivisionAssign": b"Division by zero.\n",
    "testHighCoor": b"Index out of range.\n",
    "testHighCoor2": b"Index out of range.\n",
    "testInvalidDimMultiplyAssign": b"Invalid matrix dimensions.\n",
    "testZeroDivision": b"Division by zero.\n",
    "testInputStream": b"Error loading from input stream.\n",
    "testZeroDim": ""
}

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