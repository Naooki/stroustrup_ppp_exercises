#include "simple_window.h"


int main()
try
{
	Simple_window win{ Point{ 100,100 }, 600, 400, "exercise 8" };
	
	Regular_Octagon oct{ Point{300,200}, 100 };
	oct.set_fill_color(Color::yellow);
	oct.set_color(Color::red);
	oct.set_style(Line_style(Line_style::solid, 4));
	oct.move(100, 0);
	win.attach(oct);

	win.wait_for_button();
}
catch (exception& e)
{
	cerr << e.what() << endl;
}
catch (...)
{
	cerr << "exception!" << endl;
}
