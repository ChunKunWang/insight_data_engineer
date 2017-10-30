#include "IdvCon.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <tgmath.h>

using namespace std;

namespace IdvConSpace {
  IdvCon::IdvCon() {}

  bool IdvCon::parseLine(const string line) {
    if (entry) free(entry);

    istringstream iss(line);
    string token;
    entry = new Entry();
    int index = 1;

    while (getline(iss, token, '|')) {
      //cout << "[" << index << "]: " << token << endl;
      if (index == 1)       entry->ID  = token;
      else if (index == 11) entry->ZIP = token;
      else if (index == 14) entry->DT  = token;
      else if (index == 15) entry->AMT = token.empty() ? -1 : atof(token.c_str());
      else if (index == 16) entry->OID = token;
      else ;

      index++;
    }

    if (entry->ZIP.size() > 5) entry->ZIP.resize(5);

    return true;
  }

  const void IdvCon::pushZipTable() {
    string index = entry->ID + entry->ZIP;
    _ZipKey.assign(index); 
    if (!ZipIndex[index]) {
      ZipEntry tmp;
      ZipIndex[index] = (double)ZipIndex.size();
      tmp.ID = entry->ID;
      tmp.ZIP = entry->ZIP;
      tmp.NUM = (double)1;
      tmp.AMT = entry->AMT;
      ZipTable.push_back(tmp);
    }
    else {
      double i = ZipIndex[index];
      ZipTable[i - 1].NUM++;
      ZipTable[i - 1].AMT += entry->AMT;
    }
  }

  string IdvCon::getZEid()  {return ZipTable[ZipIndex[_ZipKey] - 1].ID;}
  string IdvCon::getZEzip() {return ZipTable[ZipIndex[_ZipKey] - 1].ZIP;}
  double IdvCon::getZEnum() {return ZipTable[ZipIndex[_ZipKey] - 1].NUM;}
  double IdvCon::getZEamt() {return ZipTable[ZipIndex[_ZipKey] - 1].AMT;}

  string IdvCon::getID() const  {return entry->ID;}
  string IdvCon::getZIP() const {return entry->ZIP;}
  string IdvCon::getDT() const  {return entry->DT;}
  double IdvCon::getAMT() const {return entry->AMT;}
  string IdvCon::getOID() const {return entry->OID;}

  IdvCon::~IdvCon() {}

  IdvConDate::IdvConDate() {}

  void IdvConDate::pushDateTable(IdvCon* ptr) {
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
//    double j = DateIndex[index]-1;
//    cout << DateTable[j].ID  << " "
//      << DateTable[j].DT  << " "
//      << DateTable[j].NUM << " "
//      << DateTable[j].AMT << " "
//      << DateTable.size() << endl;
  }

  void IdvConDate::writeToFile(ofstream& dateFile) {
    for (int i = 0; i < DateTable.size(); i++) {
      double median = DateTable[i].AMT/DateTable[i].NUM;
      dateFile << DateTable[i].ID  << "|"
        << DateTable[i].DT << "|"
        << (int)(median + 0.5) << "|"
        << DateTable[i].NUM << "|"
        << DateTable[i].AMT << endl;
    }
  }

  IdvConDate::~IdvConDate() {}
}

