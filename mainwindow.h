#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QFontDatabase>
#include <QMessageBox>
#include <QSettings>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel* m_mainTitle;//
    QLabel* m_passTitle;//
    QLabel* m_userTitle;//
    QLabel* m_fileTitle;//
    QLabel* m_resultTitle;

    QLabel* m_createPassLabel;//
    QLabel* m_createUserLabel;//
    QLabel* m_saveFileLabel;//
    QLabel* m_passAmountLabel;//
    QLabel* m_symbAmountLabel;//
    QLabel* m_latinAlphabetLabel;//
    QLabel* m_symbolsLabel;//
    QLabel* m_ruAlphabetLabel;//
    QLabel* m_userAmountLabel;//
    QLabel* m_userPrefixLabel;//
    QLabel* m_digitLabel;//
    QLabel* m_exSymbolsLabel;//
    QLabel* m_startDigCountLabel;//
    QLabel* m_countStepLabel;//
    QLabel* m_filePathLabel;//
    QLabel* m_fileFormatLabel;//

    QSpinBox* m_passAmount;//
    QSpinBox* m_symbAmount;//
    QSpinBox* m_startDigCount;//
    QSpinBox* m_countStep;//
    QSpinBox* m_userAmount;//

    QCheckBox* m_createPass;//
    QCheckBox* m_createUser;//
    QCheckBox* m_saveFile;//
    QCheckBox* m_latinAlphabet;//
    QCheckBox* m_ruAlphabet;//
    QCheckBox* m_digit;//
    QCheckBox* m_exSymbols;//

    QLineEdit* m_digitLine;//
    QLineEdit* m_exSymbolsLine;//
    QLineEdit* m_userPrefixLine;//
    QLineEdit* m_filePathLine;//

    QComboBox* m_registerChoice;//
    QComboBox* m_fileFormatChoice;//

    QPushButton* m_createButton;//
    QPushButton* m_saveSettingsButton;//
    QPushButton* m_clearButton;//
    QPushButton* m_chooseFileButton;//

    QFileDialog* m_chooseFile;//

    QPlainTextEdit* m_textView;//

    QGridLayout* m_grid;//
    QGridLayout* userGrid;//

    QRandomGenerator* m_gnr;

    const QString m_latinLowerAlphabet="qwertyuiopasdfghjklzxcvbnm";
    const QString m_latinUpperAlphabet="QWERTYUIOPASDFGHJKLZXCVBNM";
    const QString m_ruLowerAlphabet="йцукенгшщзхъфывапролджэячсмитьбю";
    const QString m_ruUpperAlphabet="ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ";

    void setMainPart();
    void setPassPart();
    void setUserPart();
    void setFilePart();
    void setButtons();
    void setRightSide();
    void setFonts();
    void startValue();
    void setLimits();
    void printPasswordAndUsers(QStringList& passwordsList, QStringList& usersList);
    void showWarning(const QString title, const QString text);
    void loadSettings();

    QStringList generatePasswordsAndUsers();

    QStringList generateUsers();
    QString generatePasswords(QString& alphabet);

    void loadQSSFile();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void PassStateChanged(bool checked);
    void UserStateChanged(bool checked);
    void FileStateChanged(bool checked);
    void digitStateChanged(bool checked);
    void exSymbStateChanged(bool checked);
    void updateButtonState();
    void onChooseFileClicked();
    void onClearButtonClicked();
    void generate();
    void onSaveSettingsClicked();
};
#endif // MAINWINDOW_H
