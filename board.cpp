#include "board.hpp"

/**
 * Set the board ( width , hieght and cells )
 */
void BOARD::SetBoard( SDL_Renderer * r ) 
{
    board_rect.w = WIDTH / 1.5 ;  /* w and h values of the board board*/
    board_rect.h = HEIGHT ; 

    MoveRect_img.w = PIECE_HEIGHT + PIECE_SPACE ;
    MoveRect_img.h = MoveRect_img.w ;

    SDL_Surface * board_surface = IMG_Load ("assets/board.png") ;
    SDL_Surface * piece_surface  = IMG_Load ( "assets/pieces.png") ;

    board_texture = SDL_CreateTextureFromSurface ( r , board_surface ) ;
    peice_texture = SDL_CreateTextureFromSurface ( r , piece_surface ) ;



    SDL_FreeSurface ( board_surface ) ;
    SDL_FreeSurface ( piece_surface ) ;

    /*Picked_Focus_img.w = MoveRect_img.w ;
    Picked_Focus_img.h = MoveRect_img.w ;*/

     for ( int i = 0 ; i <= TGRID ; i++ )  // setting all cells into defaulte because not doing it can make some errors 
     {
         for ( int j = 0 ; j <= TGRID ; j++ )
          borad[i][j].Default() ;
     }
}


void BOARD::DeleteBoard()
{
    SDL_DestroyTexture ( peice_texture ) ;
    SDL_DestroyTexture ( board_texture ) ;


    delete TeamB;
    TeamB = nullptr;

    delete TeamR;
    TeamR = nullptr;
    

}

/**
 * Render the board 
 */
void BOARD::RenderBoard ( SDL_Renderer * r )
{

    SDL_RenderCopy ( r , board_texture , NULL , &board_rect ) ;
}

void BOARD::SetTeam()
{
    TeamR = new Team() ;
    TeamB = new Team () ;

    TeamR->InitTeam( 'r' , -1 ) ;
    TeamB->InitTeam( 'b' , 1 ) ;

    TeamR->Normal_Piece_img.w = NORMAL_RED_IMG_W ;
    TeamR->Normal_Piece_img.h = NORMAL_RED_IMG_H ;
    TeamR->Normal_Piece_img.x = PIECE_IMG_X_250 ;
    TeamR->Normal_Piece_img.y = PIECE_IMG_Y_0 ;

    TeamR->Upgraded_Piece_img.w = UPGRADED_RED_IMG_W ;
    TeamR->Upgraded_Piece_img.h = UPGRADED_RED_IMG_H;

    TeamB->Normal_Piece_img.w = NORMAL_BLACK_IMG_W ; 
    TeamB->Normal_Piece_img.h = NORMAL_BLACK_IMG_H ;
    TeamB->Normal_Piece_img.x = PIECE_IMG_X_0 ;
    TeamB->Normal_Piece_img.y = PIECE_IMG_Y_250 ;

    TeamB->Upgraded_Piece_img.w = UPGRADED_BLACK_IMG_W ;
    TeamB->Upgraded_Piece_img.h = UPGRADED_BLACK_IMG_H ;
    TeamB->Upgraded_Piece_img.x = PIECE_IMG_X_250 ;
    TeamB->Upgraded_Piece_img.y = PIECE_IMG_Y_250 ;

    Team_In_Board( TeamR ) ;
    Team_In_Board ( TeamB ) ;

}

void BOARD::Team_In_Board( Team * temp_Team  )
{

    int co = 0 ,
        n_row_min ,
        n_row_max ;
    Cordinates temp_cord ;

    if ( temp_Team->direction == 1 )
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

           for ( int j = 0 ; j <= TGRID ; j++ )
           {

            temp_cord.x = j ;
            temp_cord.y = i ;

              if ( i % 2 == 0 )
              {

                 if ( j % 2 == 0 )
                 {
                    temp_Team->Pieces[co] = new Piece (  temp_cord  , temp_Team->id , temp_Team->direction , co ) ;
                    borad[i][j].SetCell( temp_cord , temp_Team->id , co ) ;
                    co++ ;
                 }


              }
              else 
              {

                  if ( j % 2 == 1 )
                  {
                    temp_Team->Pieces[co] = new Piece (  temp_cord  , temp_Team->id , temp_Team->direction , co ) ;
                    borad[i][j].SetCell( temp_cord , temp_Team->id , co ) ;
                    co++ ;
                  }


              }

                     
           }

         }

}


/**
 * Let Piece Render or not based on board attributes
 */
bool BOARD::LetPiece_Render ( Piece * temp_piece )
{
    Cordinates temp_cord = temp_piece->GetCordinates() ;

    if ( temp_piece->isAlive() )
    {
       if ( borad[temp_cord.y][temp_cord.x].empty == true )
        printf( " game logic error , piece number : %d\n" , temp_piece->GetNum() ) ;
       else
        return true ;
    }
    else
     return false ;

    return false ;
}

void BOARD::RendererTeams( SDL_Renderer * r  ) 
{

    int number = NUMBER_OF_PIECES - 1 ;

    SDL_Rect rec_temp1 , rec_temp2 , Rpiece_type , Bpiece_type ;
    Cordinates cord_temp1 , cord_temp2 ;


    rec_temp1.w = PIECE_WIDTH ;
    rec_temp1.h = PIECE_HEIGHT ;
    rec_temp2.w = PIECE_WIDTH ;
    rec_temp2.h = PIECE_HEIGHT ;
    

    for ( int i = 0 ; i <= number ; i++ )
    {
       /* ********************** */ 
       cord_temp1 = Draw_Cord ( TeamR->Pieces[i]->GetCordinates() ) ;      // converting BOARD cordinates to pixel ( Draw ) cordinates
       rec_temp1 = Cords_Into_Rect ( rec_temp1 , cord_temp1 ) ;            // From Cordinates to SDL_Rect ( type converte ) 

       cord_temp2 = Draw_Cord ( TeamB->Pieces[i]->GetCordinates() ) ;      // converting BOARD cordinates to pixel ( Draw ) cordinates
       rec_temp2 = Cords_Into_Rect ( rec_temp2 , cord_temp2 ) ;            // From Cordinates to SDL_Rect ( type converte ) 
       /* ********************** */

       /* ********************** */
         
         /*   Here the decision if the piece is normal version or upgraded is all based on the direction of the piece  */
         /*  1 , -1 => normal / 0 => upgraded */

       Rpiece_type = ( TeamR->Pieces[i]->GetDirection() != UPGRADE_PIECE_DIRECTION ? TeamR->Normal_Piece_img : TeamR->Upgraded_Piece_img ) ;
       Bpiece_type = ( TeamB->Pieces[i]->GetDirection() != UPGRADE_PIECE_DIRECTION ? TeamB->Normal_Piece_img : TeamB->Upgraded_Piece_img ) ;
       
       /* ********************** */

       if ( LetPiece_Render( TeamR->Pieces[i] ) )
        SDL_RenderCopy( r , peice_texture , &Rpiece_type , &rec_temp1 ) ;
       

       if ( LetPiece_Render ( TeamB->Pieces[i] ) )
       SDL_RenderCopy( r , peice_texture , &Bpiece_type , &rec_temp2 ) ;

    }

}

bool BOARD::Correct_Cords ( Cordinates temp_cord )
{ 
   return ( temp_cord.x <= 7 && temp_cord.x > direction_move__1 ? true : false ) ;
}

bool BOARD::Correct_PieceCords ( Cordinates temp_cord , char id )
{
    //std:: cout << " => " << t << std::endl ;
    return ( ( AllowValue ( temp_cord.y ) && AllowValue ( temp_cord.x ) ) 
         && ( borad[temp_cord.y][temp_cord.x].empty == false && borad[temp_cord.y][temp_cord.x].id == id ) 
             ? true : false ) ;
             //&&  t == id ? true : false ) ;
}

int BOARD::GetPiece_FromBoard ( Cordinates temp_cord )
{
    return ( borad[temp_cord.y][temp_cord.x].num ) ;
}

int BOARD::GetDirection_OfPiece ( Cordinates temp_cord )
{

      int r = borad[temp_cord.y][temp_cord.x].num ;

      if ( borad[temp_cord.y][temp_cord.x].id == TeamR->id )
         return TeamR->Pieces[r]->GetDirection() ;
      else 
        return TeamB->Pieces[r]->GetDirection() ;

     return 0 ;
}

void BOARD::ChangePiece_Cords ( Cordinates * piece_cord , Cordinates * Change_cord , char id )
{

    Piece * temp_piece = nullptr ;
    temp_piece = ( id == TeamR->id ? TeamR->Pieces[ borad[piece_cord->y][piece_cord->x].num ] : TeamB->Pieces[ borad[piece_cord->y][piece_cord->x].num ] ) ;
    temp_piece->SetCordinates( *Change_cord ) ;
    borad[piece_cord->y][piece_cord->x].Default() ;
    borad[Change_cord->y][Change_cord->x].SetCell ( *Change_cord , id , temp_piece->GetNum() ) ;


   if ( temp_piece->GetDirection() != UPGRADE_PIECE_DIRECTION )
   {

     if ( id == 'r' )
     {
        if ( Change_cord->y == UPGRADE_PIECE_DIRECTION )
         temp_piece->KingUpgrade() ;
     }
     else
     {
         if ( Change_cord->y == TGRID )
          temp_piece->KingUpgrade() ;
     }

   }



    temp_piece = nullptr ;

    delete ( temp_piece ) ;

}

void BOARD::ChangePiece_TakeCords ( Cordinates track_cord ,  Cordinates curr_cord , Cordinates opp_cord , Cordinates Change_cord , int * array , int direction , char id   ) 
{
    Team * temp_team = ( id == TeamR->id ? TeamR : TeamB ) , 
         * temp_team_opp = ( temp_team == TeamR ? TeamB : TeamR ) ;
            
     
    int 
      curr_num =  borad[curr_cord.y][curr_cord.x].num ,
      opp_num ;

      bool let_change = false ;

      switch (direction)
      {

        case 0 : 


        if ( array != nullptr )
        {
          
            Change_cord.x +=  array[0] * array[2]  ;
            Change_cord.y +=  array[1] * array[2]  ;
            
            opp_cord.x +=  (array[0] * array[2]) - ( 1 * array[0] )  ;
            opp_cord.y +=  (array[1] * array[2]) - ( 1 * array[1] )  ;


            let_change = true ;

        }
         
         break;


       case 1 :
       
       Change_cord.x += 2 ;
       opp_cord.x += direction_move_1 ;
       let_change = true ;

        break;
      
       case 2 :

       Change_cord.x -= 2 ;
       opp_cord.x += direction_move__1 ;
       let_change = true ;

        break;

       case 3 : // if it not the first one , it must be the second one 

        Change_cord.x += 2 ;
        opp_cord.x += direction_move_1 ;
        
        if ( track_cord.x != Change_cord.x ) 
        {
            Change_cord.x -= 4 ;
            opp_cord.x -= 2 ;
        }

        let_change = true ;

        break;

      }



    if ( let_change )
    {

      if ( temp_team->Pieces[curr_num]->GetDirection() != UPGRADE_PIECE_DIRECTION )
       {
    
         if ( id == 'r' )
         {
            if ( Change_cord.y == UPGRADE_PIECE_DIRECTION )
             temp_team->Pieces[curr_num]->KingUpgrade() ;
         }
         else
         {
             if ( Change_cord.y == TGRID )
              temp_team->Pieces[curr_num]->KingUpgrade() ;
         }
    
       }
    
           opp_num = borad[opp_cord.y][opp_cord.x].num ;
    
           /* changing the piece place & updating in board */
           borad[curr_cord.y][curr_cord.x].Default() ;
           temp_team->Pieces[curr_num]->SetCordinates( Change_cord ) ;
           borad[Change_cord.y][Change_cord.x].SetCell ( Change_cord , id , curr_num ) ;
    
    
    
    
           /* killing piece & updating board */
           borad[opp_cord.y][opp_cord.x].Default() ;
           temp_team->Num_Of_Pieces-- ;
           temp_team_opp->Pieces[opp_num]->KillPiece() ;
    
    
           temp_team = nullptr ;
           temp_team_opp = nullptr ;
    
    }



}

Team* BOARD::GetTeam( char id )
{
   if ( id == TeamR->id )
    return TeamR ;
   else 
    return TeamB ;
}
