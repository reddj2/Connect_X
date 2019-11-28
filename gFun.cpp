#include "gFun.h"

void fillBoard(vector<vector<char>> &b, int rowS, int colS);
void showBoard(vector<vector<char>> &b, int rowS, int colS);

void getPlayerMove(vector<vector<char>> &b, int rowS, int colS, bool isP2);
bool isValidMove(vector<vector<char>> &b, int rowS, int colS, bool isP2, int pMove);

bool patternSearch(vector<vector<char>> &b, int rowD, int colD, int depth, char tChar, int rowP, int colP);
bool patternCheck(vector<vector<char>> &b, int rowS, int colS, bool isP2, int pSize);
bool movesLeft(vector<vector<char>> &b, int rowS, int colS);
bool winCheck(vector<vector<char>> &b, int rowS, int colS, bool isP2, int pSize);


void fillBoard(vector<vector<char>> &b, int rowS, int colS)
{
    for(int i = 0; i < rowS; i++)
    {
        for(int j = 0; j < colS; j++)
        {
            b[i][j] = '*';
            ///cout << i << j << endl;

        }

    }
    return;
}

void showBoard(vector<vector<char>> &b, int rowS, int colS)
{
    cout << "";  
    for(int h = 0; h < colS; h++){cout << " " << h + 1 << " ";}
    cout << endl;
    for(int i = 0; i < rowS; i++)
    {
        ///cout << " " << i + 1;
        for(int j = 0; j < colS; j++)
        {
            cout << "|" << b[i][j] << "|";
        }
        cout << endl;
    }

}

void getPlayerMove(vector<vector<char>> &b, int rowS, int colS, bool isP2)
{
  char playerSymbol = (isP2) ? 'O':'X';
  int pChoice = -1;

  do
  {
  cout << "Player " << ((isP2) ? "2":"1") << " please select a column: " << endl;
  cin >> pChoice;
  }
  while(!isValidMove(b, rowS, colS, isP2, (pChoice - 1)));


}

bool isValidMove(vector<vector<char>> &b, int rowS, int colS, bool isP2, int pMove)
{
  for(int i = 0; i < rowS; i++)
  {
    if((b[rowS - 1 - i][pMove]) == '*')
    {
      b[rowS - 1 - i][pMove] = (isP2) ? 'O':'X';
      return true;
    }
  }
  return false;
}

bool winCheck(vector<vector<char>> &b, int rowS, int colS, bool isP2, int pSize)
{
  int pID = (isP2) ? 2:1;
  if (patternCheck(b, rowS,  colS, isP2, pSize))
  {
    cout << "Player " << pID << " WINS!!!" << endl;
    return true;
  }
  else if (!(movesLeft(b,rowS,colS)))
  {
    cout << "It's a tie!!!"<< endl;
    return true;
  }
  return false;
}

bool patternCheck(vector<vector<char>> &b, int rowS, int colS, bool isP2 ,int pSize)
{
  char tChar = (isP2) ? 'O':'X';
   ///DownRight search
  for(int i = 0; i <= (rowS - pSize); i++)
  {
    for(int j = 0; j <= (colS - pSize); j++)
    {
      if(patternSearch(b, 1, 1, pSize, tChar, i, j)){return true;}
    }
  }
  ///DownLeft search
  for(int i = 0; i <= (rowS - pSize); i++)
  {
    for(int j = (pSize - 1); j <= (colS - 1); j++)
    {
      if(patternSearch(b, 1, -1, pSize, tChar, i, j)){return true;}
    }
  }
  ///Vertical search
  for(int i = 0; i <= (rowS - pSize); i++)
  {
    for(int j = 0; j <= (colS - 1); j++)
    {
      if(patternSearch(b, 1, 0, pSize, tChar, i, j)){return true;}
    }
  }
  ///Horizontal search
  for(int i = 0; i <= (rowS - 1); i++)
  {
    for(int j = 0; j <= (colS - pSize); j++)
    {
      if(patternSearch(b, 0, 1, pSize, tChar, i, j)){return true;}
    }
  }
  ///If Searches find nothing return false.
   return false;
}

bool patternSearch(vector<vector<char>> &b, int rowD, int colD, int depth, char tChar, int rowP, int colP)
{
  if(b[rowP][colP] != tChar){return false;}
  
  for(int i = 1; i < depth; i++)
  {
    if(b[rowP + (rowD * i)][colP + (colD * i)] != tChar){return false;}
  }
  return true;
}

bool movesLeft(vector<vector<char>> &b, int rowS, int colS)
{
  for(int i = 0; i < rowS; i++)
  {
    for(int j = 0; j < colS; j++)
    {
      ///Checks if board contains '*'
      if(b[i][j] == '*'){return true;}
    }
  }
  return false;
}
