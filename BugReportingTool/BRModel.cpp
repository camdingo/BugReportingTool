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

QModelIndex BRModel::index(int row, int column, const QModelIndex& parent) const
{
	QModelIndex index;
	return index;
}

QModelIndex BRModel::parent(const QModelIndex& index) const
{
	return QModelIndex();
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

Qt::ItemFlags BRModel::flags(const QModelIndex& index) const 
{

	Qt::ItemFlags result = Qt::ItemIsEditable | QAbstractItemModel::flags(index);

	return result;

}

bool BRModel::setData(const QModelIndex& index, const QVariant& value, int role)
{

	bool result = false;

	if (index.isValid() && role == Qt::EditRole) 
	{

		index.row(), index.column();

		int row = index.row();
		int column = index.column();


		switch (column) 
		{

			case 0:
				//_data.at(row).setName(value.toString());
				break;

			case 1:
				//_data.at(row).setAge(value.toInt());
				break;

			default:
				break;

		} // end switch column

		emit dataChanged(index, index);

		result = true;

	}

	return result;

}

QVariant BRModel::headerData(int section, Qt::Orientation orientation, int role) const {

	QVariant result = QVariant();

	if (Qt::DisplayRole == role && Qt::Horizontal == orientation) 
	{
		switch (section) 
		{

			case 0:
				result = "Hello";
				break;

			default:
				break;

		}

	}
	else if (Qt::DisplayRole == role && Qt::Vertical == orientation) 
	{ 

		switch (section) 
		{
			case 0:
				result = "Welcome";
				break;

			default:
				break;

		}

	}
	else {

	}

	return result;

}
