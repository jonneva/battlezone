#include "model.h"



model::model()
{
    parseModels("models.dat");
}

model::model(QString file)
{
}

void model::parseModels(QString filePath)
{
        QFile file(filePath);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
                qDebug() << "Could not open file: '" << filePath << "' on line "
                << __LINE__ << " in " << __FILE__;
        }
        else
        {
        QString currentLine = file.readLine();
        currentLine = file.readLine();
        while(currentLine.size() != 0)
        {
            point3d line;
            int i = 0;
            int e = 0;

            while(e <= 6)
            {
                QString point = currentLine.section(' ', i, i);
                if(point != "")
                {
                    float p = point.toFloat();
                    if( e == 1 ) { line.x1 = p; }
                    else if ( e == 2 ) {line.y1 = p; }
                    else if ( e == 3 ) {line.z1 = p; }
                    else if ( e == 4 ) {line.x2 = p; }
                    else if ( e == 5 ) {line.y2 = p; }
                    else if ( e == 6 ) {line.z2 = p; }
                    else{}
                    e++;
                }
                i++;
                tank.append(line);
            }
            currentLine = file.readLine();
        }
        this->print();
    }
}

void model::print()
{

    for(int i = 0; i < tank.size(); i++)
    {
        qDebug() << "x1:" << tank[i].x1 << endl;
    }
}
