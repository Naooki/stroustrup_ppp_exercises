
#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)

using namespace Graph_lib;

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

struct Checkerboard_window : Window {
	Checkerboard_window(Point xy, const string& title)
		: Window(xy, 400, 420, title),
		button_pushed(false),
		next_button(Point(x_max() - 70, 0), 70, 20, "Next", cb_next),
		quit_button(Point(x_max() - 150, 0), 70, 20, "Quit", [](Address, Address pw) {reference_to<Checkerboard_window>(pw).quit(); })
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				cells.push_back(new Button{ Point(x_max() / 4 * j, 20 + (y_max() - 20) / 4 * i), 100, 100, "Check",
					[](Address pb, Address pw) { reference_to<Checkerboard_window>(pw).check(pb); } });
				//I tried to get "pb"(Widget address, accoriding to stroustrup book), through "reference_to<Button> get access to the object on
				//that address, and finally change label. But it seems like this address doesn't acctually provide access to the object, so
				// the program just stops whenever I try to change the label".
				
				
				attach(cells[cells.size() - 1]);
			}
		}
		attach(quit_button);
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

	Button next_button;
	Button quit_button;
	Vector_ref<Button> cells;
private:
	bool button_pushed;

	static void cb_next(Address, Address addr) // callback for next_button
											   //	{ reference_to<Simple_window>(addr).next(); }
	{
		static_cast<Checkerboard_window*>(addr)->next();
	}

	void next() { button_pushed = true; }
	void quit() { hide(); }
	void check(Address pb)
	{
		for (int i = 0; i < cells.size(); ++i)
		{
			cells[i].label = "Check";
		}
		reference_to<Widget>(pb).label = "CHEKED";
		redraw();	
	}
};
