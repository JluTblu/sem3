#include "headers/PhoneBook.h"
#include "headers/ContactDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QHeaderView>
#include <QDir>
#include <QComboBox>

PhoneBook::PhoneBook(QWidget *parent) : QWidget(parent){
    filename = QDir::homePath() + "/phonebook.txt";
    
    setWindowTitle("Телефонный справочник");
    setMinimumSize(800, 600);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Поиск
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLabel *searchLabel = new QLabel("Поиск:", this);
    searchEdit = new QLineEdit(this);
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchEdit);
    mainLayout->addLayout(searchLayout);
    
    // поиск по выбранному полю
    QComboBox *fieldCombo = new QComboBox(this); // выпадающий список для выбора поля
    fieldCombo->addItem("Фамилия", 0);
    fieldCombo->addItem("Имя", 1);
    fieldCombo->addItem("Отчество", 2);
    fieldCombo->addItem("Адрес", 3);
    fieldCombo->addItem("Дата рождения", 4);
    fieldCombo->addItem("Email", 5);
    fieldCombo->addItem("Телефоны", 6);

    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchEdit);
    searchLayout->addWidget(fieldCombo);
    mainLayout->addLayout(searchLayout);

    // подключаем поиск по выбранному полю
    connect(searchEdit, &QLineEdit::textChanged, this, [this, fieldCombo](){
    int column = fieldCombo->currentData().toInt();
        searchByColumn(column);
});

    // Таблица
    table = new QTableWidget(this);
    // добавил
    table->setSelectionMode(QAbstractItemView::SingleSelection); // исключительно выбор одного (Запрещение множественного выделения)
    table->setColumnCount(7);
    QStringList headers;
    headers << "Фамилия" << "Имя" << "Отчество" << "Адрес" 
            << "Дата рождения" << "Email" << "Телефоны";
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSortingEnabled(true);
    mainLayout->addWidget(table);
    
    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addButton = new QPushButton("Добавить", this);
    QPushButton *editButton = new QPushButton("Редактировать", this);
    QPushButton *deleteButton = new QPushButton("Удалить", this);
    QPushButton *saveButton = new QPushButton("Сохранить", this);
    QPushButton *loadButton = new QPushButton("Загрузить", this);
    
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(loadButton);
    mainLayout->addLayout(buttonLayout);
    
    // Подключение сигналов
    connect(addButton, &QPushButton::clicked, this, &PhoneBook::addContact);
    connect(editButton, &QPushButton::clicked, this, &PhoneBook::editContact);
    connect(deleteButton, &QPushButton::clicked, this, &PhoneBook::deleteContact);
    connect(saveButton, &QPushButton::clicked, this, &PhoneBook::saveToFile);
    connect(loadButton, &QPushButton::clicked, this, &PhoneBook::loadFromFile);
    
    // Загрузка данных
    loadFromFile();
}

void PhoneBook::addContact(){
    ContactDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted){
        Contact contact = dialog.getContact();
        contacts.append(contact);
        updateTable();
    }
}

void PhoneBook::editContact(){
    int row = table->currentRow();
    if (row < 0){
        QMessageBox::warning(this, "Ошибка", "Выберите контакт для редактирования");
        return;
    }
    
    int index = table->item(row, 0)->data(Qt::UserRole).toInt(); // запоминание индекса
    ContactDialog dialog(this);
    dialog.setContact(contacts[index]); // добавил (1 правка)

    if (dialog.exec() == QDialog::Accepted){
        contacts[index] = dialog.getContact();
        updateTable();
    }
}


void PhoneBook::deleteContact(){
    int row = table->currentRow();
    if (row < 0){
        QMessageBox::warning(this, "Ошибка", "Выберите контакт для удаления");
        return;
    }
    
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение", 
                                  "Удалить выбранный контакт?",
                                  QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes){
        int index = table->item(row, 0)->data(Qt::UserRole).toInt(); // добавил также как в editContacts (1 правка)
        contacts.removeAt(index);
        updateTable();
    }
}

void PhoneBook::updateTable(){
    table->setSortingEnabled(false);
    table->setRowCount(contacts.size());

    for (int i = 0; i < contacts.size(); i++){ // каждого контакта (1 правка)
        const Contact &c = contacts[i]; // сохраняем индекс контакта в UserRole
        QTableWidgetItem *lastNameItem = new QTableWidgetItem(c.getLastName());
        lastNameItem->setData(Qt::UserRole, i);
        table->setItem(i, 0, lastNameItem);

        table->setItem(i, 1, new QTableWidgetItem(c.getFirstName()));
        table->setItem(i, 2, new QTableWidgetItem(c.getMiddleName()));
        table->setItem(i, 3, new QTableWidgetItem(c.getAddress()));
        table->setItem(i, 4, new QTableWidgetItem(c.getBirthDate().toString("dd.MM.yyyy")));
        table->setItem(i, 5, new QTableWidgetItem(c.getEmail()));
        table->setItem(i, 6, new QTableWidgetItem(c.getPhones().join(", ")));
    }
    table->setSortingEnabled(true);
}

void PhoneBook::saveToFile(){
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи");
        return;
    }
    
    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    
    for (const Contact &c : contacts){
        out << c.toString() << "\n";
    }
    
    file.close();
    QMessageBox::information(this, "Успех", "Данные сохранены");
}

void PhoneBook::loadFromFile(){
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    
    contacts.clear();
    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);
    
    while (!in.atEnd()){
        QString line = in.readLine();
        Contact contact = Contact::fromString(line);
        if (!contact.getLastName().isEmpty()){
            contacts.append(contact);
        }
    }
    
    file.close();
    updateTable();
}

void PhoneBook::searchByColumn(int column){
    QString text = searchEdit->text().trimmed().toLower();
    
    if(text.isEmpty()){
        for(int i=0; i<table->rowCount(); i++)
            table->setRowHidden(i, false);
        return;
    }
    
    for(int i=0; i<table->rowCount(); i++){
        bool found = false;
        
        if(column >= 0 && column < 6){
            if(table->item(i, column) && table->item(i, column)->text().toLower().contains(text)) {
                found = true;
            }
        } else {
            if(table->item(i, 6)){
                QString phones = table->item(i, 6)->text().toLower();
                QStringList phoneList = phones.split(",", Qt::SkipEmptyParts);
                
                for(const QString &phone : phoneList){
                    if(phone.trimmed().contains(text)){
                        found = true;
                        break;
                    }
                }
            }
        } 
        table->setRowHidden(i, !found);
    }
}