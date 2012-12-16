#include "BmpToXml.h"

BmpToXml::BmpToXml(const QString imgPrefix
				   , const QString imgPostfix
				   , const int countOfImages
				   , const int sensitivity
				   , const int imgSizeX
				   , const int imgSizeY
				   ) {
	mImgPrefix = imgPrefix;
	mImgPostfix = imgPostfix;
	mCountOfImages = countOfImages;
	mImgSizeX = imgSizeX;
	mImgSizeY = imgSizeY;
	mSens = sensitivity;
	mNowInput.resize(imgSizeX * imgSizeY);
}

void BmpToXml::makeNowInput (const int imgNumber) {
	QString stringImgNum = QString::number(imgNumber);
	QString fileName = mImgPrefix + stringImgNum + mImgPostfix;
	QFile img (fileName);
	QByteArray byteArray;
	img.open(QIODevice::ReadOnly);
	byteArray = img.readAll();
	QVector<int> positiveByteArray;
	int minImgSizeAndArraySize;
	if (byteArray.size() >= mImgSizeX * mImgSizeY * 3) {
		minImgSizeAndArraySize = mImgSizeX * mImgSizeY * 3;
	}
	else {
		minImgSizeAndArraySize = byteArray.size();
	}
	for (int i = 0; i < minImgSizeAndArraySize; i++) {
		positiveByteArray << byteArray.at(i);
		if (positiveByteArray[i] < 0) {
			positiveByteArray[i] += 255;
		}
	}
	img.close();
	int i, j = 0, k;
	for (i = 54; i < minImgSizeAndArraySize; i += 3) {
		k = mImgSizeY * (mImgSizeY - 1) - j + 2 * (j % mImgSizeY);
		// to make (0,0) the upper left edge of the picture
		mNowInput[k] = positiveByteArray[i] + positiveByteArray[i + 1] + positiveByteArray[i + 2];
		if (mNowInput[k] < mSens) {
			mNowInput[k] = 1;
		}
		else {
			mNowInput[k] = 0;
		}
		j++;
	}
	for (i = j; i < mImgSizeX * mImgSizeY; i++) {
		mNowInput[i] = 0;
	}
}

QDomElement BmpToXml::saveImage(QDomDocument &sampleXml, const int imgNum) {
	QDomElement image = sampleXml.createElement("image");
	image.setAttribute("number", imgNum + 1);
	int i, j;
	QString lineStr;
	makeNowInput(imgNum);
	for (i = 0; i < mImgSizeY; i++) {
		QDomElement line = sampleXml.createElement("line");
		line.setAttribute("number", i + 1);
		for (j = 0; j < mImgSizeX; j++) {
			lineStr[j] = mNowInput[i * mImgSizeY + j] + 48;
		}
		line.setAttribute("value", lineStr);
		image.appendChild(line);
	}
	return image;
}

void BmpToXml::makeXml(QString xmlFile) {
	QDomDocument sampleXml ("NeuralNetworkSample");
	QDomElement sample = sampleXml.createElement("sample");
	sample.setAttribute("countOfImages", mCountOfImages);
	sampleXml.appendChild(sample);
	for (int i = 0; i < mCountOfImages; i++) {
		sample.appendChild(saveImage(sampleXml, i));
	}
	QFile saveSample(xmlFile);
	saveSample.open(QIODevice::WriteOnly);
	QTextStream(&saveSample) << sampleXml.toString();
	saveSample.close();
}
