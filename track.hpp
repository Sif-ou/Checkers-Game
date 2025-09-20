#pragma once
#include "piece.hpp"


extern SDL_Color yellow;
extern SDL_Color green;
extern SDL_Color black;
extern SDL_Color white;
extern SDL_Color red;

struct cord {

    int x , y ;
    int x_parametre ;



    struct cord * next ;

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
    int pieces_left ;
    Piece * Pieces = new  Piece [N] ; 

};


class Tracker{

    private :

      SDL_Rect track_rec ;
      int tdir = -3 ,
          tx = -1 ,
          ty = -1 ,
          tpa ;
      int fly[4] =  { -1 , -1 , -1 , -1 } ;

      cord * ForecedTakeSaver = nullptr ;


    public : // track the excact piece 
      
      void TrackPieceCord ( int &x , int &y ) ;
/*    char TeamIdent ( cell temp_board[grid][grid] ) { return temp_board[y_cord][x_cord].c ; }
      int PieceNumberIdent ( cell temp_board[grid][grid] ) { return temp_board[y_cord][x_cord].n ; }
*/
    public : // handle piece move

      int x_cord ,
          y_cord ;

      int pa = -3 ;

      

      void Possible_Movement(  SDL_Renderer * r   , Piece * temp_Piece , cell temp_board[grid][grid] , int n ) ;
      void Movement_Direction ( SDL_Renderer * r   , int n ) ;
      void ShowMovement ( SDL_Renderer * r  ,cell temp_board [grid][grid] ) ;

    
      bool CorrectCord () ;
      void ClearMoveFromBoard ( SDL_Renderer * r ) ;
      void DefaultTrack () ;

      bool PossibleUpgrade ( int y , int dir ) ;


      bool ClickedMove ( int &x , int &y ) ;


      void HandleFly ( cell  temp_board [grid][grid] ) ;

      void VerfieTakeCondPiece (  Team * temp_team , cell  temp_board [grid][grid] ) ;

      bool ForcedTake ( Piece * temp_piece , cell  temp_board [grid][grid] , int n ) ;
      bool CorrectTake ( cell temp_board [grid][grid] , int x , int y , char id ) ;
      int CheckDir( int x ) ;

      cord * ScanTeam_ForTakes ( cell temp_board[grid][grid] , Team * temp_team  ) ;
      bool TakePiece_Cord ( Piece * temp_piece , int n , int &x , int &y ) ;
      int EnemyTakePiece ( int x , int y , int direction , char id ,cell temp_board[grid][grid] ) ;
      
};

int CordCalcu ( int x ) ;
bool AllowedMove ( int n ) ;
bool AllowedMoveInBoard ( cell temp[grid][grid] , int x , int y ) ;
void DrawPause( SDL_Renderer * r , SDL_Color color , int x , int y ) ;
void TDraw ( SDL_Renderer * r , SDL_Color color , int x , int y ) ;

