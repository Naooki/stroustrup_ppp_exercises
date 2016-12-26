#include "Simple_window.h"


int main()
try
{
	Simple_window win{ Point{ 50,50 },800,800,"Stars" };


	int cell_x = 200;
	int cell_y = 200;
	Vector_ref<Star> stars;
	int n, m;
	for (int i = 0; i <= win.x_max(); i += cell_x)
	{
		for (int j = 0; j <= win.y_max(); j += cell_y)
		{
			n = randint(4, 10);
			m = n / 2 - 1;
			stars.push_back(new Star{ Point{i,j}, n, 100, m });
			stars[stars.size() - 1].set_fill_color(randint(255));
			stars[stars.size() - 1].set_color(randint(255));
			win.attach(stars[stars.size() - 1]);
		}
	}
	Graph_lib::Rectangle my_rect{ Point{400,400}, 200,100 };
	my_rect.set_fill_color(Color::green);
	win.attach(my_rect);

	
	Star my_star{ Point{400,400},5,200,2 };

	my_star.set_style(Line_style(Line_style::solid, 6));
	win.attach(my_star);

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