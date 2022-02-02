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
#include <QTextBrowser>
#include <QHeaderView>

#include "BRCreateDialog.h"

BRWindow::BRWindow()
{
	init();
}

BRWindow::BRWindow(std::shared_ptr<BRModel> model)
{
	init();

	_completer->setModel(model.get());
	_issueTable->setModel(model.get());

	resize(1280, 720);
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
}

void BRWindow::closeEvent(QCloseEvent* event)
{
	QMessageBox msgBox(this);

	msgBox.setText("Are you sure you want to exit?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);

	int ret = msgBox.exec();

	if (ret == QMessageBox::No)
		event->ignore();


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
	_issueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	_issueTable->horizontalHeader()->setStretchLastSection(true);
	_issueTable->verticalHeader()->hide();
	_issueTable->setContextMenuPolicy(Qt::CustomContextMenu);
	_issueTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	_issueTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	_issueTable->setAlternatingRowColors(true);

	connect(_issueTable, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
	connect(_issueTable, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(editReport(const QModelIndex&)));

	connect(_issueTable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenuRequested(QPoint)));

	vlayout->addWidget(_issueTable);

	QHBoxLayout* hlayout = new QHBoxLayout();

	_detailView = new QTextBrowser(this);
	_detailView->setDisabled(true);

	hlayout->addLayout(vlayout);
	hlayout->addWidget(_detailView);

	mainWidget->setLayout(hlayout);
	setCentralWidget(mainWidget);
}

void BRWindow::onTableClicked(const QModelIndex& index)
{
	if (index.isValid()) 
	{
		emit getDetailedView(index.row());
	}
}

void BRWindow::editReport(const QModelIndex& index)
{
	//refactort later...dupe code
	//open dialog, but load all older data from that row



	//_createIssueDialog = new BRCreateDialog(this, report);
	//connect(_createIssueDialog, SIGNAL(finished(int)), this, SLOT(dialogIsFinished(int)));

	//_createIssueDialog->exec();

}

void BRWindow::customMenuRequested(const QPoint& pos)
{
	// Handle global position
	QPoint globalPos = _issueTable->mapToGlobal(pos);
	
	//No idea why this works this way, using pos of the click to get index of table...
	//but if you look at where we draw the menu, it uses globalpos... weird...
	onTableClicked(_issueTable->indexAt(pos));

	// Create menu and insert some actions
	QMenu myMenu;
	myMenu.addAction("Delete", this, SLOT(eraseItem()));

	// Show context menu at handling position
	myMenu.exec(globalPos);
}


void BRWindow::setDetailView(QString details)
{
	_detailView->setHtml(details);
}

void BRWindow::createIssueButtonPressed()
{
	_createIssueDialog = new BRCreateDialog(this);
	connect(_createIssueDialog, SIGNAL(finished(int)), this, SLOT(dialogIsFinished(int)));

	//wait here until dialog is closed either via accept or finished
	_createIssueDialog->exec();
}

void BRWindow::dialogIsFinished(int result)
{
	BRData pendingIssue = _createIssueDialog->getPendingIssue();

	emit generateReport(pendingIssue);
}

void BRWindow::exportIssuesButtonPressed()
{
	//Gather all data items and create the csv files for export
}
