//#include "Simple_window.h"
//
//
//int main()
//try
//{
//	Simple_window win{ Point{ 50,50 },800,800,"Colour matrix" };
//
//	Point p1{ 200,400 };
//	Right_triangle rt1{ p1,40,80,0 };
//	rt1.set_fill_color(Color::red);
//	win.attach(rt1);
//	Right_triangle rt2{ rt1.point(2),40,80,-45 };
//	rt2.set_fill_color(Color::magenta);
//	win.attach(rt2);
//	Right_triangle rt3{ rt2.point(2),40,80,-90 };
//	rt3.set_fill_color(Color::blue);
//	win.attach(rt3);
//	Right_triangle rt4{ rt3.point(2),40,80,-135 };
//	rt4.set_fill_color(Color::cyan);
//	win.attach(rt4);
//	Right_triangle rt5{ rt4.point(2),40,80,-180 };
//	rt5.set_fill_color(Color::dark_blue);
//	win.attach(rt5);
//	Right_triangle rt6{ rt5.point(2),40,80,-225 };
//	rt6.set_fill_color(Color::dark_yellow);
//	win.attach(rt6);
//	Right_triangle rt7{ rt6.point(2),40,80,-270 };
//	rt7.set_fill_color(Color::green);
//	win.attach(rt7);
//	Right_triangle rt8{ rt7.point(2),40,80,-315 };
//	rt8.set_fill_color(Color::yellow);
//	win.attach(rt8);
//	win.wait_for_button();
//}
//catch (exception& e) {
//	cerr << "exception: " << e.what() << endl;
//	keep_window_open();
//}
//catch (...) {
//	cerr << "exception" << endl;
//	keep_window_open();
//}