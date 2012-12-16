#include <iostream>
#include "BmpToXml.h"
#include "ImgToXml.h"

using namespace std;

int main()
{
	//BmpToXml Test ("test", ".bmp", 3, 200, 80, 80);
	// i.e. "test0.bmp", "test1.bmp", "test2.bmp".
	//Test.makeXml("sample.xml");

	ImgToXml Test ("img", ".jpg", 5, 4000000, 80, 80);
	// i.e. "img0.jpg" ... "img4.jpg"
	Test.makeXml("img.xml");
	cout << "done";
}
