#include "Game.hpp"

int absComplex(const Complex& obj){
    return sqrt((obj.real * obj.real) + (obj.imaginary * obj.imaginary));
}

Game::Game(Handle& handle) : handle(handle){
    mQuit = false;
    mUpdated = false;
    mZoomLevel = 0;
    mXOffset = 0;
    mYOffset = 0; 
}

void Game::gameLoop(){

    HSVtoRGB(188, 58, 27);

    while(mQuit == false){
        while(SDL_PollEvent(&mEvent)){
           handleInput(mEvent);
        }
        
        update();

        draw();

    }
}

void Game::update(){

}

void Game::draw(){
    if(mUpdated == false){
        Complex c(0, 0);
        const double RE_START = (-2 + mXOffset) - mZoomLevel;
        const double RE_END = (1 + mXOffset);
        const double IM_START = (-1 + mYOffset) - mZoomLevel;
        const double IM_END = (1 + mYOffset);

        float hue = 0;
        float saturation = 0;
        float value = 0;
        SDL_SetRenderDrawColor(handle.getRenderer(), 187, 173, 160, 255);
        SDL_RenderClear(handle.getRenderer());
        SDL_Color clr = { .r = 0, .g = 0, .b = 0, .a = 255};
        int m = 0;
        for(double y = 0; y < static_cast<double>(handle.getHeight()); y++){
            for(double x = 0; x < static_cast<double>(handle.getWidht()); x++){
                c = Complex(
                    RE_START + (x / static_cast<double>(handle.getWidht()) * (RE_END - RE_START)),
                    IM_START + (y / static_cast<double>(handle.getHeight()) * (IM_END - IM_START))
                );
                m = mandlebrot(c);
                hue = (int)(360 * m / cMaxIter);
                saturation = 100;
                value = (m < cMaxIter) ? 100 : 0;
                clr = HSVtoRGB(hue, saturation, value);
                SDL_SetRenderDrawColor(handle.getRenderer(), clr.r, clr.g, clr.b, clr.a);
                SDL_RenderDrawPoint(handle.getRenderer(), x, y);

                /*c = Complex(static_cast<float>(i)/10.f, static_cast<float>(j)/10.f);
                c.print();
                std::cout<< ", " << mandlebrot(c) << std::endl;*/
            }
        }

        SDL_RenderPresent(handle.getRenderer());

        SDL_DestroyTexture(handle.getTexture());

        mUpdated = true;
    }
}

void Game::handleInput(SDL_Event& event){
    switch (event.type)
    {
    case SDL_QUIT:
        mQuit = true;
        break;
    case SDL_KEYDOWN:
        handleKeyboardInput(event);
        break;
    default:
        break;
    }
}

void Game::handleKeyboardInput(SDL_Event& event){
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
        mXOffset -= 0.1;
        mUpdated = false;
       break;
    case SDLK_RIGHT:
        mXOffset += 0.1;
        mUpdated = false;
       break;
    case SDLK_UP:
        mYOffset += 0.1;
        mUpdated = false;
       break;
    case SDLK_DOWN:
        mYOffset -= 0.1;
        mUpdated = false;
       break;
    case SDLK_w:
        mZoomLevel -= 0.5;
        mXOffset -= 0.25;
        mYOffset -= 0.25;
        mUpdated = false;
       break;
    case SDLK_s:
        mZoomLevel += 0.5;
        mXOffset += 0.25;
        mYOffset += 0.25;
        mUpdated = false;
       break;
    default:
        break;
    }
}

int Game::mandlebrot(Complex c){
    Complex z(0, 0);
    int n = 0;
    while(absComplex(z) <= 2 && n < cMaxIter){
        z = (z * z) + c;
        n = n + 1;
    }
    if(n == cMaxIter)
        return cMaxIter;
    return n + 1 - log(log2(absComplex(z)));
}