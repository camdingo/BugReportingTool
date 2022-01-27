#ifndef _BRCREATEDIALOG_
#define _BRCREATEDIALOG_

#include <QDialog>

#include "BRData.h"

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
};

#endif
