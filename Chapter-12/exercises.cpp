#include "Simple_window.h"
#include <cmath>

void ex_01()  //exercise 01
{
	Simple_window win{ Point{250,250}, 800, 600, "Exercise 1" };

	Graph_lib::Rectangle rect{ Point{50,50}, 200,100 };
	rect.set_color(Color::blue);

	Graph_lib::Polygon poly_rect;
	poly_rect.add(Point{ 300,50 });
	poly_rect.add(Point{ 500,50 });
	poly_rect.add(Point{ 500,150 });
	poly_rect.add(Point{ 300,150 });
	poly_rect.set_color(Color::red);

	win.attach(rect);
	win.attach(poly_rect);

	win.wait_for_button();
}

void ex_02() //exercise 02
{
	Simple_window win{ Point{ 250,250 }, 800, 600, "Exercise 2" };
	Graph_lib::Rectangle rect{ Point{ 100,100 }, 100,30 };

	Text t{ Point{120,120}, "Howdy!" };
	
	win.attach(t);
	win.attach(rect);
	win.wait_for_button();
}

void ex_03() //exercise 03
{
	Simple_window win{ Point{ 250,250 }, 800, 600, "Exercise 3" };

	Text letter_s{ Point{ 350,300 }, "S" };
	letter_s.set_font(Font::times_bold);
	letter_s.set_font_size(150);
	letter_s.set_color(Color::red);
	

	Text letter_e{ Point{ 400,300 }, "E" };
	letter_e.set_font(Font::times_bold);
	letter_e.set_font_size(150);
	letter_e.set_color(Color::white);

	Text letter_a{ Point{ 450,300 }, "A" };
	letter_a.set_font(Font::times_bold);
	letter_a.set_font_size(150);
	letter_a.set_color(Color::blue);

	win.attach(letter_s);
	win.attach(letter_e);
	win.attach(letter_a);

	win.wait_for_button();
}

void ex_04() //exercise 04
{
	Simple_window win{ Point{ 100,100 }, 800, 600, "Exercise 4" };

	//vector<Graph_lib::Rectangle> rects;  // seems like I can't use vector of rectangles (Error code: C2280  File: xmemory0)
	
	Graph_lib::Rectangle rect_0_0{ Point{100,100},100,100 };
	rect_0_0.set_color(Color::white);
	win.attach(rect_0_0);
	Graph_lib::Rectangle rect_0_1{ Point{ 200,100 },100,100 };
	rect_0_1.set_color(Color::red);
	win.attach(rect_0_1);
	Graph_lib::Rectangle rect_0_2{ Point{ 300,100 },100,100 };
	rect_0_2.set_color(Color::white);
	win.attach(rect_0_2);

	Graph_lib::Rectangle rect_1_0{ Point{ 100,200 },100,100 };
	rect_1_0.set_color(Color::red);
	win.attach(rect_1_0);
	Graph_lib::Rectangle rect_1_1{ Point{ 200,200 },100,100 };
	rect_1_1.set_color(Color::white);
	win.attach(rect_1_1);
	Graph_lib::Rectangle rect_1_2{ Point{ 300,200 },100,100 };
	rect_1_2.set_color(Color::red);
	win.attach(rect_1_2);

	Graph_lib::Rectangle rect_2_0{ Point{ 100,300 },100,100 };
	rect_2_0.set_color(Color::white);
	win.attach(rect_2_0);
	Graph_lib::Rectangle rect_2_1{ Point{ 200,300 },100,100 };
	rect_2_1.set_color(Color::red);
	win.attach(rect_2_1);
	Graph_lib::Rectangle rect_2_2{ Point{ 300,300 },100,100 };
	rect_2_2.set_color(Color::white);
	win.attach(rect_2_2);


	win.wait_for_button();
}

void ex_05() //exercise 05
{
	Simple_window win{ Point{ 0,0 }, x_max(), y_max()-30, "Exercise 5" };

	Graph_lib::Rectangle rect{ Point{ 150, 150 }, x_max()*3/4, y_max()*2/3 };
	rect.set_color(Color::red);
	rect.set_style(Line_style(Line_style::solid, 10));

	win.attach(rect);
	win.wait_for_button();
}

void ex_06() //exercise 06
{
	//Simple_window win{ Point{ 200,200 }, 4000, 2500, "Exercise 6" };  //...so shrink to the current resolution (1600x900 in my case)
	Simple_window win{ Point{ 100,100 }, 800, 600, "Exercise 6" };
	Graph_lib::Rectangle rect{ Point{100,100},900,700 };  // it isn't drawn out of window, obviously
	win.attach(rect);
	win.wait_for_button();
}

void ex_07() //exercise 07
{
	Simple_window win{ Point{ 100,100 }, 800, 600, "Exercise 7" };
	Graph_lib::Rectangle walls{ Point{ 300,350 },200,200 };  
	Graph_lib::Rectangle window{ Point{ 325,425 },50,50 };
	Graph_lib::Rectangle door{ Point{ 400,400 },75,150 };
	Graph_lib::Polygon roof;
	roof.add(Point{ 275,350 });
	roof.add(Point{ 400,250 });
	roof.add(Point{ 525,350 });
	win.attach(roof);
	win.attach(walls);
	win.attach(window);
	win.attach(door);

	win.wait_for_button();
}

void ex_08() //exercise 08
{
	Simple_window win{ Point{ 100,100 }, 1000, 600, "Exercise 8" };

	Circle c_blue{ Point{200,200},100 };
	c_blue.set_style(Line_style(Line_style::solid, 14));
	c_blue.set_color(Color::dark_blue);

	Circle c_black{ Point{ 420,200 },100 };
	c_black.set_style(Line_style(Line_style::solid, 14));
	c_black.set_color(Color::black);

	Circle c_red{ Point{ 640,200 },100 };
	c_red.set_style(Line_style(Line_style::solid, 14));
	c_red.set_color(Color::red);

	Circle c_yellow{ Point{ 310,300 },100 };
	c_yellow.set_style(Line_style(Line_style::solid, 14));
	c_yellow.set_color(Color::yellow);

	Circle c_green{ Point{ 530,300 },100 };
	c_green.set_style(Line_style(Line_style::solid, 14));
	c_green.set_color(Color::dark_green);

	win.attach(c_blue);
	win.attach(c_black);
	win.attach(c_red);
	win.attach(c_yellow);
	win.attach(c_green);

	win.wait_for_button();
}

void ex_09() //exercise 09
{
	Simple_window win{ Point{ 150,300 }, 400, 600, "Exercise 9" };
	win.set_label("That feel Pepe");

	Image img{ Point{50,150}, "that_feel_pepe.jpg" };
	win.attach(img);
	Text txt{ Point{75,75}, "That feel Pepe" };
	win.attach(txt);
	win.wait_for_button();
}

void ex_10() //exercise 10
{
	Simple_window win{ Point{ 150,300 }, 800, 600, "Exercise 10" };
	
	Graph_lib::Rectangle fltk1(Point(400, 10), 120, 40);
	fltk1.set_fill_color(Color::yellow);
	win.attach(fltk1);
	Graph_lib::Rectangle fltk2(Point(406, 16), 120, 40);
	fltk2.set_fill_color(Color::yellow);
	win.attach(fltk2);
	Graph_lib::Rectangle fltk3(Point(412, 22), 120, 40);
	fltk3.set_fill_color(Color::yellow);
	win.attach(fltk3);
	Text fltk_txt(Point(418, 42), "FLTK headers");
	win.attach(fltk_txt);

	Graph_lib::Rectangle win_rect(Point(389, 130), 166, 80);
	win_rect.set_fill_color(Color::yellow);
	win.attach(win_rect);
	Text win_txt0(Point(389, 127), "Window.h:");
	win_txt0.set_font(Font::helvetica_bold);
	win.attach(win_txt0);
	Text win_txt1(Point(395, 150), "// window interface:");
	win.attach(win_txt1);
	Text win_txt2(Point(395, 170), "class Window {...};");
	win_txt2.set_font(Font::helvetica_bold);
	win.attach(win_txt2);
	Text win_txt3(Point(395, 190), "...");
	win.attach(win_txt3);

	Open_polyline win_fltk;
	win_fltk.add(Point(472, 130));
	win_fltk.add(Point(472, 62));
	win.attach(win_fltk);
	Graph_lib::Polygon win_fltk_arw;
	win_fltk_arw.add(Point(472, 62));
	win_fltk_arw.add(Point(474, 67));
	win_fltk_arw.add(Point(470, 67));
	win_fltk_arw.set_fill_color(Color::black);
	win.attach(win_fltk_arw);

	// add rest, would be much easier if not everything were passed by reference
	// and would thus stop existing when leaving a scope


	win.wait_for_button();
}



int inner_angle(int n)   // inner angle of N-polygon
{
	return (n - 2) / double(n) * 180;
}

void ex_11() // exercise 11
{
	Simple_window win{ Point{ 300,50 }, 800, 800, "Exercise 10" };

	int side = 300;
	int x0 = 400;
	int y0 = 300;
	double PI{ 3.14159265 };

	Graph_lib::Polygon triangle;
	triangle.add(Point{ x0,y0 });
	triangle.add(Point{ x0-side/2,int(y0 + side*sqrt(3) / 2) });
	triangle.add(Point{ x0+side/2,int(y0 + side*sqrt(3) / 2) });

	Graph_lib::Polygon square;
	square.add(Point{ x0 - side/2,y0 });
	square.add(Point{ x0 + side / 2,y0 });
	square.add(Point{ x0 + side / 2,y0 + side });
	square.add(Point{ x0 - side / 2,y0 + side });

	Graph_lib::Polygon pentagon;
	int penta_angle = inner_angle(5);

	double penta_side = (side / 2) / sin(penta_angle /2 * PI / 180) + side*sin((penta_angle-90)*PI/180) / sin(penta_angle*PI/180);
	double penta_0_x = x0;
	double penta_0_y = y0 - int(side /2 / tan(penta_angle / 2 * PI / 180));
	pentagon.add(Point{int(penta_0_x),int(penta_0_y)});
	double penta_1_x{ penta_0_x + penta_side*sin(penta_angle / 2 * PI / 180) };
	double penta_1_y{ penta_0_y + penta_side*cos(penta_angle / 2 * PI / 180) };
	pentagon.add(Point{ int(penta_1_x),int(penta_1_y) });
	double penta_2_x{ penta_1_x - penta_side*cos((180 - penta_angle) * PI / 180) };
	double penta_2_y{ penta_1_y + penta_side*sin((180 - penta_angle) * PI / 180) };
	pentagon.add(Point{ int(penta_2_x),int(penta_2_y) });
	double penta_3_x{ penta_2_x - penta_side };
	double penta_3_y{ penta_2_y };
	pentagon.add(Point{ int(penta_3_x),int(penta_3_y) });
	double penta_4_x{ penta_0_x - penta_side*sin(penta_angle / 2 * PI / 180) };
	double penta_4_y{ penta_0_y + penta_side*cos(penta_angle / 2 * PI / 180) };
	pentagon.add(Point{ int(penta_4_x),int(penta_4_y) });


	// seems like there is a mistake

	/*Graph_lib::Polygon hexagon;                  
	int hexa_angle = inner_angle(6);
	double hexa_side = penta_side / sin(hexa_angle * PI / 180) * sin((180 - hexa_angle - (hexa_angle - penta_angle) / 2) * PI / 180);
	double hexa_0_x{ penta_0_x };
	double hexa_0_y{ penta_0_y };
	hexagon.add(Point{ int(hexa_0_x),int(hexa_0_y) });
	double hexa_1_x{ hexa_0_x + hexa_side*sin(hexa_angle / 2 * PI / 180) };
	double hexa_1_y{ hexa_0_y + hexa_side*cos(hexa_angle / 2 * PI / 180) };
	hexagon.add(Point{ int(hexa_1_x),int(hexa_1_y) });
	double hexa_2_x{ hexa_1_x };
	double hexa_2_y{ hexa_1_y + hexa_side };
	hexagon.add(Point{ int(hexa_2_x),int(hexa_2_y) });
	double hexa_3_x{ hexa_2_x - hexa_side*sin(hexa_angle / 2 * PI / 180) };
	double hexa_3_y{ hexa_2_y + hexa_side*cos(hexa_angle / 2 * PI / 180) };
	hexagon.add(Point{ int(hexa_3_x),int(hexa_3_y) });
	double hexa_4_x{ hexa_3_x - hexa_side*sin(hexa_angle / 2 * PI / 180) };
	double hexa_4_y{ hexa_3_y - hexa_side*cos(hexa_angle / 2 * PI / 180) };
	hexagon.add(Point{ int(hexa_4_x),int(hexa_4_y) });
	double hexa_5_x{ hexa_0_x - hexa_side*sin(hexa_angle / 2 * PI / 180) };
	double hexa_5_y{ hexa_0_y + hexa_side*cos(hexa_angle / 2 * PI / 180) };
	hexagon.add(Point{ int(hexa_5_x),int(hexa_5_y) });*/


	// it's better but still not perfect, I'll try to fix it later

	Graph_lib::Polygon hexagon;
	int hexa_angle = inner_angle(6);
	double hexa_side = 2 * penta_side / sin(hexa_angle * PI / 180) * sin((180 - hexa_angle - (180 - penta_angle) /2) * PI / 180);
	double hexa_0_x{ penta_0_x + hexa_side / 2 };
	double hexa_0_y{ penta_0_y };
	hexagon.add(Point{ int(hexa_0_x),int(hexa_0_y) });
	double hexa_1_x{ hexa_0_x + hexa_side * cos((180 - hexa_angle) * PI / 180) };
	double hexa_1_y{ hexa_0_y + hexa_side * sin((180 - hexa_angle) * PI / 180) };
	hexagon.add(Point{ int(hexa_1_x),int(hexa_1_y) });
	double hexa_2_x{ hexa_1_x - hexa_side * cos((180 - hexa_angle) * PI / 180) };
	double hexa_2_y{ hexa_1_y + hexa_side * sin((180 - hexa_angle) * PI / 180) };
	hexagon.add(Point{ int(hexa_2_x),int(hexa_2_y) });
	double hexa_3_x{ hexa_2_x - hexa_side };
	double hexa_3_y{ hexa_2_y };
	hexagon.add(Point{ int(hexa_3_x),int(hexa_3_y) });
	double hexa_4_x{ hexa_3_x - hexa_side * cos((180 - hexa_angle) * PI / 180) };
	double hexa_4_y{ hexa_3_y - hexa_side * sin((180 - hexa_angle) * PI / 180) };
	hexagon.add(Point{ int(hexa_4_x),int(hexa_4_y) });
	double hexa_5_x{ penta_0_x - hexa_side / 2 };
	double hexa_5_y{ penta_0_y };
	hexagon.add(Point{ int(hexa_5_x),int(hexa_5_y) });



	win.attach(triangle);
	win.attach(square);
	win.attach(pentagon);
	win.attach(hexagon);
	win.wait_for_button();
}

double sgn(double d)
{
	if (d>0) return 1;
	else if (d<0) return -1;
	else return 0;
}
void ex_12(int a, int b, double m, double n, int N)
{
	const double pi = 3.14159;
	a = 100 * a;    // a = 1 corresponds to -100px to +100px
	b = 100 * b;

	Point tl(300, 25);
	Simple_window win(tl, a * 2 + 20, b * 2 + 20, "Superellipse");


	vector<Point> se_points;
	double se_point_x, se_point_y;
	for (double theta = 0; theta < 2 * pi; theta += (2 * pi / N))
	{
		se_point_x = pow(abs(cos(theta)), 2 / m) * a * sgn(cos(theta)) + a + 10;
		se_point_y = pow(abs(sin(theta)), 2 / n) * b * sgn(sin(theta)) + b + 10;
		se_points.push_back(Point{ int(se_point_x),int(se_point_y) });
	}


	Graph_lib::Closed_polyline se;
	for (Point p : se_points)
		se.add(p);
	

	Graph_lib::Open_polyline lower_lines;
	for (int i = 0; i < se_points.size() / 4; ++i)
	{
		lower_lines.add(se_points[i]);
		for (int j = se_points.size() / 4; j < 2 * se_points.size() / 4; ++j)
		{
			lower_lines.add(se_points[j]);
			lower_lines.add(se_points[i]);
		}
	}
	lower_lines.set_color(Color::cyan);
	win.attach(lower_lines);

	Graph_lib::Open_polyline upper_lines;
	for (int i = 2 * se_points.size() / 4; i <  3 * se_points.size() / 4; ++i)
	{
		upper_lines.add(se_points[i]);
		for (int j = 3 * se_points.size() / 4; j < se_points.size(); ++j)
		{
			upper_lines.add(se_points[j]);
			upper_lines.add(se_points[i]);
		}
	}
	upper_lines.set_color(Color::red);
	win.attach(upper_lines);

	se.set_style(Line_style(Line_style::solid, 4));
	win.attach(se);
	win.wait_for_button();
}

int main()
try
{
	//ex_01();
	//ex_02();
	//ex_03();
	//ex_04();
	//ex_05();
	//ex_06();
	//ex_07();
	//ex_08();
	//ex_09();
	//ex_10();
	//ex_11();
	ex_12(4,4,0.5,0.5,100);
}
catch (exception& e)
{
	cerr << e.what() << endl;
}
catch (...)
{
	cerr << "Exception!" << endl;
}