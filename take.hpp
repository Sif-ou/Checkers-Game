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
   

     bool left , right ; // normal 

     bool top_left , top_right , bottom_left , bottom_right ;

    void Default () ;

    
    void SetTake ( Cordinates cords , Cordinates opp_cord , Cordinates change_cord  ) ;

    void SetTakeInfo ( int num ) ;


    void SetDirection ( bool right ,  bool left ) ;

    void SetDirectionKing ( bool top_left  , bool top_right , bool bottom_left , bool bottom_right  ) ;

    

    Cordinates GetCords () ;
    Cordinates GetEnemyCords() ;
    Cordinates GetChangeCords() ;
    int getDirectionKing () ;
    int getDirection () ;

    int GetNum () ; 

};


class Take
{

    private :

     std::list<TakeDirection> take_list  ;

    public :

    void ScanBoard ( cell (&board)[GRID][GRID] , Team * temp_team ) ;

    /**
     * scan for piece only 
     */

    void Scan_Advantage ( cell (&board)[GRID][GRID] , Team * temp_team , int peice_num ) ;


    std::list<TakeDirection> getTakeList () ;
    int getTakeNum ( Cordinates temp ) ;
    
    Cordinates getCord ( int num ) ;
    Cordinates getChangeCord ( int num ) ;
    Cordinates getEnemyCord ( int num ) ;
    int getDirection ( int num ) ;

    bool isTakeEmpty() ;
    void ResetTakes () ;



    void TestFunc ()
    {
        printf ( " here is all informations of the take list : \n") ;
        printf ( "######################################\n") ;
        for ( auto& temp_take : take_list )
        {
            printf("piece forced to take %d \n" , temp_take.GetNum() ) ;
            printf("left : %d \n" , temp_take.left ) ;
            printf("right : %d \n" , temp_take.right ) ;
            printf ( "######################################\n") ;
        }
    }

};