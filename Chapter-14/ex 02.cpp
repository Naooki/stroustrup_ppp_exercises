#include "Simple_window.h"


int main()
try
{
	Simple_window win{ Point{ 100,100 }, 600, 400, "Exercise 2" };
	
	Hat_frowny hf{ Point{200,200}, 100 };

	Hat_frowny hf1{ hf };  //So, cause copying constructor is deleted, we cant do it;
	Hat_frowny hf2 = hf;   //'=' has also been deleted in Shape;


	win.attach(hf);

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
