#include <iostream>
using namespace std;
int main()
{
	int arr[3];
	cout << "Array: " << arr << " " << &arr[1] << " " << &arr[2] << " " <<
		&arr[3] << " " << &arr[4] << endl;
	//int* p =  &arr[1000];
	//int a = *p;
	//cout << a << endl;

	//for (int* p = arr; p < &arr[10]; ++p)
	//{
	//	cout << *p << endl;
	//}

	int arr1[10];
	cout << sizeof(arr1) << endl;  //in this case size of gets the size of the all array
	int* p = arr1;
	cout << sizeof(p) << endl;  //and here it's int's size
	int* dp = new int[10];
	cout << sizeof(dp) << endl;	// obviously


}