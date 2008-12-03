#ifndef MODEL_H
#define MODEL_H

#include <QFile>
#include <QString>
#include <QList>
#include <QtDebug>

//class QList;

class model
{
    public:

        typedef struct point3d {
            float x1;
            float y1;
            float z1;
            float x2;
            float y2;
            float z2;
        };

        model();
        model(QString file);

        QList<point3d> tank;
        QList<point3d> deadTank;
        QList<point3d> projectile;

        void parseModels(QString pathFile);

        void print(QList<point3d> printMe);

};

#endif // MODEL_H
