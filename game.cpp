#include "game.hpp"

double elapsed , frametime ;
int x_cord , y_cord ;
int framerate ;
bool f = false ;

void GAME::Init()
{
    if ( SDL_Init ( SDL_INIT_EVERYTHING) < 0 )
     std:: cout << " Error Can't INIT // " << SDL_GetError() ;
    else
     {
         w = SDL_CreateWindow ( "Checkers" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WIDTH , HEIGHT , f ) ;
          if ( !w )
           std:: cout << " Can't Create Window " << SDL_GetError() ;
          else
          {
            r = SDL_CreateRenderer ( w  , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ) ; 
             
             if ( !r )
              std:: cout << " Can't Create Renderer " << SDL_GetError() ; 
             else
              std:: cout << " INIT : " << std:: endl 
                         << " Window Created  " << std:: endl 
                         << " Renderer Created " << std:: endl ;
          }
       }

       /*SDL_Rect test_rec , postest ;
       test_rec.w = 213 ;
       test_rec.h = 234 ;
       test_rec.x = 0 ;
       test_rec.y = 0 ;
       postest.x = 1100 ;
       postest.y = 400 ;
       postest.w = 100 ;
       postest.h = 100 ;

       SDL_Surface * surface = IMG_Load ( "assets/move.png") ;
       t = SDL_CreateTextureFromSurface ( r , surface ) ;
       SDL_RenderCopy ( r , t , &test_rec , &postest) ; */
}

void GAME::InitBoard()
{
  if ( !b )
   printf ( " error in init the board \n" ) ;
  else
  {
   
    b->Render_Board( r ) ;
     if ( !b )
      printf ( " error in redering the board \n" ) ;
     else 
       {
         b->InitTeam( r ) ;
          if ( !b )
           printf ( " error in inti Teams \n" ) ; 
       }

  }



}

void GAME::Clear()
{
    SDL_RenderClear( r ) ;
}


void GAME::ClearTex()
{
   
}

void GAME::Present()
{
  SDL_RenderPresent( r ) ;
}

void GAME::Leave()
{
    SDL_RenderClear(r) ;
    SDL_DestroyRenderer(r) ;
    SDL_DestroyWindow( w ) ;
    SDL_Quit() ;
}

void GAME::Event()
{
    SDL_Event e ;

     while ( SDL_PollEvent ( &e ) )
     {
         switch ( e.type )
         {
             case SDL_QUIT : 
                exit = true ; 
              break;


              case SDL_MOUSEBUTTONDOWN : 
                
               SDL_GetMouseState ( &x_cord , &y_cord  ) ;

               if ( b->piece_clicked == true )
               {
                 b->ClearTracker ( r ) ;
                 b->CheckCord( x_cord , y_cord ) ;
                  if ( b->move_clicked == true )
                   {
                     b->NewPieceCord( r ) ;
                     b->piece_clicked = false ;
                     
                   }
                   else
                     b->piece_clicked = false ;

               }
               else
                 if ( b->ClickTracker( x_cord , y_cord ) == true )
                  {
                    b->Tracker_Board ( r ) ;
                  }
                 else
                  {
                    b->SetTrackerDefault () ;
                    b->ClearTracker ( r ) ;
                  }
               
                 
               break;

         }
     }

}

void GAME::Start()
 {

    Init() ;
    InitBoard() ;


    while ( IsRunning() == false )
      {
        Event() ;
        Present() ;
      }
       
       Leave() ;
    
 }