#pragma once 
#include "struct.hpp"
#include "take.hpp"

class Movement 
{
    private :      

      SDL_Surface * move_surface = nullptr ;
      
     /* ### Highlights ### */ 
     SDL_Rect Move_rect ;
     SDL_Rect draw_rect ;
     /* ### ### */

     Cordinates curr_cords ;

      int y ,
          x1 , x2 , x3 , x4 ;

      int direction ,
          move_case ;
      
      bool take = false ;
          
    public :

     Movement() ;
     void Move_Draw ( SDL_Renderer * r , SDL_Texture * t ) ;
     void ScanBoard_ForMove( Cordinates temp_cord , cell (&board)[GRID][GRID] , int direction  ) ; 
     void Reset_Move () ;
     bool MoveCLicked ( Cordinates temp_cords ) ;
     Cordinates GetCordinates () ;


     public :

     void TakeMove ( Cordinates change_cord , int direction , SDL_Renderer * r , SDL_Texture * t ) ;

     bool TakeMove_Clicked ( Cordinates temp ) ;
     int getTakeDirection () ;

};