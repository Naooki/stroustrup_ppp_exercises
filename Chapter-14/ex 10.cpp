#include "simple_window.h"


int main()
try
{
	Simple_window win{ Point{ 100,100 }, 800, 600, "exercise 10" };
	Pseudo_window pw{ Point{100,100},400,300, "My_pseudo_window" };
	win.attach(pw);

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
