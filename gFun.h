#ifndef gFun_h
#define gFun_h

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void fillBoard(vector<vector<char>> &b, int rowS, int colS);
void showBoard(vector<vector<char>> &b, int rowS, int colS);

void getPlayerMove(vector<vector<char>> &b, int rowS, int colS, bool isP2);
bool isValidMove(vector<vector<char>> &b, int rowS, int colS, bool isP2, int pMove);

bool patternSearch(vector<vector<char>> &b, int rowD, int colD, int depth, char tChar, int rowP, int colP);
bool patternCheck(vector<vector<char>> &b, int rowS, int colS, bool isP2, int pSize);
bool movesLeft(vector<vector<char>> &b, int rowS, int colS);
bool winCheck(vector<vector<char>> &b, int rowS, int colS, bool isP2, int pSize);

#endif