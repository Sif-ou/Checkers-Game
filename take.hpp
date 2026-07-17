#pragma once 
#include "struct.hpp"
#include "piece.hpp"

struct TakeDirection 
{
   private :
     Cordinates cords ,
                opp_cord ,
                change_cord ;
     int num ;

     public :
   

     bool left , right , top , bottom ;

    void Default ()
    {
         cords.x = -1 ;
         cords.y = -1 ;
         opp_cord.x = -1 ;
         opp_cord.y = -1 ;
         change_cord.x = -1 ;
         change_cord.y = -1 ; 

         left = 0 ;
         right = 0 ;
         top = 0 ;
         bottom  = 0 ;
         
    }
    
    void SetTake ( Cordinates cords , Cordinates opp_cord , Cordinates change_cord  )
    {
        this->cords = cords ;
        this->opp_cord = opp_cord ;
        this->change_cord = change_cord ;
    }

    void SetTakeInfo ( int num ) 
    {
        this->num = num ;
    }

    void SetDirection ( bool right ,  bool left )
    {
        this->right = right ;
        this->left = left ;
    }

    void SetDirectionKing ( bool right , bool left , bool top , bool bottom )
    {
        this->right = right ;
        this->left = left ;
        this->top = top ;
        this->bottom = bottom ;
    }

    Cordinates getCords ()  { return cords ; } 
    Cordinates getEnemyCords() { return opp_cord ; } 
    Cordinates getChangeCords() { return change_cord ; } 
    int getDirectionKing () ;
    int getDirection () 
    {
        int n = 0 ;


        n = ( right == true ? direction_move_1 : UPGRADE_PIECE_DIRECTION ) ;
        n = (  left == true ? n+2: UPGRADE_PIECE_DIRECTION ) ;

        return n ;
    }

    int getNum () { return num ; }  

};


class Take
{

    private :

     std::list<TakeDirection> take_list  ;

    public :

    void ScanBoard ( cell (&board)[GRID][GRID] , Team * temp_team ) ;

    /**
     * scan for piece only 
     * usually used when the first take is played 
     */
    void ScanPiece ( cell (&board)[GRID][GRID] , Team * temp_team , int num ) ;


    std::list<TakeDirection> getTakeList () ;
    int getTakeNum ( Cordinates temp ) ;
    
    Cordinates getCord ( int num ) ;
    Cordinates getChangeCord ( int num ) ;
    Cordinates getEnemyCord ( int num ) ;
    int getDirection ( int num ) ;

    bool isTakeEmpty() ;
    void ResetTakes () ;

};