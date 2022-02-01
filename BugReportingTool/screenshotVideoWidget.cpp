#include "screenshotVideoWidget.h"

#include <QHBoxLayout>
#include <QMenu>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>

#include <array>
#include <stdexcept>
#include <stdio.h>

ScreenShotVideoWidget::ScreenShotVideoWidget(QWidget* parent)
{
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenuRequested(QPoint)));

	setSelectionMode(SelectionMode::SingleSelection);

	setAlternatingRowColors(true);


	//CTR testing, remove later
	for (int i = 0; i < 5; ++i)
	{
		QListWidgetItem* item = new QListWidgetItem("test" + QString::number(i));
		QString fileLocation("/msic/egfeg/gere");
		item->setData(Qt::UserRole, fileLocation);
		addItem(item);

	}
}

ScreenShotVideoWidget::~ScreenShotVideoWidget() 
{

}

void ScreenShotVideoWidget::customMenuRequested(const QPoint& pos)
{
	// Handle global position
	QPoint globalPos = this->mapToGlobal(pos);

	// Create menu and insert some actions
	QMenu myMenu;
	myMenu.addAction("Open", this, SLOT(openItems()));
	myMenu.addAction("Delete", this, SLOT(eraseItems()));

	// Show context menu at handling position
	myMenu.exec(globalPos);
}

void ScreenShotVideoWidget::openItems()
{

}

void ScreenShotVideoWidget::eraseItems()
{

	QMessageBox msgBox(this);

	msgBox.setText("Are you sure you want to delete selected items?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);

	int ret = msgBox.exec();

	if (ret == QMessageBox::No)
	{
		return;
	}
	else if (ret == QMessageBox::Yes)
	{
		auto items = selectedItems();
		foreach(QListWidgetItem * item, items)
		{
			delete takeItem(row(item));
		}
	}

}

std::string grabXwinInfo() 
{
	//std::array<char, 128> buffer;
	std::string result;
	//std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("xwininfo", "r"), pclose);
	//if (!pipe) {
	//	throw std::runtime_error("popen() failed!");
	//}
	//while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
	//	result += buffer.data();
	//}
	return result;
}

void getWindowDimensions(int & absX, int & absY, int & width, int & height)
{
	std::string xwininfo = grabXwinInfo();

	absX = std::stoi(xwininfo.substr(xwininfo.find("Absolute upper-left X: ") + 23, 4));
	absY = std::stoi(xwininfo.substr(xwininfo.find("Absolute upper-left Y: ") + 23, 4));

	width = std::stoi(xwininfo.substr(xwininfo.find("Width: ") + 7, 4));
	height = std::stoi(xwininfo.substr(xwininfo.find("Height: ") + 8, 4));

}

void ScreenShotVideoWidget::createScreenShot()
{
	QMessageBox prompt(this);

	prompt.setWindowTitle("ScreenShot");
	prompt.addButton("Fullscreen", QMessageBox::ButtonRole::YesRole);
	prompt.addButton("Select Window", QMessageBox::ButtonRole::NoRole);
	prompt.addButton(QMessageBox::StandardButton::Cancel);

	int ret = prompt.exec();

	if (ret == QMessageBox::Yes)
	{
		//cap fullscreen

	}
	else if (ret == QMessageBox::No)
	{
		//cap window
		int absX, absY, width, height;
		getWindowDimensions(absX, absY, width, height);

		//contruct ffmpeg cmd line args
	}

}

void ScreenShotVideoWidget::createVideo()
{
	QMessageBox prompt(this);

	prompt.setWindowTitle("Video Capture");
	prompt.addButton("Fullscreen", QMessageBox::ButtonRole::YesRole);
	prompt.addButton("Select Window", QMessageBox::ButtonRole::NoRole);
	prompt.addButton(QMessageBox::StandardButton::Cancel);

	int ret = prompt.exec();

	if (ret == QMessageBox::Yes)
	{
		//cap fullscreen

	}
	else if (ret == QMessageBox::No)
	{
		//cap window
		int absX, absY, width, height;
		getWindowDimensions(absX, absY, width, height);

		//contruct ffmpeg cmd line args
	}

	
}

void ScreenShotVideoWidget::drawRedBorder(int xPos, int yPos, int width, int height)
{
	QFrame* frame = new QFrame();
	frame->setFrameStyle(QFrame::Box | QFrame::Plain);
	frame->setWindowFlags(Qt::FramelessWindowHint
		| Qt::Tool
		| Qt::WindowTransparentForInput
		| Qt::WindowDoesNotAcceptFocus
		| Qt::WindowStaysOnTopHint);

	frame->setGeometry(xPos, yPos, width, height);

	// Set a solid green thick border.
	frame->setObjectName("testframe");
	frame->setStyleSheet("#testframe {border: 5px solid red;}");

	// IMPORTANT: A QRegion's coordinates are relative to the widget it's used in. This is not documented.
	QRegion wholeFrameRegion(0, 0, width, height);
	QRegion innerFrameRegion = wholeFrameRegion.subtracted(QRegion(5, 5, width - 10, height - 10));
	frame->setMask(innerFrameRegion);
	frame->setWindowOpacity(0.5);
	frame->show();
}