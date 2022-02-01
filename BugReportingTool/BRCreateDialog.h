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

	void generatePendingIssue();

signals:

public slots:
	void formModifiedHandler();
	void createIssueClicked();

private:
	virtual void closeEvent(QCloseEvent* event);

	bool _formModified;

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
