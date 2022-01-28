#ifndef _BRCREATEDIALOG_
#define _BRCREATEDIALOG_

#include <QDialog>

#include "BRData.h"

class QLineEdit;
class QComboBox;

class BRCreateDialog : public QDialog
{
	Q_OBJECT

public:
	BRCreateDialog(QWidget* parent);
	~BRCreateDialog();


signals:
	void finished(BRData);

private:
	virtual void closeEvent(QCloseEvent* event);

	bool _formModified;

	//Entry fields
	QLineEdit* _summary;
	QLineEdit* _description;
	QComboBox* _string;
	QComboBox* _priority;


};

#endif
