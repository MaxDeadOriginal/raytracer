/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Raycaster main
 *
 *        Created:  17/03/18 00:30:14
 *       Compiler:  gcc
 *
 *         Author:  Jacob
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "img.h"
#include "camera.h"
#include "render.h"
#include "obj.h"
#include "scene.h"
#include "thpool.h"

int main(int argc, char** argv) {
    SDL_Surface* surf;
    scene sc;
    obj shape;

    if (argc != 2) {
        printf("Usage: raycaster <.obj file path>\n");
        exit(EXIT_FAILURE);
    }

    shape = read_OBJ(argv[1]);

    printf("Object has:\n\
\t%d triangles,\n\
\t%d vertices\n\
\t%d normals\n\
\t%d uv coords\n", shape.amount_tris, shape.amount_verts, shape.amount_norms, shape.amount_uvs);

    sc.cam = (camera){
        .origin = (vec3d){-4.84913, 2.92571, 0.80132},
        .yaw    = 12.2,
        .pitch  = -20.8,
        .fov    = 85,
        .res_x  = 500,
        .res_y  = 500
    };

    sc.amount_tris = shape.amount_tris;
    sc.tris = shape.tris;

    sc.ambient_intensity = 0.12;
    sc.background_colour = 0x000000ff;

    sc.amount_pointlights = 1;
    sc.pointlights = malloc(sizeof(point_light) * sc.amount_pointlights);
    sc.pointlights[0] = (point_light){
        .pos = (vec3d){-2.00111, 1.77898, -0.35923},
        .energy = 1.5
    };

    camera_calculate_w_h(&sc.cam);

    surf = create_surface(sc.cam.res_x, sc.cam.res_y);

    printf("Rendering..");
    fflush(stdout);
    render_scene_to_surface(&sc, surf);
    printf("Done!\n");

    SDL_SaveBMP(surf, "out.bmp");
}
