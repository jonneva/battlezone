#include "view.h"

view::view()
    : QWidget(),
      field(0, 0, 1000, 1000),
      fieldofview(&field,this)
{
	fieldofview.setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	fieldofview.setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
}
