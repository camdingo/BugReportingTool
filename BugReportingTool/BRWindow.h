#ifndef _BRWINDOW_
#define _BRWINDOW_

#include <QMainWindow>
#include <QTableView>
#include <QSortFilterProxyModel>

#include "BRModel.h"
#include "BRData.h"
#include "BRCreateDialog.h"

class QPushButton;
class QMenu;
class QLineEdit;
class QCompleter;
class QTextBrowser;
class QSortFilterProxyModel;


class ProxyModel : public QSortFilterProxyModel
{
public:
	ProxyModel(QWidget* parent) : QSortFilterProxyModel(parent) {}

private:
	bool ProxyModel::filterAcceptsRow(int row, const QModelIndex& parent) const;
};

//This whole subclass was created to allow for arrow key scrolling... yea yea, i wanted this feature!
class IssueTable : public QTableView
{
public:
	IssueTable(QWidget* parent) : QTableView(parent) {}

	void keyPressEvent(QKeyEvent* event);
};

class BRWindow : public QMainWindow
{
	Q_OBJECT

public:
	BRWindow();
	BRWindow(std::shared_ptr<BRModel> model);
	~BRWindow();

	void setDetailView(QString);
	void updateReport(BRData);

private slots:
	//override
	void customMenuRequested(const QPoint&);

	void filterTable(const QString&);
	void createIssueButtonPressed();
	void exportIssuesButtonPressed();
	void closeEvent(QCloseEvent*);
	void dialogIsFinished(int);
	void onTableClicked(const QModelIndex&);
	void editReport(const QModelIndex&);
	void eraseItem();

signals:
	void getDetailedView(int);
	void generateReport(BRData);
	void deleteSelectedReport(int);
	void retrieveSelectedReport(int);
	void sendUpdatedReport(BRData);

private:
	void init();

	void savePositionSize();
	void loadPositionSize();

	void createMenuBar();
	void createStatusBar();
	void createLayout();

	//TODO implement in Phase 2
	//void deleteIssue();
	//void editIssue();

	bool _updatingOlder;

	ProxyModel* _proxyModel;

	BRCreateDialog* _createIssueDialog;
	
	//Menu Bar
	QMenu *	_fileMenu;
	QAction *_createIssueAction;
	QAction* _exportIssuesAction;
	QAction *_exitAppAction;

	//Search box
	QLineEdit* _searchBar;
	
	//Buttons
	QPushButton *_createIssueButton;
	QPushButton *_deleteIssueButton;
	QPushButton *_editIssueButton;

	//Table
	IssueTable *_issueTable;

	//Detail View
	QTextBrowser *_detailView;

};

#endif //_BRWINDOW_