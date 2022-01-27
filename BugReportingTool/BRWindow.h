#ifndef _BRWINDOW_
#define _BRWINDOW_

#include <QMainWindow>
#include <memory>
#include "BRModel.h"

class QPushButton;
class QMenu;
class QLineEdit;
class QCompleter;
class QTableView;
class QTextEdit;

class BRWindow : public QMainWindow
{
	Q_OBJECT

public:
	BRWindow();
	BRWindow(std::shared_ptr<BRModel> model);
	~BRWindow();

private slots:
	void createIssueButtonPressed();
	void exportIssuesButtonPressed();
	void closeEvent(QCloseEvent* event);

private:
	void init();

	void savePositionSize();
	void loadPositionSize();

	void createMenuBar();
	void createStatusBar();
	void createLayout();

	void createIssue();

	void drawRedBorder(int xPos, int yPos, int width, int height);

	//TODO implement in Phase 2
	//void deleteIssue();
	//void editIssue();
	
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
	QTextEdit *_detailView;

	bool _issuePending;

};

#endif //_BRWINDOW_