#include "Graph.h"
#include<map>

namespace Graph_lib {

	void Shape::draw_lines() const
	{
		if (color().visibility() && 1 < points.size())	// draw sole pixel?
			for (unsigned int i = 1; i < points.size(); ++i)
				fl_line(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
	}

	void Shape::draw() const
	{
		Fl_Color oldc = fl_color();
		// there is no good portable way of retrieving the current style
		fl_color(lcolor.as_int());
		fl_line_style(ls.style(), ls.width());
		draw_lines();
		fl_color(oldc);	// reset color (to pevious) and style (to default)
		fl_line_style(0);
	}


	// does two lines (p1,p2) and (p3,p4) intersect?
	// if se return the distance of the intersect point as distances from p1
	inline pair<double, double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel)
	{
		double x1 = p1.x;
		double x2 = p2.x;
		double x3 = p3.x;
		double x4 = p4.x;
		double y1 = p1.y;
		double y2 = p2.y;
		double y3 = p3.y;
		double y4 = p4.y;

		double denom = ((y4 - y3)*(x2 - x1) - (x4 - x3)*(y2 - y1));
		if (denom == 0) {
			parallel = true;
			return pair<double, double>(0, 0);
		}
		parallel = false;
		return pair<double, double>(((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3)) / denom,
			((x2 - x1)*(y1 - y3) - (y2 - y1)*(x1 - x3)) / denom);
	}


	//intersection between two line segments
	//Returns true if the two segments intersect,
	//in which case intersection is set to the point of intersection
	bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection) {
		bool parallel;
		pair<double, double> u = line_intersect(p1, p2, p3, p4, parallel);
		if (parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1) return false;
		intersection.x = p1.x + u.first*(p2.x - p1.x);
		intersection.y = p1.y + u.first*(p2.y - p1.y);
		return true;
	}

	void Polygon::add(Point p)
	{
		int np = number_of_points();

		if (1 < np) {	// check that thenew line isn't parallel to the previous one
			if (p == point(np - 1)) error("polygon point equal to previous point");
			bool parallel;
			line_intersect(point(np - 1), p, point(np - 2), point(np - 1), parallel);
			if (parallel)
				error("two polygon points lie in a straight line");
		}

		for (int i = 1; i < np - 1; ++i) {	// check that new segment doesn't interset and old point
			Point ignore(0, 0);
			if (line_segment_intersect(point(np - 1), p, point(i - 1), point(i), ignore))
				error("intersect in polygon");
		}


		Closed_polyline::add(p);
	}


	void Polygon::draw_lines() const
	{
		if (number_of_points() < 3) error("less than 3 points in a Polygon");
		Closed_polyline::draw_lines();
	}

	void Open_polyline::draw_lines() const
	{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for (int i = 0; i < number_of_points(); ++i) {
				fl_vertex(point(i).x, point(i).y);
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility())
			Shape::draw_lines();
	}


	//   Poly ----------------------------
	Poly::Poly(vector<Point> pts)
	{
		for (Point p : pts)
			add(p);
	}
	void Poly::add(Point p)
	{
		Polygon::add(p);
	}
	void Poly::draw_lines() const
	{
		Polygon::draw_lines();
	}
	//------------------------------------


	void Closed_polyline::draw_lines() const
	{
		Open_polyline::draw_lines();

		if (color().visibility())	// draw closing line:
			fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y, point(0).x, point(0).y);
	}
	void Shape::move(int dx, int dy)
	{
		for (unsigned int i = 0; i < points.size(); ++i) {
			points[i].x += dx;
			points[i].y += dy;
		}
	}

	void Lines::draw_lines() const
	{
		//	if (number_of_points()%2==1) error("odd number of points in set of lines");
		if (color().visibility())
			for (int i = 1; i < number_of_points(); i += 2)
				fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);
	}

	void Text::draw_lines() const
	{
		int ofnt = fl_font();
		int osz = fl_size();
		fl_font(fnt.as_int(), fnt_sz);
		fl_draw(lab.c_str(), point(0).x, point(0).y);
		fl_font(ofnt, osz);
	}

	Function::Function(Fct f, double r1, double r2, Point xy, int count, double xscale, double yscale)
		// graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
		// x coordinates are scaled by xscale and y coordinates scaled by yscale
	{
		if (r2 - r1 <= 0) error("bad graphing range");
		if (count <= 0) error("non-positive graphing count");
		double dist = (r2 - r1) / count;
		double r = r1;
		for (int i = 0; i < count; ++i) {
			add(Point(xy.x + int(r*xscale), xy.y - int(f(r)*yscale)));
			r += dist;
		}
	}

	void Rectangle::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			fl_rectf(point(0).x, point(0).y, w, h);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {	// edge on top of fill
			fl_color(color().as_int());
			fl_rect(point(0).x, point(0).y, w, h);
		}
	}
	void Box::draw_lines() const
	{

		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());

			//lines
			fl_line(point(0).x + r, point(0).y, point(0).x + w - r, point(0).y);
			fl_line(point(0).x + r, point(0).y + h, point(0).x + w - r, point(0).y + h);
			fl_line(point(0).x, point(0).y + r, point(0).x, point(0).y + h - r);
			fl_line(point(0).x + w, point(0).y + r, point(0).x + w, point(0).y + h - r);
			//arcs
			fl_arc(point(0).x, point(0).y, r + r, r + r, 90, 180);
			fl_arc(point(0).x + w - 2 * r, point(0).y, r + r, r + r, 0, 90);
			fl_arc(point(0).x, point(0).y + h - 2 * r, r + r, r + r, 180, 270);
			fl_arc(point(0).x + w - 2 * r, point(0).y + h - 2 * r, r + r, r + r, 270, 360);

			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {
			fl_color(color().as_int());
			//lines
			fl_line(point(0).x + r, point(0).y, point(0).x + w - r, point(0).y);
			fl_line(point(0).x + r, point(0).y + h, point(0).x + w - r, point(0).y + h);
			fl_line(point(0).x, point(0).y + r, point(0).x, point(0).y + h - r);
			fl_line(point(0).x + w, point(0).y + r, point(0).x + w, point(0).y + h - r);
			//arcs
			fl_arc(point(0).x, point(0).y, r + r, r + r, 90, 180);
			fl_arc(point(0).x + w - 2 * r, point(0).y, r + r, r + r, 0, 90);
			fl_arc(point(0).x, point(0).y + h - 2 * r, r + r, r + r, 180, 270);
			fl_arc(point(0).x + w - 2 * r, point(0).y + h - 2 * r, r + r, r + r, 270, 360);
		}
	}


	void TextBox::draw_lines() const
	{
		Box::draw_lines();
		label.draw();
	}
	void TextBox::move(int dx, int dy)
	{
		Box::move(dx, dy);
		label.move(dx, dy);
	}
	void TextBox::set_color(Color c)
	{
		Box::set_color(c);
		label.set_color(c);
	}


	void Arrow::draw_lines() const
	{
		Line::draw_lines();

		//find arrow length:
		double arrow_len = sqrt(pow(point(0).x - point(1).x, 2) + pow(point(0).y - point(1).y, 2));
		int ah_length = 10;
		int ah_width = 6;

		//point where arrowhead begins  
		double ah_p_x = point(1).x - (ah_length / arrow_len*(point(1).x - point(0).x));
		double ah_p_y = point(1).y + (ah_length / arrow_len*(point(0).y - point(1).y));
		//arrowhead "left" point
		double ah_pl_x = ah_p_x - (ah_width / 2)*(point(0).y - point(1).y) / arrow_len;
		double ah_pl_y = ah_p_y - (ah_width / 2)*(point(1).x - point(0).x) / arrow_len;
		//arrowhead "left" point
		double ah_pr_x = ah_p_x + (ah_width / 2)*(point(0).y - point(1).y) / arrow_len;
		double ah_pr_y = ah_p_y + (ah_width / 2)*(point(1).x - point(0).x) / arrow_len;

		if (color().visibility()) {
			fl_color(color().as_int());

			Polygon arrowhead;
			arrowhead.add({ Point{ int(ah_pl_x),int(ah_pl_y) } });
			arrowhead.add(point(1));
			arrowhead.add({ Point{ int(ah_pr_x),int(ah_pr_y) } });
			arrowhead.set_fill_color(Color::black);
			arrowhead.draw_lines();
		}
	}



	Axis::Axis(Orientation d, Point xy, int length, int n, string lab)
		:label(Point(0, 0), lab)
	{
		if (length < 0) error("bad axis length");
		switch (d) {
		case Axis::x:
		{	Shape::add(xy);	// axis line
		Shape::add(Point(xy.x + length, xy.y));	// axis line
		if (1 < n) {
			int dist = length / n;
			int x = xy.x + dist;
			for (int i = 0; i < n; ++i) {
				notches.add(Point(x, xy.y), Point(x, xy.y - 5));
				x += dist;
			}
		}
		// label under the line
		label.move(length / 3, xy.y + 20);
		break;
		}
		case Axis::y:
		{	Shape::add(xy);	// a y-axis goes up
		Shape::add(Point(xy.x, xy.y - length));
		if (1 < n) {
			int dist = length / n;
			int y = xy.y - dist;
			for (int i = 0; i < n; ++i) {
				notches.add(Point(xy.x, y), Point(xy.x + 5, y));
				y -= dist;
			}
		}
		// label at top
		label.move(xy.x - 10, xy.y - length - 10);
		break;
		}
		case Axis::z:
			error("z axis not implemented");
		}
	}

	void Axis::draw_lines() const
	{
		Shape::draw_lines();	// the line
		notches.draw();	// the notches may have a different color from the line
		label.draw();	// the label may have a different color from the line
	}


	void Axis::set_color(Color c)
	{
		Shape::set_color(c);
		notches.set_color(c);
		label.set_color(c);
	}

	void Axis::move(int dx, int dy)
	{
		Shape::move(dx, dy);
		notches.move(dx, dy);
		label.move(dx, dy);
	}


	void Arc::draw_lines() const
	{
		if (color().visibility()) {
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, w + w, h + h, a_first, a_second);
		}
	}
	void Circle::set_radius(int rr)
	{
		r = rr;
	}
	void Circle::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, r + r - 1, r + r - 1, 0, 360);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);
		}
	}


	void Ellipse::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, w + w - 1, h + h - 1, 0, 360);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, w + w, h + h, 0, 360);
		}
	}

	void draw_mark(Point xy, char c)
	{
		static const int dx = 4;
		static const int dy = 4;
		string m(1, c);
		fl_draw(m.c_str(), xy.x - dx, xy.y + dy);
	}

	void Marked_polyline::draw_lines() const
	{
		Open_polyline::draw_lines();
		for (int i = 0; i < number_of_points(); ++i)
			draw_mark(point(i), mark[i%mark.size()]);
	}
	/*
	void Marks::draw_lines() const
	{
		for (int i=0; i<number_of_points(); ++i)
			fl_draw(mark.c_str(),point(i).x-4,point(i).y+4);
	}
	*/


	std::map<string, Suffix::Encoding> suffix_map;

	int init_suffix_map()
	{
		suffix_map["jpg"] = Suffix::jpg;
		suffix_map["JPG"] = Suffix::jpg;
		suffix_map["jpeg"] = Suffix::jpg;
		suffix_map["JPEG"] = Suffix::jpg;
		suffix_map["gif"] = Suffix::gif;
		suffix_map["GIF"] = Suffix::gif;
		suffix_map["bmp"] = Suffix::bmp;
		suffix_map["BMP"] = Suffix::bmp;
		return 0;
	}

	Suffix::Encoding get_encoding(const string& s)
		// try to deduce type from file name using a lookup table
	{
		static int x = init_suffix_map();

		string::const_iterator p = find(s.begin(), s.end(), '.');
		if (p == s.end()) return Suffix::none;	// no suffix

		string suf(p + 1, s.end());
		return suffix_map[suf];
	}

	bool can_open(const string& s)
		// check if a file named s exists and can be opened for reading
	{
		ifstream ff(s.c_str());
		return bool(ff);
	}


	// somewhat overelaborate constructor
	// because errors related to image files can be such a pain to debug
	Image::Image(Point xy, string s, Suffix::Encoding e)
		:w(0), h(0), fn(xy, "")
	{
		add(xy);

		if (!can_open(s)) {
			fn.set_label("cannot open \"" + s + '\"');
			p = new Bad_image(30, 20);	// the "error image"
			return;
		}

		if (e == Suffix::none) e = get_encoding(s);

		switch (e) {
		case Suffix::jpg:
			p = new Fl_JPEG_Image(s.c_str());
			break;
		case Suffix::gif:
			p = new Fl_GIF_Image(s.c_str());
			break;
			//	case Suffix::bmp:
			//		p = new Fl_BMP_Image(s.c_str());
			//		break;
		default:	// Unsupported image encoding
			fn.set_label("unsupported file type \"" + s + '\"');
			p = new Bad_image(30, 20);	// the "error image"
		}
	}

	void Image::draw_lines() const
	{
		if (fn.label() != "") fn.draw_lines();

		if (w&&h)
			p->draw(point(0).x, point(0).y, w, h, cx, cy);
		else
			p->draw(point(0).x, point(0).y);
	}

	Point Graph_lib::n(const Rectangle& r)
	{
		return Point{ r.point(0).x + r.width() / 2, r.point(0).y };
	}
	Point Graph_lib::s(const Rectangle& r)
	{
		return Point{ r.point(0).x + r.width() / 2, r.point(0).y + r.height() };
	}
	Point Graph_lib::e(const Rectangle& r)
	{
		return Point{ r.point(0).x + r.width(), r.point(0).y + r.height() / 2 };
	}
	Point Graph_lib::w(const Rectangle& r)
	{
		return Point{ r.point(0).x, r.point(0).y + r.height() / 2 };
	}
	Point Graph_lib::center(const Rectangle& r)
	{
		return Point{ r.point(0).x + r.width() / 2, r.point(0).y + r.width() / 2 };
	}
	Point Graph_lib::ne(const Rectangle& r)
	{
		return Point{ r.point(0).x + r.width(), r.point(0).y };
	}
	Point Graph_lib::se(const Rectangle& r)
	{
		return Point{ r.point(0).x + r.width(), r.point(0).y + r.height() };
	}
	Point Graph_lib::nw(const Rectangle& r)
	{
		return Point{ r.point(0).x, r.point(0).y };
	}
	Point Graph_lib::sw(const Rectangle& r)
	{
		return Point{ r.point(0).x, r.point(0).y + r.height() };
	}



	Point Graph_lib::n(const Circle& c)
	{
		return Point{ c.center().x, c.center().y - c.radius() };
	}
	Point Graph_lib::s(const Circle& c)
	{
		return Point{ c.center().x, c.center().y + c.radius() };
	}
	Point Graph_lib::e(const Circle& c)
	{
		return Point{ c.center().x + c.radius(), c.center().y };
	}
	Point Graph_lib::w(const Circle& c)
	{
		return Point{ c.center().x - c.radius(), c.center().y };
	}
	Point Graph_lib::center(const Circle& c)
	{
		return Point{ c.center() };
	}
	Point Graph_lib::ne(const Circle& c)
	{
		return Point{ c.center().x + int(c.radius() * sqrt(2) / 2), c.center().y - int(c.radius() * sqrt(2) / 2) };
	}
	Point Graph_lib::se(const Circle& c)
	{
		return Point{ c.center().x + int(c.radius() * sqrt(2) / 2), c.center().y + int(c.radius() * sqrt(2) / 2) };
	}
	Point Graph_lib::nw(const Circle& c)
	{
		return Point{ c.center().x - int(c.radius() * sqrt(2) / 2), c.center().y - int(c.radius() * sqrt(2) / 2) };
	}
	Point Graph_lib::sw(const Circle& c)
	{
		return Point{ c.center().x - int(c.radius() * sqrt(2) / 2), c.center().y + int(c.radius() * sqrt(2) / 2) };
	}



	Point Graph_lib::n(const Ellipse& e)
	{
		return Point{ e.center().x, e.center().y - e.minor() };
	}
	Point Graph_lib::s(const Ellipse& e)
	{
		return Point{ e.center().x, e.center().y + e.minor() };
	}
	Point Graph_lib::e(const Ellipse& e)
	{
		return Point{ e.center().x + e.major(), e.center().y };
	}
	Point Graph_lib::w(const Ellipse& e)
	{
		return Point{ e.center().x - e.major(), e.center().y };
	}
	Point Graph_lib::center(const Ellipse& e)
	{
		return Point{ e.center() };
	}
	Point Graph_lib::ne(const Ellipse& e)
	{
		return Point{ e.center().x + int(e.major() * sqrt(2) / 2), e.center().y - int(e.minor() * sqrt(2) / 2) };
	}
	Point Graph_lib::se(const Ellipse& e)
	{
		return Point{ e.center().x + int(e.major() * sqrt(2) / 2), e.center().y + int(e.minor() * sqrt(2) / 2) };
	}
	Point Graph_lib::nw(const Ellipse& e)
	{
		return Point{ e.center().x - int(e.major() * sqrt(2) / 2), e.center().y - int(e.minor() * sqrt(2) / 2) };
	}
	Point Graph_lib::sw(const Ellipse& e)
	{
		return Point{ e.center().x - int(e.major() * sqrt(2) / 2), e.center().y + int(e.minor() * sqrt(2) / 2) };
	}




	Point n(const Box& box)
	{
		return Point{ box.point(0).x + box.width() / 2, box.point(0).y };
	}
	Point s(const Box& box)
	{
		return Point{ box.point(0).x + box.width() / 2, box.point(0).y + box.height() };
	}
	Point e(const Box& box)
	{
		return Point{ box.point(0).x + box.width(), box.point(0).y + box.height() / 2 };
	}
	Point w(const Box& box)
	{
		return Point{ box.point(0).x, box.point(0).y + box.height() / 2 };
	}
	Point center(const Box& box)
	{
		return Point{ box.point(0).x + box.width() / 2, box.point(0).y + box.height() / 2 };
	}
	Point ne(const Box& box)
	{
		return Point{ box.point(0).x + box.width() - box.radius() + int(box.radius() * sqrt(2) / 2), box.point(0).y + box.radius() - int(box.radius()*sqrt(2) / 2) };
	}
	Point se(const Box& box)
	{
		return Point{ box.point(0).x + box.width() - box.radius() + int(box.radius() * sqrt(2) / 2), box.point(0).y + box.height() - box.radius() + int(box.radius()*sqrt(2) / 2) };
	}
	Point nw(const Box& box)
	{
		return Point{ box.point(0).x + box.radius() - int(box.radius() * sqrt(2) / 2), box.point(0).y + box.radius() - int(box.radius()*sqrt(2) / 2) };
	}
	Point sw(const Box& box)
	{
		return Point{ box.point(0).x + box.radius() - int(box.radius() * sqrt(2) / 2), box.point(0).y + box.height() - box.radius() + int(box.radius()*sqrt(2) / 2) };
	}

	Regular_Hexagon::Regular_Hexagon(Point center, int max_rad)
		:Shape::Shape(), max_r{ max_rad }
	{
		Shape::add(center);
		if (max_r <= 0) error("Max radius can't be smaller than 0");
	}

	void Regular_Hexagon::draw_lines() const
	{
		fl_line(point(0).x - max_r / 2, point(0).y - min_radius(), point(0).x + max_r / 2, point(0).y - min_radius());
		fl_line(point(0).x + max_r / 2, point(0).y - min_radius(), point(0).x + max_r, point(0).y);
		fl_line(point(0).x + max_r, point(0).y, point(0).x + max_r / 2, point(0).y + min_radius());
		fl_line(point(0).x + max_r / 2, point(0).y + min_radius(), point(0).x - max_r / 2, point(0).y + min_radius());
		fl_line(point(0).x - max_r / 2, point(0).y + min_radius(), point(0).x - max_r, point(0).y);
		fl_line(point(0).x - max_r, point(0).y, point(0).x - max_r / 2, point(0).y - min_radius());
	}

	Regular_polygon::Regular_polygon(Point center, int nn, int max_rad)
		:Shape::Shape(), n{nn}, max_r{ max_rad }
	{
		if (n < 3) error("Polgon should have at least 3 sides");
		inner_angle = double(n - 2) / n * 180;
		round_angle = 360 / double(n);
		if (max_r <= 0) error("Max radius can't be smaller than 0");
		Shape::add(center);
	}

	void Regular_polygon::draw_lines() const
	{

		/*vector<Point> pts;
		for (int i = 0; i < n; ++i)
		{
			pts.push_back(Point{ point(0).x + int(max_r*cos(i * round_angle * PI / 180)),point(0).y + int(max_r*sin(i * round_angle * PI / 180)) });
		}*/
		Polygon poly;
		for (int i = 0; i < n; ++i)
			poly.add(Point{ point(0).x + int(max_r*cos(i * round_angle * PI / 180)),point(0).y + int(max_r*sin(i * round_angle * PI / 180)) });
		if (fill_color().visibility())
		{
			poly.set_fill_color(fill_color().as_int());
		}
		if (color().visibility())
		{
			poly.set_color(color().as_int());
		}
		poly.draw_lines();
	}
	Star::Star(Point center, int nn, int max_rad, int m_value)
		:Regular_polygon(center, 2 * nn, max_rad) 
	{
		if (nn < m_value * 2 + 1) error("Invalid n/m correlation!");
		m = m_value;
		inn_rad = max_rad * (cos(PI / nn * m_value) / cos(PI / nn * (m_value - 1)));
	}
	
	void Star::draw_lines() const
	{
		vector<Point> pts;
		if(fill_color().visibility())
		{
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for (int i = 0; i < edges_number(); ++i)
			{
				if (i % 2 == 0)
				{
					pts.push_back(Point{ point(0).x + int(max_radius()*cos((i * round_ang() - 90) * PI / 180)),point(0).y + int(max_radius()*sin((i * round_ang() - 90) * PI / 180)) });
					fl_vertex(pts[pts.size() - 1].x, pts[pts.size() - 1].y);
				}
				else
				{
					pts.push_back(Point{ point(0).x + int(inn_rad*cos((i * round_ang() - 90) * PI / 180)),point(0).y + int(inn_rad*sin((i * round_ang() - 90) * PI / 180)) });
					fl_vertex(pts[pts.size() - 1].x, pts[pts.size() - 1].y);
				}
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());
		}
		if (color().visibility())
		{
			for (int i = 0; i < edges_number(); ++i)
			{
				if (i % 2 == 0)
				{
					pts.push_back(Point{ point(0).x + int(max_radius()*cos((i * round_ang() - 90) * PI / 180)),point(0).y + int(max_radius()*sin((i * round_ang() - 90) * PI / 180)) });
				}
				else
				{
					pts.push_back(Point{ point(0).x + int(inn_rad*cos((i * round_ang() - 90) * PI / 180)),point(0).y + int(inn_rad*sin((i * round_ang() - 90) * PI / 180)) });
				}
			}
			for (int i = 0; i < pts.size()-1; ++i)
			{
				fl_line(pts[i].x, pts[i].y, pts[i + 1].x, pts[i + 1].y);
			}
			fl_line(pts[pts.size()-1].x, pts[pts.size()-1].y, pts[0].x, pts[0].y);

		}	
	}


	Right_triangle::Right_triangle(Point p, int x_edge, int y_edge, double angle)
		:x{ x_edge }, y{ y_edge }, phi{ angle }
	{
		add(p);	//point at right angle
		add(Point{ vertex().x + int(x*cos(phi * PI / 180)), vertex().y - int(x*sin(phi * PI / 180)) });
		add(Point{ vertex().x + int(y*cos((phi+90) * PI / 180)), vertex().y - int(y*sin((phi+90) * PI / 180)) });
	}

	void Right_triangle::draw_lines() const
	{

		if (fill_color().visibility())
		{
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for (int i = 0; i < number_of_points(); ++i)
				fl_vertex(point(i).x, point(i).y);
			fl_end_complex_polygon();
			fl_color(color().as_int());
		}

		Shape::draw_lines();
		if (color().visibility())
			fl_line(point(2).x, point(2).y, point(0).x, point(0).y);
	}

	Circle_face::Circle_face(Point p, int radius)
		:Circle{ p,radius },
		left_eye{ Point(p.x - radius / 5, p.y - radius / 5), radius / 8, radius / 3 },
		right_eye{ Point(p.x + radius / 5, p.y - radius / 5), radius / 8, radius / 3 },
		mouth{ p, radius*0.66, radius*0.066, 180, 360 } {}
	

	void Circle_face::draw_lines() const
	{
		if (color().visibility())
		{
			Circle::draw_lines();
			left_eye.draw();
			right_eye.draw();
			mouth.draw();
		}
	}
	void Circle_face::move(int dx, int dy)
	{
		Circle::move(dx, dy);
		left_eye.move(dx, dy);
		right_eye.move(dx, dy);
		mouth.move(dx, dy);
	}
	void Circle_face::set_color(Color c)
	{
		mouth.set_color(c);
		Circle::set_color(c);
		right_eye.set_fill_color(c);
		left_eye.set_fill_color(c);
	}
	void Circle_face::set_style(Line_style ls)
	{
		Circle::set_style(ls);
		mouth.set_style(ls);
		left_eye.set_style(ls);
		right_eye.set_style(ls);
	}
	void Circle_face::set_radius(int rr)
	{
		int old_r = radius();
		Circle::set_radius(rr);
		left_eye.set_minor(rr / 3);
		left_eye.set_major(rr / 8);
		right_eye.set_minor(rr / 3);
		right_eye.set_major(rr / 8);

		// move eyes and mouth
		left_eye.move((old_r - rr) / 5 + (rr-old_r), (old_r - rr) / 5);
		right_eye.move((rr - old_r) / 5 + (rr-old_r), (old_r - rr) / 5);
		mouth.move((rr - old_r), (rr - old_r));
		// scale mouth
		mouth.set_height(rr*0.066);
		mouth.set_width(rr*0.66);
	}




	Smiley::Smiley(Point p, int radius)
		:Circle_face(p, radius) 
	{
		mouth.move(0, radius*0.66);
	}
	Hat_smiley::Hat_smiley(Point p, int radius)
		: Smiley(p, radius)
	{
		Point sp{ Circle::center().x, center().y - int(radius*0.8) };
		hat.add(sp);
		hat.add({ sp.x - int(1.2*radius), sp.y });
		hat.add({ sp.x - int(1.2*radius), sp.y-10 });
		hat.add({ sp.x - int(0.8*radius), sp.y-10 });
		hat.add({ sp.x - int(0.8*radius), sp.y - 10 - int(radius*0.3) });
		hat.add({ sp.x + int(0.8*radius), sp.y - 10 - int(radius*0.3) });
		hat.add({ sp.x + int(0.8*radius), sp.y - 10 });
		hat.add({ sp.x + int(1.2*radius), sp.y - 10 });
		hat.add({ sp.x + int(1.2*radius), sp.y });
		hat.set_fill_color(Color::yellow);
	}
	void Hat_smiley::draw_lines() const
	{
		Smiley::draw_lines();
		hat.draw();
	}
	void Hat_smiley::move(int dx, int dy)
	{
		Smiley::move(dx, dy);
		hat.move(dx, dy);
	}
	void Hat_smiley::set_color(Color c)
	{
		Smiley::set_color(c);
	}


	Frowny::Frowny(Point p, int radius)
		: Circle_face(p, radius)
	{
		mouth.set_angle1(0);
		mouth.set_angle2(180);
		mouth.move(0, radius*0.66);
	}
	Hat_frowny::Hat_frowny(Point p, int radius)
		:Frowny(p, radius)
	{
		Point sp{ Circle::center().x, center().y - int(radius*0.8) };
		cap.add(sp);
		cap.add({ sp.x - int(1.0*radius), sp.y });
		cap.add({ sp.x, sp.y - radius });
		cap.add({ sp.x + int(1.0*radius), sp.y });
		cap.set_fill_color(Color::black);
	}
	void Hat_frowny::draw_lines() const
	{
		Frowny::draw_lines();
		cap.draw();
	}
	void Hat_frowny::move(int dx, int dy)
	{
		Frowny::move(dx, dy);
		cap.move(dx, dy);
	}
	void Hat_frowny::set_color(Color c)
	{
		Frowny::set_color(c);
	}



	void Striped_rectangle::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			for (Point p = point(0); p.x < point(0).x + width(); p.x += 2)
			{
				fl_line(p.x, p.y, p.x, p.y + height()-2);
			}
		}

		if (color().visibility()) {	// edge on top of fill
			fl_color(color().as_int());
			fl_rect(point(0).x, point(0).y, width(), height());
		}
	}

	void Striped_circle::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			for (Point p{ center().x - radius(), center().y }; p.x < center().x + radius(); p.x += 2)
				fl_line(p.x, p.y - int(sqrt(pow(radius(), 2) - pow(center().x - p.x, 2))),
					p.x, p.y + int(sqrt(pow(radius(), 2) - pow(center().x - p.x, 2))));
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, radius() + radius(), radius() + radius(), 0, 360);
		}
	}

	void Striped_closed_polyline::draw_lines() const
	{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());

			int x_min{ point(0).x };
			int x_max{ point(0).x };
			int y_min{ point(0).y };
			int y_max{ point(0).y };
			for (int i = 0; i < number_of_points(); ++i)
			{
				if (point(i).x < x_min) x_min = point(i).x;
				if (point(i).x > x_max) x_max = point(i).x;
				if (point(i).y < y_min) y_min = point(i).y;
				if (point(i).y > y_max) y_max = point(i).y;
			}
			y_min -= 5;
			y_max += 5;

			
			for (int x = x_min; x < x_max; x += 2)
			{
				vector<Point> intersections;
				Point intersection;
				for (int i = 1; i < number_of_points(); ++i)
				{
					if (line_segment_intersect(Point{ x, y_min },
						Point{ x, y_max },
						point(i - 1),
						point(i),
						intersection)) intersections.push_back(intersection);

					//closing line
					if (line_segment_intersect(Point{ x, y_min },
						Point{ x, y_max },
						point(0),
						point(number_of_points() - 1),
						intersection)) intersections.push_back(intersection);
				}

				for (int i = 1; i < intersections.size(); i += 2)
					fl_line(intersections[i].x, intersections[i].y,
						intersections[i - 1].x, intersections[i - 1].y);
			}

			

			fl_color(color().as_int());	// reset color
		}

		if (color().visibility())
		{
			Shape::draw_lines();
			fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y,
				point(0).x, point(0).y);
		}
	}


	void Group::set_color(Color c)
	{
		for (int i = 0; i < shapes.size(); ++i)
			shapes[i].set_color(c);
	}
	void Group::set_fill_color(Color c)
	{
		for (int i = 0; i < shapes.size(); ++i)
			shapes[i].set_fill_color(c);
	}
	void Group::move(int dx, int dy)
	{
		for (int i = 0; i < shapes.size(); ++i)
			shapes[i].move(dx, dy);
	}
	void Group::draw_lines() const
	{
		for (int i = 0; i < shapes.size(); ++i)
			shapes[i].draw();
	}



	Pseudo_window::Pseudo_window(Point xy, int ww, int hh, string lab)
		:Box(xy, ww, hh, 10),
		win_name(Point(xy.x + 8, xy.y + 22), lab),
		ctrl1(Point(xy.x + ww - 26, xy.y + 4), 22, 22, 3),
		ctrl2(Point(xy.x + ww - 26 - 30, xy.y + 4), 22, 22, 3),
		ctrl3(Point(xy.x + ww - 26 - 60, xy.y + 4), 22, 22, 3),
		bg(Point(xy.x + 4, xy.y + 32), Point(xy.x + ww - 4, xy.y + hh - 4)),
		content(Point(xy.x + 4, xy.y + 32), "img.jpg")
	{
		set_color(Color::invisible);
		set_fill_color(Color::blue);
		win_name.set_font_size(15);
		win_name.set_color(Color::white);
		win_name.set_font(Font::helvetica_bold);
		ctrl1.set_color(Color::white);
		ctrl1.set_fill_color(Color::red);
		x.add(Point(xy.x + ww - 20, xy.y + 10), Point(xy.x + ww - 10, xy.y + 20));
		x.add(Point(xy.x + ww - 20, xy.y + 20), Point(xy.x + ww - 10, xy.y + 10));
		//x.add(Point(xy.x, xy.y - 30), Point(xy.x + ww, xy.y + 30));
		x.set_style(Line_style(Line_style::solid, 3));
		x.set_color(Color::white);
		bg.set_color(Color::invisible);
		bg.set_fill_color(fl_rgb_color(236, 233, 216));
		content.set_mask(Point(0, 0), bg.width(), bg.height());
	}

	void Pseudo_window::draw_lines() const
	{
		Box::draw_lines();
		win_name.draw();
		ctrl1.draw();
		ctrl2.draw();
		ctrl3.draw();
		x.draw();
		bg.draw();
		content.draw();
	}

	Binary_tree::Binary_tree(Point xy, int levels_number, string edge_style)
		:levels{levels_number}
	{
		if (levels < 0) error("Levels number must be at least zero!");
		if (levels == 0) return;
		int dw = 50;
		int dh = 100;
		for (int i = 0; i < levels; ++i)
		{
			for (int j = 0; j < pow(2, i); ++j)
			{
				add(Point{ xy.x - int(pow(2, i)-1)*dw/2 + j*dw, xy.y + i*dh });	
			}
		}

		for (int i = 0; i < number_of_points(); ++i)
		{
			labels.push_back(new Text{ Point{point(i).x + 5, point(i).y - 20}, "" });
			if (2 * i + 2 < number_of_points())
			{
				if (edge_style == "ad")
				{
					edges.push_back(new Arrow{ Point{point(i).x - int(15 * cos(45 * PI / 180)), point(i).y + int(15 * cos(45 * PI / 180))},
						Point{point(2 * i + 1).x, point(2 * i + 1).y - 15 } });
					edges.push_back(new Arrow{ Point{ point(i).x + int(15 * cos(45 * PI / 180)), point(i).y + int(15 * cos(45 * PI / 180)) },
						Point{ point(2 * i + 2).x, point(2 * i + 2).y - 15 } });
				}
				if (edge_style == "au")
				{
					edges.push_back(new Arrow{ Point{ point(2 * i + 1).x, point(2 * i + 1).y - 15 },
						Point{ point(i).x - int(15 * cos(45 * PI / 180)), point(i).y + int(15 * cos(45 * PI / 180)) } });
					edges.push_back(new Arrow{ Point{ point(2 * i + 2).x, point(2 * i + 2).y - 15 },
						Point{ point(i).x + int(15 * cos(45 * PI / 180)), point(i).y + int(15 * cos(45 * PI / 180)) } });
					edges[edges.size() - 1].set_color(Color::red);
					edges[edges.size() - 2].set_color(Color::red);
				}
				else
				{
					edges.push_back(new Line{ Point{ point(i).x - int(15 * cos(45 * PI / 180)), point(i).y + int(15 * cos(45 * PI / 180)) },
						Point{ point(2 * i + 1).x, point(2 * i + 1).y - 15 } });
					edges.push_back(new Line{ Point{ point(i).x + int(15 * cos(45 * PI / 180)), point(i).y + int(15 * cos(45 * PI / 180)) },
						Point{ point(2 * i + 2).x, point(2 * i + 2).y - 15 } });
				}
			}
		}
	}

	void Binary_tree::draw_lines() const
	{
		for (int i = 0; i < number_of_points(); ++i)
		{
			if (labels[i].label() != "")
				labels[i].draw_lines();
			Circle nod{ point(i), 15 };
			nod.draw_lines();
		}
		for (int i = 0; i < edges.size(); ++i)
			edges[i].draw();
	}

	void Binary_tree::set_node_label(const string& path)
	{
		if (path.empty()) error("Path is empty!");
		if (path.size() > levels) error("Path is too long for this tree!");
		istringstream istr{ path };
		char ch;
		istr >> ch;
		if (path.size() == 1)
		{
			labels[0].set_label("root");
			return;
		}
		int index{0};
		while (istr >> ch)
		{
			switch (ch)
			{
			case 'l':
				index = 2 * index + 1;
				break;
			case 'r':
				index = 2 * index + 2;
				break;
			default:
				error("Invalid letter in the path!");
			}
		}
		labels[index].set_label(path);
	}


	void Star_nodes_B_tree::draw_lines() const
	{
		for (int i = 0; i < number_of_points(); ++i)
		{
			if (labels[i].label() != "")
				labels[i].draw_lines();
			Star nod{ point(i), 8, 15, 3 };
			nod.draw_lines();
		}
		for (int i = 0; i < edges.size(); ++i)
			edges[i].draw();

	}

} // Graph