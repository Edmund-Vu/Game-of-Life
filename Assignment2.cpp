#include "Assignment2.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

settings::settings(){

}

settings::~settings(){

}

classicMode::classicMode(){

}

classicMode::~classicMode(){

}

mirrorMode::mirrorMode(){

}

mirrorMode::~mirrorMode(){

}

donutMode::donutMode(){

}

donutMode::~donutMode(){

}

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
      rows = stoi(fileRows);
      columns = stoi(fileColumns);
      iStream.close();
      exit = false;
    }
    else if(boardType == "random"){
      cout << "Rows: ";
      cin >> rows;
      cout << "Columns: ";
      cin >> columns;
      cout << "Density: ";
      cin >> density;
      exit = false;
    }
    else{
      cout << "Please input a valid option." << endl;
    }
  }
}


void classicMode::createBoard(){
  currBoard = new char*[rows];
  prevBoard = new char*[rows];

  for(int i = 0; i < rows; ++i){
    currBoard[i] = new char[columns];
    for(int j = 0; j < columns; ++j){
      currBoard[i][j] = '-';
    }
  }

  for(int i = 0; i < rows; ++i){
    prevBoard[i] = new char[columns];
    for(int j = 0; j < rows; ++j){
      prevBoard[i][j] = '-';
    }
  }

  if(boardType == "random"){
    int tileTotal = rows * columns;
    //cast to an int to get a whole number of live cells
    int xTotal = int(tileTotal * density);

    for(int i = 0; i < xTotal; ++i){
      int randRow = rand() % rows;
      int randColumn = rand() % columns;
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
      else if(c == 'n'){
        //reset at the end of each line to get correct indexes in future rows
        columnCount = 0;
        ++rowCount;
      }
    }
  }
}
