#pragma once
#include <QtXml>
#include <QImage>


class ImgToXml
{
public:
	ImgToXml(const QString imgPrefix
			 , const QString imgPostfix
			 , const int countOfImages
			 , const int sensitivity
			 , const int imgSizeX
			 , const int imgSizeY
			 );
	void makeXml(QString xmlFile);
private:
	void makeNowInput(const int imgNum);
	QDomElement saveImage(QDomDocument &sampleXml, const int imgNum);
	QVector<int> mNowInput;
	QString mImgPrefix, mImgPostfix;
	int mCountOfImages, mSens, mImgSizeX, mImgSizeY;
};
