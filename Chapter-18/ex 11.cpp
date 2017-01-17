#include "../../../../libs/std_lib_facilities.h"
using namespace std;

struct Node {
	Node(int val, int height)
		:value(val), next(height) {}
	int value;
	vector<Node*> next; //levels with pointers
};

class Skip_list {
public:
	Skip_list(int max_height)
		:max_h(max_height), head(nullptr) {}


	void insert(int x);
	void remove(int x);
	Node* find(int x);
	void print_all();
	void print_level(int lvl);
private:
	Node* head;
	int max_h;
	int roll_height();
};

int Skip_list::roll_height()
{
	int rand_height = 1;
	while (randint(10000) < 2500 && rand_height < max_h)
		++rand_height;
	return rand_height;
}


void Skip_list::insert(int x)
{
	if (head == nullptr)// empty list
	{
		head = new Node(x, max_h);
		for (int i = 0; i < max_h; ++i)
			head->next[i] = nullptr;
	}
	else if (x < head->value)//becomes new head
	{
		Node* new_node = new Node(x, max_h);
		for (int i = 0; i < max_h; ++i)
			new_node->next[i] = head;
		head = new_node;
	}
	else
	{
		Node* new_node = new Node(x, roll_height());
		for (int i = 0; i < new_node->next.size(); ++i)
		{
			Node* prev_i_lvl = head;
			Node* next_i_lvl = head->next[i];
			while (next_i_lvl != nullptr && next_i_lvl->value < x)
			{
				next_i_lvl = next_i_lvl->next[i];
				prev_i_lvl = prev_i_lvl->next[i];
			}
			prev_i_lvl->next[i] = new_node;
			new_node->next[i] = next_i_lvl;
		}
	}
}
void Skip_list::remove(int x)
{
	if (head == nullptr)
	{
		cerr << "The skip list is empty!\n";
		return;
	}
	if (head->value == x)  //remove head, make the next node to be the new head, or make empty list, if it was the only element
	{
		if (head->next[0] == nullptr)
		{
			head = nullptr;
			return;
		}
		vector<Node*> new_ptrs(max_h);
		int old_ptrs_num = head->next[0]->next.size();
		for (int i = 0; i < old_ptrs_num; ++i)
			new_ptrs[i] = head->next[0]->next[i];
		for (int i = old_ptrs_num; i < max_h; ++i)
			new_ptrs[i] = head->next[i];

		head->next[0]->next = new_ptrs;
		Node* buff = head->next[0];
		delete head;
		head = buff;
		return;
	}

	Node* prev_i_lvl = nullptr;
	Node* curr_i_lvl = nullptr;
	Node* next_i_lvl = nullptr;
	for (int i = max_h - 1 ; i >= 0; --i)
	{
		prev_i_lvl = nullptr;
		curr_i_lvl = head;
		next_i_lvl = head->next[i];
		while (next_i_lvl != nullptr && curr_i_lvl->value != x)
		{
			prev_i_lvl = curr_i_lvl;
			curr_i_lvl = next_i_lvl;
			next_i_lvl = next_i_lvl->next[i];
		}
		if (curr_i_lvl->value == x)
		{
			prev_i_lvl->next[i] = next_i_lvl;
		}
	}
	if (curr_i_lvl->value != x) cerr << "There is no such element in the list!\n";
	else delete curr_i_lvl;
}
Node* Skip_list::find(int x)//returns nullptr if a value is not found
{
	int curr_lvl = max_h - 1;
	Node* curr_node = head;
	while (curr_node->value != x)
	{
		if (curr_node->next[curr_lvl] == nullptr) --curr_lvl;
		else if (curr_node->next[curr_lvl]->value > x) --curr_lvl;
		else curr_node = curr_node->next[curr_lvl];
		if (curr_lvl < 0) break;
	}
	if (curr_node->value != x) return nullptr;
	return curr_node;
}
void Skip_list::print_all()
{
	Node* current = head;
	cout << "All nodes of the skip list:\n{ ";
	while (current != nullptr)
	{
		cout << current->value;
		current = current->next[0];
		if (current != nullptr) cout << ", ";
	}
	cout << " }";
}
void Skip_list::print_level(int lvl)
{
	Node* current = head;
	cout << "Nodes on the " << lvl <<" level of the skip list:\n{ ";
	while (current != nullptr)
	{
		cout << current->value;
		current = current->next[lvl];
		if (current != nullptr) cout << ", ";
	}
	cout << " }";
}

int main()
{
	Skip_list my_sl(4);
	my_sl.print_all(); // empty
	cout << endl;

	my_sl.insert(10);
	my_sl.insert(20);
	my_sl.insert(-20);
	my_sl.insert(40);
	my_sl.insert(45);
	my_sl.insert(50);
	my_sl.insert(60);
	my_sl.insert(110);
	my_sl.print_all();
	cout << endl;
	my_sl.print_level(0);
	cout << endl;
	my_sl.print_level(1);
	cout << endl;
	my_sl.print_level(2);
	cout << endl;
	my_sl.print_level(3);
	cout << endl;
	cout << "--- --- ---\n";
	my_sl.remove(45);
	my_sl.print_all(); // empty
	cout << endl;
	my_sl.print_level(0);
	cout << endl;
	my_sl.print_level(1);
	cout << endl;
	my_sl.print_level(2);
	cout << endl;
	my_sl.print_level(3);
	cout << endl;
	cout << "--- --- ---\n";
	Node* search = my_sl.find(50);
	if (search == nullptr) cout << "Not found\n";
	else cout << "Node has been found: " << search->value << endl;
}