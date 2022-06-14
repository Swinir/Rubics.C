#include <stdio.h>
#include "rubiks.h"
#include "rubiks.c"
#include "conio.h"
#include "conio.c"

int main() {
    Faces* Rubiks;
    int choose, run, color;
    T_COLOR g_raison;
    run = 1;
    Rubiks = create_rubiks();
    init_rubiks(Rubiks);
    display_rubiks(Rubiks);
    while(run == 1) {
        color = rand() % ( 13 + 1 ) ;
        c_textcolor(color);
        printf("\n --------------------------------------------------------------------------------------------- \n");
        color = rand() % ( 13 + 1 )  ;
        c_textcolor(color);
        printf("   1 : Scramble    2: Reset     3: Blank     ");
        color = rand() % ( 13 + 1 )  ;
        c_textcolor(color);
        printf("4: Play     5: Fill    6: Solve    7: Quit   \n");
        color = rand() % ( 13 + 1 )  ;
        c_textcolor(color);
        printf("--------------------------------------------------------------------------------------------- \n");
        color = rand() % ( 13 + 1 )  ;
        c_textcolor(color);
        printf("Enter number : ");
        scanf("%d", &choose);


        switch (choose) {
            case 1: scramble_rubiks(Rubiks);
            break;
            case 2: init_rubiks(Rubiks);
            break;
            case 3: blank_rubiks(Rubiks);
            break;
            case 4: move_rubiks(Rubiks);
            break;
            case 5: fill_rubiks(Rubiks);
            break;
            case 6: solve_rubiks(Rubiks);
            break;
            case 7: run = 0;
            break;
        }
        display_rubiks(Rubiks);
    }
    free_rubiks(Rubiks);
    return 0;
}

