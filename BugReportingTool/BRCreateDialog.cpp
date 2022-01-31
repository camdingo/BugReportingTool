#include "BRCreateDialog.h"

#include <QMessageBox>
#include <QCloseEvent>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QSpacerItem>

#include "BRData.h"


BRCreateDialog::BRCreateDialog(QWidget* parent)
	:	QDialog(parent)
	,	_formModified(false)
{
	qRegisterMetaType<BRData>("BRData");

	resize(620, 480);

	QGridLayout* mainLayout = new QGridLayout(this);

	//Summary
	QLabel* summaryLabel = new QLabel("Summary");
	_summary = new QLineEdit(this);

	mainLayout->addWidget(summaryLabel, 0, 0);
	mainLayout->addWidget(_summary, 0, 1);


	//Description
	QLabel* desLabel = new QLabel("Description");
	_description = new QTextEdit(this);

	mainLayout->addWidget(desLabel, 1, 0);
	mainLayout->addWidget(_description, 1, 1);

	//String
	QLabel* stringLabel = new QLabel("String");
	_string = new QComboBox(this);
	_string->addItems({"String 1", "String 2", "String 3", "String 4", "Engineering 1", "Engineering 2"});

	mainLayout->addWidget(stringLabel, 2, 0);
	mainLayout->addWidget(_string, 2, 1);


	//Priority 
	QLabel* prioLabel = new QLabel("Priority");
	_priority = new QComboBox(this);
	_priority->addItems({ "Minor", "Major", "Critical", "Blocker" });

	mainLayout->addWidget(prioLabel, 3, 0);
	mainLayout->addWidget(_priority, 3, 1);


	//Space Between Priority and Attachments
	QSpacerItem* attachspacer = new QSpacerItem(33, 33, QSizePolicy::Fixed, QSizePolicy::Fixed);
	mainLayout->addItem(attachspacer, 4, 0, 1, 1);


	//Attachments area
	QLabel* attachmentsLabel = new QLabel("Attachments");
	mainLayout->addWidget(attachmentsLabel, 5, 0);

	_ssvWidget = new ScreenShotVideoWidget(this);
	mainLayout->addWidget(_ssvWidget, 5, 1);


	//Screencap/Video Buttons
	QHBoxLayout* ssvButtonLayout = new QHBoxLayout();
	_addScreenshotButton = new QPushButton("Add Screenshot");
	_addVideoButton = new QPushButton("Add Video");

	ssvButtonLayout->addWidget(_addScreenshotButton);
	ssvButtonLayout->addWidget(_addVideoButton);
	mainLayout->addLayout(ssvButtonLayout, 6, 1);


	//Space Between Screencap/Video Buttons and Create Button
	QSpacerItem* spacer = new QSpacerItem(150, 150, QSizePolicy::Fixed, QSizePolicy::Fixed);
	mainLayout->addItem(spacer,7,0,2,2);


	//Create
	_createIssueButton = new QPushButton("Create Report");
	mainLayout->addWidget(_createIssueButton, 8, 0, 1, 2);

	setLayout(mainLayout);

	createConnections();
}

BRCreateDialog::~BRCreateDialog()
{

}

void BRCreateDialog::createConnections()
{
	connect(_summary, SIGNAL(textChanged(const QString&)), this, SLOT(formModifiedHandler()));

	connect(_createIssueButton, SIGNAL(clicked()), this, SLOT(createIssueClicked()));
}

void BRCreateDialog::generatePendingIssue()
{
	QString originator; //get from access control
	QString affectedVersion;
	QString component;
	//_pendingIssue = BRData(0, QString("SAGE"), _summary->text(), QString(""), originator, affectedVersion, _string->currentText(), QString("DOMES"),
	//	BRData::ISSUE_TYPE::DR, component, _description->toPlainText(), _priority->currentText(), BRData::CATEGORY::BUG);
}

void BRCreateDialog::createIssueClicked()
{
	//create br data
	generatePendingIssue();

	//close dialog?
	accept();
}

void BRCreateDialog::formModifiedHandler()
{
	if (	_summary->text() == ""
		&&	_description->toPlainText() == ""
		&& _ssvWidget->count() == 0
		)
	{
		_formModified = false;
	}
	else
	{
		_formModified = true;
	}
}

void BRCreateDialog::closeEvent(QCloseEvent* event)
{
	QMessageBox msgBox(this);

	if (!_formModified)
		return;

	msgBox.setText("Issue Creation In Progress!");
	msgBox.setInformativeText("Do you want to Create the report?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	msgBox.setDefaultButton(QMessageBox::Yes);
	

	int ret = msgBox.exec();

	if (ret == QMessageBox::Cancel)
	{
		event->ignore();
	}
	else if (ret == QMessageBox::No)
	{
		//delete current working form
	}
	else if (ret == QMessageBox::Yes)
	{
		event->accept();

	}

	emit finished(1);
}