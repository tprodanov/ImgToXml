#pragma once
#include <QtXml>

class BmpToXml
{
public:
	BmpToXml(const QString &imgPrefix
			 , const QString &imgPostfix
			 , const int countOfImages
			 , const int sensitivity
			 , const int imgSizeX
			 , const int imgSizeY
			 );
	void makeXml(const QString &xmlFile);
private:
	void makeNowInput(const int imgNumber);
	QDomElement saveImage(QDomDocument &sampleXml, const int imgNum);
	QString mImgPrefix, mImgPostfix;
	QVector<int> mNowInput;
	int mCountOfImages, mSens, mImgSizeX, mImgSizeY;
};
