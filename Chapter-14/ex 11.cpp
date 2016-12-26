#include "simple_window.h"

int main()
try
{
	Simple_window win{ Point{ 100,100 }, 800, 600, "exercise 10" };
	

	Binary_tree tree{ Point{400,50},4 };
	win.attach(tree);

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
