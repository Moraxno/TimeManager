#include "TimeManager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TimeManager w;
	w.show();
	return a.exec();
}
