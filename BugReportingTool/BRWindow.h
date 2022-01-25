#include <QMainWindow>
#include <memory>
#include "BRModel.h"

class QPushButton;
class QMenu;
class QLineEdit;
class QCompleter;

class BRWindow : public QMainWindow
{
	Q_OBJECT

public:
	BRWindow();

private slots:
	void createIssueButtonPressed();
	void closeEvent(QCloseEvent* event);

private:
	void init();
	void createMenuBar();
	void createStatusBar();
	void createLayout();

	void createIssue();

	//TODO implement in Phase 2
	//void deleteIssue();
	//void editIssue();
	
	std::shared_ptr<BRModel> _model;

	//Menu Bar
	QMenu *	_fileMenu;
	QAction *_createIssueAction;
	QAction *_exitAppAction;

	//Search box
	QLineEdit* _searchBar;
	QCompleter* _completer;
	
	//Buttons
	QPushButton *_createIssueButton;
	QPushButton *_deleteIssueButton;
	QPushButton *_editIssueButton;



	bool _issuePending;

};