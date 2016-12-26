#include "simple_window.h"


int main()
try
{
	Simple_window win{ Point{ 100,100 }, 600, 400, "exercise 7" };

	/*Striped_closed_pylyline scp;
	scp.set_fill_color(Color::red);
	win.attach(scp);*/

	Striped_closed_polyline cp;
	cp.add(Point{ 100,100 });
	cp.add(Point{ 500,100 });
	cp.add(Point{ 450,300 });
	cp.add(Point{ 400,50 });
	cp.add(Point{ 350,250 });

	cp.set_fill_color(Color::red);
	win.attach(cp);

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
