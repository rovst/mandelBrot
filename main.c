#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <complex.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xFFFFFF
#define MAX_ITER 100
#define Z_LIMIT 1000

// Function declarations
bool checkMandelbrot(double re, double im);
void drawMandelbrot(SDL_Surface *psurface);

int main() {
    printf("Rendering Mandelbrot set...\n");

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *pwindow = SDL_CreateWindow("Mandelbrot",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);

    SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);
    bool running = true;
    SDL_Event event;

    drawMandelbrot(psurface);
    SDL_UpdateWindowSurface(pwindow);

    // Event loop
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    SDL_Quit();
    return 0;
}

bool checkMandelbrot(double re, double im) {
    double complex c = re + im * I;
    double complex z = 0;

    for (int i = 0; i < MAX_ITER; i++) {
        z = z * z + c;
        if (cabs(z) > Z_LIMIT) return false;
    }
    return true;
}

void drawMandelbrot(SDL_Surface *psurface) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            // Map (x, y) to complex plane coordinates
            double re = (x - WIDTH / 2.0) * 4.0 / WIDTH;
            double im = (y - HEIGHT / 2.0) * 4.0 / WIDTH;

            if (checkMandelbrot(re, im)) {
                SDL_Rect pixel = { x, y, 1, 1 };
                SDL_FillRect(psurface, &pixel, COLOR_WHITE);
            }
        }
    }
}
