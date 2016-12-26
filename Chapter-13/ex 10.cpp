//#include "Simple_window.h"
//
//
//int main()
//try
//{
//	Simple_window win{ Point{ 50,50 },1000,600,"Regular N-gon" };
//
//	Point p{ 500,300 };
//	Regular_polygon rp3{ p,3,50 };
//	win.attach(rp3);
//	Regular_polygon rp4{ p,4,80 };
//	win.attach(rp4);
//	Regular_polygon rp5{ p,5,110 };
//	win.attach(rp5);
//	Regular_polygon rp6{ p,6,140 };
//	win.attach(rp6);
//	Regular_polygon rp7{ p,7,170 };
//	win.attach(rp7);
//	Regular_polygon rp8{ p,8,200 };
//	win.attach(rp8);
//
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