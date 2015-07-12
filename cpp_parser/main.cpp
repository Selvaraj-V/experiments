// This file contains code for parsing the cpp
// to find 
// 1) construtor 
//
//
//
//
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <boost/regex.hpp>

int main ( int argc , char *argv[])
{
  // open the file

  std::ifstream in("test.cpp");

  std::string s;
  boost::regex re;
  boost::cmatch matches;

  std::vector<std::string> lines ;

  while(getline (in,s)) {
      lines.push_back(s);
  }

  std::cout << lines.size() << std::endl;

  //std::regex cons_regex(".*::.*");
  //std::regex cons_regex(".*");
  std::regex cons_regex("(\\+|-)?[[:digit:]]+");

  std::vector<std::string>::iterator it = lines.begin();

  for (; it < lines.end() ; ++it ){
      if(std::regex_match(*it,cons_regex)) {
          //std::cout <<*it<<std::endl;
      }
  }
}






