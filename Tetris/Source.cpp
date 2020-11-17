/* Load Libraries */
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <time.h>
/* Load also Stdlib.h because it has the sleep function */
#include <stdlib.h>
using namespace std;
//global variables
char field[264];
int track [264];
int pro[264];
int pro2[264];
char store[264];
char store2[264];
char shape[16];
int leftc;
int rightc;
int dc;
int delete_index[21];

int L[4] = { 0,4,8,9 };
int I[4] = { 0,4,8,12 };
int Sq[4] = { 0,1,4,5 };
int gu[4] = { 1,4,5,8 };
int gd[4] = { 0,4,5,9 };
int oL[4] = { 1,5,9,8 };
int T[4] = { 0,1,2,5 };

/* Declare Goto Function */
void gotoxy(int, int);
void draw();

void store_fill() {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 12; j++) {
            store[i * 12 + j] = '\0';
        }

    }
}

void store2_fill() {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 12; j++) {
            store2[i * 12 + j] = '\0';
        }

    }
}

void fill() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            shape[i * 4 + j] = '\0';
        }

    }
}

void track_fill() {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 12; j++) {
            track[i * 12 + j] = 0;
        }

    }
}
void pro_fill() {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 12; j++) {
            pro[i * 12 + j] = 0;
        }

    }
}
void pro2_fill() {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 12; j++) {
            pro2[i * 12 + j] = 0;
        }

    }
}


//Setup screen for tetris
void initialiseField() {
    for (int i = 0; i < 22; i++) {
        field[i * 12] = '#';
        field[(i * 12) + 11] = '#';

    }

    for (int i = 0; i < 12; i++) {
        //field[i] = '#';
        field[252 + i] = '#';

    }
}

//Print field
void printField() {

    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 12; j++) {
            printf("%c",field[i * 12 + j]);
            //cout << " ";
        }
        printf("\n");
    }

}

//Create shape
void create_shape() {
    int r = rand() % 6 + 1;
    //int r = 3;
    switch (r) {
    case 1:
        shape[L[0]] = 'L';
        shape[L[1]] = 'L';
        shape[L[2]] = 'L';
        shape[L[3]] = 'L';
        leftc = 0;
        rightc = 1;
        dc = 2;
        break;
    case 2:
        shape[I[0]] = 'I';
        shape[I[1]] = 'I';
        shape[I[2]] = 'I';
        shape[I[3]] = 'I';
        leftc = 0;
        rightc = 0;
        dc = 3;
        break;
    case 3:
        shape[Sq[0]] = 'S';
        shape[Sq[1]] = 'S';
        shape[Sq[2]] = 'S';
        shape[Sq[3]] = 'S';
        leftc = 0;
        rightc = 1;
        dc = 1;
        break;
    case 4:
        shape[gu[0]] = 'U';
        shape[gu[1]] = 'U';
        shape[gu[2]] = 'U';
        shape[gu[3]] = 'U';
        leftc = 0;
        rightc = 1;
        dc = 2;
        break;
    case 5:
        shape[gd[0]] = 'D';
        shape[gd[1]] = 'D';
        shape[gd[2]] = 'D';
        shape[gd[3]] = 'D';
        leftc = 0;
        rightc = 1;
        dc = 2;
        break;
    case 6:
        shape[oL[0]] = 'F';
        shape[oL[1]] = 'F';
        shape[oL[2]] = 'F';
        shape[oL[3]] = 'F';
        leftc = 0;
        rightc = 1;
        dc = 2;
        break;
    case 7:
        shape[T[0]] = 'T';
        shape[T[1]] = 'T';
        shape[T[2]] = 'T';
        shape[T[3]] = 'T';
        leftc = 0;
        rightc = 2;
        dc = 1;
        break;
    default:
        break;
    }

}





/* Make GOTOXY function */
void gotoxy(int eex, int eey)
{
    COORD coord;
    coord.X = eex;
    coord.Y = eey;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void print_shape(int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (field[((i+y) * 12) + x + j] != '#' && track[((i + y) * 12) + x + j] !=1) {
                gotoxy(x + j, y + i);
                printf("%c", shape[i * 4 + j]);
            }
            
        }
        
            printf("\n");
        
    }
}

void empty_shape(int x,int y) {
    
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (field[((i+y) * 12) + x + j] != '#' && track[((i + y) * 12) + x + j] != 1) {
                gotoxy(x + j, y + i);
                printf("%c", '\0');
            }
        }
        printf("\n");
    }
}
void tracker(int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i*4+j]!='\0') {
                track[((i + y) * 12) + x + j] = 1;
                store[((i + y) * 12) + x + j] = shape[i * 4 + j];
            }
        }
        
    }

}
void current_progress(int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i * 4 + j] != '\0') {
                pro[((i + y) * 12) + x + j] = 1;
            }
        }

    }
}

void current_progress2(int x, int y) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i * 4 + j] != '\0') {
                pro2[((i + y) * 12) + x + j] = 1;
            }
        }

    }
}



int check(int x, int y)
{
    current_progress(x, y);
    for (int j = 1; j > -2; j--) {
        for (int i = 0; i < 12; i++) {
            if (track[((dc + y + j) * 12) + i] != 0) {
                if (pro[(((dc + y + j - 1) * 12) + i)] == 1) {
                    pro_fill();
                    return 0;
                }
            }
        }
    }
        pro_fill();
        return 1;

    /*current_progress(x, y);
    for (int i = 0; i < 12; i++) {
        if (track[((dc + y+1) * 12) + i] != 0) {
            if (pro[(((dc + y) * 12) + i)]==1) {
                pro_fill();
                return 0;
            }
        }
    }
    pro_fill();
    return 1;*/
}
/*
current_progress(x, y);
    for(int j=1;j>-2;j++){
    for (int i = 0; i < 12; i++) {
        if (track[((dc + y+j) * 12) + i] != 0) {
            if (pro[(((dc + y+j-2) * 12) + i)]==1) {
                pro_fill();
                return 0;
            }
        }
    }
    pro_fill();
    return 1;
    }
    

*/

int check_track_right(int x, int y) {
    /*current_progress2(x, y);
    for (int j = 1; j > -2; j--) {
        for (int i = 0; i < 21; i++) {
            if (track[((rightc + x + j) * 22) + i] != 0) {
                if (pro2[(((rightc + x + j - 1) * 22) + i)] == 1) {
                    pro2_fill();
                    return 0;
                }
            }
        }
    }
    
    pro2_fill();
    return 1;
    */
    current_progress2(x, y);
    for (int i = dc; i >= 0; i--) {
        for (int j = 1; j > -2; j--) {
            if (track[((i + y) * 12) + j + x+rightc] != 0) {
                if (pro2[((i + y) * 12) + j + x+rightc - 1] == 1)
                {
                    pro2_fill();
                    return 0;
                }
            }
        }
    }
    pro2_fill();
    return 1;
}

int check_track_left(int x, int y) {
    /*current_progress2(x, y);
    for (int j = 1; j > -2; j--) {
        for (int i = 0; i < 21; i++) {
            if (track[((rightc + x + j) * 22) + i] != 0) {
                if (pro2[(((rightc + x + j - 1) * 22) + i)] == 1) {
                    pro2_fill();
                    return 0;
                }
            }
        }
    }

    pro2_fill();
    return 1;
    */
    current_progress2(x, y);
    for (int i = dc; i >= 0; i--) {
        for (int j = -1; j <= 1; j++) {
            if (track[((i + y) * 12) + j + x + leftc] != 0) {
                if (pro2[((i + y) * 12) + j + x + leftc + 1] == 1)
                {
                    pro2_fill();
                    return 0;
                }
            }
        }
    }
    pro2_fill();
    return 1;
}



/* Init X and Y plus the Variables which hold
     previous X and Y. */

int x, y, lastx, lasty;
//draw
void draw() {

    int ch;
    /* Make a CHAR variable to get Key Input */
    char a;
    if (leftc == 0 && rightc ==1) {
        x = (rand() % 9) + 1;
    }
    else if (leftc==0 && rightc==0) {
        x = (rand() % 10) + 1;
    }
    else if (leftc == 0 && rightc == 2) {
        x = (rand() % 8) + 1;
    }
    
    //y = (rand() % 40) + 1;
    /* Store the previous X and Y */
    //x = 5;
    y = 0;
    lastx = x; lasty = y;
    
    ch = check(x, y);

    /* start an Infinite Loop */
    while (y + dc < 21 && ch == 1)
    {
        /* Head to LastX and LastY and clear old O*/
        //gotoxy(lastx, lasty);
        empty_shape(lastx,lasty);
        //printf(" ");
        /* Draw New O */
        //gotoxy(x, y);
        //printf("O");
        print_shape(x,y);
        
        /* Remember Old X and Y */
        lastx = x; lasty = y;

        /* Get Input */
        while (_kbhit() && y+dc < 20) {
            ch = check(x, y);
            a = _getch();
            /* If Down Arrow is Pressed, Y is increased */

            if (a == 80) {
                if (y + dc < 20 && ch == 1) {
                    y = y + 1;
                }
                
            }
            /*If Right Arrow is Pressed, X is increased */
            if (a == 77) {
                //cout << x;
                if (x+rightc < 10 && ch == 1) {
                    //check right side if occupied
                    //if track right side==1 then no
                    if (check_track_right(x,y)==1) {
                        x = x + 1;
                    }
                    
                    
                }
            }

            /*If Left Arrow is Pressed, X is decreased */
            if (a == 75)
            {
                //cout << x;
                if (x-leftc > 1 && ch == 1) {
                    //check left side if occupied
                    if (check_track_left(x,y)==1) {
                        x = x - 1;
                    }
                    
                }
            }

            //gotoxy(lastx, lasty);
            //printf(" ");
            /* Draw New O */
            empty_shape(lastx,lasty);
            //gotoxy(x, y);
            print_shape(x,y);
            //printf("O");

            /* Remember Old X and Y */
            lastx = x; lasty = y;

            Sleep(100);

        }
        /* If Up Arrow is Pressed, Y is decreased */
        //if (a == 72) y = y - 1;
        /* If Right Arrow is Pressed, X is increased */
        //if (a == 77) x = x + 1;
        /* If Left Arrow is Pressed, X is decreased */
        //if (a == 75) x = x - 1;
        if (y + dc < 21) {
            ch = check(x, y);
            if(ch == 1)
            {
                y = y + 1;
            }
            
        }

        Sleep(1000);
    }
    if (!(y + dc < 21)) {
        tracker(x, y - 1);
    }
    else {
        tracker(x, y );

    }
    

}
int is_ind(int index){

    for (int k = 0; k < 21; k++) {
        if (delete_index[k] == index) {
            //printf("%d",index);
            return 1;
        }
    }
    return 0;
}
int search(int ind) {
    for (int i = ind; i >=0; i--) {
        for (int j = 1; j<11; j++) {
            if (store[i * 12 + j] != '\0') {
                return i;
            }
        }
        
    }
    /*for (int i = 0; i < 21; i++) {
        if (delete_index[i] == ind) {
            return ind;
        }
    }*/
    return -1;
}
void down(int i, int s) {
    for (int j = 1; j < 11; j++) {
        store2[i * 12 + j] = store[s * 12 + j];
    }
    }
void copy() {
    for (int i = 0; i < 21; i++) {
        for (int j = 1; j < 11; j++) {
            store[i * 12 + j] = store2[i * 12 + j];
        }
    }
}

void fix_track() {
    for (int i = 0; i < 21; i++) {
        for (int j = 1; j < 11; j++) {
            if (store[i * 12 + j] != '\0') {
                track[((i) * 12) + j] = 1;
                
            }
            else {
                track[((i) * 12) + j] = 0;
            }
        }

    }
}

void spacing() {
    /*for (int i = 0; i < 21; i++) {
        printf("%d", delete_index[i]);

    }*/
    //int hi = 0;
    int btn = 0;
    int do_nothing = 0;
    int s;
    for (int i = 20; i >= 1; i--) {
        if (is_ind(i) == 1 || btn==1) {
            //btn = 1;
            //printf("%d", i);
            //printf("%c",'\0');
                s = search(i - 1);
                if (s == -1) {
                    do_nothing = 0;
                }
                else {
                    down(i, s);
                    btn = 1;


                }
            
        }
        else {
            for (int j = 1; j < 11; j++)
            {
               //system("cls");
                //if (store[i * 12 + j] != '\0') {
                store2[i * 12 + j] = store[i * 12 + j];
                /*if (hi == 0) {
                    printf("%c", store2[i * 12 + j]);
                }*/
                //}
            }//hi++;
            
        }
        

    }
   
    copy();
    
    fix_track();

}
void init_delete() {
    for (int i = 0; i < 21; i++) {
        delete_index[i] = -1;
    }
}
void reprint() {
    
    for (int i = 0; i < 21; i++) {
        gotoxy(1, i);
        for (int j = 1; j < 11; j++) {
            
            printf("%c",store[((i) * 12) + j]);
            
        }printf("\n");

    }
}
void all_one() {
    int sum = 0;
    int cnt = 0;
    init_delete();
    store2_fill();
    for (int i = 20; i >= 0; i--) {
        sum = 0;
        for (int j = 1; j < 11; j++) {
            if (track[i * 12 + j] == 1) {
                sum++;
                
            }
        }
        if (sum == 10) {
            
            delete_index[cnt] = i;
            cnt++;
        }
    }
    for (int k = 0; k < 21; k++) {
        if (delete_index[k] != -1) {
            for (int m = 1; m < 11; m++) {
                //gotoxy(m, delete_index[k]);
                //printf("%c", '\0');
                store[delete_index[k] * 12 + m] = '\0';
            }
            
        }
    }
    
    if (cnt > 0) {
        spacing();
        reprint();
    }
    
    
}



/* Main Function */
int main()
{   
    int alive = 1;
    fill();
    //for (int i = 0; i < 4; i++) {
    //    for (int j = 0; j < 4; j++) {
    //        printf("%c",shape[i * 4 + j]);
    //    }
    //    printf("\n");

    //}
    /* type some message for the user */
    printf("My Moving Char program!\n\n");
    /* sleep waits in miliseconds, so 5 * 1000 = 5 seconds */
    //Sleep(5 * 1000);
    /* Clear the screen completely */
    system("cls");
    /* if we dont use SRAND, RAND returns the same number over and over */
    srand((unsigned)time(NULL));
    /* a typical Console screen is 80x40, since a Console Screen is
       made of only text. 80 is the number of columns and 40 is the
       number of rows. so we randomize X and Y in those areas */
    initialiseField();
    store_fill();
    track_fill();
    pro_fill();
    pro2_fill();
    printField();
    
    while (alive < 20) {

        create_shape();
        draw();
        all_one();
        fill();
        alive++;
    }
        system("cls");
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 12; j++) {
                printf("%d",track[i*12+j]);

            }
            printf("\n");
        }
        for (int i = 0; i < 22; i++) {
            for (int j = 0; j < 12; j++) {
                printf("%c", store[i * 12 + j]);

            }
            printf("\n");
        }
    
        

    
}

/* for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 12; j++) {
            printf("%c", store2[i * 12 + j]);
        }
        printf("\n");
    }*/