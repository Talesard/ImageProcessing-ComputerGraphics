#include "View.h"
#define QT_TEXTURE_
View::View(QWidget* parent) :QOpenGLWidget(parent), QOpenGLFunctions() {
	layer = 0;
	projection_num = 1;
	setFocus();						//чтобы нажимались кнопки
}

void View::initializeGL() {
	max = data.getMax();
	min = data.getMin();
	initializeOpenGLFunctions();
	glClearColor(1, 1, 1, 1);		//белый заполняющий цвет
	glShadeModel(GL_SMOOTH);		//сглаживание
	glMatrixMode(GL_MODELVIEW);		//модельно-видовая матрица
	glLoadIdentity();				//единичная матрица
	//способ наложения текстуры: цвет текстуры перекрывает цвет пикселя
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void View::resizeGL(int nWidth, int nHeight) {
	glMatrixMode(GL_PROJECTION);					//режим матрицы
	glLoadIdentity();								//единичная матрица
	int right, top;				
	switch (projection_num) {						//выбор параметром для орт. преобразования		
	case 1:
		right = data.getWidth() - 1;
		top = data.getHeight() - 1;
		break;
	case 2:
		right = data.getWidth() - 1;
		top = data.getDepth() - 1;
		break;
	case 3:
		right = data.getHeight() - 1;
		top = data.getDepth() - 1;
		break;
	default:
		//projection_num wrong value
		throw - 1;
	}
	glOrtho(0.0f, right, 0.0f, top, -1.0f, 1.0f);	//орт. преобразование
	glViewport(0, 0, nWidth, nHeight);				//окно обзора
	//update();										//не нужно в qt 5.4
}

void View::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//очистка буфферов (экрана)
	switch (visualization_state) {
	case VISUALIZATION_QUADS:
		VisualizationQuads();
		break;
	case VISUALIZATION_QUADSTRIP:
		VisualizationQuadStrip();
		break;
	case VISUALIZATION_TEXTURE:
		VisualizationTexture();
		break;
	default:
		//ошибка в режиме визуализации
		throw - 1;
		break;
	}
}

void View::LoadData(QString filename) {
	setWindowTitle("Tomogram VISUALIZATION_QUADS");
	data.readFile(filename);
	resize(clamp(data.getWidth(), MIN_WIN_SIZE, MAX_WIN_SIZE), clamp(data.getHeight(), MIN_WIN_SIZE, MAX_WIN_SIZE));
	update();
}

void View::set_projection_num(int num)
{
	projection_num = num;
}

void View::setupTransferFunction(int _min, int _max)
{
	if (_min == _max) { max++; } //избегаем деления на 0 в TransferFunction
	min = _min;
	max = _max;
}

float View::TransferFunction(short value) {
	float c = (value - min) * 1.f / (max - min);
	return c;
}

void View::VisualizationQuads() {
	float c;
	int w = data.getWidth();
	int h = data.getHeight();
	int d = data.getDepth();
	switch (projection_num){
	case 1:
		glBegin(GL_QUADS);
		for (int y = 0; y < (h - 1); y++) {
			for (int x = 0; x < (w - 1); x++) {
				c = TransferFunction(data[layer * w * h + y * w + x]);
				glColor3f(c, c, c);
				glVertex2i(x, y);

				c = TransferFunction(data[layer * w * h + (y + 1) * w + x]);
				glColor3f(c, c, c);
				glVertex2i(x, y + 1);

				c = TransferFunction(data[layer * w * h + (y + 1) * w + x + 1]);
				glColor3f(c, c, c);
				glVertex2i(x + 1, y + 1);

				c = TransferFunction(data[layer * w * h + y * w + x + 1]);
				glColor3f(c, c, c);
				glVertex2i(x + 1, y);
			}
		}
		glEnd();
		break;
	case 2:
		glBegin(GL_QUADS);
		for (int z = 0; z < (d - 1); z++) {
			for (int x = 0; x < (w - 1); x++) {
				c = TransferFunction(data[z * w * h + layer * w + x]);
				glColor3f(c, c, c);
				glVertex2i(x, z);

				c = TransferFunction(data[(z + 1) * w * h + (layer) * (w)+x]);
				glColor3f(c, c, c);
				glVertex2i(x, z + 1);

				c = TransferFunction(data[(z + 1) * w * h + (layer) * (w)+x + 1]);
				glColor3f(c, c, c);
				glVertex2i(x + 1, z + 1);

				c = TransferFunction(data[z * w * h + layer * w + x + 1]);
				glColor3f(c, c, c);
				glVertex2i(x + 1, z);
			}
		}
		glEnd();
		break;
	case 3:
		glBegin(GL_QUADS);
		for (int z = 0; z < (d - 1); z++) {
			for (int y = 0; y < (h - 1); y++) {
				c = TransferFunction(data[z*w*h+y*w+layer]);
				glColor3f(c, c, c);
				glVertex2i(y,z);

				c = TransferFunction(data[(z+1) * w * h + y * w + layer]);
				glColor3f(c, c, c);
				glVertex2i( y ,z+1);

				c = TransferFunction(data[(z + 1) * w * h +(y+1)*w+layer ]);
				glColor3f(c, c, c);
				glVertex2i(y + 1,z+1);

				c = TransferFunction(data[z*w*h+(y+1)*w+layer]);
				glColor3f(c, c, c);
				glVertex2i(y+1,z);
			}
		}
		glEnd();
		break;
	default:
		//projection_num wrong value
		throw - 1;
	}
}

void View::VisualizationQuadStrip() {
	float c;
	int w = data.getWidth();
	int h = data.getHeight();
	int d = data.getDepth();
	switch (projection_num) {
	case 1:
		for (int y = 0; y < h - 1; y++) {
			glBegin(GL_QUAD_STRIP);

			c = TransferFunction(data[layer * w * h + y * w]);
			glColor3f(c, c, c);
			glVertex2i(0, y);

			c = TransferFunction(data[layer * w * h + (y + 1) * w]);
			glColor3f(c, c, c);
			glVertex2i(0, y + 1);

			for (int x = 0; x < w - 1; x++) {
				c = TransferFunction(data[layer * w * h + (y + 1) * w + x + 1]);
				glColor3f(c, c, c);
				glVertex2i(x + 1, y + 1);

				c = TransferFunction(data[layer * w * h + y * w + x + 1]);
				glColor3f(c, c, c);
				glVertex2i(x + 1, y);
			}
			glEnd();
		}
		break;
	case 2:
		for (int z = 0; z < d - 1; z++) {
			glBegin(GL_QUAD_STRIP);
			c = TransferFunction(data[z*w*h+layer*w]);
			glColor3f(c, c, c);
			glVertex2i(0, z);

			c = TransferFunction(data[(z+1)*w*h+layer*w]);
			glColor3f(c, c, c);
			glVertex2i(0, z + 1);

			for (int x = 0; x < w - 1; x++) {
				c = TransferFunction(data[(z + 1) * w * h + (layer) * (w)+x + 1]);
				glColor3f(c, c, c);
				glVertex2i(x + 1, z + 1);

				c = TransferFunction(data[z * w * h + layer * w + x + 1]);
				glColor3f(c, c, c);
				glVertex2i(x + 1, z);
			}
			glEnd();
		}
		break;
	case 3:
		for (int z = 0; z < d - 1; z++) {
			glBegin(GL_QUAD_STRIP);
			c = TransferFunction(data[z * w * h + layer]);
			glColor3f(c, c, c);
			glVertex2i(0, z);

			c = TransferFunction(data[(z + 1) * w * h + layer]);
			glColor3f(c, c, c);
			glVertex2i(0, z + 1);

			for (int y = 0; y < h - 1; y++) {
				c = TransferFunction(data[(z+1)*w*h+(y+1)*w+layer]);
				glColor3f(c, c, c);
				glVertex2i(y + 1, z + 1);

				c = TransferFunction(data[z*w*h+(y+1)*w+layer]);
				glColor3f(c, c, c);
				glVertex2i(y+ 1, z);
			}
			glEnd();
		}
		break;
	default:
		//projection_num wrong value
		throw - 1;
		break;
	}
}

void View::genTextureImage() {
	int w = data.getWidth();
	int h = data.getHeight();
	int d = data.getDepth();
	switch (projection_num) {
	case 1:
	textureImage = QImage(w, h, QImage::Format_RGB32);
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				int c = clamp((int)(255 * TransferFunction(data[layer * w * h + w * y + x])), 0, 255);
				QColor qc(c, c, c);
				textureImage.setPixelColor(x, y, qc);
			}
		}
		break;
	case 2:
		textureImage = QImage(w, d, QImage::Format_RGB32);
		for (int z = 0; z < d; z++) {
			for (int x = 0; x < w; x++) {
				int c = clamp((int)(255 * TransferFunction(data[z*w*h+layer*w+x])), 0, 255);
				QColor qc(c, c, c);
				textureImage.setPixelColor(x, z, qc);
			}
		}
		break;
	case 3:
		textureImage = QImage(h, d, QImage::Format_RGB32);
		for (int z = 0; z < d; z++) {
			for (int y = 0; y < h; y++) {
				int c = clamp((int)(255 * TransferFunction(data[z * w * h + y*w+layer])), 0, 255);
				QColor qc(c, c, c);
				textureImage.setPixelColor(y, z, qc);
			}
		}
		break;
	default:
		//projection_num wrong value
		throw - 1;
		break;
	}
	texture = new QOpenGLTexture(textureImage);
	texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
	texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void View::VisualizationTexture() {
	switch (projection_num) {
	case 1:
		glEnable(GL_TEXTURE_2D);
		texture->bind();
		glBegin(GL_QUADS);

		glTexCoord2f(0, 0);
		glVertex2i(0, 0);

		glTexCoord2f(0, 1);
		glVertex2i(0, data.getHeight());

		glTexCoord2f(1, 1);
		glVertex2d(data.getWidth(), data.getHeight());

		glTexCoord2f(1, 0);
		glVertex2i(data.getWidth(), 0);

		glEnd();
		glDisable(GL_TEXTURE_2D);
		break;
	case 2:
		glEnable(GL_TEXTURE_2D);
		texture->bind();
		glBegin(GL_QUADS);

		glTexCoord2f(0, 0);
		glVertex2i(0, 0);

		glTexCoord2f(0, 1);
		glVertex2i(0, data.getDepth());

		glTexCoord2f(1, 1);
		glVertex2d(data.getWidth(), data.getDepth());

		glTexCoord2f(1, 0);
		glVertex2i(data.getWidth(), 0);

		glEnd();
		glDisable(GL_TEXTURE_2D);
		break;
	case 3:
		glEnable(GL_TEXTURE_2D);
		texture->bind();
		glBegin(GL_QUADS);

		glTexCoord2f(0, 0);
		glVertex2i(0, 0);

		glTexCoord2f(0, 1);
		glVertex2i(0, data.getDepth());

		glTexCoord2f(1, 1);
		glVertex2d(data.getHeight(), data.getDepth());

		glTexCoord2f(1, 0);
		glVertex2i(data.getHeight(), 0);

		glEnd();
		glDisable(GL_TEXTURE_2D);
		break;
	default:
		//projection_num wrong value
		throw - 1;
	}
}

void View::changeLayer() {
	if (visualization_state == VISUALIZATION_TEXTURE) {
		genTextureImage();
	}
}

void View::up() {
	int limit;
	switch (projection_num) {
	case 1: limit = data.getDepth(); break;
	case 2: limit = data.getHeight(); break;
	case 3: limit = data.getWidth(); break;
	default:
		//projection_num wrong value
		throw - 1;
		break;
	}
	if (layer + 1 < limit) {
		layer++;
	}
	update();
}

void View::down() {
	if (layer - 1 >= 0) {
		layer--;
	}
	update();
}

void View::keyPressEvent(QKeyEvent* event) {
	if (event->nativeVirtualKey() == Qt::Key_W) {								//Слой вверх
		up();
		changeLayer();
	}
	else if (event->nativeVirtualKey() == Qt::Key_S) {							//Слой вниз
		down();
		changeLayer();
	}
	else if (event->nativeVirtualKey() == Qt::Key_N) {							//Изменение режима визуализации
		visualization_state = (visualization_state + 1) % 3;
		switch (visualization_state) {
		case VISUALIZATION_QUADS:
			setWindowTitle("Tomogram VISUALIZATION_QUADS");
			break;
		case VISUALIZATION_QUADSTRIP:
			setWindowTitle("Tomogram VISUALIZATION_QUADSTRIP");
			break;
		case VISUALIZATION_TEXTURE:
			setWindowTitle("Tomogram VISUALIZATION_TEXTURE");
			genTextureImage();
			break;
		default:
			setWindowTitle("Tomogram ERROR_VISUALIZATION");
			break;
		}
	}
	else if (event->nativeVirtualKey() == Qt::Key_T) {							//Настройка TransferFucntion
		bool ok1=false;
		int value1 = min;
		int value2 = max;
		value1 = QInputDialog::getInt(this, QString::fromUtf8("TF MIN"),
			QString::fromUtf8("MIN:"), data.getMin(), -10000,10000 , 1, &ok1);
		if (ok1) {
			setupTransferFunction(value1, max);
		}
		bool ok2 = false;
		value2 = QInputDialog::getInt(this, QString::fromUtf8("TF MAX"),
			QString::fromUtf8("MAX:"), data.getMax(), -10000, 10000, 1, &ok2);
		if (ok2) {
			setupTransferFunction(min, value2);
		}
		changeLayer();
	}
	update();
}

int clamp(int val, int _min, int _max) {		//Вспомогательная функция
	if (val > _max) return _max;
	if (val < _min) return _min;
	return val;
}