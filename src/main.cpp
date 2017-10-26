#include <iostream>
#include <fstream>
#include <string>
#include "IdvCon.h"

using namespace std;
using namespace IdvConSpace;

void usage() {
  cout << "Instruction: ..." << endl;
}

int main(int argc, char *argv[])
{
  string inName   = "../input/itcont.txt";
  string zipName  = "../output/medianvals_by_zip.txt";
  string dateName = "../output/medianvals_by_date.txt";

  if (argc == 4) {
    inName   = argv[1];
    zipName  = argv[2];
    dateName = argv[3];
  }
  IdvCon obj;

  ifstream inFile   (inName.c_str());
  ofstream zipFile  (zipName.c_str());
  ofstream dateFile (dateName.c_str());
  string line;

  if (inFile.is_open() && zipFile.is_open() && dateFile.is_open()) {
    while (getline(inFile, line))
    {
      cout << line << '\n';
      zipFile << line << '\n';
      dateFile << line << '\n';
    }
    inFile.close();
    zipFile.close();
    dateFile.close();
  }
  else cout << "Fail" << endl;

  cout << "find_political_donors: Hello World!" << endl;
  return 0;
}


