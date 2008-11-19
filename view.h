#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>


class view : public QWidget
{
	public:

	view();
    	QGraphicsScene field;
    	QGraphicsView fieldofview;

	


};

#endif
