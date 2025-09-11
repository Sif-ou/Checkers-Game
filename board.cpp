#include "board.hpp"

SDL_Rect board_rec ;
const int w = 7 ; 
const int c = 7 ;

void board::SetBoard()
{
   int n = 1 , k = 1 ;
     

    for ( int i = 0 ; i < grid ; i++ )
    {
        for ( int j = 0 ; j < grid ; j++ )
        {
            BOARD[i][j].x = n ;
            BOARD[i][j].y = k ;
            n++; 
        }

        n = 1 ;
        k++;

    }

     for ( int i = 0 ; i < grid ; i++ )
      for ( int j = 0 ; j < grid ; j++ )
       BOARD[i][j].empty = true ;

}
void board::Render_Board(  SDL_Renderer * r  ) //SDL_Texture * t )
{
/*
    board_rec.x = VIDE ;
    board_rec.y = VIDE ;
    board_rec.w = 680 ;
    board_rec.h = 680 ;
    s = IMG_Load ( "assets/board.png" ) ;
    t = SDL_CreateTextureFromSurface ( r , s ) ;
    SDL_FreeSurface( s ) ;
    SDL_RenderCopy ( r , t , NULL , &board_rec ) ;

   rec.h = D ;
   rec.w = D ;
   rec.x = 20 ;
   rec.y = 20 ;
*/
   rec.h = D ;
   rec.w = D ;
   rec.x = 20 ;
   rec.y = 20 ;

   SDL_SetRenderDrawColor ( r , 255 , 255 , 255 , SDL_ALPHA_OPAQUE ) ;

    for ( int i = 0 ; i <= c ; i++ )
    {
      for ( int j = 0 ; j <= w ; j++ )
       {
          SDL_RenderDrawRect ( r , &rec ) ;
          rec.x += D ;  
       }

       rec.x = 20 ;
       rec.y += D ;
    }

   SetBoard() ;
   
}
//


void board::InitTeam( SDL_Renderer * r )
{
     SetTeam() ;
     PieceInBoard( r ) ;  
}
void board::SetTeam()
{
    TeamR = new Team ;
    TeamB = new Team ; 

    TeamR->ID = 'r' ;
    TeamB->ID = 'b' ;

    PiecePlacment ( TeamR , 1 ) ;
    PiecePlacment ( TeamB , -1 ) ;
}
//

void board::PiecePlacment(  Team * Temp , int direction  )
{
    int co = 0 ,
        n_row_min ,
        n_row_max ;

    if ( direction == 1 )
    {
        n_row_max = 2 ;
        n_row_min = 0 ;
    }
    else
    {
        n_row_max = 7 ;
        n_row_min = 5 ;
    }


       for ( int i =  n_row_min ; i <= n_row_max ; i++ )
         {

           for ( int j = 0 ; j < grid ; j++ )
           {

              if ( i % 2 == 0 )
              {

                 if ( j % 2 == 1 )
                 {
                    Temp->Pieces[co].InitPiece( j , i , Temp->ID , direction , Temp->ID ) ; 
                    BOARD[i][j].Set ( j , i , false , Temp->ID , co ) ;
                    co++ ;
                 }


              }
              else 
              {

                  if ( j % 2 == 0 )
                  {
                    Temp->Pieces[co].InitPiece( j , i , Temp->ID , direction , Temp->ID ) ;
                    BOARD[i][j].Set ( j , i , false , Temp->ID , co ) ;
                    co++ ;
                  }


              }

                     
           }

         }

}
void board::PieceInBoard ( SDL_Renderer * r )
{
    for ( int i = 0 ; i < N ; i++ )
     {
        TeamR->Pieces[i].DrawPiece ( r ) ;
        TeamB->Pieces[i].DrawPiece ( r ) ;
     }
}
//

void board::Tracker_Board (  SDL_Renderer * r  )
{
   px = track->x_cord ;
   py = track->y_cord ;
    
   if ( BOARD[track->y_cord][track->x_cord].c == 'r'  )
      {
        piece_clicked = true ;
        track->DrawPause ( r , yellow ) ;
        track->Possible_Movement ( r  , TeamR->Pieces , BOARD , BOARD[track->y_cord][track->x_cord].n ) ;
      }
        
   else if ( BOARD[track->y_cord][track->x_cord].c == 'b'  )
       {
         piece_clicked = true ;
         track->DrawPause ( r , yellow ) ;
         track->Possible_Movement ( r  , TeamB->Pieces , BOARD , BOARD[track->y_cord][track->x_cord].n ) ;
       }
      else
         piece_clicked = false ;
      
}
bool board::ClickTracker( int x , int y )
{

 track->TrackPieceCord( x , y ) ;

    if ( BOARD[track->y_cord][track->x_cord].empty == false  && track->CorrectCord () == true )
     return true ;
    else
      return false ;

   return false ;
}
void board::ClearTracker( SDL_Renderer * r )
{
    track->ClearMoveFromBoard ( r ) ;
}
void board::SetTrackerDefault()
{
   track->DefaultTrack () ;
}
//

void board::CheckCord( int x , int y )
{
   move_clicked = track->ClickedMove ( x , y ) ;
}

void board::NewPieceCord (SDL_Renderer * r )   
{

int n ;
   

    if ( BOARD[py][px].c == 'r' )
    {
       turn = false ;
       n = BOARD[py][px].n ;
       TeamR->Pieces[BOARD[py][px].n].RemovePiece( r ) ;
       TeamR->Pieces[BOARD[py][px].n].ChangePieceCord ( track->x_cord , track->y_cord ) ;
  
       if ( track->PossibleUpgrade( track->y_cord  , TeamR->Pieces[n].Direction() ) == true )
         {
            printf ( " direction set to 0 \n" ) ;
            TeamR->Pieces[BOARD[py][px].n].SetDirection ( 0 ) ; 
         }
       
       TeamR->Pieces[BOARD[py][px].n].DrawPiece( r ) ;
       
       BOARD[py][px].Default() ;
       BOARD[track->y_cord][track->x_cord].Set( track->x_cord , track->y_cord , false , 'r' , n ) ;
    }
    else
    {
       turn = true ;
       n = BOARD[py][px].n ;
       TeamB->Pieces[BOARD[py][px].n].RemovePiece( r ) ;
       TeamB->Pieces[BOARD[py][px].n].ChangePieceCord ( track->x_cord , track->y_cord ) ;

       if ( track->PossibleUpgrade( track->y_cord , TeamB->Pieces[n].Direction() ) == true )
       {
        printf ( " direction set to 0 \n" ) ; 
        TeamB->Pieces[BOARD[py][px].n].SetDirection ( 0 ) ;
       }
         

       TeamB->Pieces[BOARD[py][px].n].DrawPiece( r ) ;
       BOARD[py][px].Default() ;
       BOARD[track->y_cord][track->x_cord].Set( track->x_cord , track->y_cord , false , 'b' , n ) ;
    } 


}