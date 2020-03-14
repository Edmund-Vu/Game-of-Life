#include "Assignment2.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv){
  bool exit = true;
  gameOfLife *game = new gameOfLife();

  game -> prompt();
  for(int i = 0; i < 4; ++i){
    game -> printGen();
    game -> nextGen();
  }
  delete game;

  return 0;
}
