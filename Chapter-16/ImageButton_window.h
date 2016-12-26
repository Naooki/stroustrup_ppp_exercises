
#include <random>
#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)

using namespace Graph_lib;

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

struct ImageButton_window : Window {
	ImageButton_window(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		button_pushed(false),
		next_button(Point(x_max() - 70, 0), 70, 20, "Next", cb_next),
		image_button(Point(x_max() / 2, y_max() / 2), 100, 50, "img_button", [](Address, Address pw) {reference_to<ImageButton_window>(pw).move(); }),
		img(image_button.loc, "button_img.jpg")
	{
		attach(image_button);
		attach(img);
		attach(next_button);
	}

	void wait_for_button()
		// modified event loop
		// handle all events (as per default), but quit when button_pushed becomes true
		// this allows graphics without control inversion
	{
		while (!button_pushed) Fl::wait();
		button_pushed = false;
		Fl::redraw();
	}
	Button image_button;
	Image img;
	Button next_button;
private:
	bool button_pushed;

	static void cb_next(Address, Address addr) // callback for next_button
											   //	{ reference_to<Simple_window>(addr).next(); }
	{
		static_cast<ImageButton_window*>(addr)->next();
	}

	void next() { button_pushed = true; }
	void move();
};

inline int rand_int(int min, int max)
{
	static default_random_engine ran;
	return uniform_int_distribution<>{min, max} (ran);
}

void ImageButton_window::move()
{
	int new_x{ rand_int(0, x_max() - 200) };
	int new_y{ rand_int(0, y_max() - 100) };
	int dx{ new_x - image_button.loc.x };
	int dy{ new_y - image_button.loc.y };
	image_button.move(dx, dy);
	img.move(dx, dy);
	redraw();
}

