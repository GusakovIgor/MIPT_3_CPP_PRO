#include "Math.hpp"


Point2f::Point2f () :
    x (0),
    y (0)
{}

Point2f::Point2f (float init_x, float init_y) :
    x (init_x),
    y (init_y)
{}

std::string Point2f::ToString () const
{
    return "Point2f(coords: " + std::to_string (x) + ", " + std::to_string (y) + ")";
}

Set2f operator- (const Point2f& left, const Point2f& right)
{
    return Set2f (left.x - right.x, left.y - right.y);
}

Point2f::operator SDL_FPoint() const
{
    return {x, y};
}


Set2f::Set2f () :
    first  (0),
    second (0)
{}

Set2f::Set2f (double init_x, double init_y) :
    first  (init_x),
    second (init_y)
{}

std::string Set2f::ToString () const
{
    return "Set2f(coords: " + std::to_string (first) + ", " + std::to_string (second) + ")";
}

Vector2f::Vector2f () :
    x (0),
    y (0),
    len (0)
{}

Vector2f::Vector2f (const Set2f& init_coords) :
    x (init_coords.first),
    y (init_coords.second)
{
    len = sqrt (x*x + y*y);
}

Vector2f::Vector2f (const Point2f& start, const Point2f& end) :
    Vector2f (end - start)
{}

std::string Vector2f::ToString () const
{
    return "Vector2f(coords: " + std::to_string (x) + ", " + std::to_string (y) + "; length: " + std::to_string (len) + ")";
}

// FIXME: Here can occure some inaccuracies
void Vector2f::Normalize ()
{
    x /= len;
    y /= len;

    len = 1;
}


Point3f::Point3f () :
    x (0),
    y (0),
    z (0)
{}

Point3f::Point3f (double init_x, double init_y, double init_z) :
    x (init_x),
    y (init_y),
    z (init_z)
{}

std::string Point3f::ToString () const
{
    return "Point3f(coords: " + std::to_string (x) + ", " + std::to_string (y) + ", " + std::to_string (z) + ")";
}

Set3f operator- (const Point3f& left, const Point3f& right)
{
    return Set3f (left.x - right.x, left.y - right.y, left.z - right.z);
}


Set3f::Set3f () :
    first  (0),
    second (0),
    third  (0)
{}

Set3f::Set3f (double init_x, double init_y, double init_z) :
    first  (init_x),
    second (init_y),
    third  (init_z)
{}

std::string Set3f::ToString () const
{
    return "Set3f(coords: " + std::to_string (first) + ", " + std::to_string (second) + ", " + std::to_string (third) + ")";
}


Vector3f::Vector3f () :
    x (0),
    y (0),
    z (0),
    len (0)
{}

Vector3f::Vector3f (const Set3f& init_coords) :
    x (init_coords.first),
    y (init_coords.second),
    z (init_coords.third)
{
    len = sqrt (x*x + y*y + z*z);
}

Vector3f::Vector3f (const Point3f& start, const Point3f& end) :
    Vector3f (end - start)
{}

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


Ray3f::Ray3f () :
    start     (Point3f ()),
    direction (Vector3f ())
{}

Ray3f::Ray3f (const Point3f& init_start, const Vector3f& init_direction) :
    start     (init_start),
    direction (init_direction)
{}

Ray3f::Ray3f (const Point3f& init_start, const Point3f& some_point) :
    start     (init_start),
    direction (Vector3f (init_start, some_point))
{
    direction.Normalize ();
}

std::string Ray3f::ToString () const
{
    return "Ray3f(start: " + start.ToString () + "; direction: " + direction.ToString () + ")";
}