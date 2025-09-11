#pragma once
#include "piece.hpp"


extern SDL_Color yellow;
extern SDL_Color green;
extern SDL_Color black;
extern SDL_Color white;
extern SDL_Color red;




struct part {

    int w , h ;

};

struct cell {

   
    int x , y  ; // cord 
    bool empty ; 
    char c ;  // team id 
    int n ; // number of the piece in the team 

    void Default ()
    {
        char tc;
        empty = true ;
        c = tc ;
        n = 0 ;
    }

    void Set( int x , int y , bool empty , char c , int n )
    {
         this->x = x ;
         this->y = y ;
         this->empty = empty ;
         this->c = c ;
         this-> n = n ;
    }
};

struct Team{

    char ID ;
    Piece * Pieces = new  Piece [N] ; 

};

class Tracker{

    private :

      SDL_Rect track_rec ;
      int pa = -3 ,
          tdir = -3 ,
          tx = -1 ,
          ty = -1 ;
      SDL_Surface * sur = nullptr ;
      int fly[4] =  { -1 , -1 , -1 , -1 } ;
    public : // track the excact piece 
      
      void TrackPieceCord ( int &x , int &y ) ;
/*    char TeamIdent ( cell temp_board[grid][grid] ) { return temp_board[y_cord][x_cord].c ; }
      int PieceNumberIdent ( cell temp_board[grid][grid] ) { return temp_board[y_cord][x_cord].n ; }
*/
    public : // handle piece move

      int x_cord ,
          y_cord ;

      int CordCalcu ( int x ) ;
      void Possible_Movement(  SDL_Renderer * r   , Piece * temp_Piece , cell temp_board[grid][grid] , int n ) ;
      void Movement_Direction ( SDL_Renderer * r   , int n ) ;
      void ShowMovement ( SDL_Renderer * r  ,cell temp_board [grid][grid] ) ;

      bool AllowedMove ( int n ) ;
      bool AllowedMoveInBoard ( cell temp[grid][grid] , int x , int y ) ;
      bool CorrectCord () ;
      void ClearMoveFromBoard ( SDL_Renderer * r ) ;
      void TDraw ( SDL_Renderer * r , SDL_Color color ) ;
      void DefaultTrack () ;
      void DrawPause( SDL_Renderer * r , SDL_Color color ) ;

      bool PossibleUpgrade ( int y , int dir ) ;


      bool ClickedMove ( int &x , int &y ) ;


      void HandleFly ( cell  temp_board [grid][grid] ) ;


      /*void Case2Move( SDL_Renderer * r , SDL_Color color ) ;*/
      
};