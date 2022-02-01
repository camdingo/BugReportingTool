#ifndef _BRWINDOW_
#define _BRWINDOW_

#include <QMainWindow>

#include "BRModel.h"
#include "BRData.h"
#include "BRCreateDialog.h"

class QPushButton;
class QMenu;
class QLineEdit;
class QCompleter;
class QTableView;
class QTextBrowser;


class BRWindow : public QMainWindow
{
	Q_OBJECT

public:
	BRWindow();
	BRWindow(std::shared_ptr<BRModel> model);
	~BRWindow();

	void setDetailView(QString);

private slots:
	void createIssueButtonPressed();
	void exportIssuesButtonPressed();
	void closeEvent(QCloseEvent*);
	void dialogIsFinished(int);
	void onTableClicked(const QModelIndex&);
	void editItem(const QModelIndex&);
	void editItem();
	void customMenuRequested(const QPoint&);

signals:
	void getDetailedView(int);
	void generateReport(BRData);
	void editReport();

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

	BRCreateDialog* _createIssueDialog;
	
	//Menu Bar
	QMenu *	_fileMenu;
	QAction *_createIssueAction;
	QAction* _exportIssuesAction;
	QAction *_exitAppAction;

	//Search box
	QLineEdit* _searchBar;
	QCompleter* _completer;
	
	//Buttons
	QPushButton *_createIssueButton;
	QPushButton *_deleteIssueButton;
	QPushButton *_editIssueButton;

	//Table
	QTableView *_issueTable;

	//Detail View
	QTextBrowser *_detailView;

};

#endif //_BRWINDOW_