#include "track.hpp"


class board {

     private : 

        SDL_Rect rec  ;
        SDL_Surface * s = nullptr ; 
        Team * TeamR = nullptr ;
        Team * TeamB = nullptr ;
        cell  BOARD[grid][grid]  ;  
        Tracker * track = new Tracker ;

        int px , py ;
       

        bool turn = false ;
      

        
     public :

        bool piece_clicked = false ;
        bool move_clicked = false ;
        bool upgrade = false ;

       void Render_Board ( SDL_Renderer * r  ) ;
       void SetBoard () ;       
       //

       void InitTeam( SDL_Renderer * r ) ;
       void SetTeam() ;
       //

       void PiecePlacment(  Team * Temp , int direction ) ;
       void PieceInBoard( SDL_Renderer * r ) ;
       //

       void Tracker_Board (  SDL_Renderer * r );
       bool ClickTracker ( int x , int y ) ;
       void SetTrackerDefault () ;
       void ClearTracker ( SDL_Renderer * r ) ;
       //       

       void CheckCord ( int x , int y ) ;

       void NewPieceCord ( SDL_Renderer * r ) ;

       bool PieceToDam () ;


};