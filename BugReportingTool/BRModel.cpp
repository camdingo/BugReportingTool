#include "BRModel.h"

BRModel::BRModel()
	: _uuid(0)
	, _summary("TBD")
	, _assignee("TBD")
	, _reporter("TBD")
	, _issueType(ISSUE_TYPE::DR)
	, _description("")
	, _priority(PRIORITY::LOW)
{

}


BRModel::BRModel (	QWidget* parent,	QUuid uuid, QString summary, QString assignee, QString reporter,
					ISSUE_TYPE issueType, QString description, PRIORITY priority)
	:	_parent(parent)
	,	_uuid(uuid)
	,	_summary(summary)
	,	_assignee(assignee)
	,	_reporter(reporter)
	,	_issueType(issueType)
	,	_description(description)
	,	_priority(priority)
{

}



QModelIndex BRModel::index(int row, int column, const QModelIndex& parent) const
{
	QModelIndex index;
	return index;
}

QModelIndex BRModel::parent(const QModelIndex& index) const
{
	QModelIndex parent;
	return parent;
}

int BRModel::rowCount(const QModelIndex& parent) const 
{
	return 0;
}

int BRModel::columnCount(const QModelIndex& parent) const
{
	return 0;
}

QVariant BRModel::data(const QModelIndex& index, int role) const
{
	return 0;
}