#include "board.hpp"
#include "track.hpp"



class GAME
{

    private :

      SDL_Renderer * renderer = nullptr ;
      SDL_Window * window = nullptr ;
      SDL_Texture * texture = nullptr ;
      
      BOARD * board = nullptr ;
      Tracker * track = nullptr ;
      Movement * movement = nullptr ; 
      Take * take = nullptr ;
  
      SDL_Event event ;
      char turn = 'r' ;
      Team * curr_team = nullptr ;
      

      bool run = true ;
      bool piece_clicked = false ;

    public : 

     /* ### Mouse Cordinates ### */
     int x_cord , y_cord ;
     /* ###### */
     


     void Init () ;
     void Clear () ;
     void Present () ;
     void Leave () ;
     void Event () ;
     bool isRunning () ;
     void Board() ;
     void BoardUpdate () ;
     void ChangeTurn() ;
};

void GAME_START () ;