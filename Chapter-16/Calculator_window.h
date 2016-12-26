
#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)

using namespace Graph_lib;
struct Token {
	char kind;
	double value;
};
struct Tokenstream {
	Tokenstream(string str)
		:iss(str), empty(true) {}
	Token get();
	void putback(Token& t);
private:
	istringstream iss;
	bool empty;
	Token buffer;
};

Token Tokenstream::get() {
	if (!empty)
	{	
		empty = true;
		return buffer;
	}
	char ch;
	iss >> ch;
	double val;
	Token t;
	if (isdigit(ch))
	{
		iss.putback(ch);	
		iss >> val;	
		t.kind = '#';
		t.value = val;
		return t;
	}
	t.kind = ch;
	t.value = 0;
	return t;
}

void Tokenstream::putback(Token& t) {
	if (!empty) error(" Tokenstream is not empty! ");
	empty = false;
	buffer = t;
}

double expression(Tokenstream& ts);

double primary(Tokenstream& ts) {
	Token t = ts.get();
	if (t.kind == '#') return t.value;
	if (t.kind == '(')
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')') error(" ')' was expected! ");
		return d;
	}
	error("Invalid token!");
}
double term(Tokenstream& ts)
{
	double d = primary(ts);
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '*':
			d *= primary(ts);
			t = ts.get();
			break;
		case '/':
		{
			double divider = primary(ts);
			if (divider == 0) error("Divide-by-zero error!");
			d /= divider;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return d;
		}
	}
}
double expression(Tokenstream& ts) {
	double d = term(ts);
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '+':
			d += term(ts);
			t = ts.get();
			break;
		case '-':
			d -= term(ts);
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return d;
		}
	}
}
 
struct Calculator_window : Window {
	Calculator_window(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		calculate_button(Point(x_max() - 400, 30), 100, 100, "Calculate", [](Address, Address pw) { reference_to<Calculator_window>(pw).calculate(); }),
		input(Point(x_max() - 400, 0), 200, 20, "Input experssion: "),
		output(Point(x_max() - 100, 0), 80, 20, "Result: ")
	{
		attach(calculate_button);
		attach(input);
		attach(output);
	}
private:
	Button calculate_button;
	In_box input;
	Out_box output;

	void calculate();
};

void Calculator_window::calculate()
{
	Tokenstream ts{ input.get_string() + '=' };
	double result = expression(ts);
	output.put(result);
	redraw();
}