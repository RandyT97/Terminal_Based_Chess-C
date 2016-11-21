/*Randy Tsui
10/28/16
Chess.c
*/
#include <stdio.h>
#include <stdlib.h>

struct player{
  char fname[20];
  char lname[20];
  int win;
  int loss;
};
// REMEMBER TO CHECK FOR WHETHER IT IS IN THE BOARD ARRAY

/*int playStandard(player A, player B);
int playHorde(player A, player B);
void boardHorde(char board[8][8]);
int playChess960(char board[8][8]);
void board960(char board[8][8]);
char move(char board[8][8], int initx, int inity, int x, int y);
// REMEMBER TO CHECK FOR WHETHER FINAL POS IS IN THE BOARD[8][8] ARRAY
int isValid(char board[8][8], int initx, int inity, int x, int y);
void kingSafe(char board[8][8],int x, int y);
void castle(char board[8][8], int initx, int inity, int x, int y);
*/
void boardStandard(char board[8][8]);
void displayBoard(char board[8][8]);
int knight(char board[8][8], int initx, int inity, int x, int y);
int queen(char board[8][8], int initx, int inity, int x, int y);
int king(char board[8][8], int initx, int inity, int x, int y);
int rook(char board[8][8], int initx, int inity, int x, int y);
int bishop(char board[8][8], int initx, int inity, int x, int y);
int pawn(char board[8][8], int initx, int inity, int x, int y);
void promote(char board[8][8],char piece);
int isCheck(char board[8][8]);
int isCheckMate(char board[8][8]);
void notate();
//t
int main() {
  int input=0;
  printf("Welcome to \"C\"hess!\n \n");
  printf("What would you like to do?");
  while(input!=5) {
    printf("Chess Menu!\n1. Start a game\n5. Quit\n");
    scanf("%d",&input);
    switch(input) {
      case(1):
        printf("Starting a game!\n");
        char currboard[8][8];
        boardStandard(currboard);
        displayBoard(currboard);


    }
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

//Pre-conditions: Move is already confirmed valid
//Post-conditions: Deletes the piece from initial position and places it in final
void move(char board[8][8], int initx, int inity, int x, int y) {
  board[initx][inity] = "-";


}
//Preconditions: Board, initial x and y, and desired final location is passed
//returns 0 if impossible, returns 1 if possible
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
  //i hope this works.........
  for(int i=0;i<8;i++) {
    for(int j=0;j<2;j++) {
      if((x==possible[i])&&(y==possible[j]))
        flag=1;
    }
  }
  return flag;
}

int queen(char board[8][8], int initx, int inity, int x, int y) {
  int possible[]
  int flag=0;
  //if in same column or row it is a possible move
  if((initx==x)||(inity==y))
    flag=1;
  else {
    for(int i=initx,i<8;i++)
      for(int j=inity,i<8;j++)

  }



}
int king(char board[8][8], int initx, int inity, int x, int y) {
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
  for(int i=0;i<8;i++) {
    for(int j=0;j<8;j++) {
      if((x==possible[i])&&(y==possible[j]))
        flag=1;
      }
    }
  return flag;
}
int rook(char board[8][8], int initx, int inity, int x, int y) {
  int flag=0;
  if((initx == x)||(inity==y))
    flag=1;
  return flag;
}
int bishop(char board[8][8], int initx, int inity, int x, int y);
int pawn(char board[8][8], int initx, int inity, int x, int y);
