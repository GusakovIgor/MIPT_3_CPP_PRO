#include <Application.hpp>
#include <Math.hpp>
#include <Objects.hpp>
#include <Materials.hpp>
#include "Figures.hpp"


Figure::Figure () : Object ()
{
	material = Material ();
}

Figure::Figure (const Spatial& init_spatial, const Material& init_material) : Object (init_spatial)
{
	material = init_material;
}

Colour Figure::GetColour ()
{
    return material.colour;
}


Sphere3f::Sphere3f () : Figure ()
{
    radius = 0;
}

Sphere3f::Sphere3f (const Spatial& init_spatial, coord_t init_radius, const Material& init_material) : Figure (init_spatial, init_material)
{
    radius = init_radius;
}

std::string Sphere3f::ToString () const
{
    return "Sphere3f(position: " + (spatial.Position ()).ToString () + "; radius: " + std::to_string (radius) + ")";
}


coord_t Sphere3f::GetCollision (const Ray3f& ray)
{
    Vector3f centre_direction = Vector3f (ray.start, spatial.Position ());

    coord_t centre_direction_projection = centre_direction * ray.direction;

    if (centre_direction_projection < 0)
    {
        return -1;
    }

    coord_t ray_centre_distance_sq = centre_direction * centre_direction - centre_direction_projection * centre_direction_projection;

    coord_t sphere_radius_sq = radius * radius;

    if (ray_centre_distance_sq > sphere_radius_sq)
    {
        return -1;
    }

    coord_t intersection_centre_distance = sqrt (sphere_radius_sq - ray_centre_distance_sq);

    coord_t start_intersection_distance = centre_direction_projection - intersection_centre_distance;

    if (start_intersection_distance < 0)
    {
        start_intersection_distance = centre_direction_projection + intersection_centre_distance;
    }

    if (start_intersection_distance < 0)
    {
        return -1;
    }

    return start_intersection_distance;
}


Colour Sphere3f::GetCollisionColour (const vector<Light*>& lights, const Point3f& hit_point)
{
    double light_intensity = GetLight (lights, hit_point);

    return GetColour () * light_intensity;
}


double Sphere3f::GetLight (const vector<Light*>& lights, const Point3f& hit_point)
{
    Vector3f point_normal = Vector3f (spatial.Position (), hit_point);
    point_normal.Normalize ();

    double total_intensity = 0.0;

    for (Light* light : lights)
    {
        Vector3f light_reversed_direction = Vector3f (hit_point, light->spatial.Position ());

        light_reversed_direction.Normalize ();

        double light_reduce_factor = std::max (0.0, light_reversed_direction * point_normal);

        total_intensity += light->Intensity () * light_reduce_factor;
    }

    total_intensity /= lights.size ();

    return total_intensity;
}