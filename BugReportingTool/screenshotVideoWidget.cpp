#include "screenshotVideoWidget.h"

#include <QHBoxLayout>
#include <QMenu>
#include <QDebug>
#include <QMessageBox>

ScreenShotVideoWidget::ScreenShotVideoWidget(QWidget* parent)
{
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenuRequested(QPoint)));

	setSelectionMode(SelectionMode::ExtendedSelection);

	setAlternatingRowColors(true);

	for (int i = 0; i < 5; ++i)
	{
		QListWidgetItem* item = new QListWidgetItem("test" + QString::number(i));
		QString fileLocation("/msic/egfeg/gere");
		item->setData(Qt::UserRole, fileLocation);
		addItem(item);

	}
}

ScreenShotVideoWidget::~ScreenShotVideoWidget() 
{

}

void ScreenShotVideoWidget::customMenuRequested(const QPoint& pos)
{
	// Handle global position
	QPoint globalPos = this->mapToGlobal(pos);

	// Create menu and insert some actions
	QMenu myMenu;
	myMenu.addAction("Delete", this, SLOT(eraseItems()));

	// Show context menu at handling position
	myMenu.exec(globalPos);
}

void ScreenShotVideoWidget::eraseItems()
{

	QMessageBox msgBox(this);

	msgBox.setText("Are you sure you want to delete selected items?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);

	int ret = msgBox.exec();

	if (ret == QMessageBox::No)
	{
		return;
	}
	else if (ret == QMessageBox::Yes)
	{
		auto items = selectedItems();
		foreach(QListWidgetItem * item, items)
		{
			delete takeItem(row(item));
		}
	}

}