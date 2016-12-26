#include "Simple_window.h"


int main()
{
	Simple_window win(Point(100, 100), 1000, 600, "ex 6-7");

	vector<double> vals = {14.88, 3.22, 5.56, 5.45};
	Bar_graph bg(Point(100, 100),"MLG", vals, 800);
	bg.set_color(Color::blue);


	/*bg.rects[0].set_fill_color(Color::red);
	bg.labels[0].set_label("\\o");
	bg.rects[1].set_fill_color(Color::blue);
	bg.labels[1].set_label("SOLO");
	bg.rects[2].set_fill_color(Color::green);
	bg.labels[2].set_label("nato");
	bg.rects[3].set_fill_color(Color::yellow);
	bg.labels[3].set_label("russian");*/

	win.attach(bg);


	win.wait_for_button();

}
