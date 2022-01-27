#include "BRData.h"

BRData::BRData()
	: _issueNumber(0)
	, _summary("TBD")
	, _assignee("TBD")
	, _reporter("TBD")
	, _issueType(ISSUE_TYPE::DR)
	, _description("")
	, _priority(PRIORITY::LOW)
{

}


BRData::BRData(quint32 issueNumber, QString summary, QString assignee, QString reporter,
	ISSUE_TYPE issueType, QString description, PRIORITY priority)
	:  _issueNumber(issueNumber)
	, _summary(summary)
	, _assignee(assignee)
	, _reporter(reporter)
	, _issueType(issueType)
	, _description(description)
	, _priority(priority)
{

}
