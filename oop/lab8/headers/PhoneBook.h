#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QList>
#include "Contact.h"

class PhoneBook : public QWidget {
    Q_OBJECT
    
private:
    QTableWidget *table;
    QLineEdit *searchEdit;
    QList<Contact> contacts;
    QString filename;
    
    void updateTable();
    
private slots:
    void addContact();
    void editContact();
    void deleteContact();
    void searchContacts();
    void saveToFile();
    void loadFromFile();
    
public:
    PhoneBook(QWidget *parent = nullptr);
};