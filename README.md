# CP386 Assignment 4
CP386 Assignment4

## MOTIVATION
This project is a part of an assignment of Operating System course(CP 386).

## INSTALLATION
1. Clone this repo.

2. Transfer code to your VM.

3. Use Makefile command "make".

4. Run using "./Question1 X X X X"  --replace X X X X with the Max Resources you desire.

5. Request resources using "RQ X X X X"

6. Release using "RL X X X X"

## SCREENSHOTS

![Screenshot1](/images/Capture.JPG "Program Start")

![Screenshot2](/images/Capture1.JPG "use of RQ, RL and *")

![Screenshot3](/images/Capture2.JPG "Run command")

## CONTRIBUTION (Per Function)
```
int main(int argc, char *argv[]); //Kush
int readFile(char *fileName, Customer **tempCustomer); //Aryan
void allocateResources(int custID, int type_1, int type_2, int type_3, int type_4, int customerCount); //Kush
void releaseResources(int custID, int type_1, int type_2, int type_3, int type_4); //Aryan
int safetyAlgorithm(int numOfCustomers); //Aryan
void outputValues(int numOfCustomers); //Kush
void runBankerAlgo(int numOfCustomers); //Kush
void *runThread(void *thread); //Aryan
```

## FEATURES

1. Able to request and release resource accurately.
2. Able to show current available resources.

## TESTS

Above screenshot show a sample test case

## USE EXAMPLES

RQ: Request Resource
RL: Release Resource
* : Show current resources
RUN: Run safety Algorithm and find Safe sequence
exit: Stop the program

All commands are case sensitive 

## AUTHORS

Kush Rabadia, [@kushrabadia](https://github.com/KushRabadia)

Aryan Amin, [@aryanamin](https://github.com/AryanAmin)

## CREDITS
Kush Rabadia, [@kushrabadia](https://github.com/KushRabadia) Contributor

Aryan Amin, [@aryanamin](https://github.com/AryanAmin) Contributor

## MIT License

Copyright (c) 2021 KushRabadia and AryanAmin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
