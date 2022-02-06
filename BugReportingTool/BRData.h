#ifndef _BRDATA_
#define _BRDATA_

#include <QString>
#include <QVector>
#include <QMetaType>
#include <QDateTime>

typedef QVector<QPair<QString, QString> > ATTACHMENTS;
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

	bool operator==(const BRData& rhs) {  return (_issueNumber == rhs.getIssueNumber()); }

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
	void setAttachments(ATTACHMENTS attachments) { _attachments = attachments; }

	//Getters
	quint32 getIssueNumber() const { return _issueNumber; }
	QString getProject() const { return _project; }
	QString getSummary() const { return _summary; }
	QString getAssignee() const { return _assignee; }
	QString getOriginator() const { return _originator; }
	ISSUE_TYPE getIssueType() const { return _issueType; }
	QString getDescription() const { return _description; }
	PRIORITY getPriority() const { return _priority; }
	QString getAffectedVersion() const { return _affectedVersion; }
	QString getFundingSource() const { return _fundingSource; }
	QString getComponent() const { return _component; }
	CATEGORY getCategory() const { return _category; }
	QDateTime getCreationDate() const { return _creationDate; }
	QString getStringName() const { return _stringName; }
	ATTACHMENTS getAttachments() const { return _attachments; }


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
	ATTACHMENTS _attachments;

};

Q_DECLARE_METATYPE(BRData);

#endif // _BRDATA_