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

	//Pure Virtual Functions
	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

	// Override Virtual Functions
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	//bool insertRows(int position, int rows, const QModelIndex& index = QModelIndex());
	//bool removeRows(int position, int rows, const QModelIndex& index = QModelIndex());

	//setters
	void addIssue(BRData issue);
	void setLastIssueNumber(int lastIssueNumber) { _lastIssueNumber = lastIssueNumber; }

	//getters
	QString getDetails(int row);
	int getLastIssueNumber() { return _lastIssueNumber; }

private:
	std::vector<BRData> _data;
	int _lastIssueNumber; //change this to always pull the real last num from file
};

#endif // _BRMODEL_