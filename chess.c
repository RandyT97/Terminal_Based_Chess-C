/*Randy Tsui
10/28/16
Chess.c
*/
#include <stdio.h>
#include <stdlib.h>
void board(char board[8][8]);
void displayBoard(char board[8][8]);
void knight(int x,int y);
void queen(int x,int y);
void king(int x,int y);
void rook(int x,int y);
void bishop(int x,int y);
void pawn(int x,int y);


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
        board(currboard);
        displayBoard(currboard);


    }
  }


}

//Populates board
void board(char board[8][8]) {
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
