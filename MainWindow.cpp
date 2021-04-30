#include "MainWindow.h"
#include "flowlayout.h"
#include "locationlayout.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	ui.widget_right->setStyleSheet("#widget_right{border-image: url(:/images/camera_bk_1347x363.png);}");


	FlowLayout *fl = new FlowLayout(ui.widget_left, 9, 9, 9);

	for (int i = 0; i < 100; i++)
	{
		QPushButton *button = new QPushButton(QString(tr("button_%1")).arg(i), this);
		fl->addWidget(button);
	}

	LocationLayout *ll = new LocationLayout(ui.widget_right, 1347, 363);

	{
		
	}



	QList<QRect> lstRect;
	lstRect.append(QRect(105, 88, 65, 81));
	lstRect.append(QRect(105, 185, 65, 81));
	lstRect.append(QRect(405, 12, 65, 81));
	lstRect.append(QRect(405, 274, 65, 81));
	lstRect.append(QRect(1227, 17, 65, 81));
	lstRect.append(QRect(1227, 137, 65, 81));
	lstRect.append(QRect(1227, 276, 65, 81));

	foreach(QRect rc, lstRect)
	{
		QPushButton *button = new QPushButton(this);
		button->setStyleSheet("border-image: url(:/images/camera_65x81_pressed.png);");
		ll->addWidget(button, rc);
	}

	lstRect.clear();
	lstRect.append(QRect(206, 94, 269, 164));
	lstRect.append(QRect(860, 9, 269, 164));
	lstRect.append(QRect(860, 184, 269, 164));
	foreach(QRect rc, lstRect)
	{
		QPushButton *button = new QPushButton(this);
		button->setStyleSheet("border-image: url(:/images/group_title_bk.png);");
		ll->addWidget(button, rc);
	}

#if 0
	for (int i = 0; i < 6; i++)
	{
		QPushButton *button = new QPushButton(QString(tr("button_%1")).arg(i), this);
		ll->addWidget(button, QRect(i * 80, 100, 60, 30));
	}

#endif
}
