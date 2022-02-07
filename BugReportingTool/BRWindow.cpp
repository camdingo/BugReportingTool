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
#include <QTextBrowser>
#include <QHeaderView>
#include <QSortFilterProxyModel>

#include "BRCreateDialog.h"

//-------------------------------------------------------------------------------------------------------
//Proxy Model Class Functions
//-------------------------------------------------------------------------------------------------------
bool ProxyModel::filterAcceptsRow(int row, const QModelIndex& parent) const
{
	QModelIndex issueNum = sourceModel()->index(row, 0, parent);
	QModelIndex summary = sourceModel()->index(row, 1, parent);
	QModelIndex desc = sourceModel()->index(row, 2, parent);
	QModelIndex prio = sourceModel()->index(row, 3, parent);
	QModelIndex version = sourceModel()->index(row, 4, parent);
	QModelIndex originator = sourceModel()->index(row, 5, parent);

	return (sourceModel()->data(issueNum).toString().contains(filterRegExp())
		|| sourceModel()->data(summary).toString().contains(filterRegExp())
		|| sourceModel()->data(desc, Qt::UserRole).toString().contains(filterRegExp())
		|| sourceModel()->data(prio, Qt::UserRole).toString().contains(filterRegExp())
		|| sourceModel()->data(version, Qt::UserRole).toString().contains(filterRegExp())
		|| sourceModel()->data(originator, Qt::UserRole).toString().contains(filterRegExp())
		);
}

//-------------------------------------------------------------------------------------------------------
//Issue Table Class Functions
//This is silly, but i wanted to be able to scroll with my up and down arrows
//-------------------------------------------------------------------------------------------------------
void IssueTable::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Up
		|| event->key() == Qt::Key_Down)
	{
		QTableView::keyPressEvent(event);
	
		emit clicked(selectedIndexes().front());
	}
}

//-------------------------------------------------------------------------------------------------------
//BRWindow Class Functions
//-------------------------------------------------------------------------------------------------------
BRWindow::BRWindow()
{
	init();
}

BRWindow::BRWindow(std::shared_ptr<BRModel> model)
	:	_updatingOlder(false)
{
	init();

	_proxyModel = new ProxyModel(this);
	_proxyModel->setSourceModel(model.get());
	_issueTable->setModel(_proxyModel);

	//Hide columns that done matter
	_issueTable->hideColumn(2);
	_issueTable->hideColumn(3);
	_issueTable->hideColumn(4);
	_issueTable->hideColumn(5);

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

	_searchBar = new QLineEdit(this);
	vlayout->addWidget(_searchBar);
	connect(_searchBar, SIGNAL(textChanged(const QString&)), this, SLOT(filterTable(const QString&)));

	_issueTable = new IssueTable(this);
	_issueTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	_issueTable->horizontalHeader()->setStretchLastSection(true);
	_issueTable->verticalHeader()->hide();
	_issueTable->setContextMenuPolicy(Qt::CustomContextMenu);
	_issueTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	_issueTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	_issueTable->setAlternatingRowColors(true);
	_issueTable->hideColumn(2);

	connect(_issueTable, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
	connect(_issueTable, SIGNAL(entered(const QModelIndex&)), this, SLOT(onTableClicked(const QModelIndex&)));
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
		emit getDetailedView(_proxyModel->mapToSource(index).row());
	}
}

void BRWindow::editReport(const QModelIndex& index)
{
	if (index.isValid())
	{
		emit retrieveSelectedReport(_proxyModel->mapToSource(index).row());
	}
}

void BRWindow::filterTable(const QString& searchPhrase)
{
	_proxyModel->setFilterRegExp(QRegExp(searchPhrase, Qt::CaseInsensitive, QRegExp::FixedString));
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

void BRWindow::eraseItem()
{
	QMessageBox msgBox(this);

	msgBox.setText("Are you sure you want to erase this report?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);

	int ret = msgBox.exec();

	if (ret == QMessageBox::Yes)
	{
		QModelIndexList selection = _issueTable->selectionModel()->selectedRows();
		if (selection.count() == 1)
		{
			QModelIndex index = selection.at(0);
			emit deleteSelectedReport(_proxyModel->mapToSource(index).row());
		}
	}
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

void BRWindow::updateReport(BRData report)
{
	_updatingOlder = true;
	_createIssueDialog = new BRCreateDialog(this);
	_createIssueDialog->loadReport(report);
	connect(_createIssueDialog, SIGNAL(finished(int)), this, SLOT(dialogIsFinished(int)));

	_createIssueDialog->exec();
}

void BRWindow::dialogIsFinished(int result)
{
	BRData pendingIssue = _createIssueDialog->getPendingIssue();

	if (!_updatingOlder)
	{
		qDebug() << "BRWindow Creating Report";
		emit generateReport(pendingIssue);
	}
	else
	{
		qDebug() << "BRWindow Updating Report"; 
		//TODO
		// no need to grab new report id
		emit sendUpdatedReport(pendingIssue);
		_updatingOlder = false;
	}
}

void BRWindow::exportIssuesButtonPressed()
{
	//Gather all data items and create the csv files for export
}
