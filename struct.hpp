#pragma once 
#include "SDL.h"
#include "SDL_image.h"
#include <list>
#include <iostream>


constexpr int NUMBER_OF_PIECES = 12 ;

constexpr int CELL_DES = 90 ;
constexpr int PIECE_WIDTH = 70;
constexpr int PIECE_HEIGHT = 70;
constexpr int PIECE_SPACE = 20;
constexpr int PIECE_VOID = 10;

constexpr int WIDTH = 1080;
constexpr int HEIGHT = 720;
constexpr int GRID = 8;     
constexpr int TGRID = 7;   


constexpr int UPGRADED_RED_IMG_W = 243;
constexpr int UPGRADED_RED_IMG_H = 236;

constexpr int NORMAL_RED_IMG_W = 230; 
constexpr int NORMAL_RED_IMG_H = 237;

constexpr int UPGRADED_BLACK_IMG_W = 235;
constexpr int UPGRADED_BLACK_IMG_H = 235;

constexpr int NORMAL_BLACK_IMG_W = 235;
constexpr int NORMAL_BLACK_IMG_H = 243;


constexpr int PIECE_IMG_X_250 = 250;
constexpr int PIECE_IMG_Y_250 = 250;
constexpr int PIECE_IMG_X_0 = 0; 
constexpr int PIECE_IMG_Y_0 = 0;


constexpr int MOVE_DES = 498;
constexpr int MOVE_X = 550;
constexpr int MOVE_Y = 0;

constexpr int FOCUS_W = 499 ;
constexpr int FOCUS_H = 499 ; 
constexpr int FOCUS_X = 0 ;
constexpr int FOCUS_Y = 0 ;


constexpr int MOVE_SPACE = 15 ;
constexpr int MOVE_VOID = 7 ;
constexpr int UPGRADE_PIECE_DIRECTION = 0;

constexpr int direction_move_1 = 1 ;
constexpr int direction_move__1 = -1 ;


  

/**
 *   int x , y ;
 *   default () = > x = -1 , y = - 1 
 *   SetCord ( int x , int y ) 
 */
struct Cordinates 
{

    int x , y ;

    void Default ()
    {
        x = -1 ;
        y = -1 ;
    }

    void SetCord ( int x , int y )
    {
         this->x = x ;
         this->y = y ;
    }

};

/**
 *   int ( x , y ) cords , 
 *
 *   id ( takes the id of the piece if it's there ) ,
 *
 *   empty ( true or false ) .
 *
 *   default () => set the cell attr into default 
 *
 *   SetCell ( int x , int y , char id ) => set values of the cell from the given parameteres and put empty = false 
 */
struct cell 
{
    Cordinates cell_cord ;
    int num ;
    bool empty  ;
    char id  ;

/**
 * default () => set the cell attr into default 
 */
    void Default()
    {
        empty = true ;
        cell_cord.Default() ;
        num = -1 ;
        id = 'x' ;
    }

/**
 * SetCell ( int x , int y , char id ) => set values of the cell from the given parameteres and put empty = false   
 */
    void SetCell( Cordinates cell_cord , char id , int num )
    {
        empty = false ;
        this->num = num ;
        this->cell_cord = cell_cord ;
        this->id = id ;
    }
    
} ;


void ChangeTurn ( char &id ) ;

/**
 * return rect
 * only change the x , y values 
 */
SDL_Rect Cords_Into_Rect ( SDL_Rect temp_rect , Cordinates temp_cord ) ;

/**
 * return Cordinates 
 * change cords x,y to pixels cords 
 */
Cordinates Draw_Cord ( Cordinates temp_cord ) ;

/**
 * return Cordinates 
 * change pixels x,y to BOARD cords 
 */
Cordinates Board_Cord ( Cordinates temp_cord ) ;

/**
 * return Cordinates 
 * Change pixels x,y from mouse click to fix numbers to the board 
 * example ( x = 50 , y = 140 )  ==> ( x = 0 , y = 1 ) 
 */
Cordinates Mouse_To_BOARD_Cord ( Cordinates temp_cord ) ;


/**
 * return Cordinates 
 * Change BOARD x,y To Mouse Cords  
 */
Cordinates BOARD_To_MOUSE_Cord ( Cordinates temp_cord ) ;


bool AllowMove ( int x , int dir ) ;
bool AllowValue ( int x ) ;