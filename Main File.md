# Minesweeper
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include "funcF.h"

/*Global variables*/
long long r,a,c,b,numberOfMines,remainingFlags,usedFlags=0,usedNotSure=0,numberOfMoves=0,totalTime=0,timeTemp=0;
int g;
/*score sheet structure*/
struct users{
    char name[100];
    double score;
};
/*saving files*/
FILE *sf,*sf2,*ss;
/*functions declaration*/
void printGrid(char grid[r][c],long long startTime,long long moveTime);
void timer(long long startTime, long long moveTime);
void mines_Array(long long rowNumber,long long columnNumber,int minesArray[r][c]);
void open(char grid[r][c],int minesArray[r][c],long long coordinate1,long long coordinate2);
long long winCheck(char grid[r][c],long long loopCouter,long long r,long long c);
void winGrid(char grid[r][c],long long r,long long c);
void save(void);
void loadvar(void);
void loadarray(char grid[r][c],int minesArray[r][c]);
void saveArray(char grid[r][c],int minesArray[r][c]);
int compare(char savedName[100],char newName[100]);
void scoreSheet(double userScore);
/*main function*/
int main(){
    system("COLOR 0A"); /*changes console screen color.First char is the background,second is the font color*/
    MineSweeper();
    g=getG();
    clrscr(); /*cleans console screen*/
    if(g==3){ /*if user presses 3 for score board*/
        printf("                => Score Board <=\n\n");
        int k=0,i,j;
        double t;
        char temp[100];
        struct users l[100];
        ss = fopen("ScoreSheet.txt","rb"); /*loading names with scores from score sheet file*/
        fread(&k,1,1,ss);
        for(i=0; i<k; i++){
            fread(&l[i], sizeof(struct users), 1, ss);
        }
        fclose(ss);
        /*arrange the names in descending order by scores*/
        for (i=0;i<k;i++){
            for (j=i+1;j<k;j++){
                if (l[i].score < l[j].score){
                    t = l[i].score; /*swap the score*/
                    l[i].score = l[j].score;
                    l[j].score = t;
                    strcpy(temp,l[i].name); /*swap the name*/
                    strcpy(l[i].name,l[j].name);
                    strcpy(l[j].name,temp);
                }
            }
        } /*printing the score board*/
        printf("\n\n| R |      score        |        Name\n----------------------------------------------------------");
        for (i=0;i<k;i++){
            printf("\n|%03d|     %08.0lf      |      %s",i+1,l[i].score,l[i].name);
        }
        printf("\n\n\n\n\n                           1-New Game   2-Load Game\n");
        printf("\n\n                               Select Option:");
        g=getG1(); /*get the option number,new game or load game*/
    }
    if(g==1){ /*if user presses 1 for new game*/
        printf("Enter number of rows: ");
        r=getGrid(); /*get number of rows of the grid*/
        printf("Enter number of columns: ");
        c=getGrid(); /*get number of columns of the grid*/
        clrscr();
    }
    else if (g==2){ /*if user presses 2 for load game*/
        loadvar(); /*load variables*/
        timeTemp=totalTime; /*saved game time to add to the time after loading*/
    }
    a=r;
    b=c;
    int minesArray[r][c];
    char grid[r][c];
    numberOfMines=1+(r*c)/10; /*formula for the number of mines in grid according to r&c */
    if(g==1){
        remainingFlags=numberOfMines; /*initializing number of flags could be used*/
    }
    if(g==1){ /*printing the closed grid before doing the first move*/
        printf("Moves: %lld Flags: %lld Used flags: %lld Used not sure: %lld Time: 00:00\n\n",numberOfMoves,remainingFlags,usedFlags,usedNotSure);
        int i,j,k;
        for(i=0; i<=r; i++){
            for(j=0; j<=c; j++){
                grid[i][j]='X';
            }
        }
        for(i=0; i<r; i++){
            for(j=0; j<c; j++){
                if(c>=10){
                    printf(" %c | ",grid[i][j]);
                }
                else{
                    printf(" %c |",grid[i][j]);
                }
            }
            printf(" %d",i+1);
            printf("\n");
            if(c<10){
                for(k=0; k<4*c+3; k++){
                    printf("-");
                }
            }
            else{
                for(k=0; k<8+5*(c-1); k++){
                    printf("-");
                }
            }
            printf("\n");
        }
        for(i=1; i<=c; i++){
            if(c<10){
                printf(" %d |",i);
            }
            if(c>=10){
                if(i<10){
                    printf(" %d | ",i);
                }
                else{
                    printf("%d | ",i);
                }
            }
        }
        printf(" o");
        printf(" ");
    }
    else if (g==2){ /*printing saved game grid to continue playing*/
        loadarray(grid,minesArray);
        printGrid(grid,1,1);
    }
    long long loopCounter=1; /*flag that determine if the game comes to an end or still in progress*/
    time_t startTime=time(NULL); /*storing the time when starting the game*/
    while(loopCounter){
        long long rowNumber,columnNumber;
        do{ /*get coordinates of the cell the user want to do action on it*/
            printf("\n\nEnter appropriate Row number: ");
            rowNumber=getCoordinates();
        }while(rowNumber>r);
        do{
            printf("\nEnter appropriate Column number: ");
            columnNumber=getCoordinates();
        }while(columnNumber>c);
        printf("Options: 1-Open 2-Flag 3-Not sure 4-Unmark 5-Save & Exit"); /*displaying options*/
        printf("\nEnter option number: ");
        int option;
        option=getOption(); /*get option number*/
        if(loopCounter==1 && g==1){ /*generating hidden array that contains hidden content that appears when user open its cell*/
            mines_Array(rowNumber,columnNumber,minesArray);
        }
        numberOfMoves++; /*number of moves increases by 1 after every action */
        switch(option){
        case 1 : /*if user pressed 1 for open cell*/
            if(grid[rowNumber-1][columnNumber-1]!='F'){
                if(minesArray[rowNumber-1][columnNumber-1]==0){
                    minesArray[rowNumber-1][columnNumber-1]=-1;
                    open(grid,minesArray,rowNumber,columnNumber);
                    grid[rowNumber-1][columnNumber-1] = ' ';
                    break;
                }
                else if(minesArray[rowNumber-1][columnNumber-1]==42){
                    grid[rowNumber-1][columnNumber-1] = '*';
                    loopCounter=-1;
                }
                else if(grid[rowNumber-1][columnNumber-1]!='X' && grid[rowNumber-1][columnNumber-1]!='F' && grid[rowNumber-1][columnNumber-1]!='?'){
                    long long x=rowNumber-1,y=columnNumber-1;
                    int i,j,temp=0;
                    for(i=x-1; i<=x+1; i++){
                        if((i<r) && (i>=0)){
                            for(j=y-1; j<=y+1; j++){
                                if((j<c) && (j>=0)){
                                    if((i!=x)||(j!=y)){
                                        if (grid[i][j]=='F'){
                                            temp++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if(temp==minesArray[x][y]){
                        for(i=x-1; i<=x+1; i++){
                            if((i<r) && (i>=0)){
                                for(j=y-1; j<=y+1; j++){
                                    if((j<c) && (j>=0)){
                                        if(((i!=x)||(j!=y)) && (grid[i][j]!='F') && (grid[i][j]!='?')){
                                            if(minesArray[i][j]==0){
                                                minesArray[i][j]=-1;
                                                open(grid,minesArray,i+1,j+1);
                                                grid[i][j]=' ';
                                            }
                                            else{
                                                switch(minesArray[i][j]){
                                                case 1:
                                                    grid[i][j]=49;
                                                    break;
                                                case 2:
                                                    grid[i][j]=50;
                                                    break;
                                                case 3:
                                                    grid[i][j]=51;
                                                    break;
                                                case 4:
                                                    grid[i][j]=52;
                                                    break;
                                                case 5:
                                                    grid[i][j]=53;
                                                    break;
                                                case 6:
                                                    grid[i][j]=54;
                                                    break;
                                                case 7:
                                                    grid[i][j]=55;
                                                    break;
                                                case 8:
                                                    grid[i][j]=56;
                                                    break;
                                                case 42:
                                                    grid[i][j]='*';
                                                    loopCounter = -1;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else{
                    switch(minesArray[rowNumber-1][columnNumber-1]){
                    case 1:
                        grid[rowNumber-1][columnNumber-1]=49;
                        break;
                    case 2:
                        grid[rowNumber-1][columnNumber-1]=50;
                        break;
                    case 3:
                        grid[rowNumber-1][columnNumber-1]=51;
                        break;
                    case 4:
                        grid[rowNumber-1][columnNumber-1]=52;
                        break;
                    case 5:
                        grid[rowNumber-1][columnNumber-1]=53;
                        break;
                    case 6:
                        grid[rowNumber-1][columnNumber-1]=54;
                        break;
                    case 7:
                        grid[rowNumber-1][columnNumber-1]=55;
                        break;
                    case 8:
                        grid[rowNumber-1][columnNumber-1]=56;
                        break;
                    }
                }
            }
            break;
        case 2: /*if user pressed 2 for putting flag in a cell*/
            if(remainingFlags>0){
                if(grid[rowNumber-1][columnNumber-1]=='X'){
                    grid[rowNumber-1][columnNumber-1]='F';
                    remainingFlags--;
                    usedFlags++;
                }
            }
            break;
        case 3: /*if user pressed 3 for putting question mark in a cell*/
            if(grid[rowNumber-1][columnNumber-1]=='X'){
                grid[rowNumber-1][columnNumber-1]='?';
                usedNotSure++;
            }
            break;
        case 4: /*if user pressed 4 for unmarking a cell*/
            if(grid[rowNumber-1][columnNumber-1]=='F'){
                grid[rowNumber-1][columnNumber-1]='X';
                remainingFlags++;
                usedFlags--;
            }
            else if(grid[rowNumber-1][columnNumber-1]=='?'){
                grid[rowNumber-1][columnNumber-1]='X';
                usedNotSure--;
            }
            break;
        case 5: /*if user pressed 5 to save current progress and exit the game*/
            save();
            saveArray(grid,minesArray);
            exit(0);
        }
        printf("\n");
        time_t moveTime=time(NULL); /*storing the time after every move*/
        loopCounter = winCheck(grid,loopCounter,r,c); /*check if the user wins*/
        if(loopCounter == -1){ /*if user opened cell containing mine*/
            int q,w;
            for(q=0; q<r; q++){
                for(w=0; w<c; w++){
                    if(grid[q][w]=='*'){
                        grid[q][w]='!';
                    }
                    else if(grid[q][w]=='F'){
                        if(minesArray[q][w]==42){
                            grid[q][w]='*';
                        }
                        else{
                            grid[q][w]='-';
                        }
                    }
                    else if (minesArray[q][w]==42)
                        grid[q][w]= 'M';
                }
            }
            printGrid(grid,startTime,moveTime);
            printf("\n\n                 You Lose !\n\n");
            char zzz;
            printf("                 Press any key then Enter to exit ");
            scanf(" %c",&zzz);
        }
        else if(loopCounter == -2){ /*if user wins*/
            winGrid(grid,r,c);
            double finishTime=moveTime-startTime+1; /*adding 1 to finish time is here to make sure time is not 0*/
            long long score1=(r*r*r*r*c*c*c*c)/(finishTime*numberOfMoves); /*calculating score*/
            printGrid(grid,startTime,moveTime);
            printf("\n\nYou Win !\nYour score is %lld\n\n",score1);
            scoreSheet(score1); /*save the winner name and his score*/
            loopCounter=-1;
        }
        else{ /*continue for next move*/
            printGrid(grid,startTime,moveTime);
        }
        loopCounter++;
    }
    return 0;
}/*end main*/
/*functions declaration*/
void printGrid(char grid[a][b],long long startTime,long long moveTime){
    clrscr();
    if(g==2){
        numberOfMoves--;
        g=-1;
    }
    printf("Moves: %lld Flags: %lld Used flags: %lld Used not sure: %lld Time: ",numberOfMoves,remainingFlags,usedFlags,usedNotSure);
    timer(startTime,moveTime+1);
    printf("\n\n");
    int i,j,k;
    for(i=0; i<a; i++){
        for(j=0; j<b; j++){
            if(b>=10){
                printf(" %c | ",grid[i][j]);
            }
            else{
                printf(" %c |",grid[i][j]);
            }
        }
        printf(" %d",i+1);
        printf("\n");
        if(c<10){
            for(k=0; k<4*c+3; k++){
                printf("-");
            }
        }
        else{
            for(k=0; k<8+5*(c-1); k++){
                printf("-");
            }
        }
        printf("\n");
    }
    for(i=1; i<=b; i++){
        if(b<10){
            printf(" %d |",i);
        }
        if(b>=10){
            if(i<10){
                printf(" %d | ",i);
            }
            else{
                printf("%d | ",i);
            }
        }
    }
    printf(" o");
    printf(" ");
}

void timer(long long startTime, long long moveTime){
    totalTime = timeTemp + moveTime - startTime;
    long long  minute = totalTime / 60;
    long long second = totalTime % 60;
    printf("%.2lld:%.2lld",minute,second);
}

void mines_Array(long long rowNumber,long long columnNumber,int minesArray[r][c]){
    srand(time(NULL));
    int random1,random2;
    int x,y,i,j,z=0,temp,numberOfMines=1+(r*c)/10;
    while(z<numberOfMines){
        random1=rand();
        x=random1%r;
        random2=rand();
        y=random2%c;
        if((x!=rowNumber-1) || (y!=columnNumber-1)){
            if(minesArray[x][y]!=42){
                minesArray[x][y]=42;
                z++;
            }
        }
    }
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            temp=0;
            if(minesArray[i][j]!=42){
                if(((i+1)<r && (i+1)>=0) && ((j)<c && (j)>=0)){
                    if(minesArray[i+1][j]==42){
                        temp++;
                    }
                }
                if(((i+1)<r && (i+1)>=0) && ((j+1)<c && (j+1)>=0)){
                    if(minesArray[i+1][j+1]==42){
                        temp++;
                    }
                }
                if(((i+1)<r && (i+1)>=0) && ((j-1)<c && (j-1)>=0)){
                    if(minesArray[i+1][j-1]==42){
                        temp++;
                    }
                }
                if(((i)<r && (i)>=0) && ((j-1)<c && (j-1)>=0)){
                    if(minesArray[i][j-1]==42){
                        temp++;
                    }
                }
                if(((i-1)<r && (i-1)>=0) && ((j-1)<c && (j-1)>=0)){
                    if(minesArray[i-1][j-1]==42){
                        temp++;
                    }
                }
                if(((i-1)<r && (i-1)>=0) && ((j)<c && (j)>=0)){
                    if(minesArray[i-1][j]==42){
                        temp++;
                    }
                }
                if(((i-1)<r && (i-1)>=0) && ((j+1)<c && (j+1)>=0)){
                    if(minesArray[i-1][j+1]==42){
                        temp++;
                    }
                }
                if(((i)<r && (i)>=0) && ((j+1)<c && (j+1)>=0)){
                    if(minesArray[i][j+1]==42){
                        temp++;
                    }
                }
                minesArray[i][j]=temp;
            }
        }
    }
}


void open(char grid[r][c],int minesArray[r][c],long long coordinate1,long long coordinate2){
    long long x,y;
    x=coordinate1-1;
    y=coordinate2-1;
    if (minesArray[x][y]>=1 && minesArray[x][y]<=8){
        return;
    }
    int i,j;
    for(i=x-1; i<=x+1; i++){
        if((i<r) && (i>=0)){
            for(j=y-1; j<=y+1; j++){
                if((j<c) && (j>=0)){
                    if(((i!=x)||(j!=y)) && ((grid[i][j]!='F') && (grid[i][j]!='?'))){
                        if (minesArray[i][j]==0){
                            grid[i][j]=' ';
                            minesArray[i][j]=-1;
                            open(grid,minesArray,i+1,j+1);
                        }
                        else{
                            switch(minesArray[i][j]){
                            case 1:
                                grid[i][j]=49;
                                break;
                            case 2:
                                grid[i][j]=50;
                                break;
                            case 3:
                                grid[i][j]=51;
                                break;
                            case 4:
                                grid[i][j]=52;
                                break;
                            case 5:
                                grid[i][j]=53;
                                break;
                            case 6:
                                grid[i][j]=54;
                                break;
                            case 7:
                                grid[i][j]=55;
                                break;
                            case 8:
                                grid[i][j]=56;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}


long long  winCheck(char grid[r][c],long long loopCouter,long long r,long long c){
    int i,j,k=0;
    long long n = r*c - numberOfMines;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            if (grid[i][j]!='X' && grid[i][j]!='F' && grid[i][j]!='?' && grid[i][j]!='*'){
                k++;
            }
        }
    }
    if (k==n){
        return -2;
    }
    else{
        return loopCouter;
    }
}
void winGrid(char grid[r][c],long long r,long long c){
    int i,j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            if(grid[i][j]=='X'){
                grid[i][j]='F';
            }
        }
    }
}
void save(){
    sf = fopen("saveFile.txt","wb");
    fwrite(&r,1, 1,sf);
    fwrite(&c,1, 1,sf);
    fwrite(&numberOfMoves,1,1,sf);
    fwrite(&usedFlags,1,1,sf);
    fwrite(&remainingFlags,1,1,sf);
    fwrite(&usedNotSure,1,1,sf);
    fwrite(&totalTime,1,1,sf);
    fclose(sf);
}


void saveArray(char grid[r][c],int minesArray[r][c]){
    sf2 = fopen("saveFile2.txt","wb");
    int n,l;
    for (n = 0; n < r; n++){
        for(l=0; l<c; l++){
            fwrite(&grid[n][l], 1, 1, sf2);
            fwrite(&minesArray[n][l], 1, 10, sf2);
        }
    }
    fclose(sf2);
}
void loadvar(){
    sf = fopen("saveFile.txt","rb");
    fread(&r,1, 1,sf);
    fread(&c,1, 1,sf);
    fread(&numberOfMoves,1,1,sf);
    fread(&usedFlags,1,1,sf);
    fread(&remainingFlags,1,1,sf);
    fread(&usedNotSure,1,1,sf);
    fread(&totalTime,1,1,sf);
    fclose(sf);
}
void loadarray(char grid[r][c],int minesArray[r][c]){
    sf2 = fopen("saveFile2.txt","rb");
    int n,l;
    for (n = 0; n < r; n++){
        for(l=0; l<c; l++){
            fread(&grid[n][l], 1, 1, sf2);
            fread(&minesArray[n][l], 1, 10, sf2);
        }
    }
    fclose(sf2);
}

int compare(char savedName[100],char newName[100]){
    int i;
    char n1[100], n2[100];
    strcpy(n1,savedName);
    strcpy(n2,newName);
    if (strlen(n1)!=strlen(n2)) return 0;
    for(i=0; i<strlen(n2); i++)
    {
        n2[i]=toupper(n2[i]);
        n1[i]=toupper(n1[i]);
    }
    i = strcmp(n2,n1);
    if (i==0) return 1;
    else return 0;
}
void scoreSheet (double userScore){
    int i,j=0,k=0;
    FILE *ss;
    struct users l[100];
    ss = fopen("ScoreSheet.txt","rb");
    fread(&k,1,1,ss);
    for(i=0; i<k; i++){
        fread(&l[i], sizeof(struct users), 1, ss);
    }
    fclose(ss);
    char userName[100];
    printf("\nEnter your name ,winner! : ");
    gets(userName);
    for(i=0; i<100; i++){
        if (l[i].score == 0) break;
        if (compare(l[i].name,userName)){
            l[i].score = l[i].score + userScore;
            j =1;
        }
    }
    if(j==0){
        k=i+1;
        strcpy(l[i].name,userName);
        l[i].score=userScore;
    }
    ss = fopen("ScoreSheet.txt","wb");
    fwrite(&k,1,1,ss);
    for(i=0; i<k; i++){
        fwrite(&l[i], sizeof(struct users), 1, ss);
    }
    fclose(ss);
}

