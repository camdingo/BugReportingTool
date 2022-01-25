#include <QString>
#include <QUuid>
#include <QVector>

class BRData
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

	BRData();

	BRData(QUuid _uuid, QString _summary, QString _assignee, QString _reporter,
			ISSUE_TYPE _issueType, QString _description, PRIORITY _priority);

	//Setters
	QUuid setUuid(QUuid uuid) {_uuid = uuid; }
	QString setSummary(QString summary) { _summary = summary; }
	QString setAssignee(QString assignee) { _assignee = assignee; }
	QString setReporter(QString reporter) { _reporter = reporter; }
	ISSUE_TYPE setIssueType(ISSUE_TYPE issueType) { _issueType = issueType; }
	QString setDescription(QString description) { _description = description; }
	PRIORITY setPriority(PRIORITY priority) { _priority = priority; }

	//Getters
	QUuid getUuid() { return _uuid; }
	QString getSummary() { return _summary; }
	QString getAssignee() { return _assignee; }
	QString getReporter() { return _reporter; }
	ISSUE_TYPE getIssueType() { return _issueType; }
	QString getDescription() { return _description; }
	PRIORITY getPriority() { return _priority; }

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