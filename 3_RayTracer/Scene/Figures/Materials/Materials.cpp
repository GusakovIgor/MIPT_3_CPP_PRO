#include <Application.hpp>
#include "Materials.hpp"


Material::Material ()
{
    colour = Black;
}

Material::Material (const Colour& init_colour)
{
    colour = init_colour;
}