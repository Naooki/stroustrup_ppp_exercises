#include "ShapeMenu_window.h"

int main()
try
{
	ShapeMenu_window win{ Point(100,100), 600,400, "Exercise 4" };
	return gui_main();
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
