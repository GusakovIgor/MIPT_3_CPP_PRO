#include <vector>

using std::vector;



class Spatial
{
private:

    Point3f position;

    Set3f rotation;

    Set3f scale;

public:

    explicit Spatial ();
    explicit Spatial (const Point3f& init_position, const Set3f& init_rotation = Set3f (0.0, 0.0, 0.0), const Set3f& init_scale = Set3f (1.0, 1.0, 1.0));

    Point3f Position () const;
    Set3f   Rotation () const;
    Set3f   Scale    () const;

    void Move    (const Vector3f& delta);
    void Rotate  (const Set3f& delta);
    void ScaleUp (const Set3f& delta);
};


class Object
{
public:

    Spatial spatial;

    Object ();
    explicit Object (const Spatial& init_spatial);
    virtual ~Object () {}
};



class Camera : public Object
{
private:

    double fov_degrees;
    double fov_radians;

public:

    Camera ();
    explicit Camera (const Spatial& init_spatial, double init_fov_degrees = 60.0);

    double GetFovDegrees ();
    double GetFovRadians ();
};


class Light : public Object
{
private:

    double intensity;

public:

    Light ();
    explicit Light (const Spatial& init_spatial, double init_intensity);

    double Intensity ();
};