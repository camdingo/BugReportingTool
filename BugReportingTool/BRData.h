#ifndef _BRDATA_
#define _BRDATA_

#include <QString>
#include <QVector>
#include <QMetaType>

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

	BRData(quint32 issueNumber, QString summary, QString assignee, QString reporter,
			ISSUE_TYPE issueType, QString description, PRIORITY priority);

	//Setters
	quint32 setIssueNumber(quint32 issueNumber) {_issueNumber = issueNumber; }
	QString setSummary(QString summary) { _summary = summary; }
	QString setAssignee(QString assignee) { _assignee = assignee; }
	QString setReporter(QString reporter) { _reporter = reporter; }
	ISSUE_TYPE setIssueType(ISSUE_TYPE issueType) { _issueType = issueType; }
	QString setDescription(QString description) { _description = description; }
	PRIORITY setPriority(PRIORITY priority) { _priority = priority; }

	//Getters
	quint32 getIssueNumber() { return _issueNumber; }
	QString getSummary() { return _summary; }
	QString getAssignee() { return _assignee; }
	QString getReporter() { return _reporter; }
	ISSUE_TYPE getIssueType() { return _issueType; }
	QString getDescription() { return _description; }
	PRIORITY getPriority() { return _priority; }

private:
	quint32 _issueNumber;
	QString _summary;
	QString _assignee;
	QString _reporter;
	ISSUE_TYPE _issueType;
	QString _description;
	PRIORITY _priority;

	//The attachments can hold locations of logs/videos/screencaps
	QVector<QString> _attachments;

};

Q_DECLARE_METATYPE(BRData);

#endif // _BRDATA_