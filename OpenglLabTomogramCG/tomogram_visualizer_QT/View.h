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
//#include <glut.h>									//���-�� ��� OpenGL		glut.h �������������� � VS �������
//#include <gl/GL.h>								//���-�� �� ����� 
//#include <gl/GLU.h>								//����� ���� ������		upd: #pragma comment �������� ���

#define QT_TEXTURE_

class View : public QOpenGLWidget, protected QOpenGLFunctions {
	Q_OBJECT
private:
	int max; int min;								//��� �������� TransferFunction
	Data data;										//�������� ����	
	int layer;										//������� ����
	int projection_num;								//��� �������: 1,2,3 (� ����� ������� �������)
	
	void up();										//���������� ������
	void down();									//���������� ������

	void setupTransferFunction(int _min, int _max);

	static const int MAX_WIN_SIZE = 1080;			//���� ������ ����
	static const int MIN_WIN_SIZE = 250;			//��� ������ ����

	int visualization_state = 0;					//���� ������������ (����������)
	static const int VISUALIZATION_QUADS = 0;
	static const int VISUALIZATION_QUADSTRIP = 1;
	static const int VISUALIZATION_TEXTURE = 2;

	void changeLayer();								//����� ���� 
	float TransferFunction(short value);			//������� ��������� � ����
	void VisualizationQuads();						//�����
	void VisualizationQuadStrip();					//����� �� 2-� �������� (�������)
	void VisualizationTexture();					//���� ��������
	void genTextureImage();							//��� ����������� ������

	QImage textureImage;
	QOpenGLTexture* texture;

	friend int clamp(int val, int _min, int _max);	//��������������� �������
protected:											//���� ���������
	void initializeGL() override;
	void resizeGL(int nWidth, int nHeight) override;
	void paintGL() override;
public:
	void set_projection_num(int num);
	View(QWidget* parent);							//�����������
	void LoadData(QString filename);				//�������� ����� � Data
	~View() {};										//����������
public slots:										
	void keyPressEvent(QKeyEvent* event)override;	//�������
};