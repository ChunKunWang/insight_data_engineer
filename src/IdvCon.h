#ifndef IDVCON_INCLUDED
#define IDVCON_INCLUDED

// Standard C++ header
#include <iostream>

using namespace std;

namespace IdvConSpace {
  class IdvCon {
    public:
      void setInName(string input_string);
      void setOutZip(string input_string);
      void setOutDate(string input_string);
    private:
      string input_name;
      string output_zip_name;
      string output_date_name;
  };
}

#endif

