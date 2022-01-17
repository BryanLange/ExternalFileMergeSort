#include <iostream>
#include <fstream>
using namespace std;

void readBoth(ifstream&, ifstream&, ofstream&, int*, int*, bool*, bool*);
void readFile1(ifstream&, ifstream&, ofstream&, int*, int*, bool*, bool*);
void readFile2(ifstream&, ifstream&, ofstream&, int*, int*, bool*, bool*);

int main(int argc, char** argv) {
    if(argc == 4) {

        // open input and output files
        ifstream inFile1, inFile2;
        inFile1.open(argv[1]);
        inFile2.open(argv[2]);
        ofstream outFile;
        outFile.open(argv[3]);

        int data1, data2;
        bool hold1 = false, hold2 = false;

        while(true) {

            // initial read of files, no hold on either data (both false)
            if(!hold1 && !hold2) {
                readBoth(inFile1, inFile2, outFile, &data1, &data2, &hold1, &hold2);
            }

            // hold on data1, last read still needs sorting
            else if(hold1 && !hold2) {
                readFile2(inFile1, inFile2, outFile, &data1, &data2, &hold1, &hold2);
            }

            // hold on data2, last read still needs sorting
            else if(!hold1 && hold2) {
                readFile1(inFile1, inFile2, outFile, &data1, &data2, &hold1, &hold2);
            }

            // both flags true, both files are EOF, break while loop
            else if(hold1 && hold2) {
                break;
            }
        }

        // close input and output files
        inFile1.close();
        inFile2.close();
        outFile.close();

    } else {
        cout << "Invalid number of arguments.\n";
    }
} // end main


// read from both files, output lesser data
// place a hold on the data that still needs sorting
void readBoth(ifstream& inFile1, ifstream& inFile2, ofstream& outFile,
              int* data1, int* data2, bool* hold1, bool* hold2) {
    inFile1 >> *data1;
    inFile2 >> *data2;
    if(data1 < data2) {
        outFile << *data1 << " ";
        *hold1 = false;
        *hold2 = true;
    } else {
        outFile << *data2 << " ";
        *hold1 = true;
        *hold2 = false;
    }
} // end readBoth()


// hold on data2 exists, read from inFile1 and output lesser data
// place a hold on the data that still needs sorting
// if inFile1 is EOF, output the rest of inFile2 and set both flags true
void readFile1(ifstream& inFile1, ifstream& inFile2, ofstream& outFile,
              int* data1, int* data2, bool* hold1, bool* hold2) {
    if(inFile1 >> *data1) {
        if(*data1 < *data2) {
            outFile << *data1 << " ";
            *hold1 = false;
            *hold2 = true;
        } else {
            outFile << *data2 << " ";
            *hold1 = true;
            *hold2 = false;
        }
    } else {
        outFile << *data2 << " ";
        while(inFile2 >> *data2) {
            outFile << *data2 << " ";
        }
        *hold1 = true;
        *hold2 = true;
    }
} // end readFile1()


// hold on data1 exists, read from inFile2 and output lesser data
// place a hold on the data that still needs sorting
// if inFile2 is EOF, output the rest of inFile1 and set both flags true
void readFile2(ifstream& inFile1, ifstream& inFile2, ofstream& outFile,
              int* data1, int* data2, bool* hold1, bool* hold2) {
    if(inFile2 >> *data2) {
        if(*data1 < *data2) {
            outFile << *data1 << " ";
            *hold1 = false;
            *hold2 = true;
        } else {
            outFile << *data2 << " ";
            *hold1 = true;
            *hold2 = false;
        }
    } else {
        outFile << *data1 << " ";
        while(inFile1 >> *data1) {
            outFile << *data1 << " ";
        }
        *hold1 = true;
        *hold2 = true;
    }
} // end readFile2()
