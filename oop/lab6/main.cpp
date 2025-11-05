#include <QApplication>
#include "other.h"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    allMyWidgets window;
    window.show();
    return app.exec();
}