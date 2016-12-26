//#include "Simple_window.h"
//
//
//int main()
//try
//{
//	Simple_window win{ Point{ 50,50 },1000,600,"Regular N-gon" };
//
//	
//	Graph_lib::Ellipse elps{ Point{500,300}, 150, 100 };
//	Axis ox{ Axis::Orientation::x, Point{ 300,300 }, 400, 40,"Horizontal axis" };
//	win.attach(ox);
//	Axis oy{ Axis::Orientation::y, Point{ 500,450 }, 300, 40,"Vertical axis" };
//	win.attach(oy);
//
//	Mark foc1{ elps.focus1(), 'x' };
//	win.attach(foc1);
//	Mark foc2{ elps.focus2(), 'x' };
//	win.attach(foc2);
//	win.attach(elps);
//
//	Point elps_p;
//	elps_p.x = elps.center().x + int(elps.major()*sqrt(2) / 2);
//	elps_p.y = elps.center().y + int(elps.minor()*sqrt(2) / 2);
//	Mark mark_elps_p{ elps_p, 'x' };
//	win.attach(mark_elps_p);
//	Graph_lib::Line l1{ elps.focus1(),elps_p };
//	win.attach(l1);
//	Graph_lib::Line l2{ elps.focus2(),elps_p };
//	win.attach(l2);
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