#ifndef _BRMODEL_
#define _BRMODEL_

#include <QString>
#include <QUuid>
#include <QVector>
#include <QAbstractTableModel>

#include "BRData.h"

class BRModel: public QAbstractTableModel
{
public:

	BRModel();

	BRModel(int rowCount, int colCount);

	//Pure Virtual Functions
	virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex& index) const;
	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	// Override Virtual Functions
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	bool insertRows(int position, int rows, const QModelIndex& index = QModelIndex());
	bool removeRows(int position, int rows, const QModelIndex& index = QModelIndex());


	void addIssue(BRData issue);


private:
	std::vector<BRData> _data;
	int _rowCount;
	int _colCount;

};

#endif // _BRMODEL_