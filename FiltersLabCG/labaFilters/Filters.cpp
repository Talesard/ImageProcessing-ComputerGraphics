#include "Filters.h"
#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES
template <class T>
T clamp(T v, int max, int min) {
	if (v > max) {
		return max;
	}
	else {
		if (v < min) {
			return min;
		}
	}
	return v;
}
int ColorCompare(const void* x1, const void* x2) {
	float L = (*(QColor*)x1).red() * 0.3 + (*(QColor*)x1).green() * 0.59 + (*(QColor*)x1).blue() * 0.11;
	float R = (*(QColor*)x2).red() * 0.3 + (*(QColor*)x2).green() * 0.59 + (*(QColor*)x2).blue() * 0.11;
	return L - R;
}
//----------------------------------------------------------------------------------//
QImage Invert_Filter::calculateNewImagePixMap(const QImage& photo, int radius) {
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			QColor photo_color = photo.pixelColor(x, y);
			photo_color.setRgb(255 - photo_color.red(), 255 - photo_color.green(), 255 - photo_color.blue());
			result_Image.setPixelColor(x, y, photo_color);
		}
	}
	return result_Image;
}
//----------------------------------------------------------------------------------//
QColor Matrix_Filter::calculateNewPixelColor(QImage photo, int x, int y, int radius) {
	int returnR = 0;
	int returnG = 0;
	int returnB = 0;
	int size = 2 * radius + 1;
	for (int i =  - radius; i <= radius; i++) {
		for (int j = -radius; j <= radius; j++) {
			int idx = (i + radius) * size + j + radius;
			QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0),clamp<int>(y+i,photo.height()-1,0));
			returnR += color.red() * vector[idx];
			returnG += color.green() * vector[idx];
			returnB += color.blue() * vector[idx];
		}
		//return QColor(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));
	}
	return QColor(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));
}
QImage Matrix_Filter::calculateNewImagePixMap(const QImage& photo, int radius) {
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			result_Image.setPixelColor(x, y, calculateNewPixelColor(photo,x,y,radius));
		}
	}
	return result_Image;
}
//----------------------------------------------------------------------------------//
void Gaussian_Blur_Filter::createGaussianVector(int radius, int sigma) {
	//размер ядра
	const uint size = 2 * radius + 1; 
	//коэффициент нормировки ядра
	float norm = 0; 
	//создаем ядро фильтра
	vector = new float[size * size];
	//рассчитываем ядро фильтра
	for (int i = -radius; i <= radius; i++) {
		for (int j = -radius; j <= radius; j++) {
			int idx = (i + radius) * size + (j + radius);
			vector[idx] = exp(-(i * i + j * j) / (sigma * sigma));
			norm += vector[idx];
		}
	}
	//нормируем ядро
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			vector[i * size + j] /= norm;
		}
	}
}
//----------------------------------------------------------------------------------//
QColor Gray_Scale_Filter::calculateNewPixelColor(QImage photo, int x, int y) {
	float Intensity;
	QColor photo_color = photo.pixelColor(x, y);
	Intensity = photo_color.red() * 0.36 + photo_color.green() * 0.53 + photo_color.blue() * 0.11;
	photo_color.setRgb(Intensity, Intensity, Intensity);
	return photo_color;
}
QImage Gray_Scale_Filter::calculateNewImagePixMap(const QImage& photo, int radius) {
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			QColor photo_color = calculateNewPixelColor(photo, x, y);
			result_Image.setPixelColor(x, y, photo_color);
		}
	}
	return result_Image;
}
//----------------------------------------------------------------------------------//
QColor Sepia_Filter::calculateNewPixelColor(QImage photo, int x, int y,int k) {
	float Intensity;
	QColor photo_color = photo.pixelColor(x, y);
	Intensity = photo_color.red() * 0.36 + photo_color.green() * 0.53 + photo_color.blue() * 0.11;
	photo_color.setRgb(clamp<float>(Intensity+2*k,255,0), clamp<float>(Intensity+0.5*k,255,0), clamp<float>(Intensity-1*k,255,0));
	return photo_color;
}
QImage Sepia_Filter::calculateNewImagePixMap(const QImage& photo, int k) {
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			QColor photo_color = calculateNewPixelColor(photo, x, y,k);
			result_Image.setPixelColor(x, y, photo_color);
		}
	}
	return result_Image;
}
//----------------------------------------------------------------------------------//
QImage Brihtness_Filter::calculateNewImagePixMap(const QImage& photo, int k) {
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			QColor photo_color = photo.pixelColor(x, y);
			photo_color.setRgb(clamp(photo_color.red()+k,255,0), clamp(photo_color.green() + k, 255, 0), clamp(photo_color.blue() + k, 255, 0));
			result_Image.setPixelColor(x, y, photo_color);
		}
	}
	return result_Image;
}
//----------------------------------------------------------------------------------//
QColor Sobel_Filter::calculateNewPixelColor(QImage photo, int x, int y, int radius) {
	int returnR = 0;
	int returnG = 0;
	int returnB = 0;
	int size = 2 * radius + 1;
	for (int i = -radius; i <= radius; i++) {
		for (int j = -radius; j <= radius; j++) {
			int idx = (i + radius) * size + j + radius;
			QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0), clamp<int>(y + i, photo.height() - 1, 0));
			returnR += color.red() * vector_x[idx]+ color.red() * vector_y[idx];
			returnG += color.green() * vector_x[idx] + color.green() * vector_y[idx];
			returnB += color.blue() * vector_x[idx]+ color.blue() * vector_y[idx];
		}
	}
	return QColor(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));
}
QImage Sobel_Filter::calculateNewImagePixMap(const QImage& photo, int radius) {
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			result_Image.setPixelColor(x, y, calculateNewPixelColor(photo,x,y,radius));
		}
	}
	return result_Image;
}
//-------------------------------------LAB TASKS:--------------------------------------------//
QColor Embossing_Filter::calculateNewPixelColor(QImage photo, int x, int y, int radius) {
	int brightness=30;
	int returnR = 0;
	int returnG = 0;
	int returnB = 0;
	int norm = 1;
	int size = 2 * radius + 1;
	for (int i = -radius; i <= radius; i++) {
		for (int j = -radius; j <= radius; j++) {
			int idx = (i + radius) * size + j + radius;
			QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0), clamp<int>(y + i, photo.height() - 1, 0));
			returnR += color.red() * vector[idx]/norm;
			returnG += color.green() * vector[idx]/norm;
			returnB += color.blue() * vector[idx]/norm;
		}
		returnR += brightness; 
		returnG += brightness; 
		returnB += brightness;
	}
	return QColor(clamp(returnR, 255, 0), clamp(returnG, 255, 0), clamp(returnB, 255, 0));
}
QImage Embossing_Filter::calculateNewImagePixMap(const QImage& photo, int radius) {
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			result_Image.setPixelColor(x, y, calculateNewPixelColor(photo, x, y, radius));
		}
	}
	return result_Image;
}
//----------------------------------------------------------------------------------//

QImage Rotation_Filter::calculateNewImagePixMap(const QImage& photo, int radius) {
	QImage result_Image(photo);
	int x0 = photo.width() / 2; //rotate center x
	int y0 = photo.height() / 2;//rotate center y
	int x, y;
	float angle = 3.14/4; //radian
	for (int k = 0; k < photo.width(); k++) {
		for (int l = 0; l < photo.height(); l++) {
			x = (k - x0) * cos(angle) - (l - y0) * sin(angle) + x0;
			y = (k - x0) * sin(angle) + (l - y0) * cos(angle) + y0;
			result_Image.setPixelColor(k, l, photo.pixelColor(clamp(x,photo.width()-2,0), clamp(y,photo.height()-2,0)));
		}
	}
	return result_Image;
}
//----------------------------------------------------------------------------------//
QImage Waves_Filter::calculateNewImagePixMap(const QImage& photo, int radius) {
	QImage result_Image(photo);
	int x, y;
	for (int k = 0; k < photo.width(); k++) {
		for (int l = 0; l < photo.height(); l++) {
			x = k + 20 * sin(2 * 3.14 * l / 60);
			y = l;
			result_Image.setPixelColor(k, l, photo.pixelColor(clamp (x,photo.width()-2,0), clamp(y,photo.height()-2,0)));
		}
	}
	return result_Image;
}
//----------------------------------------------------------------------------------//
QImage Dilation::calculateNewImagePixMap(const QImage& photo, int radius,int* strElem) {
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			result_Image.setPixelColor(x, y, calculateNewPixelColor(photo, x, y, radius,strElem));
		}
	}
	return result_Image;
}
QColor Dilation::calculateNewPixelColor(QImage photo, int x, int y, int radius, int* strElem) {
	int size = 2 * radius + 1;
	float max = -1;
	QColor maxcolor;
	for (int i = -radius; i <= radius; i++) {
		for (int j = -radius; j <= radius; j++) {
			int idx = (i + radius) * size + j + radius;
			QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0), clamp<int>(y + i, photo.height() - 1, 0));
			if ((strElem[idx]==1)&&(color.red() + color.green() + color.blue() > max)) {
				max = color.red() + color.green() + color.blue();
				maxcolor = color;
			}
		}
	}
	return maxcolor;
}
//----------------------------------------------------------------------------------//
QImage Erosion::calculateNewImagePixMap(const QImage& photo, int radius, int* strElem) {
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			result_Image.setPixelColor(x, y, calculateNewPixelColor(photo, x, y, radius,strElem));
		}
	}
	return result_Image;
}
QColor Erosion::calculateNewPixelColor(QImage photo, int x, int y, int radius, int* strElem) {
	int size = 2 * radius + 1;
	float min = 1500;
	QColor mincolor;
	for (int i = -radius; i <= radius; i++) {
		for (int j = -radius; j <= radius; j++) {
			int idx = (i + radius) * size + j + radius;
			QColor color = photo.pixelColor(clamp<int>(x + j, photo.width() - 1, 0), clamp<int>(y + i, photo.height() - 1, 0));
			if ((strElem[idx] == 1) && (color.red() + color.green() + color.blue() <min)) {
				min = color.red() + color.green() + color.blue();
				mincolor = color;
			}
		}
	}
	return mincolor;
}
//----------------------------------------------------------------------------------//
QImage Opening::calculateNewImagePixMap(const QImage& photo, int radius,int* strElem) {
	Erosion* eros = new Erosion();
	QImage erosImage = eros->calculateNewImagePixMap(photo, radius,strElem);
	Dilation* dil = new Dilation();
	QImage dilImage = dil->calculateNewImagePixMap(erosImage, radius,strElem);
	return dilImage;
}
//----------------------------------------------------------------------------------//
QImage Closing::calculateNewImagePixMap(const QImage& photo, int radius,int* strElem) {
	Dilation* dil = new Dilation();
	QImage dilImage = dil->calculateNewImagePixMap(photo, radius,strElem);
	Erosion* eros = new Erosion();
	QImage erosImage = eros->calculateNewImagePixMap(dilImage, radius,strElem);
	return erosImage;
}
//----------------------------------------------------------------------------------//
QImage Grad::calculateNewImagePixMap(const QImage& photo, int _radius,int* strElem) {
	//grad(I)=(I+B)-(I-B);
	int* B;
	B = strElem;
	//(I+B):
	Dilation* dil = new Dilation();
	QImage dilImage = dil->calculateNewImagePixMap(photo, _radius, B);
	//(I-B):
	Erosion* eros = new Erosion();
	QImage erosImage = eros->calculateNewImagePixMap(photo, _radius, B);
	//(I+B)-(I-B):
	QImage resImage(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			int r, g, b;
			r = clamp(dilImage.pixelColor(x, y).red() - erosImage.pixelColor(x, y).red(), 255, 0);
			g = clamp(dilImage.pixelColor(x, y).green() - erosImage.pixelColor(x, y).green(), 255, 0);
			b = clamp(dilImage.pixelColor(x, y).blue() - erosImage.pixelColor(x, y).blue(), 255, 0);
			QColor col(r, g, b);
			resImage.setPixelColor(x, y, col);
		}
	}
	return resImage;
}
//----------------------------------------------------------------------------------//
QImage Median_Filter::calculateNewImagePixMap(const QImage& photo, int radius) {
	QImage result_Image(photo);
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			result_Image.setPixelColor(x, y, calculateNewPixelColor(photo, x, y, radius));
		}
	}
	return result_Image;
}
QColor Median_Filter::calculateNewPixelColor(QImage photo, int x, int y, int radius) {
	QColor* vector;
	int size = (2 * radius + 1) * (2 * radius + 1);
	vector = new QColor[(2 * radius + 1) * (2 * radius + 1)];
	int n = 0;
	for (int i = clamp(x - radius, photo.width()-1, 0); i <= clamp(x + radius, photo.width()-1, 0); i++) {
		for (int j = clamp(y - radius, photo.height()-1, 0); j <= clamp(y + radius, photo.height()-1, 0); j++) {
			vector[n] = photo.pixelColor(i, j);
			n++;
		}
	}
	qsort(vector, size, sizeof(QColor), ColorCompare);
	QColor res = vector[size / 2];
	delete vector;
	return res;
}
//----------------------------------------------------------------------------------//
QImage Gray_World::calculateNewImagePixMap(const QImage& photo) {
	QImage resImage(photo);
	int N = photo.width() * photo.height();
	float sumR = 0, sumG = 0, sumB = 0;
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			QColor color = photo.pixelColor(x, y);
			sumR += color.red();
			sumG += color.green();
			sumB += color.blue();
		}
	}
	float R1, G1, B1;
	R1 = sumR / N; G1 = sumG / N; B1 = sumB / N;
	float avg = (R1 + G1 + B1) / 3;
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			QColor color = photo.pixelColor(x, y);
			QColor resColor;
			resColor.setRgb(clamp((color.red() * avg / R1),255,0), clamp((color.green() * avg / G1),255,0), clamp((color.blue() * avg / B1),255,0));
			resImage.setPixelColor(x, y, resColor);
		}
	}
	return resImage;
}
//----------------------------------------------------------------------------------//
QImage Linear_Stretch:: calculateNewImagePixMap(const QImage& photo) {
	QImage resImage(photo);
	float max = -1500;
	float min = 1500;
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			QColor color = photo.pixelColor(x, y);
			if (0.3 * color.red() + 0.59 * color.green() + 0.11 * color.blue() > max) {
				max = 0.3 * color.red() + 0.59 * color.green() + 0.11 * color.blue();
			}
			if (0.3 * color.red() + 0.59 * color.green() + 0.11 * color.blue() < min) {
				min = 0.3 * color.red() + 0.59 * color.green() + 0.11 * color.blue();
			}
		}
	}
	for (int x = 0; x < photo.width(); x++) {
		for (int y = 0; y < photo.height(); y++) {
			QColor color = photo.pixelColor(x, y);
			QColor resColor;
			resColor.setRgb(clamp((color.red()-min)*(255-0)/(max-min), 255, 0), clamp((color.green() - min) * (255 - 0) / (max - min), 255, 0), clamp((color.blue() - min) * (255 - 0) / (max - min), 255, 0));
			resImage.setPixelColor(x, y, resColor);
		}
	}
	return resImage;
}