#include <iostream>
#include "BmpToXml.h"
#include "ImgToXml.h"

using namespace std;

int main()
{
	QVector<int> imgClassVec;
	imgClassVec << 0 << 0 << 0 << 0 << 0 << 1 << 1 << 1 << 1 << 1;
	ImgToXml Test ("img", ".jpg", 10, 4000000, 80, 80, imgClassVec);
	Test.makeXml("sample.xml");
	Test.convert("img10.jpg", "img.xml");
	cout << "done";
}
