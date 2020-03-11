#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

class classicMode{
  public:
    classicMode();
    ~classicMode();

    int rows;
    int columns;
    int genCount = 1;
    char** prevBoard;
    char** currBoard;

    void randomBoard(int rows, int columns, float density);
    void fileBoard(int rows, int columns, float density);
    int checkCornerNW(int row, int column);
    int checkCornerNE(int row, int column);
    int checkCornerSW(int row, int column);
    int checkCornerSE(int row, int column);
    int checkTop(int row, int column);
    int checkRight(int row, int column);
    int checkBottom(int row, int column);
    int checkLeft(int row, int column);

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
