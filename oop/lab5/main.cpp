#include "asd.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    HelloWidget window;
    window.show();

    return app.exec();
}
