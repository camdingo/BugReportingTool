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

	void drawRedBorder(int xPos, int yPos, int width, int height);

signals:
	
public slots:
	void customMenuRequested(const QPoint& pos);
	void eraseItems();
	void openItems();

	void createScreenShot();
	void createVideo();

private:


};

#endif // _SCREENSHOTVIDEOWIDGET_
