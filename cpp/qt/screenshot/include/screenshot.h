#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QtCore/QObject>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>

class Screenshot : public QWidget
{
	Q_OBJECT
public:
	Screenshot();

protected:
	void resizeEvent(QResizeEvent* event) override;

private slots:
	void newScreenshot();
	void saveScreenshot();
	void shootScreen();
	void updateCheckBox();

private:
	void updateScreenshotLabel();

	QPixmap originalPixmap;

	QLabel* screenshotLabel;
	QSpinBox* delaySpinBox;
	QCheckBox* hideThisWindowCheckBox;
	QPushButton* newScreenshotButton;
	
};

#endif
