#ifndef MATH_HPP
#define MATH_HPP

#include <string>
#include <cmath>


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


class Point2f;
class Set2f;
class Point3f;
class Set3f;
class Vector3f;
class Ray3f;


class Point2f
{

public:

    float x;
    float y;

    Point2f ();
    explicit Point2f (float init_x, float init_y);
    std::string ToString () const;

    operator SDL_FPoint() const;
};

Set2f operator- (const Point2f& left, const Point2f& right);

class Set2f
{

public:

    double first;
    double second;

    Set2f ();
    explicit Set2f (double init_x, double init_y);
    std::string ToString () const;
};

class Vector2f
{

private:

    Vector2f (const Set2f& a);


public:

    double x;
    double y;

    double len;

    Vector2f ();
    explicit Vector2f (const Point2f& start, const Point2f& end);
    std::string ToString () const;

    void Normalize ();
};




class Point3f
{

public:

    double x;
    double y;
    double z;

    Point3f ();
    explicit Point3f (double init_x, double init_y, double init_z);
    std::string ToString () const;
};

Set3f operator- (const Point3f& left, const Point3f& right);

class Set3f
{

public:

    double first;
    double second;
    double third;

    Set3f ();
    explicit Set3f (double init_x, double init_y, double init_z);
    std::string ToString () const;
};


class Vector3f
{

private:

    Vector3f (const Set3f& a);


public:

    double x;
    double y;
    double z;

    double len;

    Vector3f ();
    explicit Vector3f (const Point3f& start, const Point3f& end);
    std::string ToString () const;

    void Normalize ();
};

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


#endif // MATH_HPP