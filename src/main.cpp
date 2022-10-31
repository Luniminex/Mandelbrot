#include "Handle.hpp"
#include "Game.hpp"

#define WINDOW_WIDHT 1200
#define WINDOW_HEIGHT 900

int main(){

    Handle handle;

    if(handle.initLibs() != 1){
        std::cout << "Failed to initialize SDL libraries" << std::endl;
        return 1;
    }
    if(handle.createWindow("Mandelbrot", WINDOW_WIDHT, WINDOW_HEIGHT)!= 1){
        std::cout << "Could not create a window" << std::endl;
        return 1;
    }
    if(handle.createRenderer() != 1){
        std::cout << "Could not create a renderer" << std::endl;
        return 1;
    }

    Game game(handle);
    game.gameLoop();
    
    handle.quit();

    return 0;
}

