#include <iostream>
#include "BmpToXml.h"
#include "ImgToXml.h"

using namespace std;

int main()
{
	//BmpToXml Test ("test", ".bmp", 3, 200, 80, 80);
	// i.e. "test0.bmp", "test1.bmp", "test2.bmp".
	//Test.makeXml("sample.xml");

	QVector<int> imgClassVec;
	imgClassVec << 0 << 0 << 1 << 1 << 2;
	ImgToXml Test ("img", ".jpg", 5, 4000000, 80, 80, imgClassVec);
	// i.e. "img0.jpg" ... "img4.jpg", 1st pictures belongs to 0th class (for example, square), etc.
	Test.makeXml("img.xml");
	cout << "done";
}
