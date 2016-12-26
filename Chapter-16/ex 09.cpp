#include "Calculator_window.h"

int main()
try
{
	Calculator_window win{ Point(100,100), 550, 200, "Exercise 9" };
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