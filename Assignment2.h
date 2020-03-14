#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

class gameOfLife{
  public:
    gameOfLife();
    ~gameOfLife();
    int rowTotal;
    int columnTotal;
    int genCount = 0;
    int oscillationCount = 0;
    int patternLoopingCount = 0;
    float density;
    string boardType;
    string outputType;
    string fileName;
    string gameMode;
    string outputContent;
    string outputFileName;

    char** currBoard;
    char** prevBoard;
    char** secondPrevBoard;

    void prompt();
    void createBoard();
    //classic mode functions
    int classicTopLeft(int row, int column);
    int classicBottomLeft(int row, int column);
    int classicTopRight(int row, int column);
    int classicBottomRight(int row, int column);
    int classicTop(int row, int column);
    int classicRight(int row, int column);
    int classicBottom(int row, int column);
    int classicLeft(int row, int column);
    int checkMiddle(int row, int column);
    //mirror mode functions
    int mirrorTopLeft(int row, int column);
    int mirrorBottomLeft(int row, int column);
    int mirrorTopRight(int row, int column);
    int mirrorBottomRight(int row, int column);
    int mirrorTop(int row, int column);
    int mirrorRight(int row, int column);
    int mirrorBottom(int row, int column);
    int mirrorLeft(int row, int column);
    //doughnut mode functions
    int doughnutTopLeft(int row, int column);
    int doughnutBottomLeft(int row, int column);
    int doughnutTopRight(int row, int column);
    int doughnutBottomRight(int row, int column);
    int doughnutTop(int row, int column);
    int doughnutRight(int row, int column);
    int doughnutBottom(int row, int column);
    int doughnutLeft(int row, int column);
    //functions shared by all 3 game modes
    void printGen();
    void nextGen();
    bool checkEmpty();
    bool checkOscillation();
    bool checkPatternLooping();
};
