#pragma once 
#include "Movement.hpp"

class BOARD
{

    private : 

    SDL_Rect board_rect ;        // determine the width and height of the board 
    //cell borad [grid][grid] ;  
    SDL_Rect MoveRect_img ;
        

    SDL_Surface * board_surface = nullptr ; // to load the board img 
    SDL_Surface * piece_surface = nullptr ; 

    

    Team * TeamR = nullptr ;
    Team * TeamB = nullptr ;

    cell borad [GRID][GRID] ;

    public : 

    

    void SetBoard () ;
    void RenderBoard (  SDL_Renderer * r , SDL_Texture * t  ) ;

    void SetTeam () ;
    void Team_In_Board ( Team * temp_Team ) ;
    
    void RendererTeams( SDL_Renderer * r , SDL_Texture * t ) ;
    bool LetPiece_Render ( Piece * temp_Piece ) ;

    bool Correct_Cords ( Cordinates temp_cord ) ;
    bool Correct_PieceCords ( Cordinates temp_cord , char id ) ;
    int GetPiece_FromBoard ( Cordinates temp_cord ) ;

    void HandlePiece_Move ( int num , char id , Cordinates temp_cords ) ;
    int GetDirection_OfPiece ( Cordinates temp_cord ) ;

    void ChangePiece_Cords ( Cordinates * piece_cord , Cordinates * Change_cord , char id  ) ;
    void ChangePiece_TakeCords ( Cordinates Change_cord , int direction , char id  ) ;

    


    Team* GetTeam ( char id ) ;
    cell ( &getBoard() ) [GRID][GRID] {
             return borad ;
        }




    //void MovePiece ( char id , int num ) ;
    //bool isPieceClicked () ;
};