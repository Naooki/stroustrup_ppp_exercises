#include "Simple_window.h"


int main()
try
{
	Simple_window win{ Point{ 50,50 },600,600,"Colour matrix" };

	Vector_ref<Graph_lib::Rectangle> rects;
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			rects.push_back(new Graph_lib::Rectangle{ Point{20 * i,20 * j},20,20 });
			rects[rects.size() - 1].set_fill_color(Color{ i * 16 + j });
			rects[rects.size() - 1].set_color(Color::Transparency::invisible);

			win.attach(rects[rects.size() - 1]);
		}
	}
	win.wait_for_button();
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	keep_window_open();
}
catch (...) {
	cerr << "exception" << endl;
	keep_window_open();
}
