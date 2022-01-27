#include "BRController.h"

BRController::BRController(std::shared_ptr<BRModel> model, std::shared_ptr<BRWindow> view)
{
	_model = model;
	_view = view;

	loadIssues();
}

BRController::~BRController()
{

}

void BRController::loadIssues()
{
	//use boost fs to iterate folders
	//convert csv to BRData
	//push data into model


	//TESTING

	for (int i = 0; i < 20; ++i)
	{
		BRData data(i, "Test Summary", "cameron", "rob",
			BRData::ISSUE_TYPE::DR, "this thing is broken", BRData::PRIORITY::BLOCKER);

		_model->addIssue(data);
	}

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