#include <Application.hpp>
#include <Math.hpp>
#include <Materials.hpp>
#include <Objects.hpp>
#include <Figures.hpp>
#include "Scene.hpp"


Scene::Scene ()
{
	static Camera* default_camera = new Camera ();

	Cameras.push_back (default_camera);

	active_camera = 0;
}

void Scene::AddCamera (Camera* camera)
{
    Cameras.push_back (camera);
}

void Scene::AddLight (Light* light)
{
	Lights.push_back (light);
}

void Scene::AddFigure (Figure* figure)
{
	Figures.push_back (figure);
}


void Scene::Render (Application* App)
{
    static const int32_t app_width  = App->Width  ();
    static const int32_t app_height = App->Height ();

    static const double view_x_factor = (2.0 / static_cast<double>(app_width));
    static const double view_y_factor = (2.0 / static_cast<double>(app_height));
    static const double aspect_ratio  = app_width / static_cast<double>(app_height);

    Camera* current_camera = ActiveCamera ();
    const double fov_factor = tan (current_camera->GetFovRadians () / 2.0);

    for (uint32_t i = 0; i < app_width; ++i)
    {
        for (uint32_t j = 0; j < app_height; ++j)
        {
            coord_t x =  ((static_cast<coord_t>(i) + 0.5) * view_x_factor - 1) * fov_factor * aspect_ratio;
            coord_t y = -((static_cast<coord_t>(j) + 0.5) * view_y_factor - 1) * fov_factor;

            Ray3f test_ray (current_camera->spatial.Position (), Point3f (x, y, -1));

            Colour point_colour = RayCast (test_ray);

            int32_t max_colour = std::max (point_colour.red, std::max (point_colour.green, point_colour.blue));

            if (max_colour > 255)
            {
                point_colour = point_colour * (1.0 / static_cast<double> (max_colour));
            }

            App->DrawPoint (Point2f (i, j), point_colour);
        }
    }
}

Colour Scene::RayCast (const Ray3f& ray)
{
	Colour result = Grey;

    Point3f hit_point;

    int32_t hit_figure = GetHit (ray, &hit_point);

    if (hit_figure != -1)
    {
	    result = Figures[hit_figure]->GetCollisionColour (Lights, hit_point);
    }

    return result;
}

int32_t Scene::GetHit (const Ray3f& ray, Point3f* hit_point)
{
    int32_t hit_figure = -1;

    coord_t intersection_dist = 0.0;

    coord_t min_intersection_dist = std::numeric_limits<float>::max ();

    for (int32_t current_figure = 0; current_figure < Figures.size (); ++current_figure)
    {
    	intersection_dist = Figures[current_figure]->GetCollision (ray);

        if (0 < intersection_dist && intersection_dist < min_intersection_dist)
        {
            hit_figure = current_figure;

            min_intersection_dist = intersection_dist;
        }
    }

    *hit_point = ray.start.Move (ray.direction * min_intersection_dist);

    return hit_figure;
}


Camera* Scene::ActiveCamera ()
{
    return dynamic_cast <Camera*> (Cameras[active_camera]);
}

void Scene::MoveActiveCamera (const Vector3f& delta)
{
    Camera* current_camera = ActiveCamera ();

    current_camera->spatial.Move (delta);
}

// void Scene::CheckEvents (queue <Event>& events)
// {
//     while (!events.empty ())
//     {
//         Event current_event = events.front ();

//         events.pop ();

//         switch (current_event.type)
//         {
//             case EVENT_MOUSEMOTION:     
//                                         break;

//             case EVENT_MOUSEBUTTON:     
//                                         break;

//             case EVENT_MOUSEWHEEL:      
//                                         break;

//             case EVENT_KEYBOARD:        
//                                         break;
//         }
//     }
// }