//// Chapter 13, exercise 07: make an RGB color chart
//#include "Simple_window.h"
//
//int main()
//try {
//	using namespace Graph_lib;
//
//	Point tl(200, 50);
//	Simple_window win(tl, 1400, 800, "RGB chart");
//
//
//	Vector_ref<Graph_lib::Rectangle> cells;
//	Point pos{ 0,0 };
//	int size = 10;
//	for (int k = 1; k <= 16; ++k)
//	{
//		for (int i = 0; i < 16; ++i)
//		{
//			for (int j = 0; j < 16; ++j)
//			{
//				cells.push_back(new Graph_lib::Rectangle{ pos,size,size });
//				cells[cells.size() - 1].set_fill_color(fl_rgb_color(16 * i, 16 * j, 16 * k - 1));
//				cells[cells.size() - 1].set_color(Color::black);
//				win.attach(cells[cells.size() - 1]);
//				pos.x += size;
//			}
//			pos.x -= 16 * size;
//			pos.y += size;
//		}
//		if (!(k % 4))
//		{
//			pos.x = 0;
//		}
//		else 
//		{
//			pos.x += 16 * size;
//			pos.y -= 16 * size;
//		}
//	}
//	win.wait_for_button();
//}
//catch (exception& e) {
//	cerr << "exception: " << e.what() << endl;
//	keep_window_open();
//}
//catch (...) {
//	cerr << "exception\n";
//	keep_window_open();
//}