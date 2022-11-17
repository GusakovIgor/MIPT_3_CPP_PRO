#include <Application.hpp>
#include <Math.hpp>
#include "Objects.hpp"


Spatial::Spatial ()
{
    position = Point3f (0, 0, 0);
    rotation = Set3f   (0, 0, 0);
    scale    = Set3f   (1, 1, 1);
}

Spatial::Spatial (const Point3f& init_position, const Set3f& init_rotation, const Set3f& init_scale)
{
    position = init_position;
    rotation = init_rotation;
    scale    = init_scale;
}

Point3f Spatial::Position () const
{
    return position;
}

Set3f Spatial::Rotation () const
{
    return rotation;
}

Set3f Spatial::Scale () const
{
    return scale;
}

void Spatial::Move (const Vector3f& delta)
{
    position.Move (delta);
}

void Spatial::Rotate (const Set3f& delta)
{
    rotation += delta;
}

void Spatial::ScaleUp (const Set3f& delta)
{
    scale += delta;
}


Object::Object ()
{
    spatial = Spatial ();
}

Object::Object (const Spatial& init_spatial)
{
    spatial = init_spatial;
}


Camera::Camera () : Object ()
{
    fov_degrees = 60.0;
    fov_radians = (fov_degrees / 180.0) * M_PI;
}

Camera::Camera (const Spatial& init_spatial, double init_fov_degrees) : Object (init_spatial)
{
    fov_degrees = init_fov_degrees;
    fov_radians = (fov_degrees / 180.0) * M_PI;
}

double Camera::GetFovDegrees ()
{
    return fov_degrees;
}

double Camera::GetFovRadians ()
{
    return fov_radians;
}


Light::Light () : Object ()
{
    intensity = 1.0;
}

Light::Light (const Spatial& init_spatial, double init_intensity) : Object (init_spatial)
{
    intensity = init_intensity;
}

double Light::Intensity ()
{
    return intensity;
}