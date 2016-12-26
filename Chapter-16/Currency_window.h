#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)

using namespace Graph_lib;

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

struct Currency_window : Window {
	enum currencies {BYN, EUR, USD };
	Currency_window(Point xy, int w, int h, const string& title);
private:
	In_box input;
	Out_box output;
	Button from_button;
	Button to_button;
	Button convert_button;
	Menu from_menu;
	Menu to_menu;

	int type_from = BYN;
	int type_to = BYN;
	double usd_to_byn;
	double eur_to_byn;

	void show_from_menu() { from_button.hide(); from_menu.show(); }
	void show_to_menu() { to_button.hide(); to_menu.show(); }

	void set_from_byn() { from_menu.hide(); from_button.show(); type_from = BYN; }
	void set_from_eur() { from_menu.hide(); from_button.show(); type_from = EUR; }
	void set_from_usd() { from_menu.hide(); from_button.show(); type_from = USD; }

	void set_to_byn() { to_menu.hide(); to_button.show(); type_to = BYN; }
	void set_to_eur() { to_menu.hide(); to_button.show(); type_to = EUR; }
	void set_to_usd() { to_menu.hide(); to_button.show(); type_to = USD; }

	void convert();
};

Currency_window::Currency_window(Point xy, int w, int h, const string& title)
	: Window(xy, w, h, title),
	input(Point(x_max() - 250, 0), 80, 20, "Input sum: "),
	output(Point(x_max() - 100, 0), 80, 20, "Result: "),
	from_button(Point(x_max() - 250, 40), 80, 20, "from", [](Address, Address pw) { reference_to<Currency_window>(pw).show_from_menu(); }),
	to_button(Point(x_max() - 100, 40), 80, 20, "to", [](Address, Address pw) { reference_to<Currency_window>(pw).show_to_menu(); }),
	convert_button(Point(x_max() - 450, 0), 80, 80, "Convert", [](Address, Address pw) { reference_to<Currency_window>(pw).convert(); }),
	from_menu(Point(x_max() - 250, 40), 80, 20, Menu::vertical, "From: "),
	to_menu(Point(x_max() - 100, 40), 80, 20, Menu::vertical, "To: ")
{
	string curr;
	ifstream ifs{ "currency.txt" };
	ifs >> curr;
	if (curr != "EUR") error("Wrong format!");
	ifs >> eur_to_byn;
	ifs >> curr;
	if (curr != "USD") error("Wrong format!");
	ifs >> usd_to_byn;
	ifs.close();

	attach(input);
	attach(output);
	attach(from_button);
	attach(to_button);
	attach(convert_button);

	from_menu.attach(new Button(Point(0, 0), 0, 0, "BYN", [](Address, Address pw) { reference_to<Currency_window>(pw).set_from_byn(); }));
	from_menu.attach(new Button(Point(0, 0), 0, 0, "EUR", [](Address, Address pw) { reference_to<Currency_window>(pw).set_from_eur(); }));
	from_menu.attach(new Button(Point(0, 0), 0, 0, "USD", [](Address, Address pw) { reference_to<Currency_window>(pw).set_from_usd(); }));
	attach(from_menu);
	from_menu.hide();

	to_menu.attach(new Button(Point(0, 0), 0, 0, "BYN", [](Address, Address pw) { reference_to<Currency_window>(pw).set_to_byn(); }));
	to_menu.attach(new Button(Point(0, 0), 0, 0, "EUR", [](Address, Address pw) { reference_to<Currency_window>(pw).set_to_eur(); }));
	to_menu.attach(new Button(Point(0, 0), 0, 0, "USD", [](Address, Address pw) { reference_to<Currency_window>(pw).set_to_usd(); }));
	attach(to_menu);
	to_menu.hide();
}

void Currency_window::convert() {
	if (input.get_string() == "") return;
	double input_val_byn;
	switch (type_from)
	{
	case BYN:
		input_val_byn = input.get_int();
		break;
	case EUR:
		input_val_byn = eur_to_byn * input.get_int();
		break;
	case USD:
		input_val_byn = usd_to_byn * input.get_int();
		break;
	}
	double output_value;
	switch (type_to)
	{
	case BYN:
		output_value = input_val_byn;
		break;
	case EUR:
		output_value = input_val_byn / eur_to_byn;
		break;
	case USD:
		output_value = input_val_byn / usd_to_byn;
		break;
	}
	stringstream str;
	str << output_value;
	output.put(str.str());
}
