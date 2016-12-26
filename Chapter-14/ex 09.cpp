#include "simple_window.h"


int main()
try
{
	Simple_window win{ Point{ 100,100 }, 600, 400, "exercise 9" };

	Group gr;
	Circle cir{ Point{ 200,200 }, 100 };
	gr.add(cir);
	Graph_lib::Rectangle rect{ Point{ 300,300 },200,100 };
	gr.add(rect);

	win.attach(gr);

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
