#include "Simple_window.h"

int main()
try
{
	Graph_lib::Window win{ Point(100,100), 600, 600, "Exercise 6" };
	Clock clk{ Point(300,300), 200 };
	win.attach(clk);
	win.redraw();
	while (true) {
		Fl::wait(); //nice, but how does it work? =/
		Sleep(1000);
		clk.increase_time();
		win.redraw();
	}
	
}
catch (exception& e)
{
	cerr << e.what() << endl;
	return 1;
}
catch (...)
{
	cerr << "Exception!" << endl;
	return 2;
}
