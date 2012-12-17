#include <iostream>
#include "ImgToXml.h"

using namespace std;

int main()
{
	QVector<int> imgClassVec;
	imgClassVec << 0 << 1;
	ImgToXml Test ("img", ".jpg", 2, 4000000, 80, 80, imgClassVec);
	Test.makeXml("sample.xml");
	Test.convert("img2.jpg", "img.xml");
	cout << "done";
}
