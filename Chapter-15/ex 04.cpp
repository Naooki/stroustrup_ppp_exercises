#include "Simple_window.h"

int main()
{
	Simple_window win(Point(100, 100), 600, 400, "ex 2");

	Axis x{ Axis::x,Point(100,200),400, 20, "Axis X" };
	win.attach(x);
	Axis y{ Axis::y,Point(300,350), 300, 15, "Axis Y" };
	win.attach(y);

	Func f1([](double x) { return sin(x); }, -10, 11, Point(300, 200), 200);
	f1.set_color(Color::red);
	win.attach(f1);
	Func f2([](double x) { return cos(x); }, -10, 11, Point(300, 200), 200);
	f2.set_color(Color::blue);
	win.attach(f2);
	Func f3([](double x) { return sin(x) + cos(x); }, -10, 11, Point(300, 200), 200);
	f3.set_color(Color::green);
	win.attach(f3);
	Func f4([](double x) { return sin(x)*sin(x) + cos(x)*cos(x); }, -10, 11, Point(300, 200), 200);
	f4.set_color(Color::yellow);
	win.attach(f4);
	win.wait_for_button();
}
