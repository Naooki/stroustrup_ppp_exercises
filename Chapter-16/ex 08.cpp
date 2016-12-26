#include "Currency_window.h"

int main()
try
{
	Currency_window win{ Point(100,100), 600, 400, "Exercise 8" };
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