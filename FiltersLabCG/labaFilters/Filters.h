#pragma once
#include <qimage.h>
class Filters
{
public:
	Filters() {};
	~Filters() {};
	virtual QImage calculateNewImagePixMap(const QImage& photo, int radius) = 0;
};
//----------------------------------------------------------------------------------//
class Invert_Filter : public Filters {
public:
	Invert_Filter() {};
	~Invert_Filter() {};
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
};
//----------------------------------------------------------------------------------//
class Matrix_Filter :public Filters {
public:
	float* vector;
	int mRadius;
	Matrix_Filter(int radius = 1) :mRadius(radius) {};
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
	QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
};
//----------------------------------------------------------------------------------//
class Blur_Filter :public Matrix_Filter {
public:
	Blur_Filter() {
			int size = 2 * mRadius + 1;
			vector = new float[size * size];
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					vector[i * size + j] = float(1.0f / (float(size * size))); 
				}
			}
		}
	~Blur_Filter(){
		delete vector;
	}
};
//----------------------------------------------------------------------------------//
class Gaussian_Blur_Filter :public Matrix_Filter {
public:
	Gaussian_Blur_Filter() {
		createGaussianVector(3, 2);
	}
	~Gaussian_Blur_Filter() {};
	void createGaussianVector(int radius, int sigma);
};
//----------------------------------------------------------------------------------//
class Gray_Scale_Filter : public Filters {
public:
	Gray_Scale_Filter() {};
	~Gray_Scale_Filter() {};
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
	QColor calculateNewPixelColor(QImage photo, int x, int y);
};
//----------------------------------------------------------------------------------//
class Sepia_Filter : public Filters {
public:
	Sepia_Filter() {};
	~Sepia_Filter() {};
	QImage calculateNewImagePixMap(const QImage& photo, int k);
	QColor calculateNewPixelColor(QImage photo, int x, int y,int k);
};
//----------------------------------------------------------------------------------//
class Brihtness_Filter :public Filters {
public:
	Brihtness_Filter() {};
	~Brihtness_Filter() {};
	QImage calculateNewImagePixMap(const QImage& photo,int k);
};
//----------------------------------------------------------------------------------//
class Sobel_Filter{
public:
	float* vector_x;
	float* vector_y;
	Sobel_Filter() {
		vector_x = new float[3 * 3];
		vector_x[0] = -1; vector_x[3] = -2; vector_x[6] = -1;
		vector_x[1] =  0; vector_x[4] =  0; vector_x[7] =  0;
		vector_x[2] =  1; vector_x[5] =  2; vector_x[8] =  1;

		vector_y = new float[3 * 3];
		vector_y[0] = -1; vector_y[3] = 0; vector_y[6] = 1;
		vector_y[1] = -2; vector_y[4] = 0; vector_y[7] = 2;
		vector_y[2] = -1; vector_y[5] = 0; vector_y[8] = 1;
	}
	~Sobel_Filter() {
		delete vector_x;
		delete vector_y;
	}
	QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
};
//----------------------------------------------------------------------------------//
class Sharpness_Filter:public Matrix_Filter {
public:
	Sharpness_Filter() {
		vector = new float[3 * 3];
		vector[0] = 0; vector[3] = -1; vector[6] = 0;
		vector[1] = -1; vector[4] = 5; vector[7] = -1;
		vector[2] = 0; vector[5] = -1; vector[8] = 0;
	}
	~Sharpness_Filter() {
		delete vector;
	}
};
//----------------------------------------------------------------------------------//
class Embossing_Filter {
public:
	float* vector;
	int mRadius;
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
	QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
	Embossing_Filter(int radius = 1) : mRadius(radius) {
		vector = new float[3 * 3];
		//ÑÓÌÌÀ ÝËÅÌÅÍÒÎÂ ÌÀÒÐÈÖÛ=0, ×ÒÎ ÄÅËÀÒÜ Ñ ÍÎÐÌÈÐÎÂÊÎÉ?
		vector[0] = 0; vector[3] = 1; vector[6] = 0;
		vector[1] = 1; vector[4] = 0; vector[7] = -1;
		vector[2] = 0; vector[5] = -1; vector[8] = 0;
	}
	~Embossing_Filter() {
		delete vector;
	}
};

//----------------------------------------------------------------------------------//
class Rotation_Filter :public Filters {
public:
	Rotation_Filter() {};
	~Rotation_Filter() {};
	QImage calculateNewImagePixMap(const QImage& photo, int radius); //radius ~ angle
};

//----------------------------------------------------------------------------------//
class Waves_Filter :public Filters {
public:
	Waves_Filter() {};
	~Waves_Filter() {};
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
};
//----------------------------------------------------------------------------------//
class Sharpness2_Filter :public Matrix_Filter {
public:
	Sharpness2_Filter() {
		vector = new float[3 * 3];
		vector[0] = -1; vector[3] = -1; vector[6] = -1;
		vector[1] = -1; vector[4] = 9; vector[7] = -1;
		vector[2] = -1; vector[5] = -1; vector[8] = -1;
	}
	~Sharpness2_Filter() {
		delete vector;
	}
};
//----------------------------------------------------------------------------------//
class Dilation {
public:
	int mRadius;
	QImage calculateNewImagePixMap(const QImage& photo, int radius, int* strElem);
	QColor calculateNewPixelColor(QImage photo, int x, int y, int radius, int* strElem);
	Dilation(int radius = 1) : mRadius(radius) {
	}
};
//----------------------------------------------------------------------------------//
class Erosion {
public:
	int mRadius;
	QImage calculateNewImagePixMap(const QImage& photo, int radius, int* strElem);
	QColor calculateNewPixelColor(QImage photo, int x, int y, int radius, int* strElem);
	Erosion(int radius = 1) : mRadius(radius) {
	}
};
//----------------------------------------------------------------------------------//
class Opening{
public:
	QImage calculateNewImagePixMap(const QImage& photo, int radius,int* strElem);
};
//----------------------------------------------------------------------------------//
class Closing {
public:
	QImage calculateNewImagePixMap(const QImage& photo, int radius,int* strElem);
};
//----------------------------------------------------------------------------------//
class Grad {
public:
	QImage calculateNewImagePixMap(const QImage& photo, int radius, int* strElem);
};
//----------------------------------------------------------------------------------//
class Median_Filter {
public:
	int mRadius;
	QImage calculateNewImagePixMap(const QImage& photo, int radius);
	QColor calculateNewPixelColor(QImage photo, int x, int y, int radius);
	Median_Filter(int radius = 1) : mRadius(radius) {}
	~Median_Filter() {}
};

class Gray_World{
public:
	QImage calculateNewImagePixMap(const QImage& photo);
	Gray_World() {};
	~Gray_World() {};
};
class Linear_Stretch {
public:
	QImage calculateNewImagePixMap(const QImage& photo);
};