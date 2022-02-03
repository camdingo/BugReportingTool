#include <QDebug>
#include <QStyleFactory>
#include <QApplication>

#include "BRModel.h"
#include "BRWindow.h"
#include "BRController.h"

using namespace std;

//Dark Theme
void setStyle(QApplication* application)
{
	// set style
	application->setStyle(QStyleFactory::create("Fusion"));

	// increase font size for better reading
	QFont defaultFont = QApplication::font();
	defaultFont.setPointSize(defaultFont.pointSize() + 2);
	application->setFont(defaultFont);

	// modify palette to dark
	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::WindowText, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(127, 127, 127));
	darkPalette.setColor(QPalette::Base, QColor(42, 42, 42));
	darkPalette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
	darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
	darkPalette.setColor(QPalette::ToolTipText, Qt::white);
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
	darkPalette.setColor(QPalette::Dark, QColor(35, 35, 35));
	darkPalette.setColor(QPalette::Shadow, QColor(20, 20, 20));
	darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127, 127, 127));
	darkPalette.setColor(QPalette::BrightText, Qt::red);
	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80, 80, 80));
	darkPalette.setColor(QPalette::HighlightedText, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(127, 127, 127));

	application->setPalette(darkPalette);

}

/*
* TODO
* search bar
* export issues ... ie tar all new issue folders since last export for SRE transfer
* add modelName to creation dialog
* pull components from model for creation dialog
* add ffmpeg calls to screen shot and video cap
* attachment opening/playing
* creation of issues/attachments to disk... ie /...../<issueNumber>/*csv , *jpg , *mp4
* load issues/ attachments from disk
* write last issue number to persistence file
* lock file for sync purpose when getting next issue number
* populate originator with access control info
* access control export and delete actions (Base only?)
* more logging???
* auto populate affected version when user enters which string
* edit previous reports
*/

int main(int argc, char** argv)
{
	qDebug() << "Bug Reporting Tool Starting.";

	QApplication app(argc, argv);

	QCoreApplication::setOrganizationName("Bug Report Tool");
	QCoreApplication::setApplicationName("Bug Report Tool");
	QCoreApplication::setApplicationVersion(QT_VERSION_STR);


	std::shared_ptr<BRModel> model = std::make_shared<BRModel>();
	std::shared_ptr<BRWindow> mainWindow = std::make_shared<BRWindow>(model);

	BRController controller(model, mainWindow);

	mainWindow->show();

	setStyle(&app);

	app.exec();

	return 0;
}
