#include "Simple_window.h"


int main()
try
{
	Simple_window win{ Point{100,100}, 600, 400, "Exercise 1" };
	Hat_smiley hsm{ Point{200,200}, 100 };
	hsm.move(-50, 0);
	hsm.set_color(Color::red);
	hsm.set_style(Line_style{ Line_style::solid, 4 });
	win.attach(hsm);
	Frowny hfr{ Point{400,200},100 };
	hfr.set_color(Color::dark_blue);
	hfr.set_radius(150);    //yeah, it doesn't work properly :D
	win.attach(hfr);
	win.wait_for_button();
}
catch (exception& e)
{
	cerr << e.what() << endl;
}
catch (...)
{
	cerr << "Exception!" << endl;
}
