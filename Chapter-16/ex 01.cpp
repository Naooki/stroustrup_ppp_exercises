#include "My_window.h"

int main()
try
{
	My_window win{ Point{100,100}, 600, 400, "exercise 1" };
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
	return 0;
}