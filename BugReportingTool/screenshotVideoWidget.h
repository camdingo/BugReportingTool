#ifndef _SCREENSHOTVIDEOWIDGET_
#define _SCREENSHOTVIDEOWIDGET_

#include <QListWidget>

class QPushButton;

class ScreenShotVideoWidget : public QListWidget
{
	Q_OBJECT

public:
	ScreenShotVideoWidget(QWidget* parent);
	~ScreenShotVideoWidget();


signals:
	
public slots:
	void customMenuRequested(const QPoint& pos);
	void eraseItems();

private:


};

#endif
