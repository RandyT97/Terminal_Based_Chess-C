/*Randy Tsui
10/28/16
Chess.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define LENGTH 20
#define structLength 50


FILE * globalifp;
int profilecounter=0;
char globalfilename[70];


struct player{
  char fname[LENGTH];
  char lname[LENGTH];
  int win;
  int loss;
};

void boardStandard(char board[8][8]);
void displayBoard(char board[8][8]);
void playStandard(struct player upperCase, struct player lowerCase);

int knight(char board[8][8], int initx, int inity, int x, int y);
int queen(char board[8][8], int initx, int inity, int x, int y);
int king(char board[8][8], int initx, int inity, int x, int y);
int rook(char board[8][8], int initx, int inity, int x, int y);
int bishop(char board[8][8], int initx, int inity, int x, int y);
int pawn(char board[8][8], int initx, int inity, int x, int y);
void move(char board[8][8], int initx, int inity, int x, int y);
char promote();

void playerMenu();

void recordLookup(struct player base[structLength]);
int findProfile(struct player base[structLength],char fname[LENGTH]);
void updateProfiles(struct player base[structLength]);
void scanProfiles(struct player entries[structLength]);
void createProfile(struct player base[structLength]);
void fileprintProfiles(struct player base[structLength]);
void printProfile(struct player base[structLength]);

int isEnd(char board[8][8]);

void initializeEmpty(struct player newbase[structLength]);
int main() {
  int input=5;
  char fileexists;
  char path[70];
  printf("Are you importing an existing playerbase? Answer Y/N\n");
  scanf("%c",&fileexists);
  if(fileexists=='Y') {
    printf("What is the file path?\n");
    scanf("%s",path);
    globalifp = fopen(path,"r");
  }
  else {
    strcpy(path,"chessplayers.txt");
    globalifp = fopen("chessplayers.txt","w+"); //new file created

  }
  strcpy(globalfilename,path);
  printf("Welcome to \"C\"hess!\n \n");
  printf("What would you like to do?\n");
  playerMenu(globalifp);

}
//player menu
void playerMenu() {
  int input=0;
  int playercounter=0;
  char capfname[LENGTH];
  char lowfname[LENGTH];
  struct player database[structLength];

  initializeEmpty(database);
  scanProfiles(database);

  while(input!=5){
    fileprintProfiles(database);

    printf("1. Start a standard game\n");
    printf("2. Create Player Profile\n");
    printf("3. Print Player Statistics\n");
    printf("4. Record Lookup\n");
    printf("5. Quit Game\n");
    scanf("%d",&input);

    switch(input) {

      case(1):
        printf("First name of the player in control of upper case pieces?\n");
        scanf("%s",capfname);
        printf("First name of the player in control of lower case pieces?\n");
        scanf("%s",lowfname);
        playStandard(database[findProfile(database,capfname)], database[findProfile(database,lowfname)]);
        break;

      case(2):
        createProfile(database);
        break;

      case(3):
        printProfile(database);
        break;

      case(4):
        recordLookup(database);
        break;
      }
    }
}
//Default initializes player array
void initializeEmpty(struct player newbase[structLength]) {
  for(int i=0;i<structLength;i++) {
    strcpy(newbase[i].fname," ");
    strcpy(newbase[i].lname," ");
    newbase[i].win=0;
    newbase[i].loss=0;
  }
}
//Create a profile, prompts for first and last name
void createProfile(struct player base[structLength]) {

  printf("What is your first name?\n");
  scanf("%s",base[profilecounter].fname);
  printf("What is your last name?\n");
  scanf("%s",base[profilecounter].lname);

  base[profilecounter].win=0;
  base[profilecounter].loss=0;
  profilecounter++;
}
//Prints the current player array to the file pointed by the global file var globalifp
void fileprintProfiles(struct player base[structLength]) { //code can be recycled to update file
  globalifp = fopen(globalfilename,"w+");

  for(int i=0;i<structLength;i++){
    fprintf(globalifp,"\n%s\t",base[i].fname);
    fprintf(globalifp,"%s\t",base[i].lname);
    fprintf(globalifp,"%d\t",base[i].win);
    fprintf(globalifp,"%d\t \n",base[i].loss);
  }
}
//Scans file into player structure
void scanProfiles(struct player entries[structLength]) { //find a way to scan a file
  while(fscanf(globalifp,"%s",entries[profilecounter].fname)!=EOF) {
    fscanf(globalifp,"%s",entries[profilecounter].lname);
    fscanf(globalifp,"%d",&entries[profilecounter].win);
    fscanf(globalifp,"%d",&entries[profilecounter].loss);
    profilecounter++;
  }
}
//prints all profiles to terminal
void printProfile(struct player base[structLength]) {
  for(int i=0;i<structLength;i++) {
    printf("Firstname:%s\tLastname:%s\tWins:%d\tLosses:%d\t\n",base[i].fname,base[i].lname,base[i].win,base[i].loss);
  }
}
//given first name finds index
int findProfile(struct player base[structLength],char fname[LENGTH]) {
  int index;

  for(int i=0;i<structLength;i++) {
    if(strcmp(base[i].fname,fname)==0)
      index = i;
  }
  return index;
}
void recordLookup(struct player base[structLength]) {
  char name[LENGTH];
  int flag=0;

  printf("What is the first name of the player you are looking for?\n");
  scanf("%s",name);

  for(int i=0;i<structLength;i++) {
    if(strcmp(base[i].fname,name)==0) {
      printf("Wins: %d\tLosses: %d\n",base[i].win,base[i].loss);
      flag=1;
    }
  }
  if(!flag)
    printf("Player does not exist or name is spelt wrong **CASE SENSITIVE**");
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
//Pre-Conditions: Two player structs
//Post-Conditions: Adds a win to the winner and a loss to the loser
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
        lowerCase.loss+=1;
        game=0;
      }
      else{
        lowerCase.win+=1;
        upperCase.loss+=1;
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
//returns char representation of intended piece from user
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
  return flag;
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
