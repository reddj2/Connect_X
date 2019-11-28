#include "gFun.h"
#include <fstream>

struct bSet
{
  int colS;
  int rowS;
  int pSize;
};
///New Functions 
///Displays main menu and reads in a player choice.
int mainMenuDisplay();
///Switch statements to run the game based on menu selection
bool gameModes(int gameModeID);
///Allows user to set up the board
bSet setupBoard(vector<vector<char>> &b);

void pvpGameMode();
void pvcGameMode();

int minMaxMove(vector<vector<char>> &b, bSet bVal, int depth, bool isMax, bool isP2);
int moveScore(vector<vector<char>> &b, bSet bVal, bool isP2);
int getOptimalMove(vector<vector<char>> &b, bSet bVal, bool isP2);

bool aiWinCon(vector<vector<char>> &b, int rowS, int colS, bool isP2, int pSize);


int main() 
{
  
  while(gameModes(mainMenuDisplay())){}

  return 0;
}

int mainMenuDisplay()
{
  int pChoice = -1;
  string lineOut = "";
  ifstream tFile;
  tFile.open("Title.txt");
  
  while(getline(tFile, lineOut))
  {
    cout << lineOut << endl;
  }

  /*cout << "~XOXOXOXOX~" << endl;
  cout << " CONNECT_X " << endl;
  cout << "~OXOXOXOXO~" << endl; */
  cout << endl;
  cout << endl;
  cout << "X_Main Menu_O" << endl;
  cout << "0 -Player vs Player" << endl; 
  cout << "1 -Player vs Computer" << endl; 
  cout << "2 -Computer vs Player" << endl;
  cout << "3 -Computer vs Computer" << endl;
  cout << "66 -Exit" << endl;
  cout << endl;
  do
  {
    cout << "Type number for selection: " << endl;
    cin >> pChoice;
  }
  while((pChoice != 0)&&(pChoice != 1)&&(pChoice != 2)&&(pChoice != 3)&&(pChoice != 66));
  cout << endl;
  return pChoice;
}
///Not finished///
bool gameModes(int gameModeID)
{
  switch(gameModeID)
  {
    case 0:
    pvpGameMode();
    return true;
      break;
    case 1:
    pvcGameMode();
    return true;
      break;
    case 2:

      return true;
      break;
    case 3:

      return true;
      break;
    case 66:
      cout << "Goodbye!" << endl;
      return false;
      break;
  }
  cout << "Error should not have happend" << endl;
  return false;
}

bSet setupBoard(vector<vector<char>> &b)
{
  int rSize = 6;
  int cSize = 7;
  int pSize = 4;
  int dChoice = 1;
  int maxPat = 0;
  bSet rValues;
  do
  {
    cout << "Use default board size(0=No // 1=Yes):" << endl;
    cin >> dChoice;
  }
  while((dChoice < 0) || (dChoice > 1));
  if(dChoice == 0)
  {
    do
    {
      cout << "Enter row size between 3-16: " << endl;
      cin >> rSize;
    }
    while((rSize < 3) || (rSize > 16));

    do
    {
      cout << "Enter column size between 3-16: " << endl;
      cin >> cSize;
    }
    while((cSize < 3) || (cSize > 16));
    ///Sets the maximum pattern size
    maxPat = min(rSize,cSize);

    do
    {
      
      cout << "Enter pattern size between a minimum of 3 and a max of " << maxPat << endl;
      cin >> pSize;
    }
    while((pSize < 3) || (pSize > maxPat));
   
  } 
  b.resize(rSize, vector<char>(cSize));
  fillBoard(b, rSize, cSize);
  //Sets the struct values before returning them
  rValues.rowS = rSize;
  rValues.colS = cSize;
  rValues.pSize = pSize;

  return rValues;
}

void pvpGameMode()
{
  bSet bValues;
  vector<vector<char>> board;
  bool isPlayer2 = true;
  bValues = setupBoard(board);
  showBoard(board, bValues.rowS, bValues.colS);

  do
  {
    isPlayer2 = !(isPlayer2);
    
    
    getPlayerMove(board,board.size(), board[0].size(),isPlayer2);
    cout << endl;
    showBoard(board, bValues.rowS, bValues.colS);
  }
  while(!winCheck(board, bValues.rowS, bValues.colS, isPlayer2, bValues.pSize));
  cout << endl;
}

void pvcGameMode()
{
  bSet bValues;
  vector<vector<char>> board;
  bool isPlayer2 = true;
  bValues = setupBoard(board);
  showBoard(board, bValues.rowS, bValues.colS);
  int aiMove = -1;

  do
  {
    isPlayer2 = !(isPlayer2);
    
    if(!isPlayer2)
    { 
      getPlayerMove(board,board.size(), board[0].size(),isPlayer2);
      cout << endl;
    }
    else
    {
      aiMove = getOptimalMove(board , bValues, isPlayer2);
      ///aiMove = 1;
      if(isValidMove(board, bValues.rowS, bValues.colS, isPlayer2, aiMove)){cout << aiMove << endl;}
    }
    showBoard(board, bValues.rowS, bValues.colS);
  }
  while(!winCheck(board, bValues.rowS, bValues.colS, isPlayer2, bValues.pSize));
  cout << endl;
}

int getOptimalMove(vector<vector<char>> &b, bSet bVals, bool isP2)
{
    int bestScore = -1000;
    int optMove;
    optMove = -1;

    for(int j = 0; j < bVals.colS; j++)
    {
      int rcount = bVals.rowS -1;
      while((b[rcount][j] != '*') && (rcount >= 0)){rcount--;}
        if(b[rcount][j] == '*')
        {
            b[rcount][j] = (!isP2) ? 'X' : 'O';

            int tempScore = minMaxMove(b, bVals, 0, false, isP2);

            b[rcount][j] = '*';

            if(tempScore > bestScore)
            {
                optMove = j;
                bestScore = tempScore;
            }
        }
    }
    return optMove;
}

int moveScore(vector<vector<char>> &b, bSet bVal, bool isP2)
{
    char winC = 'X';
    char loseC = 'O';
    if(isP2)
        {
            winC = 'O';
            loseC = 'X';
        }

    if(aiWinCon(b, bVal.rowS, bVal.colS, isP2, bVal.pSize))
    {
        return 10;
    }
    else if(aiWinCon(b, bVal.rowS, bVal.colS, !isP2, bVal.pSize))
    {
        return -10;
    }
    else
    {
        return 0;
    }

}

int minMaxMove(vector<vector<char>> &b, bSet bVal, int depth, bool isMax, bool isP2)
{
    int score = moveScore(b, bVal, isP2);

    ///Returns a win/loss/or tie else continues to minMax
    if(score == 10) {return score;}
    if(score == -10) {return score;}

    if(movesLeft(b, bVal.rowS, bVal.colS) == false) {return 0;}

    if(isMax)
    {
        ///seeks to find the max score possible.
        int bestScore = -10000;

        for(int i = 0; i < bVal.rowS; i++)
        {
            for(int j = 0; j < bVal.colS; j++)
            {
                if(b[i][j] == '*')
                {
                    b[i][j] = (!isP2) ? 'X' : 'O';

                    bestScore = max(bestScore, minMaxMove(b, bVal, depth +1, !isMax, isP2 ));

                    b[i][j] = '*';
                }
            }
        }
        return bestScore - depth;
    }
    else
    {
        ///seeks to find the min score possible.
        int bestScore = 10000;

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if(b[i][j] == '*')
                {
                    b[i][j] = (!isP2) ? 'O' : 'X';

                    bestScore = min(bestScore, minMaxMove(b, bVal, depth +1, !isMax, isP2 ));

                    b[i][j] = '*';
                }
            }
        }
        return bestScore + depth;
    }
}

bool aiWinCon(vector<vector<char>> &b, int rowS, int colS, bool isP2, int pSize)
{
  int pID = (isP2) ? 2:1;
  if (patternCheck(b, rowS,  colS, isP2, pSize))
  {
    ///cout << "Player " << pID << " WINS!!!" << endl;
    return true;
  }
  /*else if (!(movesLeft(b,rowS,colS)))
  {
    ///cout << "It's a tie!!!"<< endl;
    return true;
  }
  */
  return false;
}