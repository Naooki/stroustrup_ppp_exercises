#include "MovingShape_window.h"

int main()
try
{
	MovingShape_window win{ Point(100,100), 600,400, "Exercise 4" };
	while (true)
	{
		win.wait_for_button();

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
