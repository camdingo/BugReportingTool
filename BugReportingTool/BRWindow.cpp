#include "BRWindow.h"

#include <QDebug>

#include <QMainWindow>
#include <QSettings>
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QLineEdit>
#include <QCompleter>
#include <QTableView>
#include <QTextEdit>
#include <QHeaderView>

BRWindow::BRWindow()
	: _issuePending(false)
{
	init();
}

BRWindow::BRWindow(std::shared_ptr<BRModel> model)
	:	_issuePending(false)
{
	init();

	_completer->setModel(model.get());
	_issueTable->setModel(model.get());

}

BRWindow::~BRWindow()
{
	savePositionSize();
}

void BRWindow::init()
{
	loadPositionSize();

	createMenuBar();
	createStatusBar();
	createLayout();

	//Remove later
	//drawRedBorder(1000, 500, 600, 300);
}

void BRWindow::closeEvent(QCloseEvent* event)
{
	QMessageBox msgBox(this);

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

	savePositionSize();
}

void BRWindow::savePositionSize()
{
	QSettings qsettings("SAGE", "BugReportTool");

	qsettings.beginGroup("BRWindow");

	qsettings.setValue("geometry", saveGeometry());
	qsettings.setValue("savestate", saveState());
	qsettings.setValue("maximized", isMaximized());
	if (!isMaximized()) {
		qsettings.setValue("pos", pos());
		qsettings.setValue("size", size());
	}

	qsettings.endGroup();
}

void BRWindow::loadPositionSize()
{
	QSettings qsettings("SAGE", "BugReportTool");

	qsettings.beginGroup("mainwindow");

	restoreGeometry(qsettings.value("geometry", saveGeometry()).toByteArray());
	restoreState(qsettings.value("savestate", saveState()).toByteArray());
	move(qsettings.value("pos", pos()).toPoint());
	resize(qsettings.value("size", size()).toSize());
	if (qsettings.value("maximized", isMaximized()).toBool())
		showMaximized();

	qsettings.endGroup();
}

void BRWindow::createMenuBar()
{
	_fileMenu = new QMenu("&File");
	_createIssueAction = new QAction("Create Issue");
	_exportIssuesAction = new QAction("Export Issues");
	_exitAppAction = new QAction("Exit");
	
	_fileMenu->addAction(_createIssueAction);
	_fileMenu->addAction(_exportIssuesAction);
	_fileMenu->addAction(_exitAppAction);

	connect(_createIssueAction, SIGNAL(triggered()), this, SLOT(createIssueButtonPressed()));
	connect(_exportIssuesAction, SIGNAL(triggered()), this, SLOT(exportIssuesButtonPressed()));
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
	QVBoxLayout* vlayout = new QVBoxLayout();

	_completer = new QCompleter(this);

	_searchBar = new QLineEdit(this);
	_searchBar->setCompleter(_completer);
	vlayout->addWidget(_searchBar);

	_issueTable = new QTableView(this);
	_issueTable->horizontalHeader()->setStretchLastSection(true);
	_issueTable->verticalHeader()->hide();

	vlayout->addWidget(_issueTable);

	QHBoxLayout* hlayout = new QHBoxLayout();

	_detailView = new QTextEdit(this);
	_detailView->setDisabled(true);

	hlayout->addLayout(vlayout);
	hlayout->addWidget(_detailView);

	mainWidget->setLayout(hlayout);
	setCentralWidget(mainWidget);
}

void BRWindow::createIssueButtonPressed()
{
	qDebug() << "Create new issue button pressed";

}


void BRWindow::createIssue()
{

}

void BRWindow::exportIssuesButtonPressed()
{
	//Gather all data items and create the csv files for export
}

void BRWindow::drawRedBorder(int xPos, int yPos, int width, int height)
{
	QFrame* frame = new QFrame();
	frame->setFrameStyle(QFrame::Box | QFrame::Plain);
	frame->setWindowFlags(	Qt::FramelessWindowHint 
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