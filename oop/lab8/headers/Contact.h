#pragma once

#include <QString>
#include <QStringList>
#include <QDate>

class Contact {
private:
    QString lastName;
    QString firstName;
    QString middleName;
    QString address;
    QDate birthDate;
    QString email;
    QStringList phones;
    
public:
    Contact();
    
    // Геттеры
    QString getLastName() const;
    QString getFirstName() const;
    QString getMiddleName() const;
    QString getAddress() const;
    QDate getBirthDate() const;
    QString getEmail() const;
    QStringList getPhones() const;
    
    // Сеттеры
    void setLastName(const QString &value);
    void setFirstName(const QString &value);
    void setMiddleName(const QString &value);
    void setAddress(const QString &value);
    void setBirthDate(const QDate &value);
    void setEmail(const QString &value);
    void setPhones(const QStringList &value);
    
    // Методы для работы с файлом
    QString toString() const;
    static Contact fromString(const QString &str);
};