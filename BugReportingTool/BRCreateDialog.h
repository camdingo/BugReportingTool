#ifndef _BRCREATEDIALOG_
#define _BRCREATEDIALOG_

#include <QDialog>

#include "BRData.h"
#include "screenshotVideoWidget.h"

class QLineEdit;
class QTextEdit;
class QComboBox;
class QListWidget;

class BRCreateDialog : public QDialog
{
	Q_OBJECT

public:
	BRCreateDialog(QWidget* parent);
	~BRCreateDialog();

	void createConnections();
	BRData getPendingIssue() { return _pendingIssue; }

	void loadReport(BRData);

	void loadComponents();
	void generatePendingIssue();

signals:

public slots:
	void formModifiedHandler();
	void createIssueClicked();

private:
	virtual void closeEvent(QCloseEvent* event);

	bool _update;
	int _updateIssueId;
	bool _formModified;

	std::map < std::string, std::list<std::string> > _modelComponents; // ie egplite1: streamer1 streamer2
																	   //    egplite2: streamer1 streamer2

	//Hidden fields
	QString _originator; //get from access control

	//Entry fields
	QLineEdit* _summary;
	QLineEdit* _affectedVersion;
	QTextEdit* _description;
	QComboBox* _string;
	QComboBox* _priority;
	QComboBox* _component;
	QComboBox* _category;

	ScreenShotVideoWidget* _ssvWidget;

	QPushButton* _addScreenshotButton;
	QPushButton* _addVideoButton;
	QPushButton* _createIssueButton;

	//Exported data
	BRData _pendingIssue;
};

#endif // _BRCREATEDIALOG_
