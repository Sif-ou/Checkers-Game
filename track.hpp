#include "struct.hpp"
#include "take.hpp"

class Tracker 
{

    private :

     Cordinates track_cord ;
     int take_num ;
     SDL_Surface * track_surface = nullptr ;

     /* ### Highlights ### */ 
     SDL_Rect Focus_rect ;
     SDL_Rect draw_rect ;
     /* ### ### */

    public :

      Tracker() ;
      void DeleteTracker () ;
      void SetTrack_cord ( int x , int y ) ;
      Cordinates TrackCord_Board_converter () ;
      Cordinates GetTrack_Cord () ;
      void Focus_Draw ( SDL_Renderer * r , SDL_Texture * t ) ;  

      /**
       * reset track_cords to 
       * track_cord.x = -1 ;
       * track_cord.y = -1 ; 
       */
      void Reset_Track () ;

      public :

      void ForcedTake ( std::list<TakeDirection> take_list , SDL_Renderer * r , SDL_Texture * t ) ;
      bool isTakePiece ( std::list<TakeDirection> take_list  ) ;
      int getTakeNum () ;
      /*Cordinates TakeCord ( std::list<TakeDirection> take_list ) ; 
      int DirectionTake ( std::list<TakeDirection> take_list ) ;*/


     // int TakeDirection ( std::list<TakeDirection> take_list ) ;
};