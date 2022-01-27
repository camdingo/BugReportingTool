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

	std::shared_ptr<BRModel> _model;
	std::shared_ptr<BRWindow> _view;
};

#endif // _BRCONTROLLER_