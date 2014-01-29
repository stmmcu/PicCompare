#include "picturewidget.h"
#include <QApplication>

#include <demo.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PictureWidget w;
//  demo();
    w.show();
    return a.exec();
}
