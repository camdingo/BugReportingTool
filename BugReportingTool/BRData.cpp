#include "BRData.h"

BRData::BRData()
	: _issueNumber(0)
	, _project("SAGE")
	, _summary("")
	, _assignee("")
	, _originator("")
	, _affectedVersion("")
	, _stringName("")
	, _fundingSource("")
	, _issueType(ISSUE_TYPE::DR)
	, _component("")
	, _description("")
	, _priority(PRIORITY::MINOR)
	, _category(CATEGORY::BUG)
{
	_creationDate = QDateTime::currentDateTime();
}


BRData::BRData(quint32 issueNumber, QString project, QString summary, QString assignee, QString originator,
	QString affectedVersion, QString stringName, QString fundingSource, ISSUE_TYPE issueType, QString component,
	QString description, PRIORITY priority, CATEGORY category)
	: _issueNumber(issueNumber)
	, _project(project)
	, _summary(summary)
	, _assignee(assignee)
	, _originator(originator)
	, _affectedVersion(affectedVersion)
	, _stringName(stringName)
	, _fundingSource(fundingSource)
	, _issueType(issueType)
	, _component(component)
	, _description(description)
	, _priority(priority)
	, _category(category)
{
	_creationDate = QDateTime::currentDateTime();
}

QString BRData::getCategoryStr()
{
	if (_category == BUG)
		return "Bug";
	else if (_category == FEATURE_REQUEST)
		return "Feature Request";
	else if (_category == USABILITY_ISSUE)
		return "Usability Issue";
	else if(_category == CRASH)
		return "Crash";
	else
	return "Other";
}

void BRData::setCategoryFromStr(QString category)
{
	_category = categoryFromString(category);
}

BRData::CATEGORY BRData::categoryFromString(QString category)
{
	if (category == "Bug")
		return BRData::CATEGORY::BUG;
	else if (category == "Feature Request")
		return BRData::CATEGORY::FEATURE_REQUEST;
	else if (category == "Usability Request")
		return BRData::CATEGORY::USABILITY_ISSUE;
	else if (category == "Crash")
		return BRData::CATEGORY::CRASH;
	else
		return BRData::CATEGORY::OTHER;
}

QString BRData::getPriorityStr()
{
	if (_priority == MINOR)
		return "Minor";
	else if (_priority == MAJOR)
		return "Major";
	else if (_priority == CRITICAL)
		return "Critical";
	else
		return "Blocker";
}

void BRData::setPriorityFromStr(QString priority)
{
	_priority = priorityFromString(priority);
}

BRData::PRIORITY BRData::priorityFromString(QString priority)
{
	if (priority == "Minor")
		return BRData::PRIORITY::MINOR;
	else if(priority == "Major")
		return BRData::PRIORITY::MAJOR;
	else if (priority == "Critical")
		return BRData::PRIORITY::CRITICAL;
	else
		return BRData::PRIORITY::BLOCKER;
}