#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "rot.h"
#include "cube.h"

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 800

#define wpp weak_perspective_projection

V2f weak_perspective_projection(V3f p, V3f perspective, double f){
    int nx = p.x * f / (p.z + perspective.z) + perspective.x;
    int ny = p.y * f / (p.z + perspective.z) + perspective.y;
    return (V2f){ .x = nx, .y = ny };
}

void print_v2f(V2f v){
    printf("V2f: x = %f, y = %f\n", v.x, v.y);
}

void print_v3f(V3f v){
    printf("V3f: x = %f, y = %f, z = %f\n", v.x, v.y, v.z);
}

void print_m3x3(M3x3 m){
    printf("m3x3:\n");
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("\t%f", m.m[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

V2f square[] = {
    (V2f){.x = 100, .y = 100},
    (V2f){.x = 100, .y = 200},
    (V2f){.x = 200, .y = 200},
    (V2f){.x = 200, .y = 100},
};

void sdl_vec2d_example(SDL_Renderer *renderer, double angle){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0 ,0); 
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    V2f prev = {0};
    for(int i = 0; i < 4; i++){
        rotatePoint2d(&square[i], angle);
        if(i != 0){
            SDL_RenderDrawLine(renderer, 
                    prev.x,      prev.y,
                    square[i].x, square[i].y);
        }
        prev = square[i];
    }

    SDL_RenderDrawLine(renderer, 
            prev.x,      prev.y,
            square[0].x, square[0].y);
    SDL_RenderPresent(renderer);
}

int c_x = 0;
int c_y = 0;
int c_z = 200;
int c_len = 200;

V3f cube[16] = {0};

void sdl_vec3d_example(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 18, 18, 18, 255); 
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    double yaw = 0;
    double pitch = 1;
    double roll = 0;
    double f = 200;

    V2f prev = {0};
    for(int i = 0; i < sizeof(cube) / sizeof(cube[0]); i++){
        rotatePoint3d(&cube[i], (V3f){.x = 300, .y = 300, .z = 500}, yaw, pitch, roll);
        V2f proj = wpp(cube[i], (V3f){.x = 400, .y = 400, .z = 100}, f);

        if(i != 0){
            SDL_RenderDrawLine(renderer, prev.x, prev.y, proj.x, proj.y);
        }
        prev = proj;
    }

    SDL_RenderPresent(renderer);
}


int main(){
    make_cube(cube, c_x, c_y, c_z, c_len);
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window;
    window = SDL_CreateWindow("rotations", 50, 50, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    double angle = 1.0f;
    int timer = 0;
    SDL_Event e;
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&e)){
            switch(e.type){
            case SDL_QUIT:
                quit = true;
                break;
            }
        }
        timer ++;
        if(timer >= 1000){
            sdl_vec3d_example(renderer);
            timer=0;
        }
    }
}

int main2(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window;
    window = SDL_CreateWindow("rotations", 50, 50, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    double angle = 1.0f;
    int timer = 0;
    SDL_Event e;
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&e)){
            switch(e.type){
            case SDL_QUIT:
                quit = true;
                break;
            }
        }

        timer ++;
        if(timer >= 1000){
            sdl_vec2d_example(renderer, angle);
            timer=0;
        }
    }
}
