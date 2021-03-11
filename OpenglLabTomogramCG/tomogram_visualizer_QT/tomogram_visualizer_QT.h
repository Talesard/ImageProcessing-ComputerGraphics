#pragma once

#include <QtWidgets/QWidget>
#include "ui_tomogram_visualizer_QT.h"

class tomogram_visualizer_QT : public QWidget
{
	Q_OBJECT

public:
	tomogram_visualizer_QT(QWidget *parent = Q_NULLPTR);

private:
	Ui::tomogram_visualizer_QTClass ui;
};
