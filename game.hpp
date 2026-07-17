#include "board.hpp"
#include "track.hpp"



class GAME
{

    private :

      SDL_Renderer * renderer = nullptr ;
      SDL_Window * window = nullptr ;
      
      BOARD * board = nullptr ;
      Tracker * track = nullptr ;
      Movement * movement = nullptr ; 
      Take * take = nullptr ;
  
      SDL_Event event ;
      char turn = 'r' ;

      

      bool run = true ;
      bool piece_clicked = false ;
      bool take_advantage = false ;
      int advantage_num ;

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

void Launcher () ;