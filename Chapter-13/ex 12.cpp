#include "Simple_window.h"


int main()
try
{
	Simple_window win{ Point{ 50,50 },1000,600,"Moving mark" };

	Point center{ 500,300 };
	int radius = 200;
	Graph_lib::Circle my_circle{ center, radius };
	win.attach(my_circle);
	
	constexpr double pi = 3.1415926;
	
	double theta = 0;
	double dtheta = pi / 8;
	Point mark_pos{ center.x + radius, center.y };
	Mark my_mark{ mark_pos, 'x' };
	win.attach(my_mark);
	win.wait_for_button();

	for(int i = 0; i < 20; ++i)
	{
		int dx = -int(radius*(cos(theta) - cos(theta + dtheta)));
		int dy = int(radius*(sin(theta) - sin(theta + dtheta)));
		theta += dtheta;
		my_mark.move(dx, dy);
		win.wait_for_button();
	}
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	keep_window_open();
}
catch (...) {
	cerr << "exception" << endl;
	keep_window_open();
}
