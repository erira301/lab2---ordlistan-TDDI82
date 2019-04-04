#include "Ordlistan.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
int main(int argc ,char* argv[])
{
  if(argc > 1)
    {
      ifstream is{argv[1]};
      worder word_list{is};
      cout<<endl;
      cout<<endl;
      word_list.out_data(cout);
    }

  return 0;
}
