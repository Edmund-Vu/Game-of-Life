#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

class settings{
  public:
    settings();
    ~settings();
    int rows;
    int columns;
    float density;
    string boardType;
    string outputType;
    string fileName;

    void prompt();
};

class classicMode : public settings{
  public:
    classicMode();
    ~classicMode();

    int genCount = 0;
    char** prevBoard;
    char** currBoard;

    void createBoard();
    int checkCornerNW();
    int checkCornerNE();
    int checkCornerSW();
    int checkCornerSE();
    int checkTop();
    int checkRight();
    int checkBottom();
    int checkLeft();

    void nextGen();
    void printGen();
    bool checkContinue();
};

class mirrorMode : public classicMode{
  public:
    mirrorMode();
    ~mirrorMode();
};

class donutMode : public classicMode{
  public:
    donutMode();
    ~donutMode();
};
