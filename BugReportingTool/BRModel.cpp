#include "BRModel.h"

#include <QDebug>
#include <QPair>

BRModel::BRModel()
{
	
}

int BRModel::rowCount(const QModelIndex& parent) const 
{
	return _data.size();
}

int BRModel::columnCount(const QModelIndex& parent) const
{
	return 6;
}

QVariant BRModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() < 0)
		return QVariant();

	BRData issue = _data[index.row()];
	
	if (role == Qt::DisplayRole) 
	{
		if (index.column() == 0)
			return issue.getIssueNumber();
		else if (index.column() == 1)
			return issue.getSummary();
	}
	else if(role == Qt::UserRole)
	{
		if (index.column() == 2)
			return issue.getDescription();
		else if (index.column() == 3)
			return issue.getPriorityStr();
		else if(index.column() == 4)
			return issue.getAffectedVersion();
		else if (index.column() == 5)
			return issue.getOriginator();

	}
	return QVariant();
}

Qt::ItemFlags BRModel::flags(const QModelIndex& index) const 
{

	Qt::ItemFlags result = Qt::ItemIsEditable | QAbstractItemModel::flags(index);

	return result;

}

QVariant BRModel::headerData(int section, Qt::Orientation orientation, int role) const 
{
	if (role != Qt::DisplayRole)
		return QVariant();

	switch (section)
	{
		case 0:
			return tr("Issue #");

		case 1:
			return tr("Summary");

		default:
			return QVariant();
	}

	return QVariant();


}

void BRModel::removeSelectedIssue(int row)
{
	beginRemoveRows(QModelIndex(), row, row);
	_data.erase(_data.begin() + row );
	endRemoveRows();
}


void BRModel::addIssue(BRData issue)
{
	beginInsertRows(QModelIndex(), 0, 0);
	_data.push_front(issue);
	endInsertRows();
}

void BRModel::updateIssue(BRData issue)
{
	beginResetModel();

	std::deque<BRData>::iterator itr;
	itr = std::find(_data.begin(), _data.end(), issue);
	if (itr != _data.end())
	{
		qDebug() << "Found";
		*itr = issue;
	}
	else
	{
		qDebug() << "Not Found";
	}

	endResetModel();
}

BRData BRModel::getReport(int row)
{
	return _data[row];
}

QString BRModel::getDetails(int row)
{
	QString details;
	details += QString("<b>Issue #: </b>") + QString::number(_data[row].getIssueNumber()) + QString("<br/>");
	details += QString("<b>Summary: </b>") + _data[row].getSummary() + QString("<br/>");

	details += QString("<br/><br/><br/>");

	details += QString("<b>Creation Date: </b>") + _data[row].getCreationDate().toString() + QString("<br/>");
	details += QString("<b>Affected Version: </b>") + _data[row].getAffectedVersion() + QString("<br/>");
	details += QString("<b>String: </b>") + _data[row].getStringName() + QString("<br/>");
	details += QString("<b>Originator: </b>") + _data[row].getOriginator() + QString("<br/>");

	details += QString("<b>Component: </b>") + _data[row].getComponent() + QString("<br/>");
	details += QString("<b>Category: </b>") + _data[row].getCategoryStr() + QString("<br/>");
	details += QString("<b>Priority: </b>") + _data[row].getPriorityStr() + QString("<br/>");

	details += QString("<br/>");

	details += QString("<b>Description: </b>") + _data[row].getDescription() + QString("<br/>");

	details += QString("<br/>");

	int numAttach = _data[row].getAttachments().size();
	qDebug() << "num attach " << numAttach;
	if (numAttach > 0)
		details += QString("<b>Attachments: </b>") + QString("<br/>");

	for (int i = 0; i < numAttach; ++i)
		details += _data[row].getAttachments()[i].second + QString("/") + _data[row].getAttachments()[i].first + QString("<br/>");


	return QString("<html> <body style='color:white'>") + details + QString("< / body> < / html>");
}

//CTR probably not needed
//bool BRModel::insertRows(int position, int rows, const QModelIndex& index)
//{
//	Q_UNUSED(index);
//	beginInsertRows(QModelIndex(), position, position + rows - 1);
//
//	for (int row = 0; row < rows; row++) {
//		
//	}
//
//	endInsertRows();
//	return true;
//}
//
//bool BRModel::removeRows(int position, int rows, const QModelIndex& index)
//{
//	Q_UNUSED(index);
//	beginRemoveRows(QModelIndex(), position, position + rows - 1);
//
//	for (int row = 0; row < rows; ++row) {
//		
//	}
//
//	endRemoveRows();
//	return true;
//}