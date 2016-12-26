#include "Simple_window.h"

int main()
try
{
	Simple_window win{ Point{100,50}, 1200,800,"Test window" };

	Graph_lib::Rectangle rct{ Point{500,500},200,100 };
	rct.set_fill_color(Color::dark_green);
	win.attach(rct);

	TextBox window{ Point{150,50}, 70, "Window" };
	win.attach(window);
	TextBox line_style{ Point{ 300,50 }, 85, "Line_style" };
	win.attach(line_style);
	TextBox color{ Point{ 450,50 }, 70, "Color" };
	win.attach(color);

	TextBox simple_window{ Point{ 115,150 }, 140, "Simple_Window" };
	Arrow ar1{ n(simple_window),s(window) };
	win.attach(ar1);
	win.attach(simple_window);

	TextBox shape{ Point{ 350,150 }, 70, "Shape" };
	win.attach(shape);
	TextBox point{ Point{ 500,150 }, 70, "Point" };
	win.attach(point);

	TextBox line{ Point{ 50,300 }, 70, "Line" };
	Arrow ar2{ n(line),w(shape) };
	win.attach(ar2);
	win.attach(line);
	TextBox lines{ Point{ 150,300 }, 70, "Lines" };
	Arrow ar3{ n(lines),sw(shape) };
	win.attach(ar3);
	win.attach(lines);
	TextBox polygon{ Point{ 250,300 }, 70, "Polygon" };
	Arrow ar4{ n(polygon),Point{s(shape).x - shape.width() / 4, s(shape).y} };
	win.attach(ar4);
	win.attach(polygon);
	TextBox axis{ Point{ 350,300 }, 70, "Axis" };
	Arrow ar5{ n(axis), s(shape) };
	win.attach(ar5);
	win.attach(axis);
	TextBox rectangle{ Point{ 450,300 }, 80, "Rectangle" };
	Arrow ar6{ n(rectangle),Point{ s(shape).x + shape.width() / 4, s(shape).y } };
	win.attach(ar6);
	win.attach(rectangle);
	TextBox text{ Point{ 550,300 }, 70, "Text" };
	Arrow ar7{ n(text), se(shape) };
	win.attach(ar7);
	win.attach(text);
	TextBox image{ Point{ 650,300 }, 70, "Image" };
	Arrow ar8{ n(image), e(shape) };
	win.attach(ar8);
	win.attach(image);

	win.wait_for_button();
}
catch (exception& e)
{
	cerr << e.what() << endl;
}
catch (...)
{
	cerr << "Exception!" << endl;
}
