#include "Simple_window.h"



int main()
{
	string filename = "people_height.txt";
	ifstream ifs{ filename };
	if (!ifs) error("can't open input file", filename);

	vector<int> heights;
	vector<double> numbers;
	int max_number = 0;
	while (ifs)
	{
		char ch;
		ifs >> ch;
		if (isdigit(ch))
		{
			ifs.putback(ch);
			int num;
			ifs >> num;
			heights.push_back(num);
			ifs >> ch;
			if (ch != ',') error("Wrong data format!");
			ifs >> num;
			numbers.push_back(num);
			if (num >= max_number) max_number = num;
		}
	}
	vector<string> labels;
	for (int i =0; i < heights.size(); ++i)
	{
		stringstream ss;
		ss << heights[i];
		labels.push_back(ss.str());
	}

	Simple_window win{ Point(100,100), 800, 600, "Exercise 8" };

	Axis ax{ Axis::x, Point(100, 500), 500, max_number, "Number of people" };
	Axis ay{ Axis::y, Point(100,500), 400, 10, "Height (150-200 cm)" };
	win.attach(ax);
	win.attach(ay);


	Bar_graph bars{ Point(100,0), "", numbers, 500, 30, 0 };

	for (int i = 0; i < bars.bars_num(); ++i)
	{
		bars.set_bar_color(i, i);
		bars.set_bar_label(i, labels[i]);
		bars.move_bar(i, Point(100, 500 - int((double(heights[i]) - 150) / 50 * 400)));
	}

	win.attach(bars);


	win.wait_for_button();
}
