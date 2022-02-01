#ifndef _BRDATA_
#define _BRDATA_

#include <QString>
#include <QVector>
#include <QMetaType>
#include <QDateTime>


class BRData
{
public:

	enum PRIORITY {
		MINOR,
		MAJOR,
		CRITICAL,
		BLOCKER
	};

	enum ISSUE_TYPE {
		DR
	};

	enum CATEGORY {
		BUG,
		FEATURE_REQUEST,
		USABILITY_ISSUE,
		CRASH,
		OTHER
	};

	BRData();

	BRData(quint32 issueNumber, QString project, QString summary, QString assignee, QString originator,
		QString affectedVersion, QString stringName, QString fundingSource, ISSUE_TYPE issueType, QString component,
		QString description, PRIORITY priority, CATEGORY category);

	//Setters
	void setIssueNumber(quint32 issueNumber) {_issueNumber = issueNumber; }
	void setSummary(QString summary) { _summary = summary; }
	void setProject(QString project) { _project = project; }
	void setAssignee(QString assignee) { _assignee = assignee; }
	void setOriginator(QString originator) { _originator = originator; }
	void setIssueType(ISSUE_TYPE issueType) { _issueType = issueType; }
	void setDescription(QString description) { _description = description; }
	void setPriority(PRIORITY priority) { _priority = priority; }
	void setPriorityFromStr(QString priority);
	void setAffectedVersion(QString affectedVersion) { _affectedVersion = affectedVersion; }
	void setFundingSource(QString fundingSource) { _fundingSource = fundingSource; }
	void setComponent(QString component) { _component = component; }
	void setCategory(CATEGORY category) { _category = category; }
	void setCategoryFromStr(QString category);
	void setStringName(QString stringName) { _stringName = stringName; }

	//Getters
	quint32 getIssueNumber() { return _issueNumber; }
	QString getProject() { return _project; }
	QString getSummary() { return _summary; }
	QString getAssignee() { return _assignee; }
	QString getOriginator() { return _originator; }
	ISSUE_TYPE getIssueType() { return _issueType; }
	QString getDescription() { return _description; }
	PRIORITY getPriority() { return _priority; }
	QString getAffectedVersion() { return _affectedVersion; }
	QString getFundingSource() { return _fundingSource; }
	QString getComponent() { return _component; }
	CATEGORY getCategory() { return _category; }
	QDateTime getCreationDate() { return _creationDate; }
	QString getStringName() { return _stringName; }

	QString getCategoryStr();
	QString getPriorityStr();

	CATEGORY categoryFromString(QString);
	PRIORITY priorityFromString(QString);

private:
	quint32 _issueNumber;
	QString _project;
	QString _summary;
	QString _assignee;
	QString _originator;
	QString _affectedVersion;
	QString _stringName;
	QString _fundingSource;
	QString _component;
	ISSUE_TYPE _issueType;
	QString _description;
	PRIORITY _priority;
	QDateTime _creationDate;
	CATEGORY _category;

	//The attachments can hold locations of logs/videos/screencaps
	QVector<QString> _attachments;

};

Q_DECLARE_METATYPE(BRData);

#endif // _BRDATA_