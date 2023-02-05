from subprocess import PIPE, Popen
import time

for n in range(1, 34):
    startTime = time.time()
    inputFile = f'./lab03/trains/input{n}.txt'
    outputFile = f'./lab03/trains/output{n}.txt'
    f = open(outputFile)
    output = f.read()
    command = "trains.exe < " + inputFile
    process = Popen(command, shell=True, stdout=PIPE, stderr=PIPE)
    producedOutput, err = process.communicate()

    if (output.split() == producedOutput.decode("utf-8").split()):
        print(f'+++ Testcase {n} passed!')
    else:
        print(f'--- Testcase {n} failed!')
        print(f'Expected Output: {output}')
        print(f'Produced Output: {producedOutput.decode("utf-8")}')
    executionTime = (time.time() - startTime)
    print('Execution time in seconds: ' + str(executionTime))
