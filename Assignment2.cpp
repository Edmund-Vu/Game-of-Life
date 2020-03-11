#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

//constructors and destructors
settings::settings(){}
settings::~settings(){}

classicMode::classicMode(){}
classicMode::~classicMode(){}

mirrorMode::mirrorMode(){}
mirrorMode::~mirrorMode(){}

donutMode::donutMode(){}
donutMode::~donutMode(){}


void settings::prompt(){
  //strings to hold the string value of the row/column counts from the file
  string fileRows = "";
  string fileColumns = "";
  int lineCount = 0;
  char c;
  bool exit = true;
  //while loop to keep prompting the user for either file or random
  while(exit){
    cout << "How would you like your output? Pause, Enter, or File?" << endl;
    cin >> outputType;
    //turns the input into an all-lowercase string for a better conditional statement
    for(int i = 0; i < outputType.length(); ++i){
      outputType[i] = tolower(outputType[i]);
    }

    cout << "Would you like a random board, or would you like to use a file? Type 'random' or 'file.'" << endl;
    cin >> boardType;
    for(int j = 0; j < boardType.length(); ++j){
      boardType[j] = tolower(boardType[j]);
    }

    if(boardType == "file"){
      cout << "What is the name of the file? Include the file extension as well." << endl;
      cin >> fileName;
      ifstream iStream;
      iStream.open(fileName);

      while(!iStream.eof() && lineCount < 2){
        iStream >> noskipws >> c;
        if(c == '\n'){
          lineCount++;
        }
        //first line contains the number of rows
        else if(lineCount == 0){
          fileRows.append(1, c);
        }
        //second line contains the number of columns
        else if(lineCount == 1){
          fileColumns.append(1, c);
        }
        else{
          break;
        }
      }
      //convert the strings read from the file into ints
      rowTotal = stoi(fileRows);
      columnTotal = stoi(fileColumns);
      iStream.close();
      createBoard();
      exit = false;
    }
    else if(boardType == "random"){
      cout << "Rows: ";
      cin >> rowTotal;
      cout << "Columns: ";
      cin >> columnTotal;
      cout << "Density: ";
      cin >> density;
      createBoard();
      exit = false;
    }
    else{
      cout << "Please input a valid option." << endl;
    }
  }
}


void settings::createBoard(){
  currBoard = new char*[rowTotal];
  prevBoard = new char*[rowTotal];

  for(int i = 0; i < rowTotal; ++i){
    currBoard[i] = new char[columnTotal];
    for(int j = 0; j < columnTotal; ++j){
      currBoard[i][j] = '-';
    }
  }

  for(int i = 0; i < rowTotal; ++i){
    prevBoard[i] = new char[columnTotal];
    for(int j = 0; j < rowTotal; ++j){
      prevBoard[i][j] = '-';
    }
  }

  if(boardType == "random"){
    int tileTotal = rowTotal * columnTotal;
    //cast to an int to get a whole number of live cells
    int xTotal = int(tileTotal * density);

    for(int i = 0; i < xTotal; ++i){
      int randRow = rand() % rowTotal;
      int randColumn = rand() % columnTotal;
      if(currBoard[randRow][randColumn] == '-'){
        currBoard[randRow][randColumn] = 'X';
      }
      else{
        //decrement if the position chosen already has an X
        --i;
      }
    }
  }
  else{
    ifstream iStream;
    iStream.open(fileName);
    char c;
    //rowCount is -2 to account for the two lines with the row and column count in the file
    int rowCount = -2;
    int columnCount = 0;
    while(!iStream.eof()){
      iStream >> noskipws >> c;
      if(c == '-' || c == 'X'){
        currBoard[rowCount][columnCount] = c;
        ++columnCount;
      }
      else if(c == '\n'){
        //reset at the end of each line to get correct indexes in future rows
        columnCount = 0;
        ++rowCount;
      }
    }
  }
}


int classicMode::checkTopLeft(int rows, int columns){
  int neighborCount = 0;
  if(prevBoard[rows + 1][columns] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows + 1][columns + 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows][columns + 1] == 'X'){
    ++neighborCount;
  }

  return neighborCount;
}


int classicMode::checkBottomLeft(int rows, int columns){
  int neighborCount = 0;
  if(prevBoard[rows][columns + 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows - 1][columns + 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows - 1][columns] == 'X'){
    ++neighborCount;
  }

  return neighborCount;
}


int classicMode::checkTopRight(int rows, int columns){
  int neighborCount = 0;
  if(prevBoard[rows + 1][columns] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows + 1][columns -1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows][columns - 1] == 'X'){
    ++neighborCount;
  }

  return neighborCount;
}


int classicMode::checkBottomRight(int rows, int columns){
  int neighborCount = 0;
  if(prevBoard[rows - 1][columns] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows - 1][columns - 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows][columns - 1] == 'X'){
    ++neighborCount;
  }

  return neighborCount;
}

int classicMode::checkTop(int rows, int columns){
  int neighborCount = 0;
  if(prevBoard[rows][columns - 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows + 1][columns - 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows + 1][columns] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows + 1][columns + 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows][columns + 1] == 'X'){
    ++neighborCount;
  }

  return neighborCount;
}


int classicMode::checkRight(int rows, int columns){
  int neighborCount = 0;
  if(prevBoard[rows - 1][columns] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows - 1][columns-1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows][columns - 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows + 1][columns - 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows + 1][columns] == 'X'){
    ++neighborCount;
  }

  return neighborCount;
}


int classicMode::checkBottom(int rows, int columns){
  int neighborCount = 0;
  if(prevBoard[rows][columns - 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows - 1][columns - 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows - 1][columns] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows - 1][columns + 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows][columns + 1] == 'X'){
    ++neighborCount;
  }

  return neighborCount;
}


int classicMode::checkLeft(int rows, int columns){
  int neighborCount = 0;
  if(prevBoard[rows - 1][columns] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows - 1][columns + 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows][columns + 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows + 1][columns + 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows + 1][columns] == 'X'){
    ++neighborCount;
  }

  return neighborCount;
}


int classicMode::checkMiddle(int rows, int columns){
  int neighborCount = 0;
  if(prevBoard[rows - 1][columns - 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows - 1][columns] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows - 1][columns + 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows][columns + 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows + 1][columns + 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows + 1][columns] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows + 1][columns - 1] == 'X'){
    ++neighborCount;
  }

  if(prevBoard[rows][columns - 1] == 'X'){
    ++neighborCount;
  }

  return neighborCount;
}


void classicMode::nextGen(){
  int neighborCount;
  for(int i = 0; i < rowTotal; ++i){
    for(int j = 0; j < columnTotal; ++j){
      prevBoard[i][j] = currBoard[i][j];
    }
  }

  for(int k = 0; k < rowTotal; ++k){
    for(int l = 0; l < columnTotal; ++l){
      //reset the neighborCount with each iteration
      neighborCount = 0;
      if(prevBoard[k][l] == 'X'){
        //check for top left or top right corners, else check top
        if(k == 0){
          if(l == 0){
            neighborCount = checkTopLeft(k, l);
          }
          else if(l == (columnTotal - 1)){
            neighborCount = checkTopRight(k, l);
          }
          else{
            neighborCount = checkTop(k, l);
          }
        }
      }
      //check for bottom left or bottom right corners, else check bottom
      else if(k == (rowTotal - 1)){
        if(l == 0){
          neighborCount = checkBottomLeft(k, l);
        }
        else if(l == (columnTotal - 1)){
          neighborCount = checkBottomRight(k, l);
        }
        else{
          neighborCount = checkBottom(k, l);
        }
      }
      else if(l == 0){
        //check whether it isn't a corner
        if(k != 0 && k != (rowTotal - 1)){
          neighborCount = checkLeft(k, l);
        }
      }
      else if(l == (columnTotal - 1)){
        if(k != 0 && k != (rowTotal - 1)){
          neighborCount = checkRight(k, l);
        }
      }
      else{
        neighborCount = checkMiddle(k, l);
      }
      if(neighborCount <= 1){
        currBoard[k][l] = '-';
      }
      else if(neighborCount == 3){
        currBoard[k][l] = 'X';
      }
      else{
        currBoard[k][l] = '-';
      }
    }
  }
}


void classicMode::printGen(){
  cout << "Generation " << genCount << endl;
  for(int i = 0; i < rowTotal; ++i){
    for(int j = 0; j < columnTotal; ++j){
      cout << currBoard[i][j];
    }
  }
  ++genCount;
}


bool classicMode::checkEmpty(){
  bool isEmpty = false;
  if(currBoard[0][0] == '-'){
    for(int i = 0; i < rowTotal; ++i){
      for(int j = 0; j < columnTotal; ++j){
        if(currBoard[i][j] == '-'){
          isEmpty = true;
        }
        else{
          isEmpty = false;
        }
      }
    }
  }
  return isEmpty;
}


int mirrorMode::mirrorTopLeft(int rows, int columns){
  int neighborCount = 3;
  if(prevBoard[rows + 1][columns] == 'X'){
    neighborCount += 2;
  }
  else if(prevBoard[rows + 1][columns + 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows][columns + 1] == 'X'){
    neighborCount += 2;
  }

  return neighborCount;
}


int mirrorMode::mirrorBottomLeft(int rows, int columns){
  int neighborCount = 3;
  if(prevBoard[rows - 1][columns] == 'X'){
    neighborCount += 2;
  }
  else if(prevBoard[rows - 1][columns + 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows][columns + 1] == 'X'){
    neighborCount += 2;
  }

  return neighborCount;
}


int mirrorMode::mirrorTopRight(int rows, int columns){
  int neighborCount = 3;
  if(prevBoard[rows][columns - 1] == 'X'){
    neighborCount += 2;
  }
  else if(prevBoard[rows + 1][columns - 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows + 1][columns] == 'X'){
    neighborCount += 2;
  }

  return neighborCount;
}


int mirrorMode::mirrorBottomRight(int rows, int columns){
  int neighborCount = 3;
  if(prevBoard[rows - 1][columns] == 'X'){
    neighborCount += 2;
  }
  else if(prevBoard[rows - 1][columns - 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows][columns - 1] == 'X'){
    neighborCount += 2;
  }

  return neighborCount;
}


int mirrorMode::mirrorTop(int rows, int columns){
  int neighborCount = 1;
  if(prevBoard[rows][columns - 1] == 'X'){
    neighborCount += 2;
  }
  else if(prevBoard[rows + 1][columns - 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows + 1][columns] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows + 1][columns + 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows][columns + 1] == 'X'){
    neighborCount += 2;
  }

  return neighborCount;
}


int mirrorMode::mirrorRight(int rows, int columns){
  int neighborCount = 1;
  if(prevBoard[rows - 1][columns] == 'X'){
    neighborCount += 2;
  }
  else if(prevBoard[rows - 1][columns - 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows][columns - 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows + 1][columns - 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows + 1][columns] == 'X'){
    neighborCount += 2;
  }

  return neighborCount;
}


int mirrorMode::mirrorBottom(int rows, int columns){
  int neighborCount = 1;
  if(prevBoard[rows][columns - 1] == 'X'){
    neighborCount += 2;
  }
  else if(prevBoard[rows - 1][columns - 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows - 1][columns] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows - 1][columns + 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows][columns + 1] == 'X'){
    neighborCount += 2;
  }

  return neighborCount;
}


int mirrorMode::mirrorLeft(int rows, int columns){
  int neighborCount = 1;
  if(prevBoard[rows - 1][columns] == 'X'){
    neighborCount += 2;
  }
  else if(prevBoard[rows - 1][columns + 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows][columns + 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows + 1][columns + 1] == 'X'){
    ++neighborCount;
  }
  else if(prevBoard[rows + 1][columns] == 'X'){
    neighborCount += 2;
  }

  return neighborCount;
}


int donutMode::donutTopLeft(int rows, int columns){
  int neighborCount = 
}
