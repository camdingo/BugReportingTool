#include <QString>
#include <QUuid>
#include <QVector>
#include <QAbstractItemModel>

class BRModel: public QAbstractItemModel
{
public:

	enum PRIORITY {
		LOW,
		MEDIUM,
		HIGH,
		BLOCKER
	};

	enum ISSUE_TYPE {
		DR
	};


	BRModel();

	BRModel(QWidget * _parent, QUuid _uuid, QString _summary, QString _assignee, QString _reporter,
			ISSUE_TYPE _issueType, QString _description, PRIORITY _priority);

	virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const;
	virtual QModelIndex parent(const QModelIndex& index) const;
	virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

private:
	QWidget* _parent;

	QUuid _uuid;
	QString _summary;
	QString _assignee;
	QString _reporter;
	ISSUE_TYPE _issueType;
	QString _description;
	PRIORITY _priority;

	//The attachments can hold locations of logs/videos/screencaps
	QVector<QString> _attachments;

};