#ifndef PLANE_H
#define PLANE_H
#include "common.h"
#include "hittable.h"


class plane : public hittable {
    public:
        plane() {}

        plane(point3 cen, vec3 n, shared_ptr<material> m)
            : center(cen), normal(n), mat_ptr(m) {};

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 center;
        vec3 normal;
        shared_ptr<material> mat_ptr;
};


bool plane::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = center - r.origin();
    auto vertical = dot(normal, unit_vector(r.direction()));
    
    // no root
    if (vertical == 0) return false;

    // Find the root that lies in the acceptable range.
    auto root = dot(oc, normal) / vertical;
    if (root < t_min || t_max < root) {
        return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.set_face_normal(r, normal);
    rec.mat_ptr = mat_ptr;

    return true;
}


#endif
