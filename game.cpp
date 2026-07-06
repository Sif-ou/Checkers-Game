#include "game.hpp"

int FPS = 1000 / 60; 
Uint32 elapsed = 0;
int frameTime = 0;

//Cordinates cord ;

void GAME::Init()
{
   if ( SDL_Init ( SDL_INIT_EVERYTHING ) < 0 )
    printf( " error in init " , SDL_GetError() ) ;
  else
  {
    window = SDL_CreateWindow ( "Checkers" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WIDTH , HEIGHT , false ) ;
     if ( !window )
      printf ( " Can't Init Window " , SDL_GetError() ) ;
     else
     {
         renderer = SDL_CreateRenderer ( window , -1 , SDL_RENDERER_ACCELERATED ) ;
         if ( !renderer )
          printf ( " Can't Init Renderer " , SDL_GetError() ) ;
         else
         {
           /* ###### Setup For The Game ###### */
             
             track = new Tracker() ; 
             take = new Take() ;
             movement = new Movement() ;
             board = new BOARD() ;
             board->SetBoard() ;
             board->SetTeam() ;




           /*######   ######*/
         }
         
          
     }
  }
    
}

bool GAME::isRunning()
{
    return run ;
}

void GAME::Clear()
{
    SDL_RenderClear( renderer ) ;
}

void GAME::Present()
{
    SDL_RenderPresent ( renderer ) ;
}

void GAME::ChangeTurn ()
{
   if ( turn == 'r' )
    turn = 'b' ;
   else
    turn = 'r' ;
}

void GAME::Board()
{
    board->RenderBoard ( renderer , texture ) ;
    board->RendererTeams( renderer , texture ) ;
}

void GAME::BoardUpdate ()
{

   take->ScanBoard( board->getBoard() , board->GetTeam( turn ) ) ;

  if ( take->isTakeEmpty() ) // normal play ( no takes forced )
  {

    if ( board->Correct_PieceCords ( track->GetTrack_Cord() , turn ) )
    {
     track->Focus_Draw( renderer , texture );
     movement->ScanBoard_ForMove ( track->GetTrack_Cord() , board->getBoard() , board->GetDirection_OfPiece( track->GetTrack_Cord() ) ) ;
     movement->Move_Draw ( renderer , texture ) ;
    }

    if ( movement->MoveCLicked ( track->GetTrack_Cord() ) )
    {
      Cordinates t1 = movement->GetCordinates() , t2 = track->GetTrack_Cord() ;
      board->ChangePiece_Cords ( &t1 , &t2 , turn ) ;
      movement->Reset_Move() ;
      ChangeTurn() ;
    }


  }
  else 
  {

    if ( movement->TakeMove_Clicked( track->GetTrack_Cord() ) )
    {
      int n = track->getTakeNum() ;
      printf ( " here num from take it SELF => %d \n " , n ) ;
      printf ( " here direction from take it SELF => %d \n " , take->getDirection(n) ) ;
      board->ChangePiece_TakeCords ( take->getCord( n ) , take->getEnemyCord( n ) ,
                                     take->getChangeCord( n ) ,take->getDirection( n ) , turn ) ;
      movement->Reset_Move() ;
    }
    else
    {

     if ( track->isTakePiece( take->getTakeList() ) == false )
       track->ForcedTake( take->getTakeList() , renderer , texture ) ; 
     else
      {
        track->Focus_Draw( renderer , texture );
        movement->TakeMove ( take->getChangeCord( track->getTakeNum() ) , take->getDirection( track->getTakeNum() ) , renderer , texture ) ;
      }

    }

     

  }

}

void GAME::Event()
{

    while ( SDL_PollEvent( &event ) )
    {
       switch( event.type )
       {
          case SDL_QUIT :
            run = false ;
           break;

           case SDL_MOUSEBUTTONDOWN :
            Cordinates tt ;
             SDL_GetMouseState ( &x_cord , &y_cord ) ;
             track->SetTrack_cord( x_cord , y_cord ) ;

              //printf ( " cord => %d %d \n" , x_cord , y_cord ) ;

              //cord = track->GetTrack_Cord() ;

              //printf ( " track cord => %d %d \n" , cord.x , cord.y ) ;
             break;

          case SDL_KEYDOWN :  // press I to see info about (only) boolean board array 
           
             switch ( event.key.keysym.scancode )
             {
                 case SDL_SCANCODE_I :

                   cell (&t) [GRID][GRID] = board->getBoard() ;
                   for ( int i = 0 ; i <= TGRID ; i++ )
                   {
                    printf( "\n" ) ;

                    for ( int j = 0 ; j <= TGRID ; j++ )        
                    std:: cout << "|" << t[i][j].num  << "|" ;  
                    //printf ( "|%d|" , board->borad[i][j].id ) ;

                   }
                   Cordinates p = track->GetTrack_Cord() ;
                   printf ( "\n cords %d/%d \n ", p.x , p.y ) ;

                  take->TestFunc() ;
                  break;
             }
             
           break;
       }
    }

}
/*
                   cell (&t) [GRID][GRID] = board->getBoard() ;
                   for ( int i = 0 ; i <= TGRID ; i++ )
                   {
                    printf( "\n" ) ;

                    for ( int j = 0 ; j <= TGRID ; j++ )        
                    std:: cout << "|" << t[i][j].num  << "|" ;  
                    //printf ( "|%d|" , board->borad[i][j].id ) ;

                   }
                   Cordinates p = track->GetTrack_Cord() ;
                   printf ( "\n cords %d/%d \n ", p.x , p.y ) ;

*/



void GAME::Leave()
{
  track->DeleteTracker() ;
  SDL_DestroyTexture ( texture ) ;
  SDL_DestroyRenderer ( renderer ) ;
  SDL_DestroyWindow ( window ) ;
  SDL_Quit() ;
}


void GAME_START ()
{
    GAME * Checkers = new GAME() ;

    Checkers->Init() ;

    while ( Checkers->isRunning() )
    {
        elapsed = SDL_GetTicks();

        Checkers->Clear();
        Checkers->Board(); 
        Checkers->BoardUpdate();
        Checkers->Event();
        Checkers->Present();

        frameTime = SDL_GetTicks() - elapsed;

        if (FPS > frameTime)
            SDL_Delay(FPS - frameTime);
            
    }
   Checkers->Clear() ;
   Checkers->Leave() ;
}