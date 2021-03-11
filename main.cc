#include "common.h"
#include "camera.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "plane.h"
#include "Cone.h"
#include "ellipsoid.h"
#include "image.h"

#include <iostream>

int hit = 0;
int not_hit = 0;
color ray_color(const ray& r, point3 light_source, color light_color, const hittable& world) {
    hit_record rec;
    // find the closest intersection
    if (world.hit(r, 0, infinity, rec)) {
        hit++;
        auto light_dir = light_source - rec.p;
        ray light_ray = ray(light_source, light_dir);
        bool shadow = false;
        hit_record shadow_rec;
        if(world.hit(light_ray, 0, infinity, shadow_rec)){
            shadow = true;
        }
        color pixel_color = rec.mat_ptr->scatter(light_ray, rec, light_color, shadow);
        return pixel_color;
    }
    else
    {
        not_hit++;
        return color(0,0,0);
    }
    
}

                                                                              
hittable_list random_scene() {
    hittable_list world;
    double ka = 0.3;
    double kd = 0.7;
    auto sphere_material = make_shared<lambertian>(color(1, 0, 0), ka, kd);
    world.add(make_shared<sphere>(point3(0,0,1), 1, sphere_material));

    auto cone_material = make_shared<lambertian>(color(0, 1, 0), ka, kd);
    world.add(make_shared<Cone>(point3(-1,-1,1), 1, 3, cone_material));

    auto ellipsoid_material = make_shared<lambertian>(color(0, 0, 1), ka, kd);
    world.add(make_shared<ellipsoid>(point3(0.5,0.5,-0.5), 0.2, 2, 2, 1, ellipsoid_material));

    auto plane_material = make_shared<lambertian>(color(0.5, 0.5, 0.5), ka, kd);
    world.add(make_shared<plane>(point3(1,-1.4,1), vec3(0,1,0), plane_material));

    return world;
}


int main() {
    // view point 
    point3 viewpoint(0, 0, -1);
    point3 lookat(0,0,0);

    // view plane 
    auto viewplane_height = 3.0; // y[-1.5,1.5]
    auto viewplane_width = 4.0; // x[-2,2]
    
    // canvas
    const int pixel_column = 640;
    const int pixel_row = 480;
    color* canvas = new color[pixel_row*pixel_column];
    
    // camera
    camera cam(viewpoint, lookat, viewplane_width, viewplane_height, pixel_row, pixel_column);

    // light
    point3 light_source = point3(0, 5, 0);
    color light_color = color(1, 0, 0); 

    // objects
    auto world = random_scene();
    
    // render perspective
    for (int i = 1; i <= pixel_row; i++) {
        for(int j = 1; j <= pixel_column; j++){
            ray r = cam.get_ray(i, j);
            canvas[(pixel_row - i) * pixel_column + j - 1]= ray_color(r, light_source, light_color, world);
        }
    }

    color_to_jpeg(pixel_row, pixel_column, canvas, "perspective.jpg");

    // render parallel
    for (int i = 1; i <= pixel_row; i++) {
        for(int j = 1; j <= pixel_column; j++){
            ray r = cam.get_ray_parallel(i, j);
            canvas[(pixel_row - i) * pixel_column + j - 1]= ray_color(r, light_source, light_color, world);
        }
    }

    color_to_jpeg(pixel_row, pixel_column, canvas, "parallel.jpg");

    // cout<<"hit:"<<hit<<endl;
    // cout<<"not_hit:"<<not_hit<<endl;
    delete canvas;
}
