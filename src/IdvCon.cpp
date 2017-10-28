#include "IdvCon.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <tr1/unordered_map>

using namespace std;
using namespace std::tr1;

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

  const void IdvCon::pushZipTable() const {
    string index = entry->ID + entry->ZIP;
    ZipEntry *ptr = new ZipEntry();
    ZipEntry  temp;
    ptr->ID  = entry->ID;
    ptr->ZIP = entry->ZIP;
    ptr->NUM = 1;
    ptr->AMT = entry->AMT;
    //pair<string, double> it(index, 0);
    pair<string, ZipEntry> it;
    it.first = index;
    it.second.ID = entry->ID;
    unordered_map<std::string, std::int> test;
    test.insert(index, int(0));
    cout << "Call pushZipTable, index: " << index << endl;
  }

  const void IdvCon::pushDateTable() const {
    cout << "Call pushDateTable!" << endl;
  }

  string IdvCon::getID() const  {return entry->ID;}
  string IdvCon::getZIP() const {return entry->ZIP;}
  string IdvCon::getDT() const  {return entry->DT;}
  double IdvCon::getAMT() const {return entry->AMT;}
  string IdvCon::getOID() const {return entry->OID;}

  IdvCon::~IdvCon() {}
}

