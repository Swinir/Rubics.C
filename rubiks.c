#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// return color number
int select_color(T_COLOR color){
    switch (color) {
        case R : return 4;
        case B : return 1;
        case G : return 2;
        case W :return 15;
        case Y :return 14;
        case O :return 6;
        case LG : return 7;
    }
}

// return a char to display
char* display_color(T_COLOR color){
    switch(color)
    {
        case R : return "R";
        case B : return "B";
        case G : return "G";
        case W : return "W";
        case Y : return "Y";
        case O : return "O";
        default : return "LG";
    }
}

// return the number of face
int side_to_index(T_SIDE side) {
    switch (side) {
        case FRONT: return 4;
        case BACK : return 5;
        case UP : return 2;
        case DOWN : return 3;
        case RIGHT : return 1;
        case LEFT : return 6;
    }
}

// creat the array of Structure who represent the rubiks
Faces* create_rubiks() {
    int s ;
    Faces* Rubiks = malloc(6 * sizeof(Faces));
    T_SIDE side[] = {UP,LEFT,FRONT,RIGHT,BACK,DOWN};

    for (s =0 ; s < 6 ; s ++) {
        Rubiks[s].type_face = side[s];
    }
    return Rubiks;
}

// initialisation of the rubiks not scramble
void init_rubiks(Faces* Rubiks){
    int face , line , cases;
    T_COLOR color_rubiks[] = {W,O,G,R,B,Y};
    for (face =0 ; face < 6 ; face ++){
        for (line = 0 ; line <3; line ++) {
            for (cases = 0 ; cases <3  ; cases ++){
                Rubiks[face].face[line][cases] = color_rubiks[face];
            }
        }
    }
}

// display the rubiks in the console
void display_rubiks(Faces* Rubiks){
    int face , line , cases ,nbr_color;
    T_COLOR  color;

    for (line = 0 ; line < 3 ; line ++) {
        printf("\n");
        printf("       ");
        for (cases = 0 ; cases < 3 ; cases ++){
            color = Rubiks[0].face[line][cases];
            nbr_color = select_color(color);
            c_textcolor(nbr_color);
            printf("%s " , display_color(color));
        }
    }
    printf("\n \n");
    for (line = 0 ; line < 3 ; line ++) {
        for (face =1 ; face < 5 ; face ++){
            for (cases = 0 ; cases < 3 ; cases ++){
                color = Rubiks[face].face[line][cases];
                nbr_color = select_color(color);
                c_textcolor(nbr_color);
                printf("%s " , display_color(color));
            }
            printf(" ");
        }
        printf("   \n");
    }
    for (line = 0 ; line < 3 ; line ++) {
        printf("\n");
        printf("       ");
        for (cases = 0 ; cases < 3 ; cases ++){
            color = Rubiks[5].face[line][cases];
            nbr_color = select_color(color);
            c_textcolor(nbr_color);
            printf("%s " , display_color(color));
        }
    }
}

// Every color become light grey
void blank_rubiks(Faces* Rubiks) {
    int face , line , cases;
    for (face = 0; face < 6; face++) {
        for (line = 0; line < 3; line++) {
            for (cases = 0; cases < 3; cases++) {
                Rubiks[face].face[line][cases] = LG ;
            }
        }
    }
}


// Function of rotation
void rotate_clockwise(T_COLOR (face)[3][3] ){
    int i, j;
    T_COLOR curr_color;

    //Copying face
    T_COLOR face_cop[3][3] ;
    for (i=0; i<3; i++) {
        for (j = 0; j < 3; j++) {
            curr_color = face[i][j];
            face_cop[i][j] = curr_color;
        }
    }

    //Rotating face
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++)
            face[j][2 - i] = face_cop[i][j];
    }

}


// Principal function used for every clockwise rotation
void clockwise(Faces* Rubiks, int face) {
    int left = (face-1), right = (face%4)+1, x_up, y_up, x_down, y_down, i;
    T_COLOR color;

    if (face==1) {
        left = 4;
    }
    for (i = 0; i < 3; i++) {

        switch (face) {
            case 1: x_up = i, y_up = 0, x_down = i, y_down = 0;
                break;
            case 2: x_up = 2, y_up = i, x_down = 0, y_down = 2-i;
                break;
            case 3: x_up = 2-i, y_up = 2, x_down = 2-i, y_down = 2;
                break;
            case 4: x_up = 0, y_up = 2-i, x_down = 2, y_down = i;
                break;
            default: x_up = 0, y_up = 0, x_down = 0, y_down = 0;
        }

        color = Rubiks[0].face[x_up][y_up];
        Rubiks[0].face[x_up][y_up] = Rubiks[left].face[2 - i][2];
        Rubiks[left].face[2 - i][2] = Rubiks[5].face[x_down][y_down];
        Rubiks[5].face[x_down][y_down] = Rubiks[right].face[i][0];
        Rubiks[right].face[i][0] = color;
    }
}

void up_clockwise(Faces* Rubiks, int rota_type){
    int n, i, j;
    T_COLOR first_line[3];

    for (n=0; n<rota_type; n++) {
        rotate_clockwise(Rubiks[0].face);

        for (i = 0; i < 3; i++)
            first_line[i] = Rubiks[1].face[0][i];

        for (i = 1; i < 4; i++) {
            for (j = 0; j < 3; j++)
                Rubiks[i].face[0][j] = Rubiks[i + 1].face[0][j];
        }

        for (i = 0; i < 3; i++)
            Rubiks[4].face[0][i] = first_line[i];
    }

}

void down_clockwise(Faces* Rubiks, int rota_type){
    int n, i, j;
    T_COLOR last_line[3];

    for (n=0; n<rota_type; n++) {
        rotate_clockwise(Rubiks[5].face);
        for (i = 0; i < 3; i++)
            last_line[i] = Rubiks[4].face[2][i];

        for (i = 4; i > 1; i--) {
            for (j = 0; j < 3; j++)
                Rubiks[i].face[2][j] = Rubiks[i - 1].face[2][j];
        }

        for (i = 0; i < 3; i++)
            Rubiks[1].face[2][i] = last_line[i];
    }

}

void front_clockwise(Faces* Rubiks, int rota_type){
    int n;
    for (n=0; n<rota_type; n++) {
        rotate_clockwise(Rubiks[2].face);
        clockwise(Rubiks, 2);
    }
}

void back_clockwise(Faces* Rubiks, int rota_type){
    int n;
    for (n=0; n<rota_type; n++) {
        rotate_clockwise(Rubiks[4].face);
        clockwise(Rubiks, 4);
    }
}

void right_clockwise(Faces* Rubiks, int rota_type){
    int n;
    for (n=0; n<rota_type; n++) {
        rotate_clockwise(Rubiks[3].face);
        clockwise(Rubiks, 3);
    }
}

void left_clockwise(Faces* Rubiks, int rota_type){
    int n;
    for (n=0; n<rota_type; n++) {
        rotate_clockwise(Rubiks[1].face);
        clockwise(Rubiks, 1);
    }
}


// simple rotation
void horizontal_rotation(Faces* Rubiks){
    Faces temp_face, curr_face;
    int i, j;

    //Rotate UP, DOWN faces
    for (i=0; i<2; i++) {
        if (i==0)
            curr_face = Rubiks[0];
        else
            curr_face = Rubiks[5];

        for (j=0; j<2; j++)
            rotate_clockwise(curr_face.face);
    }

    //Switch other faces
    for (i=1; i<3; i++) {
        temp_face = Rubiks[i];
        Rubiks[i] = Rubiks[i+2];
        Rubiks[i+2] = temp_face;
    }
}

void vertical_rotation(Faces* Rubiks){
    Faces temp_face1, temp_face2, curr_face;
    int i, j;

    //Rotate LEFT and RIGHT faces
    for (i=0; i<2; i++) {
        if (i==0)
            curr_face = Rubiks[1];
        else
            curr_face = Rubiks[3];

        for (j=0; j<2; j++)
            rotate_clockwise(curr_face.face);
    }

    //Switch the other faces
    temp_face1 = Rubiks[0];
    Rubiks[0] = Rubiks[5];
    Rubiks[5] = temp_face1;

    temp_face2 = Rubiks[2];
    Rubiks[2] = Rubiks[4];
    Rubiks[4] = temp_face2;

    for (j=0; j<2; j++) {
        rotate_clockwise(Rubiks[2].face);
        rotate_clockwise(Rubiks[4].face);
    }
}


void rotate_anticlockwise(T_COLOR (face)[3][3]){
    int i, j;
    T_COLOR curr_color;

    //Copying face
    T_COLOR face_cop[3][3];
    for (i=0; i<3; i++) {
        for (j = 0; j < 3; j++) {
            curr_color = face[i][j];
            face_cop[i][j] = curr_color;
        }
    }
    //Rotating face
    for (i=0; i<3; i++) {
        for (j=0; j<3; j++)
            face[i][j] = face_cop[j][2-i];
    }
}

void anticlockwise(Faces* Rubiks, int face) {
    int left = (face-1);
    int right = (face%4)+1, x_up, y_up, x_down, y_down, i;
    T_COLOR temp_color;

    if (face==1)
        left = 4;

    for (i = 0; i < 3; i++) {

        switch (face) {
            case 1: x_up = i, y_up = 0, x_down = i, y_down = 0;
                break;
            case 2: x_up = 2, y_up = i, x_down = 0, y_down = 2-i;
                break;
            case 3: x_up = 2-i, y_up = 2, x_down = 2-i, y_down = 2;
                break;
            case 4: x_up = 0, y_up = 2-i, x_down = 2, y_down = i;
                break;
            default: x_up = 0, y_up = 0, x_down = 0, y_down = 0;
        }

        temp_color = Rubiks[left].face[2 - i][2];
        Rubiks[left].face[2 - i][2] = Rubiks[0].face[x_up][y_up];
        Rubiks[0].face[x_up][y_up] = Rubiks[right].face[i][0];
        Rubiks[right].face[i][0] = Rubiks[5].face[x_down][y_down];
        Rubiks[5].face[x_down][y_down] = temp_color;
    }
}

void up_anticlockwise(Faces* Rubiks, int rota_type){
    int n, i, j;
    T_COLOR first_line[3];

    for (n=0; n<rota_type; n++) {
        rotate_anticlockwise(Rubiks[0].face);

        for (i = 0; i < 3; i++)
            first_line[i] = Rubiks[4].face[0][i];

        for (i = 4; i > 1; i--) {
            for (j = 0; j < 3; j++)
                Rubiks[i].face[0][j] = Rubiks[i-1].face[0][j];
        }

        for (i = 0; i < 3; i++)
            Rubiks[1].face[0][i] = first_line[i];
    }
}

void down_anticlockwise(Faces* Rubiks, int rota_type){
    int n, i, j;
    T_COLOR last_line[3];

    for (n=0; n<rota_type; n++) {
        rotate_anticlockwise(Rubiks[5].face);

        for (i = 0; i < 3; i++)
            last_line[i] = Rubiks[1].face[2][i];

        for (i = 1; i < 4; i++) {
            for (j = 0; j < 3; j++)
                Rubiks[i].face[2][j] = Rubiks[i + 1].face[2][j];
        }

        for (i = 0; i < 3; i++)
            Rubiks[4].face[2][i] = last_line[i];
    }

}

void front_anticlockwise(Faces* Rubiks, int rota_type){
    int n;
    for (n=0; n<rota_type; n++) {
        rotate_anticlockwise(Rubiks[2].face);
        anticlockwise(Rubiks, 2);
    }
}

void back_anticlockwise(Faces* Rubiks, int rota_type){
    int n;
    for (n=0; n<rota_type; n++) {
        rotate_anticlockwise(Rubiks[4].face);
        anticlockwise(Rubiks, 4);
    }
}

void right_anticlockwise(Faces* Rubiks, int rota_type){
    int n;
    for (n=0; n<rota_type; n++) {
        rotate_anticlockwise(Rubiks[3].face);
        anticlockwise(Rubiks, 3);
    }
}

void left_anticlockwise(Faces* Rubiks, int rota_type){
    int n;
    for (n=0; n<rota_type; n++) {
        rotate_anticlockwise(Rubiks[1].face);
        anticlockwise(Rubiks, 1);
    }
}

void free_rubiks(Faces* Rubiks){
    free(Rubiks);
}

// recieve the user choose mouvement
int choose_mouvement(){
    int choose, color;
    T_SIDE side;
    printf("\n --------------------------------------------------------------------------------------------- \n");
    color = rand() % ( 13 + 1 )  ;
    c_textcolor(color);
    printf("   1: Front   2: Back   3: Up   4: Down   5: Right  6: Left \n  ");
    color = rand() % ( 13 + 1 )  ;
    c_textcolor(color);
    printf("--------------------------------------------------------------------------------------------- \n");
    printf("Enter number : ");
    scanf("%d", &choose);
    switch(choose){
        case 1: side = FRONT;
        case 2: side = BACK;
        case 3: side = UP;
        case 4: side = DOWN;
        case 5: side = RIGHT;
        case 6: side = LEFT;
    }
    choose = side_to_index(side);
    return choose;
}

// The user choose the type of rotation
void move_rubiks(Faces* Rubiks) {
    int color, choose, mouv,rotate;
    printf("\n --------------------------------------------------------------------------------------------- \n");
    color = rand() % (13 + 1);
    c_textcolor(color);
    printf("   1 : Clockwise    2: Rotation   3: Anticlockwise  \n  ");
    color = rand() % (13 + 1);
    c_textcolor(color);
    printf("--------------------------------------------------------------------------------------------- \n");
    printf("Enter number : ");
    scanf("%d", &choose);

    switch (choose) {
        case 1 :
            mouv = choose_mouvement();
            printf("Enter 1 for quarter-turn and 2 for half-turn ");
            scanf("%d", &rotate);

            switch (mouv) {
                case 1 : front_clockwise(Rubiks, rotate);
                    break;
                case 2: back_clockwise(Rubiks, rotate);
                    break;
                case 3: up_clockwise(Rubiks, rotate);
                    break;
                case 4: down_clockwise(Rubiks, rotate);
                    break;
                case 5: right_clockwise(Rubiks, rotate);
                    break;
                case 6: left_clockwise(Rubiks, rotate);
                    break;
            }
            break;

        case 2:
            printf("\n --------------------------------------------------------------------------------------------- \n");
            color = rand() % (13 + 1);
            c_textcolor(color);
            printf("   1: Horizontale   2: Vertical \n  ");
            color = rand() % (13 + 1);
            c_textcolor(color);
            printf("--------------------------------------------------------------------------------------------- \n");
            printf("Enter number : ");
            scanf("%d", &mouv);

            switch (mouv) {
                case 1: horizontal_rotation(Rubiks);
                    break;
                case 2: vertical_rotation(Rubiks);
                    break;
            }
            break;

        case 3:
            mouv = choose_mouvement();
            printf("Enter 1 for a quarter-turn clockwise rotation and 2 for half a turn ");
            scanf("%d", &rotate);

            switch (mouv) {
                case 1 : front_anticlockwise(Rubiks, rotate);
                    break;
                case 2: back_anticlockwise(Rubiks, rotate);
                    break;
                case 3: up_anticlockwise(Rubiks, rotate);
                    break;
                case 4: down_anticlockwise(Rubiks, rotate);
                    break;
                case 5: right_anticlockwise(Rubiks, rotate);
                    break;
                case 6: left_anticlockwise(Rubiks, rotate);
                    break;
            }
            break;
    }
}

// scramble the rubiks function
void scramble_rubiks(Faces* Rubiks){
    int nbr, nbr2 , rotate, i;
    nbr2 = rand() %50 + 5;
    for (i=0; i < nbr2 ; i ++) {
        nbr = rand() %14;
        switch (nbr) {
            case 1 :
                front_anticlockwise(Rubiks, (rotate = rand() % 2));
                break;
            case 2:
                back_anticlockwise(Rubiks, (rotate = rand() % 2));
                break;
            case 3:
                up_anticlockwise(Rubiks, (rotate = rand() % 2));
                break;
            case 4:
                down_anticlockwise(Rubiks, (rotate = rand() % 2));
                break;
            case 5:
                right_anticlockwise(Rubiks, (rotate = rand() % 2));
                break;
            case 6:
                left_anticlockwise(Rubiks, (rotate = rand() % 2));
                break;
            case 7 : front_clockwise(Rubiks, (rotate = rand() % 2));
                break;
            case 8: back_clockwise(Rubiks, (rotate = rand() % 2));
                break;
            case 9: up_clockwise(Rubiks, (rotate = rand() % 2));
                break;
            case 10: down_clockwise(Rubiks, (rotate = rand() % 2));
                break;
            case 11: right_clockwise(Rubiks, (rotate = rand() % 2));
                break;
            case 12: left_clockwise(Rubiks, (rotate = rand() % 2));
                break;
            case 13: horizontal_rotation(Rubiks);
                break;
            case 14: vertical_rotation(Rubiks);
                break;
        }
    }
}

// Let the user choose the color
int fill_rubiks( Faces* Rubiks ){
    T_SIDE side;
    int line , cases , face , r = 0, b= 0 , g = 0, w = 0, y= 0 ,o = 0 , correct_entry = 0 ;
    char color;
    for (face=0; face < 6 ; face ++) {
        for (line = 0; line < 3; line++) {
            for (cases = 0; cases < 3; cases++) {
                while (correct_entry == 0) {
                    printf("\n Enter color for face %d line %d and case %d : \n", face, line, cases);
                    scanf("%s", &color);
                    switch (color) {
                        case 'R' :
                            r = r + 1;
                            if (r > 9) {
                                printf(" Every red is used,try another color \n");
                                break;
                            } else {
                                printf(" There is %d red left \n", 9 - r);
                                Rubiks[face].face[line][cases] = R;
                                correct_entry = 1;
                                break;
                            }

                        case 'B' :
                            b = b + 1;
                            if (b > 9) {
                                printf(" Every blue is used,try another color \n");
                                break;
                            } else {
                                printf(" There is %d blue left \n", 9 - b);
                                Rubiks[face].face[line][cases] = B;
                                correct_entry = 1;
                                break;
                            }
                        case 'G' :
                            g = g + 1;
                            if (g > 9) {
                                printf(" Every green is used,try another color \n");
                                break;
                            } else {
                                printf(" There is %d green left \n", 9 - g);
                                Rubiks[face].face[line][cases] = G;
                                correct_entry = 1;
                                break;
                            }
                        case 'W' :
                            w = w + 1;
                            if (w > 9) {
                                printf(" Every white is used,try another color \n");
                                break;
                            } else {
                                printf(" There is %d white left \n", 9 - w);
                                Rubiks[face].face[line][cases] = W;
                                correct_entry = 1;
                                break;
                            }
                        case 'Y' :
                            y = y + 1;
                            if (y > 9) {
                                printf(" Every yellow is used,try another color \n");
                                break;
                            } else {
                                printf(" There is %d yellow left \n", 9 - y);
                                Rubiks[face].face[line][cases] = Y;
                                correct_entry = 1;
                                break;
                            }
                        case 'O' :
                            o = o + 1;
                            if (o > 9) {
                                printf(" Every orange is used,try another color \n");
                                break;
                            } else {
                                printf(" There is %d orange left \n", 9 - o);
                                Rubiks[face].face[line][cases] = O;
                                correct_entry = 1;
                                break;
                            }
                        default :
                            printf(" NOPE ! This is NOT a color !! \n");
                    }
                }
                correct_entry = 0;
            }
        }
    }
    return 0;
}



// We did not manage to finish this function
int solve_rubiks(Faces* Rubiks){

    init_rubiks(Rubiks);
    system("start https://www.youtube.com/watch?v=7Ron6MN45LY");

    return 0;
}


// solve rubik function ( not finished )
// here are the functions we created to try to solve the rubi cube


/*
We did a solve function that scramble the rubiks while he is not finised but it's too long for us computer
 int compare_array(Faces* Rubiks){
    int line,cases;
    int a = 0;
    for (line = 0; line < 3; line++) {
        for (cases = 0; cases < 3; cases++) {
            if (Rubiks[0].face[line][cases] == W) {
                a = a + 1;
            }
        }
    }
    for (line = 0; line < 3; line++) {
        for (cases = 0; cases < 3; cases++) {
            if (Rubiks[1].face[line][cases] == O) {
                a = a + 1;
            }
        }
    }
    for (line = 0; line < 3; line++) {
        for (cases = 0; cases < 3; cases++) {
            if (Rubiks[2].face[line][cases] == G) {
                a = a + 1;
            }
        }
    }
    for (line = 0; line < 3; line++) {
        for (cases = 0; cases < 3; cases++) {
            if (Rubiks[3].face[line][cases] == R) {
                a = a + 1;
            }
        }
    }
    for (line = 0; line < 3; line++) {
        for (cases = 0; cases < 3; cases++) {
            if (Rubiks[4].face[line][cases] == B) {
                a = a + 1;
            }
        }
    }
    for (line = 0; line < 3; line++) {
        for (cases = 0; cases < 3; cases++) {
            if (Rubiks[5].face[line][cases] == Y) {
                a = a + 1;
            }
        }
    }
    if ( a == 54 ){
        return 1;
    }
    else {
        return 0;
    }
}

 int solve_rubiks(Faces* Rubiks){
    int finish = 0 , cpt = 0;
    init_rubiks(Rubiks);
    system("start https://www.youtube.com/watch?v=7Ron6MN45LY");
    while (finish == 0){
        scramble_rubiks(Rubiks);
        finish = compare_array(Rubiks);
        cpt = cpt + 1;
    }
    printf("%d",cpt );
    return 0;
}





We also did many function to situate us to solve the rubiks

T_COLOR color_cote_side(Faces* Rubiks, int face, int line , int cases ){
    T_COLOR color;
    int nbr_color;
    int n_face, n_line  ,n_cases;
    switch(line){
        case 0:
            n_line = 2-line;
            n_cases = cases;
            switch(face){
                case 5: n_face = 2;
                    break;
                case 0: n_face = 1;
                    break;
                default : n_face = 0;
                    break;
            }
            break;
        case 1:
            n_cases = 2-cases;
            n_line = line;
            switch(cases) {
                case 0:
                    switch (line) {
                        case 0: n_face = 1;
                            break;
                        case 5: n_face = 3;
                            break;
                        default: n_face = face -1;
                            break;
                    }
                    break;
                case 2:
                    switch (line) {
                        case 0: n_face = 3;
                            break;
                        case 5: n_face = 1;
                            break;
                        default: n_face = face +1;
                            break;

                    }
                    break;
            }
            break;
        case 2:
            n_line = 2-line;
            n_cases = cases;
            switch(face){
                case 5: n_face = 1;
                    break;
                case 0: n_face = 2;
                    break;
                default : n_face = 0;
                    break;
            }
            }

        color = Rubiks[n_face].face[n_line][n_cases];
        return color;
        }
// HERE I WANT TO DIE
int cote_face(Faces* Rubiks, int face, int line , int cases){
    T_COLOR color;
    int nbr_color;
    int n_face, n_line  ,n_cases;
    switch(line){
        case 0:
            n_line = 2-line;
            n_cases = cases;
            switch(face){
                case 5: n_face = 2;
                    break;
                case 0: n_face = 1;
                    break;
                default : n_face = 0;
                    break;
            }
            break;
        case 1:
            n_cases = 2-cases;
            n_line = line;
            switch(cases) {
                case 0:
                    switch (line) {
                        case 0: n_face = 1;
                            break;
                        case 5: n_face = 3;
                            break;
                        default: n_face = face -1;
                            break;
                    }
                    break;
                case 2:
                    switch (line) {
                        case 0: n_face = 3;
                            break;
                        case 5: n_face = 1;
                            break;
                        default: n_face = face +1;
                            break;

                    }
                    break;
            }
            break;
        case 2:
            n_line = 2-line;
            n_cases = cases;
            switch(face){
                case 5: n_face = 1;
                    break;
                case 0: n_face = 2;
                    break;
                default : n_face = 0;
                    break;
            }
    }
    return n_face;
}


int** coord(Faces* Rubiks, T_COLOR choose_color) {
    int face, line, cases,i ;
    int a = 0, b = 0;
    int **coord_arrays;
    coord_arrays = (int **) malloc(9 * sizeof(int *));
    for (i = 0; i < 3; i++) {
        coord_arrays[i] = (int *) malloc(3 * sizeof(int));

        for (face = 0; face < 6; face++) {
            for (line = 0; line < 3; line++) {
                for (cases = 0; cases < 3; cases++) {
                    if (Rubiks[face].face[line][cases] == choose_color) {
                        coord_arrays[a][b] = face;
                        coord_arrays[a][b + 1] = line;
                        coord_arrays[a][b + 2] = cases;
                        a = a + 1;
                        b = 0;
                    }
                }
            }
        }
        return coord_arrays;
    }
}

void have_angle(Faces* Rubiks, int** coord_arrays) {
    int cases, coord;
    int a = 0;
    int **coord_arrays_angle;
    coord_arrays_angle = (int **) malloc(9 * sizeof(int *));
    for (cases = 0; cases < 3; cases++) {
        coord_arrays_angle[cases] = (int *) malloc(3 * sizeof(int));
    }
    for (cases = 0; cases < 3; cases++) {
        coord_arrays_angle[cases] = (int *) malloc(3 * sizeof(int));
    }

    for (cases = 0; cases < 9; cases++) {
        if ((coord_arrays[cases][1] == 0 || coord_arrays[cases][1] == 2) &&
            (coord_arrays[cases][2] == 0 || coord_arrays[cases][2] == 2)) {
            coord_arrays_angle[a] = coord_arrays[cases];
            a = a + 1;
        }
    }
}

 void white_cross(Faces* Rubiks){
    int i, n_face,cote, c;
    int** white_coord_arrays ;
    white_coord_arrays = coord(Rubiks, W);
    for (i = 0; i < 9; i++) {
        if (white_coord_arrays[i][0] == 5){
            break;
        }
        if (white_coord_arrays[i][0] == 0){
            if (Rubiks[5].face[white_coord_arrays[i][1]][white_coord_arrays[i][2]] == W){
                while(Rubiks[5].face[white_coord_arrays[i][1]][white_coord_arrays[i][2]] == W){
                    up_clockwise(Rubiks, 1);
                }
            }
            else {
                n_face = cote_face( Rubiks, white_coord_arrays[i][0], white_coord_arrays[i][1] , white_coord_arrays[i][2] );
                switch(n_face){
                    case 0 :
                        front_clockwise(Rubiks, 2);
                        break;
                    case 1:
                        left_clockwise(Rubiks, 2);
                        break;
                    case 2:
                        down_clockwise(Rubiks, 2);
                        break;
                    case 3:
                        right_clockwise(Rubiks, 2);
                        break;
                    case 4:
                        up_clockwise(Rubiks, 2);
                        break;
                    case 5:
                        back_clockwise(Rubiks, 2);
                        break;
                }
            }
        }
        else {
            if (Rubiks[5].face[white_coord_arrays[i][1]][white_coord_arrays[i][2]] == W){
                while(Rubiks[5].face[white_coord_arrays[i][1]][white_coord_arrays[i][2]] == W){
                    up_clockwise(Rubiks, 1);
                }
            }
            else {
                for (i = 0; i < 9; i++){
                    for (c = 0; c < 9; c++){
                        if ( white_coord_arrays[i][1] =   )
                    }

*/











