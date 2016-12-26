#include "Simple_window.h"

class Controller
{
public:
	virtual void on() = 0;
	virtual void off() = 0;
	virtual void set_level(int level) = 0;
	virtual void show() = 0;

};

class Tester : public Controller
{
public:
	Tester(bool is_on, int level)
		:state(is_on), lvl(level) {}
public:
	void show() override;
private:
	bool state;
	int lvl;
};

void Tester::show()
{
	cout << "Tester::show() : " << endl;
	if (state) cout << "ON ";
	else cout << "OFF; ";
	cout << lvl << ';' << endl;
}

class Shape_controller : public Controller
{
public:
	Shape_controller(Shape& shape)
		:shp(&shape) {}
private:      //pointer, again i'll skip it for now
	Shape* shp;
};
