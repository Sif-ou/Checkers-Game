#include "piece.hpp"


Team::~Team()
{

    for ( int i = 0 ; i < NUMBER_OF_PIECES ; i++ )
     {
         delete this->Pieces[i]  ;
         this->Pieces[i] = nullptr ; 
     }

}


Piece::Piece ( Cordinates piece_cord , char id , int direction , int num )
{
    alive = true ;
    this->piece_cord = piece_cord ;
    this->id = id ;
    this->direction = direction ;
    this->num = num ;
}

bool Piece::isAlive()
{
    return this->alive ;
}

void Piece::KillPiece()
{
    this->alive = false ;
    //printf ( " piece killed with success ! \n") ;
}

void Piece::SetCordinates ( Cordinates piece_cord )
{
    this->piece_cord = piece_cord ;
}

void Piece::SetDirection ( int direction )
{
    this->direction = direction ;
}

Cordinates Piece::GetCordinates()
{
    return piece_cord ;
}

int Piece::GetNum()
{
    return num ;
}

int Piece::GetDirection()
{
    return direction ;
}

void Piece::KingUpgrade()
{
    this->direction = UPGRADE_PIECE_DIRECTION ; 
}

void Team::InitTeam( char id , int direction  )
{
        this->Num_Of_Pieces = 12 ;
        this->id = id ;
        this->direction = direction ;
}