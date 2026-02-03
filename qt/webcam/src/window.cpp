#include <window.h>
#include <QtCore/QDebug>
#include <Qtcore/QList>
#include <QtWidgets/QWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtMultimedia/QCamera>
#include <QtMultimedia/QCameraInfo>
#include <QtMultimedia/QCameraImageCapture>
#include <QtMultimediaWidgets/QCameraViewfinder>
#include <QtMultimediaWidgets/QVideoWidget>
#include <iostream>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
	QWidget* dialogwindow = new Window1;
	QWidget* camerawindow = new Window2;

	QStackedWidget* stackedwidget = new QStackedWidget;
	stackedwidget->addWidget(dialogwindow);
	stackedwidget->addWidget(camerawindow);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(stackedwidget);
	setLayout(layout);
}

Window1::Window1(QWidget* parent) : QWidget(parent)
{

	setAttribute(Qt::WA_DeleteOnClose, true);
	//Create group of pushbuttons
	m_grid = new QGridLayout(this);
	
	//create group of buttons
	m_group1 = new QGroupBox(this);
	m_vbox = new QVBoxLayout(this);
	m_button1 = new QRadioButton("One", this);
	m_button2 = new QRadioButton("Two", this);
	m_button3 = new QRadioButton("Three", this);
	m_vbox->addWidget(m_button1);
	m_vbox->addWidget(m_button2);
	m_vbox->addWidget(m_button3);
	m_group1->setLayout(m_vbox);

	//Init window control buttons
	m_group2 = new QGroupBox(this);
	m_hbox = new QHBoxLayout(this);
	m_button_ok = new QPushButton("Next", this);
	m_button_cancel = new QPushButton("Cancel", this);
	m_hbox->addWidget(m_button_cancel);
	m_hbox->addWidget(m_button_ok);
	m_group2->setLayout(m_hbox);


	//layout widgets onto grid
	m_grid->addWidget(m_group1, 0, 0);
	m_grid->addWidget(m_group2, 1, 0);
	
	setLayout(m_grid);
	//button for next window
	connect(m_button_ok, &QPushButton::clicked, this, [this]()
	{
		close();
	});
	
	//cancel program
	connect(m_button_cancel, &QPushButton::clicked, this, [this]()
	{
		close();
	});
}


Window2::Window2(QWidget* parent) : QWidget(parent)
{
	//init camera
	const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();

	if(cameras.isEmpty())
		std::cout << "No cameras found" << std::endl;
	
//	QList<QCameraInfo>::const_iterator camera_ptr = cameras.begin();

	for (const auto& cam : cameras)
		qDebug() << cam.deviceName();

	camera = new QCamera(cameras[0]);
	viewfinder = new QCameraViewfinder;
	camera->setViewfinder(viewfinder);
	
	//define button for capturing image
	button_capture = new QPushButton("Capture Image");
	connect(button_capture, &QPushButton::clicked, this, &captureImage);

	//define button for switching cameras
	button_switchcamera = new QPushButton("Switch Camera", this);
	connect(button_switchcamera, &QPushButton::clicked, this, &switchCamera);
	
	//layout
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(viewfinder);
	layout->addWidget(button_switchcamera);
	layout->addWidget(button_capture);
	setLayout(layout);

	//show window after initialization and start camera
	show();
	camera->start();
}

Window2::~Window2()
{
	if(camera)
	{
		camera->stop();
		delete camera;
	}
}

void Window2::switchCamera()
{
	camera->stop();
	delete camera;
	delete viewfinder;
	
	std::cout << "Camera closed" << std::endl;

	qsizetype index{ 0 };


	std::cout << "reindexing camera" << std::endl;
	if(index  >= cameras.size() - 1)
		index = 0;
	else
		++index;

	qDebug() << index;

	std::cout << "resetting camera" << std::endl;
	camera = new QCamera(cameras[index]);
	viewfinder = new QCameraViewfinder;
	camera->setViewfinder(viewfinder);

	camera->start();
}

void Window2::captureImage()
{
	std::cout << "captureImage() called" << std::endl;

	QCameraImageCapture* imageCapture = new QCameraImageCapture(this->camera);
	

	camera->setCaptureMode(QCamera::CaptureStillImage);

	imageCapture->capture();
}

/*
void Window2::processCapturedImage(int requestId, const QImage &img)
{
	Q_UNUSED(requestId);
	qDebug() << "Image captured, size:" << img.size();

	//Display the cptured image in QLabel
	QPixmap pixmap = QPixmap::fromImage(img);
	imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

	//Optional: Save the image to a file
	//QString filename = QFileDialog::getSaveFileName(this, "Save Image", "", "JPEG Image (*.jpg);;PNG Image (*.png)");
	//if (!fileName.isEmpty()){
	//	img.save(fileName);
	//}
}
*/
