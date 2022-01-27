#ifndef _BRCONTROLLER_
#define _BRCONTROLLER_

#include "BRModel.h"
#include "BRWindow.h"

#include <memory>

class BRController
{
public:
	BRController(std::shared_ptr<BRModel> model, std::shared_ptr<BRWindow> view);
	~BRController();

private:

	void loadIssues();
	
	void saveIssue();

	std::shared_ptr<BRModel> _model;
	std::shared_ptr<BRWindow> _view;

	uint32_t _lastIssueNumber;
};

#endif // _BRCONTROLLER_