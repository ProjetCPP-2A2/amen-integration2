// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QtCharts/QtCharts>
#include<QtCharts/QPieSeries>
#include "kinees.h"
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include "smtp.h"


#include "ajouterSupplier.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QtCharts>
#include <QThread>
#include <QProgressBar>
#include <QTableView>


#include <QColor>
#include <QProgressBar>
#include <QSortFilterProxyModel>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QFileDialog>
#include <QTableView>
#include <QHeaderView>
////////////////////////////ben fardjzeoigfj///////////////////////////
#include "seance.h"
#include "qr.h"
#include <QUrl>
#include <QDebug>
#include <QDateTime>

#include <vector>
#include <QPdfWriter>
#include <QFile>
#include <QSqlRecord>
#include <QSqlError>
#include <QDesktopServices>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QSqlQuery>
#include <QSystemTrayIcon>
#include <sys/types.h>
#include <QComboBox>
#include <QDate>
#include <QBrush>


#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QTimer>
#include <QRect>
#include <QSqlQueryModel>
#include <QIntValidator>
#include <QtDebug>

#include <QtPrintSupport/QPrinter>
#include <QPrinter>
#include <QXmlStreamWriter>
#include <QDoubleValidator>
#include <QValidator>
#include <QIntValidator>
#include <QSettings>
#include <QPushButton>
#include <QTranslator>
#include <QChartView>
#include <QPieSeries>
#include <QtWidgets>
#include <QtNetwork>


#include"activity.h"
#include<QSize>
#include<QIcon>
#include<QSize>
#include<QIcon>
#include<QSqlRecord>
#include"dialogk.h"

////////////////////////////////
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void generatePdf();
    QString generatePassword();
    void stats();
    void statsKinees(int id);
    void sendMail(const QString &recipient, const QString &subject, const QString &body);

    void mailSent(QString status);
    QMap<QString, int> getData(int id_kinee);
    void logOut();
    void kinees_switch();
    bool saisirActivity(QString nom,int duree,QString image);
        bool saisirActivity1(QString nom,int duree);
        void statistique();


private slots:
    void on_KAdd_clicked();

    void on_KList_3_clicked();

    void on_KList_4_clicked();

    void on_KmenuBtn_clicked();

    void on_KAjouter_2_clicked();


    void on_KDelete_clicked();



    void on_KUpdate_clicked();

    void on_KAjouter_3_clicked();

    void on_KPDF_clicked();

    void on_KLineSearch_textChanged();

    void on_KcomboBox_currentIndexChanged();

    void on_KPICTURE_clicked();

    void on_KPICTURE_2_clicked();

    void on_LOG_clicked();

    void on_forget_clicked();
    void slider(QWidget *leftMenu,QWidget *mainBody);





    void on_KmenuBtn_3_clicked();

    void on_KmenuBtn_4_clicked();


    //////////////////////////////////SAIFEDINNNNE/////////////////////////////////////////////////////////


    void on_Ajouter_3_dal_clicked();

    void on_ajouter_dal_clicked();

    void on_Delete_dal_clicked();

    void on_update_dal_clicked();

    void on_update_2_dal_clicked();

    void on_liste_s_dal_clicked();

    void on_update_s_dal_clicked();

    void on_add_s_dal_clicked();

    void on_liste_s_2_dal_clicked();

    void on_PDF_dal_clicked();

   void on_linesearch_dal_textChanged(const QString &arg1);

   void on_comboBox_dal_currentIndexChanged(int index);

   void updateProgressBar_dal();

   void on_supmax_dal_clicked();

   void on_btn_total_dal_clicked();


   void on_Kevent_clicked();

   void on_Kevent_3_clicked();

   void on_Kevent_4_clicked();

   void on_employe_dal_clicked();

   void on_employe_4_dal_clicked();

   void on_employe_6_dal_clicked();

   ////////////////////////////////BEN FARDGJEJF//////////////////////////////////////////////

public slots :
    void page1Widget();
    void page2Widget();
    void page3Widget();
    void page5Widget();
    void page6Widget();
    void pageaffichercalWidget();








private slots:
    void on_AAjouter_sbf_clicked();
    void on_ADelete_6_sbf_clicked();
    void on_Amodifier_sbf_clicked();


    void on_AAdd_6_sbf_clicked();

    void on_pushButton_5_sbf_clicked();
    void on_pushButton_2_sbf_clicked();
    void on_PDF_sbf_clicked();
    void on_choisir_calender_sbf_clicked();
    void on_calendarWidget_selectionChanged();





    //void on_calendarWidget_clicked(const QDate &date);




    void on_afficher_calender_sbf_clicked();

    //void on_calendarWidget_2_selectionChanged();
    QDate on_calendarWidget_2_selectionChanged();
    void on_Statistics_sbf_clicked();
    void on_AList_6_sbf_clicked();
    void on_garder_date_calender_sbf_clicked();
    void on_AUpdate_6_sbf_clicked();
    void on_modifier_calender_sbf_clicked();



    void on_Update_3_sbf_clicked();



    void on_Aemploye_6_sbf_clicked();

    void on_Aemploye_7_sbf_clicked();

    void on_Aemploye_10_sbf_clicked();

    void on_Aemploye_11_sbf_clicked();

    void on_Aemploye_12_sbf_clicked();

    void on_Aemploye_13_sbf_clicked();

    void on_Kappointments_clicked();

    void on_Kappointments_3_clicked();

    void on_Kappointments_4_clicked();

    void on_appointments_dal_clicked();

    void on_appointments_4_dal_clicked();

    void on_appointments_6_dal_clicked();

    void on_Aevent_6_sbf_clicked();

    void on_Aevent_7_sbf_clicked();

    void on_Aevent_10_sbf_clicked();

    void on_Aevent_11_sbf_clicked();

    void on_Aevent_12_sbf_clicked();

    void on_Aevent_13_sbf_clicked();

    //amen
    void on_AAdd_6_clicked();

       void on_Aliste_7_clicked();

       void on_AAjouter_clicked();

       void on_ADelete_6_clicked();

       void on_AimageB_clicked();

       void on_AUpdate_6_clicked();

       void on_Aliste_9_clicked();

       void on_Aadd_3_clicked();



       void on_Amodifier_clicked();

       void on_AimageB_2_clicked();







       void on_Atoggle_clicked();



       void on_ALineSearch_6_textChanged(const QString &arg1);

       void on_AExel_7_clicked();
//*****************************************************************************************************************

       void on_AcomboBox_2_sbf_currentIndexChanged(const QString &arg1);

       void on_AcomboBox_4_sbf_currentIndexChanged(const QString &arg1);

       void on_Aemploye_6_clicked();

       void on_Aappointments_6_clicked();

       void on_Aevent_6_clicked();

       void on_Aproducts_6_clicked();

       void on_Apatient_6_clicked();

       void on_Aemploye_7_clicked();

       void on_Apatient_7_clicked();

       void on_Aappointments_7_clicked();

       void on_Aproducts_7_clicked();

       void on_Aevent_7_clicked();

       void on_Aemploye_10_clicked();

       void on_Apatient_10_clicked();

       void on_Aappointments_10_clicked();

       void on_Aproducts_10_clicked();

       void on_Aevent_10_clicked();

       void on_Kprograms_clicked();

       void on_Kprograms_3_clicked();

       void on_Kprograms_4_clicked();

       void on_programs_dal_clicked();

       void on_programs_4_dal_clicked();

       void on_programs_6_dal_clicked();

       void on_Aprograms_6_sbf_clicked();

       void on_Aprograms_7_sbf_clicked();

       void on_Aprograms_10_sbf_clicked();

public :
        kinees k;
private:
    Ui::MainWindow *ui;

private:
    QPieSeries *series;
    QLineSeries *series2;
    QChartView *chartView,*chartVieww,*ChartView_amen;


private :
    Activity ac;
    supplier Etmp;
    Seance Stemp;




    // Add a private member for the chart
    QChartView *chartview_saif;
    QPieSeries *series_saif;

    // Add private members to track counts for added, updated, and deleted suppliers
    int addedCount = 0;
    int updatedCount = 0;
    int deletedCount = 0;
    //variable checked amen
    bool checked;

    // Helper function to update the chart with the latest counts
    void updateChart_dal();
    QProgressBar *progressBar;
};

#endif // MAINWINDOW_H
