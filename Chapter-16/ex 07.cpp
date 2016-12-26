#include "Plane_window.h"

int main()
try
{
	Plane_window win{ Point(100,100), 1400, 600, "Exercise 7" };
	while (true) {
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
