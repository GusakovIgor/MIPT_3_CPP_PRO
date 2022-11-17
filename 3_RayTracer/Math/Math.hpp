#include <string>
#include <cmath>


typedef float coord_t;


class Point3f;
class Vector3f;
class Set3f;
class Ray3f;


class Point3f
{

public:

    coord_t x;
    coord_t y;
    coord_t z;


    Point3f ();
    explicit Point3f (coord_t init_x, coord_t init_y, coord_t init_z);

    std::string ToString () const;


    Point3f Move (const Vector3f& delta) const;
};

Point3f operator- (const Point3f& left, const Point3f& right);
Point3f operator+ (const Point3f& left, const Point3f& right);



class Vector3f
{

private:

    Vector3f (const Point3f& a);


public:

    coord_t x;
    coord_t y;
    coord_t z;

    coord_t len;


    Vector3f ();
    explicit Vector3f (const Point3f& a, const Point3f& b);

    std::string ToString () const;


    void Normalize ();
};

double   operator* (const Vector3f& left, const Vector3f& right);
Vector3f operator* (const Vector3f& vector, const double factor);



class Set3f
{

public:

    double x;
    double y;
    double z;

    Set3f ();
    explicit Set3f (double x, double y, double z);

    std::string ToString () const;
};

Set3f operator+  (const Set3f& left, const Set3f& right);
Set3f operator-  (const Set3f& left, const Set3f& right);
Set3f operator+= (Set3f& set, const Set3f& delta);
Set3f operator-= (Set3f& set, const Set3f& delta);


class Ray3f
{

private:

    Ray3f (const Point3f& init_start, const Vector3f& init_direction);


public:

    Point3f start;

    Vector3f direction;


    Ray3f ();

    explicit Ray3f (const Point3f& init_start, const Point3f& some_point);

    std::string ToString () const;
};