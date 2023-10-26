#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define BEGINNER 0
#define INTERMEDIATE 1
#define ADVANCED 2
#define MAXSIDE 25
#define MAXMINES 99
#define MOVESIZE 526  //(25*25-99)


int SIDE;     //tahtanin yan uzunlugu
int MINES;    //tahtadaki mayin sayisi

bool isValid(int row, int col)   //verilen hucre icin satir sutun kontrolu yapar, gecerli mi degil mi
{
    return (row >= 0) && (row < SIDE) && (col >= 0) && (col < SIDE);
    // satir ve sutun numarasi varsa true doner

}


bool isMine(int row, int col, char board[][MAXSIDE])   //verilen hucrede mayin olup olmadiginin kontrolunu yapar
{
    if(board[row][col] == '*')
        return (true);
    else
        return (false);
}

void makeMove(int &x, int &y)  //oyuncunun hangi hucreye týklamak istedini iletir
{
    cout<<"Enter your move, (row, column) -> ";
    cin>>x>>y;
    return;
}

void printBoard(char myBoard[][MAXSIDE])   //mevcut olan tahtayi yazdirir
{
    int i,j;

    cout<<"  ";

    for(i=0; i<SIDE; i++){
        if(i < 10)
        {
            cout<<" "<<i<<" ";
        }
        else
        {
            cout<<i<<" ";
        }
    }

    cout<<endl;
    cout<<" +";
    for(i = 0; i<SIDE; i++){
        cout<<"---";
    }
    cout<<endl;

    for(i=0; i<SIDE; i++){
        if(i < 10)
        {
            cout<<" "<<i<<"|";
        }
        else
        {
            cout<<i<<"|";
        }

        for(j=0; j<SIDE; j++){
            cout<<" "<<myBoard[i][j]<<" ";
        }
        cout<<"|"<<endl;
    }
    cout<<" +";
    for(i = 0; i<SIDE; i++){
        cout<<"---";
    }
    cout<<endl;

    return;
}

int countAdjacentMines(int row, int col, int mines[][2], char realBoard[][MAXSIDE])   //verilen hucrenin etrafindakileri mayinlari sayar.
{
    int i;
    int count = 0;

    /*
		Bitisik 8 hucredeki tum mayinlari sayar

			N.W N N.E
			\ | /
			\ | /
			W----Cell----E
				/ | \
			/ | \
			S.W S S.E

		Hucre-->Mevcut hucre (satir,sutun)  //(row, col)
		N --> Kuzey	(satir-1, sutun)  //(row-1, col)
		S --> Guney	(satir+1, sutun)  //(row+1, col)
		E --> Dogu	(satir, sutun+1)  //(row, col+1)
		W --> Bati  (satir, sutun-1)  //(row, col-1)
		N.E--> Kuzey-Dogu (satir-1, sutun+1)  //(row-1, col+1)
		N.W--> Kuzey-Bati (satir-1, sutun-1)  //(row-1, col-1)
		S.E--> Guney-Dogu (satir+1, sutun+1)  //(row+1, col+1)
		S.W--> Guney-Bati (satir+1, sutun-1)  //(row+1, col-1)
	*/


	//----------- 1. KOMSU (KUZEY) -----------

        if(isValid(row-1, col) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row-1, col, realBoard) == true)
            {
                count++;
            }
        }

    //----------- 2. KOMSU (GUNEY) -----------

        if(isValid(row+1, col) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row+1, col, realBoard) == true)
            {
                count++;
            }
        }

    //----------- 3. KOMSU (DOGU) -----------

        if(isValid(row, col+1) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row, col+1, realBoard))
            {
                count++;
            }
        }

    //----------- 4. KOMSU (BATI) -----------

        if(isValid(row, col-1) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row, col-1, realBoard))
            {
                count++;
            }
        }

    //----------- 5. KOMSU (KUZEY-DOGU) -----------

        if(isValid(row-1, col+1) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row-1, col+1, realBoard))
            {
                count++;
            }
        }

    //----------- 6. KOMSU (KUZEY-BATI) -----------

        if(isValid(row-1, col-1) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row-1, col-1, realBoard))
            {
                count++;
            }
        }

    //----------- 7. KOMSU (GUNEY-DOGU) -----------

        if(isValid(row+1, col+1) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row+1, col+1, realBoard))
            {
                count++;
            }
        }

    //----------- 8. KOMSU (GUNEY-BATI) -----------

        if(isValid(row+1, col-1) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row+1, col-1, realBoard))
            {
                count++;
            }
        }
    return(count);
}

bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE], int mines[][2], int row, int col, int *movesLeft)  //oyunu oynamak icin recursive(ozyinelemeli) calýsýr. Oyunun asil mantigi burada olur.
//Eger mayin acilirsa oyunu kaybeder, aksi halde oyun devam eder
{
    if(myBoard[row][col] != '-')
        return (false);

    int i, j;

    if(realBoard[row][col] == '*')   //Mayini acarsan kaybedersin
    {
        myBoard[row][col] = '*';

        for(i=0; i<MINES; i++){
            myBoard[mines[i][0]][mines[i][1]] = '*';
        }

        printBoard(myBoard);
        cout<<endl;
        cout<<"YOU LOST!"<<endl;
        return(true);
    }

    else
    {
        int count = countAdjacentMines(row, col, mines, realBoard);
        (*movesLeft)--;

        myBoard[row][col] = count + '0';

        if(!count)
        {

        /*
            Bitisik 8 hucreyi yineler

                N.W N N.E
                \ | /
                \ | /
                W----Cell----E
                    / | \
                / | \
                S.W S S.E

            Hucre-->Mevcut hucre (satir,sutun)  //(row, col)
            N --> Kuzey	(satir-1, sutun)  //(row-1, col)
            S --> Guney	(satir+1, sutun)  //(row+1, col)
            E --> Dogu	(satir, sutun+1)  //(row, col+1)
            W --> Bati  (satir, sutun-1)  //(row, col-1)
            N.E--> Kuzey-Dogu (satir-1, sutun+1)  //(row-1, col+1)
            N.W--> Kuzey-Bati (satir-1, sutun-1)  //(row-1, col-1)
            S.E--> Guney-Dogu (satir+1, sutun+1)  //(row+1, col+1)
            S.W--> Guney-Bati (satir+1, sutun-1)  //(row+1, col-1)
        */

        //----------- 1. KOMSU (KUZEY) -----------

        if(isValid(row-1, col) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row-1, col, realBoard) == false)
            {
                playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft);
            }
        }

        //----------- 2. KOMSU (GUNEY) -----------

        if(isValid(row+1, col) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row+1, col, realBoard) == false)
            {
                playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft);
            }
        }

        //----------- 3. KOMSU (DOGU) -----------

        if(isValid(row, col+1) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row, col+1, realBoard) == false)
            {
                playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft);
            }
        }

        //----------- 4. KOMSU (BATI) -----------

        if(isValid(row, col-1) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row, col-1, realBoard) == false)
            {
                playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft);
            }
        }

        //----------- 5. KOMSU (KUZEY-DOGU) -----------

        if(isValid(row-1, col+1) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row-1, col+1, realBoard) == false)
            {
                playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
            }
        }

        //----------- 6. KOMSU (KUZEY-BATI) -----------

        if(isValid(row-1, col-1) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row-1, col-1, realBoard) == false)
            {
                playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
            }
        }

        //----------- 7. KOMSU (GUNEY-DOGU) -----------

        if(isValid(row+1, col+1) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row+1, col+1, realBoard) == false)
            {
                playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
            }
        }

         //----------- 8. KOMSU (GUNEY-BATI) -----------

        if(isValid(row+1, col-1) == true) //Eger gerceli hucre ise isle
        {
            if(isMine(row+1, col-1, realBoard) == false)
            {
                playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft);
            }
        }

        }
        return(false);
    }

}

void placeMines(int mines[][2], char realBoard[][MAXSIDE]) //mayinlari rastgele yerleþtirir.
//mines adli bir dizi, her mayinin koordinatlarini saklar.
{
    bool mark[MAXSIDE*MAXSIDE];

    memset(mark, false, sizeof(mark));

    for(int i=0; i<MINES; ){      //tum mayinlar olusturulana kadar devam eder
        int random = rand() % (SIDE*SIDE);
        int x = random / SIDE;
        int y = random % SIDE;

        if(mark[random] == false)//mayin yoksa mayin ekler
        {
            mines[i][0] = x;  //mayinin satir dizini

            mines[i][1] = y;  //mayinin sutun dizini

            realBoard[mines[i][0]][mines[i][1]] = '*';   //mayini yerlestir
            mark[random] = true;
            i++;
        }
    }
    return;
}



void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE])   //oyunu baslatir ve baslangic durumuna getirir.
{
    srand(time(NULL));    //Rastgele sayi ureteci baslatýr ve ayný konfigirasyon denk gelmez

    for(int i=0; i<SIDE; i++){   //tum hucreleri mayinsiz yapar
        for(int j=0; j<SIDE; j++){
            myBoard[i][j] = realBoard[i][j] = '-';
        }
    }
    return;

}

void cheatMinesweeper(char realBoard[][MAXSIDE])    //mayinin nerede oldugunu gosterir
// hile yaparak oynamak isteyen oyuncular icin tüm mayinlarin yerini gosterir.
{
    cout<<"The mines locations are-"<<endl;
    printBoard(realBoard);
    return;
}

void replaceMine(int row, int col, char board[][MAXSIDE] ) //verilen hucredeki bir mayini baska bir bos hucreye tasir
{
    for(int i=0; i<SIDE; i++){
        //tahtadaki mayin olmayan ilk yeri bulur ve mayin koyar.
        for(int j=0; j<SIDE; j++){
            if(board[i][j]!= '*')
            {
                board[i][j] = '*';
                board[row][col] = '-';
                return;
            }
        }
    }
    return;
}

void playMinesweeper()   //oyunun ana mantigi baslar
//kullaniciya oyun tahtasini acma ve oynama firsati verir.
//Oyuncu sirayla hücreler acar.
//Mayinla karsilasirsa, oyunu kaybeder.
//Aksi takdirde, hucrede kac mayin oldugunu gosteren bir sayi goruntulenir.
//Oyun tahtasi tamamen acýldiginda veya bir mayina tiklanmadiginda, oyuncu oyunu kazanir.
{
    bool gameOver = false;   //baslangicta oyun bitmedi

    char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];    //gercek tahta(pano) ve benim tahtam

    int movesLeft = SIDE * SIDE - MINES, x, y;
    int mines[MAXMINES][2];    //tum mayinlarin (x,y) koordinatlarini saklar

    initialise(realBoard, myBoard);

    placeMines(mines, realBoard);   //mayinlari rastgele yerlestir



    //mayin acmadigin surece oyundasýn, devam ettirir
    int currentMoveIndex = 0;
    while(gameOver == false){
        cout<<"Current Status of Board : "<<endl;
        printBoard(myBoard);
        makeMove(x, y);


        if(currentMoveIndex == 0) //ilk hamlenin her zaman garanti olmasini saglar
        {
            //ilk hamlenin kendisi mayin ise mayini o konumdan kaldirir
            if(isMine(x, y, realBoard) == true)
            {
                replaceMine(x, y, realBoard);
            }
        }

        currentMoveIndex++;

        gameOver = playMinesweeperUtil(myBoard, realBoard, mines, x, y, &movesLeft);

        if((gameOver == false) && (movesLeft == 0))
        {
            cout<<endl;
            cout<<"YOU WON !"<<endl;
            gameOver = true;
        }
    }
    return;

}

void chooseDifficultyLevel()  //oyuun zorluk seviyesini secer
{
    /*
	--> BEGINNER = 9 * 9 hucre and 10 mayin
	--> INTERMEDIATE = 16 * 16 hucre and 40 mayin
	--> ADVANCED = 24 * 24 hucre and 99 mayin
	*/

	int level;

	cout<<"Enter the Difficulty Level"<<endl;
	cout<<"Press 0 for BEGINNER (9 * 9 Cells and 10 Mines)"<<endl;
	cout<<"Press 1 for INTERMEDIATE (16 * 16 Cells and 40 Mines)"<<endl;
	cout<<"Press 2 for ADVANCED (24 * 24 Cells and 99 Mines)"<<endl;

	cin>>level;

	if(level == BEGINNER)
    {
        SIDE = 9;
        MINES = 10;
    }

    if(level == INTERMEDIATE)
    {
        SIDE = 16;
        MINES = 40;
    }

    if(level == ADVANCED)
    {
        SIDE = 24;
        MINES = 99;
    }

    return;
}

int main()
{
    /*
    Bir seviye sec

	--> BEGINNER = 9 * 9 hucre and 10 mayin
	--> INTERMEDIATE = 16 * 16 hucre and 40 mayin
	--> ADVANCED = 24 * 24 hucre and 99 mayin
	*/

    chooseDifficultyLevel();

    playMinesweeper();

    return 0;
}
