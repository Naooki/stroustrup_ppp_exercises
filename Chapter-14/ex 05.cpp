#include "simple_window.h"


int main()
try
{
	Simple_window win{ Point{100,100}, 600, 400, "exercise 5" };
	
	Striped_rectangle srect{ Point {100,100},200,100 };
	srect.set_fill_color(Color::red);
	win.attach(srect);

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
