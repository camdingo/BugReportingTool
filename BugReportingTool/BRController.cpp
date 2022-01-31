#include "BRController.h"

BRController::BRController(std::shared_ptr<BRModel> model, std::shared_ptr<BRWindow> view)
{
	_model = model;
	_view = view;

	createConnections();

	loadIssues();


}

BRController::~BRController()
{

}

void BRController::createConnections()
{
	connect(_view.get(), SIGNAL(getDetailedView(int)), this, SLOT(getDetails(int)));
}

void BRController::getDetails(int row)
{
	QString details = _model->getDetails(row);

	_view->setDetailView(details);
}

void BRController::loadIssues()
{
	//use boost fs to iterate folders
	//convert csv to BRData
	//push data into model


	//TESTING

	for (quint32 i = 0; i < 20; ++i)
	{
		BRData test(i, "SAGE", "Component crashed", "cameron", "rob", "21.1", "engineering","domes", 
			BRData::ISSUE_TYPE::DR, "backend", "exe crashed", BRData::PRIORITY::BLOCKER, BRData::CATEGORY::CRASH);

		_model->addIssue(test);

		
	}

	_model->setLastIssueNumber(19);

	//need to set highest issue number when loading

}


void BRController::saveIssue()
{

}

//Use this to capture output from calling xwininfo
//std::string exec(const char* cmd) 
//{
//    std::array<char, 128> buffer;
//    std::string result;
//    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
//    if (!pipe) {
//        throw std::runtime_error("popen() failed!");
//    }
//    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
//        result += buffer.data();
//    }
//    return result;
//}