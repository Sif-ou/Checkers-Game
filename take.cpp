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
         top = 0 ;
         bottom  = 0 ;
         
}


void TakeDirection::SetTake ( Cordinates cords , Cordinates opp_cord , Cordinates change_cord  )
{
        this->cords = cords ;
        this->opp_cord = opp_cord ;
        this->change_cord = change_cord ;
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


void TakeDirection::SetDirectionKing ( bool right , bool left , bool top , bool bottom )
{
    this->right = right ;
    this->left = left ;
    this->top = top ;
    this->bottom = bottom ;
}






int TakeDirection::getDirection()
{
        int n = ( right == true ? direction_move_1 : UPGRADE_PIECE_DIRECTION ) ;

        n = (  left == true ? n+2: n ) ;

        return n ;
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



void Take:: ScanPiece ( cell (&board)[GRID][GRID] , Team * temp_team , int num ) 
{

   /* ResetTakes() ;

    Cordinates piece_cord , opp_cord ;
    TakeDirection take_element ;

    int y , x1 , x2 ;

         piece_cord = temp_team->Pieces[num]->GetCordinates() ;

         switch ( temp_team->Pieces[num]->GetDirection() )
         {
            case 0 :
             break;

            default :

             y = ( AllowMove( piece_cord.y , temp_team->direction ) 
                  ? piece_cord.y + temp_team->direction : direction_move__1 ) ;

             if ( y != direction_move__1 )
             {
                 x1 = piece_cord.x + direction_move_1 ;
                 x2 = piece_cord.x + direction_move__1 ;

                 x1 = ( AllowValue ( piece_cord.x ) &&  
                       ( board[y][x1].empty == false && board[y][x1].id != temp_team->id )
                        ? x1 : -1  
                      ) ;

                 x2 = ( AllowValue ( piece_cord.x ) && 
                        ( board[y][x2].empty == false && board[y][x2].id != temp_team->id )
                        ? x2 : -1  
                      ) ;
                 if ( ( x1 != direction_move__1 || x2 != direction_move__1 ) && AllowMove ( y , temp_team->direction ) )
                 {
                    opp_cord.SetCord( piece_cord.x , y ) ;

                    y += temp_team->direction ;
                    int temp_direction , direction1 , direction2 ;

                    direction1 = ( AllowMove( x1 , direction_move_1 ) && board[y][x1 + direction_move_1 ].empty 
                                   ? direction_move_1 : UPGRADE_PIECE_DIRECTION );
                    direction2 = ( AllowMove( x2 , direction_move__1 ) && board[y][x2 + direction_move__1 ].empty 
                                   ? 2 : UPGRADE_PIECE_DIRECTION );
                    temp_direction = direction1 + direction2 ;
                    take_element.SetTake( piece_cord , opp_cord , temp_direction ) ;
                


                    if ( temp_direction != 0 )
                        take_list.push_back( take_element ) ;
                    
                 }
             }

             break;
 
         }*/

}




void Take::ScanBoard(  cell (&board)[GRID][GRID] , Team * temp_team  )
{
     
     ResetTakes() ;
 
     Cordinates temp_cord ;
     TakeDirection take_elemnt ;

     int y = 0 , x1 = 0 , x2 = 0 , x3 = 0  , x4 = 0  ;


    for ( int i = 0 ; i < NUMBER_OF_PIECES ; i++ )    // <---- ' NUMBER_OF_PIECES ' is no good , replace with current_number_of_pieces 
      if ( temp_team->Pieces[i]->isAlive() )          //       that track how many pices left in the board                                
      { 

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


                  

            Cordinates temp_cord2 ;
            temp_cord2.y = y ;
            temp_cord2.x = temp_cord.x ;
            
             take_elemnt.SetTake ( temp_cord , temp_cord1 , temp_cord2 ) ;
             take_elemnt.SetTakeInfo ( i ) ;

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
       
       /* else */ // king condition 

       }
     

                                                
}


