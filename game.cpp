#include "game.hpp"

int FPS = 1000 / 60; 
Uint32 elapsed = 0;
Uint32 frameTime = 0;

bool reload = false ; 
bool leave_ = false ;


//Cordinates cord ;

void GAME::Init()
{
    this->run = true ;
   if ( SDL_Init ( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( " error in init %s" , SDL_GetError() ) ;
        this->run = false ; 
        return ;
    }
  else
  {
    window = SDL_CreateWindow ( "Checkers" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , WIDTH , HEIGHT , false ) ;
     if ( !window )
      {
        printf ( " Can't Init Window %s" , SDL_GetError() ) ;
         this->run = false ; 
        return ;
      }
     else
     {
         renderer = SDL_CreateRenderer ( window , -1 , SDL_RENDERER_ACCELERATED ) ;
         if ( !renderer )
          {
            printf ( " Can't Init Renderer %s" , SDL_GetError() ) ;
            this->run = false ; 
            return ;
          }
         else
         {
           /* ###### Setup For The Game ###### */
             
             track = new Tracker( renderer ) ; 
             take = new Take() ;
             movement = new Movement( renderer ) ;
             board = new BOARD() ;
             board->SetBoard( renderer ) ;
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
    board->RenderBoard(renderer);
    
    board->RendererTeams(renderer);

    if (take->isTakeEmpty()) 
    {
        if (board->Correct_PieceCords(track->GetTrack_Cord(), turn)) {
            track->Focus_Draw(renderer);
            movement->Move_Draw(renderer);
        }
    }
    else 
    {
        if (!track->isTakePiece(take->getTakeList())) {
            track->ForcedTake(take->getTakeList(), renderer);
        }
        else {
            track->Focus_Draw(renderer);
            movement->TakeMove(take->getChangeCord(track->getTakeNum()), take->getDirection(track->getTakeNum()), renderer);
        }
    }
}

void GAME::BoardUpdate()
{
    if (take->isTakeEmpty()) 
    {
        if (take_advantage) {
            take_advantage = false;
            ChangeTurn();
        }

        if (board->Correct_PieceCords(track->GetTrack_Cord(), turn)) {
            movement->ScanBoard_ForMove(track->GetTrack_Cord(), board->getBoard(), board->GetDirection_OfPiece(track->GetTrack_Cord()));
        }
        else if (movement->MoveCLicked(track->GetTrack_Cord())) {
            Cordinates t1 = movement->GetCordinates();
            Cordinates t2 = track->GetTrack_Cord();
            board->ChangePiece_Cords(&t1, &t2, turn);
            movement->Reset_Move();
            ChangeTurn();
        }
        else {
            movement->Reset_Move();
        }
    }
    else 
    {
        if ( movement->TakeMove_Clicked( track->GetTrack_Cord() ) ) {

            if (!take_advantage) 
              advantage_num = track->getTakeNum() ;

            board->ChangePiece_TakeCords(track->GetTrack_Cord(), take->getCord(advantage_num), take->getEnemyCord(advantage_num),
                                         take->getChangeCord(advantage_num), take->getDirection(advantage_num), turn);
            movement->Reset_Move();
            take_advantage = true;
        }
        else
         movement->Reset_Move() ; 
    }

    if (take_advantage)
        take->Scan_Advantage(board->getBoard(), board->GetTeam(turn), advantage_num);
    else
        take->ScanBoard(board->getBoard(), board->GetTeam(turn));
}
void GAME::Event()
{

    while ( SDL_PollEvent( &event ) )
    {
       switch( event.type )
       {
          case SDL_QUIT :
            run = false ;
            reload = false ;
            leave_ = true ;
           break;

           case SDL_MOUSEBUTTONDOWN :
            Cordinates tt ;
             SDL_GetMouseState ( &x_cord , &y_cord ) ;
             track->SetTrack_cord( x_cord , y_cord ) ;

              //printf ( " cord => %d %d \n" , x_cord , y_cord ) ;

              //cord = track->GetTrack_Cord() ;

              //printf ( " track cord => %d %d \n" , cord.x , cord.y ) ;
             break;

          case SDL_KEYDOWN : 
           
             switch ( event.key.keysym.scancode )
             {
                 case SDL_SCANCODE_I :
                 {


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

                 }
                  break;

                
                case SDL_SCANCODE_X : 
                 
                {

                   int pc , di  ;
                   char te ;
                   printf ( " enter the piece number , the direction you want to change then the team of you choice  :: ( piece_num ; direction , team_num ) " ) ;
                   std::cin >> pc >> di >> te ;
                   Team * temp_team_test = board->GetTeam ( te ) ;
                   temp_team_test->Pieces[pc]->SetDirection ( di ) ;
                   printf ( " done " ) ;
                   temp_team_test = nullptr ;

                }
                   

                 break;


                 case SDL_SCANCODE_N : 
                  {
                    Piece * temp_piece = board->GetTeam( turn )->Pieces[ board->GetPiece_FromBoard( track->GetTrack_Cord() ) ] ;
                    
                    printf( 
                         " piece number : %d | "
                         " direction : %d | " 
                         " to it right : %d | "
                         " to it left : %d | \n" ,
                         temp_piece->GetNum() , temp_piece->GetDirection() , 
                         board->getBoard()[ temp_piece->GetCordinates().y + temp_piece->GetDirection() ][ temp_piece->GetCordinates().x + direction_move_1 ].empty ,
                         board->getBoard()[ temp_piece->GetCordinates().y + temp_piece->GetDirection() ][ temp_piece->GetCordinates().x + direction_move__1 ].empty
                    ) ;


                    temp_piece = nullptr ;
                  }
                  break;


                  case SDL_SCANCODE_LSHIFT : 
                  
                   run = false ;
                   reload = true ;

                   break;

                 case SDL_SCANCODE_ESCAPE : 
                   run = false ;
                   reload = false ;
                   leave_ = true ;
                  break;



                case SDL_SCANCODE_P : 
                {
                  Team * temp_team = board->GetTeam( 'r' ) ;

                  printf ( " TEAM RED : \n " " ########## \n" ) ;
                  for ( int i = 0 ; i < temp_team->Num_Of_Pieces ; i++ ) 
                   printf ( " piece num : %d / Alive => %d \n " , i , temp_team->Pieces[i]->isAlive() ) ;
                   
                  printf ( " ########## \n" ) ; 


                  temp_team = board->GetTeam( 'b' ) ;

                  printf ( " TEAM BLACK : \n " " ########## \n" ) ;
                  for ( int i = 0 ; i < temp_team->Num_Of_Pieces ; i++ ) 
                   printf ( " piece num : %d / Alive => %d \n " , i , temp_team->Pieces[i]->isAlive() ) ;
                   
                  printf ( " ########## \n" ) ; 

                  temp_team = nullptr ;

                }

             }
             
           break;
       }
    }

}

void GAME::Leave()
{

  track->DeleteTracker() ;
  movement->DeleteMovement() ;
  board->DeleteBoard() ;
  
  delete board ;
  board = nullptr ;

  delete track ;
  track = nullptr ;

  delete take ;
  take = nullptr ; 

  delete movement ;
  movement = nullptr ; 


  SDL_DestroyRenderer ( renderer ) ;
  SDL_DestroyWindow ( window ) ;
  SDL_Quit() ;
}


void GAME_START ()
{

    reload = false ;
    GAME * Checkers = new GAME() ;
    Checkers->Init() ;

    while ( Checkers->isRunning() )
    {
      elapsed = SDL_GetTicks();

      
      Checkers->Clear();
      Checkers->Event();
      Checkers->BoardUpdate();
      Checkers->Board(); 
      Checkers->Present();

      frameTime = SDL_GetTicks() - elapsed;

      if (FPS > frameTime)
        SDL_Delay(FPS - frameTime);
            
    }

   Checkers->Clear() ;
   Checkers->Leave() ;
   delete Checkers ;
   Checkers = nullptr ;

   SDL_PumpEvents();
   SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);

} 


void Launcher ()
{

reload = true;

while (1)
{
    if (reload)
    {
        reload = false; 
        printf(" reloading ... \n ");
        GAME_START();
    }
    else if (leave_)
     break; 
}

    printf(" breaking ... \n ");

}