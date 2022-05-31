#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Quản lý phòng bệnh");
    this->setWindowIcon(QIcon("C:/Users/sanhg/OneDrive/Máy tính/sources/img/app_icon.png"));

    ui->avar_icon->setVisible(false);
    ui->change_room_btn->setVisible(false);
    ui->list_patient->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->list_room->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->list_doctor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap px("C:/Users/sanhg/OneDrive/Máy tính/sources/img/home_img.png");
    ui->home_img->setPixmap(px.scaled(ui->home_img->width(), ui->home_img->height(), Qt::KeepAspectRatio));

    px = QPixmap("C:/Users/sanhg/OneDrive/Máy tính/sources/img/manage_icon.png");
    ui->home_manage_icon->setPixmap(px.scaled(ui->home_manage_icon->width(), ui->home_manage_icon->height(), Qt::KeepAspectRatio));

    px = QPixmap("C:/Users/sanhg/OneDrive/Máy tính/sources/img/avar_icon.png");
    ui->avar_icon->setPixmap(px.scaled(ui->avar_icon->size(), Qt::KeepAspectRatio));

    ui->stackedWidget->setCurrentIndex(homePage);

// set chiều rộng cho bảng bệnh án
    int id_benh_an_col = 0, chieu_cao_col = 1, can_nang_col = 2, tinh_trang_col = 3,
            ngay_kham_col = 4, ngay_tai_kham_col = 5, don_thuoc_col = 6;

    for (auto i: {id_benh_an_col, ngay_tai_kham_col, ngay_kham_col})
        ui->list_case_record->setColumnWidth(i, 100);
    for (auto i: {chieu_cao_col, can_nang_col})
        ui->list_case_record->setColumnWidth(i, 70);
    for (auto i: {tinh_trang_col, don_thuoc_col})
        ui->list_case_record->setColumnWidth(i, (ui->list_case_record->width() - 3*100 - 2*70)/2 - 1);

// tạo kết nối tới database
    myDB = QSqlDatabase::addDatabase("QODBC");
    QString connectString = "Driver={SQL Server Native Client 11.0};";
    connectString.append("Server=DESKTOP-F5NCIAK;");
    connectString.append("Database=PBL;");
    connectString.append("Trusted_connection=yes;");
    myDB.setDatabaseName(connectString);

//  kiểm tra kết nối
    if(myDB.open()){
        ui->check->setText("Conect to Database: Oke");
    }
    else{
        ui->check->setText("");
    }

//  truy vấn dữ liệu bệnh nhân
    QSqlQuery query;
    query.exec("select id_BN, ten, tuoi, gioi_tinh, dia_chi, sdt, lich_su, nhom_mau, chieu_cao, can_nang from BENHNHAN");
    while(query.next())
    {
       listPatient.add(patient(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toString()
                      , query.value(4).toString(), query.value(5).toString(), query.value(6).toInt(), query.value(7).toString(), query.value(8).toFloat(), query.value(9).toFloat()));
    }
// truy vấn dữ liệu khoa
    query.exec("select id_khoa, ten_khoa from KHOA order by ten_khoa");
    while(query.next()){
        listDepartement.add(departement(query.value(0).toString(), query.value(1).toString()));
    }

    for(int i = 0; i < listDepartement.length(); i++){
        ui->list_room_cbb_1->addItem(listDepartement[i].getDepartementName());
        ui->admit_hp_cbb_4->addItem(listDepartement[i].getDepartementName());
    }
// truy vấn dữ liệu phòng
    query.exec("select id_phong, loai_phong, so_giuong, KHOA.id_khoa, KHOA.ten_khoa from PHONGBENH inner join KHOA on PHONGBENH.id_khoa = KHOA.id_khoa");
    while(query.next()){
        listRoom.add(room(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toString()));
    }

// truy vấn dữ liệu giường bệnh
    query.exec("select id_giuong, trang_thai, GIUONGBENH.id_phong, PHONGBENH.loai_phong, PHONGBENH.so_giuong, KHOA.id_khoa, KHOA.ten_khoa from GIUONGBENH inner join PHONGBENH on GIUONGBENH.id_phong = PHONGBENH.id_phong inner join KHOA on PHONGBENH.id_khoa = KHOA.id_khoa");
    while(query.next()){
        QSqlQuery q(myDB);
        q.exec("select id_BN from NHAPVIEN where id_giuong = '" + query.value(0).toString() + "' order by ngay_nhap_vien desc");
        q.first();
        if(q.value(0).toString() != "")
        {
            listBed.add(bed(query.value(0).toString(), query.value(1).toInt(), q.value(0).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toInt(), query.value(5).toString(), query.value(6).toString()));
        }
        else
            listBed.add(bed(query.value(0).toString(), query.value(1).toInt(), "", query.value(2).toString(), query.value(3).toString(), query.value(4).toInt(), query.value(5).toString(), query.value(6).toString()));
    }

// truy vấn dữ liệu ad
    query.exec("select id_BS, ten_dn, pass from ADMIN");
    while(query.next()){
        listAd.add(admin(query.value(0).toString(), query.value(1).toString(), query.value(2).toString()));
    }

// truy vấn dữ liệu bác sĩ
    query.exec("select id_BS, ten, tuoi, gioi_tinh, dia_chi, sdt, KHOA.id_khoa, KHOA.ten_khoa from BACSI inner join KHOA on BACSI.id_khoa = KHOA.id_khoa order by BACSI.ten");
    while(query.next()){
        listDoctor.add(doctor(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString(), query.value(6).toString(), query.value(7).toString()));
    }
}

MainWindow::~MainWindow()
{
    myDB.close();
    delete ui;
}

void MainWindow::clickedButton(int i){
    QPushButton *qbb[] = {ui->home_btn, ui->manage_btn};

    for(auto p: qbb)
        p->setStyleSheet("QPushButton{border: none;color: white;font-size: 16px;}QPushButton:hover{color: #ccc;}");

    if(i != -1)
        qbb[i]->setStyleSheet("QPushButton{border: none; border-bottom: 1px solid #dedede;color: white;font-size: 16px;}");
}

void MainWindow::clickedButtonInManagePage(int i){
    QPushButton *qbb[] = {ui->patient_btn, ui->case_record_btn, ui->room_btn, ui->doctor_btn};
    for(auto p:qbb)
        p->setStyleSheet("QPushButton{border: none;color: white;font-size: 15px;text-align: left;}QPushButton:hover{color: #ccc;}");

    if(i != -1)
        qbb[i]->setStyleSheet("QPushButton{border: none;color: #ccc;font-size: 15px;text-align: left;}");
}
// xóa dữ liệu cũ trang thông tin bệnh nhân
void MainWindow::clearInputText(){
    QLineEdit *qledit[] = {ui->infor_ptn_input_1, ui->infor_ptn_input_2, ui->infor_ptn_input_3, ui->infor_ptn_input_4, ui->infor_ptn_input_6, ui->infor_ptn_input_7};
    QTextEdit *qtedit[] = {ui->infor_ptn_input_5};
    QRadioButton *qrdiobtn[] = {ui->radioButton, ui->radioButton_2, ui->radioButton_3};
    for (auto p: qledit)
        p->setText("");
    for (auto p: qtedit)
        p->setText("");
    for (auto p: qrdiobtn)
    {
        p->setAutoExclusive(false);
        p->setChecked(false);
        p->setAutoExclusive(true);
    }

    ui->infor_ptn_cbb->setCurrentIndex(-1);
}

void MainWindow::clearAllItems(QComboBox* cb){// xóa dữ liệu trong combobox
    while(cb->count()!=0){
        cb->removeItem(0);
    }
}

void MainWindow::clearRadioChecked(QRadioButton *qrbtn[], int n){// bỏ checked radio button
    for(int i = 0; i < n; i++){
        qrbtn[i]->setAutoExclusive(false);
        qrbtn[i]->setChecked(false);
        qrbtn[i]->setAutoExclusive(true);
    }
}

void MainWindow::disableInforPatientInput(){// vô hiệu hóa các ô input trang thông tin bệnh nhân
    QLineEdit *qledit[] = {ui->infor_ptn_input_1, ui->infor_ptn_input_2, ui->infor_ptn_input_3, ui->infor_ptn_input_4, ui->infor_ptn_input_6, ui->infor_ptn_input_7};
    QTextEdit *qtedit[] = {ui->infor_ptn_input_5};
    QComboBox *qcbb[] = {ui->infor_ptn_cbb};
    QRadioButton *qrdo[] = {ui->radioButton, ui->radioButton_2, ui->radioButton_3};
    for (auto p: qledit)
        p->setEnabled(false);
    for (auto p: qtedit)
        p->setEnabled(false);
    for (auto p: qcbb)
        p->setEnabled(false);
    for (auto p: qrdo)
        p->setEnabled(false);
}

void MainWindow::enableInforPatientInput(){// bỏ vô hiệu hóa các ô input trang thông tin bệnh nhân
    QLineEdit *qledit[] = {ui->infor_ptn_input_2, ui->infor_ptn_input_3, ui->infor_ptn_input_4, ui->infor_ptn_input_6, ui->infor_ptn_input_7};
    QTextEdit *qtedit[] = {ui->infor_ptn_input_5};
    QComboBox *qcbb[] = {ui->infor_ptn_cbb};
    QRadioButton *qrdo[] = {ui->radioButton, ui->radioButton_2, ui->radioButton_3};
    for (auto p: qledit)
        p->setEnabled(true);
    for (auto p: qtedit)
        p->setEnabled(true);
    for (auto p: qcbb)
        p->setEnabled(true);
    for (auto p: qrdo)
        p->setEnabled(true);
}

// Hiện thông tin phòng
void MainWindow::showRoomInfor(){
    QLabel *qlb[] = {ui->hospitalize_label, ui->dp_label, ui->room_label, ui->bed_label};
    for (auto p: qlb){
        p->setVisible(true);
        p->setEnabled(false);
    }

    QLineEdit *qledit[] = {ui->infor_ptn_input_8, ui->infor_ptn_input_9, ui->infor_ptn_input_10};
    for (auto p:qledit){
        p->setVisible(true);
        p->setEnabled(false);
    }
}

// Ẩn thông tin phòng
void MainWindow::hiddenRoomInfor()
{
    QLabel *qlb[] = {ui->hospitalize_label, ui->dp_label, ui->room_label, ui->bed_label};
    for (auto p: qlb)
        p->setVisible(false);
    QLineEdit *qledit[] = {ui->infor_ptn_input_8, ui->infor_ptn_input_9, ui->infor_ptn_input_10};
    for (auto p:qledit)
        p->setVisible(false);
}

//Thêm thông tin vào bảng bệnh án
void MainWindow::addDataToCaseRecordTable(int row, QString id_BN){
    while(row){
        ui->list_case_record->removeRow(row - 1);
        row --;
    }

    QSqlQuery query(myDB);
    query.exec("select id_benh_an, chieu_cao, can_nang, tinh_trang, ngay_tai_kham, ngay_kham, don_thuoc from BENHAN where id_BN = '" + id_BN + "'");
    while(query.next()){
        ui->list_case_record->insertRow(row);
        for (int i = 0; i < 7; i++){
            ui->list_case_record->setItem(row, i, new QTableWidgetItem(query.value(i).toString()));
        }
        row ++;
    }
}

void MainWindow::addDataToRoomTable(int row, QString id_room, QString name_dep, int *status){
    QSqlQuery query(myDB);
    arrayBed tmpt;

    while(row){
        ui->list_room->removeRow(row - 1);
        row --;
    }
    if(name_dep != "Departement"){
        if(id_room != "Room"){
            for(int i = 0; i < listBed.length(); i++){
                if(listBed[i].getRoomId() == id_room && listBed[i].getDepartementName() == name_dep && (listBed[i].getBedStatus() == status[0] || listBed[i].getBedStatus() == status[1]))
                    tmpt.add(listBed[i]);
            }
        }
        else{
            for(int i = 0; i < listBed.length(); i++){
                if(listBed[i].getDepartementName() == name_dep && (listBed[i].getBedStatus() == status[0] || listBed[i].getBedStatus() == status[1]))
                    tmpt.add(listBed[i]);
            }
        }
    }
    else{
        for(int i = 0; i < listBed.length(); i++){
            if(listBed[i].getBedStatus() == status[0] || listBed[i].getBedStatus() == status[1])
                tmpt.add(listBed[i]);
        }
    }

    QString **content;
    content = new QString*[tmpt.length()];

    for(int i = 0; i < tmpt.length(); i++){
        content[i] = new QString[5];
    }

    for(int i = 0; i < tmpt.length(); i++){
        content[i][0] = tmpt[i].getBedId();
        content[i][1] = QString::number(tmpt[i].getBedStatus());
        content[i][2] = tmpt[i].getRoomId();
        content[i][3] = tmpt[i].getTypeRoom();
        content[i][4] = tmpt[i].getDepartementName();
    }

    for(int i = 0; i < tmpt.length(); i++){
        ui->list_room->insertRow(row);
        for(int j = 0; j < 5; j++){
            if(j == 1){
                if(content[i][j].toInt()){
                    ui->list_room->setItem(row, j, new QTableWidgetItem("Trống"));
                }
                else ui->list_room->setItem(row, j, new QTableWidgetItem("Có bệnh nhân"));
                continue;
            }
            ui->list_room->setItem(row, j, new QTableWidgetItem(content[i][j]));
        }
        row ++;
    }
}
//thêm thông tin bệnh nhân
void MainWindow::addInforPtnData(int i, QLineEdit *qledit[], QRadioButton *qradiobtn[], QTextEdit *qtextedit[]){
    patient A = listPatient[i];

    // set thông tin cho các ô input trang thông tin bệnh nhân
    qledit[0]->setText(A.getId());
    qledit[1]->setText(A.getName());
    qledit[2]->setText(QString::number(A.getAge()));

    if(A.getGender() == "Nam"){
        qradiobtn[0]->setChecked(true);
    }
    else{
        if(A.getGender() == "Nữ"){
            qradiobtn[1]->setChecked(true);
        }
        else{
            qradiobtn[2]->setChecked(true);
        }
    }

    qledit[3]->setText(A.getNumber());
    qtextedit[0]->setText(A.getAddress());
}

//thêm thông tin vào trang chi tiết bệnh án
void MainWindow::addDataToViewCaseDetailPg(QString id_case){
    QSqlQuery query(myDB);
    query.exec("select ngay_kham, chieu_cao, can_nang, tinh_trang, ngay_tai_kham, don_thuoc, id_BS from BENHAN where id_benh_an = '" + id_case + "'");
    query.first();

    QStringList date_list;

    ui->add_htr_caseId_input->setText(id_case);

    ui->add_htr_input_1->setText(ui->view_htr_input_1->text());
    ui->add_htr_input_2->setText(ui->view_htr_input_2->text());

    // chuyển các nút về trạng thái khóa
    ui->add_htr_caseId_input->setEnabled(false);
    ui->add_htr_input_1->setEnabled(false);
    ui->add_htr_input_2->setEnabled(false);

    date_list = query.value(0).toString().split("-");
    ui->add_htr_cbb_1->setCurrentIndex(ui->add_htr_cbb_1->findText(date_list[2]));
    ui->add_htr_cbb_2->setCurrentIndex(ui->add_htr_cbb_2->findText(date_list[1]));
    ui->add_htr_cbb_3->setCurrentIndex(ui->add_htr_cbb_3->findText(date_list[0]));


    ui->add_htr_input_3->setText(query.value(1).toString());
    ui->add_htr_input_4->setText(query.value(2).toString());
    ui->add_htr_input_5->setText(query.value(3).toString());

    if(query.value(4).toString() != ""){
        date_list = query.value(4).toString().split("-");
        ui->add_htr_cbb_4->setCurrentIndex(ui->add_htr_cbb_4->findText(date_list[2]));
        ui->add_htr_cbb_5->setCurrentIndex(ui->add_htr_cbb_5->findText(date_list[1]));
        ui->add_htr_cbb_6->setCurrentIndex(ui->add_htr_cbb_6->findText(date_list[0]));
    }
    else{
        ui->add_htr_cbb_4->setCurrentIndex(-1);
        ui->add_htr_cbb_5->setCurrentIndex(-1);
        ui->add_htr_cbb_6->setCurrentIndex(-1);
    }

    ui->add_htr_input_6->setText(query.value(5).toString());
    ui->doctor_name->setText(listDoctor[listDoctor.find(query.value(6).toString())].getName());
}

bool MainWindow::checkString(QString s){
    for(auto i: s)
        if(i < '0' || i > '9')
            return 1;
    return 0;
}

void MainWindow::on_home_btn_clicked()// nút trang chủ
{
    ui->stackedWidget->setCurrentIndex(homePage);

    this->clickedButton(0);
}

void MainWindow::on_back_btn_clicked()// nút quay lui
{
    if(page_back.size() > 1){
        page_back.pop();
        switch (page_back.top()) {
        case 1:
        {
            this->on_patient_search_input_textChanged("");
            break;
        }
        case 5:
        {
            this->addDataToCaseRecordTable(ui->list_case_record->rowCount(), ui->infor_ptn_input_1->text());
        }
        }
        ui->stackedWidget_2->setCurrentIndex(page_back.top());
    }
}

void MainWindow::on_manage_btn_clicked()// nút quản lý
{
    if(doctorId != ""){
        // chuyển tới giao diện quản lý
            ui->stackedWidget->setCurrentIndex(mangePage);
            ui->back_btn->setVisible(false);
            ui->stackedWidget_2->setCurrentIndex(homeMangePage);
            page_back.push(homeMangePage);

            this->clickedButton(1);
            this->clickedButtonInManagePage(-1);
    }
    else{
        ui->stackedWidget->setCurrentIndex(notifyPage);
    }
}

void MainWindow::on_login_btn_clicked()// nút đăng nhập
{
    this->clickedButton(-1);
    if(ui->login_btn->text() == "Đăng nhập"){
        ui->stackedWidget->setCurrentIndex(loginPage);
        ui->login_label->setText("");
        ui->username_input->setText("");
        ui->password_input->setText("");
    }
    else{
        ui->login_btn->setText("Đăng nhập");
        ui->avar_icon->setVisible(false);
        doctorId = "";
        ui->doctorName->setText("");
        ui->stackedWidget->setCurrentIndex(homePage);
        this->clickedButton(0);
    }
}

void MainWindow::on_login_ok_btn_clicked()
{
    QString username, pass;
    username = ui->username_input->text();
    pass = ui->password_input->text();

    for(int i = 0; i < listAd.length(); i++){
        if(listAd[i].getUsername() == username && listAd[i].getPassword() == pass){
            ui->stackedWidget->setCurrentIndex(homePage);
            ui->login_btn->setText("Đăng xuất");
            ui->avar_icon->setVisible(true);
            doctorId = listAd[i].getDoctorId();

            doctor A = listDoctor[listDoctor.find(doctorId)];
            ui->doctorName->setText(A.getName());
            this->clickedButton(0);
            return;
        }
    }

    ui->login_label->setText("Tên đăng nhập hoặc mật khẩu sai");
}

void MainWindow::on_patient_btn_clicked()// nút bệnh nhân
{
//    menu = 1;
//    ui->ID_input->setText("");
    ui->back_btn->setVisible(true);
    ui->patient_search_input->setText("");

//// chuyển tới trang nhập id bệnh nhân
//    ui->stackedWidget_2->setCurrentIndex(idPatientInput);
    while (!page_back.empty())
           page_back.pop();
    page_back.push(listPatientPage);

    this->clickedButtonInManagePage(0);
    for(int i = 0; i < 4; i++)
        ui->list_patient->setColumnWidth(i, ui->list_patient->width()/4);

    ui->stackedWidget_2->setCurrentIndex(listPatientPage);

    this->on_patient_search_input_textChanged("");
}

void MainWindow::on_case_record_btn_clicked()// nút bệnh án
{
    ui->back_btn->setVisible(false);//ẩn nút quay lui
    ui->id_case_err_label->setText("");

    ui->ID_case_input->setText("");//xóa thông tin cũ trong ô id
    ui->stackedWidget_2->setCurrentIndex(idRecordInput);
    while(page_back.size()){
        page_back.pop();
    }

    this->clickedButtonInManagePage(1);
}

void MainWindow::on_room_btn_clicked()// nút phòng bệnh
{
    QRadioButton *qrbtn[] = {ui->bed_status_1, ui->bed_status_2};// bỏ tích thông tin lọc
    this->clearRadioChecked(qrbtn, 2);

    ui->back_btn->setVisible(true);
    while(page_back.size()){
        page_back.pop();
    }
    page_back.push(listRoomPage);
    // set chiều rộng cho bảng giường bệnh
    for(int i = 0; i < 5; i++){
        if(i == 0 || i == 1 || i == 2){
            ui->list_room->setColumnWidth(i, 90);
            continue;
        }
        ui->list_room->setColumnWidth(i, (ui->list_room->width() - 270)/2 - 1);
    }
    int arr[] = {1, 0};
    this->addDataToRoomTable(ui->list_room->rowCount(), "Room", "Departement", arr);
    ui->stackedWidget_2->setCurrentIndex(listRoomPage);

    ui->list_room_cbb_1->setCurrentIndex(-1);
    ui->list_room_cbb_2->setCurrentIndex(-1);

    this->clickedButtonInManagePage(2);
}

void MainWindow::on_doctor_btn_clicked()// nút bác sĩ
{
    ui->stackedWidget_2->setCurrentIndex(listDoctorPage);
    ui->back_btn->setVisible(true);
    this->clickedButtonInManagePage(3);

    while(!page_back.empty())
        page_back.pop();

    page_back.push(listDoctorPage);

    this->on_doctor_search_input_textChanged("");
    for(int i = 0; i < 4; i++){
        ui->list_doctor->setColumnWidth(i, ui->list_doctor->width()/4);
    }
}

// kiểm tra ô combobox đã có dữ liệu chưa
bool MainWindow::checkComboboxIsFilled(QComboBox *q[], int n){
    for(int i = 0; i < n; i++){
        if(q[i]->currentIndex() == -1){
            return 0;
        }
    }
    return 1;
}

//Set các nút trang thông báo (1)(2)--------------------------------------------------------
void MainWindow::on_ok_btn_clicked()// nút oke
{
    QString id;
    id = ui->ID_input->text();
    if(id != ""){

        QSqlQuery query(myDB);

        int index = listPatient.find(id);

        if(index != -1){
            switch (menu){
            case 1: // vào trang thông tin bệnh nhân
            {
                ui->stackedWidget_2->setCurrentIndex(inforPatientPage);
                page_back.push(inforPatientPage);

                // lấy thông tin bệnh nhân từ mảng bệnh nhân
                patient A = listPatient[index];

                // set thông tin cho các ô input trang thông tin bệnh nhân
                QLineEdit *qledit[] = {ui->infor_ptn_input_1, ui->infor_ptn_input_2, ui->infor_ptn_input_3, ui->infor_ptn_input_4};
                QRadioButton *qradiobtn[] = {ui->radioButton, ui->radioButton_2, ui->radioButton_3};
                QTextEdit *qtextedit[] = {ui->infor_ptn_input_5};

                this->addInforPtnData(index, qledit, qradiobtn, qtextedit);

                ui->infor_ptn_cbb->setCurrentText(A.getTypeBlood());
                ui->infor_ptn_input_6->setText(QString::number(A.getHeight()));
                ui->infor_ptn_input_7->setText(QString::number(A.getWeight()));

                if(A.getHospitalize() == 1){
                    // hiện thông tin khoa, phòng
                    ui->hospitalize_label->setText("Đang điều trị nội trú");
                    this->showRoomInfor();
                    // truy vấn id giường, phòng và tên khoa
                    QString id_giuong, id_phong, ten_khoa;
                    query.exec("select id_giuong from NHAPVIEN where id_BN = '" + id + "' order by ngay_nhap_vien desc");
                    query.first();
                    id_giuong = query.value(0).toString();

                    query.exec("select id_phong from GIUONGBENH where id_giuong = '" + id_giuong + "'");
                    query.first();
                    id_phong = query.value(0).toString();

                    query.exec("select ten_khoa from KHOA where id_khoa in (select id_khoa from PHONGBENH where id_phong = '" + id_phong + "')");
                    query.first();
                    ten_khoa = query.value(0).toString();

                    //loại bỏ id_phong ra khỏi id_giường (vì id_giường được tạo bởi id_phong + số giường)
                    id_giuong.remove(id_phong);

                    ui->infor_ptn_input_8->setText(ten_khoa);
                    ui->infor_ptn_input_9->setText(id_phong);
                    ui->infor_ptn_input_10->setText(id_giuong);
                }
                else{
                    this->hiddenRoomInfor();
                }

                this->disableInforPatientInput();
                break;
            }
            case 2:// vào trang nhập viện
            {
                ui->stackedWidget_2->setCurrentIndex(admitToHospitalPage);
                page_back.push(admitToHospitalPage);
                ui->in_out_hospital->setCurrentIndex(0);

                QComboBox *qcbb[] = {ui->admit_hp_cbb_1, ui->admit_hp_cbb_2, ui->admit_hp_cbb_3, ui->admit_hp_cbb_4, ui->admit_hp_cbb_5, ui->admit_hp_cbb_6};
                for(auto p: qcbb)
                    p->setCurrentIndex(-1);

                ui->admit_hp_input_6->setText("");

                QLineEdit *qledit[] = {ui->admit_hp_input_1, ui->admit_hp_input_2, ui->admit_hp_input_3, ui->admit_hp_input_4};
                QRadioButton *qradiobtn[] = {ui->admit_hp_radio_btn_1, ui->admit_hp_radio_btn_2, ui->admit_hp_radio_btn_3};
                QTextEdit *qtextedit[] = {ui->admit_hp_input_5};

                this->addInforPtnData(index, qledit, qradiobtn, qtextedit);
                for (auto p:qledit)
                    p->setEnabled(false);
                for (auto p:qtextedit)
                    p->setEnabled(false);
                for (auto p:qradiobtn)
                    p->setEnabled(false);
                break;
            }
            case 3://vào trang xuất viện
            {
                ui->stackedWidget_2->setCurrentIndex(admitToHospitalPage);
                page_back.push(admitToHospitalPage);

                ui->in_out_hospital->setCurrentIndex(1);

                QLineEdit *qledit[] = {ui->admit_hp_input_1, ui->admit_hp_input_2, ui->admit_hp_input_3, ui->admit_hp_input_4};
                QRadioButton *qradiobtn[] = {ui->admit_hp_radio_btn_1, ui->admit_hp_radio_btn_2, ui->admit_hp_radio_btn_3};
                QTextEdit *qtextedit[] = {ui->admit_hp_input_5};

                this->addInforPtnData(index, qledit, qradiobtn, qtextedit);
                for (auto p:qledit)
                    p->setEnabled(false);
                for (auto p:qtextedit)
                    p->setEnabled(false);
                for (auto p:qradiobtn)
                    p->setEnabled(false);
                break;
            }
            }
        }
        else{
            this->clearInputText();
            this->enableInforPatientInput();
            ui->stackedWidget_2->setCurrentIndex(idPatientError);
            page_back.push(idPatientError);

            ui->infor_ptn_input_1->setText(id);

            ui->infor_ptn_input_1->setEnabled(false);

            this->hiddenRoomInfor();
       }
    }
}

void MainWindow::on_yes_btn_clicked()// nút có
{
// chuyển tới trang nhập mới thông tin bệnh nhân
   ui->stackedWidget_2->setCurrentIndex(inforPatientPage);
   page_back.push(inforPatientPage);

   ui->infor_ptn_label->setText("");

   editOrSave = 0;

   QString id = ui->infor_ptn_input_1->text();
   this->clearInputText();
   ui->infor_ptn_input_1->setText(id);

   ui->repair_inf_ptn_btn->setText("Lưu thông tin");
}

void MainWindow::on_no_btn_clicked()// nút không
{
// chuyển tới trang nhập id
   ui->stackedWidget_2->setCurrentIndex(idPatientInput);
   page_back.push(idPatientInput);
}
//--------------------------------------------------------------------------

//Set các nút trang thông tin bệnh nhân (3)-----------------------------------------

void MainWindow::on_htr_btn_clicked()//nút hồ sơ bệnh án
{
    if(ui->repair_inf_ptn_btn->text() != "Sửa thông tin"){
        ui->infor_ptn_label->setText("Bạn chưa lưu thông tin");//thông báo chưa lưu thông tin
    }
    else{
        //chuyển tới trang danh sách bệnh án
            ui->stackedWidget_2->setCurrentIndex(listCaseRecordPage);
            page_back.push(listCaseRecordPage);

        //lấy id và tên
            QString id, name;
            id = ui->infor_ptn_input_1->text();
            name = ui->infor_ptn_input_2->text();

        //set id và tên cho ô input ở trang hồ sơ bệnh án
            ui->view_htr_input_1->setText(id);
            ui->view_htr_input_2->setText(name);

        //disable 2 ô input
            ui->view_htr_input_1->setEnabled(false);
            ui->view_htr_input_2->setEnabled(false);

            int row = ui->list_case_record->rowCount();
            this->addDataToCaseRecordTable(row, id);
    }
}

void MainWindow::on_repair_inf_ptn_btn_clicked()//nút sửa thông tin bệnh nhân
{
    // kiểm tra trạng thái nút hiện tại

    if(editOrSave){// trạng thái sửa
        editOrSave = 0;
        ui->repair_inf_ptn_btn->setText("Lưu thông tin");
        this->enableInforPatientInput();
    }
    else{// trạng thái lưu
        QString id = ui->infor_ptn_input_1->text();
        int index = listPatient.find(id);

        QString name, age, gender, address, phone, hospitalize, blood_type, height, weight;
        name = ui->infor_ptn_input_2->text().toUtf8();
        age = ui->infor_ptn_input_3->text();

        if(ui->radioButton->isChecked()){
            gender = "Nam";
        }
        else{
            if(ui->radioButton_2->isChecked()){
                gender = "Nữ";
            }
            else{
                gender = "Khác";
            }
        }

        address = ui->infor_ptn_input_5->toPlainText();
        phone = ui->infor_ptn_input_4->text();
        blood_type = ui->infor_ptn_cbb->currentText();
        height = ui->infor_ptn_input_6->text();
        weight = ui->infor_ptn_input_7->text();

        QSqlQuery query(myDB);
        if(name == "" || age == "" || gender == "" || address == "" || phone == "" || blood_type == "Blood type" || height == "" || weight == ""){
            ui->infor_ptn_label->setText("Bạn cần điền đủ thông tin");// thông báo chưa điền đủ thông tin
        }
        else{
            if(index != -1){
                patient &A = listPatient[index];
                hospitalize = QString::number(A.getHospitalize());

                A = patient(id, name, age.toInt(), gender, address, phone, hospitalize.toInt(), blood_type, height.toFloat(), weight.toFloat());

                query.exec("update BENHNHAN set ten = N'"+ name + "',tuoi = " + age + ", gioi_tinh = N'" + gender + "', dia_chi = N'" + address + "', sdt = '" + phone + "', lich_su = " + hospitalize + ", nhom_mau = '" + blood_type + "', chieu_cao = " + height + ", can_nang = " + weight + "  where id_BN ='" + id + "'");
                listPatient[index] = patient(id, name, age.toInt(), gender, address, phone, 0, blood_type, height.toFloat(), weight.toFloat());
            }
            else{
                query.exec("insert into BENHNHAN values('" + id  + "',N'" + name + "'," + age + ",N'" + gender + "',N'" + address + "','" + phone + "', 0 ,'" + blood_type + "'," + height + "," + weight + ")");
                listPatient.add(patient(id, name, age.toInt(), gender, address, phone, 0, blood_type, height.toFloat(), weight.toFloat()));
            }

            ui->infor_ptn_label->setText("");
            ui->repair_inf_ptn_btn->setText("Sửa thông tin");
            editOrSave = 1;
            this->disableInforPatientInput();
        }
    }
}
//--------------------------------------------------------------------------------------------------------

//Set các nút trang danh sách bệnh án (4)------------------------------------------------------------------------------
void MainWindow::on_add_htr_btn_clicked()//nút thêm bệnh án
{
    ui->save_htr_btn->setVisible(true);
    ui->save_htr_btn->setText("Lưu");
    ui->save_htr_btn->setEnabled(true);

    // chuyển tới trang nhập thông tin bệnh án
    ui->stackedWidget_2->setCurrentIndex(detailCaseRecordPage);
    page_back.push(detailCaseRecordPage);

    ui->doctor_name->setVisible(false);// ẩn tên bác sĩ
    QString id, name, id_case = "";
    QSqlQuery query(myDB);
    id = ui->view_htr_input_1->text();
    name = ui->view_htr_input_2->text();

    ui->add_htr_input_1->setText(id);
    ui->add_htr_input_2->setText(name);

    ui->add_htr_caseId_input->setEnabled(false);
    ui->add_htr_input_1->setEnabled(false);
    ui->add_htr_input_2->setEnabled(false);

    // xóa text cũ trong ô input
    QLineEdit *qledit[] = {ui->add_htr_input_3, ui->add_htr_input_4};
        for (auto p: qledit) p->setText("");
    QTextEdit *qtedit[] = {ui->add_htr_input_5, ui->add_htr_input_6};
        for (auto p: qtedit) p->setText("");
    QComboBox *qcbb[] = {ui->add_htr_cbb_1, ui->add_htr_cbb_2, ui->add_htr_cbb_3, ui->add_htr_cbb_4, ui->add_htr_cbb_5, ui->add_htr_cbb_6};
        for (auto p: qcbb) p->setCurrentIndex(-1);

    int i = name.length() - 1;
    while(id_case.length() < 2 && i >= 0){
        if(name[i] < "a" || name[i] > "z")
            i--;
        else{
            id_case += name[i];
            i--;
        }
    }
    for(int i = 0; i < 3; i++){
        id_case += QString(id[i]);
    }

// Tạo id bệnh án mới
    query.exec("select top 1 id_benh_an from BENHAN where id_BN = '" + id + "' order by id_benh_an desc");
    query.first();
    QString id_case_pre = query.value(0).toString();
    if(id_case_pre != ""){
        id_case_pre = QString::number(id_case_pre.remove(id_case).toInt() + 1);
        id_case += id_case_pre;
    }
    else
        id_case += "1";
    ui->add_htr_caseId_input->setText(id_case);
}

void MainWindow::on_edit_htr_btn_3_clicked()// nút sửa bệnh án
{
    if(ui->list_case_record->currentRow() != -1){
        ui->stackedWidget_2->setCurrentIndex(detailCaseRecordPage);
        page_back.push(detailCaseRecordPage);

        ui->save_htr_btn->setVisible(true);//hiện nút lưu

        QString id_case = ui->list_case_record->item(ui->list_case_record->currentRow(), 0)->text();

        this->addDataToViewCaseDetailPg(id_case);
    }
}

void MainWindow::on_del_htr_btn_4_clicked()// nút xóa bệnh án
{
    if(ui->list_case_record->currentRow() == -1){
        return;
    }
    QString id = ui->view_htr_input_1->text(), id_case = ui->list_case_record->item(ui->list_case_record->currentRow(), 0)->text();

    QSqlQuery query(myDB);
    query.exec("delete from BENHAN where id_benh_an = '" + id_case + "'");
    this->addDataToCaseRecordTable(ui->list_case_record->rowCount(), id);
}

void MainWindow::on_list_case_record_cellDoubleClicked(int row, int column)// double click để xem chi tiết bệnh án
{
    ui->stackedWidget_2->setCurrentIndex(detailCaseRecordPage);
    page_back.push(detailCaseRecordPage);

    ui->save_htr_btn->setVisible(false);//ẩn nút lưu
    ui->doctor_name->setVisible(true);// hiện tên bác sĩ

    QString id_case = ui->list_case_record->item(row, 0)->text();

    this->addDataToViewCaseDetailPg(id_case);
}

//--------------------------------------------------------------------------------------------------------------------

//Set các nút trang thêm thông tin bệnh án (5)----------------------------------------------------------------------------------------
void MainWindow::on_save_htr_btn_clicked()// nút lưu bệnh án
{
    cout << doctorId.toStdString() << endl;
    QSqlQuery query(myDB);
    QString id_case, id_ptn, date_create, date_back, height, weight, health, list_medicine;

    id_case = ui->add_htr_caseId_input->text();
    id_ptn = ui->add_htr_input_1->text();

    if(ui->add_htr_cbb_1->currentText() == "Date" || ui->add_htr_cbb_2->currentText() == "Month" || ui->add_htr_cbb_3->currentText() == "Year"){
        ui->add_htr_err_label->setText("Bạn cần nhập đủ thông tin");
        return;
    }

    date_create = ui->add_htr_cbb_3->currentText() + "-" + ui->add_htr_cbb_2->currentText() + "-" + ui->add_htr_cbb_1->currentText();
    date_back = ui->add_htr_cbb_6->currentText() + "-" + ui->add_htr_cbb_5->currentText() + "-" + ui->add_htr_cbb_4->currentText();

    height = ui->add_htr_input_3->text();
    weight = ui->add_htr_input_4->text();
    health = ui->add_htr_input_5->toPlainText();

    if(height == "" || weight == "" || health == ""){
        ui->add_htr_err_label->setText("Bạn cần nhập đủ thông tin");
        return;
    }

    list_medicine = ui->add_htr_input_6->toPlainText();

    // kiểm tra id bệnh án tồn tại chưa
    query.exec("select id_benh_an from BENHAN where id_benh_an = '" + id_case + "'");
    query.first();
    int saveOrUpdate;

    if(query.value(0).toString() == ""){
        saveOrUpdate = 1;
    }
    else saveOrUpdate = 0;

    if(date_back == "Year-Month-Date"){
        date_back = "NULL";
        if(saveOrUpdate)// id bệnh án chưa tồn tại thì lưu thông tin
            query.exec("insert into BENHAN values('" + id_case + "'," + "'" + id_ptn + "'," + height + "," + weight + ",N'" + health + "','" + date_create + "'," + date_back + ",N'" + list_medicine + "', '" + doctorId + "')");
        else// ngược lại thì update
            query.exec("update BENHAN set chieu_cao = " + height + ", can_nang = " + weight + ", tinh_trang = N'" + health + "', ngay_kham = '" + date_create + "', ngay_tai_kham = " + date_back + ", don_thuoc = N'" + list_medicine + "', id_BS = '" + doctorId + "' where id_benh_an = '" + id_case +"'");
    }
    else
        if(saveOrUpdate)
            query.exec("insert into BENHAN values('" + id_case + "'," + "'" + id_ptn + "'," + height + "," + weight + ",N'" + health + "','" + date_create + "','" + date_back + "',N'" + list_medicine + ", '" + doctorId + "')");
        else
            query.exec("update BENHAN set chieu_cao = " + height + ", can_nang = " + weight + ", tinh_trang = N'" + health + "', ngay_kham = '" + date_create + "', ngay_tai_kham = '" + date_back + "', don_thuoc = N'" + list_medicine + "', id_BS = '" + doctorId + "' where id_benh_an = '" + id_case +"'");

    patient &A = listPatient[listPatient.find(id_ptn)];
    A.setHeight(height.toFloat());
    A.setWeight(weight.toFloat());

    ui->save_htr_btn->setText("Đã lưu");
    ui->save_htr_btn->setEnabled(false);
    ui->add_htr_err_label->setText("");
}
//------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_ok_btn_2_clicked()// nút oke 2
{
    QString id_case = ui->ID_case_input->text(), id_ptn;

    QSqlQuery query(myDB);
    query.exec("select id_benh_an from BENHAN where id_benh_an = '" + id_case + "'");
    query.first();

    if(query.value(0).toString() != ""){
        ui->id_case_err_label->setText("");

        ui->stackedWidget_2->setCurrentIndex(detailCaseRecordPage);
        page_back.push(detailCaseRecordPage);

        ui->save_htr_btn->setText("Lưu");// enable nút lưu bệnh án
        ui->save_htr_btn->setEnabled(true);
        ui->save_htr_btn->setVisible(true);

        this->addDataToViewCaseDetailPg(id_case);

        QSqlQuery query(myDB);
        query.exec("select id_BN from BENHAN where id_benh_an = '" + id_case + "'");
        query.first();
        id_ptn = query.value(0).toString();

        ui->add_htr_input_1->setText(id_ptn);
        patient  A = listPatient[listPatient.find(id_ptn)];
        ui->add_htr_input_2->setText(A.getName());
    }
    else{
        ui->id_case_err_label->setText("ID không tồn tại");
    }
}

//trang danh sách phòng bệnh--------------------------------------------------------------------
void MainWindow::on_list_room_cbb_1_activated(const QString &arg1)
{
    ui->id_bed_search_input->setText("");
    this->clearAllItems(ui->list_room_cbb_2);

    for(int i = 0; i < listRoom.length(); i++){
        if(listRoom[i].getDepartementName() == arg1 && listRoom[i].getNumberBed() > 0){
            ui->list_room_cbb_2->addItem(listRoom[i].getRoomId());
        }
    }

    int arr[] = {1, 0};
    this->addDataToRoomTable(ui->list_room->rowCount(), "Room", arg1, arr);

    QRadioButton *qrbtn[] = {ui->bed_status_1, ui->bed_status_2};
    this->clearRadioChecked(qrbtn, 2);
}

void MainWindow::on_list_room_cbb_2_activated(const QString &arg1)
{
    int arr[] = {1, 0};
    this->addDataToRoomTable(ui->list_room->rowCount(), arg1, ui->list_room_cbb_1->currentText(), arr);
}

void MainWindow::on_admit_to_hospital_btn_clicked()// nút nhập viện
{
    ui->stackedWidget_2->setCurrentIndex(idPatientInput);
    page_back.push(idPatientInput);
    ui->in_out_hospital->setCurrentIndex(idPatientInput);
    menu = 2;

    ui->ID_input->setText("");

    ui->admit_quit_hp_savebtn->setText("Lưu");
    ui->admit_quit_hp_savebtn->setEnabled(true);
}

void MainWindow::on_all_bed_btn_clicked()// nút tất cả phòng bệnh
{
    int arr[] = {1, 0};
    this->addDataToRoomTable(ui->list_room->rowCount(), "Room", "Departement", arr);
    this->clearAllItems(ui->list_room_cbb_2);
    ui->list_room_cbb_1->setCurrentIndex(-1);

    QRadioButton *qrbtn[] = {ui->bed_status_1, ui->bed_status_2};
    this->clearRadioChecked(qrbtn, 2);
}

void MainWindow::on_quit_hp_btn_clicked()// nút xuất viện
{
    ui->stackedWidget_2->setCurrentIndex(idPatientInput);
    page_back.push(idPatientInput);
    menu = 3;

    ui->ID_input->setText("");

    ui->admit_quit_hp_savebtn->setText("Lưu");
    ui->admit_quit_hp_savebtn->setEnabled(true);
}

void MainWindow::on_id_bed_search_input_textChanged(const QString &arg1)// ô tìm kiếm ID giường
{
    ui->list_room_cbb_1->setCurrentIndex(-1);
    ui->list_room_cbb_2->setCurrentIndex(-1);

    int row = ui->list_room->rowCount();
    while(row){
        ui->list_room->removeRow(row - 1);
        row --;
    }

    QRadioButton *qrb[] = {ui->bed_status_1, ui->bed_status_2};
    this->clearRadioChecked(qrb, 2);

    for(int i = 0; i < listBed.length(); i++){
        if(listBed[i].getRoomId().indexOf(arg1) != -1){
            ui->list_room->insertRow(row);
            ui->list_room->setItem(row, 0, new QTableWidgetItem(listBed[i].getBedId()));
            if(listBed[i].getBedStatus()){
                ui->list_room->setItem(row, 1, new QTableWidgetItem("Trống"));
            }
            else
                ui->list_room->setItem(row, 1, new QTableWidgetItem("Có bệnh nhân"));
            ui->list_room->setItem(row, 2, new QTableWidgetItem(listBed[i].getRoomId()));
            ui->list_room->setItem(row, 3, new QTableWidgetItem(listBed[i].getTypeRoom()));
            ui->list_room->setItem(row, 4, new QTableWidgetItem(listBed[i].getDepartementName()));

            row++;
        }
    }
}

void MainWindow::on_list_room_cellDoubleClicked(int row, int column)
{
    ui->stackedWidget_2->setCurrentIndex(inforRoomPage);
    page_back.push(inforRoomPage);

    QString id_bed = ui->list_room->item(row, 0)->text();
    int index = listBed.find(id_bed);

    ui->infor_room_input_1->setText(listBed[index].getDepartementName());
    ui->infor_room_input_2->setText(listBed[index].getRoomId());
    ui->infor_room_input_3->setText(listBed[index].getTypeRoom());
    ui->infor_room_input_4->setText(QString::number(listBed[index].getBedId().remove(listBed[index].getRoomId()).toInt()));
    if(listBed[index].getBedStatus()){
        ui->infor_room_input_5->setText("Trống");
    }
    else
        ui->infor_room_input_5->setText("Có bệnh nhân");

    if(listBed[index].getBedStatus() == 0){
        QString id_ptn = listBed[index].getPatientId();
        cout << id_ptn.toStdString() << endl;
        int index = listPatient.find(id_ptn);

        cout << index << endl;

        ui->infor_room_input_6->setText(listPatient[index].getId());
        ui->infor_room_input_7->setText(listPatient[index].getName());
        if(listPatient[index].getGender() == "Nam"){
            ui->infor_room_rdb_1->setChecked(true);
        }
        else{
            if(listPatient[index].getGender() == "Nữ"){
                ui->infor_room_rdb_2->setChecked(true);
            }
            else
                ui->infor_room_rdb_3->setChecked(true);
        }
        ui->infor_room_input_8->setText(QString::number(listPatient[index].getAge()));
    }
    else{
        ui->infor_room_input_6->setText("");
        ui->infor_room_input_7->setText("");

        QRadioButton *qrb[] = {ui->infor_room_rdb_1, ui->infor_room_rdb_2, ui->infor_room_rdb_3};
        for(auto p:qrb){
            p->setAutoExclusive(false);
            p->setChecked(false);
            p->setAutoExclusive(true);
        }

        ui->infor_room_input_8->setText("");
    }
}
//-------------------------------------------------------------------------------------------------

//trang nhập viện----------------------------------------------------------------------
void MainWindow::on_admit_quit_hp_savebtn_clicked()// nút lưu thông tin xuất viện, nhập viện
{
    QString id_ptn = ui->ID_input->text(), id_case;
    QSqlQuery query(myDB);
    patient A = listPatient[listPatient.find(id_ptn)];

    // Tạo id bệnh án mới
    query.exec("select top 1 id_benh_an from BENHAN where id_BN = '" + id_ptn + "' order by id_benh_an desc");
    query.first();
    QString id_case_pre = query.value(0).toString();
    if(id_case_pre != ""){
        id_case_pre = QString::number(id_case_pre.remove(id_case).toInt() + 1);
        id_case += id_case_pre;
    }
    else
        id_case += "1";

    QComboBox *qcbb[] = {ui->admit_hp_cbb_1, ui->admit_hp_cbb_2, ui->admit_hp_cbb_3, ui->admit_hp_cbb_4, ui->admit_hp_cbb_5, ui->admit_hp_cbb_6};
    if(menu == 2){
        if(checkComboboxIsFilled(qcbb, 6)){
            QString health, id_giuong, id_phong, date;
            health = ui->admit_hp_input_6->toPlainText();
            id_phong = ui->admit_hp_cbb_5->currentText();
            id_giuong = ui->admit_hp_cbb_6->currentText();

            while(id_phong.length() + id_giuong.length() < 7){
                id_phong += "0";
            }

            id_giuong = id_phong + id_giuong;

            date = ui->admit_hp_cbb_3->currentText() + "-" + ui->admit_hp_cbb_2->currentText() + "-" + ui->admit_hp_cbb_1->currentText();

            query.exec("insert into NHAPVIEN values('" + id_ptn + "','" + id_giuong + "','" + date + "','" + listDoctor[listDoctor.find(doctorId)].getId() + "',N'" + health + "')");
            query.exec("insert into BENHAN values('" + id_case + "'," + "'" + id_ptn + "'," + QString::number(A.getHeight()) + "," + QString::number(A.getWeight()) + ",N'" + health + " (đã nhập viện điều trị)','" + date + "'," + "NULL" + ",N'','" + doctorId + "')");
            //bug
            ui->admit_quit_hp_savebtn->setText("Đã lưu");
            ui->admit_quit_hp_savebtn->setEnabled(false);
            ui->admit_hp_err_label->setText("");

            listBed[listBed.find(id_giuong)].setBedStatus(0);
            listBed[listBed.find(id_giuong)].setPatientId(id_ptn);
            listBed[listBed.find(id_giuong)].setNumberBed(-1);

            listRoom[listRoom.find(id_giuong)].setNumberBed(-1);

            listPatient[listPatient.find(id_ptn)].setHospitalize(1);
        }
        else
            ui->admit_hp_err_label->setText("Bạn cần điền đủ thông tin");
    }
    if(menu == 3){
        QComboBox *qcbb[] = {ui->admit_hp_cbb_7, ui->admit_hp_cbb_8, ui->admit_hp_cbb_9};
        if(checkComboboxIsFilled(qcbb, 3)){
            QString date = ui->admit_hp_cbb_9->currentText() + "-" + ui->admit_hp_cbb_8->currentText() + "-" + ui->admit_hp_cbb_7->currentText();

            query.exec("insert into XUATVIEN values('" + id_ptn + "','" + date + "','" + listDoctor[listDoctor.find(doctorId)].getId() + "')");
            query.exec("insert into BENHAN values('" + id_case + "'," + "'" + id_ptn + "'," + QString::number(A.getHeight()) + "," + QString::number(A.getWeight()) + ",N'Đã xuất viện','" + date + "'," + "NULL" + ",N'','" + doctorId + "')");

            ui->admit_quit_hp_savebtn->setText("Đã lưu");
            ui->admit_quit_hp_savebtn->setEnabled(false);
            ui->admit_hp_err_label->setText("");

            for(int i = 0; i < listBed.length(); i++){
                if(listBed[i].getPatientId() == id_ptn){
                    listBed[i].setPatientId("");
                    listBed[i].setBedStatus(1);
                    listBed[i].setNumberBed(+1);
                    listRoom[listRoom.find(listBed[i].getRoomId())].setNumberBed(+1);
                }
            }

            listPatient[listPatient.find(id_ptn)].setHospitalize(0);
        }
        else
            ui->admit_hp_err_label->setText("Bạn cần điền đủ thông tin");
    }
}

void MainWindow::on_admit_hp_cbb_4_activated(const QString &arg1)
{
    this->clearAllItems(ui->admit_hp_cbb_5);

    for(int i = 0; i < listRoom.length(); i++){
        if(listRoom[i].getNumberBed() > 0 && listRoom[i].getDepartementName() == arg1){
            ui->admit_hp_cbb_5->addItem(listRoom[i].getRoomId());
        }
    }
}

void MainWindow::on_admit_hp_cbb_5_activated(const QString &arg1)
{
    this->clearAllItems(ui->admit_hp_cbb_6);

    for(int i = 0; i < listBed.length(); i++){
        if(listBed[i].getRoomId() == arg1 && listBed[i].getBedStatus() == 1){
            ui->admit_hp_cbb_6->addItem(QString::number(listBed[i].getBedId().remove(arg1).toInt()));
        }
    }
}

void MainWindow::on_list_room_filter_btn_clicked()
{
    int row = ui->list_room->rowCount();

    if(ui->bed_status_1->isChecked() || ui->bed_status_2->isChecked()){
        if(ui->bed_status_1->isChecked()){
            int arr[] = {1};
            this->addDataToRoomTable(row, ui->list_room_cbb_2->currentText(), ui->list_room_cbb_1->currentText(), arr);
        }
        else{
            int arr[] = {0};
            this->addDataToRoomTable(row, ui->list_room_cbb_2->currentText(), ui->list_room_cbb_1->currentText(), arr);
        }
   }
}
//-----------------------------------------------------------------------------------------------------------------------------------------

// trang danh sách bệnh nhân
void MainWindow::on_patient_search_input_textChanged(const QString &arg1)
{
    int row = ui->list_patient->rowCount();
    while(row > 0){
        ui->list_patient->removeRow(row - 1);
        row --;
    }
    if(checkString(arg1)){
        cout << "bug" << endl;
        for(int i = 0; i < listPatient.length(); i++){
            if(listPatient[i].getName().indexOf(arg1) != -1){
                ui->list_patient->insertRow(row);

                ui->list_patient->setItem(row, 0, new QTableWidgetItem(listPatient[i].getId()));
                ui->list_patient->setItem(row, 1, new QTableWidgetItem(listPatient[i].getName()));
                ui->list_patient->setItem(row, 2, new QTableWidgetItem(QString::number(listPatient[i].getAge())));
                ui->list_patient->setItem(row, 3, new QTableWidgetItem(listPatient[i].getGender()));

                row++;
            }
        }
    }
    else{
        for(int i = 0; i < listPatient.length(); i++){
            if(listPatient[i].getId().indexOf(arg1) != -1){
                ui->list_patient->insertRow(row);

                ui->list_patient->setItem(row, 0, new QTableWidgetItem(listPatient[i].getId()));
                ui->list_patient->setItem(row, 1, new QTableWidgetItem(listPatient[i].getName()));
                ui->list_patient->setItem(row, 2, new QTableWidgetItem(QString::number(listPatient[i].getAge())));
                ui->list_patient->setItem(row, 3, new QTableWidgetItem(listPatient[i].getGender()));

                row++;
            }
        }
    }
}

void MainWindow::on_list_patient_cellDoubleClicked(int row, int column)
{
    QString id_ptn = ui->list_patient->item(row, 0)->text();
    int index = listPatient.find(id_ptn);

    ui->stackedWidget_2->setCurrentIndex(inforPatientPage);
    page_back.push(inforPatientPage);

    ui->infor_ptn_label->setText("");
    ui->repair_inf_ptn_btn->setText("Sửa thông tin");

    // lấy thông tin bệnh nhân từ mảng bệnh nhân
    patient A = listPatient[index];

    // set thông tin cho các ô input trang thông tin bệnh nhân
    QLineEdit *qledit[] = {ui->infor_ptn_input_1, ui->infor_ptn_input_2, ui->infor_ptn_input_3, ui->infor_ptn_input_4};
    QRadioButton *qradiobtn[] = {ui->radioButton, ui->radioButton_2, ui->radioButton_3};
    QTextEdit *qtextedit[] = {ui->infor_ptn_input_5};

    this->addInforPtnData(index, qledit, qradiobtn, qtextedit);

    ui->infor_ptn_cbb->setCurrentText(A.getTypeBlood());
    ui->infor_ptn_input_6->setText(QString::number(A.getHeight()));
    ui->infor_ptn_input_7->setText(QString::number(A.getWeight()));

    if(A.getHospitalize() == 1){
        // hiện thông tin khoa, phòng
        ui->hospitalize_label->setText("Đang điều trị nội trú");
        this->showRoomInfor();

        int index;
        for(int i = 0; i < listBed.length(); i++){
            if(listBed[i].getPatientId() == id_ptn){
                index = i;
            }
        }

        ui->infor_ptn_input_8->setText(listBed[index].getDepartementName());
        ui->infor_ptn_input_9->setText(listBed[index].getRoomId());
        ui->infor_ptn_input_10->setText(QString::number(listBed[index].getBedId().remove(listBed[index].getRoomId()).toInt()));
    }
    else{
        this->hiddenRoomInfor();
    }

    this->disableInforPatientInput();
}

void MainWindow::on_new_inf_ptn_button_clicked()// nút tạo hồ sơ mới
{
    this->on_yes_btn_clicked();
    ui->infor_ptn_input_1->setText("");
    ui->infor_ptn_input_1->setEnabled(true);
    this->enableInforPatientInput();
    this->hiddenRoomInfor();
}

void MainWindow::on_new_inf_ptn_button_2_clicked()
{
    int row = ui->list_patient->currentRow();
    QString id = ui->list_patient->item(row, 0)->text();


}
//------------------------------------------------------------------------------------------------------------------------------------------------
//trang danh sách bác sĩ

void MainWindow::on_doctor_search_input_textChanged(const QString &arg1)
{
    int row = ui->list_doctor->rowCount();
    while(row){
        ui->list_doctor->removeRow(row - 1);
        row--;
    }

    for(int i = 0; i < listDoctor.length(); i++){
        if(listDoctor[i].getName().indexOf(arg1) != -1){
            ui->list_doctor->insertRow(row);
            ui->list_doctor->setItem(row, 0, new QTableWidgetItem(listDoctor[i].getId()));
            ui->list_doctor->setItem(row, 1, new QTableWidgetItem(listDoctor[i].getName()));
            ui->list_doctor->setItem(row, 2, new QTableWidgetItem(QString::number(listDoctor[i].getAge())));
            ui->list_doctor->setItem(row, 3, new QTableWidgetItem(listDoctor[i].getGender()));
            row ++;
        }
    }
}

void MainWindow::on_list_doctor_cellDoubleClicked(int row, int column)
{
    ui->stackedWidget_2->setCurrentIndex(inforDoctorPage);
    page_back.push(inforDoctorPage);

    QString id_doctor = ui->list_doctor->item(row, 0)->text();

    doctor A = listDoctor[listDoctor.find(id_doctor)];

    ui->infor_doctor_input_1->setText(id_doctor);
    ui->infor_doctor_input_2->setText(A.getName());
    ui->infor_doctor_input_3->setText(QString::number(A.getAge()));

    if(A.getGender() == "Nam"){
        QPixmap px = QPixmap("C:/Users/sanhg/OneDrive/Máy tính/sources/img/avar_icon.png");
        ui->inf_doctor_picture->setPixmap(px.scaled(ui->inf_doctor_picture->size(), Qt::KeepAspectRatio));
        ui->inf_doctor_rdb_1->setChecked(true);
    }
    else{
        if(A.getGender() == "Nữ"){
            QPixmap px = QPixmap("C:/Users/sanhg/OneDrive/Máy tính/sources/img/avar_icon_2.png");
            ui->inf_doctor_picture->setPixmap(px.scaled(ui->inf_doctor_picture->size(), Qt::KeepAspectRatio));
            ui->inf_doctor_rdb_2->setChecked(true);
        }
        else{
            QPixmap px = QPixmap("C:/Users/sanhg/OneDrive/Máy tính/sources/img/avar_icon.png");
            ui->inf_doctor_picture->setPixmap(px.scaled(ui->inf_doctor_picture->size(), Qt::KeepAspectRatio));
            ui->inf_doctor_rdb_3->setChecked(true);
        }
    }

    ui->infor_doctor_input_4->setText(A.getNumber());
    ui->infor_doctor_input_5->setText(A.getAddress());

    ui->infor_doctor_input_6->setText(A.getDepartementName());
}
