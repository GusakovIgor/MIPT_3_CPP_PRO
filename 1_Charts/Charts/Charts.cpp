#include <Math.hpp>
#include <Events.hpp>
#include <Application.hpp>
#include <iostream>
#include "Charts.hpp"


ChartFunction::ChartFunction () :
	m_function (NULL),
	m_colour   (DefaultColour)
{}

ChartFunction::ChartFunction (Function init_function, Colour init_colour) :
	m_function (init_function),
	m_colour   (init_colour)
{}


Chart::Chart () :
	m_lcorner (Point2f ()),
	m_rcorner (Point2f ()),
	m_xrange  (Set2f ()),
	m_yrange  (Set2f ())
{}

Chart::Chart (Application* App,
			  const Point2f& init_lcorner,
			  const Point2f& init_rcorner,
			  const Set2f& init_xrange,
			  const Set2f& init_yrange
			 ) :
	m_lcorner (init_lcorner),
	m_rcorner (init_rcorner),
	m_xrange  (init_xrange),
	m_yrange  (init_yrange)
{
	m_width  = m_rcorner.x - m_lcorner.x;
	m_height = m_rcorner.y - m_lcorner.y;

	m_xfactor = (m_rcorner.x - m_lcorner.x) / (m_xrange.second - m_xrange.first);
	m_yfactor = (m_rcorner.y - m_lcorner.y) / (m_yrange.second - m_yrange.first);

	m_texture = App->CreateTexture (m_rcorner.x - m_lcorner.x, m_rcorner.y - m_lcorner.y);
}

void Chart::CheckEvent (const Event& event)
{
	switch (event.base.type)
	{
		case APP_MOUSEMOTION:	CheckMouseMotion (event.base.motion.state, event.base.motion.xrel, event.base.motion.yrel);
								break;

		case APP_MOUSEWHEEL:	CheckMouseWheel (event.base.wheel.preciseY);
								break;

		default:				break;
	}
}

void Chart::CheckMouseMotion (uint32_t buttons_state, int32_t x_motion, int32_t y_motion)
{
	if ((buttons_state & APP_LEFTBUTTON) == 0)
	{
		return;
	}

	float xrange_motion = -x_motion / m_xfactor;
	float yrange_motion = +y_motion / m_yfactor;

	m_xrange.first  += xrange_motion;
	m_xrange.second += xrange_motion;
	m_yrange.first  += yrange_motion;
	m_yrange.second += yrange_motion;

	m_need_update = true;
}

void Chart::CheckMouseWheel (float y_scroll)
{
	float y_factor = 1.1;

	if (y_scroll > 0.0)
	{
		y_factor = 1.0 / y_factor;
	}

	m_xrange.first  *= y_factor;
	m_xrange.second *= y_factor;
	m_yrange.first  *= y_factor;
	m_yrange.second *= y_factor;

	m_xfactor /= y_factor;
	m_yfactor /= y_factor;

	m_need_update = true;
}

void Chart::AddFunction (ChartFunction* new_function)
{
	m_functions.push_back (new_function);

	m_need_update = true;
}

void Chart::Draw (Application* App)
{
	if (m_need_update)
	{
		UpdateTexture (App);
	}

	App->DrawTexture (m_texture, m_lcorner, m_rcorner);
}


void Chart::UpdateBase (Application* App) const
{
	static char* y_min = (char*) calloc (20, sizeof (char*));
	static char* y_max = (char*) calloc (20, sizeof (char*));
	static char* x_min = (char*) calloc (20, sizeof (char*));
	static char* x_max = (char*) calloc (20, sizeof (char*));

	// snprintf (y_min, "%.1f", m_yrange.first);
	// snprintf (y_max, "%.1f", m_yrange.second);
	// snprintf (x_min, "%.1f", m_xrange.first);
	// snprintf (x_max, "%.1f", m_xrange.second);

	float arrow_factor = 0.01;

	App->ClearScreen ();
	App->DrawRect (Point2f (0, 0), Point2f (m_width, m_height), Maroon);

	float offset_xcentre = (0.0 - m_xrange.first) * m_xfactor;
	float offset_ycentre = (m_yrange.second - 0.0) * m_yfactor;

	if (offset_ycentre > 0.0)
	{
		App->DrawLine (Point2f (0, offset_ycentre), Point2f (m_width, offset_ycentre), White);
		App->DrawLine (Point2f (m_width * (1 - arrow_factor), offset_ycentre * (1 - arrow_factor)), Point2f (m_width, offset_ycentre), White);
		App->DrawLine (Point2f (m_width * (1 - arrow_factor), offset_ycentre * (1 + arrow_factor)), Point2f (m_width, offset_ycentre), White);
	}

	if (offset_xcentre > 0.0)
	{
		App->DrawLine (Point2f (offset_xcentre, m_height), Point2f (offset_xcentre, 0), White);
		App->DrawLine (Point2f (offset_xcentre * (1.0 - arrow_factor), m_height * arrow_factor), Point2f (offset_xcentre, 0), White);
		App->DrawLine (Point2f (offset_xcentre * (1.0 + arrow_factor), m_height * arrow_factor), Point2f (offset_xcentre, 0), White);
	}
}


void Chart::UpdateTexture (Application* App)
{
	App->SetTextureMode (m_texture);

	UpdateBase (App);

	for (const ChartFunction* chart_function : m_functions)
	{
		float step = (1.0 / m_xfactor) * 0.01;

		for (float chart_x = m_xrange.first; chart_x < m_xrange.second; chart_x += step)
		{
			float chart_y = (*chart_function->m_function)(chart_x);

			float window_x = (chart_x - m_xrange.first) * m_xfactor;
			float window_y = (m_yrange.second - chart_y) * m_yfactor;

			if (0 < window_y && window_y < m_height)
			{
				App->DrawPoint (Point2f (window_x, window_y), chart_function->m_colour);
			}
		}
	}

	App->SetWindowMode ();

	m_need_update = false;
}

bool Chart::ContainsPoint (Point2f point)
{
	if (m_lcorner.x < point.x && point.x < m_rcorner.x &&
		m_lcorner.y < point.y && point.y < m_rcorner.y)
	{
		return true;
	}

	return false;
}


ChartManager::ChartManager ()
{}

void ChartManager::AddChart (Chart* new_chart)
{
	charts.push_back (new_chart);
}

void ChartManager::AddFunction (ChartFunction* new_function)
{
	for (Chart* chart : charts)
	{
		chart->AddFunction (new_function);
	}
}

void ChartManager::Draw (Application* App)
{
	for (Chart* chart : charts)
	{
		chart->Draw (App);
	}
}

void ChartManager::CheckEvents (Application* App)
{
	int active_chart = 0;

	for (Chart* chart : charts)
	{
		if (chart->ContainsPoint (App->GetMouse ()))
		{
			break;
		}

		++active_chart;
	}

	Event event;

	while (App->PollEvent (&event))
	{
		charts[active_chart]->CheckEvent (event);
	}
}