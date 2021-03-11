#pragma once
#pragma comment(lib,"opengl32.lib")
#include <qopengl.h>
#include <qopenglextrafunctions.h>
#include <qopenglwidget.h>
#include <qimage.h>
#include <qopengltexture.h>
#include <QOpenGLShaderProgram>
#include <qopenglfunctions_4_3_core.h>
#include <qevent.h>

class ShaderWidget :public QOpenGLWidget {
private:
	QOpenGLShaderProgram m_program;
	GLfloat* vert_data;
	int vert_data_location;
	int m_position;
	QOpenGLFunctions_4_3_Core* functions;
	GLuint ssbo = 0;
	struct Sphere {
		QVector3D position;
		float radius;
		QVector3D color;
		int material_idx;
	};
	struct Triangle
	{
		QVector3D v1;
		QVector3D v2;
		QVector3D v3;
		QVector3D color;
	};
	QVector3D light_pos;
	bool enable_additional_light;
	float brightness_coeff;
	struct Camera {
		QVector3D position;
		QVector3D view;
		QVector3D up;
		QVector3D side;
	};
	Camera camera;
protected:
	void initializeGL()override;
	void resizeGL(int nWidth, int nHeight)override;
	void paintGL()override;
public:
	ShaderWidget(QWidget* parent = 0);
	~ShaderWidget();

public slots:
	void keyPressEvent(QKeyEvent* event)override;
};

