#include "struct.hpp"


void ChangeTurn ( char &id ) 
{
    id = ( id == 'r' ? 'b' : 'r' ) ;
}

Cordinates Draw_Cord ( Cordinates temp_cord ) 
{

    temp_cord.x = temp_cord.x * ( PIECE_WIDTH + PIECE_SPACE ) + PIECE_VOID ;
    temp_cord.y = temp_cord.y * ( PIECE_HEIGHT + PIECE_SPACE ) + PIECE_VOID ;
    
    return temp_cord ;
}

Cordinates Board_Cord ( Cordinates temp_cord ) 
{
    temp_cord.x = ( temp_cord.x - PIECE_VOID ) / ( PIECE_WIDTH + PIECE_SPACE ) ;
    temp_cord.y = ( temp_cord.y - PIECE_VOID ) / ( PIECE_WIDTH + PIECE_SPACE ) ;
    return temp_cord ;
}



SDL_Rect Cords_Into_Rect ( SDL_Rect temp_rect , Cordinates temp_cord )
{
    temp_rect.x = temp_cord.x ; 
    temp_rect.y = temp_cord.y ;

    return temp_rect ;
}


Cordinates Mouse_To_BOARD_Cord ( Cordinates temp_cord ) 
{
    temp_cord.x /= CELL_DES ;
    temp_cord.y /= CELL_DES ;

    return temp_cord ;
}

Cordinates BOARD_To_MOUSE_Cord ( Cordinates temp_cord ) 
{
    temp_cord.x *= CELL_DES ;
    temp_cord.y *= CELL_DES ;

    return temp_cord ;
}

bool AllowMove ( int x , int dir )
{
    x += dir ; 

    return ( x > 7 || x < 0 ? false : true ) ;
}

bool AllowValue ( int x ) 
{
    return ( x > 7 || x < 0 ? false : true ) ;
}

