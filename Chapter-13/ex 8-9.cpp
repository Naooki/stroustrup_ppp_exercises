//#include "Simple_window.h"
//
//
//int main()
//try
//{
//	Simple_window win{ Point{50,50},1000,600,"Regular Hexagons" };
//
//	Vector_ref<Regular_Hexagon> hexas;
//	Point pos{ 0,0 };
//	int rad = 20;
//	int row = 0;
//	for (int j = 0; j < 600; j += int(rad*sqrt(3)/2))
//	{
//		for (int i = 0; i< 1000; i += 3 * rad)
//		{
//			if (row % 2 == 0) hexas.push_back(new Regular_Hexagon{ Point{ i,j }, rad });
//			else hexas.push_back(new Regular_Hexagon{ Point{ i + int(1.5*rad),j }, rad });
//			win.attach(hexas[hexas.size() - 1]);
//		}
//		++row;
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