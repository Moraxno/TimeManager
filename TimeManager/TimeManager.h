#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TimeManager.h"

class TimeManager : public QMainWindow
{
	Q_OBJECT

public:
	TimeManager(QWidget *parent = Q_NULLPTR);

private:
	Ui::TimeManagerClass ui;
};
