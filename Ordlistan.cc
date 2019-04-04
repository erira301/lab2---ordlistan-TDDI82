
#include "Ordlistan.h"

worder::worder(std::ifstream & is):word_count{}
{
  
  auto to_map = [this](std::string str)
    {
      auto hej = this->word_count.emplace(str,1); 
      if(!hej.second)
	{
	  ++(hej.first)->second;
	}
     
    };
  
  std::vector<std::string> stinger;
  stinger = readwords(is);

  std::for_each(stinger.begin(), stinger.end(), to_map);
}


void worder::out_data(std::ostream & os)
{
  auto print= [&os] (std::pair<std::string,unsigned int> item)
  {
    os<<item.first<<": "<<item.second<<std::endl;
    
  };

    std::for_each(word_count.begin(),word_count.end(),print);
  
}

std::vector<std::string> worder::readwords(std::ifstream & is)
{
  std::string line;
  std::vector<std::string> strings;
  while(is >> line)
    {
      clean(line);
      if(islegal(line))
	{
	  strings.push_back(line);
	  std::cout << line << std::endl;
	}
    }
  return strings;
}
  
void worder::clean(std::string & str)
{
  std::list<char>const forbidden_start{'\"', '\'', '('};
  std::list<char>const forbidden_end{'?', '!', ';', ':', ',',
      '.', '\"', '\'', ')'};
  while(forbidden_start.end() != std::find(forbidden_start.begin(), forbidden_start.end(), str.front()))
    {
      str.erase(str.begin());
    }
  
  while(forbidden_end.end() != std::find(forbidden_end.begin(), forbidden_end.end(), str.back()))
    {
      str.pop_back();
    }
  
  
  if(str[str.size() - 2] == '\'' && str.back() == 's')
    {
      str.erase(str.size() - 2);
    }
  
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

bool worder::islegal(std::string str)
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
}
 
