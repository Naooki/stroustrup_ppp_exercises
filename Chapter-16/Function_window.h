
#include "GUI.h"

using namespace Graph_lib;


struct Function_window : Window {
	Function_window(Point xy, int w, int h, const string& title);

private:
	Axis ox;
	Axis oy;
	Button draw_button;
	Button funcs_button;
	Menu funcs_menu;

	In_box min_inbox;
	In_box max_inbox;
	In_box pts_num_inbox;
	In_box xscale_inbox;
	In_box yscale_inbox;

	// store function pointer
	Fct* fct_pointer;
	Func flex_function;

	void show_func_menu() { funcs_button.hide(); funcs_menu.show(); }
	void func_pressed(Fct f) { funcs_menu.hide(); funcs_button.show(); fct_pointer = f; }
	void draw_pressed();
	
};

Function_window::Function_window(Point xy, int w, int h, const string& title)
	: Window(xy, w, h, title),
	draw_button(Point(450, 0), 100, 60, "Draw function", [](Address, Address pw) { reference_to<Function_window>(pw).draw_pressed(); }),
	funcs_button(Point(250, 0), 100, 30, "Functions", [](Address, Address pw) { reference_to<Function_window>(pw).show_func_menu(); }),
	funcs_menu(Point(250, 0), 100, 30, Menu::vertical, "Functions"),
	ox(Axis::x, Point(50, y_max() / 2), x_max() - 100, 20, "Axis X"),
	oy(Axis::y, Point(x_max() / 2, y_max() - 50), y_max() - 100, 20, "Axis Y"),
	min_inbox(Point(100, 0), 100, 20, "Min x: "),
	max_inbox(Point(100, 25), 100, 20, "Max x: "),
	pts_num_inbox(Point(100, 50), 100, 20, "Number of pts: "),
	xscale_inbox(Point(100, 75), 100, 20, "X scale: "),
	yscale_inbox(Point(100,100), 100, 20, "Y scale: "),
	flex_function(sqrt, -10, 10, Point(x_max() / 2, y_max() /2))
{
	attach(ox);
	attach(oy);
	attach(draw_button);
	attach(funcs_button);
	attach(funcs_menu);

	attach(min_inbox);
	attach(max_inbox);
	attach(pts_num_inbox);
	attach(xscale_inbox);
	attach(yscale_inbox);

	funcs_menu.attach(new Button(Point(0, 0), 0, 0, "sin", [](Address, Address pw) { reference_to<Function_window>(pw).func_pressed(sin); }));
	funcs_menu.attach(new Button(Point(0, 0), 0, 0, "cos", [](Address, Address pw) { reference_to<Function_window>(pw).func_pressed(cos); }));
	funcs_menu.attach(new Button(Point(0, 0), 0, 0, "log", [](Address, Address pw) { reference_to<Function_window>(pw).func_pressed(log); }));
	funcs_menu.attach(new Button(Point(0, 0), 0, 0, "exp", [](Address, Address pw) { reference_to<Function_window>(pw).func_pressed(exp); }));
	attach(funcs_menu);
	funcs_menu.hide();

	fct_pointer = sqrt;
	flex_function.set_color(Color::invisible);
	attach(flex_function);
}

void Function_window::draw_pressed()
{
	if (min_inbox.get_string() == "" && max_inbox.get_string() == "") return;
	int new_r1 = min_inbox.get_int();
	int new_r2 = max_inbox.get_int();
	if (new_r1 < 0) new_r1 = 0;
	flex_function.set_range(new_r1, new_r2);

	if (pts_num_inbox.get_string() != "") //default = 100
		flex_function.set_points_num(pts_num_inbox.get_int());


	if (xscale_inbox.get_string() != "" && yscale_inbox.get_string() != "")
	{	//default = 25
		int new_xscale = xscale_inbox.get_int();
		int new_yscale = yscale_inbox.get_int();
		flex_function.set_scales(new_xscale, new_yscale);
	}
	flex_function.set_function(fct_pointer);
	flex_function.set_color(Color::red);

	redraw();
}