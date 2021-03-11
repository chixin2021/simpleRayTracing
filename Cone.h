#ifndef Cone_H
#define Cone_H

#include "common.h"
#include "hittable.h"

/**
 * Defines a simple Sphere located at 'center' 
 * with the specified radius
 */
class Cone : public hittable
{


public:	
	Cone(){};
	
    Cone(vec3 c, double r, double h, shared_ptr<material> m)
		: center(c), radius(r), height(h), mat_ptr(m)
	{
	};

	float intersect(vec3 pos, vec3 dir);

    vec3 normal(vec3 p);
    virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        vec3 center;
        double radius;
        double height;
        shared_ptr<material> mat_ptr;
};

// we assume the cone lies on the x-y plane, the axis is parallel to z
// bool Cone::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
//     double A = r.orig.x() - center.x();
//     double B = r.orig.y() - center.y();
//     double D = height - r.orig.z() + center.z();

//     double tan = (radius / height) * (radius / height);

//     double a = (r.dir.x() * r.dir.x()) + (r.dir.y() * r.dir.y()) - (tan * (r.dir.z() * r.dir.z()));
//     double b = (2 * A * r.dir.x()) + (2 * B * r.dir.y()) + (2 * tan * D * r.dir.z());
//     double c = (A * A) + (B * B) - (tan * (D * D));

//     double delta = b * b - 4 * (a * c);
//     if (delta < 0.0) return false;

//     double t1 = (-b - sqrt(delta)) / (2 * a);
//     double t2 = (-b + sqrt(delta)) / (2 * a);
//     double t;

//     if (t1 > t2) t = t2;
//     else t = t1;

//     double sum = r.orig.z() + t * r.dir.z();
//     bool flag = sum >= center.z() && sum < center.z() + height;
//     if (flag == false)
//         return false;

//     rec.t = t;
//     rec.p = r.at(rec.t);
//     double root = sqrt((rec.p.x() - center.x()) * (rec.p.x() - center.x()) + (rec.p.y() - center.y())  * (rec.p.z() - center.z()) );
//     vec3 n = vec3(rec.p.x() - center.x(), root * (radius / height), rec.p.y() - center.y());
//     vec3 outward_normal = unit_vector(n);
//     rec.set_face_normal(r, outward_normal);
//     rec.mat_ptr = mat_ptr;

//     return true;
// }

bool Cone::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    double A = r.orig.x() - center.x();
    double B = r.orig.z() - center.z();
    double D = height - r.orig.y() + center.y();

    double tan = (radius / height) * (radius / height);

    double a = (r.dir.x() * r.dir.x()) + (r.dir.z() * r.dir.z()) - (tan * (r.dir.y() * r.dir.y()));
    double b = (2 * A * r.dir.x()) + (2 * B * r.dir.z()) + (2 * tan * D * r.dir.y());
    double c = (A * A) + (B * B) - (tan * (D * D));

    double delta = b * b - 4 * (a * c);
    if (delta < 0.0) return false;

    double t1 = (-b - sqrt(delta)) / (2 * a);
    double t2 = (-b + sqrt(delta)) / (2 * a);
    double t;

    if (t1 > t2) t = t2;
    else t = t1;

    double sum = r.orig.y() + t * r.dir.y();
    bool flag = sum >= center.y() && sum < center.y() + height;
    if (flag == false)
        return false;

    rec.t = t;
    rec.p = r.at(rec.t);
    double root = sqrt((rec.p.x() - center.x()) * (rec.p.x() - center.x()) + (rec.p.z() - center.z())  * (rec.p.y() - center.y()) );
    vec3 n = vec3(rec.p.x() - center.x(), root * (radius / height), rec.p.z() - center.z());
    vec3 outward_normal = unit_vector(n);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}


#endif 
