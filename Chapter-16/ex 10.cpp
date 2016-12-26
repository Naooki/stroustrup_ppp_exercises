#include "Function_window.h"

int main()
try
{
	Function_window win{ Point(100,100), 800, 800, "Exercise 10" };
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