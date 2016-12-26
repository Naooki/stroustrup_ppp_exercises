
#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)

using namespace Graph_lib;

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

struct ShapeMenu_window : Window {
	ShapeMenu_window(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		shapes(Point(x_max() -120, 5), 100, 20, Menu::vertical, "Shapes"),
		shape_x(Point(x_max() - 400, 5), 70, 20,"Shape x:"),
		shape_y(Point(x_max() - 250, 5), 70, 20, "Shape y:")
	{
		shapes.attach(new Button(Point(0, 0), 0, 0, "Circle", [](Address, Address pw) {reference_to<ShapeMenu_window>(pw).draw_circle(); }));
		shapes.attach(new Button(Point(0, 0), 0, 0, "Square", [](Address, Address pw) {reference_to<ShapeMenu_window>(pw).draw_square(); }));
		shapes.attach(new Button(Point(0, 0), 0, 0, "Triangle", [](Address, Address pw) {reference_to<ShapeMenu_window>(pw).draw_equil_triang(); }));
		shapes.attach(new Button(Point(0, 0), 0, 0, "Hexagon", [](Address, Address pw) {reference_to<ShapeMenu_window>(pw).draw_hexagon(); }));

		attach(shapes);
		attach(shape_x);
		attach(shape_y);
	}

	Vector_ref<Shape> drawn_shapes;
private:
	Menu shapes;
	In_box shape_x;
	In_box shape_y;
	
	void draw_circle() {
		drawn_shapes.push_back(new Circle(Point(shape_x.get_int(), shape_y.get_int()), 50));
		attach(drawn_shapes[drawn_shapes.size()-1]);
		redraw();
	};
	void draw_square() {
		drawn_shapes.push_back(new Graph_lib::Rectangle(Point(shape_x.get_int(), shape_y.get_int()), 50, 50));
		attach(drawn_shapes[drawn_shapes.size() - 1]);
		redraw();
	};
	void draw_equil_triang() {
		drawn_shapes.push_back(new Regular_polygon(Point(shape_x.get_int(), shape_y.get_int()), 3, 50));
		attach(drawn_shapes[drawn_shapes.size() - 1]);
		redraw();
	};
	void draw_hexagon() {
		drawn_shapes.push_back(new Regular_polygon(Point(shape_x.get_int(), shape_y.get_int()), 6, 50));
		attach(drawn_shapes[drawn_shapes.size() - 1]);
		redraw();
	};
};
