#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "IdvCon.h"

using namespace std;
using namespace IdvConSpace;

int main(int argc, char *argv[])
{
  string inName   = "./input/itcont.txt";
  string zipName  = "./output/medianvals_by_zip.txt";
  string dateName = "./output/medianvals_by_date.txt";

  // Parse the command line parameters
  if (argc == 1) {
    cout << "Set Default Path\n" << "input: "    << inName   << "\n"
                                 << "out_zip: "  << zipName  << "\n"
                                 << "out_date: " << dateName << endl;
  }
  else if (argc == 4) {
    inName   = argv[1];
    zipName  = argv[2];
    dateName = argv[3];
  }
  else {
    cout << "Command line error!" << endl;
    return 0;
  }

  // Declare the obj: IdcCon for the general process case and medianvals_by_zip
  //                  IdvConDate for the case of medianvals_by_date
  IdvCon obj;
  IdvConDate objDate;

  ifstream inFile   (inName.c_str());
  ofstream zipFile  (zipName.c_str());
  ofstream dateFile (dateName.c_str());
  string line;

  if (inFile.is_open() && zipFile.is_open() && dateFile.is_open()) {

    // Parse the input stream from file
    while (getline(inFile, line))
    {
      // Check the info well-formed
      if (!obj.parseLine(line)) continue;
      if (obj.getID().empty() || obj.getAMT() < 1 || !obj.getOID().empty()) continue;

      // Avoid the case when the length of ZIP is not the same as 5
      if (obj.getZIP().size() == 5) {
        obj.pushZipTable();
        double median = obj.getZEamt()/obj.getZEnum();

        // Write new coming update to zip file
        zipFile << obj.getZEid() << " "  
          << obj.getZEzip() << " " 
          << (int)(median + 0.5) << " "
          << obj.getZEnum() << " " 
          << obj.getZEamt() << endl;
      }

      // Record the case only if it contains DT
      if (!obj.getDT().empty()) objDate.pushDateTable(&obj);
    }
    // Write all records into date file
    objDate.writeToFile(dateFile);

    inFile.close();
    zipFile.close();
    dateFile.close();
  }
  else cout << "Open files fail!" << endl;

  cout << "find_political_donors: Done!" << endl;
  return 0;
}

