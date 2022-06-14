#include <stdio.h>

// Definition of the type need
typedef enum { FRONT, BACK, UP, DOWN, RIGHT, LEFT } T_SIDE ;
typedef enum { R, B, G, W, Y, O, LG } T_COLOR ;

// Definition of the Structure for the Rubiks
typedef struct Faces{
    T_SIDE type_face ;
    T_COLOR face[3][3] ;
}Faces;


// Prototype of function
int select_color(T_COLOR color);

int side_to_index(T_SIDE side);

Faces* create_rubiks() ;

void init_rubiks(Faces* Rubiks);

void display_rubiks(Faces* Rubiks);

void blank_rubiks(Faces* Rubiks);

void rotate_clockwise(T_COLOR (face)[3][3] );

void clockwise(Faces* Rubiks, int face);

void up_clockwise(Faces* Rubiks, int rota_type);

void down_clockwise(Faces* Rubiks, int rota_type);

void front_clockwise(Faces* Rubiks, int rota_type);

void back_clockwise(Faces* Rubiks, int rota_type);

void right_clockwise(Faces* Rubiks, int rota_type);

void left_clockwise(Faces* Rubiks, int rota_type);

void horizontal_rotation(Faces* Rubiks);

void rotate_anticlockwise(T_COLOR (face)[3][3]);

void anticlockwise(Faces* Rubiks, int face);

void up_anticlockwise(Faces* Rubiks, int rota_type);

void down_anticlockwise(Faces* Rubiks, int rota_type);

void front_anticlockwise(Faces* Rubiks, int rota_type);

void back_anticlockwise(Faces* Rubiks, int rota_type);

void right_anticlockwise(Faces* Rubiks, int rota_type);

void left_anticlockwise(Faces* Rubiks, int rota_type);

void free_rubiks(Faces* Rubiks);

int choose_mouvement();

void move_rubiks(Faces* Rubiks);

void scramble_rubiks(Faces* Rubiks);

int fill_rubiks( Faces* Rubiks );

int solve_rubiks(Faces* Rubiks);


