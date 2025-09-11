#include "piece.hpp"


 void DrawO ( SDL_Renderer * r , SDL_Color te , float x , float y )
{

    int rad = 25 ;
    double s = PI / 180 ;
    SDL_SetRenderDrawColor ( r , te.r , te.g , te.b , te.a ) ;   
       for ( int i = 0 ; i <= 360 ; i++ )
         // ThickPoint ( r ,  x + (cos ( s * i ) * rad  ) , y+( sin(s*i) * rad ) ) ;
         SDL_RenderDrawPoint ( r , x + (cos ( s * i ) * rad  ) , y+( sin(s*i) * rad ) ) ;
       // SDL_RenderDrawPoint ( r ,  point.x + (cos ( s * i ) * rad  ) , point.y+( sin(s*i) * rad ) );
}

void FillO (SDL_Renderer * r , SDL_Color te , float x , float y)
{
    int rad = 25 ; 
    double s = PI / 180 ;
    SDL_SetRenderDrawColor ( r , te.r , te.g , te.b , te.a ) ;   
       for ( int i = 0 ; i <= 360 ; i++ )
        {
          SDL_RenderDrawPoint ( r , x + (cos ( s * i ) * rad  ) , y+( sin(s*i) * rad ) ) ;
          for ( int j = x + (cos ( s * i ) * rad ) ; j >= x - (cos ( s * i ) * rad  ) ; j-- )
           SDL_RenderDrawPoint ( r , j , y+( sin(s*i) * rad ) ) ;
        }
         

}


void upO (SDL_Renderer * r ,  float x , float y)
{
    int rad = 10 ; 
    double s = PI / 180 ;
    SDL_SetRenderDrawColor ( r , 255 , 255 , 255 , SDL_ALPHA_OPAQUE ) ;   
       for ( int i = 0 ; i <= 360 ; i++ )
        {
          SDL_RenderDrawPoint ( r , x + (cos ( s * i ) * rad  ) , y+( sin(s*i) * rad ) ) ;
          for ( int j = x + (cos ( s * i ) * rad ) ; j >= x - (cos ( s * i ) * rad  ) ; j-- )
           SDL_RenderDrawPoint ( r , j , y+( sin(s*i) * rad ) ) ;
        }
}


void Piece::InitPiece( int x , int y , char co , int direction , char color )
{


    pos.x =  ( x + 1 )  * D - VIDE ;
    pos.y =  ( y + 1 ) * D  - VIDE ;
    pos.w = w ;
    pos.h = h ;
    id = color ;
    alive = true ;


    SetDirection( direction ) ;
    SetPieceColor ( co ) ;



}


void Piece::SetDirection( int n )
{
   dir = n ; 
}

SDL_Color Piece::SetPieceColor( char color ) 
{
    switch ( color )
    {
       case 'r' :
         p_color.r = 255 ;
         p_color.g = 0 ;
         p_color.b = 0 ;
         p_color.a = SDL_ALPHA_OPAQUE  ;
        break;

       case 'b' :
         p_color.r = 0 ;
         p_color.g = 0 ;
         p_color.b = 255 ;
         p_color.a = SDL_ALPHA_OPAQUE  ;
        break;

        default : 
         p_color.r = 255 ;
         p_color.g = 255 ;
         p_color.b = 255 ;
         p_color.a = SDL_ALPHA_OPAQUE  ;
         break;
    }


    return p_color ;
}


void Piece::DrawPiece ( SDL_Renderer * r ) 
{
     if ( alive == true )
       if ( dir == 0 )
         {
            FillO ( r ,  SetPieceColor ( id ) , pos.x , pos.y ) ;
            upO( r , pos.x , pos.y ) ;
         }
        else
          FillO ( r ,  SetPieceColor ( id ) , pos.x , pos.y ) ;
      
}

void Piece::RemovePiece ( SDL_Renderer * r )
{
      SDL_Color color ;
         color.r = 0 ;
         color.g = 0 ;
         color.b = 0 ;
         color.a = SDL_ALPHA_OPAQUE  ;
       FillO ( r , color , pos.x , pos.y ) ;
}



void Piece::DeadPiece()
{
   alive = false ;
}

void Piece::ChangePieceCord ( int x , int y )
{
    pos.x =  ( x + 1 )  * D - VIDE ;
    pos.y =  ( y + 1 ) * D  - VIDE ;
}