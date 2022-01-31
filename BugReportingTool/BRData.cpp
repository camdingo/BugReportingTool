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
	else
		return "Crash";
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