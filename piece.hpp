#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "cmath"
#define D 85
#define SQUARE 62.125
#define VIDE 20 
#define grid 8 
#define N 12


const float PI = 3.14 ;



 class Piece{


     private : 

        int w = D / 2 ,
            h = D / 2 ;

        int dir ; 
        bool alive ;
    

     private : 

       SDL_Rect pos ;
       SDL_Color p_color ;


     public :
       char id ;
       
       virtual void InitPiece ( int x , int y , char co , int direction , char color );
       int Direction () { return dir ; } 
       void SetDirection ( int n ) ; 
       SDL_Color SetPieceColor( char color ) ;


       void DrawPiece( SDL_Renderer * r  ) ;
       void RemovePiece ( SDL_Renderer * r ) ;

       void DeadPiece () ;

       void ChangePieceCord ( int x , int y ) ;



 };

void DrawO ( SDL_Renderer * r , SDL_Color te , float x , float y );

void FillO (SDL_Renderer * r , SDL_Color te , float x , float y) ;


void upO (SDL_Renderer * r ,  float x , float y) ;