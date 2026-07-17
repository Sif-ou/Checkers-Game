#pragma once 
#include "struct.hpp"
#include "take.hpp"

class Movement 
{
    private :      

      SDL_Texture * move_texture = nullptr ; 
      
     /* ### Highlights ### */ 
     SDL_Rect Move_rect ;
     SDL_Rect draw_rect ;
     /* ### ### */

     Cordinates curr_cords ;

      int y ,
          x1 , x2 , x3 , x4 ;

      int direction ,
          move_case ,
          draw_case ;
      
      bool Kingtake = false ;
      int KingMove [3] ;
          
    public :

     Movement( SDL_Renderer * r ) ;
     void Move_Draw ( SDL_Renderer * r  ) ;
     void ScanBoard_ForMove( Cordinates temp_cord , cell (&board)[GRID][GRID] , int direction  ) ; 
     void Reset_Move () ;
     bool MoveCLicked ( Cordinates temp_cords ) ;
     Cordinates GetCordinates () ;

     void DeleteMovement () ;
     public :

     void TakeMove ( Cordinates change_cord , int direction , Cordinates* array , SDL_Renderer * r ) ;

     bool TakeMove_Clicked ( Cordinates temp ) ;
     int getTakeDirection () ;
     int* getKingMove () ;

};