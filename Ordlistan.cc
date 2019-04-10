#include "Ordlistan.h"

void worder::out_data(std::ostream & os,char print_type,int cnt =0)
{
  int n{};
  auto print= [&os] (std::pair<std::string,unsigned int> item)
    {
      os<<item.first<<": "<<item.second<<std::endl;    
    };
  auto compare = [](std::pair<std::string,unsigned int> const& lhs, std::pair<std::string,unsigned int> const& rhs)
    {
      return lhs.second > rhs.second;
    };
  auto printlad = [&n,cnt,&os](std::string str)
    {
      n+=str.size();
      if(n > cnt){
	n=str.size()+1;
	os<<'\n';
      }
      os<<str<<' ';
    };
  
  std::map<std::string,unsigned int> map_words;

  std::for_each(words.begin(),words.end(),[&map_words](std::string s){map_words[s]++;});
  std::vector<std::pair<std::string, unsigned int>> setofwords {map_words.begin(),map_words.end()};
  switch (print_type)
    {
    case 'a':
      std::for_each(setofwords.begin(), setofwords.end(), print);
      break;
    case 'f':
      std::sort(setofwords.begin(),setofwords.end(),compare);
      std::for_each(setofwords.begin(),setofwords.end(),print);
      break;
    case 'o':
      std::for_each(words.begin(), words.end(), printlad);
      break;
    default:
      throw std::logic_error{"Wrong second argument"};
      break;
    }
}

std::vector<std::string> worder::readwords(std::ifstream & is)
{
  auto cleanse = [](std::string str)
    {
      std::transform(str.begin(), str.end(), str.begin(), ::tolower);
      str.erase(0,str.find_first_not_of("\"\'()") );
      if(!str.empty())
	{
	  str.erase(str.find_last_not_of(" ?!;:,.\"\')")+1);
	}
      if(str[str.size() - 2] == '\'' && str.back() == 's')
	{
	  str.erase(str.size() - 2);
	}
      return str;
    };

  auto legalize = [](std::string str)
    {
      bool validator{str.length() > 2 && str.back() != '-' && str.front() != '-' &&str.find("--") == std::string::npos};
  
      auto lol = [&validator](char c)
      {
	if(!isalpha(c) && c != '-')
	  {
	    validator = false;
	  }
      };  
      std::for_each(str.begin(), str.end(), lol);
      return validator;
    }; 
  std::vector<std::string> strings;
  std::vector<std::string> strings2;
  copy(std::istream_iterator<std::string>(is),std::istream_iterator<std::string>(),inserter(strings,strings.begin()));
  transform(strings.begin(),strings.end(),strings.begin(),cleanse);
  copy_if(strings.begin(),strings.end(),inserter(strings2,strings2.begin()),legalize);
  return strings2;
}
