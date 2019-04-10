#include "Ordlistan.h"
#include <iostream>
#include <vector>
#include <fstream>
#include<sstream>
using namespace std;

int main(int argc, char *argv[]) {
  if(argc>2)
    {
      ifstream is(argv[1],ifstream::in);
      worder word_list{is};
      unsigned int t{};
      string s = argv[2];
      if(argc > 3)
	{
	   t = stoi(argv[3]);
	}
      word_list.out_data(cout,s[1],t);
      is.close();
      cout<<'\n';
    }
  return 0;
}
