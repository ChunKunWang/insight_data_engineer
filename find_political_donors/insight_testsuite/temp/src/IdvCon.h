#ifndef IDVCON_INCLUDED
#define IDVCON_INCLUDED

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

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

    public:
    IdvCon();
    ~IdvCon();
    bool parseLine(const string line);
    const void pushZipTable();

    string getZEid();
    string getZEzip();
    double getZEnum();
    double getZEamt();

    string getID()  const;
    string getZIP() const;
    string getDT()  const;
    double getAMT() const;
    string getOID() const;

    vector<ZipEntry>  ZipTable;
    string _ZipKey;
    private:
    Entry *entry;
    map<string, double> ZipIndex;
  };

  class IdvConDate{
    struct DateEntry {
      string ID;
      string DT;
      double NUM;
      double AMT;
    };
    public:
      IdvConDate();
      ~IdvConDate();
      void pushDateTable(IdvCon* ptr);
      void writeToFile(ofstream& dateFile);
      vector<DateEntry> DateTable;
    private:
      DateEntry *entry;
      map<string, double> DateIndex;
  };
}

#endif

