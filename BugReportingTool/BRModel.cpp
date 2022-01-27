#include "BRModel.h"

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