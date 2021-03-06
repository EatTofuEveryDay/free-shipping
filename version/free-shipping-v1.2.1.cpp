#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "chars.h"

double ship(std::string name1, std::string name2){
  // Define
  double t1a = 0;
  double t2a = 0;
  double t1b = 0;
  double t2b = 0;
  double c1;
  double c2;
  double c4;

  // Compute maps
  for(auto v : name1)
    t1a += mapA[v];
  for(auto v : name2)
    t2a += mapA[v];
  for(auto v : name1)
    t1b += mapB[v];
  for(auto v : name2)
    t2b += mapB[v];
  t1a /= name1.size();
  t2a /= name2.size();
  t1b /= name1.size();
  t2b /= name2.size();

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
  
  // Compute c3 and c4
  if((c1 + c2 == 0.0) || (c1 + c2 < 0.0)) 
    c4 = 0.0;
  else if(c1+c2 > 100.0)
    c4 = 100.0;
  else
    c4 = c1 + c2;
  return c4;
}

std::vector<std::string> names;
std::string mode;

void ginput(){
  std::cout << "Mode? (comp|find) ";
  getline(std::cin, mode);
  std::string line;
  std::cout << "Name? ";
  while(getline(std::cin, line)){
    if(line.empty()) break;
    names.push_back(line);
    std::cout << "Name? ";
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
    std::cout << "[\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0mMatchmaking\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0m]\n"
              << "\033[38;5;21mFemale: \033[0m" << names[0] << "\n"
              << "\033[38;5;21mMale: \033[0m" << names[1] << "\n"
              << "\033[38;5;21mMatch: \033[38;5;208m" << res << "%\033[0m\n"
              << "\033[38;5;21mMeter: \033[0m[\033[38;5;89m";
    for(int i = 0; i < 10; i++){
      if(i < ((res/10) + 1))
        std::cout << "\u2588";
      else std::cout << "\033[0m*";
    }
    std::cout << "\033[0m] ";
    if(res > 95) std::cout << "(SOUL MATE)";
    std::cout << "\n"
              << "[\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0mMatchmaking\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0m]\n";
  }else if(mode == "find"){
    std::vector<pair<std::string, double> > order; 
    for(int i = 1; i < names.size(); i++)
      order.push_back(pair<std::string, double>(names[i], ship(names[0], names[i])));
    std::sort(order.begin(), order.end());
    std::cout << "[\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0mMatchmaking\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0m]\n"
              << "\033[38;5;21mFinding match for \033[0m" << names[0] << "\033[38;5;21m:\033[0m\n";
    for(int i = order.size() - 1; i > -1; i--){
      std::cout << "\033[38;5;21m" << (order.size() - i) << ". \033[0m" << order[i].a << ": \033[38;5;208m" << order[i].b << "% ";
      if(order[i].b > 95) std::cout << "(SOUL MATE)";
      std::cout << "\n\033[0m";
    }
    std::cout << "[\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0mMatchmaking\033[38;5;196m\u2764\033[0m-+-\033[38;5;196m\u2764\033[0m]\n";
  }else{
    abort();
  }
}

int main() {
  std::cout << "\033[38;5;21mFree shipping v1.2.1\nWarning: this engine is highly optimistic.\nI take no responsibility for any emotional distress.\n\033[0m";
  for(;;){
    ginput();
    proc();
  }
}
