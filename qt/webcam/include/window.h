#ifndef QT_WINDOW_H
#define QT_WINDOW_H

#include <QtCore/QList>
#include <QtCore/QScopedPointer>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QDialogButtonBox>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QCameraImageCapture>
#include <QtMultimediaWidgets/QCameraViewFinder>
#include <QtMultimediaWidgets/QVideoWidget>

class MainWindow : public QWidget
{
public:
	explicit MainWindow(QWidget* parent = nullptr);

private:
	QStackedWidget* stackedwidget;
	QWidget* dialogwindow;
	QWidget* camerawindow;
	QVBoxLayout* layout;
};

class Window1 : public QWidget
{
public:
	explicit Window1(QWidget* parent = nullptr);

private:
	QGridLayout* m_grid;
	
	QGroupBox* m_group1;
	QVBoxLayout* m_vbox;
	QRadioButton* m_button1;
	QRadioButton* m_button2;
	QRadioButton* m_button3;

	QGroupBox* m_group2;
	QHBoxLayout* m_hbox;
	QPushButton* m_button_ok;
	QPushButton* m_button_cancel;
};

class Window2 : public QWidget
{
public:
	explicit Window2(QWidget* parent = nullptr);
private:
	
	QPushButton* button_capture;
	QPushButton* button_switchcamera;
	QVBoxLayout* layout;

	QList<QCameraInfo> cameras;
	QList<QCameraInfo>::const_iterator camera_ptr;
	QCamera* camera;
	QCameraViewfinder* viewfinder;

	void captureImage();
	void switchCamera();
	void processCapturedImage(int requestId, const QImage &img);

	~Window2();
};

#endif
