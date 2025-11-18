#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include "Contact.h"

class ContactDialog : public QDialog{
    Q_OBJECT
    
private:
    QLineEdit *lastNameEdit;
    QLineEdit *firstNameEdit;
    QLineEdit *middleNameEdit;
    QLineEdit *addressEdit;
    QDateEdit *birthDateEdit;
    QLineEdit *emailEdit;
    QLineEdit *phonesEdit;
    
    bool validateName(const QString &name, const QString &fieldName);
    bool validateEmail(const QString &email);
    bool validatePhones(const QString &phones);
    QString normalizePhone(const QString &phone) const;
    
private slots:
    void validateAndAccept();
    
public:
    ContactDialog(QWidget *parent = nullptr);
    Contact getContact() const;
    void setContact(const Contact &contact);
};