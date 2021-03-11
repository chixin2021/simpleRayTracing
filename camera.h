#ifndef CAMERA_H
#define CAMERA_H
#include "common.h"


class camera {
    public:
        camera() : camera(point3(0,0,-1), point3(0,0,0), 4, 3, 640, 480) {}

        camera(
            point3 lookfrom,
            point3 lookat,
            double canvas_width,
            double canvas_height,
            double pixel_row,
            double pixel_column
        ):origin(lookfrom), center(lookat), canvas_width(canvas_width), canvas_height(canvas_height),pixel_row(pixel_row), pixel_column(pixel_column)
        {
        }
        // perspective
        ray get_ray(double i, double j) const {
            auto z = center - origin;
            auto x = vec3(((j - pixel_column / 2) - 0.5) * canvas_width / pixel_column, 0, 0);
            auto y = vec3(0, ((i - pixel_row / 2) - 0.5) * canvas_height / pixel_row, 0);
            auto u = z + x + y;
            return ray(
                origin,
                u
            );
        }

        ray get_ray_parallel(double i, double j) const {
    
            auto origin = vec3(((j - pixel_column / 2) - 0.5) * canvas_width / pixel_column,  ((i - pixel_row / 2) - 0.5) * canvas_height / pixel_row, 0);
            auto u = vec3(0, 0, 1);
            return ray(
                origin,
                u
            );
        }

    private:
        point3 origin; // view point
        point3 center; // look at
        double pixel_row; // canvas
        double pixel_column;
        double canvas_width; // x
        double canvas_height; // y
        // double time;
};

#endif
