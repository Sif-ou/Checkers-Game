#include "take.hpp"

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
     if ( take.getNum() == num )
       temp = take.getCords() ;

       return temp ;
}

Cordinates Take::getChangeCord ( int num )
{
     Cordinates temp ;
    for (auto& take : take_list ) 
     if ( take.getNum() == num )
      temp = take.getChangeCords() ;

         return temp ;

}

Cordinates Take::getEnemyCord  ( int num )
{
     Cordinates temp ;
    for (auto& take : take_list ) 
     if ( take.getNum() == num )
       temp = take.getEnemyCords() ;

    return temp ;
}

int Take::getDirection ( int num )
{

    int n ;
    for (auto& take : take_list ) 
     if ( take.getNum() == num )
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


    for ( int i = 0 ; i < NUMBER_OF_PIECES ; i++ )
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
    
    /*ResetTakes() ;

    Cordinates piece_cord , opp_cord ;
    TakeDirection take_element ;

    int y , x1 , x2 ;

    for ( int i = 0 ; i < NUMBER_OF_PIECES ; i++ )
    {
       if ( temp_team->Pieces[i]->PieceState() )
       {
         
         piece_cord = temp_team->Pieces[i]->GetCordinates() ;

         switch ( temp_team->Pieces[i]->GetDirection() )
         {
            case 0 :
             break;

            default :

             y = piece_cord.y + temp_team->direction ;
             y = ( AllowValue( y ) ? y : direction_move__1 ) ;

             if ( y != direction_move__1 )
             {
                x1 = ( ( AllowMove ( piece_cord.x , direction_move_1 ) && board[y][ piece_cord.x + direction_move_1 ].empty == false ) 
                            &&
                        board[y][ piece_cord.x + direction_move_1 ].id != temp_team->id 
                         ?  piece_cord.x + direction_move_1  : direction_move__1 ) ;
                         
                x2 = ( ( AllowMove ( piece_cord.x , direction_move__1 ) && board[y][ piece_cord.x + direction_move__1 ].empty == false ) 
                            &&
                        board[y][ piece_cord.x + direction_move__1 ].id != temp_team->id 
                         ?  piece_cord.x + direction_move__1  : direction_move__1 ) ;

                 if ( ( x1 != direction_move__1 || x2 != direction_move__1 ) && AllowMove ( y , temp_team->direction ) )
                 {
                    opp_cord.SetCord( piece_cord.x , y ) ;


                    y += temp_team->direction ;
                    x1 = piece_cord.x + direction_move_1 ;
                    x2 = piece_cord.x + direction_move__1 ;
                    
                    int temp_direction , direction1 , direction2 ;

                    direction1 = ( AllowMove ( x1 , direction_move_1 ) && board[y][x1+direction_move_1].empty == true  
                                   ? direction_move_1 : UPGRADE_PIECE_DIRECTION );
                    direction2 = ( AllowMove ( x2 , direction_move__1 ) && board[y][x2+direction_move__1].empty == true
                                   ? 2 : UPGRADE_PIECE_DIRECTION );

                    temp_direction = (  direction1 + direction2 > 0 ?  direction1 + direction2 : direction_move__1 ) ;

                    take_element.SetTake( piece_cord , opp_cord , temp_direction ) ;

                    if ( temp_direction != direction_move__1 )
                         take_list.push_back( take_element ) ;
                    
                 }
             }

             break;
 
         }

       }
    }*/


    

}


