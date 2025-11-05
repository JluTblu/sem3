#include <QApplication>
#include "another.h"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    myWidgets window;
    window.show();
    return app.exec();
}