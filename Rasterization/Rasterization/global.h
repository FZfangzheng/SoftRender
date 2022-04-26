#pragma once
typedef unsigned char u08;
#define MY_PI 3.1415926
#define TWO_PI (2.0* MY_PI)
const float SIZE_PLANE = 5.0f;
const float plane_vertices[] = {
    // positions            // normals         // texcoords
     SIZE_PLANE, -1.0f,  SIZE_PLANE,  0.0f, 1.0f, 0.0f,  1.0f,  1.0f,
    -SIZE_PLANE, -1.0f,  SIZE_PLANE,  0.0f, 1.0f, 0.0f,   0.0f,  1.0f,
    -SIZE_PLANE, -1.0f, -SIZE_PLANE,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,

     SIZE_PLANE, -1.0f,  SIZE_PLANE,  0.0f, 1.0f, 0.0f,  1.0f,  1.0f,
    -SIZE_PLANE, -1.0f, -SIZE_PLANE,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
     SIZE_PLANE, -1.0f, -SIZE_PLANE,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f
};
//const float plane_vertices[] = {
//    // positions            // normals         // texcoords
//     SIZE_PLANE, -1.0f,  SIZE_PLANE,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
//    -SIZE_PLANE, -1.0f,  SIZE_PLANE,  0.0f, 1.0f, 0.0f,   0.0f,  1.0f,
//    -SIZE_PLANE, -1.0f, -SIZE_PLANE,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
//
//     SIZE_PLANE, -1.0f,  SIZE_PLANE,  0.0f, 1.0f, 0.0f,  1.0f,  1.0f,
//    -SIZE_PLANE, -1.0f, -SIZE_PLANE,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
//     SIZE_PLANE, -1.0f, -SIZE_PLANE,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f
//};
//const float plane_vertices[] = {
//    // positions            // normals         // texcoords
//     25.0f, -1.0f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
//    -25.0f, -1.0f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
//    -25.0f, -1.0f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
//
//     25.0f, -1.0f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
//    -25.0f, -1.0f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
//     25.0f, -1.0f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
//};
const float cube_vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};