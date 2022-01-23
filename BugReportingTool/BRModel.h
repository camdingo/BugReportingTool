#include <QString>
#include <QUuid>
#include <QVector>

class BRModel 
{
public:
	BRModel();


	enum PRIORITY {
		LOW,
		MEDIUM,
		HIGH,
		BLOCKER
	};

	enum ISSUE_TYPE {
		DR
	};

private:
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