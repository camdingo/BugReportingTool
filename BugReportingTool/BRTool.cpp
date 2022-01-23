#include <QDebug>
#include <QApplication>

#include "BRWindow.h"

using namespace std;

int main(int argc, char** argv)
{
	qDebug() << "Bug Reporting Tool Starting.";

	QApplication app(argc, argv);

	QCoreApplication::setOrganizationName("Bug Report Tool");
	QCoreApplication::setApplicationName("Bug Report Tool");
	QCoreApplication::setApplicationVersion(QT_VERSION_STR);

	BRWindow mainWindow;
	mainWindow.show();

	app.exec();

	return 0;
}
