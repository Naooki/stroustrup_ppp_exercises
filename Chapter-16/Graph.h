
#ifndef GRAPH_GUARD
#define GRAPH_GUARD 1

#include "Point.h"
#include<vector>
#include<string>
#include<cmath>
#include "fltk.h"
#include "std_lib_facilities.h"

namespace Graph_lib {
// defense against ill-behaved Linux macros:
#undef major
#undef minor

struct Color {
	enum Color_type {
		red=FL_RED, blue=FL_BLUE, green=FL_GREEN,
		yellow=FL_YELLOW, white=FL_WHITE, black=FL_BLACK,
		magenta=FL_MAGENTA, cyan=FL_CYAN, dark_red=FL_DARK_RED,
		dark_green=FL_DARK_GREEN, dark_yellow=FL_DARK_YELLOW, dark_blue=FL_DARK_BLUE,
		dark_magenta=FL_DARK_MAGENTA, dark_cyan=FL_DARK_CYAN
	};
	enum Transparency { invisible = 0, visible=255 };

	Color(Color_type cc) :c(Fl_Color(cc)), v(visible) { }
	Color(Color_type cc, Transparency vv) :c(Fl_Color(cc)), v(vv) { }
	Color(int cc) :c(Fl_Color(cc)), v(visible) { }
	Color(Transparency vv) :c(Fl_Color()), v(vv) { }

	int as_int() const { return c; }
	char visibility() const { return v; }
	void set_visibility(Transparency vv) { v=vv; }
private:
	unsigned char v;	// 0 or 1 for now
	Fl_Color c;
};

struct Line_style {
	enum Line_style_type {
		solid=FL_SOLID,				// -------
		dash=FL_DASH,				// - - - -
		dot=FL_DOT,					// ....... 
		dashdot=FL_DASHDOT,			// - . - . 
		dashdotdot=FL_DASHDOTDOT,	// -..-..
	};
	Line_style(Line_style_type ss) :s(ss), w(0) { }
	Line_style(Line_style_type lst, int ww) :s(lst), w(ww) { }
	Line_style(int ss) :s(ss), w(0) { }

	int width() const { return w; }
	int style() const { return s; }
private:
	int s;
	int w;
};

class Font {
public:
	enum Font_type {
		helvetica=FL_HELVETICA,
		helvetica_bold=FL_HELVETICA_BOLD,
		helvetica_italic=FL_HELVETICA_ITALIC,
		helvetica_bold_italic=FL_HELVETICA_BOLD_ITALIC,
		courier=FL_COURIER,
  		courier_bold=FL_COURIER_BOLD,
  		courier_italic=FL_COURIER_ITALIC,
  		courier_bold_italic=FL_COURIER_BOLD_ITALIC,
		times=FL_TIMES,
		times_bold=FL_TIMES_BOLD,
		times_italic=FL_TIMES_ITALIC,
		times_bold_italic=FL_TIMES_BOLD_ITALIC,
		symbol=FL_SYMBOL,
		screen=FL_SCREEN,
		screen_bold=FL_SCREEN_BOLD,
		zapf_dingbats=FL_ZAPF_DINGBATS
	};

	Font(Font_type ff) :f(ff) { }
	Font(int ff) :f(ff) { }

	int as_int() const { return f; }
private:
	int f;
};

template<class T> class Vector_ref {
	vector<T*> v;
	vector<T*> owned;
public:
	Vector_ref() {}

	Vector_ref(T* a, T* b=0, T* c=0, T* d=0)
	{
			if (a) push_back(a);
			if (b) push_back(b);
			if (c) push_back(c);
			if (d) push_back(d);
	}

	~Vector_ref() { for (int i=0; i<owned.size(); ++i) delete owned[i]; }

	void push_back(T& s) { v.push_back(&s); }
	void push_back(T* p) { v.push_back(p); owned.push_back(p); }

	// ???void erase(???)

	T& operator[](int i) { return *v[i]; }
	const T& operator[](int i) const { return *v[i]; }
	int size() const { return v.size(); }
};

typedef double Fct(double);

class Shape  {	// deals with color and style, and holds sequence of lines
protected:
	Shape() { }
	Shape(initializer_list<Point> lst);  // add() the Points to this Shape

//	Shape() : lcolor(fl_color()),
//		ls(0),
//		fcolor(Color::invisible) { }
	
	void add(Point p){ points.push_back(p); }
public:
	void draw() const;					// deal with color and draw_lines
	void set_point(int i, Point p) { points[i] = p; }

protected:
	void clear_points() { points.clear(); }
	virtual void draw_lines() const;	// simply draw the appropriate lines
public:
	virtual void move(int dx, int dy);	// move the shape +=dx and +=dy

	void set_color(Color col) { lcolor = col; }
	Color color() const { return lcolor; }

	void set_style(Line_style sty) { ls = sty; }
	Line_style style() const { return ls; }

	void set_fill_color(Color col) { fcolor = col; }
	Color fill_color() const { return fcolor; }

	Point point(int i) const { return points[i]; }
	int number_of_points() const { return int(points.size()); }

	virtual ~Shape() { }
	/*
	struct Window* attached;
	Shape(const Shape& a)
		:attached(a.attached), points(a.points), line_color(a.line_color), ls(a.ls)
	{
		if (a.attached)error("attempt to copy attached shape");
	}
	*/
	Shape(const Shape&) = delete;
	Shape& operator=(const Shape&) = delete;
private:
	vector<Point> points;	// not used by all shapes
	Color lcolor {fl_color()};
	Line_style ls {0};
	Color fcolor {Color::invisible};

//	Shape(const Shape&);
//	Shape& operator=(const Shape&);
};

struct Group : Shape
{
	void add(Shape& s) { shapes.push_back(s); }
	void set_color(Color c);
	void set_fill_color(Color c);
	void move(int dx, int dy);
	void draw_lines() const;
private:
	Vector_ref<Shape> shapes;
};

struct Function : Shape {
	// the function parameters are not stored
	Function(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
	//Function(Point orig, Fct f, double r1, double r2, int count, double xscale = 1, double yscale = 1);	
};

struct Func : Function
{
	Func(Fct fn, double min, double max, Point orig, int pts_num = 100, double xscale = 25, double yscale = 25, double precision = 1);
	void set_function(Fct f);
	void set_range(int min, int max);
	void set_xy(Point orig);
	void set_points_num(int pts_num);
	void set_scales(int xsc, int ysc);
	void restore();
private:
	Fct* f;
	double r1, r2;
	Point xy;
	int count;
	double xsc;
	double ysc;
	double prec;
};

struct Fill {
	Fill() :no_fill(true), fcolor(0)	{ }
	Fill(Color c) :no_fill(false), fcolor(c) { }

	void set_fill_color(Color col) { fcolor = col; }
	Color fill_color() { return fcolor; }
protected:
	bool no_fill;
	Color fcolor;
};


struct Line : Shape {
	Line(Point p1, Point p2) { add(p1); add(p2); }
};

struct Arrow : Line {
	Arrow(Point p1, Point p2) : Line{ p1,p2 } {}
	void draw_lines() const;
};

struct Arc : Shape {
	Arc(Point p, int ww, int hh, double a1, double a2)
		:w{ ww }, h{ hh }, a_first{ a1 }, a_second{a2}
	{
		if (a_first > a_second) error("The first angle can't be bigger than the second angle");
		add(Point{ p.x - w,p.y - h });
	}

	void draw_lines() const;

	Point center() const { return{ point(0).x + w,point(0).y + h }; }

	int width() const { return w; }
	void set_width(int ww) { set_point(0, {center().x - ww, center().y - h}); w = ww; }
	int height() const { return h; }
	void set_height(int hh) { set_point(0, { center().x - w, center().y - hh }); h = hh; }

	void set_angle1(double d)
	{
		if (d > a_second) error("First angle can't be bigger than second angle");
		a_first = d;
	}
	void set_angle2(double d)
	{
		if (d < a_first) error("Second angle can't be smaller than first angle");
		a_second = d;
	}
private:
	int w;
	int h;
	double a_first;
	double a_second;
};

struct Rectangle : Shape {

	Rectangle(Point xy, int ww, int hh) :w{ ww }, h{ hh }
	{
		if (h<=0 || w<=0) error("Bad rectangle: non-positive side");
		add(xy);
	}
	Rectangle(Point x, Point y) :w{ y.x - x.x }, h{ y.y - x.y }
	{
		if (h<=0 || w<=0) error("Bad rectangle: first point is not top left");
		add(x);
	}
	void draw_lines() const;

//	void set_fill_color(Color col) { fcolor = col; }
//	Color fill_color() { return fcolor; }

	int height() const { return h; }
	int width() const { return w; }
private:
	int h;			// height
	int w;			// width
//	Color fcolor;	// fill color; 0 means "no fill"
};
struct Box : Shape {

	Box(Point xy, int ww, int hh, int rr) :w{ ww }, h{ hh }, r{rr}
	{
		if (h <= 0 || w <= 0) error("Bad box: non-positive side");
		if (r > (h < w ? h : w) /2) error("Box corner radius is too large!");
		add(xy);
	}
	Box(Point xy, int ww, int hh) :w{ ww }, h{ hh }, r{ w > h ? int(0.1*h) : int(0.1*w) }
	{
		if (h <= 0 || w <= 0) error("Bad box: non-positive side");
		add(xy);
	}
	Box(Point x, Point y, int rr) :w{ y.x - x.x }, h{ y.y - x.y }, r{rr}
	{
		if (h <= 0 || w <= 0) error("Bad box: first point is not top left");
		if (r >(h < w ? h : w) / 2) error("Box corner radius is too large!");
		add(x);
	}
	void draw_lines() const;

	//  void set_fill_color(Color col);
	//	Color fill_color() { return fcolor; }

	int height() const { return h; }
	int width() const { return w; }
	int radius() const { return r; }
private:
	int h;			// height
	int w;			// width
	int r;			// radius
};




bool intersect(Point p1, Point p2, Point p3, Point p4);


struct Open_polyline : Shape {	// open sequence of lines
	using Shape::Shape;
	void add(Point p) { Shape::add(p); }
	void draw_lines() const;
};

struct Closed_polyline : Open_polyline {	// closed sequence of lines
	using Open_polyline::Open_polyline;
	void draw_lines() const;
	
//	void add(Point p) { Shape::add(p); }
};


struct Polygon : Closed_polyline {	// closed sequence of non-intersecting lines
	using Closed_polyline::Closed_polyline;
	void add(Point p);
	void draw_lines() const;
};

struct Poly : Polygon {
	Poly(vector<Point> pts);
	void add(Point p);
	void draw_lines() const;
};



struct Regular_Hexagon : Shape {
	Regular_Hexagon(Point center, int max_rad);

	void draw_lines() const;
	Point center() const { return point(0); }
	int max_radius() const { return max_r; }
	int min_radius() const { return int(max_r * sqrt(3) / 2); }
private:
	int max_r;
};

constexpr double PI = 3.14159;

struct Regular_polygon : Shape {
	Regular_polygon(Point center, int nn, int max_rad);

	void draw_lines() const;
	Point center() const { return point(0); }
	int max_radius() const { return max_r; }
	int edges_number() const { return n; }
	double inner_ang() const { return inner_angle; }
	double round_ang() const { return round_angle; }

private:
	double inner_angle;
	double round_angle;
	int n;
	int max_r;
};

struct Regular_Octagon : Regular_polygon
{
	Regular_Octagon(Point center, int max_rad)
		:Regular_polygon(center, 8, max_rad) {}
};

struct Star : Regular_polygon {
	Star(Point center, int nn, int max_rad, int m_value);

	void draw_lines() const;
private:
	int inn_rad;
	int m;   // star has 2 important values: n - number of ends, m - connection interval
};



struct Lines : Shape {	// indepentdent lines
	Lines() {}
	//Lines(initializer_list<Point> lst) : Shape{lst} { if (lst.size() % 2) error("odd number of points for Lines"); }
	void draw_lines() const;
	void add(Point p1, Point p2) { Shape::add(p1); Shape::add(p2); }
};

struct Text : Shape {
	// the point is the bottom left of the first letter
	//Text(Point x, const string& s) : lab{ s } { add(x); }
	Text(Point x, const string& s) : lab(s), fnt(fl_font()), fnt_sz(fl_size()) { add(x); }
	void draw_lines() const;

	void set_label(const string& s) { lab = s; }
	string label() const { return lab; }

	void set_font(Font f) { fnt = f; }
	Font font() const { return Font(fnt); }

	void set_font_size(int s) { fnt_sz = s; }
	int font_size() const { return fnt_sz; }
private:
	string lab;	// label
	Font fnt{ fl_font() };
	int fnt_sz{ (14<fl_size()) ? fl_size() : 14 };	// at least 14 point
};

struct TextBox : Box {
	TextBox(Point xy, int ww, string txt)
		:Box(xy, ww, h_tb), label(Point{ xy.x + 4, xy.y + 17 }, txt) {}

	Text label;
	void draw_lines() const;
	void move(int dx, int dy);
	void set_color(Color c);
	//void set_fill_color(Color c);
private:
	static const int h_tb = 24;
};


struct Bar_graph : Shape
{
	Bar_graph(Point xy, string graph_label, vector<double> values, int max_length, int bar_width = 30, int space = 5);
	//void set_label_color(Color c);
	//void set_rect_color(int n, Color c);
	void set_color(Color c);
	void draw_lines() const override;
	void move_bar(int i, Point pos);
	void set_bar_label(int i, string label) { labels[i].set_label(label); }
	void set_bar_color(int i, Color c) { rects[i].set_fill_color(c); }
	int bars_num() const { return rects.size(); }
private:
	Vector_ref<Rectangle> rects;
	Vector_ref<Text> labels;
	Text label;
	int length;
	int sp;
};


struct Axis : Shape {
	// representation left public
	enum Orientation { x, y, z };
	Axis(Orientation d, Point xy, int length, int nummber_of_notches=0, string label = "");

	void draw_lines() const;
	void move(int dx, int dy);

	void set_color(Color c);

	Text label;
	Lines notches;
//	Orientation orin;
//	int notches;
};

struct Circle : Shape {
	Circle(Point p, int rr)	// center and radius
	:r{ rr } {
		add(Point{ p.x - r, p.y - r });
	}

	void draw_lines() const;

	Point center() const { return { point(0).x + r, point(0).y + r }; }

	void set_radius(int rr);
	int radius() const { return r; }
private:
	int r;
};


struct Ellipse : Shape {
	Ellipse(Point p, int ww, int hh)	// center, min, and max distance from center
	:w{ ww }, h{ hh } {
		add(Point{ p.x - ww, p.y - hh });
	}

	void draw_lines() const;

	Point center() const { return{ point(0).x + w, point(0).y + h }; }
	Point focus1() const { return{ center().x + int(sqrt(double(w*w - h*h))), center().y }; }
	Point focus2() const { return{ center().x - int(sqrt(double(w*w - h*h))), center().y }; }
	
	void set_major(int ww) { w=ww; }
	int major() const { return w; }
	void set_minor(int hh) { h=hh; }
	int minor() const { return h; }
private:
	int w;
	int h;
};
/*
struct Mark : Text {
	static const int dw = 4;
	static const int dh = 4;
	Mark(Point xy, char c) : Text(Point(xy.x-dw, xy.y+dh),string(1,c)) {}
};
*/

struct Marked_polyline : Open_polyline {
	Marked_polyline(const string& m) :mark(m) { }
	void draw_lines() const;
private:
	string mark;
};

struct Marks : Marked_polyline {
	Marks(const string& m) :Marked_polyline(m)
	{ set_color(Color(Color::invisible)); }
};

struct Mark : Marks {
	Mark(Point xy, char c) : Marks(string(1,c)) {add(xy); }
};

/*

struct Marks : Shape {
	Marks(char m) : mark(string(1,m)) { }
	void add(Point p) { Shape::add(p); }
	void draw_lines() const;
private:
	string mark;
};
*/

struct Bad_image : Fl_Image {
	Bad_image(int h, int w) : Fl_Image(h,w,0) { }
	void draw(int x,int y, int, int, int, int) { draw_empty(x,y); }
};

struct Suffix {
	enum Encoding { none, jpg, gif, bmp };
};

Suffix::Encoding get_encoding(const string& s);

struct Image : Shape {
	Image(Point xy, string s, Suffix::Encoding e = Suffix::none);
	~Image() { delete p; }
	void draw_lines() const;
	void set_mask(Point xy, int ww, int hh) { w=ww; h=hh; cx=xy.x; cy=xy.y; }
	void move(int dx,int dy) { Shape::move(dx,dy); p->draw(point(0).x,point(0).y); }
private:
	int w,h,cx,cy; // define "masking box" within image relative to position (cx,cy)
	Fl_Image* p;
	Text fn;
};



struct Right_triangle : Shape {
	Right_triangle(Point p, int x_edge, int y_edge, double angle);

	void draw_lines() const;
	Point vertex() const { return point(0); }  //point at right angle
	int edge_x() const { return x; }
	int edge_y() const { return y; }

	void rotate(double dphi); //rotate triangle xlockwise by dphi (in degrees)
private:
	int x;	//edge of triangle along the X axis
	int y;	//edge of triangle along the Y axis
	double phi;	//angle (in degrees) by which angle is rotated
};

Point n(const Rectangle& r);
Point s(const Rectangle& r);
Point e(const Rectangle& r);
Point w(const Rectangle& r);
Point center(const Rectangle& r);
Point ne(const Rectangle& r);
Point se(const Rectangle& r);
Point nw(const Rectangle& r);
Point sw(const Rectangle& r);

Point n(const Circle& c);
Point s(const Circle& c);
Point e(const Circle& c);
Point w(const Circle& c);
Point center(const Circle& c);
Point ne(const Circle& c);
Point se(const Circle& c);
Point nw(const Circle& c);
Point sw(const Circle& c);

Point n(const Ellipse& e);
Point s(const Ellipse& e);
Point e(const Ellipse& e);
Point w(const Ellipse& e);
Point center(const Ellipse& e);
Point ne(const Ellipse& e);
Point se(const Ellipse& e);
Point nw(const Ellipse& e);
Point sw(const Ellipse& e);

Point n(const Box& box);
Point s(const Box& box);
Point e(const Box& box);
Point w(const Box& box);
Point center(const Box& box);
Point ne(const Box& box);
Point se(const Box& box);
Point nw(const Box& box);
Point sw(const Box& box);



struct Circle_face : Circle
{
	void move(int dx, int dy);
	void set_color(Color c);
	void set_style(Line_style ls);
	void set_radius(int rr);

protected:
	Circle_face(Point p, int radius);
	Arc mouth;
	void draw_lines() const;

private:
	Ellipse left_eye;
	Ellipse right_eye;
};

struct Smiley : Circle_face
{
	Smiley(Point p, int radius);
};
struct Hat_smiley : Smiley
{
	Hat_smiley(Point p, int radius);
	void move(int dx, int dy);
	void set_color(Color c);
protected:
	void draw_lines() const;
private:
	Polygon hat;
};


struct Frowny : Circle_face
{
	Frowny(Point p, int radius);
};
struct Hat_frowny : Frowny
{
	Hat_frowny(Point p, int radius);
	void move(int dx, int dy);
	void set_color(Color c);
protected:
	void draw_lines() const;
private:
	Polygon cap;
};


struct Immobile_circle : Circle
{
	Immobile_circle(Point p, int radius)
		:Circle(p, radius) {}
private:
	Circle::move;     //why not Circle::move(int dx, int dy) ???
};

struct Striped_rectangle : Rectangle
{
	Striped_rectangle(Point p1, Point p2)
		:Rectangle(p1, p2) {}
	Striped_rectangle(Point p, int w, int h)
		:Rectangle(p, w, h) {}
	
	void draw_lines() const;
};
struct Striped_circle : Circle
{
	Striped_circle(Point p, int radius)
		:Circle(p, radius) {}

	void draw_lines() const;
};

struct Striped_closed_polyline : Closed_polyline
{
	void draw_lines() const;
};

struct Pseudo_window : Box
{
	Pseudo_window(Point xy, int ww, int hh, string label);

	void draw_lines() const;
	//void move(int dx, int dy);

private:
	Text win_name;

	Box ctrl1;
	Box ctrl2;
	Box ctrl3;

	Lines x;
	Rectangle bg;
	Image content;
};


struct Binary_tree : Shape
{
	//edge style: "ad" - arrows down; "au" - arrows up; else - normal;
	Binary_tree(Point xy, int levels_number, string edge_style);

	void draw_lines() const override;
	void set_node_label(const string& path);
protected:
	Vector_ref<Shape> edges;
	Vector_ref<Text> labels;
private:
	int levels;
};

struct Star_nodes_B_tree : Binary_tree
{
	Star_nodes_B_tree(Point xy, int levels_number, string edge_style)
		:Binary_tree(xy, levels_number, edge_style) {}

	void draw_lines() const override;
private:
	int levels;
};


struct Clock : Circle {
	Clock(Point xy, int rr);
	void draw_lines() const override;
	void increase_time();
	Point center() const { return Circle::center(); }
	int radius() const { return Circle::radius(); }
	Vector_ref<Line> hands;
private:
	void update();
	Lines ticks;
	int hh;
	int mm;
	int ss;
};


}
#endif

