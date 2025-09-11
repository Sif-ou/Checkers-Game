#include "board.hpp"

#define HEIGHT 720
#define WIDTH 1280

extern bool f ;

class GAME 
{
  
    private:
    
     SDL_Window * w = nullptr ;
     SDL_Renderer * r = nullptr ;
     
     board * b = new board ; 

     bool exit = false   ;


    public:


     void Init() ;
     void InitBoard() ;
     void Clear() ;
     void ClearTex() ;
     void Leave() ;
     void Present() ;
     void Event() ;
     bool IsRunning() { return exit ; }
      void Start() ;

    
};

