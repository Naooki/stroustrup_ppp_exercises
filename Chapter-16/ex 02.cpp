#include "Checkerboard_window.h"

int main()
try
{
	Checkerboard_window win{ Point{ 100,100 }, "exercise 3" }; //It's all about Checkerboard_window.h
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