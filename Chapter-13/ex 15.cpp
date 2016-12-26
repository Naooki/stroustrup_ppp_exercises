//#include "Simple_window.h"
//
//
//int main()
//try
//{
//	Simple_window win{ Point{ 50,50 },800,800,"Colour matrix" };
//
//	int x_side{ 40 };
//	int y_side{ 80 };
//	Vector_ref<Right_triangle> rts;
//	for (int i = 0; i <= win.x_max(); i += x_side)
//	{
//		for (int j = 0; j <= win.y_max(); j += y_side)
//		{
//			rts.push_back(new Right_triangle{ Point{i,j}, x_side, y_side, 0 });
//			win.attach(rts[rts.size() - 1]);
//		}
//	}
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