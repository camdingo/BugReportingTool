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

private:
	QUuid _uuid;
	QString _summary;
	QString _description;

	QString _creator;
	PRIORITY _priority;

	//The attachments can hold locations of logs/videos/screencaps
	QVector<QString> _attachments;
	
	QString _comments;


};