#include <vector>


using std::vector;


typedef double (*Function) (double argument);


struct ChartFunction
{
	Function m_function;
	Colour   m_colour;

	ChartFunction ();
	explicit ChartFunction (Function init_function, Colour init_colour);
};


class Chart
{

private:

	vector <ChartFunction*> m_functions;

	Texture* m_texture = NULL;
	bool m_need_update = false;

	Point2f m_lcorner;
	Point2f m_rcorner;

	Set2f m_xrange;
	Set2f m_yrange;

	float m_width;
	float m_height;

	float m_xfactor = 1.0;		// pixels per chart 1
	float m_yfactor = 1.0;		// pixels per chart 1

	void UpdateTexture (Application* App);
	void UpdateBase (Application* App) const;

	void CheckMouseMotion (uint32_t buttons_state, int32_t x_motion, int32_t y_motion);
	void CheckMouseWheel (float y_scroll);


public:

	Chart ();
	Chart (Application* App,
		   const Point2f& init_lcorner,
		   const Point2f& init_rcorner,
		   const Set2f& init_xrange,
		   const Set2f& init_yrange
		  );

	void CheckEvent (const Event& event);

	void AddFunction (ChartFunction* new_function);
	void Draw (Application* App);

	bool ContainsPoint (Point2f point);
};


class ChartManager
{

private:

	vector <Chart*> charts;

public:

	ChartManager ();

	void AddChart (Chart* new_chart);
	void AddFunction (ChartFunction* new_function);

	void Draw (Application* App);

	void CheckEvents (Application* App);
};