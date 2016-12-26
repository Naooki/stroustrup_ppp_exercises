#include "Simple_window.h"

int main()
{
	Simple_window win(Point(100, 100), 600, 400, "ex 2");

	Axis x{ Axis::x,Point(100,200),400, 20, "Axis X" };
	win.attach(x);
	Axis y{ Axis::y,Point(300,350), 300, 15, "Axis Y" };
	win.attach(y);

	Func my_func([](double x) { return x*x; }, -10, 11, Point(300, 200), 200);
	win.attach(my_func);
	win.wait_for_button();
	my_func.set_function([](double x) {return pow(2, x); });
	win.wait_for_button();
	my_func.set_function([](double x) {return log(x); });
	win.wait_for_button();
	my_func.set_function([](double x) {return abs(x); });
	win.wait_for_button();
}
