#include "Assignment2.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv){
  gameOfLife *game = new gameOfLife();

  game -> prompt();
  for(int i = 0; i < 199; ++i){
    game -> printGen();
    game -> nextGen();
    if(game -> checkEmpty()){
      cout << "The board is empty." << endl;
      break;
    }
    if(game -> checkOscillation()){
      cout << "The board is oscillating." << endl;
      break;
    }
    if(game -> checkRepeating()){
      cout << "The board is repeating." << endl;
    }
  }

  delete game;
  return 0;
}
