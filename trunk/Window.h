#ifndef _WINDOW_H
#define	_WINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QAbstractButton>
#include <QLayout>
#include <QApplication>

class QAction;
class QLabel;

class Window : public QMainWindow
{
    Q_OBJECT

    public:
        Window();
        
    private:
        
        void newSheet();
        void saveSheet();
        void loadSheet();
        
        QWidget *MainWidget;
        
        void createMenus();
            QMenu* fileMenu;
            QMenu* helpMenu;	
            
        void createActions();
            QAction* HelpAction;
            
        void Help();

};
#endif	
