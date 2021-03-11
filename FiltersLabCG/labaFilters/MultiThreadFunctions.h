#pragma once
#include <QtCore/QCoreApplication>
#include <qimage.h>
#include <string>
#include "Filters.h"
#include <iostream>
#include <Windows.h>
using namespace std;

QImage spbMT;
QImage catMT;
QImage wolfMT;
QImage grlecMT;
QImage lslecMT;

void loadimages() {
	spbMT.load("C:/ProgrammingCurrentProjects/labaFilters/input/spb.PNG");
	catMT.load("C:/ProgrammingCurrentProjects/labaFilters/input/cat.PNG");
	wolfMT.load("C:/ProgrammingCurrentProjects/labaFilters/input/wolf.PNG");
	grlecMT.load("C:/ProgrammingCurrentProjects/labaFilters/input/grlec.PNG");
	lslecMT.load("C:/ProgrammingCurrentProjects/labaFilters/input/lslec2.PNG");
}

DWORD WINAPI InversionTP(LPVOID lp) {
	Invert_Filter* invert = new Invert_Filter();
	QImage invertImage = invert->calculateNewImagePixMap(spbMT, 0);
	invertImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Invert.PNG");
	return 0;
}
DWORD WINAPI BlurTP(LPVOID lp) {
	Blur_Filter* blur = new Blur_Filter();
	QImage blurImage = blur->calculateNewImagePixMap(spbMT, 1);
	blurImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Blur.PNG");
	return 0;
}
DWORD WINAPI GaussianTP(LPVOID lp) {
	Gaussian_Blur_Filter* gblur = new Gaussian_Blur_Filter();
	QImage gblurImage = gblur->calculateNewImagePixMap(spbMT, 3);
	gblurImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/GaussBlur.PNG");
	return 0;
}
DWORD WINAPI GrayScaleTP(LPVOID lp) {
	Gray_Scale_Filter* grayscale = new Gray_Scale_Filter();
	QImage grayscaleImage = grayscale->calculateNewImagePixMap(spbMT, 0);
	grayscaleImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/GrayScale.PNG");
	return 0;
}
DWORD WINAPI SepiaTP(LPVOID lp) {
	Sepia_Filter* sepia = new Sepia_Filter();
	QImage sepiaImage = sepia->calculateNewImagePixMap(spbMT, 25);
	sepiaImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Sepia.PNG");
	return 0;
}
DWORD WINAPI BrithnessTP(LPVOID lp) {
	Brihtness_Filter* bright = new Brihtness_Filter();
	QImage brightImage = bright->calculateNewImagePixMap(spbMT, 100);
	brightImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Brightness.PNG");
	return 0;
}
DWORD WINAPI SobelTP(LPVOID lp) {
	Sobel_Filter* sobel = new Sobel_Filter();
	QImage sobelImage = sobel->calculateNewImagePixMap(spbMT, 1);
	sobelImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Sobel.PNG");
	return 0;
}
DWORD WINAPI EmbossingTP(LPVOID lp) {
	Embossing_Filter* emb = new Embossing_Filter();
	QImage embImage = emb->calculateNewImagePixMap(spbMT, 1);
	embImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Embossing.PNG");
	return 0;
}
DWORD WINAPI RotationTP(LPVOID lp) {
	Rotation_Filter* rot = new Rotation_Filter();
	QImage rotImage = rot->calculateNewImagePixMap(spbMT, 0);
	rotImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Rotation.PNG");
	return 0;
}
DWORD WINAPI WavesTP(LPVOID lp) {
	Waves_Filter* wav = new Waves_Filter();
	QImage wavImage = wav->calculateNewImagePixMap(spbMT, 0);
	wavImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Waves.PNG");
	return 0;
}
DWORD WINAPI Sharpness1TP(LPVOID lp) {
	Sharpness_Filter* sharp = new Sharpness_Filter();
	QImage sharpImage = sharp->calculateNewImagePixMap(spbMT, 1);
	sharpImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Sharpness1.PNG");
	return 0;
}
DWORD WINAPI Sharpness2TP(LPVOID lp) {
	Sharpness2_Filter* sharp = new Sharpness2_Filter();
	QImage sharpImage = sharp->calculateNewImagePixMap(spbMT, 1);
	sharpImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Sharpness2.PNG");
	return 0;
}
DWORD WINAPI DilationTP(LPVOID lp) {
	int* strElem;
	strElem = new int[9];
	strElem[0] = 1; strElem[3] = 1; strElem[6] = 1;
	strElem[1] = 1; strElem[4] = 1; strElem[7] = 1;
	strElem[2] = 1; strElem[5] = 1; strElem[8] = 1;
	Dilation* dil = new Dilation();
	QImage dilImage = dil->calculateNewImagePixMap(wolfMT, 1, strElem);
	dilImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Dilation.PNG");
	return 0;
}
DWORD WINAPI ErosionTP(LPVOID lp) {
	int* strElem;
	strElem = new int[9];
	strElem[0] = 1; strElem[3] = 1; strElem[6] = 1;
	strElem[1] = 1; strElem[4] = 1; strElem[7] = 1;
	strElem[2] = 1; strElem[5] = 1; strElem[8] = 1;
	Erosion* eros = new Erosion();
	QImage erosImage = eros->calculateNewImagePixMap(catMT, 1, strElem);
	erosImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Erosion.PNG");
	return 0;
}
DWORD WINAPI OpeningTP(LPVOID lp) {
	int* strElem;
	strElem = new int[9];
	strElem[0] = 1; strElem[3] = 1; strElem[6] = 1;
	strElem[1] = 1; strElem[4] = 1; strElem[7] = 1;
	strElem[2] = 1; strElem[5] = 1; strElem[8] = 1;
	Opening* op = new Opening();
	QImage opImage = op->calculateNewImagePixMap(catMT, 1, strElem);
	opImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Opening.PNG");
	return 0;
}
DWORD WINAPI ClosingTP(LPVOID lp) {
	int* strElem;
	strElem = new int[9];
	strElem[0] = 1; strElem[3] = 1; strElem[6] = 1;
	strElem[1] = 1; strElem[4] = 1; strElem[7] = 1;
	strElem[2] = 1; strElem[5] = 1; strElem[8] = 1;
	Closing* cl = new Closing();
	QImage clImage = cl->calculateNewImagePixMap(wolfMT, 1, strElem);
	clImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Closing.PNG");
	return 0;
}
DWORD WINAPI GradTP(LPVOID lp) {
	int* strElem;
	strElem = new int[9];
	strElem[0] = 0; strElem[3] = 1; strElem[6] = 0;
	strElem[1] = 1; strElem[4] = 1; strElem[7] = 1;
	strElem[2] = 0; strElem[5] = 1; strElem[8] = 0;
	Grad* gr = new Grad();
	QImage grImage = gr->calculateNewImagePixMap(grlecMT, 1, strElem);
	grImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Grad.PNG");
	return 0;
}
DWORD WINAPI MedianTP(LPVOID lp) {
	Median_Filter* med = new Median_Filter();
	QImage medImage = med->calculateNewImagePixMap(spbMT, 2);
	medImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/Mediane.PNG");
	return 0;
}
DWORD WINAPI GrayWorldTP(LPVOID lp) {
	Gray_World* gw = new Gray_World();
	QImage gwImage = gw->calculateNewImagePixMap(spbMT);
	gwImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/GrayWorld.PNG");
	return 0;
}
DWORD WINAPI LinearStretchTP(LPVOID lp) {
	Linear_Stretch* ls = new Linear_Stretch();
	QImage lsImage = ls->calculateNewImagePixMap(lslecMT);
	lsImage.save("C:/ProgrammingCurrentProjects/labaFilters/output/LinearStretch.PNG");
	return 0;
}