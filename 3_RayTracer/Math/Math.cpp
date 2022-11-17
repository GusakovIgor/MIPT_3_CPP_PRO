#include "Math.hpp"



Point3f::Point3f ()
{
    x = 0;
    y = 0;
    z = 0;
}

Point3f::Point3f (coord_t init_x, coord_t init_y, coord_t init_z)
{
    x = init_x;
    y = init_y;
    z = init_z;
}

std::string Point3f::ToString () const
{
    return "Point3f(coords: " + std::to_string (x) + ", " + std::to_string (y) + ", " + std::to_string (z) + ")";
}

Point3f Point3f::Move (const Vector3f& delta) const
{
    return Point3f (x + delta.x, y + delta.y, z + delta.z);
}

Point3f operator- (const Point3f& left, const Point3f& right)
{
    return Point3f (left.x - right.x, left.y - right.y, left.z - right.z);
}

Point3f operator+ (const Point3f& left, const Point3f& right)
{
    return Point3f (left.x + right.x, left.y + right.y, left.z + right.z);
}


Vector3f::Vector3f ()
{
    x = 0;
    y = 0;
    z = 0;

    len = 0;
}

Vector3f::Vector3f (const Point3f& init_point)
{
    x = init_point.x;
    y = init_point.y;
    z = init_point.z;

    len = sqrt (x*x + y*y + z*z);
}

Vector3f::Vector3f (const Point3f& start, const Point3f& end) : Vector3f (end - start)
{
}

std::string Vector3f::ToString () const
{
    return "Vector3f(coords: " + std::to_string (x) + ", " + std::to_string (y) + ", " + std::to_string (z) + "; length: " + std::to_string (len) + ")";
}

// FIXME: Here can occure some inaccuracies
void Vector3f::Normalize ()
{
    x /= len;
    y /= len;
    z /= len;

    len = 1;
}

double operator* (const Vector3f& left, const Vector3f& right)
{
    return left.x * right.x + left.y * right.y + left.z * right.z;
}

Vector3f operator* (const Vector3f& vector, const double factor)
{
    return Vector3f (Point3f (0, 0, 0), Point3f (vector.x * factor, vector.y * factor, vector.z * factor));
}


Set3f::Set3f ()
{
    x = 0;
    y = 0;
    z = 0;
}

Set3f::Set3f (double init_x, double init_y, double init_z)
{
    x = init_x;
    y = init_y;
    z = init_z;
}

std::string Set3f::ToString () const
{
    return "Set3f(coords: " + std::to_string (x) + ", " + std::to_string (y) + ", " + std::to_string (z) + ")";
}

Set3f operator+ (const Set3f& left, const Set3f& right)
{
    return Set3f (left.x + right.x, left.y + right.y, left.z + right.z);
}

Set3f operator- (const Set3f& left, const Set3f& right)
{
    return Set3f (left.x - right.x, left.y - right.y, left.z - right.z);
}

Set3f operator+= (Set3f& set, const Set3f& delta)
{
    set.x += delta.x;
    set.y += delta.y;
    set.z += delta.z;

    return set;
}

Set3f operator-= (Set3f& set, const Set3f& delta)
{
    set.x -= delta.x;
    set.y -= delta.y;
    set.z -= delta.z;

    return set;
}


Ray3f::Ray3f ()
{
    start = Point3f ();
    direction = Vector3f ();
}

Ray3f::Ray3f (const Point3f& init_start, const Vector3f& init_direction)
{
    start = init_start;
    direction = init_direction;
}

Ray3f::Ray3f (const Point3f& init_start, const Point3f& some_point)
{
    start = init_start;
    direction = Vector3f (init_start, some_point);
    direction.Normalize ();
}

std::string Ray3f::ToString () const
{
    return "Ray3f(start: " + start.ToString () + "; direction: " + direction.ToString () + ")";
}