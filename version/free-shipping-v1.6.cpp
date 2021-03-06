#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "chars.h"

std::ostringstream out;

double ship(std::string name1, std::string name2){
  // Define
  double t1a = 0;
  double t2a = 0;
  double t1b = 0;
  double t2b = 0;
  double t1c = 0;
  double t2c = 0;
  double c1;
  double c2;
  double c3;

  // Compute maps
  for(auto v : name1){
    t1a += mapA[v];
    t1b += mapB[v];
    t1c += mapC[v];
  }
    
  for(auto v : name2){
    t2a += mapA[v];
    t2b += mapB[v];
    t2c += mapC[v];
  }
  
  t1a /= name1.size();
  t2a /= name2.size();
  t1b /= name1.size();
  t2b /= name2.size();
  t1c /= name1.size();
  t2c /= name2.size();

  // Calculate c1
  c1 = ((1 - sqrt(fabs(t1a - t2a) / 10))) * 100;

  // Normalize c2
  if(t1b == 0.0 || t2b == 0.0) {
    c2 = 0;
  } else if((t1b > 0 && t2b > 0) || (t1b < 0 && t2b < 0)) {
    if(fabs(t1b - t2b) == 0)
      c2 = -100;
    else
      c2 = (0 - sqrt(1 / fabs(t1b - t2b))) * 3;
  } else 
    c2 = sqrt(fabs(t1b - t2b)) * 3;
  
  c3 = (c1 + c2) * (sqrt(fabs(t1c - t2c)) / 10) * 10;

  // Range-check
  if(c3 < 0.0) 
    return 0.0;
  else if(c3 > 100.0)
    return 100.0;
  else
    return c3;
}

std::string tostring(std::string s){
  return s;
}

std::string tostring(double d){
  return std::to_string(d);
}

template<class T>
std::string to_string7(T d){
  std::string ret = tostring(d);
  if(ret.size() > 7)
    ret = ret.substr(0,7);
  else if(ret.size() < 7)
    ret.append(7 - ret.size(), ' ');
  return ret;
}

std::vector<std::string> names;
std::vector<std::string> namest;
std::string mode;

void ginput(){
  names = std::vector<std::string>();
  namest = std::vector<std::string>();
  std::cout << "Mode? (comp|find|table|avg) ";
  getline(std::cin, mode);
  std::string line;
  std::cout << "Name? ";
  while(getline(std::cin, line)){
    if(line.empty()) break;
    names.push_back(line);
    std::cout << "Name? ";
  }
  if(mode == "table"){
    std::cout << "Name? ";
    while(getline(std::cin, line)){
      if(line.empty()) break;
      namest.push_back(line);
      std::cout << "Name? ";
    }
  }
}

template<class T1, class T2>
struct pair {
  pair() : a{}, b{} {}
  pair(T1 na, T2 nb) : a{na}, b{nb} {}
  T1 a;
  T2 b;
  bool operator<(pair<T1, T2> p){
    return b < p.b;
  }
};

void proc(){
  if(mode == "comp"){
    double res = ship(names[0], names[1]);
    std::string buf;
    out << "\n\n\n\n\n\n\n\n";
    out << "[\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0mMatchmaking\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0m]\n\r"
        << "\033[38;5;21mFemale: \033[0m" << names[0] << "\n\r"
        << "\033[38;5;21mMale: \033[0m" << names[1] << "\n\r"
        << "\033[38;5;21mMatch: \033[38;5;208m" << res << "%\033[0m\n\r"
        << "\033[38;5;21mMeter: \033[0m[\033[38;5;89m";
    for(int i = 0; i < 10; i++){
      if(i < ((res/10) + 1))
        out << "\u2588";
      else out << "\033[0m*";
    }
    out << "\033[0m] ";
    if(res > 95) out << "\033[36m(SOUL MATE)\033[0m";
    out << "\n\r"
        << "[\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0mMatchmaking\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0m]\n\r";
  }else if(mode == "find"){
    std::vector<pair<std::string, double> > order; 
    for(int i = 1; i < names.size(); i++)
      order.push_back(pair<std::string, double>(names[i], ship(names[0], names[i])));
    std::sort(order.begin(), order.end());
    out << "[\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0mMatchmaking\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0m]\n\r"
        << "\033[38;5;21mFinding match for \033[0m" << names[0] << "\033[38;5;21m:\033[0m\n\r";
    for(int i = order.size() - 1; i > -1; i--){
      out << "\033[38;5;21m" << (order.size() - i) << ". \033[0m" << order[i].a << ": \033[38;5;208m" << order[i].b << "% ";
      if(order[i].b > 95) out << "(SOUL MATE)";
      out << "\n\r\033[0m";
    }
    out << "[\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0mMatchmaking\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0m]\n\r";
  }else if(mode == "table"){
    out << "+-------+";
    for(auto v : namest){
      out << "-------+";
    }
    out << "\n\r| Names ";
    for(auto v : namest){
      out << "|" << to_string7(v);
    }
    out << "|\n\r+-------+";
    for(auto v : namest){
      out << "-------+";
    }
    out << "\n\r";
    for(auto v : names){
      out << "|" << to_string7(v) << "|";
      for(auto s : namest){
        out << to_string7(ship(v, s)) << " ";
      }
      out << "\n\r";
    }
    out << "+-------+\n\r";
  }else if(mode == "avg"){
    double total;
    for(int i = 1; i < names.size(); i++)
      total += ship(names[0], names[i]);
    total /= names.size() - 1;
    out << "[\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0mMatchmaking\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0m]\n\r"
        << "\033[38;5;196mAverage for \033[0m" << names[0] << ":\n\r"
        << "\033[38;5;196mAvg: " << total << "%\n\r"
        << "\033[0m[\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0mMatchmaking\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0m]\n\r";
  }else{
    abort();
  }
}

int main() {
  std::cout << "Free shipping v1.6\n";
  for(;;){
    out.str("");
    ginput();
    proc();
    std::cout << "Finished\n\r";
    std::string s = out.str();
    std::cout << s;
    std::fstream fout("out.txt", std::ios::out);
    bool inescape = false;
    for(char c : s){
      /*if(c == '\033')
        inescape = true;
      else if(c == 'm'){
        inescape = false;
      }else if(!inescape)*/ fout << c;
    }
    fout.close();
  }
}
