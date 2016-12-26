#include "Simple_window.h"


int main()
try
{
	Simple_window win{ Point{ 50,50 },800,800,"Colour matrix" };

	 this one should work
	vector<Point> points;
	points.push_back(Point(100, 100));
	points.push_back(Point(150, 100));
	points.push_back(Point(150, 150));
	points.push_back(Point(125, 150));
	points.push_back(Point(100, 125));
	Poly p(points);
	win.attach(p);
	win.wait_for_button();
	p.set_fill_color(Color::red);
	win.wait_for_button();

	 this one should complain
	vector<Point> points2;
	points2.push_back(Point(300, 300));
	points2.push_back(Point(350, 300));
	points2.push_back(Point(350, 350));
	points2.push_back(Point(325, 275));
	Poly p2(points2);    complain!
	win.attach(p2);

	win.wait_for_button();
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	keep_window_open();
}
catch (...) {
	cerr << "exception" << endl;
	keep_window_open();
}
