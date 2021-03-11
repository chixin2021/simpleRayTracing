#ifndef ELLIPSOID_H
#define ELLIPSOID_H
#include <math.h>
#include "common.h"

#include "hittable.h"
using namespace std;

class ellipsoid : public hittable {
    public:
        ellipsoid() {};

        ellipsoid(point3 cen, double r, double a, double b, double c, shared_ptr<material> m)
            : center(cen), radius(r), ra(a), rb(b), rc(c), mat_ptr(m) {};

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 center;
        double radius;
        double ra;
        double rb;
        double rc;
        shared_ptr<material> mat_ptr;
};


bool ellipsoid::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = vec3((r.origin().x() - center.x())/ra  , (r.origin().y() - center.y())/rb, (r.origin().z() - center.z())/rc);
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    // no root
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    auto n = rec.p - center;
    vec3 outward_normal = vec3(n.x()/ra,n.y()/rb,n.z()/rc);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}


#endif
