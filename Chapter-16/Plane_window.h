
#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)

using namespace Graph_lib;

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

struct Plane_window : Window {
	Plane_window(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		stop_button(Point(x_max() - 100, 0), 80, 20, "Stop", [](Address, Address pw) { reference_to<Plane_window>(pw).stop(); }),
		start_button(Point(x_max() - 200, 0), 80, 20, "Start", [](Address, Address pw) { reference_to<Plane_window>(pw).start(); }),
		plane( Point(1000,300), "sabre.gif" ),
		paused(true)
	{
		attach(start_button);
		attach(stop_button);
		attach(plane);
	}
	void wait_for_button() {
		if (paused) Fl::wait();
		else {
			Sleep(100);
			Fl::wait();
			plane.move(-10, 0);
			redraw();
		}
	}

private:
	Button start_button;
	Button stop_button;
	bool paused;
	Image plane;
	void start() { paused = false; }
	void stop() { paused = true; }
};
