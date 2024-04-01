#ifndef ROT_H_
#define ROT_H_

#include <math.h>
#include <stdio.h>

typedef struct{ double x, y; }V2f;
typedef struct{ double x, y, z; }V3f;

typedef struct{
    double r1[2];
    double r2[2];
}M2x2;

typedef struct{
    double m[3][3];
}M3x3;

M3x3 x_rot_3d(double angle);
M3x3 y_rot_3d(double angle);
M3x3 z_rot_3d(double angle);

V3f  mul_3x3_v3f(M3x3 m, V3f v);
M3x3 mul_3x3_3x3(M3x3 m1, M3x3 m2);

// --- DEFINITIONS ---


double deg_rad(double deg){
    return deg * M_PI / 180;
}
double rad_deg(double rad){
    return rad * 180 / M_PI;
}

void rotatePoint2d(V2f *p, double angle_deg){
    double angle = deg_rad(angle_deg);
    double nx = p->x * cos(angle) - p->y * sin(angle);
    double ny = p->x * sin(angle) + p->y * cos(angle);
    p->x = nx;
    p->y = ny;
}

void rotatePoint3d(V3f *p, V3f center, double yaw_deg, double pitch_deg, double roll_deg){
    p->x -= center.x;
    p->y -= center.y;
    p->z -= center.z;

    double yaw   = deg_rad(yaw_deg);
    double pitch = deg_rad(pitch_deg);
    double roll  = deg_rad(roll_deg);

    M3x3 full_rotation = mul_3x3_3x3(mul_3x3_3x3(x_rot_3d(yaw), y_rot_3d(pitch)), z_rot_3d(roll));

    *p = mul_3x3_v3f(full_rotation, *p);

    p->x += center.x;
    p->y += center.y;
    p->z += center.z;
}

// matrix mulitplication

V3f mul_3x3_v3f(M3x3 m, V3f v){
    V3f res = {0};
    res.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
    res.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
    res.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;
    return res;
}

M3x3 mul_3x3_3x3(M3x3 m1, M3x3 m2){
    M3x3 res = {0};
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            double x = 0;
            for(int k = 0; k < 3; k++){
                x += m1.m[i][k] * m2.m[k][j];
            }
            res.m[j][i] = x;
        }
    }
    return res;
}

// basic 3d rotations

M3x3 x_rot_3d(double angle){
    return (M3x3){ .m = {
        { 1,          0,          0  },
        { 0, cos(angle), -sin(angle) },
        { 0, sin(angle),  cos(angle) }}
    };
}

M3x3 y_rot_3d(double angle){
    return (M3x3){.m = {
        {  cos(angle), 0, sin(angle) },
        {           0, 1,          0 },
        { -sin(angle), 0, cos(angle) }}
    };
}

M3x3 z_rot_3d(double angle){
    return (M3x3){ .m = {
        { cos(angle), -sin(angle), 0 },
        { sin(angle),  cos(angle), 0 },
        {          0,           0, 1 }}
    };
}

#endif //ROT_H_
