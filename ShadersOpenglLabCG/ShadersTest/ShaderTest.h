#pragma once

#include <QtWidgets/QWidget>
#include "ui_ShaderTest.h"

class ShaderTest : public QWidget
{
	Q_OBJECT

public:
	ShaderTest(QWidget *parent = Q_NULLPTR);

private:
	Ui::ShaderTestClass ui;
};
