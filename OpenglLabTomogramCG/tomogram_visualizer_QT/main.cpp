#include "tomogram_visualizer_QT.h"
#include <QtWidgets/QApplication>
#include <QFileDialog>
#include "View.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	View w(NULL);
	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setVersion(3, 5);
	format.setProfile(QSurfaceFormat::CoreProfile);
	w.setFormat(format);
	bool ok1 = false;
	int value1 = 1;
	do {
		value1 = QInputDialog::getInt(NULL, QString::fromUtf8("View"),
			QString::fromUtf8("Num"), 1, 1, 3, 1, &ok1);
	} while (!(ok1 && (value1 == 1 || value1 == 2 || value1 == 3)));
	if (ok1) {
		w.set_projection_num(value1);
	}
	QString filename = QFileDialog::getOpenFileName(NULL,QString("Open File"),QString("."),QString("Binary files (*.bin)"));
	w.LoadData(filename);
	w.show();
	return a.exec();
}
