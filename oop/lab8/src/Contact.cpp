#include "headers/Contact.h"

Contact::Contact() {
    birthDate = QDate::currentDate();
}

QString Contact::getLastName() const { return lastName; }
QString Contact::getFirstName() const { return firstName; }
QString Contact::getMiddleName() const { return middleName; }
QString Contact::getAddress() const { return address; }
QDate Contact::getBirthDate() const { return birthDate; }
QString Contact::getEmail() const { return email; }
QStringList Contact::getPhones() const { return phones; }

void Contact::setLastName(const QString &value) { lastName = value; }
void Contact::setFirstName(const QString &value) { firstName = value; }
void Contact::setMiddleName(const QString &value) { middleName = value; }
void Contact::setAddress(const QString &value) { address = value; }
void Contact::setBirthDate(const QDate &value) { birthDate = value; }
void Contact::setEmail(const QString &value) { email = value; }
void Contact::setPhones(const QStringList &value) { phones = value; }

QString Contact::toString() const {
    return lastName + "|" + firstName + "|" + middleName + "|" + 
           address + "|" + birthDate.toString("yyyy-MM-dd") + "|" + 
           email + "|" + phones.join(",");
}

Contact Contact::fromString(const QString &str) {
    Contact contact;
    QStringList parts = str.split('|');
    
    if (parts.size() == 7) {
        contact.setLastName(parts[0]);
        contact.setFirstName(parts[1]);
        contact.setMiddleName(parts[2]);
        contact.setAddress(parts[3]);
        contact.setBirthDate(QDate::fromString(parts[4], "yyyy-MM-dd"));
        contact.setEmail(parts[5]);
        contact.setPhones(parts[6].split(','));
    }
    
    return contact;
}