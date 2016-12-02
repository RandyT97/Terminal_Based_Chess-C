/*Randy Tsui
10/28/16
Chess.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define LENGTH 20

struct player{
  char fname[LENGTH];
  char lname[LENGTH];
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
void move(char board[8][8], int initx, int inity, int x, int y);
char promote();
int isCheck(char board[8][8]);
int isCheckMate(char board[8][8]);
void notate(int x, int y);
void playerMenu(FILE * ifp);
void updateProfiles(FILE * ifp,struct player base[20]);
void playStandard(struct player upperCase, struct player lowerCase);
//void printProfiles(FILE * ifp);
//void scanProfiles(FILE * ifp);
void createProfile(struct player base[20],int playercounter);
void loadProfiles(FILE * ifp,struct player base[20]);
void updateProfiles(FILE * ifp,struct player base[20]);
void printProfile(struct player base[20]);
int isEnd(char board[8][8]);
int findProfile(struct player base[20],char fname[20]);
int main() {
  int input=5;
  char fileexists;
  char path[70];
  FILE * ifp;
  printf("Are you importing an existing playerbase? Answer Y/N\n");
  scanf("%c",&fileexists);
  if(fileexists=='Y') {
    printf("What is the file path?\n");
    scanf("%s",path);
    ifp = fopen(path,"r");
  }
  else {
    ifp = fopen("chessplayers.txt","w+"); //new file created

  }
  printf("Welcome to \"C\"hess!\n \n");
  printf("What would you like to do?\n");
  playerMenu(ifp);

}
/*void scanProfiles(FILE * ifp) { //find a way to scan a file
  struct player entries[20];
  int c=0;
  while(fscanf(globalifp,"%s",fname)!=EOF) {
    fscanf(globalifp,"%s",entries[c].lname);
    fscanf(globalifp,"%d",entries[c].win);
    fscanf(globalifp,"%d",entries[c].loss);
    c++;
  }
}
void playerMenu(FILE * ifp) {
  int input=0;
  int playercounter=0;
  char capfname[20];
  char lowfname[20];
  struct player database[20];
  loadProfiles(ifp,database);
  for(int i=0;i<20;i++) {
    strcpy(database[i].fname,"_");
    strcpy(database[i].lname,"_");
    database[i].win = 0;
    database[i].loss = 0;
  }


  while(input!=4){
    printf("1. Start a standard game\n");
    printf("2. Create Player Profile\n");
    printf("3. Print Player Statistics\n");
    printf("4. Exit\n");
    scanf("%d",&input);
    switch(input) {
      case(1):
        printf("First name of the player in control of upper case pieces?\n");
        scanf("%s",capfname);
        printf("First name of the player in control of upper case pieces?\n");
        scanf("%s",lowfname);
        playStandard(database[findProfile(database,capfname)], database[findProfile(database,lowfname)]);
        break;
      case(2): {
        //createProfile(database,playercounter);
        //playercounter++;
        loadProfiles(ifp,database);
        updateProfiles(ifp,database);
        break;
        }
      case(3):
        printProfile(database);
      }
    }
}
void loadProfiles(FILE * ifp,struct player base[20]) {
  for(int i=0;i<20;i++) {
    fscanf(ifp,"%s",base[i].fname);
    fscanf(ifp,"%s",base[i].lname);
    fscanf(ifp,"%d",base[i].win);
    fscanf(ifp,"%d",base[i].loss);
  }
}
void updateProfiles(FILE * ifp,struct player base[20]) {
    char fname[20];
    char lname[20];
    int win=0;
    int loss=0;
    printf("Please type your first and last name.\n");
    scanf("%s",fname);
    scanf("%s",lname);
    fprintf(ifp,"\n%s\t",fname);
    fprintf(ifp,"%s\t",lname);
    fprintf(ifp,"%d\t",win);
    fprintf(ifp,"%d\t \n",loss);
}
/*void createProfile(struct player base[20],int playercounter) {
  char fname[LENGTH];
  char lname[LENGTH];

  printf("~~~~~~%d",playercounter);
  printf("Please input first name\n");
  scanf("%s",base[playercounter].fname);

  printf("Please input last name\n");
  scanf("%s",base[playercounter].lname);
}*/
void printProfile(struct player base[20]) {
  for(int i=0;i<20;i++) {
    printf("Firstname:%s\tLastname:%s\tWins:%d\tLosses:%d\t\n",base[i].fname,base[i].lname,base[i].win,base[i].loss);
  }
}
int findProfile(struct player base[20],char fname[20]) {
  int index;
  for(int i=0;i<20;i++) {
    if(strcmp(base[i].fname,fname)==0)
      index = i;
  }
  return index;
}
int isEnd(char board[8][8]) {
  int lowerKingAlive=0;
  int upperKingAlive=0;
  for(int i=0;i<8;i++) {
    for(int j=8;j<8;j++) {
      if(board[i][j]=='K')
        lowerKingAlive=1;
      if(board[i][j]=='k')
        upperKingAlive=1;
    }
  }
  if(!lowerKingAlive) {
    printf("Game is over, upper case won!\n");
    return 1;
  }
  if(!upperKingAlive) {
    printf("Game is over, lower case won!\n");
    return 2;
  }
  return 0;
}
// STANDARD BOARD MATERIALS
void playStandard(struct player upperCase, struct player lowerCase) {//DEPENDS ON PRINTOUT LOCATIONS!!!
  int game = 1;
  int initialx;
  int initialy;
  int finalx;
  int finaly;
  char standardboard[8][8];
  boardStandard(standardboard);
  while(game==1) {
    displayBoard(standardboard);
    printf("Enter the location of your piece.\n");
    scanf("%d",&initialx); //Depends on how location is prented
    scanf("%d",&initialy); //^^
    printf("Enter the final location\n");
    scanf("%d",&finalx);
    scanf("%d",&finaly);
    move(standardboard, initialx, initialy, finalx, finaly);
    if(isEnd(standardboard)!=0) {
      if(isEnd(standardboard)==1) {
        upperCase.win+=1;
        game=0;
      }
      else{
        lowerCase.win+=1;
        game=0;
      }
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
    printf("[%d]\t",abs(i));
    for(int j=0;j<8;j++) {
      printf("%c\t",board[i][j]);
    }
    printf("\n\n");
  }
  printf("\t[0]\t[1]\t[2]\t[3]\t[4]\t[5]\t[6]\t[7]\n");
}

//Pre-conditions:
//Post-conditions: Deletes the piece from initial position and places it in final
void move(char board[8][8], int initx, int inity, int x, int y) {
  char piece = board[initx][inity];
  printf("%c!!!!!!\n",piece); //TEST REMOVE
  int flag=0;
  int flag1=0;
  switch(piece) {
    case('n'):
    case('N'):
    {
      flag = knight(board,initx,inity,x,y);
      break;
    }
    case('q'):
    case('Q'):
    {
      flag = queen(board,initx,inity,x,y);
      break;
    }
    case('k'):
    case('K'):
    {
      flag = king(board,initx,inity,x,y);
      break;
    }
    case('r'):
    case('R'):
    {
      flag = rook(board,initx,inity,x,y);
      break;
    }
    case('b'):
    case('B'):
    {
      flag = bishop(board,initx,inity,x,y);
    }
    case('p'):
    case('P'):
    {
      flag = pawn(board,initx,inity,x,y);
      if((x==7)||(x==0))
        piece = promote();
      break;
    }
  }
  if(flag) {
    board[initx][inity]='-';
    board[x][y]=piece;
  }
      else
        printf("Move is invalid, please try again.\n");

}

char promote() {//may be an issue, case sensitive?
  char piece;
  printf("What piece would you like to promote to?\n");
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
    int possibleP[4][2] = {
      {initx-1,inity},
      {initx-2,inity},
      {initx-1,inity+1},
      {initx-1,inity-1},
    };
      //Search loop is functional
    for(int i=0;i<3;i++) {
        if((x==possibleP[i][0])&&(y==possibleP[i][1]))
          flag=1;
    }
  }
  else {
    int possibleP[4][2] = {
      {initx+1,inity},
      {initx+2,inity},
      {initx+1,inity+1},
      {initx+1,inity-1},
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
