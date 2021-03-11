#pragma once
#include <iostream>
#include <fstream>
#include <qstring.h>
#include <qdebug.h>

class Data
{
private:
	float scaleX;
	float scaleY;
	float scaleZ;

	short* arr;

	int width;
	int height;
	int depth;

	short max;
	short min;
public:
	int getMin() { return min; }

	int getMax() { return max; }

	int getWidth(){return width;}

	int getHeight() {return height;}

	int getDepth() {return depth;}

	Data() :width(0), height(0), depth(0), min(0), max(0), scaleX(0), scaleY(0), scaleZ(0) {
		arr == nullptr;
	}
	~Data() {
		delete arr;
	}
	void MinMax() {
		min = arr[0];
		max = arr[0];
		for (int i = 0; i < width * height * depth; i++) {
			if (arr[i] < min) min = arr[i];
			if (arr[i] > max) max = arr[i];
		}
	}
	int readFile(QString filename) {
		std::ifstream file;
		file.open(filename.toStdString(), std::ios::binary | std::ios::in);
		if (!file.is_open()) {
			qDebug() << "file can't be open!!!\n";
		}
		int x, y, z;
		qDebug() << QString("file was opened");
		file.read((char*)&x, sizeof(int));
		file.read((char*)&y, sizeof(int));
		file.read((char*)&z, sizeof(int));
		if (x == 0 || y == 0 || z == 0) {
			qDebug() << QString("wrong datasize");
			file.close();
			return -1;
		}
		file.read((char*)&scaleX, sizeof(float));
		file.read((char*)&scaleY, sizeof(float));
		file.read((char*)&scaleZ, sizeof(float));
		if (arr != nullptr) {
			delete[]arr;
		}
		width = x;
		height = y;
		depth = z;
		long sizeArr = width * height * depth;
		arr = new short[sizeArr];
		file.read((char*)arr, sizeArr*sizeof(short));
		file.close();
		qDebug() << QString("file was closed");
		MinMax();
		return 0;
	}

	short& operator[](const int ind) {
		assert(ind >= 0 && ind < width * height * depth);
		return arr[ind];
	}
};

