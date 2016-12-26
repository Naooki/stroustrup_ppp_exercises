#include "ImageButton_window.h"

int main()
try
{
	ImageButton_window win{ Point(100,100), 600,400, "Exercise 3" };
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
