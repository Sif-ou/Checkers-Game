#include "take.hpp"



void TakeDirection::Default()
{
         cords.x = -1 ;
         cords.y = -1 ;
         opp_cord.x = -1 ;
         opp_cord.y = -1 ;
         change_cord.x = -1 ;
         change_cord.y = -1 ; 

         left = 0 ;
         right = 0 ;


         this->top_left = false ; 
         this->top_right = false ; 
         this->bottom_left = false ;
         this->bottom_right = false ;

         for ( int i = 0 ; i <= 3 ; i++ )
          {
            change_cord_king[i].x = direction_move__1 ;
            change_cord_king[i].y = direction_move__1 ;
          } 
         
}


void TakeDirection::SetTake ( Cordinates cords , Cordinates opp_cord , Cordinates change_cord  )
{
        this->cords = cords ;
        this->opp_cord = opp_cord ;
        this->change_cord = change_cord ;
}


void TakeDirection::setKingTake ( Cordinates t1 , Cordinates t3 , Cordinates t4 , Cordinates t2 )
{
    change_cord_king[0] = t1 ;
    change_cord_king[1] = t3 ;
    change_cord_king[2] = t4 ;
    change_cord_king[3] = t2 ; 
    
           /*printf ( " SET SHIT BABY !! \n " 
                   " x1 ==> %d \n " 
                   " x3 ==> %d \n " 
                   " x4 ==> %d \n " 
                   " x2 ==> %d \n " , change_cord_king[0].x , change_cord_king[1].x , change_cord_king[2].x , change_cord_king[3].x ) ;  */

}



void TakeDirection::SetTakeInfo ( int num )
{
    this->num = num ;
}



void TakeDirection::SetDirection ( bool right ,  bool left )
{
    this->right = right ;
    this->left = left ;
}


void TakeDirection::SetDirectionKing ( bool top_left , bool top_right , bool bottom_left , bool bottom_right  )
{

         this->top_left = top_left ; 
         this->top_right = top_right ; 
         this->bottom_left = bottom_left ;
         this->bottom_right = bottom_right ;

}


int TakeDirection::getDirection()
{
        
    if ( !bottom_left && !bottom_right && !top_left && !top_right )
     {
        int n = ( right == true ? direction_move_1 : UPGRADE_PIECE_DIRECTION ) ;
        n = (  left == true ? n+2: n ) ;
         return n ;
     }
    else
    {
        return UPGRADE_PIECE_DIRECTION ;
    }

    return direction_move__1 ;

}


Cordinates* TakeDirection::getKingDirections() 
{

    return change_cord_king ;
    
}


Cordinates TakeDirection::GetCords ()  { return cords ; } 
Cordinates TakeDirection::GetEnemyCords() { return opp_cord ; } 
Cordinates TakeDirection::GetChangeCords() { return change_cord ; } 


int TakeDirection::GetNum () { return num ; }  


bool Take::isTakeEmpty()
{
    return take_list.empty() ;
}

void Take::ResetTakes()
{
    take_list.clear() ;
}

std::list<TakeDirection> Take::getTakeList()
{
    return take_list ;
}

Cordinates Take::getCord ( int num )
{
    Cordinates temp ;

    for (auto& take : take_list ) 
     if ( take.GetNum() == num )
       temp = take.GetCords() ;

       return temp ;
}

Cordinates Take::getChangeCord ( int num )
{
     Cordinates temp ;
    for (auto& take : take_list ) 
     if ( take.GetNum() == num )
      temp = take.GetChangeCords() ;

         return temp ;

}

Cordinates Take::getEnemyCord  ( int num )
{
     Cordinates temp ;
    for (auto& take : take_list ) 
     if ( take.GetNum() == num )
       temp = take.GetEnemyCords() ;

    return temp ;
}

int Take::getDirection ( int num )
{

    int n ;
    for (auto& take : take_list ) 
     if ( take.GetNum() == num )
      n = take.getDirection() ;

    return n ;

}

Cordinates* Take::getKingTakes( int num ) 
{
 
    for (auto& take : take_list ) 
     if ( take.GetNum() == num )
      return take.getKingDirections() ;

    return nullptr ;
    
} 


void Take::ScanBoard(  cell (&board)[GRID][GRID] , Team * temp_team  )
{
     
     ResetTakes() ;
 
     Cordinates temp_cord ;
     TakeDirection take_elemnt ;

     int y = 0 , x1 = 0 , x2 = 0 , x3 = 0  , x4 = 0  ;




    for ( int i = 0 ; i < NUMBER_OF_PIECES ; i++ )    
      if ( temp_team->Pieces[i]->isAlive() )          //       that track how many pices left in the board                                
      { 

        //printf( " inside the loop wiht i => %d \n" , i ) ;
       take_elemnt.Default() ;
       temp_cord = temp_team->Pieces[i]->GetCordinates() ;
       y = temp_cord.y + temp_team->direction ;
       x1 = temp_cord.x ;
       x2 = x1 ;


       if ( temp_team->Pieces[i]->GetDirection() != 0 && AllowValue ( y )  )
       {

          x1 += direction_move_1 ;
          x2 += direction_move__1 ;
          
          x1 = ( AllowValue ( x1 ) && 
                 ( board[y][x1].empty == false && board[y][x1].id != temp_team->id ) 
                 ? x1 : direction_move__1 ) ;

          x2 = ( AllowValue ( x2 ) && 
                 ( board[y][x2].empty == false && board[y][x2].id != temp_team->id ) 
                 ? x2 : direction_move__1 ) ;

          Cordinates temp_cord1 ;
          temp_cord1.y = y ;
          temp_cord1.x = temp_cord.x ;

          y += temp_team->direction ;

          if ( ( x1 != direction_move__1 || x2 != direction_move__1 ) && AllowValue ( y ) )
          {
             x1 = ( ( x1 != direction_move__1 && AllowMove ( x1 , direction_move_1 ) )
                   && board[y][ x1 + direction_move_1 ].empty  
                   ? x1 + direction_move_1 : direction_move__1 ) ;

             x2 = ( ( x2 != direction_move__1 && AllowMove( x2 , direction_move__1 ) )
                   && board[y][x2 + direction_move__1 ].empty  
                   ? x2 + direction_move__1 : direction_move__1 ) ;


                  

           // printf( " reached this far \n") ;
            Cordinates temp_cord2 ;
            temp_cord2.y = y ;
            temp_cord2.x = temp_cord.x ;
            
             take_elemnt.SetTake ( temp_cord , temp_cord1 , temp_cord2 ) ;
             take_elemnt.SetTakeInfo ( i ) ;

            bool left = ( x2 != direction_move__1 ? true : false ) , 
                 right = ( x1 != direction_move__1 ? true : false ) ;

            //printf( " checking right and left shit  \n") ;
             if ( left || right )
             {
                 //printf ( " we reached here \n" ) ;
                 take_elemnt.SetDirection( right , left ) ;
                 take_list.push_back ( take_elemnt ) ;
             }

             //printf( " is it empty man ? ===> %d \n " , isTakeEmpty() ) ;

             // printf ( " ==> %d , %d \n " , left , right ) ;


          }
       }   
       
       else if ( temp_team->Pieces[i]->GetDirection() == 0 )
       {
        
          take_elemnt.Default() ;
          temp_cord = temp_team->Pieces[i]->GetCordinates() ;
          y = temp_cord.y ;
          int y1 = y ;
          x1 = temp_cord.x ;
          x2 = x1 ;

          int x3 = x1 , x4 = x1 ;
          
          bool top_left = false, top_right = false, bottom_left = false, bottom_right = false;
          
          bool top_left_blocked = false ,
               top_right_blocked = false ,
               bottom_left_blocked = false ,
               bottom_right_blocked = false ;

          
         Cordinates temp1 , temp2 , temp3 , temp4 ;
          
          temp1.x = direction_move__1 ; temp1.y = direction_move__1 ;
          temp2.x = direction_move__1 ; temp2.y = direction_move__1 ;
          temp4.x = direction_move__1 ; temp4.y = direction_move__1 ;
          temp3.x = direction_move__1 ; temp3.y = direction_move__1 ;
          
          while ( 1 )
          { 

              y += direction_move__1 ;
              y1 += direction_move_1 ;

              x1 += direction_move__1 ;
              x2 += direction_move_1 ;
              x3 += direction_move_1 ; 
              x4 += direction_move__1 ;

              if (!AllowValue(y) && !AllowValue(y1) ) {
                  break;
              }
          
              if (!top_left_blocked) 
              {
                  if (!AllowValue(x1)) {
                      top_left_blocked = true;
                  }
                  else if (!board[y][x1].empty) 
                  {
                      top_left_blocked = true; 
          
                      if (board[y][x1].id != temp_team->id) 
                      {
                          const int _y = y + direction_move__1;
                          const int _x = x1 + direction_move__1;
                          if (AllowValue(_y) && AllowValue(_x) && board[_y][_x].empty) {
                             
                             temp1.x = _x ;
                             temp1.y = _y ;
                             top_left = true;
                          }
                      }
                  }
              }
          

              if (!top_right_blocked ) 
              {

                  if (!AllowValue(x3)) {
                      top_right_blocked = true;
                  }

                  else if (!board[y][x3].empty ) 
                  {
                      top_right_blocked = true; 
          
                      if (board[y][x3].id != temp_team->id) 
                      {
                          const int _y = y + direction_move__1;
                          const int _x = x3 + direction_move_1;
                          if (AllowValue(_y) && AllowValue(_x) && board[_y][_x].empty) {
                             temp3.x = _x ;
                             temp3.y = _y ;
                             top_right = true;
                          }
                      }
                  }

              }
          



              if (!bottom_left_blocked) 
              {
                  if (!AllowValue(x4)) {
                      bottom_left_blocked = true;
                  }
                  else if (!board[y1][x4].empty) 
                  {
                      bottom_left_blocked = true; 
          
                      if (board[y1][x4].id != temp_team->id) 
                      {
                          const int _y = y1 + direction_move_1;
                          const int _x = x4 + direction_move__1;
                          if (AllowValue(_y) && AllowValue(_x) && board[_y][_x].empty) {
                             
                             temp4.x = _x ;
                             temp4.y = _y ;
                             bottom_left = true;
                          }
                      }
                  }
              }
          

              if (!bottom_right_blocked ) 
              {

                  if (!AllowValue(x2)) {
                      bottom_right_blocked = true;
                  }

                  else if (!board[y1][x2].empty ) 
                  {
                      bottom_right_blocked = true; 
          
                      if (board[y1][x2].id != temp_team->id) 
                      {
                          const int _y = y1 + direction_move_1;
                          const int _x = x2 + direction_move_1;
                          if (AllowValue(_y) && AllowValue(_x) && board[_y][_x].empty) {
                             temp2.x = _x ;
                             temp2.y = _y ;  
                             bottom_right = true;
                          }
                      }
                  }

              }
          

              if ( top_left_blocked && top_right_blocked && bottom_left_blocked && bottom_right_blocked ) {
                  break;
              }
          }

          

          if ( top_left || top_right || bottom_left || bottom_right  )
          {
            take_elemnt.SetTake ( temp_cord , temp_cord , temp_cord ) ;
            take_elemnt.setKingTake ( temp1 , temp3 , temp4 , temp2 ) ;
            take_elemnt.SetDirectionKing ( top_left , top_right , bottom_left , bottom_right ) ;
            take_elemnt.SetTakeInfo ( i ) ;
            take_elemnt.SetTake ( temp_cord , temp_cord , temp_cord ) ;
            take_list.push_back ( take_elemnt ) ;
          }


        
       }


       }
     

                                                
}

void Take::Scan_Advantage ( cell (&board)[GRID][GRID] , Team * temp_team , int peice_num ) 
{
    ResetTakes() ;

     Cordinates temp_cord ;
     TakeDirection take_elemnt ;

     int y = 0 , x1 = 0 , x2 = 0 , x3 = 0  , x4 = 0  ;

     if ( temp_team->Pieces[peice_num]->isAlive() )          //       that track how many pices left in the board                                
      { 

       temp_cord = temp_team->Pieces[peice_num]->GetCordinates() ;
       y = temp_cord.y + temp_team->direction ;
       x1 = temp_cord.x ;
       x2 = x1 ;


       if ( temp_team->Pieces[peice_num]->GetDirection() != 0 && AllowValue ( y )  )
       {

          x1 += direction_move_1 ;
          x2 += direction_move__1 ;
          
          x1 = ( AllowValue ( x1 ) && 
                 ( board[y][x1].empty == false && board[y][x1].id != temp_team->id ) 
                 ? x1 : direction_move__1 ) ;

          x2 = ( AllowValue ( x2 ) && 
                 ( board[y][x2].empty == false && board[y][x2].id != temp_team->id ) 
                 ? x2 : direction_move__1 ) ;

          Cordinates temp_cord1 ;
          temp_cord1.y = y ;
          temp_cord1.x = temp_cord.x ;

          y += temp_team->direction ;

          if ( ( x1 != direction_move__1 || x2 != direction_move__1 ) && AllowValue ( y ) )
          {
             x1 = ( ( x1 != direction_move__1 && AllowMove ( x1 , direction_move_1 ) )
                   && board[y][ x1 + direction_move_1 ].empty  
                   ? x1 + direction_move_1 : direction_move__1 ) ;

             x2 = ( ( x2 != direction_move__1 && AllowMove( x2 , direction_move__1 ) )
                   && board[y][x2 + direction_move__1 ].empty  
                   ? x2 + direction_move__1 : direction_move__1 ) ;


            Cordinates temp_cord2 ;
            temp_cord2.y = y ;
            temp_cord2.x = temp_cord.x ;
            
             take_elemnt.SetTake ( temp_cord , temp_cord1 , temp_cord2 ) ;
             take_elemnt.SetTakeInfo ( peice_num ) ;

            bool left = ( x2 != direction_move__1 ? true : false ) , 
                 right = ( x1 != direction_move__1 ? true : false ) ;

            
             if ( left || right )
             {
                 take_elemnt.SetDirection( right , left ) ;
                 take_list.push_back ( take_elemnt ) ;
             }

             // printf ( " ==> %d , %d \n " , left , right ) ;


          }
       }   
       
       else if ( temp_team->Pieces[peice_num]->GetDirection() == 0 )
       {
        
         Cordinates temp1 , temp2 , temp3 , temp4 ;
          
          temp1.x = direction_move_1 ; temp1.y = direction_move__1 ;
          temp2.x = direction_move_1 ; temp2.y = direction_move__1 ;
          temp3.x = direction_move_1 ; temp3.y = direction_move__1 ;
          temp4.x = direction_move_1 ; temp4.y = direction_move__1 ;

          temp_cord = temp_team->Pieces[peice_num]->GetCordinates() ;
          y = temp_cord.y ;
          int y1 = y ;
          x1 = temp_cord.x ;
          x2 = x1 ;

          int x3 = x1 , x4 = x1 ;
          
          bool top_left = false, top_right = false, bottom_left = false, bottom_right = false;
          
          bool top_left_blocked = false ,
               top_right_blocked = false ,
               bottom_left_blocked = false ,
               bottom_right_blocked = false ;

          
          while ( 1 )
          { 

              y += direction_move__1 ;
              y1 += direction_move_1 ;

              x1 += direction_move__1 ;
              x2 += direction_move_1 ;
              x3 += direction_move_1 ; 
              x4 += direction_move__1 ;

              if (!AllowValue(y) && !AllowValue(y1) ) {
                  break;
              }
          
              if (!top_left_blocked) 
              {
                  if (!AllowValue(x1)) {
                      top_left_blocked = true;
                  }
                  else if (!board[y][x1].empty) 
                  {
                      top_left_blocked = true; 
          
                      if (board[y][x1].id != temp_team->id) 
                      {
                          const int _y = y + direction_move__1;
                          const int _x = x1 + direction_move__1;
                          if (AllowValue(_y) && AllowValue(_x) && board[_y][_x].empty) {
                             temp1.x = _x ;
                             temp1.y = _y ; 
                             top_left = true;
                          }
                      }
                  }
              }
          

              if (!top_right_blocked ) 
              {

                  if (!AllowValue(x3)) {
                      top_right_blocked = true;
                  }

                  else if (!board[y][x3].empty ) 
                  {
                      top_right_blocked = true; 
          
                      if (board[y][x3].id != temp_team->id) 
                      {
                          const int _y = y + direction_move__1;
                          const int _x = x3 + direction_move_1;
                          if (AllowValue(_y) && AllowValue(_x) && board[_y][_x].empty) {
                             temp3.x = _x ;
                             temp3.y = _y ; 
                             top_right = true;
                          }
                      }
                  }

              }
          



              if (!bottom_left_blocked) 
              {
                  if (!AllowValue(x4)) {
                      bottom_left_blocked = true;
                  }
                  else if (!board[y1][x4].empty) 
                  {
                      bottom_left_blocked = true; 
          
                      if (board[y1][x4].id != temp_team->id) 
                      {
                          const int _y = y1 + direction_move_1;
                          const int _x = x4 + direction_move__1;
                          if (AllowValue(_y) && AllowValue(_x) && board[_y][_x].empty) {
                             temp4.x = _x ;
                             temp4.y = _y ; 
                             bottom_left = true;
                          }
                      }
                  }
              }
          

              if (!bottom_right_blocked ) 
              {

                  if (!AllowValue(x2)) {
                      bottom_right_blocked = true;
                  }

                  else if (!board[y1][x2].empty ) 
                  {
                      bottom_right_blocked = true; 
          
                      if (board[y1][x2].id != temp_team->id) 
                      {
                          const int _y = y1 + direction_move_1;
                          const int _x = x2 + direction_move_1;
                          if (AllowValue(_y) && AllowValue(_x) && board[_y][_x].empty) {
                             temp2.x = _x ;
                             temp2.y = _y ; 
                             bottom_right = true;
                          }
                      }
                  }

              }
          

              if ( top_left_blocked && top_right_blocked && bottom_left_blocked && bottom_right_blocked ) {
                  break;
              }
          }

          

          if ( top_left || top_right || bottom_left || bottom_right  )
          {
            take_elemnt.SetTake ( temp_cord , temp_cord , temp_cord ) ;
            take_elemnt.setKingTake ( temp1 , temp3 , temp4 , temp2 ) ;
            take_elemnt.SetDirectionKing ( top_left , top_right , bottom_left , bottom_right ) ;
            take_elemnt.SetTakeInfo ( peice_num ) ;
            take_elemnt.SetTake ( temp_cord , temp_cord , temp_cord ) ;
            take_list.push_back ( take_elemnt ) ;
          }


        
       }


      }
}

