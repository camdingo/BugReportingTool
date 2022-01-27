#include "BRData.h"

BRData::BRData()
	: _uuid(0)
	, _summary("TBD")
	, _assignee("TBD")
	, _reporter("TBD")
	, _issueType(ISSUE_TYPE::DR)
	, _description("")
	, _priority(PRIORITY::LOW)
{

}


BRData::BRData(QUuid uuid, QString summary, QString assignee, QString reporter,
	ISSUE_TYPE issueType, QString description, PRIORITY priority)
	:  _uuid(uuid)
	, _summary(summary)
	, _assignee(assignee)
	, _reporter(reporter)
	, _issueType(issueType)
	, _description(description)
	, _priority(priority)
{

}
