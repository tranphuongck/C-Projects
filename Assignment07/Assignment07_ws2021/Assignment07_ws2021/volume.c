/*
Compile: make volume
Run: ./volume
make volume && ./volume
*/
#define _USE_MATH_DEFINES
#define _GNU_SOURCE
#include "base.h"

enum Tag { TCylinder, TSphere, TCuboid };
typedef enum Tag Tag;

struct Cylinder {
    double r, h; // V = pi * r^2 * h
};

struct Sphere {
    double r; // V = 4 / 3 * pi * r^3
};

struct Cuboid {
    double a, b, c; // V = a * b *c
};

struct GeomObject {
    // todo: implement
	Tag tag;
    union {
	   struct{double r, h;} cylinder;
	   struct{double r;} sphere;
	   struct{double a, b, c;} cuboid;
   };
};

typedef struct Cylinder Cylinder;
typedef struct Sphere Sphere;
typedef struct Cuboid Cuboid;
typedef struct GeomObject GeomObject;

GeomObject make_cylinder(double r, double h) {
    // todo: implement
    GeomObject o = {};
	o.tag = TCylinder;
	o.cylinder.r = r;
	o.cylinder.h = h;
    return o;
}

GeomObject make_sphere(double r) {
    // todo: implement
    GeomObject o = {};
	o.tag = TSphere;
	o.sphere.r = r;
    return o;
}

GeomObject make_cuboid(double a, double b, double c) {
    // todo: implement
    GeomObject o = {};
	o.tag = TCuboid;
	o.cuboid.a = a;
	o.cuboid.b = b;
	o.cuboid.c = c;
	
    return o;
}

double volume(GeomObject o);

void volume_test(void) {
    test_within_d(volume(make_sphere(2)), 4 /3.0 * M_PI * 2 * 2 * 2, 1e-6);
    test_within_d(volume(make_cuboid(2, 3, 4)), 2 * 3 * 4, 1e-6);
    test_within_d(volume(make_cylinder(3, 4)), 4 * M_PI * 3 * 3 , 1e-6);
}
    
// GeomObject -> double
// Computes the surface area of the given object.
double volume(GeomObject o) {
    // todo: implement
	switch(o.tag){
		case TSphere:
			return 4/3.0 * M_PI * o.sphere.r * o.sphere.r * o.sphere.r;
		case TCuboid:
			return o.cuboid.a * o.cuboid.b * o.cuboid.c;
		case TCylinder:
			return o.cylinder.h * M_PI * o.cylinder.r * o.cylinder.r;
	}
	return 0.0;
}

int main(void) {
    volume_test();
    return 0;
}

//todo: d)
Enum tag nutzt man hier, da:
*) einfacher definieren welches GeomObject Sphere, Cuboid oder Cylinder ist
*) man kann hier andere Name erstellen um die Anderen zu missverstehen: Geo







