#include "BRModel.h"

#include <QDebug>
BRModel::BRModel()
	: _rowCount(0)
	, _colCount(0)
{

}

BRModel::BRModel(int rowCount, int colCount)
	: _rowCount(rowCount)
	, _colCount(colCount)
{
}

int BRModel::rowCount(const QModelIndex& parent) const 
{
	return _data.size();
}

int BRModel::columnCount(const QModelIndex& parent) const
{
	return 2;
}

QVariant BRModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (index.row() < 0)
		return QVariant();

	if (role == Qt::DisplayRole) 
	{
		BRData issue = _data[index.row()];

		if (index.column() == 0)
			return issue.getIssueNumber();
		else if (index.column() == 1)
			return issue.getSummary();
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

bool BRModel::insertRows(int position, int rows, const QModelIndex& index)
{
	Q_UNUSED(index);
	beginInsertRows(QModelIndex(), position, position + rows - 1);

	for (int row = 0; row < rows; row++) {
		
	}

	endInsertRows();
	return true;
}

bool BRModel::removeRows(int position, int rows, const QModelIndex& index)
{
	Q_UNUSED(index);
	beginRemoveRows(QModelIndex(), position, position + rows - 1);

	for (int row = 0; row < rows; ++row) {
		
	}

	endRemoveRows();
	return true;
}


void BRModel::addIssue(BRData issue)
{
	_data.push_back(issue);
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

	return QString("<html> <body style='color:white'>") + details + QString("< / body> < / html>");
}