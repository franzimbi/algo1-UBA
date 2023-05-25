#include <stdio.h>
#include <stdlib.h>

/*
Para acceder a cada uno de los campos de las estructuras, escribí una expresión. Por ejemplo, para acceder al campo stamp:

robot_pose.encabezado.stamp
*/

struct header {
    int secuencia;
    time_t stamp;
    char * frame;
};

struct pose {
    struct {
        double x, y, z;
    } posicion;
    struct {
        double qx, qy, qz, qw;
    } orientacion;
};

struct pose_stamped {
    struct header encabezado;
    struct pose pose;
} robot_pose;


