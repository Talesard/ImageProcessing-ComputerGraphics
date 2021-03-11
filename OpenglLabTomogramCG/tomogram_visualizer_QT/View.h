#pragma once
#pragma comment(lib,"opengl32.lib")
#include "Data.h"
#include <qinputdialog.h>
#include <qfiledialog.h>
#include <qopengl.h>
#include <qopenglextrafunctions.h>
#include <qopenglwidget.h>
#include <qimage.h>
#include <qopengltexture.h>
#include <qevent.h>
//#include <glut.h>									//что-то для OpenGL		glut.h устанавливался в VS вручную
//#include <gl/GL.h>								//что-то из этого 
//#include <gl/GLU.h>								//может быть лишним		upd: #pragma comment заменяет это

#define QT_TEXTURE_

class View : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
private:
	int max; int min;								//для насройки TransferFunction
	Data data;										//бинарный файл	
	int layer;										//текущий слой
	int projection_num;								//тип проеции: 1,2,3 (в каком разрезе смотрим)
	
	void up();										//управление слоями
	void down();									//управление слоями

	void setupTransferFunction(int _min, int _max);

	static const int MAX_WIN_SIZE = 1080;			//макс размер окна
	static const int MIN_WIN_SIZE = 250;			//мин размер окна

	int visualization_state = 0;					//типы визуализации (управление)
	static const int VISUALIZATION_QUADS = 0;
	static const int VISUALIZATION_QUADSTRIP = 1;
	static const int VISUALIZATION_TEXTURE = 2;

	void changeLayer();								//смена слоя 
	float TransferFunction(short value);			//перевод плотности в цвет
	void VisualizationQuads();						//квады
	void VisualizationQuadStrip();					//квады на 2-х вершинах (быстрее)
	void VisualizationTexture();					//одна текстура
	void genTextureImage();							//для предыдущего метода

	QImage textureImage;
	QOpenGLTexture* texture;

	friend int clamp(int val, int _min, int _max);	//вспомогательная функция
protected:											//сама рисовалка
	void initializeGL() override;
	void resizeGL(int nWidth, int nHeight) override;
	void paintGL() override;
public:
	void set_projection_num(int num);
	View(QWidget* parent);							//конструктор
	void LoadData(QString filename);				//загрузка файла в Data
	~View() {};										//деструктор
public slots:										
	void keyPressEvent(QKeyEvent* event)override;	//событие
};