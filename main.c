#include <stdio.h>
#include <SDL2/SDL.h>
#include <complex.h>

#define WIDTH 900
#define HEIGHT 600



#define COLOR_WHITE 0xFFFFFF

// Function declarations
bool checkMandelbrot(double re, double im, int maxIter, double escapeLimit);
void drawMandelbrot(SDL_Surface *psurface);

int main() {
    printf("hello Mandelbrot set");

    SDL_Window *pwindow = SDL_CreateWindow(
        "Mandelbrot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);

    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    bool running = true;
    SDL_Event event;

    drawMandelbrot(psurface);
    SDL_UpdateWindowSurface(pwindow);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    return 0;
}

bool checkMandelbrot(double re, double im, int maxIter, double escapeLimit) {
    double complex c = re + im * I;
    double complex z = 0;

    for (int i = 0; i < maxIter; i++) {
        z = z * z + c;
        if (cabs(z) > escapeLimit)
            return false;
    }
    return true;
}

void drawMandelbrot(SDL_Surface *psurface) {

    int r=1;
    int g=1;
    int b=1;


    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            // Convert screen pixel to complex plane coordinate
            double re = (x - WIDTH / 2.0) * 4.0 / WIDTH;
            double im = (y - HEIGHT / 2.0) * 4.0 / WIDTH;


            //color

            if (checkMandelbrot(re, im, 255, 2.0)) {
                SDL_Rect pixel = { x, y, 1, 1 };

                Uint32 color =SDL_MapRGB(psurface -> format, r%256,g%256,b%256);
                SDL_FillRect(psurface, &pixel, color);

                r=r+1;
                g=g+2;
                b=b+3;

            }
        }
    }
}
