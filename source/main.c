#include<stdio.h>
#include<string.h>

#define line 8                                                          /*defining array lines of numbers*/
#define colomn 8                                                        /*defining array colomn of numbers*/

char white[6]={'k','q','r','b','n','p'};
char black[6]={'K','Q','R','B','N','P'};
char stones[12]={'k','q','r','b','n','p','K','Q','R','B','N','P'};
char letter[8]={'a','b','c','d','e','f','g','h'};
int chess[55];                     /*this array is used for determine stones' movements than is used move and showmoves functions */
char chessboard [line] [colomn];

void place(char chessboard[][colomn], int, int);                                     /*defining functions*/
void clear(char chessboard[][colomn], int, int);
void print(char chessboard[][colomn], int, int);
void move(char chessboard[][colomn], int , int);
void showmoves(char chessboard[][colomn] , int, int);

void king(int , int , char);
void queen(int, int, char);
void bishop(int, int, int, char);
int rook(int, int, char);
void knight(int ,int, char);
void pawn(int , int ,char );

int test_stone(int, int, int, char);
void sort(int chess[],int );
int knight_control(int ,int ,int ,int ,int, char);
void pawn_control(int ,int , char );

int main()
{
    char menu[10];                                                                      /*for determining which process will do*/
clear(chessboard,line,colomn);                                                          /*for first empty board*/
do
  {
    scanf("%s" ,menu);

    if(strcmp("place",menu)==0)
                  {
                   place(chessboard,line,colomn);                                       /*given a new position*/
                  }
    else if(strcmp("move",menu)==0)
                  {
                   move(chessboard,line,colomn);                                        /*move another peace*/
                  }
    else if (strcmp("showmoves",menu)==0)
                  {
                   showmoves(chessboard,line,colomn);                                   /*show stone of movement can*/
                  }
    else if(strcmp("print",menu)==0)
                  {
                   print(chessboard,line,colomn);                                       /*show chessboard*/
                  }
    else if(strcmp("clear",menu)==0)
                  {
                   clear(chessboard,line,colomn);                                       /*clear chessboard*/
                  }
  }
while(strcmp("exit" , menu)!=0);                                                        /*exit program*/
return 0;
}
void place(char chessboard[][colomn],int f,int g)
{
    char kind;                                                                           /*for kind of stone*/
    char letter;                                                                         /*for colomn*/
    int number;                                                                          /*for line number*/
    int j;                                                                               /*for loop*/

    scanf(" %c%d %c" ,&letter,&number,&kind);

    int number_letter=letter-'a';                                                         /*determine colomn number*/

    for (j=0;j<12;j++)                                                                    /*determining kind of stone*/
    {
        if(stones[j]==kind)
        break;
    }                                   /*if entered variables conforms to the requirements,stone given positions */
        if (number_letter>7 || j==12 || number>8 || chessboard[8-number][number_letter]!=' ')
            printf("FAILED\n");
        else
        {
            chessboard[8-number][number_letter]=kind;
            printf("OK\n");
        }
}
void clear(char chessboard[][colomn],int f,int g)
{
    int i,j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        chessboard[i][j]=' ';
    }
}
void print(char chessboard[][colomn],int f,int g)
{
    int i,j;
    for (i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("%c", chessboard[i][j]);
        }
    printf("\n");
    }
}
void move (char chessboard[][colomn],int f,int g)
{
int number1,number2;                                                              /*row variables*/
char letter1,letter2;                                                             /*column variables*/
int i;                                                                            /*for loops*/
int n;
char stone,colour;

scanf(" %c%d %c%d" ,&letter1,&number1,&letter2,&number2);

int number_letter1=letter1-'a';                                                   /*determining number of letter1*/
int number_letter2=letter2-'a';                                                   /*determining number of letter2*/
stone=chessboard[8-number1][number_letter1];                                      /*determining which stone exist first location*/

for(i=0;i<12;i++)                                                                 /*finding variable colour and kind*/
{
   if(stones[i]==stone)
    break;
}

if(i<6)                                                                           /*determining colour of stone*/
    colour='w';
else
    colour='b';

if(i==0 || i==6)                                                                  /*according to kind, calling function*/
    king(number1,number_letter1,colour);
else if(i==1 || i==7)
    queen(number1,number_letter1,colour);
else if(i==2 || i==8)
    rook(number1,number_letter1,colour);
else if(i==3 || i==9)
    bishop(number1,number_letter1,n=0,colour);
else if(i==4 || i==10)
    knight(number1,number_letter1,colour);
else if(i==5 || i==11)
    pawn(number1,number_letter1,colour);
                            /*if entered variables conforms to the requirements,stone move another peace */
if (number_letter1<8 && number_letter2<8 && number1<9 && number2<9)
    {
        for(i=0;chess[i]!=-1;i+=2)
        {
            if(chess[i]==number_letter2 && chess[i+1]==number2)
            {
                chessboard[8-number2][number_letter2]=chessboard[8-number1][number_letter1];
                chessboard[8-number1][number_letter1]=' ';
                printf("OK\n");
                break;
            }
        }
    }
else
    printf("FAILED\n");
}
void showmoves(char chessboard[][colomn],int f,int g)
{
    char letter1;                                                                 /*variable of letters */
    char colour;
    int number;                                                                  /*variable of numbers*/
    int i;                                                                       /*for loops*/
    int t,n;

    for(i=0;i<55;i++)                                          /*the appointment of the first value in a array of chess*/
        chess[i]=-1;

    scanf(" %c%d" ,&letter1,&number);

    int number_letter=letter1-'a';                                                /*determinin number of letter*/

    char a=chessboard[8-number][number_letter];                                  /*determining stone at location*/

    if(number_letter<9 && number<9 && chessboard[8-number][number_letter]!=' ')  /*testing entered right variable*/
    {
          for(i=0;i<12;i++)                                                      /*finding variable colour and kind */
        {
            if(stones[i]==a)
            break;
        }
        if(i<6)                                                                  /*determining colour of stone*/
            colour='w';
        else
            colour='b';
    }
    else
        printf("FAILED");

if(i==0 || i==6)                                                                  /*according to kind, calling function*/
king(number,number_letter,colour);
else if(i==1 || i==7)
queen(number,number_letter,colour);
else if(i==2 || i==8)
rook(number,number_letter,colour);
else if(i==3 || i==9)
bishop(number,number_letter,n=0,colour);
else if(i==4 || i==10)
knight(number,number_letter,colour);
else if(i==5 || i==11)
pawn(number,number_letter,colour);

for(i=0;chess[i]!=-1;i+=2)                                                      /*showing movements of the stone can*/
{
    t=chess[i];                                                                 /*to show letter of location*/
    printf("%c%d " , letter[t], chess[i+1]);
}
printf("\n");
}
void king(int c,int j,char colour)                                               /*for determine king's showmoves*/
{
    int hide1,hide2;                    /*I start the loop from one more than the variable because of king's movement*/
    int n=0;
    hide1=j+1;                                                                    /*for hide number of letters*/
    hide2=c+1;                                                                    /*for hide numbers*/

    while(hide2>c-2 && hide2>=0)
    {
        while(hide1>j-2 && hide1>=0)
        {
            if(hide1>7)
            hide1=j;

            if(hide1==j && hide2==c)
            hide1=j-1;

            if(chessboard[8-hide2][hide1]==' ')
                {
                chess[n]=hide1;
                chess[n+1]=hide2;
                n+=2;
                }
            else
                {
                n=test_stone(n,hide2,hide1,colour);                      /*testing Is rival stone exist at location*/
                break;
                }
        --hide1;
        }
        hide1=j+1;
        --hide2;
    }
sort(chess,n);
}
void queen(int c,int j,char colour)                                              /*for determine queen's showmoves*/
{
  int n;
  n=rook(c,j,colour);                                                             /*queen can do same movement with rook */
  bishop(c,j,n,colour);                                                           /*queen can do same movement with bishop */
}
int rook(int c,int j,char colour)                                                /*for determine rook's showmoves*/
{
    int hide1,hide2;
    int n=0;

    hide1=c;                                                                    /*for hide first number value*/

    while(hide1>=0)
    {
        --hide1;
        if(chessboard[8-hide1][j]!=' ' || hide1<0)
        {
            n=test_stone(n,hide1,j,colour);
            break;
        }
            chess[n]=j;
            chess[n+1]=hide1;
            n+=2;
    }
    hide1=c;
    while(hide1<9)
    {
        ++hide1;
        if(chessboard[8-hide1][j]!=' ' || hide1==9)
        {
            n=test_stone(n,hide1,j,colour);
            break;
        }
        chess[n]=j;
        chess[n+1]=hide1;
        n+=2;
    }
    hide2=j;                                                                  /*for hide first number of letter value*/
    while(hide2>=0)
    {
        --hide2;
        if(chessboard[8-c][hide2]!=' ' || hide2<0)
        {
            n=test_stone(n,c,hide2,colour);
            break;
        }
        chess[n]=hide2;
        chess[n+1]=c;
        n+=2;
    }
    hide2=j;
    while(hide2<8)
    {
        ++hide2;
        if(chessboard[8-c][hide2]!=' ' || hide2==8)
        {
            n=test_stone(n,c,hide2,colour);
            break;
        }
        chess[n]=hide2;
        chess[n+1]=c;
        n+=2;
    }
sort(chess,n);
    return n;
}
void bishop(int c,int j,int t,char colour)                                       /*for determine bishop's showmoves*/
{
    int hide1;
    int hide2;
    int n=t;                                        /*if function called for queen movement,chess array continue in that place*/
    hide2=j;
    hide1=c;
    while(hide2<8 && hide1<9)
    {
        ++hide1;
        ++hide2;
        if(chessboard[8-hide1][hide2]!=' ' || hide1==9 || hide2==8)
        {
            n=test_stone(n,hide1,hide2,colour);
            break;
        }
        chess[n]=hide2;
        chess[n+1]=hide1;
        n+=2;
    }
    hide2=j;
    hide1=c;
    while(hide1>=0 && hide2>=0)
    {
        --hide1;
        --hide2;
        if(chessboard[8-hide1][hide2]!=' ' || hide2<0 || hide1<0)
        {
            n=test_stone(n,hide1,hide2,colour);
            break;
        }
        chess[n]=hide2;
        chess[n+1]=hide1;
        n+=2;
    }
   hide2=j;
   hide1=c;
    while(hide2<8 && hide1>=0)
    {
        --hide1;
        ++hide2;
        if(chessboard[8-hide1][hide2]!=' ' || hide2==8 || hide1<0)
        {
            n=test_stone(n,hide1,hide2,colour);
            break;
        }
        chess[n]=hide2;
        chess[n+1]=hide1;
        n+=2;
    }
    hide2=j;
    hide1=c;
    while(hide2>=0 && hide1<9)
    {
        ++hide1;
        --hide2;
        if(chessboard[8-hide1][hide2]!=' ' || hide1==9 || hide2<0)
        {
            n=test_stone(n,hide1,hide2,colour);
            break;
        }
        chess[n]=hide2;
        chess[n+1]=hide1;
        n+=2;
    }
 sort(chess,n);                                                                  /*to sort determined variables*/
}
void knight(int c,int j,char colour)                                             /*for determine knight's showmoves*/
{
int hide1,hide2;
int n=0;

hide1=j+1;
hide2=c+2;

while(hide1>=j-1 && hide1>=0)
    {
        while(hide2>=c-2 && hide2>=0)
            {
                if(hide1>7)
                    hide1=j-1;
                if(hide2>8)
                    hide2=c-2;

                if(chessboard[8-hide2][hide1]==' ')
                 {
                    chess[n]=hide1;
                    chess[n+1]=hide2;
                    n+=2;
                 }
                else
                n=test_stone(n,hide2,hide1,colour);
            hide2-=4;
            }
    hide2=c+2;
    hide1-=2;
    }

hide1=j+2;
hide2=c+1;

while(hide2>=c-1 && hide2>=0)
    {
        while(hide1>=j-2 && hide1>=0)
            {
                    if (hide2>8)
                        hide2=c-1;
                    if (hide1>7)
                        hide1=j-2;

                    if(chessboard[8-hide2][hide1]==' ')
                     {
                        chess[n]=hide1;
                        chess[n+1]=hide2;
                        n+=2;
                     }
                    else
                    n=test_stone(n,hide2,hide1,colour);
                hide1-=4;
            }
    hide1=j+2;
    hide2-=2;
    }
    sort(chess,n);                                                             /*for sorting array*/
}
void pawn(int c,int j,char colour)                                               /*for determine pawn's showmoves*/
{
if(colour=='w')
  {
        pawn_control(c+1,j,colour);
  }
else
  {
        pawn_control(c-1,j,colour);
  }
}
void pawn_control(int hide1,int hide2, char colour)
{
    int n=0;
    if(chessboard[8-(hide1)][hide2]==' ')
            {
                chess[n]=hide2;
                chess[n+1]=hide1;
                n+=2;
            }
    if(chessboard[8-(hide1)][hide2+1]!=' ')
            {
                n=test_stone(n,hide1,hide2+1,colour);
            }
    if(chessboard[8-(hide1)][hide2-1]!=' ')
            {
                n=test_stone(n,hide1,hide2-1,colour);
            }
}
int test_stone(int n,int f,int g,char colour)
{                   /*for determining exist opposite stone,I check array of opposite colour*/
int z;                                                                           /*for loop*/
if(colour=='w')                                                         /*testing whether colour of stone white or not*/
    {
        for(z=0;z<6;z++)
                    if(chessboard[8-f][g]==black[z])
                    {
                        chess[n]=g;
                        chess[n+1]=f;
                        return n+2;
                    }
        return n;
    }
else if (colour=='b')                                                 /*testing whether colour of stone black or not*/
    {
        for(z=0;z<6;z++)
                    if(chessboard[8-f][g]==white[z])
                    {
                        chess[n]=g;
                        chess[n+1]=f;
                        return n+2;
                    }
        return n;
    }
}
void sort(int chess[],int n)
{
    int i,j;                                                            /*for loops*/
    int hide1,hide2;                                                    /*for hide first variable*/
    for(i=0;i<=n;i++)                                                   /*for sorting number of letters */
    {
        for(j=0;j<n;j+=2)
        {
            if(chess[j]>chess[j+2] && chess[j+2]!=-1 )
            {
                hide1=chess[j];
                chess[j]=chess[j+2];
                chess[j+2]=hide1;

                hide2=chess[j+1];
                chess[j+1]=chess[j+3];
                chess[j+3]=hide2;
            }
        }
    }
    for(i=0;i<=n;i++)                                                   /*for sorting numbers */
    {
        for(j=0;j<n;j+=2)
        {
            if(chess[j]==chess[j+2] && chess[j+1]>chess[j+3] && chess[j+2]!=-1)
            {
                    hide1=chess[j];
                    chess[j]=chess[j+2];
                    chess[j+2]=hide1;

                    hide2=chess[j+1];
                    chess[j+1]=chess[j+3];
                    chess[j+3]=hide2;
            }
        }
    }
}
