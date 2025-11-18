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

PhoneBook::PhoneBook(QWidget *parent) : QWidget(parent){
    filename = "phonebook.txt";
    
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
    
    // Таблица
    table = new QTableWidget(this);
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
    connect(searchEdit, &QLineEdit::textChanged, this, &PhoneBook::searchContacts);
    
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
    
    ContactDialog dialog(this);
    dialog.setContact(contacts[row]);
    
    if (dialog.exec() == QDialog::Accepted){
        contacts[row] = dialog.getContact();
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
        contacts.removeAt(row);
        updateTable();
    }
}

void PhoneBook::updateTable(){
    table->setSortingEnabled(false);
    table->setRowCount(contacts.size());
    
    for (int i = 0; i < contacts.size(); i++){
        const Contact &c = contacts[i];
        
        table->setItem(i, 0, new QTableWidgetItem(c.getLastName()));
        table->setItem(i, 1, new QTableWidgetItem(c.getFirstName()));
        table->setItem(i, 2, new QTableWidgetItem(c.getMiddleName()));
        table->setItem(i, 3, new QTableWidgetItem(c.getAddress()));
        table->setItem(i, 4, new QTableWidgetItem(c.getBirthDate().toString("dd.MM.yyyy")));
        table->setItem(i, 5, new QTableWidgetItem(c.getEmail()));
        table->setItem(i, 6, new QTableWidgetItem(c.getPhones().join(", ")));
    }
    
    table->setSortingEnabled(true);
}

void PhoneBook::searchContacts(){
    QString searchText = searchEdit->text().toLower();
    
    for (int i = 0; i < table->rowCount(); i++){
        bool found = false;
        
        for (int j = 0; j < table->columnCount(); j++){
            QTableWidgetItem *item = table->item(i, j);
            if (item && item->text().toLower().contains(searchText)){
                found = true;
                break;
            }
        }
        
        table->setRowHidden(i, !found);
    }
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
