#include "piece.hpp"

Piece::Piece ( Cordinates piece_cord , char id , int direction , int num )
{
    alive = true ;
    this->piece_cord = piece_cord ;
    this->id = id ;
    this->direction = direction ;
    this->num = num ;
}

void Piece::KillPiece()
{
    this->alive = false ;
    printf ( " piece killed with success ! \n") ;
}

void Piece::SetCordinates ( Cordinates piece_cord )
{
    this->piece_cord = piece_cord ;
}

void Piece::SetDirection ( int direction )
{
    this->direction = direction ;
}

bool Piece::PieceState()
{
    return alive ;
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