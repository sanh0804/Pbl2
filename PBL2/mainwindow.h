#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QComboBox>
#include <QRadioButton>
#include <QPushButton>
#include <QTextEdit>
#include <arrayadmin.h>
#include <arraypatient.h>
#include <arraydepartement.h>
#include <arrayroom.h>
#include <arraybed.h>
#include <arraydoctor.h>
#include <bits/stdc++.h>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_patient_btn_clicked();

    void on_ok_btn_clicked();

    void on_manage_btn_clicked();

    void on_case_record_btn_clicked();

    void on_yes_btn_clicked();

    void on_no_btn_clicked();

    void on_htr_btn_clicked();

    void on_repair_inf_ptn_btn_clicked();

    void on_back_btn_clicked();

    void on_add_htr_btn_clicked();

    void on_list_case_record_cellDoubleClicked(int row, int column);

    void on_save_htr_btn_clicked();

    void on_edit_htr_btn_3_clicked();

    void on_del_htr_btn_4_clicked();

    void on_home_btn_clicked();

    void on_ok_btn_2_clicked();

    void on_room_btn_clicked();

    void on_list_room_cbb_2_activated(const QString &arg1);

    void on_all_bed_btn_clicked();

    void on_list_room_cbb_1_activated(const QString &arg1);

    void on_admit_to_hospital_btn_clicked();

    void on_id_bed_search_input_textChanged(const QString &arg1);

    void on_quit_hp_btn_clicked();

    void on_admit_quit_hp_savebtn_clicked();

    void on_admit_hp_cbb_4_activated(const QString &arg1);

    void on_admit_hp_cbb_5_activated(const QString &arg1);

    void on_list_room_filter_btn_clicked();

    void on_patient_search_input_textChanged(const QString &arg1);

    void on_list_patient_cellDoubleClicked(int row, int column);

    void on_list_room_cellDoubleClicked(int row, int column);

    void on_new_inf_ptn_button_clicked();

    void on_login_btn_clicked();

    void on_login_ok_btn_clicked();

    void on_doctor_btn_clicked();

    void on_doctor_search_input_textChanged(const QString &arg1);

    void on_list_doctor_cellDoubleClicked(int row, int column);

    void on_new_inf_ptn_button_2_clicked();

protected:
    void clickedButton(int i);

    void clickedButtonInManagePage(int i);

    void clearInputText();

    void disableInforPatientInput();

    void enableInforPatientInput();

    void hiddenRoomInfor();

    void showRoomInfor();

    void clearAllItems(QComboBox*);

    void clearRadioChecked(QRadioButton *[], int);

    void addInforPtnData(int i, QLineEdit *[], QRadioButton *[], QTextEdit *[]);

    void addDataToCaseRecordTable(int, QString);

    void addDataToRoomTable(int, QString, QString, int *);

    void addDataToViewCaseDetailPg(QString);

    bool checkComboboxIsFilled(QComboBox *[], int);

    bool checkString(QString);

private:
    Ui::MainWindow *ui;
    int menu = 0;
    QSqlDatabase myDB;
    arrayAdmin listAd;
    arrayPatient listPatient;
    arrayDepartement listDepartement;
    arrayBed listBed;
    arrayRoom listRoom;
    arrayDoctor listDoctor;

    int editOrSave = 1;

    stack <int> page_back;

    int homePage = 0, notifyPage = 1, mangePage = 2, loginPage = 3;

    const int homeMangePage = 0, listPatientPage = 1, idPatientInput = 2, idPatientError = 3, inforPatientPage = 4,
        listCaseRecordPage = 5, detailCaseRecordPage = 6, idRecordInput = 7,
        listRoomPage = 8, admitToHospitalPage = 9, inforRoomPage = 10, listDoctorPage = 11, inforDoctorPage = 12;

    QString doctorId = "";
};
#endif // MAINWINDOW_H
