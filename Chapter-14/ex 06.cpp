#include "simple_window.h"


int main()
try
{
	Simple_window win{ Point{ 100,100 }, 600, 400, "exercise 6" };

	Striped_circle scirc{ Point{ 300,200 },100 };
	scirc.set_fill_color(Color::red);
	win.attach(scirc);

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
