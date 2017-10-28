#ifndef IDVCON_INCLUDED
#define IDVCON_INCLUDED

#include <iostream>
#include <fstream>
#include <tr1/unordered_map>

using namespace std;
using namespace std::tr1;

namespace IdvConSpace {

  class IdvCon {

    struct Entry {
      string ID;     // CNTE_ID
      string ZIP;    // ZIP_CODE
      string DT;     // TRAN_DT
      double AMT;    // TRAN_AMT
      string OID;    // OTHER_ID
    };

    struct ZipEntry {
      string ID;
      string ZIP;
      double NUM;
      double AMT;
    };

    struct DateEntry {
      string ID;
      string DT;
      double NUM;
      double AMT;
    };

    public:
      IdvCon();
      bool parseLine(const string line);
      const void pushZipTable() const;
      const void pushDateTable() const;
      string getID() const;
      string getZIP() const;
      string getDT() const;
      double getAMT() const;
      string getOID() const;
      ~IdvCon();

    private:
      Entry *entry;
      unordered_map<string, ZipEntry> ZipTable;
      unordered_map<string, DateEntry> DateTable;
  };
}

#endif

