#include <window.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <iostream>

ui::MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{

	//Create group of pushbuttons
	QGridLayout* grid = new QGridLayout(this);
	
	//create group of buttons
	QGroupBox* group = new QGroupBox(this);
	QVBoxLayout* vbox = new QVBoxLayout(this);

	m_button1 = new QRadioButton("One");
	m_button2 = new QRadioButton("Two");
	m_button3 = new QRadioButton("Three");

	vbox->addWidget(m_button1);
	vbox->addWidget(m_button2);
	vbox->addWidget(m_button3);
	group->setLayout(vbox);
	group->resize(group->width()*2, group->height()); //double width
	
	//Init window control buttons
	m_button_ok = new QPushButton("Next");
	m_button_cancel = new QPushButton("Cancel");


	//layout widgets onto grid
	grid->addWidget(group, 0, 0);
	grid->addWidget(m_button_ok, 1, 1);
	grid->addWidget(m_button_cancel, 1, 0);
	

	//button for next window
	connect(m_button_ok, &QPushButton::clicked, this, [this]
	{
		hide();
		Window2* second = new Window2;
		second->show();
	});

	connect(m_button_cancel, &QPushButton::clicked, this, [this]
	{
		close();
	});
}


ui::Window2::Window2(QWidget* parent)
	: QWidget(parent)
{
	QVBoxLayout* vbox = new QVBoxLayout(this);
	m_button1 = new QPushButton("One");
	m_button2 = new QPushButton("Two");
	vbox->addWidget(m_button1);
	vbox->addWidget(m_button2);

	this->setLayout(vbox);
}
