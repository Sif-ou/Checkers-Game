#include "Movement.hpp"

Movement::Movement()
{
    move_surface = IMG_Load ( "assets/move.png" ) ;

    Move_rect.x = MOVE_X ;
    Move_rect.y = MOVE_Y ;
    Move_rect.w = MOVE_DES ;
    Move_rect.h = MOVE_DES ;

    draw_rect.h = PIECE_HEIGHT ;
    draw_rect.w = PIECE_WIDTH ;
}

void Movement::Reset_Move ()
{
    y = direction_move__1 ;
    x1 =  direction_move__1 ;
    x2 = direction_move__1 ;
    x3 = direction_move__1 ; 
    x4 = direction_move__1 ;
    move_case = direction_move__1 ;
    curr_cords.Default() ;
}

void Movement::ScanBoard_ForMove ( Cordinates temp_cord , cell (&board)[GRID][GRID]  , int direction )
{
    this->direction = direction ;

    y = temp_cord.y ;
    y = ( AllowMove ( y , this->direction ) ? y + this->direction : -1 ) ; 
    x1 = ( AllowMove( temp_cord.x , direction_move_1 ) ? temp_cord.x + direction_move_1 : -1 ) ; 
    x2 = ( AllowMove( temp_cord.x , direction_move__1 ) ? temp_cord.x + direction_move__1 : -1 ) ;
    
    curr_cords.y = temp_cord.y ,
    curr_cords.x = temp_cord.x ;

    int case1 = ( board[y][x1].empty == true && x1 != direction_move__1 ? 1 : 0 ) , 
        case2 = ( board[y][x2].empty == true && x2 != direction_move__1 ? 2 : 0 ) ;


    if ( direction != 0 )
      move_case = ( case1 + case2 > 0 ? case1 + case2 : -1 ) ;
    else
      printf ( "later buddy \n" ) ;

}

void Movement::Move_Draw( SDL_Renderer * r , SDL_Texture * t ) 
{ 
    Cordinates temp_cord ;

    t = SDL_CreateTextureFromSurface ( r , move_surface ) ;


    switch ( move_case )
    {

       case 1 :
         temp_cord.y = y ;
         temp_cord.x = x1 ;
         draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
         SDL_RenderCopy ( r , t , &Move_rect , &draw_rect ) ;
        break;

       case 2 :
         temp_cord.y = y ;
         temp_cord.x = x2 ;
         draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
         SDL_RenderCopy ( r , t , &Move_rect , &draw_rect ) ;
        break;

       case 3 :
         temp_cord.y = y ;
         temp_cord.x = x1 ;
         draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
         SDL_RenderCopy ( r , t , &Move_rect , &draw_rect ) ;
         temp_cord.x = x2 ;
         draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
         SDL_RenderCopy ( r , t , &Move_rect  , &draw_rect ) ;
        break;

        default : 
         Reset_Move() ;
         break;
    }

    SDL_DestroyTexture ( t ) ;

}

Cordinates Movement::GetCordinates ()
{
    return curr_cords ;
}

bool Movement::MoveCLicked ( Cordinates temp_cords )  
{

    bool r = false ;

     /*printf ( " track cords ==>  %d %d \n " , temp_cords.y , temp_cords.x  ) ;
     printf ( " y x1 , x2  ==>  %d %d %d \n " , y , x1 , x2  ) ;*/

    switch ( move_case )
    {
        case 1 :
          r = ( temp_cords.x == x1 &&
                   temp_cords.y == y ? true : false ) ;
         break;
        
        case 2: 
          r = ( temp_cords.x == x2 &&
                   temp_cords.y == y ? true : false ) ;
         break;

        case 3 :
          r = ( ( temp_cords.x == x1 || temp_cords.x == x2 ) &&
                   temp_cords.y == y ? true : false ) ;
         break;

        default :
          Reset_Move() ;
         break;
    }

    return r ;
}

void Movement::TakeMove ( Cordinates change_cord , int direction , SDL_Renderer * r , SDL_Texture * t)
{

  y = change_cord.y ;


  switch ( direction )
  {
     case 1 :
       x1 = change_cord.x + 2 * direction_move_1 ;
       move_case = direction_move_1 ;
       break;
     case 2 :
      x2 = change_cord.x + 2 * direction_move__1 ;
      move_case = 2 ;
      break;
     case 3 :
     x1 = change_cord.x + 2 * direction_move_1 ;
      x2 = change_cord.x + 2 * direction_move__1 ;
      move_case  = 3 ;
      break;

    default :
       move_case = direction_move__1 ;
     break;   
  }

   Move_Draw ( r , t ) ;


/*  
   int team_direction = ( id == 'r' ? direction_move__1 : direction_move_1 ) ;
   temp.y += team_direction ;
   curr_cords = temp ;

   switch ( direction )
   {
     case 3 : 
     y = temp.y ;
     x1 = temp.x + ( direction_move_1 * 2 ) ;
     x2 = temp.x + ( direction_move__1 * 2 ) ;
     move_case =  direction ;
     Move_Draw ( r , t ) ;  
      break;

      case 0 :
        printf ( " still king !!!!! \n " ) ;
       break;

     default : 
     y = temp.y ;
     x1 = temp.x + ( direction_move_1 * 2 ) ;
     x2 = temp.x + ( direction_move__1 * 2 ) ;
     move_case =  direction ;
     Move_Draw ( r , t ) ;  
      break;
   }
*/
}

bool Movement::TakeMove_Clicked ( Cordinates temp )
{
   switch ( move_case )
   {
      case 0 :
        printf ( " still w8 king !!!!! \n " ) ;
         return false ;
       break;

     default : 
       direction = ( temp.x == curr_cords.x + ( direction_move_1 * 2 ) ? direction_move_1 : direction_move__1 ) ;
       if ( temp.y == curr_cords.y && 
            ( temp.x == curr_cords.x + ( direction_move_1 * 2 ) || temp.x == curr_cords.x + ( direction_move__1 * 2 ) ) )
            return true ;
      break;
   }

  return false ;
}

int Movement::getTakeDirection ()
{
  return direction ;
}