#include "headers/ContactDialog.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDate>

ContactDialog::ContactDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Добавить/Редактировать контакт");
    setMinimumWidth(400);
    
    QFormLayout *layout = new QFormLayout(this);
    
    lastNameEdit = new QLineEdit(this);
    firstNameEdit = new QLineEdit(this);
    middleNameEdit = new QLineEdit(this);
    addressEdit = new QLineEdit(this);
    birthDateEdit = new QDateEdit(this);
    birthDateEdit->setCalendarPopup(true);
    birthDateEdit->setDate(QDate::currentDate().addYears(-20));
    birthDateEdit->setMaximumDate(QDate::currentDate().addDays(-1));
    
    emailEdit = new QLineEdit(this);
    phonesEdit = new QLineEdit(this);
    phonesEdit->setPlaceholderText("Введите телефоны через запятую");
    
    layout->addRow("Фамилия:", lastNameEdit);
    layout->addRow("Имя:", firstNameEdit);
    layout->addRow("Отчество:", middleNameEdit);
    layout->addRow("Адрес:", addressEdit);
    layout->addRow("Дата рождения:", birthDateEdit);
    layout->addRow("Email:", emailEdit);
    layout->addRow("Телефоны:", phonesEdit);
    
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("OK", this);
    QPushButton *cancelButton = new QPushButton("Отмена", this);
    
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    layout->addRow(buttonLayout);
    
    connect(okButton, &QPushButton::clicked, this, &ContactDialog::validateAndAccept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

bool ContactDialog::validateName(const QString &name, const QString &fieldName) {
    QString trimmed = name.trimmed();
    
    if (trimmed.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", fieldName + " не может быть пустым");
        return false;
    }
    
    if (!trimmed[0].isUpper()) {
        QMessageBox::warning(this, "Ошибка", fieldName + " должно начинаться с заглавной буквы");
        return false;
    }
    
    if (trimmed.startsWith('-') || trimmed.endsWith('-')) {
        QMessageBox::warning(this, "Ошибка", fieldName + " не может начинаться или заканчиваться на дефис");
        return false;
    }
    
    QRegularExpression nameRegex("^[\\p{L}\\d\\s-]+$");
    if (!nameRegex.match(trimmed).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", fieldName + " может содержать только буквы, цифры, дефис и пробел");
        return false;
    }
    
    return true;
}

bool ContactDialog::validateEmail(const QString &email) {
    QString trimmed = email.trimmed();
    trimmed.remove(' ');
    
    if (trimmed.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Email не может быть пустым");
        return false;
    }
    
    QRegularExpression emailRegex("^[a-zA-Z0-9]+@[a-zA-Z0-9]+\\.[a-zA-Z0-9]+$");
    if (!emailRegex.match(trimmed).hasMatch()) {
        QMessageBox::warning(this, "Ошибка", "Неверный формат email");
        return false;
    }
    
    return true;
}

QString ContactDialog::normalizePhone(const QString &phone) const {
    QString result;
    for (QChar c : phone) {
        if (c.isDigit() || c == '+') {
            result += c;
        }
    }
    return result;
}

bool ContactDialog::validatePhones(const QString &phones) {
    if (phones.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Необходимо указать хотя бы один телефон");
        return false;
    }
    
    QStringList phoneList = phones.split(',');
    for (const QString &phone : phoneList) {
        QString normalized = normalizePhone(phone.trimmed());
        if (normalized.length() < 10) {
            QMessageBox::warning(this, "Ошибка", "Телефон слишком короткий: " + phone);
            return false;
        }
    }
    
    return true;
}

void ContactDialog::validateAndAccept() {
    if (!validateName(lastNameEdit->text(), "Фамилия")) return;
    if (!validateName(firstNameEdit->text(), "Имя")) return;
    if (!middleNameEdit->text().trimmed().isEmpty() && 
        !validateName(middleNameEdit->text(), "Отчество")) return;
    if (!validateEmail(emailEdit->text())) return;
    if (!validatePhones(phonesEdit->text())) return;
    
    accept();
}

Contact ContactDialog::getContact() const {
    Contact contact;
    contact.setLastName(lastNameEdit->text().trimmed());
    contact.setFirstName(firstNameEdit->text().trimmed());
    contact.setMiddleName(middleNameEdit->text().trimmed());
    contact.setAddress(addressEdit->text().trimmed());
    contact.setBirthDate(birthDateEdit->date());
    
    QString email = emailEdit->text().trimmed();
    email.remove(' ');
    contact.setEmail(email);
    
    QStringList phoneList = phonesEdit->text().split(',');
    QStringList normalizedPhones;
    for (const QString &phone : phoneList) {
        normalizedPhones.append(normalizePhone(phone.trimmed()));
    }
    contact.setPhones(normalizedPhones);
    
    return contact;
}

void ContactDialog::setContact(const Contact &contact) {
    lastNameEdit->setText(contact.getLastName());
    firstNameEdit->setText(contact.getFirstName());
    middleNameEdit->setText(contact.getMiddleName());
    addressEdit->setText(contact.getAddress());
    birthDateEdit->setDate(contact.getBirthDate());
    emailEdit->setText(contact.getEmail());
    phonesEdit->setText(contact.getPhones().join(", "));
}