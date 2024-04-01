#include <stdlib.h>
#include <stdio.h>
#include "rot.h"

void make_cube(V3f *cube, float c_x, float c_y, float c_z, float c_len){
    V3f cube_t[] = {
        (V3f) {.x = c_x,         .y = c_y,         .z = c_z},
        (V3f) {.x = c_x,         .y = c_y + c_len, .z = c_z},
        (V3f) {.x = c_x + c_len, .y = c_y + c_len, .z = c_z},
        (V3f) {.x = c_x + c_len, .y = c_y,         .z = c_z},

        (V3f) {.x = c_x, .y = c_y,         .z = c_z},
        (V3f) {.x = c_x, .y = c_y,         .z = c_z + c_len},
        (V3f) {.x = c_x, .y = c_y + c_len, .z = c_z + c_len},

        (V3f) {.x = c_x + c_len, .y = c_y + c_len, .z = c_z + c_len},
        (V3f) {.x = c_x + c_len, .y = c_y,         .z = c_z + c_len},
        (V3f) {.x = c_x + c_len, .y = c_y + c_len, .z = c_z + c_len},
        (V3f) {.x = c_x + c_len, .y = c_y + c_len, .z = c_z},
        (V3f) {.x = c_x + c_len, .y = c_y,         .z = c_z},
        (V3f) {.x = c_x + c_len, .y = c_y,         .z = c_z + c_len},

        (V3f) {.x = c_x, .y = c_y,         .z = c_z + c_len},
        (V3f) {.x = c_x, .y = c_y + c_len, .z = c_z + c_len},
        (V3f) {.x = c_x, .y = c_y + c_len, .z = c_z},
    };
    memcpy(cube, cube_t, sizeof(cube_t));
}
