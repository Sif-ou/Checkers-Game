#include "track.hpp"


void Tracker::Reset_Track ()
{
    track_cord.Default() ;
}

Tracker::Tracker()
{
  track_surface = IMG_Load ( "assets/move.png" ) ; 

  track_cord.x = 9 ;
  track_cord.y = 9 ;   
  /*Move_rect.x = MOVE_X ;
  Move_rect.y = MOVE_Y ;
  Move_rect.w = MOVE_DES ;
  Move_rect.h = MOVE_DES ;*/  
  
  Focus_rect.x = FOCUS_X ;                   
  Focus_rect.y = FOCUS_Y ;
  Focus_rect.w = FOCUS_W ;
  Focus_rect.h = FOCUS_H ;

  draw_rect.h = CELL_DES ;
  draw_rect.w = CELL_DES ;

}

void Tracker::DeleteTracker ()
{
    SDL_FreeSurface ( track_surface ) ;
}

void Tracker::SetTrack_cord( int x , int y )
{
    track_cord.x = x ;
    track_cord.y = y ;
    track_cord = Mouse_To_BOARD_Cord  ( track_cord ) ;
}

Cordinates Tracker::TrackCord_Board_converter ()
{
    return track_cord ;
}

void Tracker::Focus_Draw ( SDL_Renderer * r , SDL_Texture * t ) 
{
   draw_rect = Cords_Into_Rect (  draw_rect ,  BOARD_To_MOUSE_Cord ( track_cord ) ) ;
   draw_rect.x--;

   t = SDL_CreateTextureFromSurface ( r , track_surface ) ;
   SDL_RenderCopy ( r , t , &Focus_rect , &draw_rect ) ;
   SDL_DestroyTexture( t ) ;
}

Cordinates Tracker::GetTrack_Cord ()
{
    return track_cord ;
}

void Tracker::ForcedTake (std::list<TakeDirection> take_list , SDL_Renderer * r , SDL_Texture * t  )
{

 t = SDL_CreateTextureFromSurface ( r , track_surface ) ;

  if ( take_list.empty() == false )
   for (auto& take : take_list ) 
   {

    Cordinates temp = take.getCords() ,
               temp1 = take.getCords() ;

    temp1.x += 2 ;
    draw_rect = Cords_Into_Rect (  draw_rect ,  BOARD_To_MOUSE_Cord ( temp ) ) ;
    SDL_RenderCopy ( r , t , &Focus_rect  , &draw_rect ) ;

    if ( take.right )
    {
      draw_rect = Cords_Into_Rect (  draw_rect ,  BOARD_To_MOUSE_Cord ( temp1 ) ) ;
      SDL_RenderCopy ( r , t , &Focus_rect  , &draw_rect ) ;
    }


   }

SDL_DestroyTexture ( t ) ;

}

bool Tracker::isTakePiece ( std::list<TakeDirection> take_list ) 
{

 Cordinates temp ;

 for (auto& take : take_list )
 {
   temp = take.getCords() ;
   if ( temp.x == track_cord.x && temp.y == track_cord.y )
   {
    take_num = take.getNum() ;
    return true ;
   } 
    
 } 

   return false ;
}

int Tracker::getTakeNum()
{
  return take_num ;
}

/*
Cordinates Tracker::GetTrack_Cord ()
{
    return track_cord ;
}

void Tracker::ForcedTake (std::list<TakeDirection> take_list , SDL_Renderer * r , SDL_Texture * t  )
{

 t = SDL_CreateTextureFromSurface ( r , track_surface ) ;

  if ( take_list.empty() == false )
   for (auto& take : take_list ) 
   {
    draw_rect = Cords_Into_Rect (  draw_rect ,  BOARD_To_MOUSE_Cord ( take.cords ) ) ;
    SDL_RenderCopy ( r , t , &Focus_rect  , &draw_rect ) ;
   }

SDL_DestroyTexture ( t ) ;

  
}

bool Tracker::isTakePiece ( std::list<TakeDirection> take_list ) 
{

 for (auto& take : take_list ) 
   if ( take.cords.x == track_cord.x && take.cords.y == track_cord.y  )
     return true ;

   return false ;
}

Cordinates Tracker::TakeCord( std::list<TakeDirection> take_list )
{
    Cordinates temp ;

 for (auto& take : take_list ) 
   if ( take.cords.x == track_cord.x && take.cords.y == track_cord.y  )
     {
        temp = take.opp_cord ;
        return temp ;
     }

    return temp ;
}


int Tracker::DirectionTake ( std::list<TakeDirection> take_list ) 
{

 for (auto& take : take_list ) 
   if ( take.cords.x == track_cord.x && take.cords.y == track_cord.y  )
     return take.direction ;
    
    return direction_move__1 ;
}

*/