#ifndef QT_WINDOW_H
#define QT_WINDOW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

namespace ui
{
	class MainWindow;
	class Window2;
}

class MainWindow : public QWidget
{

public:
	explicit MainWindow(QWidget* parent = 0);

private:
	QPushButton* m_button1;
	QPushButton* m_button2;
	QPushButton* m_button3;
	QVBoxLayout* vbox1;
	
	QRadioButton* m_rbutton1;
	QRadioButton* m_rbutton2;
	QRadioButton* m_rbutton3;
	QVBoxLayout* vbox2;

	QGroupBox* groupbox1;
	QGroupBox* groupbox2;
	QHBoxLayout* hbox;

};

class Window2 : public QWidget
{
public:
	explicit Window2(QWidget* parent = 0);
private:
	QPushButton* m_button1;
	QPushButton* m_button2;

	QVBoxLayout* vbox;
};

#endif
