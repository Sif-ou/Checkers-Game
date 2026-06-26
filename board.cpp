#include "board.hpp"

/**
 * Set the board ( width , hieght and cells )
 */
void BOARD::SetBoard() 
{
    board_rect.w = WIDTH / 1.5 ;  /* w and h values of the board board*/
    board_rect.h = HEIGHT ; 

    MoveRect_img.w = PIECE_HEIGHT + PIECE_SPACE ;
    MoveRect_img.h = MoveRect_img.w ;
    board_surface = IMG_Load ("assets/board.png") ;
    piece_surface = IMG_Load ( "assets/pieces.png") ;
    /*Picked_Focus_img.w = MoveRect_img.w ;
    Picked_Focus_img.h = MoveRect_img.w ;*/

     for ( int i = 0 ; i <= TGRID ; i++ )  // setting all cells into defaulte because not doing it can make some errors 
     {
         for ( int j = 0 ; j <= TGRID ; j++ )
          borad[i][j].Default() ;
     }
}


/**
 * Render the board 
 */
void BOARD::RenderBoard ( SDL_Renderer * r , SDL_Texture * t )
{
    t = SDL_CreateTextureFromSurface ( r , board_surface ) ;
    SDL_RenderCopy ( r , t , NULL , &board_rect ) ;
    SDL_DestroyTexture( t ) ;
}

void BOARD::SetTeam()
{
    TeamR = new Team() ;
    TeamB = new Team () ;

    TeamR->SetTeam( 'r' , -1 ) ;
    TeamB->SetTeam( 'b' , 1 ) ;

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

    if ( temp_piece->PieceState() )
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

void BOARD::RendererTeams( SDL_Renderer * r , SDL_Texture * t ) 
{

    int number = NUMBER_OF_PIECES - 1 ;

    SDL_Rect rec_temp1 , rec_temp2 , Rpiece_type , Bpiece_type ;
    Cordinates cord_temp1 , cord_temp2 ;


    rec_temp1.w = PIECE_WIDTH ;
    rec_temp1.h = PIECE_HEIGHT ;
    rec_temp2.w = PIECE_WIDTH ;
    rec_temp2.h = PIECE_HEIGHT ;
    
    t = SDL_CreateTextureFromSurface ( r , piece_surface ) ;

    for ( int i = 0 ; i <= number ; i++ )
    {
       /* ********************** */ 
       cord_temp1 = Draw_Cord ( TeamR->Pieces[i]->GetCordinates() ) ;      // converting BOARD cordinates to pixel ( Draw ) cordinates
       rec_temp1 = Cords_Into_Rect ( rec_temp1 , cord_temp1 ) ;            // From Cordinates to SDL_Rect ( type converte ) 

       cord_temp2 = Draw_Cord ( TeamB->Pieces[i]->GetCordinates() ) ;      // converting BOARD cordinates to pixel ( Draw ) cordinates
       rec_temp2 = Cords_Into_Rect ( rec_temp2 , cord_temp2 ) ;            // From Cordinates to SDL_Rect ( type converte ) 
       /* ********************** */

       /* ********************** */
         
         /*   Here the decision if the piece is normal version or upgraded based on the direction of the piece  */
         /*  1 , -1 => normal / 0 => upgraded */

       Rpiece_type = ( TeamR->Pieces[i]->GetDirection() != UPGRADE_PIECE_DIRECTION ? TeamR->Normal_Piece_img : TeamR->Upgraded_Piece_img ) ;
       Bpiece_type = ( TeamB->Pieces[i]->GetDirection() != UPGRADE_PIECE_DIRECTION ? TeamB->Normal_Piece_img : TeamB->Upgraded_Piece_img ) ;
       
       /* ********************** */

       if ( LetPiece_Render( TeamR->Pieces[i] ) )
        SDL_RenderCopy( r , t , &Rpiece_type , &rec_temp1 ) ;
       

       if ( LetPiece_Render ( TeamB->Pieces[i] ) )
       SDL_RenderCopy( r , t , &Bpiece_type , &rec_temp2 ) ;

    }

    SDL_DestroyTexture( t ) ;

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

void BOARD::HandlePiece_Move ( int num , char id , Cordinates temp_cord )
{
    Team * temp = ( id == TeamR->id ? TeamR : TeamB ) ;

    Cordinates temp1 = temp->Pieces[num]->GetCordinates() ; 
    temp->Pieces[num]->SetCordinates( temp_cord ) ;
    borad[temp1.y][temp1.x].Default() ;

    delete ( temp ) ;
}

int BOARD::GetDirection_OfPiece ( Cordinates temp_cord )
{

    /*int r , nu ; 

       nu = borad[temp_cord.y][temp_cord.y].num ;

      r = ( id == TeamR->id ? TeamR->Pieces[nu]->GetDirection() : TeamB->Pieces[nu]->GetDirection() ) ;*/

      int r = ( borad[temp_cord.y][temp_cord.x].id == TeamR->id ? -1 : 1 ) ;

    return r ;
}

void BOARD::ChangePiece_Cords ( Cordinates * piece_cord , Cordinates * Change_cord , char id )
{

    Piece * temp_piece = nullptr ;
    temp_piece = ( id == TeamR->id ? TeamR->Pieces[ borad[piece_cord->y][piece_cord->x].num ] : TeamB->Pieces[ borad[piece_cord->y][piece_cord->x].num ] ) ;
    temp_piece->SetCordinates( *Change_cord ) ;
    borad[piece_cord->y][piece_cord->x].Default() ;
    borad[Change_cord->y][Change_cord->x].SetCell ( *Change_cord , id , temp_piece->GetNum() ) ;
    temp_piece = nullptr ;

    delete ( temp_piece ) ;

}

void BOARD::ChangePiece_TakeCords ( Cordinates Change_cord , int direction , char id  ) 
{
    Team * temp_team = ( id == TeamR->id ? TeamR : TeamB ) , 
         * temp_team_opp = ( temp_team == TeamR ? TeamB : TeamR ) ;

    int y = Change_cord.y ;
    Change_cord.y -= 2 * temp_team->direction ;

    int curr_num = borad[Change_cord.y][Change_cord.x].num , 
        opp_num ;
    
        printf ( " case %d " , direction ) ;
    switch ( direction )
    {
        case 1 :
           
          opp_num = borad[ Change_cord.y + temp_team->direction ][ Change_cord.x + direction_move_1 ].num ;
          borad[ Change_cord.y + temp_team->direction ][ Change_cord.x + direction_move_1 ].Default() ;
          Change_cord.x += 2 * direction_move_1 ; 
         break;
        
        case 2 :
         printf ( " enemy piece => %d , %d \n" , Change_cord.y+ temp_team->direction , Change_cord.x + direction_move_1 ) ;
         printf( " board state => %d , %d \n " , borad[ Change_cord.y + temp_team->direction ][ Change_cord.x + direction_move_1 ].empty , borad[ Change_cord.y + temp_team->direction ][ Change_cord.x + direction_move_1 ].num ) ;
   
          /*opp_num = borad[ Change_cord.y + temp_team->direction ][ Change_cord.x + direction_move__1 ].num ;
          Change_cord.x += 2 * direction_move__1 ;*/
         break;
    }

     Change_cord.y = y ; 

          temp_team_opp->Pieces[opp_num]->KillPiece() ;
          temp_team_opp->Num_Of_Pieces-- ;

     Cordinates temp = temp_team->Pieces[curr_num]->GetCordinates()  ;
     ChangePiece_Cords ( &temp , &Change_cord , temp_team->id ) ;  
     
     
     printf ( " R / B <=> %d / %d \n " , temp_team->Num_Of_Pieces , temp_team_opp->Num_Of_Pieces ) ;

     temp_team = nullptr ;
     temp_team_opp = nullptr ;
     delete ( temp_team ) ;
     delete ( temp_team_opp ) ;

}

Team* BOARD::GetTeam( char id )
{
   if ( id == TeamR->id )
    return TeamR ;
   else 
    return TeamB ;
}

/*
int BOARD::Move_CaseNum ( int direction )
{
    int co = -1 ;

    int move_y = current_y + direction ,
        x_left = current_x + direction_move__1 ,// x -1 
        x_right = current_x + direction_move_1 ; // x + 1 
    

        switch ( direction )
        {
            case 0 :
             break; 

            default :
              if ( borad[move_y][current_x].empty == false )
               {
                co = ( borad[move_y][x_left].empty == false ?  1 : -1 ) ;
                co = ( borad[move_y][x_right].empty == false ? 2 : co ) ;
               }
             break;

        }

    return co ;
}

bool BOARD::AllowPiece_Move ()
{
    int num = borad[current_y][current_x].num ;
        current_direction = -1 ;
    char * temp_id =  borad[current_y][current_x].id ; 

    Team * temp_team = ( *temp_id == 'r' ? TeamR : TeamB ) ;

    current_direction = temp_team->Pieces[num]->GetDirection() ;
    move_case = Move_CaseNum( current_direction ) ;
    
     return ( move_case == -1 ? false : true ) ;
}

void BOARD::RenderMove ( SDL_Renderer * r , SDL_Texture * t )
{
    board_surface = IMG_Load ( "assets/move.png") ;

    switch ( move_case )
    {
        case 1 : 
            current_x--;
            current_y += current_direction ; 
            Cordinates temp_crod ;
            temp_crod.x = current_x ;
            temp_crod.y = current_y ;

            temp_crod = Draw_Cord ( temp_crod ) ;
            SDL_Rect temp_rect = Cords_Into_Rect ( temp_rect , temp_crod ) ;
            t = SDL_CreateTextureFromSurface ( r , board_surface ) ;
            SDL_RenderCopy ( r , t , &MoveRect_img , NULL ) ;
         break;
        case 2 : 

         
         break;

         default : 
         break;
    }

    SDL_FreeSurface ( board_surface ) ;
}

*/