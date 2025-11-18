#include <QApplication>
#include "headers/PhoneBook.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    
    PhoneBook phoneBook;
    phoneBook.show();
    
    return app.exec();
}