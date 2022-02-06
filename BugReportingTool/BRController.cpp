#include "BRController.h"

#include <QDebug>

BRController::BRController(std::shared_ptr<BRModel> model, std::shared_ptr<BRWindow> view)
{
	_model = model;
	_view = view;

	createConnections();

	loadIssues();


}

BRController::~BRController()
{

}

void BRController::createConnections()
{
	connect(_view.get(), SIGNAL(getDetailedView(int)), this, SLOT(getDetails(int)));

	connect(_view.get(), SIGNAL(generateReport(BRData)), this, SLOT(saveReport(BRData)));

	connect(_view.get(), SIGNAL(deleteSelectedReport(int)), this, SLOT(deleteSelected(int)));

	connect(_view.get(), SIGNAL(retrieveSelectedReport(int)), this, SLOT(retrieveSelected(int)));

	connect(_view.get(), SIGNAL(sendUpdatedReport(BRData)), this, SLOT(updateReport(BRData)));
}

void BRController::getDetails(int row)
{
	qDebug() << "Getting Details";
	QString details = _model->getDetails(row);
	_view->setDetailView(details);
}

void BRController::deleteSelected(int row)
{
	qDebug() << "Erasing Report";
	_model->removeSelectedIssue(row);
}

void BRController::retrieveSelected(int row)
{
	qDebug() << "Retrieving Report";
	_view->updateReport(_model->getReport(row));
}

void BRController::saveReport(BRData report)
{
	qDebug() << "Saving Report";

	//create lock file

	//get next id

	//add id to BRData

	//increment id

	//save new id to file
	_model->addIssue(report);

	//delete lock file
}

void BRController::updateReport(BRData report)
{
	qDebug() << "BRController Updating Report";

	//create lock file


	//save new id to file
	_model->updateIssue(report);

	//delete lock file
}

void BRController::loadIssues()
{
	//use boost fs to iterate folders
	//convert csv to BRData
	//push data into model


	//CTR testing, remove later
	for (quint32 i = 0; i < 5; ++i)
	{
		BRData test(i, "SAGE", "Component crashed", "cameron", "rob", "21.1", "Engineering 1","domes", 
			BRData::ISSUE_TYPE::DR, "backend", "exe crashed", BRData::PRIORITY::BLOCKER, BRData::CATEGORY::CRASH);

		_model->addIssue(test);

		
	}

	_model->setLastIssueNumber(5);

	//need to set highest issue number when loading

}


void BRController::saveIssue()
{
	
}
