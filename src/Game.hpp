#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include "Handle.hpp"
#include "Text.hpp"
#include "Converter.hpp"

struct Complex {
    double real = 0;
    double imaginary = 0;

    Complex(double real, double imaginary){
        this->real = real;
        this->imaginary = imaginary;
    }

    void print(){
        std::cout << "(" << real << " " << imaginary << "j)";
    }

    Complex operator+(const Complex& obj){
        Complex result(0, 0);
        result.real = real + obj.real;
        result.imaginary = imaginary + obj.imaginary;
        return result;
    }

    Complex operator*(const Complex& obj){
        Complex result(0, 0);
        result.real = (real * obj.real) - (imaginary * obj.imaginary);
        result.imaginary = (real * obj.imaginary) + (imaginary * obj.real);
        return result;
    }
};

int absComplex(const Complex& obj);

class Game{

private:
    Handle& handle;
    SDL_Event mEvent;

    const int cMaxIter = 500;

    bool mQuit;
    bool mUpdated;

    double mZoomLevel;
    double mXOffset;
    double mYOffset;

public:
    Game(Handle& handle);

    void gameLoop();

private:
    void update();

    void draw();

    void handleInput(SDL_Event& event);

    void handleKeyboardInput(SDL_Event& event);

    int mandlebrot(Complex c); 
};
