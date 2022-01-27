#include "BRCreateDialog.h"

#include <QMessageBox>
#include <QCloseEvent>

#include "BRData.h"


BRCreateDialog::BRCreateDialog(QWidget* parent)
	:	QDialog(parent)
	,	_formModified(false)
{
	qRegisterMetaType<BRData>("BRData");
}

BRCreateDialog::~BRCreateDialog()
{

}

void BRCreateDialog::closeEvent(QCloseEvent* event)
{
	QMessageBox msgBox(this);

	if (!_formModified)
		return;

	msgBox.setText("Issue Creation In Progress!");
	msgBox.setInformativeText("Do you want to save your changes?");
	msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Save);
	

	int ret = msgBox.exec();

	if (ret == QMessageBox::Cancel)
	{
		event->ignore();
	}
	else if (ret == QMessageBox::Discard)
	{
		//special handle for clearing the form
	}
	else if (ret == QMessageBox::Yes)
	{
		//attempt to create issue
		//need to validate fields
	}

	BRData issue;
	emit finished(issue);
}