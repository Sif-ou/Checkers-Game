#include "Movement.hpp"

Movement::Movement( SDL_Renderer * r )
{
    SDL_Surface * move_surface = IMG_Load ( "assets/move.png" ) ;

    move_texture = SDL_CreateTextureFromSurface ( r , move_surface ) ;

    SDL_FreeSurface ( move_surface ) ;

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
    draw_case = direction_move__1 ;
    Kingtake = false ;

    KingMove[0] = direction_move__1 ; 
    KingMove[1] = direction_move__1 ; 
    KingMove[2] = direction_move__1 ; 

    curr_cords.Default() ;
}

void Movement::ScanBoard_ForMove ( Cordinates temp_cord , cell (&board)[GRID][GRID]  , int direction )
{
    this->direction = direction ;
    int case1 , case2 ; 


    if ( direction != 0 )
     {
        y = temp_cord.y ;
        y = ( AllowMove ( y , this->direction ) ? y + this->direction : -1 ) ; 
        x1 = ( AllowMove( temp_cord.x , direction_move_1 ) ? temp_cord.x + direction_move_1 : -1 ) ; 
        x2 = ( AllowMove( temp_cord.x , direction_move__1 ) ? temp_cord.x + direction_move__1 : -1 ) ;
    
        curr_cords.y = temp_cord.y ;
        curr_cords.x = temp_cord.x ;

           case1 = ( board[y][x1].empty == true && x1 != direction_move__1 ? 1 : 0 ) , 
           case2 = ( board[y][x2].empty == true && x2 != direction_move__1 ? 2 : 0 ) ;

        move_case = ( case1 + case2 > 0 ? case1 + case2 : -1 ) ;
     }
    else
     {
       /*       x1       x3  
                  -    -
                   -  -
                    --   <---- king piece scan 
                   -  -
                  -    -
                x4      x2   
          
         ( y , x1 , x2 , x3 , x4 )
       */



       bool top_right = true , top_left = true , bottom_right = true , bottom_left = true ;
       y = temp_cord.y ; 
       
       curr_cords.y = temp_cord.y ;
       curr_cords.x = temp_cord.x ;
       
       move_case = UPGRADE_PIECE_DIRECTION ;
       
         case1 = temp_cord.y ;
         case2 = temp_cord.y ;

      const int i = 3 ;

      for ( int j = 0 ; j <= i ; j++ )


       x1 = UPGRADE_PIECE_DIRECTION ;      x2 = UPGRADE_PIECE_DIRECTION ;
       x3 = UPGRADE_PIECE_DIRECTION ;      x4 = UPGRADE_PIECE_DIRECTION ;


       const int base_x = temp_cord.x;
       
       do 
       {

           if (case1 != direction_move__1)
           {


               if (top_left)
               {
                   int xdirection = (direction_move__1 * x1) + direction_move__1 ;                    

                   if ( AllowMove(case1 , xdirection ) && AllowMove(base_x, xdirection  ) )
                   {

                       if ( board[ case1 + xdirection ][ base_x + xdirection  ].empty ) 
                         { x1++; }
                       else                                     
                        { top_left = false; }
                   }
                   else
                    top_left = false ;
               }
       
               if (top_right)
               {
                   int xdirection = (direction_move_1 * x3) + direction_move_1 ,
                       ydirection = (direction_move__1 * x3) + direction_move__1 ;  

                   if (AllowMove(case1 , ydirection ) && AllowMove(base_x, xdirection  ))
                   {
                       if (board[ case1 + ydirection ][base_x + xdirection ].empty) { x3++; }
                       else                                     { top_right = false; }
                   }
                   else
                    top_right = false ;
               }


           }
       
           if (case2 != direction_move__1)
           {

               if (bottom_right)
               {
                   int xdirection = (direction_move_1 * x2) + direction_move_1 ;
                      
                   if (AllowMove(case2, xdirection) && AllowMove(base_x, xdirection ))
                   {
                       if (board[case2+xdirection][base_x + xdirection ].empty) { x2++; }
                       else                                     { bottom_right = false; }
                   }
                   else
                    bottom_right = false ;
               }

       
               if (bottom_left)
               {
                   int xdirection = (direction_move__1 * x4) + direction_move__1 ,
                       ydirection = (direction_move_1 * x4) + direction_move_1 ;  
                   if ( AllowMove(case2 , ydirection) && AllowMove( base_x, xdirection ) )
                   {
                       if ( board[case2+ydirection][base_x + xdirection ].empty ) 
                          { x4++; }
                       else                                     
                         { bottom_left = false; }
                   }
                   else
                    bottom_left = false ;
               }

           }
       

           if (!top_left    && !top_right)    { case1 = direction_move__1; }
           if (!bottom_right && !bottom_left) { case2 = direction_move__1; }
       

       } while (case1 != direction_move__1 || case2 != direction_move__1);




     }
}

void Movement::Move_Draw( SDL_Renderer * r) 
{ 
    Cordinates temp_cord ;


    switch ( move_case )
    {

       case 0 : 
       {
        
        int tx1 = x1 , tx2 = x2 , tx3 = x3 , tx4 = x4 ;

       
         if ( !Kingtake )
         {
        
           while ( tx4 > 0 || tx3 > 0 || tx2 > 0 || tx1 > 0  ) 
           {
   
              if ( tx1 > 0 )
              {
                temp_cord.x = curr_cords.x - tx1 ;
                temp_cord.y = curr_cords.y - tx1 ;
                draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
                tx1--;
                SDL_RenderCopy ( r , move_texture , &Move_rect , &draw_rect ) ;
              }
   
   
              if ( tx2 > 0 )
              {
                temp_cord.x = curr_cords.x + tx2 ;
                temp_cord.y = curr_cords.y + tx2 ;
                draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
                tx2--;
                SDL_RenderCopy ( r , move_texture , &Move_rect , &draw_rect ) ;
              }
   
              if ( tx3 > 0 )
              {
                temp_cord.x = curr_cords.x + tx3 ;
                temp_cord.y = curr_cords.y - tx3 ;
                draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
                tx3--;
                SDL_RenderCopy ( r , move_texture , &Move_rect , &draw_rect ) ;
              }
   
              if ( tx4 > 0 )
              {
                temp_cord.x = curr_cords.x - tx4 ;
                temp_cord.y = curr_cords.y + tx4 ;
                draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
                tx4--;
                SDL_RenderCopy ( r , move_texture , &Move_rect , &draw_rect ) ;
              }
   
           }

         }
         else
         {

   
              if ( tx1 > 0 )
              {
                temp_cord.x = curr_cords.x - tx1  ;
                temp_cord.y = curr_cords.y - tx1  ;
                draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
                SDL_RenderCopy ( r , move_texture , &Move_rect , &draw_rect ) ;
              }
   
   
              if ( tx2 > 0 )
              {
                temp_cord.x = curr_cords.x + tx2  ;
                temp_cord.y = curr_cords.y + tx2  ;
                draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
                SDL_RenderCopy ( r , move_texture , &Move_rect , &draw_rect ) ;
              }
   
              if ( tx3 > 0 )
              {
                temp_cord.y = curr_cords.y - tx3  ;
                temp_cord.x = curr_cords.x + tx3  ;
                draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
                SDL_RenderCopy ( r , move_texture , &Move_rect , &draw_rect ) ;
              }
   
              if ( tx4 > 0 )
              {
                temp_cord.x = curr_cords.x - tx4  ;
                temp_cord.y = curr_cords.y + tx4  ;
                draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
                SDL_RenderCopy ( r , move_texture , &Move_rect , &draw_rect ) ;
              }
  

         }

        
       } 
        break;

       case 1 :
         temp_cord.y = y ;
         temp_cord.x = x1 ;
         draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
         SDL_RenderCopy ( r , move_texture , &Move_rect , &draw_rect ) ;
        break;

       case 2 :
         temp_cord.y = y ;
         temp_cord.x = x2 ;
         draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
         SDL_RenderCopy ( r , move_texture , &Move_rect , &draw_rect ) ;
        break;

       case 3 :
         temp_cord.y = y ;
         temp_cord.x = x1 ;
         draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
         SDL_RenderCopy ( r , move_texture , &Move_rect , &draw_rect ) ;
         temp_cord.x = x2 ;
         draw_rect = Cords_Into_Rect ( draw_rect , Draw_Cord ( temp_cord ) ) ;
         SDL_RenderCopy ( r , move_texture , &Move_rect  , &draw_rect ) ;
        break;

        default : 
         Reset_Move() ;
         break;
    }


}

Cordinates Movement::GetCordinates ()
{
    return curr_cords ;
}

bool Movement::MoveCLicked ( Cordinates temp_cords )  
{


    switch ( move_case )
    {

        case 0 :
        {
        

           while ( ( x4 > 0 || x3 > 0 || x2 > 0 || x1 > 0 ) ) 
         {
            if ( x1 != 0 )
            {

              if ( curr_cords.y - x1 == temp_cords.y && curr_cords.x - x1 == temp_cords.x )
                 return true ;
              

             x1--;

            }

 

            if ( x2 != 0 )
            {
              if ( curr_cords.y + x2 == temp_cords.y && curr_cords.x + x2 == temp_cords.x )
                 return true ;

             x2-- ;

            }

            if ( x3 != 0 )
            {

              if ( curr_cords.y - x3 == temp_cords.y && curr_cords.x + x3 == temp_cords.x )
                 return true ;

             x3--;

            }

            if ( x4 != 0 )
            {

              if ( curr_cords.y + x4 == temp_cords.y && curr_cords.x - x4 == temp_cords.x )
                 return true ;

             x4--;

            }

          }

        } 
         break;
         
        case 1 :
          return ( temp_cords.x == x1 &&
                   temp_cords.y == y ? true : false ) ;
         break;
        
        case 2: 
          return ( temp_cords.x == x2 &&
                   temp_cords.y == y ? true : false ) ;
         break;

        case 3 :
          return ( ( temp_cords.x == x1 || temp_cords.x == x2 ) &&
                   temp_cords.y == y ? true : false ) ;
         break;

        default :
          Reset_Move() ;
          return false ;
         break;
    }


    return false ;

    
  }



void Movement::TakeMove (  Cordinates change_cord , int direction , Cordinates* array  , SDL_Renderer * r )
{

  y = change_cord.y ;

  switch ( direction )
  {


     case 0 : 
     {

      if ( array != nullptr )
      {

        if ( array[0].x == direction_move__1 && array[1].x == direction_move__1 && array[2].x == direction_move__1 && array[3].x == direction_move__1 )
         move_case = direction_move__1 ;
        else
        {
          const int c1 = ( AllowValue( array[0].x ) ? change_cord.x - array[0].x : direction_move__1 ) , 
                    c3 = ( AllowValue( array[1].x ) ? array[1].x - change_cord.x : direction_move__1 ) , 
                    c4 = ( AllowValue( array[2].x ) ? change_cord.x - array[2].x : direction_move__1 ) ,
                    c2 = ( AllowValue( array[3].x ) ? array[3].x - change_cord.x : direction_move__1 ) ;

          x1 = ( AllowValue( c1 ) ? c1 : direction_move__1 ) ;
          x2 = ( AllowValue( c2 ) ? c2 : direction_move__1 ) ;
          x3 = ( AllowValue( c3 ) ? c3 : direction_move__1 ) ;
          x4 = ( AllowValue( c4 ) ? c4 : direction_move__1 ) ;

          
          curr_cords.x = change_cord.x ;
          curr_cords.y = change_cord.y ; 

          Kingtake = true ;


          move_case = UPGRADE_PIECE_DIRECTION ; 


                printf ( 
                 " ################ \n "
                 " x1  => %d \n "
                 " x3  => %d \n "
                 " x4 => %d \n "
                 " x2 => %d \n "
                 " ################ \n "
                 " ################ \n "
                 "  array[0].x  => %d \n "
                 "  array[1].x  => %d \n "
                 "  array[2].x => %d \n "
                 "  array[3].x => %d \n "
                 " ################ \n "
                 " ################ \n "
                 "  c1  => %d \n "
                 "  c3  => %d \n "
                 "  c4 => %d \n "
                 "  c2 => %d \n "
                 " ################ \n ",
                    x1 , x3 , x4 , x2 ,  array[0].x , array[1].x , array[2].x , array[3].x  , c1 , c3 , c4 , c2 ) ;

        }

      }
      else
       move_case = direction_move__1 ;

     }
      break;

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


   Move_Draw ( r ) ;

}

bool Movement::TakeMove_Clicked ( Cordinates temp )
{

   bool r = false ;

   switch ( move_case )
   {
      case 0 :
      
         
        if ( x1 > direction_move__1 )
        {
           const int _x = curr_cords.x - x1 ;
           const int _y = curr_cords.y - x1 ;
           
           if ( AllowValue ( _x ) && AllowValue ( _y ) )
           {
              if ( temp.x == _x && temp.y == _y )
              {
                 KingMove[0] = direction_move__1 ; 
                 KingMove[1] = direction_move__1 ;
                 KingMove[2] = x1 ;
                 r = true ;
              }
           } 
        }

        if ( x3 > direction_move__1 )
        {
           const int _x = curr_cords.x + x3 ;
           const int _y = curr_cords.y - x3 ;
           
           if ( AllowValue ( _x ) && AllowValue ( _y ) )
           {
              if ( temp.x == _x && temp.y == _y )
              {
                 KingMove[0] = direction_move_1 ; 
                 KingMove[1] = direction_move__1 ;
                 KingMove[2] = x3 ;
                 r = true ;
              }
           } 
        }

        if ( x4 > direction_move__1 )
        {
           const int _x = curr_cords.x - x4 ;
           const int _y = curr_cords.y + x4 ;
           
           if ( AllowValue ( _x ) && AllowValue ( _y ) )
           {
              if ( temp.x == _x && temp.y == _y )
              {
                 KingMove[0] = direction_move__1 ; 
                 KingMove[1] = direction_move_1 ;
                 KingMove[2] = x4 ;
                 r = true ;
              }
           } 
        }

        if ( x2 > direction_move__1 )
        {
           const int _x = curr_cords.x + x2 ;
           const int _y = curr_cords.y + x2 ;
           
           if ( AllowValue ( _x ) && AllowValue ( _y ) )
           {
              if ( temp.x == _x && temp.y == _y )
              {
                 KingMove[0] = direction_move_1 ; 
                 KingMove[1] = direction_move_1 ;
                 KingMove[2] = x2 ;
                 r = true ;
              }
           } 

        }
         

                /*printf ( 
                 " x1  => %d \n "
                 " x3  => %d \n "
                 " x4 => %d \n "
                 " x2 => %d \n "
                 " ################ \n "
                 " array[0] => %d \n "
                 " array[1] => %d \n "
                 " array[2] => %d \n " ,
                    x1 , x3 , x4 , x2 , KingMove[0] , KingMove[1] , KingMove[2] ) ;*/
       break;



      case 1 : 

        r = ( temp.x == x1 && temp.y == y ? true : false ) ;

       break;


      case 2 : 

        r = ( temp.x == x2 && temp.y == y ? true : false ) ;

       break; 

      
      case 3 : 

        r = ( ( temp.x == x1 || temp.x == x2 ) && temp.y == y ? true : false ) ;

       break; 

      default :
        Reset_Move() ;
       break;

   }


  //printf( " direction from movement => %d \n " , this->direction ) ; 
  return r ;
}

int Movement::getTakeDirection ()
{
  return this->direction ;
}

void Movement::DeleteMovement()
{
  SDL_DestroyTexture ( this->move_texture ) ;
} 

int* Movement::getKingMove () 
{
  return KingMove ;
}