#include <window.h>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLayout>
#include <QtWidgets/QRadioButton>

#include <iostream>

Window1::Window1(QWidget* parent)
	: QWidget(parent)
{

	//Create group of pushbuttons
	QVBoxLayout* vbox1 = new QVBoxLayout(this);
	m_button1 = new QPushButton("One");
	m_button2 = new QPushButton("Two");
	m_button3 = new QPushButton("Three");
	vbox1->addWidget(m_button1);
	vbox1->addWidget(m_button2);
	vbox1->addWidget(m_button3);

	QGroupBox* groupbox1 = new QGroupBox("Group1", this);
	groupbox1->setLayout(vbox1);

	//Create group of radio buttons
	QVBoxLayout* vbox2 = new QVBoxLayout(this);
	m_rbutton1 = new QRadioButton("One");
	m_rbutton2 = new QRadioButton("Two");
	m_rbutton3 = new QRadioButton("Third");
	vbox2->addWidget(m_rbutton1);
	vbox2->addWidget(m_rbutton2);
	vbox2->addWidget(m_rbutton3);

	QGroupBox* groupbox2 = new QGroupBox("Group2", this);
	groupbox2->setLayout(vbox2);

	//layout button groups horizontally
	QHBoxLayout* hbox = new QHBoxLayout(this);
	hbox->addWidget(groupbox1);
	hbox->addWidget(groupbox2);

	

	//button for next window
	connect(m_button1, &QPushButton::clicked, this, [this]{
		hide();
		Window2* second = new Window2;
		second->show();
	});
}

Window2::Window2(QWidget* parent)
	:QWidget(parent)
{
	QVBoxLayout* vbox = new QVBoxLayout(this);
	m_button1 = new QPushButton("One");
	m_button2 = new QPushButton("Two");
	vbox->addWidget(m_button1);
	vbox->addWidget(m_button2);

	this->setLayout(vbox);
}
