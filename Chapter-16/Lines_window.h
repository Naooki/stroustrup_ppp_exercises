#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)

using namespace Graph_lib;

struct Lines_window : Window {
	Lines_window(Point xy, int w, int h, const string& title);

	Open_polyline lines;
private:
	Button next_button;
	Button quit_button;
	Button color_menu_button;
	Button style_menu_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;
	Menu color_menu;
	Menu style_menu;

	void next();
	void quit();

	void color_menu_call() { color_menu_button.hide(); style_menu_button.hide(); color_menu.show(); }
	void style_menu_call() { color_menu_button.hide(); style_menu_button.hide(); style_menu.show(); }
	void hide_menu() { color_menu.hide(); style_menu.hide(); color_menu_button.show(); style_menu_button.show(); }

	void turn_red() { change_color(Color::red); hide_menu(); }
	void turn_green() { change_color(Color::green); hide_menu(); }
	void turn_blue() { change_color(Color::blue); hide_menu(); }
	void turn_black() { change_color(Color::black); hide_menu(); }
	void change_color(Color c) { lines.set_color(c); }

	void set_solid() { change_style(Line_style::solid); hide_menu(); }
	void set_dot() { change_style(Line_style::dot); hide_menu(); }
	void set_dash() { change_style(Line_style::dash); hide_menu(); }
	void set_dashdot() { change_style(Line_style::dashdot); hide_menu(); }
	void change_style(Line_style ls) { lines.set_style(ls); }
};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	:Window{ xy,w,h,title },
	next_button{ Point{ x_max() - 150,0}, 70, 20, "Next button", [](Address, Address pw) {reference_to<Lines_window>(pw).next(); } },
	quit_button{ Point{ x_max() - 70, 0}, 70, 20, "Quit", [](Address, Address pw) {reference_to<Lines_window>(pw).quit(); } },
	color_menu_button{ Point{ x_max() - 80,30}, 80, 20, "Color menu", [](Address, Address pw) {reference_to<Lines_window>(pw).color_menu_call(); } },
	style_menu_button{ Point{ x_max() - 80,50 }, 80, 20, "Style menu", [](Address, Address pw) {reference_to<Lines_window>(pw).style_menu_call(); } },
	next_x{ Point{ x_max() - 310, 0 }, 50, 20, "next x:"  },
	next_y{ Point{ x_max() - 210, 0 }, 50, 20, "next y:" },
	xy_out{ Point{ 100, 0 }, 100, 20, "current (x,y):" },
	color_menu{ Point{ x_max() - 70, 30 }, 70, 20, Menu::vertical, "Color" },
	style_menu{ Point{ x_max() - 70, 50 }, 70, 20, Menu::vertical, "Style" }

{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	attach(lines);

	attach(color_menu_button);
	color_menu.attach(new Button{ Point{0,0}, 0, 0, "Red", [](Address, Address pw) {reference_to<Lines_window>(pw).turn_red(); } });
	color_menu.attach(new Button{ Point{ 0,0 }, 0, 0, "Green", [](Address, Address pw) {reference_to<Lines_window>(pw).turn_green(); } });
	color_menu.attach(new Button{ Point{ 0,0 }, 0, 0, "Blue", [](Address, Address pw) {reference_to<Lines_window>(pw).turn_blue(); } });
	color_menu.attach(new Button{ Point{ 0,0 }, 0, 0, "Black", [](Address, Address pw) {reference_to<Lines_window>(pw).turn_black(); } });
	attach(color_menu);
	color_menu.hide();

	attach(style_menu_button);
	style_menu.attach(new Button{ Point{ 0,0 }, 0, 0, "dot", [](Address, Address pw) {reference_to<Lines_window>(pw).set_dot(); } });
	style_menu.attach(new Button{ Point{ 0,0 }, 0, 0, "dash", [](Address, Address pw) {reference_to<Lines_window>(pw).set_dash(); } });
	style_menu.attach(new Button{ Point{ 0,0 }, 0, 0, "dashdot", [](Address, Address pw) {reference_to<Lines_window>(pw).set_dashdot(); } });
	style_menu.attach(new Button{ Point{ 0,0 }, 0, 0, "solid", [](Address, Address pw) {reference_to<Lines_window>(pw).set_solid(); } });
	attach(style_menu);
	style_menu.hide();
}

void Lines_window::next()
{
	int x{ next_x.get_int() };
	int y{ next_y.get_int() };
	lines.add(Point{ x, y });
	stringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());
	redraw();
}

void Lines_window::quit()
{
	hide();
}
