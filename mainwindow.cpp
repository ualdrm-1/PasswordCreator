#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    m_grid = new QGridLayout(central);
    m_grid->setColumnStretch(2,1);
    m_grid->setColumnStretch(0,0);
    m_grid->setColumnStretch(1,0);
    m_grid->setColumnMinimumWidth(0,400);

    setMainPart();
    setPassPart();
    setUserPart();
    setFilePart();
    setButtons();
    setRightSide();
    setFonts();
    setLimits();
    loadQSSFile();
    loadSettings();

    connect(m_createPass, &QCheckBox::toggled, this, &MainWindow::PassStateChanged);
    connect(m_createUser, &QCheckBox::toggled, this, &MainWindow::UserStateChanged);
    connect(m_saveFile, &QCheckBox::toggled, this, &MainWindow::FileStateChanged);
    connect(m_digit, &QCheckBox::toggled, this, &MainWindow::digitStateChanged);
    connect(m_exSymbols, &QCheckBox::toggled, this, &MainWindow::exSymbStateChanged);
    connect(m_createButton, &QPushButton::clicked, this, &MainWindow::generate);
    connect(m_clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);
    connect(m_chooseFileButton, &QPushButton::clicked, this, &MainWindow::onChooseFileClicked);
    connect(m_saveSettingsButton, &QPushButton::clicked, this, &MainWindow::onSaveSettingsClicked);
    connect(m_createPass, &QCheckBox::toggled, this, &MainWindow::updateButtonState);
    connect(m_createUser, &QCheckBox::toggled, this, &MainWindow::updateButtonState);
    connect(m_saveFile, &QCheckBox::toggled, this, &MainWindow::updateButtonState);

    updateButtonState();

    m_gnr=QRandomGenerator::global();
}

void MainWindow::setMainPart(){
    m_mainTitle = new QLabel("Основное", this);
    m_createPassLabel = new QLabel("Создать пароли", this);
    m_createUserLabel = new QLabel("Создать имена пользователей", this);
    m_saveFileLabel = new QLabel("Сохранить в файл", this);

    m_createPass = new QCheckBox(this);
    m_createUser = new QCheckBox(this);
    m_saveFile = new QCheckBox(this);

    QGridLayout* mainGrid = new QGridLayout;

    m_mainTitle->setObjectName("Title");

    mainGrid->addWidget(m_createPassLabel,0,0);
    mainGrid->addWidget(m_createPass, 0,1);

    mainGrid->addWidget(m_createUserLabel, 1,0);
    mainGrid->addWidget(m_createUser,1,1);

    mainGrid->addWidget(m_saveFileLabel,2,0);
    mainGrid->addWidget(m_saveFile,2,1);

    QWidget* mainWidget = new QWidget(this);
    mainWidget->setObjectName("partWidget");
    mainWidget->setLayout(mainGrid);

    m_grid->addWidget(m_mainTitle, 0,0);
    m_grid->addWidget(mainWidget, 1,0);
}

void MainWindow::setPassPart(){
    m_passTitle = new QLabel("Пароли", this);
    m_passAmountLabel = new QLabel("Количество паролей", this);
    m_symbAmountLabel = new QLabel("Количество символов", this);
    m_symbolsLabel = new QLabel("Символы", this);
    m_latinAlphabetLabel = new QLabel("Латинский алфавит", this);
    m_ruAlphabetLabel = new QLabel("Русский алфавит", this);
    m_digitLabel = new QLabel("Цифры", this);
    m_exSymbolsLabel = new QLabel("Другие символы", this);
    m_passAmountLabel->setFixedWidth(210);

    m_latinAlphabet = new QCheckBox(this);
    m_ruAlphabet = new QCheckBox(this);
    m_digit = new QCheckBox(this);
    m_exSymbols = new QCheckBox(this);

    m_passAmount = new QSpinBox(this);
    m_symbAmount = new QSpinBox(this);

    m_registerChoice = new QComboBox(this);
    QStringList list = {"Верхний и нижний регистры",
                        "Верхний регистр",
                        "Нижний регистр"};
    m_registerChoice->addItems(list);

    m_digitLine = new QLineEdit(this);
    m_exSymbolsLine = new QLineEdit(this);

    m_passTitle->setObjectName("Title");

    QHBoxLayout* latinAlphabetLayout = new QHBoxLayout;
    QHBoxLayout* ruAlphabetLayout = new QHBoxLayout;
    QHBoxLayout* digitLayout = new QHBoxLayout;
    QHBoxLayout* exSymbolsLayout = new QHBoxLayout;

    latinAlphabetLayout->addWidget(m_latinAlphabet);
    latinAlphabetLayout->addWidget(m_latinAlphabetLabel);
    latinAlphabetLayout->addStretch();

    ruAlphabetLayout->addWidget(m_ruAlphabet);
    ruAlphabetLayout->addWidget(m_ruAlphabetLabel);
    ruAlphabetLayout->addStretch();

    digitLayout->addWidget(m_digit);
    digitLayout->addWidget(m_digitLabel);
    digitLayout->addStretch();

    exSymbolsLayout->addWidget(m_exSymbols);
    exSymbolsLayout->addWidget(m_exSymbolsLabel);
    exSymbolsLayout->addStretch();

    QGridLayout* passGrid = new QGridLayout;
    passGrid->addWidget(m_passAmountLabel,0,0);
    passGrid->addWidget(m_passAmount, 0,1);
    passGrid->addWidget(m_symbAmountLabel,1,0);
    passGrid->addWidget(m_symbAmount,1,1);
    passGrid->addWidget(m_symbolsLabel,2,0);
    passGrid->addLayout(latinAlphabetLayout,2,1);
    passGrid->addLayout(ruAlphabetLayout,3,1);
    passGrid->addWidget(m_registerChoice,4,1);
    passGrid->addLayout(digitLayout,5,1);
    passGrid->addWidget(m_digitLine, 6,1);
    passGrid->addLayout(exSymbolsLayout,7,1);
    passGrid->addWidget(m_exSymbolsLine, 8,1);

    QWidget* passWidget = new QWidget(this);
    passWidget->setObjectName("partWidget");
    passWidget->setLayout(passGrid);

    m_grid->addWidget(m_passTitle,2,0);
    m_grid->addWidget(passWidget, 3,0);
}

void MainWindow::setUserPart(){
    m_userTitle = new QLabel("Имена пользователей", this);
    m_userAmountLabel = new QLabel("Количество имен", this);
    m_userPrefixLabel = new QLabel("Префикс", this);
    m_startDigCountLabel = new QLabel("Начальное значение счётчика");
    m_countStepLabel = new QLabel("Шаг счётчика", this);

    m_userAmount = new QSpinBox(this);
    m_startDigCount = new QSpinBox(this);
    m_countStep = new QSpinBox(this);

    m_userPrefixLine = new QLineEdit(this);

    m_userTitle->setObjectName("Title");

    userGrid = new QGridLayout;
    userGrid->addWidget(m_userAmountLabel,0,0);
    userGrid->addWidget(m_userAmount,0,1);
    userGrid->addWidget(m_userPrefixLabel,1,0);
    userGrid->addWidget(m_userPrefixLine,1,1);
    userGrid->addWidget(m_startDigCountLabel,2,0);
    userGrid->addWidget(m_startDigCount,2,1);
    userGrid->addWidget(m_countStepLabel,3,0);
    userGrid->addWidget(m_countStep,3,1);

    QWidget* userWidget = new QWidget(this);
    userWidget->setObjectName("partWidget");
    userWidget->setLayout(userGrid);

    m_grid->addWidget(m_userTitle,4,0);
    m_grid->addWidget(userWidget,5,0);
}

void MainWindow::setFilePart(){
    m_fileTitle = new QLabel("Файл", this);
    m_filePathLabel = new QLabel("Путь до файла", this);
    m_fileFormatLabel = new QLabel("Формат файла", this);

    m_chooseFileButton = new QPushButton("Обзор",this);

    m_filePathLine = new QLineEdit(this);

    m_fileFormatChoice = new QComboBox(this);
    QStringList list = {"Текстовый (.txt)",
                        "Двоичный (.bin)"};
    m_fileFormatChoice->addItems(list);

    m_fileTitle->setObjectName("Title");

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(m_filePathLine);
    hLayout->addWidget(m_chooseFileButton);

    QGridLayout* fileGrid = new QGridLayout;
    fileGrid->addWidget(m_filePathLabel,0,0);
    fileGrid->addLayout(hLayout,0,1);
    fileGrid->addWidget(m_fileFormatLabel,1,0);
    fileGrid->addWidget(m_fileFormatChoice,1,1);

    QWidget* fileWidget = new QWidget(this);
    fileWidget->setObjectName("partWidget");
    fileWidget->setLayout(fileGrid);

    m_grid->addWidget(m_fileTitle,6,0);
    m_grid->addWidget(fileWidget,7,0);
}

void MainWindow::setButtons(){
    m_createButton = new QPushButton("Создать",this);
    m_createButton->setObjectName("CreateButton");
    m_saveSettingsButton = new QPushButton("Сохранить настройки",this);
    m_clearButton = new QPushButton("Очистить",this);

    QHBoxLayout* leftSideButtons = new QHBoxLayout;
    leftSideButtons->addWidget(m_createButton);
    leftSideButtons->addWidget(m_saveSettingsButton);

    m_grid->addLayout(leftSideButtons,8,0,Qt::AlignRight);
    m_grid->addWidget(m_clearButton, 8,2,Qt::AlignRight);
}

void MainWindow::setRightSide(){
    m_resultTitle = new QLabel("Результат",this);
    m_textView = new QPlainTextEdit(this);
    m_textView->setObjectName("Console");
    m_textView->setMinimumWidth(500);

    m_resultTitle->setObjectName("Title");

    QWidget* consoleWidget = new QWidget(this);
    consoleWidget->setObjectName("ConsoleWidget");
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(m_textView);
    consoleWidget->setLayout(layout);

    m_grid->addWidget(m_resultTitle,0,2);
    m_grid->addWidget(consoleWidget,1,2,7,1);
}

void MainWindow::setFonts(){
    int fontMBlack = QFontDatabase::addApplicationFont(":/fonts/fonts/Montserrat-Black.ttf");
    QStringList fontFamilyMontserratBlack= QFontDatabase::applicationFontFamilies(fontMBlack);
    QString fontMontserrat = fontFamilyMontserratBlack.at(0);

    int fontExLight = QFontDatabase::addApplicationFont(":/fonts/fonts/Montserrat-ExtraLight.ttf");
    QStringList fontFamilyMontserratExLight= QFontDatabase::applicationFontFamilies(fontExLight);
    fontMontserrat = fontFamilyMontserratExLight.at(0);

    int fontMRegular = QFontDatabase::addApplicationFont(":/fonts/fonts/Montserrat-Regular.ttf");
    QStringList fontFamilyMontserratRegular= QFontDatabase::applicationFontFamilies(fontMRegular);
    fontMontserrat = fontFamilyMontserratRegular.at(0);

    qApp->setProperty("Montserrat Black", fontMontserrat);
    qApp->setProperty("Montserrat Extra Light", fontMontserrat);
    qApp->setProperty("Montserrat Regular", fontMontserrat);
}

void MainWindow::loadQSSFile(){
    QFile qssFile(":/qss/style.qss");
    qssFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString style = qssFile.readAll();
    this->setStyleSheet(style);
    qssFile.close();
}

void MainWindow::startValue(){
    m_createPass->setChecked(false);
    PassStateChanged(false);

    m_createUser->setChecked(false);
    UserStateChanged(false);

    m_saveFile->setChecked(false);
    FileStateChanged(false);
}

void MainWindow::setLimits(){
    m_passAmount->setRange(1,50);
    m_symbAmount->setRange(5,15);
    m_userAmount->setRange(1,50);
    m_countStep->setMinimum(1);

    m_digitLine->setMaxLength(10);
    m_exSymbolsLine->setMaxLength(10);
    m_userPrefixLine->setMaxLength(15);

    m_digitLine->setPlaceholderText("0123456789");
    m_exSymbolsLine->setPlaceholderText("!@#$%_- и пр.");
    m_userPrefixLine->setPlaceholderText("User_");
}

QStringList MainWindow::generatePasswordsAndUsers(){
    QString alphabet="";
    QStringList list;

    int comboIndex = m_registerChoice->currentIndex();

    if(m_latinAlphabet->isChecked()){
        switch(comboIndex){
        case 0:
            alphabet+=m_latinLowerAlphabet+m_latinUpperAlphabet;
            break;
        case 1:
            alphabet+=m_latinUpperAlphabet;
            break;
        default:
            alphabet+=m_latinLowerAlphabet;
            break;
        }
    }

    if(m_ruAlphabet->isChecked()){
        switch(comboIndex){
        case 0:
            alphabet+=m_ruLowerAlphabet+m_ruUpperAlphabet;
            break;
        case 1:
            alphabet+=m_ruUpperAlphabet;
            break;
        default:
            alphabet+=m_ruLowerAlphabet;
            break;
        }
    }

    if(m_digit->isChecked()){
        if(m_digitLine->text().isEmpty()){
            showWarning("Ошибка","Поле \"Цифры\" пустое!");
            return list;
        }
        alphabet+=m_digitLine->text();
    }

    if(m_exSymbols->isChecked()){
        if(m_exSymbolsLine->text().isEmpty()){
            showWarning("Ошибка","Поле \"Другие символы\" пустое!");
            return list;
        }
        alphabet+=m_exSymbolsLine->text();
    }

    for(int i=0; i<m_passAmount->value(); ++i){
        list.append(generatePasswords(alphabet));
    }

    return list;
}

QString MainWindow::generatePasswords(QString& alphabet){
    int length = m_symbAmount->value();

    QString res="";

    for(int i=0; i<length; ++i){
        int index = m_gnr->generate()%alphabet.size();
        res+=alphabet.at(index);
    }

    return res;
}

QStringList MainWindow::generateUsers(){
    QStringList res;

    int last=m_userAmount->value()+m_startDigCount->value();

    QString prefix = m_userPrefixLine->text();

    for(int i=m_startDigCount->value(); i<last; ++i){
        res.append(prefix+QString::number(i));
    }

    return res;
}

void MainWindow::printPasswordAndUsers(QStringList& usersList, QStringList& passwordsList){
    int maxSize = qMax(passwordsList.length(), usersList.length());

    for(int i = 0; i < maxSize; ++i){
        QString user = (i < usersList.length()) ? usersList[i] : "";
        QString password = (i < passwordsList.length()) ? passwordsList[i] : "";

        if(!user.isEmpty() && !password.isEmpty()){
            m_textView->appendPlainText(user + ":\t" + password + "\n");
        }
        else if(!user.isEmpty()){
            m_textView->appendPlainText(user + "\n");
        }
        else if(!password.isEmpty()){
            m_textView->appendPlainText("\t" + password + "\n");
        }
    }
}

void MainWindow::showWarning(const QString title, const QString text){
    QMessageBox msg(this);
    msg.setWindowTitle(title);
    msg.setText(text);
    msg.setIcon(QMessageBox::Warning);
    msg.addButton("Принять", QMessageBox::AcceptRole);
    msg.exec();
}

void MainWindow::loadSettings(){
    QSettings settings;
    if(!settings.contains("main/passwords")){
        startValue();
        return;
    }

    m_createPass->setChecked(settings.value("main/passwords", false).toBool());
    m_createUser->setChecked(settings.value("main/users", false).toBool());
    m_saveFile->setChecked(settings.value("main/file", false).toBool());

    m_passAmount->setValue(settings.value("passwords/amount", 1).toInt());
    m_symbAmount->setValue(settings.value("passwords/symbols_amount", 8).toInt());
    m_latinAlphabet->setChecked(settings.value("passwords/latin_alphabet", true).toBool());
    m_ruAlphabet->setChecked(settings.value("passwords/russian_alphabet", false).toBool());
    m_digit->setChecked(settings.value("passwords/digits", true).toBool());
    m_exSymbols->setChecked(settings.value("passwords/extra_symbols", false).toBool());
    m_registerChoice->setCurrentIndex(settings.value("passwords/register_choice", 0).toInt());
    m_digitLine->setText(settings.value("passwords/digits_text", "0123456789").toString());
    m_exSymbolsLine->setText(settings.value("passwords/extra_symbols_text", "!@#$%_-").toString());

    m_userAmount->setValue(settings.value("users/amount", 1).toInt());
    m_userPrefixLine->setText(settings.value("users/prefix", "User_").toString());
    m_startDigCount->setValue(settings.value("users/start_count", 1).toInt());
    m_countStep->setValue(settings.value("users/count_step", 1).toInt());

    m_filePathLine->setText(settings.value("file/path", "").toString());
    m_fileFormatChoice->setCurrentIndex(settings.value("file/format", 0).toInt());

    PassStateChanged(m_createPass->isChecked());
    UserStateChanged(m_createUser->isChecked());
    FileStateChanged(m_saveFile->isChecked());
    digitStateChanged(m_digit->isChecked());
    exSymbStateChanged(m_exSymbols->isChecked());
}
// слоты
void MainWindow::PassStateChanged(bool checked){
    m_passTitle->setEnabled(checked);
    m_passAmountLabel->setEnabled(checked);
    m_symbolsLabel->setEnabled(checked);
    m_latinAlphabetLabel->setEnabled(checked);
    m_ruAlphabetLabel->setEnabled(checked);
    m_digitLabel->setEnabled(checked);
    m_exSymbolsLabel->setEnabled(checked);
    m_symbAmountLabel->setEnabled(checked);

    m_latinAlphabet->setEnabled(checked);
    m_ruAlphabet->setEnabled(checked);
    m_passAmount->setEnabled(checked);
    m_symbAmount->setEnabled(checked);
    m_registerChoice->setEnabled(checked);
    m_digit->setEnabled(checked);
    m_digitLine->setEnabled(checked);
    m_exSymbols->setEnabled(checked);
    m_exSymbolsLine->setEnabled(checked);
}

void MainWindow::UserStateChanged(bool checked){
    m_userTitle->setEnabled(checked);
    m_userAmountLabel->setEnabled(checked);
    m_userPrefixLabel->setEnabled(checked);
    m_startDigCountLabel->setEnabled(checked);
    m_countStepLabel->setEnabled(checked);

    m_userAmount->setEnabled(checked);
    m_userPrefixLine->setEnabled(checked);
    m_startDigCount->setEnabled(checked);
    m_countStep->setEnabled(checked);
}

void MainWindow::FileStateChanged(bool checked){
    m_fileTitle->setEnabled(checked);
    m_filePathLabel->setEnabled(checked);
    m_fileFormatLabel->setEnabled(checked);

    m_chooseFileButton->setEnabled(checked);
    m_filePathLine->setEnabled(checked);
    m_fileFormatChoice->setEnabled(checked);
}

void MainWindow::onClearButtonClicked(){
    m_textView->clear();
}

void MainWindow::generate(){
    QStringList passwordList;
    QStringList userList;

    if(m_createPass->isChecked() && m_createUser->isChecked()){
        passwordList = generatePasswordsAndUsers();
        userList = generateUsers();
        if(userList.isEmpty()) return;
        if(passwordList.isEmpty()) return;

        if(passwordList.length()==userList.length()){
            for(int i=0; i<passwordList.length();++i){
                m_textView->appendPlainText(userList[i]+":\t"+passwordList[i]+"\n");
            }
        }else{
            printPasswordAndUsers(userList, passwordList);
        }

    }else if(m_createPass->isChecked() && !m_createUser->isChecked()){
        passwordList = generatePasswordsAndUsers();
        if(passwordList.isEmpty()) return;

        for(QString& pas: passwordList){
            m_textView->appendPlainText(pas);
        }
    }else if(!m_createPass->isChecked() && m_createUser->isChecked()){
        userList = generateUsers();
        if(userList.isEmpty()) return;

        for(QString& usr: userList){
            m_textView->appendPlainText(usr);
        }
    }

    if(m_saveFile->isChecked()){
        if(m_filePathLine->text().trimmed().isEmpty()){
            showWarning("Ошибка",
                        "Не указан путь для сохранения файла");
            return;
        }
        QString directory = m_filePathLine->text().trimmed();
        QString fileName;

        if(m_fileFormatChoice->currentIndex() == 0) {
            fileName = "passwords.txt";
        } else {
            fileName = "passwords.bin";
        }

        QString filePath = QDir(directory).filePath(fileName);
        QFile file(filePath);

        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            showWarning("Ошибка","Файл недоступен для записи!");
            return;
        }

        QTextStream out(&file);

        if(passwordList.size() > 0 && userList.size() > 0){
            int countValues = qMin(passwordList.size(), userList.size());
            for(int i = 0; i < countValues; i++){
                QString str = userList.at(i) + "\t" + passwordList.at(i) + "\n";
                out << str;
            }
        }else if(passwordList.size() > 0){
            for(QString& pass: passwordList){
                out << pass << "\n";
            }
        }else if(userList.size() > 0){
            for(QString& user: userList){
                out << user << "\n";
            }
        }

        file.close();
    }
}

void MainWindow::exSymbStateChanged(bool checked){
    m_exSymbolsLine->setEnabled(checked);
}

void MainWindow::digitStateChanged(bool checked){
    m_digitLine->setEnabled(checked);
}

void MainWindow::updateButtonState(){
    bool selected = m_createPass->isChecked() ||
                    m_createUser->isChecked() ||
                    m_saveFile  ->isChecked();
    m_createButton->setEnabled(selected);
}

void MainWindow::onChooseFileClicked(){
    QString fileName = QFileDialog::getExistingDirectory(this,   "Выбрать папку",
                                                         "C:\\", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!fileName.isEmpty()) m_filePathLine->setText(fileName);
}

void MainWindow::onSaveSettingsClicked(){
    QSettings settings;

    settings.setValue("main/passwords", m_createPass->isChecked());
    settings.setValue("main/users", m_createUser->isChecked());
    settings.setValue("main/file", m_saveFile->isChecked());

    settings.setValue("passwords/amount", m_passAmount->value());
    settings.setValue("passwords/symbols_amount", m_symbAmount->value());
    settings.setValue("passwords/latin_alphabet", m_latinAlphabet->isChecked());
    settings.setValue("passwords/russian_alphabet", m_ruAlphabet->isChecked());
    settings.setValue("passwords/digits", m_digit->isChecked());
    settings.setValue("passwords/extra_symbols", m_exSymbols->isChecked());
    settings.setValue("passwords/register_choice", m_registerChoice->currentIndex());
    settings.setValue("passwords/digits_text", m_digitLine->text());
    settings.setValue("passwords/extra_symbols_text", m_exSymbolsLine->text());

    settings.setValue("users/amount", m_userAmount->value());
    settings.setValue("users/prefix", m_userPrefixLine->text());
    settings.setValue("users/start_count", m_startDigCount->value());
    settings.setValue("users/count_step", m_countStep->value());

    settings.setValue("file/path", m_filePathLine->text());
    settings.setValue("file/format", m_fileFormatChoice->currentIndex());

    showWarning("Сохранение настроек", "Настройки сохранены!");
}
//

MainWindow::~MainWindow() {}
