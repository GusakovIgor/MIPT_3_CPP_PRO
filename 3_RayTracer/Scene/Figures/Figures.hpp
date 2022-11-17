

class Figure : public Object
{

private:

	Material material;

public:

	Figure ();
	explicit Figure (const Spatial& init_spatial, const Material& init_material);

    Colour GetColour ();



    virtual coord_t GetCollision (const Ray3f& ray) = 0;
    virtual Colour GetCollisionColour (const vector<Light*>& lights, const Point3f& hit_point) = 0;
};



class Sphere3f : public Figure
{

private:

    coord_t radius;

    double GetLight (const vector<Light*>& lights, const Point3f& hit_point);

public:

    Sphere3f ();
    explicit Sphere3f (const Spatial& init_spatial, coord_t init_radius, const Material& init_material);

    std::string ToString () const;


    coord_t GetCollision (const Ray3f& ray) override;

    Colour GetCollisionColour (const vector<Light*>& lights, const Point3f& hit_point) override;
};