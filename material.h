#ifndef MATERIAL_H
#define MATERIAL_H
#include "common.h"
#include <algorithm>
using namespace std;

struct hit_record;


class material {
    public:
        virtual color scatter(
            const ray& light, const hit_record& rec, color& light_color, bool shadow
        ) const = 0;
};


class lambertian : public material {
    public:
        lambertian(const color& s, double ka, double kd) : surface(s), ka(ka), kd(kd)
        {}

        virtual color scatter(
            const ray& light, const hit_record& rec, color& light_color, bool shadow
        ) const override { 
            auto Ia_r = ka * light_color.x();         
            auto Ia_g = ka * light_color.y();   
            auto Ia_b = ka * light_color.z();
            color La = color(surface.x()+Ia_r, surface.y()+Ia_g, surface.z()+Ia_b);
            // if hit
            if(shadow){
                return La + surface;
            }
            // if not hit
            else{
                double product = dot(rec.normal, unit_vector(light.direction()));
                auto Id_r= kd * light_color.x() * max(0.0, product);
                auto Id_g =  kd * light_color.y() * max(0.0, product);
                auto Id_b =  kd * light_color.z() * max(0.0, product);
                // cout<<"rgb"<<La.x()<<" "<<La.y()<<" "<<La.z()<<" "<<endl;
                return color(Id_r, Id_g, Id_b) + La + surface;
            }

        }

    public:
        color surface;
        double ka;
        double kd;
};


#endif
