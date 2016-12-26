#include "Simple_window.h"


int main()
try
{
	Simple_window win{ Point{100,100}, 600, 400, "Exercise 4" };
	Immobile_circle imm_cir{ Point{300,200},100 };
	imm_cir.move(100, 0);   //so yeah, now it's just inaccessible
	win.attach(imm_cir);
	win.wait_for_button();
}
catch (exception& e)
{
	cerr << e.what() << endl;
}
catch (...)
{
	cerr << "Exception!" << endl;
}
