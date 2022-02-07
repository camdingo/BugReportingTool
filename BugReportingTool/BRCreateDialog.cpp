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
#include <QDebug>

#include "BRData.h"

QStringList STRING_NAMES = { "String 1", "String 2", "String 3", "String 4", "Engineering 1", "Engineering 2" };
QStringList CATEGORIES = { "Bug", "Feature Request", "Usability Issue", "Crash", "Other" };
QStringList PRIORITY = { "Minor", "Major", "Critical", "Blocker" };
QStringList COMPONENTS = { "Unknown" }; // TODO fill this in differently will real items

BRCreateDialog::BRCreateDialog(QWidget* parent)
	:	QDialog(parent)
	,	_formModified(false)
	,	_update(false)
{
	qRegisterMetaType<BRData>("BRData");

	resize(620, 480);

	QGridLayout* mainLayout = new QGridLayout(this);

	//Summary
	QLabel* summaryLabel = new QLabel("Summary");
	_summary = new QLineEdit(this);

	mainLayout->addWidget(summaryLabel, 0, 0);
	mainLayout->addWidget(_summary, 0, 1);

	//Space Between Screencap/Video Buttons and Create Button
	QSpacerItem* summarySpacer = new QSpacerItem(50, 50, QSizePolicy::Fixed, QSizePolicy::Fixed);
	mainLayout->addItem(summarySpacer, 1, 0, 2, 2);

	//String
	QLabel* stringLabel = new QLabel("String");
	_string = new QComboBox(this);
	_string->addItems(STRING_NAMES);

	mainLayout->addWidget(stringLabel, 2, 0);
	mainLayout->addWidget(_string, 2, 1);


	//Affected Version
	QLabel* versionLabel = new QLabel("Affected Version");
	_affectedVersion = new QLineEdit(this);

	mainLayout->addWidget(versionLabel, 3, 0);
	mainLayout->addWidget(_affectedVersion, 3, 1);


	//Category
	QLabel* categoryLabel = new QLabel("Category");
	_category = new QComboBox(this);
	_category->addItems(CATEGORIES);

	mainLayout->addWidget(categoryLabel, 4, 0);
	mainLayout->addWidget(_category, 4, 1);

	//Component
	QLabel* componentLabel = new QLabel("Component");
	_component = new QComboBox(this);
	_component->addItems(COMPONENTS); //Dynamically add this later

	mainLayout->addWidget(componentLabel, 5, 0);
	mainLayout->addWidget(_component, 5, 1);


	//Priority 
	QLabel* prioLabel = new QLabel("Priority");
	_priority = new QComboBox(this);
	_priority->addItems(PRIORITY);

	mainLayout->addWidget(prioLabel, 6, 0);
	mainLayout->addWidget(_priority, 6, 1);

	
	//Description
	QLabel* desLabel = new QLabel("Description");
	_description = new QTextEdit(this);

	mainLayout->addWidget(desLabel, 7, 0);
	mainLayout->addWidget(_description, 7, 1);


	//Space Between Priority and Attachments
	QSpacerItem* attachspacer = new QSpacerItem(33, 33, QSizePolicy::Fixed, QSizePolicy::Fixed);
	mainLayout->addItem(attachspacer, 8, 0, 1, 1);


	//Attachments area
	QLabel* attachmentsLabel = new QLabel("Attachments");
	_ssvWidget = new ScreenShotVideoWidget(this);

	mainLayout->addWidget(attachmentsLabel, 9, 0);
	mainLayout->addWidget(_ssvWidget, 9, 1);


	//Screencap/Video Buttons
	QHBoxLayout* ssvButtonLayout = new QHBoxLayout();
	_addScreenshotButton = new QPushButton("Add Screenshot");
	_addVideoButton = new QPushButton("Add Video");

	ssvButtonLayout->addWidget(_addScreenshotButton);
	ssvButtonLayout->addWidget(_addVideoButton);
	mainLayout->addLayout(ssvButtonLayout, 10, 1);


	//Space Between Screencap/Video Buttons and Create Button
	QSpacerItem* bottomSpacer = new QSpacerItem(100, 100, QSizePolicy::Fixed, QSizePolicy::Fixed);
	mainLayout->addItem(bottomSpacer,11,0,2,2);


	//Create
	_createIssueButton = new QPushButton("Create Report");
	mainLayout->addWidget(_createIssueButton, 12, 0, 1, 2);

	setLayout(mainLayout);

	createConnections();


	//Load user info from access control
	//_originator = "";
}

BRCreateDialog::~BRCreateDialog()
{

}

void BRCreateDialog::createConnections()
{
	connect(_summary, SIGNAL(textChanged(const QString&)), this, SLOT(formModifiedHandler()));
	
	connect(_addScreenshotButton, SIGNAL(clicked()), _ssvWidget, SLOT(createScreenShot()));
	connect(_addVideoButton, SIGNAL(clicked()), _ssvWidget, SLOT(createVideo()));

	connect(_createIssueButton, SIGNAL(clicked()), this, SLOT(createIssueClicked()));
}

void BRCreateDialog::loadReport(BRData report)
{
	_update = true;
	_updateIssueId = report.getIssueNumber();
	//set all fields from report
	_createIssueButton->setText("Update Report");

	//Hidden items
	_originator = report.getOriginator();

	//Visible items
	_summary->setText(report.getSummary());
	_string->setCurrentIndex(STRING_NAMES.indexOf(report.getStringName()));
	_affectedVersion->setText(report.getAffectedVersion());
	_category->setCurrentIndex(CATEGORIES.indexOf(report.getCategoryStr()));
	_component->setCurrentIndex(COMPONENTS.indexOf(report.getComponent()));
	_priority->setCurrentIndex(PRIORITY.indexOf(report.getPriorityStr()));
	_description->setText(report.getDescription());

	int numAttach = report.getAttachments().size();

	for (int i = 0; i < numAttach; ++i)
	{
		QListWidgetItem* item = new QListWidgetItem(report.getAttachments()[i].first);
		QString fileLocation(report.getAttachments()[i].second);
		item->setData(Qt::UserRole, fileLocation);
		_ssvWidget->addItem(item);
	}
}

void BRCreateDialog::generatePendingIssue()
{
	_pendingIssue = BRData(0, QString("SAGE"), _summary->text(), QString(""), _originator, _affectedVersion->text(), _string->currentText(), QString("DOMES"),
		BRData::ISSUE_TYPE::DR, _component->currentText(), _description->toPlainText(), BRData::PRIORITY::MINOR , BRData::CATEGORY::BUG);

	_pendingIssue.setPriorityFromStr(_priority->currentText());
	_pendingIssue.setCategoryFromStr(_category->currentText());

	ATTACHMENTS attachments;
	for (int i = 0; i < _ssvWidget->count(); ++i)
	{
		QPair<QString, QString> attachment(_ssvWidget->item(i)->text(), _ssvWidget->item(i)->data(Qt::UserRole).toString());
		attachments.push_back(attachment);
		_pendingIssue.setAttachments(attachments);
	}

	if (_update)
	{
		_pendingIssue.setIssueNumber(_updateIssueId);
	}
}

void BRCreateDialog::createIssueClicked()
{

	//Generate BRData
	generatePendingIssue();

	//Hides the modal dialog and sets the result code to Accepted
	accept();
}

void BRCreateDialog::formModifiedHandler()
{
	//TODO add more checks
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

	if (!_update)
	{
		msgBox.setText("Issue Creation In Progress!");
		msgBox.setInformativeText("Do you want to Create the report?");
	}
	else
	{
		msgBox.setText("Issue Update In Progress!");
		msgBox.setInformativeText("Do you want to Update the report?");
	}

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
		generatePendingIssue();
	}

	emit finished(1);
}


void BRCreateDialog::loadComponents()
{
	//open model files from all 
	//std::string modelName = "TBD";
	//std::list<std::string> components({ "test1", "test2"});
	//_modelComponents[modelName] = components;
}