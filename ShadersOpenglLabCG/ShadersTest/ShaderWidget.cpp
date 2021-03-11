#include "ShaderWidget.h"

GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };


ShaderWidget::ShaderWidget(QWidget* parent):QOpenGLWidget(parent),vert_data_location(0) {
	vert_data = new GLfloat[12];
	//x y z
	vert_data[0] = -1.0f;	vert_data[1] = -1.0f;	vert_data[2] = 0.0f;
	vert_data[3] = 1.0f;	vert_data[4] = -1.0f;	vert_data[5] = 0.0f;
	vert_data[6] = 1.0f;	vert_data[7] = 1.0f;	vert_data[8] = 0.0f;
	vert_data[9] = -1.0f;	vert_data[10] = 1.0f;	vert_data[11] = 0.0f;
}

ShaderWidget::~ShaderWidget() {
	delete[] vert_data;
}

void ShaderWidget::initializeGL() {
	setWindowTitle("EasyCamera: WASD    FullCamera: TGFHRY    Light: IKJLUO     AddLight: space     Brightness: ZC");

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	QOpenGLShader vShader(QOpenGLShader::Vertex);
	vShader.compileSourceFile("raytracing.vert");

	QOpenGLShader fShader(QOpenGLShader::Fragment);
	fShader.compileSourceFile("raytracing.frag");

	m_program.addShader(&vShader);
	m_program.addShader(&fShader);
	if (!m_program.link()) {
		qWarning("Shader linker error\n");
		return;
	}
	qDebug() << "Log program";
	qDebug() << m_program.log();

	vert_data_location = m_program.attributeLocation("vertex");
	if (!m_program.bind()) {
		qWarning("shader bind error\n");
		return;
	}
	light_pos = QVector3D(1, 0, -8);
	m_program.setUniformValue("light_pos", light_pos);
	enable_additional_light = false;
	m_program.setUniformValue("enable_additional_light", enable_additional_light);
	brightness_coeff = 1.0;
	m_program.setUniformValue("brightness_coeff", brightness_coeff);
	camera.position = QVector3D(0.0, 0.0, -10);
	camera.view = QVector3D(0.0, 0.0, 1.0);
	camera.up = QVector3D(0.0, 1.0, 0.0);
	camera.side = QVector3D(1.0, 0.0, 0.0);
	m_program.setUniformValue("camera.position", camera.position);
	m_program.setUniformValue("camera.view", camera.view);
	m_program.setUniformValue("camera.up", camera.up);
	m_program.setUniformValue("camera.side", camera.side);
	
	m_program.setUniformValue("scale", QVector2D(width(), height()));

	//pyramid
	//side1
	m_program.setUniformValue("triangle[0].v1", QVector3D(-2, -2, -6));
	m_program.setUniformValue("triangle[0].v2", QVector3D(2, -2, -6));
	m_program.setUniformValue("triangle[0].v3", QVector3D(0, 1, -5));
	m_program.setUniformValue("triangle[0].color", QVector3D(1.0, 0.4, 1.0));
	//side2
	m_program.setUniformValue("triangle[1].v1", QVector3D (- 2, -2, -6));
	m_program.setUniformValue("triangle[1].v2", QVector3D(2, -2, -6));
	m_program.setUniformValue("triangle[1].v3", QVector3D(0, -2, -2));
	m_program.setUniformValue("triangle[1].color", QVector3D(1.0, 0.4, 1.0));
	//side3
	m_program.setUniformValue("triangle[2].v1", QVector3D(0, 1, -5));
	m_program.setUniformValue("triangle[2].v2", QVector3D(2, -2, -6));
	m_program.setUniformValue("triangle[2].v3", QVector3D(0, -2, -2));
	m_program.setUniformValue("triangle[2].color", QVector3D(1.0, 0.4, 1.0));
	//side4
	m_program.setUniformValue("triangle[3].v1", QVector3D(0, 1, -5));
	m_program.setUniformValue("triangle[3].v2", QVector3D(0, -2, -2));
	m_program.setUniformValue("triangle[3].v3", QVector3D(-2, -2, -6));
	m_program.setUniformValue("triangle[3].color", QVector3D(1.0, 0.4, 1.0));
	
	//cube
	//side1
	m_program.setUniformValue("square[0].v1", QVector3D(3, 0, 0));
	m_program.setUniformValue("square[0].v2", QVector3D(6, 0, 0));
	m_program.setUniformValue("square[0].v3", QVector3D(6, 3, 0));
	m_program.setUniformValue("square[0].v4", QVector3D(3, 3, 0));
	m_program.setUniformValue("square[0].color", QVector3D(0.3, 0.5, 0.7));
	//side2
	m_program.setUniformValue("square[1].v1", QVector3D(6, 0, 0));
	m_program.setUniformValue("square[1].v2", QVector3D(6, 0, 3));
	m_program.setUniformValue("square[1].v3", QVector3D(6, 3, 3));
	m_program.setUniformValue("square[1].v4", QVector3D(6, 3, 0));
	m_program.setUniformValue("square[1].color", QVector3D(0.3, 0.5, 0.7));
	//side3
	m_program.setUniformValue("square[2].v1", QVector3D(6, 0, 3));
	m_program.setUniformValue("square[2].v2", QVector3D(3, 0, 3));
	m_program.setUniformValue("square[2].v3", QVector3D(3, 3, 3));
	m_program.setUniformValue("square[2].v4", QVector3D(6, 3, 3));
	m_program.setUniformValue("square[2].color", QVector3D(0.3, 0.5, 0.7));
	//side4
	m_program.setUniformValue("square[3].v1", QVector3D(3, 0, 3));
	m_program.setUniformValue("square[3].v2", QVector3D(3, 0, 0));
	m_program.setUniformValue("square[3].v3", QVector3D(3, 3, 0));
	m_program.setUniformValue("square[3].v4", QVector3D(3, 3, 3));
	m_program.setUniformValue("square[3].color", QVector3D(0.3, 0.5, 0.7));
	//side5
	m_program.setUniformValue("square[4].v1", QVector3D(3, 0, 0));
	m_program.setUniformValue("square[4].v2", QVector3D(6, 0, 0));
	m_program.setUniformValue("square[4].v3", QVector3D(6, 0, 3));
	m_program.setUniformValue("square[4].v4", QVector3D(3, 0, 3));
	m_program.setUniformValue("square[4].color", QVector3D(0.3, 0.5, 0.7));
	//side6
	m_program.setUniformValue("square[5].v1", QVector3D(3, 3, 0));
	m_program.setUniformValue("square[5].v2", QVector3D(6, 3, 0));
	m_program.setUniformValue("square[5].v3", QVector3D(6, 3, 3));
	m_program.setUniformValue("square[5].v4", QVector3D(3, 3, 3));
	m_program.setUniformValue("square[5].color", QVector3D(0.3, 0.5, 0.7));

	m_program.release();

	std::vector<Sphere> all_spheres;
	all_spheres.push_back(Sphere{ QVector3D(-1,0,10),6,QVector3D(1.0,0.4,0),0 });
	all_spheres.push_back(Sphere{ QVector3D(2,0,-3),1,QVector3D(0.0,0.6,0.2),0 });
	all_spheres.push_back(Sphere{ QVector3D(-1,0,10),1000,QVector3D(0.0,0.44,0.74),0 }); //���
	
	functions = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
	functions->glGenBuffers(1, &ssbo);
	functions->glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	functions->glBufferData(GL_SHADER_STORAGE_BUFFER, all_spheres.size() * sizeof(Sphere), all_spheres.data(), GL_DYNAMIC_COPY);
	functions->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
}

void ShaderWidget::resizeGL(int nWidth, int nHeight) {
	glViewport(0, 0, nWidth, nHeight);
	if (!m_program.bind()) {
		qWarning("shader bind error\n");
	}
	m_program.setUniformValue("scale", QVector2D(width(), height()));
	//qDebug() <<"scale = "<<QVector2D(width(), height());
	m_program.release();
	update();
}

void ShaderWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (!m_program.bind()) {
		return;
	}

	m_program.enableAttributeArray(vert_data_location);
	m_program.setAttributeArray(vert_data_location, vert_data, 3);

	glDrawArrays(GL_QUADS, 0, 4);

	m_program.disableAttributeArray(vert_data_location);
	m_program.setUniformValue("light_pos", light_pos);
	m_program.setUniformValue("camera.position", camera.position);
	m_program.setUniformValue("camera.view", camera.view);
	m_program.setUniformValue("camera.up", camera.up);
	m_program.setUniformValue("camera.side", camera.side);
	m_program.setUniformValue("enable_additional_light", enable_additional_light);
	m_program.setUniformValue("brightness_coeff", brightness_coeff);
	m_program.release();
}

void ShaderWidget::keyPressEvent(QKeyEvent* event) {
	float lx, ly, lz;
	lx = light_pos.x();
	ly = light_pos.y();
	lz = light_pos.z();
	float light_delta = 0.5;
	int cx, cy, cz;
	cx = camera.position.x();
	cy = camera.position.y();
	cz = camera.position.z();
	int cam_delta = 1;
	float angle = 0.02;

	///////////////////////Light control/////////////////////

	if (event->nativeVirtualKey() == Qt::Key_I) {
		ly += light_delta;
	}
	else if (event->nativeVirtualKey() == Qt::Key_K) {
		ly -= light_delta;
	}
	else if (event->nativeVirtualKey() == Qt::Key_J) {
		lx -= light_delta;
	}
	else if (event->nativeVirtualKey() == Qt::Key_L) {
		lx += light_delta;
	}
	else if (event->nativeVirtualKey() == Qt::Key_U) {
		lz -= light_delta;
	}
	else if (event->nativeVirtualKey() == Qt::Key_O) {
		lz += light_delta;
	}

	////////////////////////FullCamera control///////////////

	else if (event->nativeVirtualKey() == Qt::Key_T) {
		cy += cam_delta;
		camera.position = QVector3D(cx, cy, cz);
	}
	else if (event->nativeVirtualKey() == Qt::Key_G) {
		cy -= cam_delta;
		camera.position = QVector3D(cx, cy, cz);
	}
	else if (event->nativeVirtualKey() == Qt::Key_F) {
		cx -= cam_delta;
		camera.position = QVector3D(cx, cy, cz);
	}
	else if (event->nativeVirtualKey() == Qt::Key_H) {
		cx += cam_delta;
		camera.position = QVector3D(cx, cy, cz);
	}
	else if (event->nativeVirtualKey() == Qt::Key_R) {
		cz -= cam_delta;
		camera.position = QVector3D(cx, cy, cz);
	}
	else if (event->nativeVirtualKey() == Qt::Key_Y) {
		cz += cam_delta;
		camera.position = QVector3D(cx, cy, cz);
	}

	///////////////////////EasyCamera control////////////////

	else if (event->nativeVirtualKey() == Qt::Key_W) {
		camera.position += camera.view * 0.2;
	}
	else if (event->nativeVirtualKey() == Qt::Key_S) {
		camera.position -= camera.view * 0.2;
	}
	else if (event->nativeVirtualKey() == Qt::Key_A) {
		camera.view.setX(camera.view.x() * cos(angle) - camera.view.z() * sin(angle));
		camera.view.setZ(camera.view.x() * sin(angle) + camera.view.z() * cos(angle));
		camera.view.normalize();
		camera.side.setX(camera.side.x() * cos(angle) - camera.side.z() * sin(angle));
		camera.side.setZ(camera.side.x() * sin(angle) + camera.side.z() * cos(angle));
		camera.side.normalize();
	}
	else if (event->nativeVirtualKey() == Qt::Key_D) {
		camera.view.setX(camera.view.x() * cos(-angle) - camera.view.z() * sin(-angle));
		camera.view.setZ(camera.view.x() * sin(-angle) + camera.view.z() * cos(-angle));
		camera.view.normalize();
		camera.side.setX(camera.side.x() * cos(-angle) - camera.side.z() * sin(-angle));
		camera.side.setZ(camera.side.x() * sin(-angle) + camera.side.z() * cos(-angle));
		camera.side.normalize();
	}

	//SPECIAL LIGHT CONTROL

	else if (event->nativeVirtualKey() == Qt::Key_Space) {
		enable_additional_light = !enable_additional_light;
	}
	else if (event->nativeVirtualKey() == Qt::Key_C) {
		brightness_coeff += 0.1;
	}
	else if (event->nativeVirtualKey() == Qt::Key_Z) {
		brightness_coeff -= 0.1;
	}


	light_pos = QVector3D(lx, ly, lz);
	qDebug() << "********************************************";
	qDebug() << "light_pos = " << light_pos;
	qDebug() << "camera_pos = " << camera.position;
	qDebug() << "camera_view=" << camera.view;
	qDebug() << "camera_side=" << camera.side;
	update();
}
