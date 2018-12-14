#include<termios.h>
namespace getch {

  // Edited and optimized to fit C++,
  // https://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux

  struct termios old, unb;
  int setup(){
    std::cin.sync_with_stdio(true);
    tcgetattr(0, &old); 
    unb = old;
    unb.c_lflag &= ~ICANON; 
    unb.c_lflag &= ~ECHO;
    return 0;
  }

  void _on(){
    tcsetattr(0, TCSANOW, &unb);
  }

  void _off(void){
    tcsetattr(0, TCSANOW, &old);
  }

  char _(void){
    return std::cin.get();
  }
}
