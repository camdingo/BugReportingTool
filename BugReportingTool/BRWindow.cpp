#include "BRWindow.h"

#include <QDebug>

#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>

BRWindow::BRWindow()
	:_issuePending(false)
{
	init();
}

void BRWindow::init()
{
	createMenuBar();
	createStatusBar();
	createLayout();
}

void BRWindow::closeEvent(QCloseEvent* event)
{
	QMessageBox msgBox;

	if (_issuePending)
	{
		msgBox.setText("The document has been modified.");
		msgBox.setInformativeText("Do you want to save your changes?");
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
	}
	else
	{
		msgBox.setText("Are you sure you want to exit?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::Yes);
	}

	int ret = msgBox.exec();

	if (ret == QMessageBox::Cancel
		|| ret == QMessageBox::No)
	{
		event->ignore();
	}
	else if (ret == QMessageBox::Discard)
	{
		//special handle for clearing the form
	}
	else if (ret == QMessageBox::Yes)
	{

	}
	else if (ret == QMessageBox::Save)
	{
		//saveIssue();
		_issuePending = false;
	}
}

void BRWindow::createMenuBar()
{
	_fileMenu = new QMenu("&File");
	_createIssueAction = new QAction("Create Issue");
	_exitAppAction = new QAction("Exit");
	
	_fileMenu->addAction(_createIssueAction);
	_fileMenu->addAction(_exitAppAction);

	connect(_createIssueAction, SIGNAL(triggered()), this, SLOT(createIssueButtonPressed()));
	connect(_exitAppAction, SIGNAL(triggered()), this, SLOT(close()));


	menuBar()->addMenu(_fileMenu);
}

void BRWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}

void BRWindow::createLayout() 
{
	QWidget* mainWidget = new QWidget(this);
	QVBoxLayout* layout = new QVBoxLayout();
	_createIssueButton = new QPushButton("Create New Issue");
	connect(_createIssueButton, SIGNAL(clicked()), this, SLOT(createIssueButtonPressed()));

	layout->addWidget(_createIssueButton);

	mainWidget->setLayout(layout);
	setCentralWidget(mainWidget);
}

void BRWindow::createIssueButtonPressed()
{
	qDebug() << "Create new issue button pressed";
}


void BRWindow::createIssue()
{

}