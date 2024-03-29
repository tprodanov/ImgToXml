#include <QImage>
#include "ImgToXml.h"

ImgToXml::ImgToXml(const QString imgPrefix
				   , const QString imgPostfix
				   , const int countOfImages
				   , const int sensitivity
				   , const int imgSizeX
				   , const int imgSizeY, const QVector<int> &imgClassVec
				   ) {
	mImgPrefix = imgPrefix;
	mImgPostfix = imgPostfix;
	mCountOfImages = countOfImages;
	mImgSizeX = imgSizeX;
	mImgSizeY = imgSizeY;
	mSens = sensitivity;
	mNowInput.resize(imgSizeX * imgSizeY);
	mImgClassVec = imgClassVec;
}

void ImgToXml::makeNowInput(const int imgNum) {
	QString stringImgNum = QString::number(imgNum);
	QString fileName = mImgPrefix + stringImgNum + mImgPostfix;
	QImage img(fileName);
	int i, j, nowColor;
	for (i = 0; i < mImgSizeY; i++) {
		for (j = 0; j < mImgSizeX; j++) {
			nowColor = img.pixel(j, i) - 4278190080;
			if (nowColor < mSens) {
				mNowInput [mImgSizeX * i + j] = 1;
			}
			else {
				mNowInput [mImgSizeX * i + j] = 0;
			}
		}
	}
}

QDomElement ImgToXml::saveImage(QDomDocument &sampleXml, const int imgNum) {
	QDomElement image = sampleXml.createElement("image");
	image.setAttribute("number", imgNum + 1);
	image.setAttribute("imageClass", mImgClassVec.at(imgNum));
	int i, j;
	QString lineStr (mImgSizeX);
	makeNowInput(imgNum);
	for (i = 0; i < mImgSizeY; i++) {
		QDomElement line = sampleXml.createElement("line");
		line.setAttribute("number", i + 1);
		for (j = 0; j < mImgSizeX; j++) {
			lineStr[j] = mNowInput[i * mImgSizeX + j] + 48;
		}
		line.setAttribute("value", lineStr);
		image.appendChild(line);
	}
	return image;
}

void ImgToXml::makeXml(QString xmlFile) {
	QDomDocument sampleXml ("NeuralNetworkSample");
	QDomElement sample = sampleXml.createElement("sample");
	sample.setAttribute("countOfImages", mCountOfImages);
	sample.setAttribute("width", mImgSizeX);
	sample.setAttribute("height", mImgSizeY);
	sampleXml.appendChild(sample);
	for (int i = 0; i < mCountOfImages; i++) {
		sample.appendChild(saveImage(sampleXml, i));
	}
	QFile saveSample(xmlFile);
	saveSample.open(QIODevice::WriteOnly);
	QTextStream(&saveSample) << sampleXml.toString();
	saveSample.close();
}

void ImgToXml::convert(QString imgName, QString xmlFile) {
	QImage img(imgName);
	int width = img.width(), height = img.height(), nowColor;
	QVector<int> imgVec(width * height);
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			nowColor = img.pixel(j, i) - 4278190080;;
			if (nowColor < mSens) {
				imgVec [width * i + j] = 1;
			}
			else {
				imgVec [width * i + j] = 0;
			}
		}
	}
	QDomDocument picture ("Image");
	QDomElement image = picture.createElement("image");
	image.setAttribute("width", width);
	image.setAttribute("height", height);
	picture.appendChild(image);
	QString lineStr(width);
	for (i = 0; i < height; i++) {
		QDomElement line = picture.createElement("line");
		line.setAttribute("number", i + 1);
		for (j = 0; j < width; j++) {
			lineStr[j] = imgVec[i * width + j] + 48;
		}
		line.setAttribute("value", lineStr);
		image.appendChild(line);
	}
	QFile savePict(xmlFile);
	savePict.open(QIODevice::WriteOnly);
	QTextStream(&savePict) << picture.toString();
	savePict.close();
}
