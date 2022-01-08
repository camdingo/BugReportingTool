#include <QDebug>
#include  <QApplication>

using namespace std;

int main(int argc, char** argv)
{
	qDebug() << "Bug Reporting Tool Starting.";

	//Create the Model/Window

	QApplication app(argc, argv);
	app.exec();

	return 0;
}
