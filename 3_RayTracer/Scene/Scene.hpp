class Scene
{

private:

	int32_t active_camera;
	vector <Camera*> Cameras;

	vector <Light*> Lights;
	vector <Figure*> Figures;

	// queue <Event> Events;
	// vector <>

	Camera* ActiveCamera ();
	void MoveActiveCamera (const Vector3f& delta);

	Colour RayCast (const Ray3f& ray);
	int32_t GetHit (const Ray3f& ray, Point3f* hit_point);

public:

	Scene ();

	void AddCamera (Camera* camera);
	void AddLight  (Light* light);
	void AddFigure (Figure* figure);

	void Render (Application* App);

	// void CheckEvents (Application* App);
};