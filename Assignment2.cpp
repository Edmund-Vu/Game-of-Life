#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <unistd.h>

using namespace std;

//constructor and destructor
gameOfLife::gameOfLife(){}
gameOfLife::~gameOfLife(){}


void gameOfLife::prompt(){
  //strings to hold the string value of the row/column counts from the file
  string fileRows = "";
  string fileColumns = "";
  int lineCount = 0;
  char c;
  bool exit = true;
  //while loop to keep prompting the user for either file or random
  while(exit){
    cout << "What game mode would you like? Type 'classic,' 'mirror,' or 'doughnut.'" << endl;
    cin >> gameMode;
    //turns the input into an all-lowercase string for a better conditional statement
    for(int i = 0; i < gameMode.length(); ++i){
      gameMode[i] = tolower(gameMode[i]);
    }

    cout << "How would you like your output? Pause, Enter, or File?" << endl;
    cin >> outputType;
    for(int j = 0; j < outputType.length(); ++j){
      outputType[j] = tolower(outputType[j]);
    }
    if(outputType == "file"){
      cout << "What is the name of the output file? Type the full name of the file, including the file type." << endl;
      cin >> outputFileName;
    }

    cout << "Would you like a random board, or would you like to use a file? Type 'random' or 'file.'" << endl;
    cin >> boardType;
    for(int k = 0; k < boardType.length(); ++k){
      boardType[k] = tolower(boardType[k]);
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
      rowTotal = std::stoi(fileRows);
      columnTotal = std::stoi(fileColumns);
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


void gameOfLife::createBoard(){
  currBoard = new char*[rowTotal];
  //create boards full of dashes (-), and populate them later
  for(int i = 0; i < rowTotal; ++i){
    currBoard[i] = new char[columnTotal];
    for(int j = 0; j < columnTotal; ++j){
      currBoard[i][j] = '-';
    }
  }

  prevBoard = new char*[rowTotal];

  for(int i = 0; i < rowTotal; ++i){
    prevBoard[i] = new char[columnTotal];
    for(int j = 0; j < columnTotal; ++j){
      prevBoard[i][j] = '-';
    }
  }

  secondPrevBoard = new char*[rowTotal];

  for(int i = 0; i < rowTotal; ++i){
    secondPrevBoard[i] = new char[columnTotal];
    for(int j = 0; j < columnTotal; ++j){
      secondPrevBoard[i][j] = '-';
    }
  }

  if(boardType == "random"){
    int tileTotal = rowTotal * columnTotal;
    //cast to an int to get a whole number of live cells
    int xTotal = int(tileTotal * density);

    for(int i = 0; i < xTotal; ++i){
      //create random coordinates to place 'X'
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
        prevBoard[rowCount][columnCount] = c;
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

//check methods are fed the coordinates the function is named after
int gameOfLife::classicTopLeft(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1]){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::classicTopRight(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::classicBottomRight(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::classicBottomLeft(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::classicTop(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::classicRight(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::classicBottom(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::classicLeft(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::checkMiddle(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row - 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::mirrorTopLeft(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column] == 'X'){
    //if the corner is occupied, it will have at least 3 neighbors
    neighborCount += 3;
  }
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1]){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::mirrorTopRight(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column] == 'X'){
    neighborCount += 3;
  }
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1]){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::mirrorBottomRight(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column] == 'X'){
    neighborCount += 3;
  }
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::mirrorBottomLeft(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column] == 'X'){
    neighborCount += 3;
  }
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::mirrorTop(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column] == 'X'){
    neighborCount += 2;
  }
  if(prevBoard[row][column - 1] == 'X'){
    neighborCount += 2;
  }
  if(prevBoard[row + 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    neighborCount += 2;
  }
  return neighborCount;
}


int gameOfLife::mirrorRight(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column] == 'X'){
    neighborCount += 2;
  }
  if(prevBoard[row - 1][column] == 'X'){
    neighborCount += 2;
  }
  if(prevBoard[row - 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column] == 'X'){
    neighborCount += 2;
  }
  return neighborCount;
}


int gameOfLife::mirrorBottom(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column] == 'X'){
    neighborCount += 2;
  }
  if(prevBoard[row][column - 1] == 'X'){
    neighborCount += 2;
  }
  if(prevBoard[row - 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    neighborCount += 2;
  }
  return neighborCount;
}


int gameOfLife::mirrorLeft(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column] == 'X'){
    neighborCount += 2;
  }
  if(prevBoard[row - 1][column] == 'X'){
    neighborCount += 2;
  }
  if(prevBoard[row - 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column] == 'X'){
    neighborCount += 2;
  }
  return neighborCount;
}


int gameOfLife::doughnutTopLeft(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[(rowTotal - 1)][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[(rowTotal - 1)][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[(rowTotal - 1)][columnTotal - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][columnTotal - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][columnTotal - 1] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::doughnutTopRight(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[rowTotal - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[rowTotal - 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[rowTotal - 1][0] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][0] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][0] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::doughnutBottomRight(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][0] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][0] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[0][0] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[0][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[0][column] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::doughnutBottomLeft(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[0][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[0][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[0][columnTotal - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][columnTotal - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][columnTotal - 1] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::doughnutTop(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[rowTotal - 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[rowTotal - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[rowTotal - 1][column + 1] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::doughnutRight(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][0] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][0] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][0] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::doughnutBottom(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[0][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[0][column - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[0][column + 1] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


int gameOfLife::doughnutLeft(int row, int column){
  int neighborCount = 0;
  if(prevBoard[row - 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column + 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][column] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row][columnTotal - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row - 1][columnTotal - 1] == 'X'){
    ++neighborCount;
  }
  if(prevBoard[row + 1][columnTotal - 1] == 'X'){
    ++neighborCount;
  }
  return neighborCount;
}


void gameOfLife::printGen(){
  bool exit = true;
  if(outputType != "file"){
    cout << "Generation " << genCount << endl;
    for(int i = 0; i < rowTotal; ++i){
      for(int j = 0; j < columnTotal; ++j){
        cout << currBoard[i][j];
      }
      cout << endl;
    }
    ++genCount;
    cout << endl;
    if(outputType == "pause"){
      sleep(1);
    }
    else if(outputType == "enter"){
      while(exit){
        cout << "Press ENTER to continue. ";
        if(cin.get() == '\n'){
          exit = false;
        }
      }
    }
  }
  else{
    ofstream oStream;
    oStream.open(outputFileName);
    outputContent += ("Generation ");
    outputContent += to_string(genCount);
    outputContent += '\n';
    for(int i = 0; i < rowTotal; ++i){
      for(int j = 0; j < columnTotal; ++j){
        outputContent += currBoard[i][j];
      }
      outputContent += '\n';
    }
    outputContent += '\n';
    ++genCount;
    oStream << outputContent;
    oStream.close();
  }
}


void gameOfLife::nextGen(){
  int neighborCount = 0;
  char c;
  for(int i = 0; i < rowTotal; ++i){
    for(int j = 0; j < columnTotal; ++j){
      secondPrevBoard[i][j] = prevBoard[i][j];
      prevBoard[i][j] = currBoard[i][j];
    }
  }

  for(int k = 0; k < rowTotal; ++k){
    for(int l = 0; l < columnTotal; ++l){
      if(k == 0){
        if(l == 0){
          if(gameMode == "classic"){
            neighborCount = classicTopLeft(k,l);
          }
          else if(gameMode == "mirror"){
            neighborCount = mirrorTopLeft(k,l);
          }
          else if(gameMode == "doughnut"){
            neighborCount = doughnutTopLeft(k,l);
          }
        }
        else if(l == (columnTotal - 1)){
          if(gameMode == "classic"){
            neighborCount = classicTopRight(k,l);
          }
          else if(gameMode == "mirror"){
            neighborCount = mirrorTopRight(k,l);
          }
          else{
            neighborCount = doughnutTopRight(k,l);
          }
        }
        else{
          if(gameMode == "classic"){
            neighborCount = classicTop(k,l);
          }
          else if(gameMode == "mirror"){
            neighborCount = mirrorTop(k,l);
          }
          else{
            neighborCount = doughnutTop(k,l);
          }
        }
      }
      else if(k == (rowTotal - 1)){
        if(l == 0){
          if(gameMode == "classic"){
            neighborCount = classicBottomLeft(k,l);
          }
          else if(gameMode == "mirror"){
            neighborCount = mirrorBottomLeft(k,l);
          }
          else{
            neighborCount = doughnutBottomLeft(k,l);
          }
        }
        else if(l == (columnTotal - 1)){
          if(gameMode == "classic"){
            neighborCount = classicBottomRight(k,l);
          }
          else if(gameMode == "mirror"){
            neighborCount = mirrorBottomRight(k,l);
          }
          else{
            neighborCount = doughnutBottomRight(k,l);
          }
        }
        else{
          if(gameMode == "classic"){
            neighborCount = classicBottom(k,l);
          }
          else if(gameMode == "mirror"){
            neighborCount = mirrorBottom(k,l);
          }
          else{
            neighborCount = doughnutBottom(k,l);
          }
        }
      }
      else if(l == 0){
        if(gameMode == "classic"){
          neighborCount = classicLeft(k,l);
        }
        else if(gameMode == "mirror"){
          neighborCount = mirrorLeft(k,l);
        }
        else{
          neighborCount = doughnutLeft(k,l);
        }
      }
      else if(l == (columnTotal - 1)){
        if(gameMode == "classic"){
          neighborCount = classicRight(k,l);
        }
        else if(gameMode == "mirror"){
          neighborCount = mirrorRight(k,l);
        }
        else{
          neighborCount = doughnutRight(k,l);
        }
      }
      else{
        neighborCount = checkMiddle(k,l);
      }
      if(neighborCount <= 1){
        currBoard[k][l] = '-';
      }
      else if(neighborCount == 2){
        currBoard[k][l] = currBoard[k][l];
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


bool gameOfLife::checkEmpty(){
  for(int i = 0; i < rowTotal; ++i){
    for(int j = 0; j < columnTotal; ++j){
      if(currBoard[i][j] == '-'){
        ++emptyCount;
      }
    }
  }
  if(emptyCount == (rowTotal * columnTotal)){
    return true;
  }
  else{
    return false;
  }
  emptyCount = 0;
}


bool gameOfLife::checkOscillation(){
  for(int i = 0; i < rowTotal; ++i){
    for(int j = 0; j < columnTotal; ++j){
      if(secondPrevBoard[i][j] == currBoard[i][j]){
        ++oscillationCount;
      }
    }
  }
  if(oscillationCount == (rowTotal * columnTotal)){
    return true;
  }
  else{
    return false;
  }
  oscillationCount = 0;
}


bool gameOfLife::checkRepeating(){
  for(int i = 0; i < rowTotal; ++i){
    for(int j = 0; j < columnTotal; ++j){
      if(prevBoard[i][j] == currBoard[i][j]){
        ++repeatingCount;
      }
    }
  }
  if(repeatingCount == (rowTotal * columnTotal)){
    if(genCount == 0 || genCount == 1){
      return false;
    }
    else{
      return true;
    }
  }
  else{
    return false;
  }
  repeatingCount = 0;
}
