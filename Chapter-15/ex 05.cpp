#include "Simple_window.h"


double Leibniz_n_element(int n)
{
		return pow(-1, n) / (2 * n + 1);
}

int main()
{
	Simple_window win(Point(100, 100), 1000, 600, "ex 2");

	Axis x{ Axis::x,Point(100,300),800, 20, "Axis X" };
	win.attach(x);
	Axis y{ Axis::y,Point(300,550), 500, 15, "Axis Y" };
	win.attach(y);

	[n](double x) {return Leibniz(x, n); }
	Open_polyline leib;
	win.attach(leib);
	for (int i = 0; i < 100; ++i)
	{
		leib.add(Point(50 + 8 * i, 300 - 150 + 200*Leibniz_n_element(i)));
	}
	win.wait_for_button();

}
