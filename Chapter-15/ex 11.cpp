#include "Simple_window.h"

void read_data(string filename, vector<double>& data)
{
	ifstream ifs{ filename };
	if (!ifs) error("can't open input file", filename);

	while (ifs)
	{
		char ch;
		ifs >> ch;
		if (isdigit(ch))
		{
			ifs.putback(ch);
			double num;
			ifs >> num;
			ifs >> ch;
			if (ch != ',') error("Wrong data format!");
			ifs >> num;
			data.push_back(num);
		}
	}
}

int main()
{
	vector<double> camb_us;
	read_data("Cambridge(Massachusetts).txt", camb_us);
	vector<double> camb_uk;
	read_data("Cambridge(England).txt", camb_uk);


	Simple_window win{ Point(100,100), 800, 800, "Exercise 11" };

	Axis ax{ Axis::x, Point(100, 750), 600, 60, "Temperature" };
	Axis ay{ Axis::y, Point(400, 750), 700, 30, "Town/month" };
	win.attach(ax);
	win.attach(ay);


	Bar_graph bars_uk{ Point(400,100), "Campridge, England", camb_uk, 300, 20, 4 };
	Bar_graph bars_us{ Point(400,450), "Campridge, Massachusetts", camb_us, 300, 20, 4 };


	for (int i = 0; i < bars_uk.bars_num(); ++i)
	{
		bars_uk.set_bar_color(i, i);
		bars_uk.set_bar_label(i, to_string(camb_uk[i]));
		bars_us.set_bar_color(i, i);
		bars_us.set_bar_label(i, to_string(camb_us[i]));
	}

	win.attach(bars_us);
	win.attach(bars_uk);

	win.wait_for_button();
}