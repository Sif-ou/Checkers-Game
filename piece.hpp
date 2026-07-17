#pragma once 
#include "struct.hpp"

class Piece
{
    private :

      Cordinates piece_cord ;
      int direction ;
      int num ;
      char id ;      
      bool alive ; 

    public :
       
       Piece ( Cordinates piece_cord , char id , int direction , int num ) ;
       
       void KillPiece () ;
       bool isAlive () ;

       Cordinates GetCordinates () ;
       int GetDirection () ;
       int GetNum() ;
       void KingUpgrade() ;

       
       void SetCordinates ( Cordinates piece_cord ) ;
       void SetDirection ( int direction ) ;
};


/**
 *   int Num_Of_Pieces  ; 
 *   char id ;
 *   Piece * Pieces [NUMBER_OF_PIECES] ; 
 *   SDL_Rect Normal_Piece_img ,
 *   SDL_Rect Upgraded_Piece_img ;
 */
struct Team
{

    int Num_Of_Pieces ;
    int direction ;

    char id ;
    Piece * Pieces [NUMBER_OF_PIECES] ;

    SDL_Rect Normal_Piece_img ,
             Upgraded_Piece_img ;


    void InitTeam( char id , int direction ) ;
    ~Team() ;

};
