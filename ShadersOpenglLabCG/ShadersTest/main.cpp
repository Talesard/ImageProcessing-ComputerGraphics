#include "ShaderTest.h"
#include"ShaderWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ShaderWidget w(NULL);
	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setVersion(3, 5);
	format.setProfile(QSurfaceFormat::CoreProfile);
	w.setFormat(format);
	w.show();
	return a.exec();
}
