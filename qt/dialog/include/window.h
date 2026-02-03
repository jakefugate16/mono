#ifndef QT_WINDOW_H
#define QT_WINDOW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QDialogButtonBox>

namespace ui{
	class MainWindow;
	class Window2;
}


class ui::MainWindow : public QWidget
{

public:
	explicit MainWindow(QWidget* parent = nullptr);

private:
	QGridLayout* grid;
	
	QGroupBox* group;
	QVBoxLayout* vbox;
	QRadioButton* m_button1;
	QRadioButton* m_button2;
	QRadioButton* m_button3;

	QPushButton* m_button_ok;
	QPushButton* m_button_cancel;
};

class ui::Window2 : public QWidget
{
public:
	explicit Window2(QWidget* parent = nullptr);
private:
	QPushButton* m_button1;
	QPushButton* m_button2;

	QVBoxLayout* vbox;
};

#endif
