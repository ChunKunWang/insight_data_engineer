#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "IdvCon.h"

using namespace std;
using namespace IdvConSpace;

struct DateEntry {
  string ID;
  string DT;
  double NUM;
  double AMT;
};

vector<DateEntry> DateTable;
map<string, double> DateIndex;

void pushDateTable(IdvCon* ptr);

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
      if (!obj.parseLine(line)) continue;
      if (obj.getID().empty() || obj.getAMT() < 1 || !obj.getOID().empty()) continue;

      if (obj.getZIP().size() == 5) {
        obj.pushZipTable();
        double median = obj.getZEamt()/obj.getZEnum();

        zipFile << obj.getZEid() << " "  
          << obj.getZEzip() << " " 
          << (int)(median + 0.5) << " "
          << obj.getZEnum() << " " 
          << obj.getZEamt() << endl;
      }
      if (!obj.getDT().empty())  pushDateTable(&obj);
    }

    for (int i = 0; i < DateTable.size(); i++) {
      double median = DateTable[i].AMT/DateTable[i].NUM;
      dateFile << DateTable[i].ID  << " "
        << DateTable[i].DT << " "
        << (int)(median + 0.5) << " "
        << DateTable[i].NUM << " "
        << DateTable[i].AMT << endl;
    }
    inFile.close();
    zipFile.close();
    dateFile.close();
  }
  else cout << "Open files fail!" << endl;

  cout << "find_political_donors: Hello World!" << endl;
  return 0;
}

void pushDateTable(IdvCon* ptr) {
  string index = ptr->getID() + ptr->getDT();
  if (!DateIndex[index]) {
    DateEntry tmp;
    DateIndex[index] = (double)DateIndex.size();
    tmp.ID  = ptr->getID();
    tmp.DT  = ptr->getDT();
    tmp.NUM = (double)1;
    tmp.AMT = ptr->getAMT();
    DateTable.push_back(tmp);
  }
  else {
    double i = DateIndex[index];
    DateTable[i - 1].NUM++;
    DateTable[i - 1].AMT += ptr->getAMT();
  }
//  double j = DateIndex[index]-1;
//  cout << DateTable[j].ID  << " "
//       << DateTable[j].DT  << " "
//       << DateTable[j].NUM << " "
//       << DateTable[j].AMT << " "
//       << DateTable.size() << endl;
}

