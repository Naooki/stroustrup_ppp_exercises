#include "simple_window.h"

int main()
try
{
	Simple_window win{ Point{ 100,100 }, 800, 600, "exercise 10" };
	

	Star_nodes_B_tree tree{ Point{400,50},4, "ad" };
	tree.set_node_label("l");
	tree.set_node_label("ll");
	tree.set_node_label("lr");
	tree.set_node_label("lrlr");

	win.attach(tree);

	win.wait_for_button();
}
catch (exception& e)
{
	cerr << e.what() << endl;
}
catch (...)
{
	cerr << "exception!" << endl;
}
