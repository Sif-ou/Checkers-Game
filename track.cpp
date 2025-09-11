#include "track.hpp"

SDL_Color yellow = { 255 , 255 , 0 , SDL_ALPHA_OPAQUE };
SDL_Color green  = { 0 , 255 , 0 , SDL_ALPHA_OPAQUE };
SDL_Color black  = { 0 , 0 , 0 , SDL_ALPHA_OPAQUE };
SDL_Color white  = { 255 , 255 , 255 , SDL_ALPHA_OPAQUE };
SDL_Color red    = { 255 , 0 , 0 , SDL_ALPHA_OPAQUE };


int Tracker::CordCalcu ( int x )
{
  x = ( x - VIDE ) / D ;
   return x ;
}

bool Tracker::AllowedMove ( int n )
{
   if ( n > 7 )
    return false ;
   else if ( n < 0 )
    return false ;
   else 
     return true ;

   return false ;
}

bool Tracker::AllowedMoveInBoard ( cell temp [grid][grid] , int x , int y ) 
{
  if( temp[y][x].empty == true ) 
    return true ;

  else
    return false ;
   
   return false ;
}

bool Tracker::CorrectCord()
{
   if ( y_cord >= 8 || y_cord < 0 )
    return false ;
   else if ( x_cord >= 8 || x_cord < 0 )
    return false ;
   else
    return true ;
  
    return false ;
}

void Tracker::TDraw( SDL_Renderer * r , SDL_Color color )
{
  int currentX = ( D * x_cord ) ,
      currentY = ( D * y_cord ) ;

  track_rec.x = currentX + ( D / 2 ) + VIDE ; 
  track_rec.y = currentY + ( D / 2 ) + VIDE ;

  FillO ( r , color , track_rec.x , track_rec.y ) ;
}

void Tracker::DrawPause( SDL_Renderer * r , SDL_Color color )
{
  SDL_Rect pause ;
  pause.x = x_cord * D + VIDE ;
  pause.y = y_cord * D + VIDE ;
  pause.w = D ;
  pause.h = D ;
  SDL_SetRenderDrawColor ( r , color.r , color.g , color.b , color.a ) ;
  SDL_RenderDrawRect ( r , &pause ) ;
}

void Tracker::DefaultTrack()
{
   pa = -3 ;
   tdir = -3 ;
   tx = -1 ; 
   ty = -1 ;
}

void Tracker::TrackPieceCord ( int &x , int &y )
{

    x = CordCalcu ( x ) ; 
    y = CordCalcu ( y ) ;
    
    x_cord = x ;
    y_cord = y ;
}

void Tracker::Possible_Movement ( SDL_Renderer * r  , Piece * temp_Piece , cell  temp_board [grid][grid] , int n  )
{

    temp_Piece += n ;


    if ( temp_Piece->Direction() != 0 )
    {
       if ( AllowedMove ( y_cord + temp_Piece->Direction() ) == true  )
        {
           ty = y_cord ;
           tdir = temp_Piece->Direction() ;
           y_cord += tdir ;
           ShowMovement ( r , temp_board ) ;
        }
    }
    else
    {
      bool up = AllowedMove( y_cord - 1) , down = AllowedMove(y_cord + 1 ) ;
      fly[0] = (up   ? 0 : -1);
      fly[1] = (up   ? 0 : -1);
      fly[2] = (down ? 0 : -1);
      fly[3] = (down ? 0 : -1);

      HandleFly ( temp_board ) ;
      Movement_Direction ( r , 0 ) ;

    }
}

void Tracker::HandleFly ( cell  temp_board [grid][grid] )
{
   int op , n ;

   ty = y_cord ;
   tx = x_cord ;

   for ( int i = 0 ; i <= 3 ; i++ )
   {
      op = ( i < 2 ? -1 : 1 ) ;                       // ( 0 , 1 ) go up ( 2 , 3 ) go down 
      n = ( i % 2 == 0 ? 1 : -1 ) ;                   // even go right odd go left  

      if ( fly[i] != -1 )
      {
          while (true)
          { 
             y_cord += op ;
             x_cord += n ;

             if ( ( AllowedMove(x_cord)  &&  AllowedMove( y_cord )  ) &&  
                  AllowedMoveInBoard ( temp_board , x_cord  , y_cord  ) )
              fly[i]++ ;
             else 
              break;
          }
      }

      y_cord = ty ; 
      x_cord = tx ;
    }

}

void Tracker::ShowMovement ( SDL_Renderer * r  , cell temp_board [grid][grid] )
{
     if ( ( AllowedMove( x_cord + 1 ) == true  && AllowedMove( x_cord - 1 ) == true  ) &&
          ( AllowedMoveInBoard ( temp_board , x_cord+1 , y_cord ) == true && AllowedMoveInBoard ( temp_board , x_cord-1 , y_cord ) ==true )   )
         Movement_Direction( r , 2 );
      else if ( AllowedMove( x_cord + 1 ) == true  && AllowedMoveInBoard ( temp_board , x_cord+1 , y_cord ) ==true ) 
         Movement_Direction( r , 1 ) ;
      else if ( AllowedMove( x_cord - 1 ) == true && AllowedMoveInBoard ( temp_board , x_cord-1 , y_cord ) ==true )
        Movement_Direction( r  , -1  ) ;
      else
       Movement_Direction( r  , -2 ) ;
       
}

void Tracker::Movement_Direction ( SDL_Renderer * r   , int n  )
{
    track_rec.h = 60 ;
    track_rec.w = 60 ;
    tx = x_cord ;
     switch ( n )     
     {
        case 1 : 
           pa = 1 ;
           x_cord++; 
          TDraw( r , yellow ) ;
         break;
        
        case -1 :
          pa = -1 ; 
          x_cord--;
          TDraw( r , yellow ) ;
         break;

        case 2 : 
         pa = 2 ;
         x_cord++;
          TDraw( r , yellow ) ;
         x_cord -= 2 ; 
          TDraw( r , yellow ) ;
         break;

         case 0 : 

           pa = 0 ;
           int b , op , fi ;
         
            for ( int i = 0  ; i <= 3 ; i++ )
            {

              fi = fly[i] ;
              b = ( i % 2 == 0 ? 1 : -1 ) ;
              op = ( i < 2 ? -1 : 1 ) ;

               if ( fly[i] > 0 )
               { 

                 while (true)
                  {

                   fly[i]--;

                    if ( fly[i] == -1 )
                     break; 
                    else
                    {
                      y_cord += op ;
                       x_cord += b ;
                       TDraw ( r , yellow ) ;
                    }

                  }
                  y_cord = ty ;
                  x_cord = tx ;
                  fly[i] = fi ;
               }
                
            }

          break;

         default : 
           pa = -2 ;
           y_cord -= tdir ;
          DrawPause( r , yellow ) ;
          break;
     }

}

void Tracker::ClearMoveFromBoard ( SDL_Renderer * r )
{
 
  int temp_y = y_cord ; 
      
      x_cord = tx ;
      y_cord = ty ;

 switch ( pa )
 {
    case 1 :
     DrawPause ( r , white ) ;
     y_cord = temp_y ; 
     x_cord++; 
     TDraw ( r , black ) ;
     break;

    case -1 :
     DrawPause ( r , white ) ;
     y_cord = temp_y ;
     x_cord--;
     TDraw ( r , black ) ;
     break;

    case -2 : 
     DrawPause( r , white ) ;
     break;

    case 2 : 
      DrawPause ( r , white ) ;
      y_cord = temp_y ;
      x_cord++ ;
      TDraw( r , black ) ;
      x_cord -= 2 ;
      TDraw ( r , black ) ;
     break;

    case 0 :
           
           int b , op , fi ;
         
           DrawPause ( r , white ) ;

            for ( int i = 0  ; i <= 3 ; i++ )
            {

              fi = fly[i] ;
              b = ( i % 2 == 0 ? 1 : -1 ) ;
              op = ( i < 2 ? -1 : 1 ) ;

               if ( fly[i] > 0 )
               {

                 while (true)
                  {

                   fly[i]--;

                    if ( fly[i] == -1 )
                     break;
                    else
                    {
                       y_cord += op ;
                       x_cord += b ;
                       TDraw ( r , black ) ;
                    }

                  }
                  y_cord = ty ;
                  x_cord = tx ;
                  fly[i] = fi ; 
               } 
                
            }


     break;
    
    default:
     break;
 }

}

bool Tracker::ClickedMove ( int &x , int &y )
{

  y = CordCalcu ( y ) ;
  x = CordCalcu ( x ) ;
    switch ( pa )
    {

       case 2 :
        x_cord = tx ;
          if (  y_cord == y && x_cord + 1 == x  )
           {
             x_cord += 1 ;
             return true ;
           }
           else if (  y_cord == y && x_cord - 1 == x  )
           {
             x_cord -= 1 ;
             return true ;
           }
        break;

        case 0 : 

         int b , op , x0 , y0 ; 

         for ( int i = 0 ; i <= 3 ; i++ )
          {
             if ( fly[i] > 0 )
             {
                b = ( i % 2 == 0 ? 1 : -1 ) ;
                op = ( i < 2 ? -1 : 1 ) ;

                for ( int j = 0 ; j <= fly[i] ; j++ )
                {
                    x0 = CordCalcu ( ( x_cord + ( fly[i] - j ) * b ) * D + VIDE ) ;
                    y0 = CordCalcu ( ( y_cord + ( fly[i] - j ) * op ) * D + VIDE ) ;
                   if ( x0 == x && y0 == y )
                    {
                      x_cord = x0 ;
                      y_cord = y0 ;
                        return true ; 
                    }
                 }
             }
          }

           

         return false ;

         break;


       default :
         if ( x_cord == x && y_cord == y  )
          return true ;
        break;
    }


  return false ;

}

bool Tracker::PossibleUpgrade( int y , int dir )
{

  if ( dir == 1 && y == 7 )
    return true ;
  
  else if ( dir == -1 && y == 0 )
    return true ;
  else
   return false ;


  return false ;
}

