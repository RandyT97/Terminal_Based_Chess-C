/*Randy Tsui
10/28/16
Chess.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct player{
  char fname[20];
  char lname[20];
  int win;
  int loss;
};
// REMEMBER TO CHECK FOR WHETHER IT IS IN THE BOARD ARRAY
/*
int playHorde(player A, player B);
void boardHorde(char board[8][8]);
int playChess960(char board[8][8]);
void board960(char board[8][8]);

// REMEMBER TO CHECK FOR WHETHER FINAL POS IS IN THE BOARD[8][8] ARRAY
int isValid(char board[8][8], int initx, int inity, int x, int y);
void kingSafe(char board[8][8],int x, int y);
void castle(char board[8][8], int initx, int inity, int x, int y);
*/
void getInfo();
void boardStandard(char board[8][8]);
void displayBoard(char board[8][8]);
int knight(char board[8][8], int initx, int inity, int x, int y);
int queen(char board[8][8], int initx, int inity, int x, int y);
int king(char board[8][8], int initx, int inity, int x, int y);
int rook(char board[8][8], int initx, int inity, int x, int y);
int bishop(char board[8][8], int initx, int inity, int x, int y);
int pawn(char board[8][8], int initx, int inity, int x, int y);
char move(char board[8][8], int initx, int inity, int x, int y);x
char promote();
int isCheck(char board[8][8]);
int isCheckMate(char board[8][8]);
void notate();
void playerMenu();
int playStandard(player A, player B);

//t
int main() {
  int input=5;
  printf("Welcome to \"C\"hess!\n \n");
  printf("What would you like to do?");
  playerMenu();

}
void playerMenu() {
  int input=0;
  printf("1. Start a standard game\n");
  printf("2. Create Player Profile\n");
  printf("3. Print Player Statistics\n");
  printf("4. Exit\n");
  scanf("%d",&input);
  switch(input) {
    case(1): {
      playStandard()
    }
  }
}
// STANDARD BOARD MATERIALS
void playStandard(player A, player B) {//DEPENDS ON PRINTOUT LOCATIONS!!!
  int game = 1;
  int initialx;
  int initialy;
  int finalx;
  int finaly;
  char standardboard[8][8];
  boardStandard(standardboard[8][8]);
  while(game==1) {
    displayBoard(standardboard[8][8]);
    printf("Enter the location of your piece.\n");
    scanf("%d",&initialx); //Depends on how location is prented
    scanf("%d"&initialy); //^^
    printf("Enter the final location\n");
    scanf("%d",&finalx);
    scanf("%d",&finaly);
  }
}
//Populates board
void boardStandard(char board[8][8]) {
  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      board[i][j]='-';
    }
  }
  //Populate pawns
  for(int i=0;i<8;i++) {
    board[1][i]='p';
    board[6][i]='P';
  }
  //Populate rooks
  for(int i=0;i<8;i+=7) {
    board[0][i]='r';
    board[7][i]='R';
  }
  //Populate knights
  for(int i=1;i<8;i+=5) {
    board[0][i]='n';
    board[7][i]='N';
  }
  //Populate bishops
  for(int i=2;i<8;i+=3) {
    board[0][i]='b';
    board[7][i]='B';
  }
  //Populate Kings and Queens
  board[0][3]='q';
  board[0][4]='k';
  board[7][3]='Q';
  board[7][4]='K';

}
//Prints board
void displayBoard(char board[8][8]) {
  //printout
  for(int i=0;i<8;i++) {
    printf("[%d]\t",abs(i-8));
    for(int j=0;j<8;j++) {
      printf("%c\t",board[i][j]);
    }
    printf("\n\n");
  }
  printf("\t[A]\t[B]\t[C]\t[D]\t[E]\t[F]\t[G]\t[H]\n");
}

//Pre-conditions:
//Post-conditions: Deletes the piece from initial position and places it in final
void move(char board[8][8], int initx, int inity, int x, int y) {
  char piece = board[initx][inity];
  int flag=0;
  int flag1=0;
  switch(piece) {
    case('n'||'N'): {
      flag = knight(board[8][8],initx,inity,x,y);
    }
    case('q'||'Q') {
      flag = queen(board[8][8],initx,inity,x,y);
    }
    case('k'||'K') {
      flag = king(board[8][8],initx,inity,x,y);
    }
    case('r'||'R') {
      flag = rook(board[8][8],initx,inity,x,y);
    }
    case('b'||'B') {
      flag = bishop(board[8][8],initx,inity,x,y);
    }
    case('p'||'P') {
      flag = pawn(board[8][8],initx,inity,x,y);
      if((x==7)||(x==0))
        piece = promote();
    }
    if(flag) {
      board[initx][inity]='-';
      board[x][y]=piece;
    }
    else
      printf("Move is invalid, please try again.\n");
  }

}

char promote() {//may be an issue, case sensitive?
  char piece;
  printf("What piece would you like to promote to?\n")
  scanf("%c",&piece);
  return piece;
}
//ALL PIECE PATTERN FUNCTIONS INCLUDE ALL POSSIBLE MOVES INCLUDING EXCEPTIONS
//Preconditions: Board, initial x and y, and desired final location is passed
//returns 0 if impossible, returns 1 if possible.
int knight(char board[8][8], int initx, int inity,int x,int y) {
  int possible[8][2] = {
    //There is probably a loop to better initialize this array
    {initx-2,inity-1},
    {initx-2,inity+1},
    {initx-1,inity-2},
    {initx-1,inity+2},
    {initx+1,inity-2},
    {initx+1,inity+2},
    {initx+2,inity-1},
    {initx+2,inity+1}
  };
  int flag=0;
    //Search loop is functional
  for(int i=0;i<8;i++) {
      if((x==possible[i][0])&&(y==possible[i][1]))
        flag=1;
  }
  return flag;
}
int king(char board[8][8], int initx, int inity, int x, int y) {
  int flag=0;
  int possible[8][2] = {
    {initx-1,inity-1},
    {initx-1,inity},
    {initx-1,inity+1},
    {initx,inity-1},
    {initx,inity+1},
    {initx+1,inity-1},
    {initx+1,inity},
    {initx+1,inity-1}
  };
  //Search loop is functional
  for(int i=0;i<8;i++) {
      if((x==possible[i][0])&&(y==possible[i][1]))
        flag=1;
    }
  return flag;
}
//TODO: Find a way to determine which side the pawn came from
int pawn(char board[8][8], int initx, int inity, int x, int y) {
  int flag=0;
  if(board[initx][inity] == 'P') {
    int possibleP[3][2] = {
      {initx-1,inity-1},
      {initx-1,inity},
      {initx-1,inity+1}
    };
      //Search loop is functional
    for(int i=0;i<3;i++) {
        if((x==possibleP[i][0])&&(y==possibleP[i][1]))
          flag=1;
    }
  }
  else {
    int possibleP[3][2] = {
      {initx+1,inity-1},
      {initx+1,inity},
      {initx+1,inity+1}
    };
      //Search loop is functional
    for(int i=0;i<3;i++) {
        if((x==possibleP[i][0])&&(y==possibleP[i][1]))
          flag=1;
    }
  }
}
int rook(char board[8][8], int initx, int inity, int x, int y) {
  int flag=0;
  if((initx == x)||(inity == y))
    if(!((initx == x)&&(inity == y)))
        flag=1;
  return flag;
}
int bishop(char board[8][8], int initx, int inity, int x, int y) {
  if(abs(x-initx)==abs(y-inity))
    return 1;
  else
    return 0;
}
int queen(char board[8][8], int initx, int inity, int x, int y) {
  int flag=0;
  if((initx == x)||(inity == y)) //diagonals recycled from bishop
    flag=1;
  if((initx == x)||(inity == y)) //row recycled from rooks
    if(!((initx == x)&&(inity == y)))
        flag=1;
  return flag;
}
