// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

bool babaw=true;


MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent),
      ui(new Ui::MainWindow), ChartView_amen(nullptr),ac(0, "type", "nom", "degres", 0, "image", "alterre"),k(8,"nom1","prenom1","email","mdp",32,"image")
{
    ui->setupUi(this);
    ui->KtableView->setModel(k.afficher());
    ac.afficherActivite(ui->AtableView);

    // Initialisez series et chartView
      series = new QPieSeries();
      series2=new QLineSeries();
      chartView = new QChartView();
      chartVieww = new QChartView();
      ui->Kwidget_7->setLayout(new QVBoxLayout());
      ui->Kwidget_7->layout()->addWidget(chartView);
      ui->Kwidget_21->setLayout(new QVBoxLayout());
      ui->Kwidget_21->layout()->addWidget(chartVieww);
      checked=false;
    statistique();
    stats();
    QMenu *profilMenu = new QMenu;
    QAction *logoutAction = new QAction(QIcon("C:/Users/rayan/Downloads/kinees/VITALTHERA - Copie - Copie/croix.png"), "Log out");
    profilMenu->addAction(logoutAction);
    ui->profile->setMenu(profilMenu);
    QObject::connect(logoutAction, &QAction::triggered, this, &MainWindow::logOut);




    //////////////////////////////////////SAIFEDINNNNE//////////////////////////////////////////////////



    ui->tableView_dal->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_dal->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_dal->setModel(Etmp.afficherSupplier());



    // Initialize the chart
    series_saif = new QPieSeries();
    series_saif->append("Added", addedCount);
    series_saif->append("Updated", updatedCount);
    series_saif->append("Deleted", deletedCount);


    QChart *chart = new QChart();
    chart->addSeries(series_saif);
    chart->setTitle("CRUD Operations");
    chart->legend()->hide();
    chart->setVisible(true);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QChartView *chartview_saif = new QChartView(chart);

    chartview_saif->setRenderHint(QPainter::Antialiasing);
    chartview_saif->setVisible(true);

    ui->widget_dal_2->setLayout(new QVBoxLayout());
    ui->widget_dal_2->layout()->addWidget(chartview_saif); // Ensure the variable name matches



    // Connect the textChanged signal of lineEdit_id to updateProgressBar slot
    connect(ui->id_stat_dal, &QLineEdit::textChanged, this, &MainWindow::updateProgressBar_dal);
    connect(ui->supmax_dal, &QPushButton::clicked, this, &MainWindow::on_supmax_dal_clicked);
    connect(ui->btn_total_dal, &QPushButton::clicked, this, &MainWindow::on_btn_total_dal_clicked);

    ///////////////////ben faredejlkajf//////////////////////////////////////////



    // Définir le modèle de données pour la QTableView
    ui->tableView_sbf->setModel(Stemp.afficher());






    connect(ui->AAdd_6_sbf, &QPushButton::clicked, this, &MainWindow::page3Widget);
     connect(ui->AList_6_sbf, &QPushButton::clicked, this, &MainWindow::pageaffichercalWidget);


    connect(ui->Aliste_10_sbf, &QPushButton::clicked, this, &MainWindow::page5Widget);


    connect(ui->Aadd_4_sbf, &QPushButton::clicked, this, &MainWindow::page1Widget);



    connect(ui->Aliste_7_sbf, &QPushButton::clicked, this, &MainWindow::page5Widget);

    connect(ui->Aliste_9_sbf, &QPushButton::clicked, this, &MainWindow::page5Widget);
    connect(ui->Aliste_11_sbf, &QPushButton::clicked, this, &MainWindow::page5Widget);
    connect(ui->Aliste_12_sbf, &QPushButton::clicked, this, &MainWindow::page5Widget);
    connect(ui->AUpdate_6_sbf, &QPushButton::clicked, this, &MainWindow::page6Widget);
    connect(ui->calendarWidget, &QCalendarWidget::selectionChanged, this, &MainWindow::on_calendarWidget_selectionChanged);



}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::kinees_switch()
{
    if(ui->email_info->text()=="admin")
    {
        ui->stackedWidget->setCurrentWidget(ui->page_3);
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("you don't have the right to access this page.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
}

void MainWindow::slider(QWidget *leftMenu,QWidget *mainBody)
{
    // Vérifiez si le rectangle bleu est actuellement visible.
        if (babaw==true) {
            // Si le rectangle bleu est visible, animez-le pour qu'il glisse hors de la vue.
            QPropertyAnimation *animation = new QPropertyAnimation(leftMenu, "geometry");
            QPropertyAnimation *animation2 = new QPropertyAnimation(mainBody, "geometry");
            animation->setDuration(500);
            animation->setStartValue(leftMenu->geometry());
            animation->setEndValue(QRect(-leftMenu->width()+4, leftMenu->y(), leftMenu->width(),leftMenu->height()));
            animation->start(QAbstractAnimation::DeleteWhenStopped);
            animation2->setDuration(500);
            animation2->setStartValue(mainBody->geometry());
            animation2->setEndValue(QRect(7, mainBody->y(), mainBody->width(),mainBody->height()));
            animation2->start(QAbstractAnimation::DeleteWhenStopped);
            babaw=false;


        } else {
            // Si le rectangle bleu n'est pas visible, animez-le pour qu'il glisse dans la vue.
            QPropertyAnimation *animation = new QPropertyAnimation(leftMenu, "geometry");
             QPropertyAnimation *animation2 = new QPropertyAnimation(mainBody, "geometry");
            animation->setDuration(500);
            animation->setStartValue(leftMenu->geometry());
            animation->setEndValue(QRect(4,leftMenu->y(),leftMenu->width(),leftMenu->height()));
            animation->start(QAbstractAnimation::DeleteWhenStopped);
            animation2->setDuration(500);
            animation2->setStartValue(mainBody->geometry());
            animation2->setEndValue(QRect(210,mainBody->y(), mainBody->width(), mainBody->height()));
            animation2->start(QAbstractAnimation::DeleteWhenStopped);
            babaw=true;

        }

}





void MainWindow::generatePdf() {
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM kinees ORDER BY id_kinees ASC");

    // Créer un nouveau document
    QTextDocument doc;

    // Ajouter une table au document
    QTextCursor cursor(&doc);
    QTextTable *table = cursor.insertTable(model->rowCount() + 1, model->columnCount()); // +1 pour la ligne d'en-tête

    // Ajouter les en-têtes de colonne
    QStringList headers = {"id_kinees", "nom", "prenom", "email", "nb_patient", "password", "image"};
    for(int col = 0; col < model->columnCount(); ++col) {
        table->cellAt(0, col).firstCursorPosition().insertText(headers.at(col));
    }

    // Remplir la table avec les données du modèle
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->index(row, col).data().toString();
            QTextTableCell cell = table->cellAt(row + 1, col); // +1 pour tenir compte de la ligne d'en-tête
            QTextCursor cellCursor = cell.firstCursorPosition();
            if(QFileInfo::exists(data) && QFileInfo(data).isFile()) {
                QImage image(data);
                image = image.scaled(150, 150, Qt::KeepAspectRatio);
                QByteArray byteArray;
                QBuffer buffer(&byteArray);
                image.save(&buffer, "PNG"); // Enregistre l'image dans byteArray en format PNG
                QString imageBase64 = QString::fromLatin1(byteArray.toBase64().data());

                cellCursor.insertHtml("<img src='data:image/png;base64," + imageBase64 + "' />");
            } else {
                // Sinon, insérer les données comme texte
                cellCursor.insertText(data);
            }
        }
    }

    // Appliquer un formatage à la table
    QTextTableFormat format;
    format.setBorder(1);
    format.setCellPadding(10);
    format.setHeaderRowCount(1);
    format.setBackground(Qt::lightGray);
    table->setFormat(format);

    // Créer un écrivain PDF
    QPdfWriter writer("C:/Users/rayan/Downloads/kinees/kinees-saifeddin/kinees.pdf");

    // Écrire le document dans le fichier PDF
    doc.print(&writer);
}







void MainWindow::on_KAdd_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);

}


void MainWindow::on_KList_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);

}


void MainWindow::on_KList_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}



void MainWindow::on_KmenuBtn_clicked()
{

    slider(ui->KleftMenu,ui->mainBody);
     slider(ui->KleftMenu_2,ui->mainBody_2);
      slider(ui->KleftMenu_3,ui->mainBody_3);


}

void MainWindow::on_KAjouter_2_clicked()
{
     ui->KNAME->setText("");
     ui->KNAME_2->setText("");
     ui->KNAME_3->setText("");
     ui->KNAME_4->setText("");
    QRegExp regex("^[a-zA-Z]+$");
    QRegExp regex1("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    QRegExp regex2("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");
    QString nom=ui->KlineEdit_6->text();
    QString prenom=ui->KlineEdit_7->text();
    QString email=ui->KlineEdit_8->text();
    QString mdp=generatePassword();
    QString img=ui->Kimg->text();
    QSqlQueryModel *model=k.LOGIN(email);

    if(nom.isEmpty() ||!regex.exactMatch(nom))
    {
        ui->KNAME->setText("incorrect first name");
        return;
    }

    if(prenom.isEmpty() ||!regex.exactMatch(prenom))
    {
        ui->KNAME_2->setText("incorrect last name");
        return;
    }
    if(email.isEmpty() ||!regex1.exactMatch(email) || model->rowCount()==1)
    {
        ui->KNAME_3->setText("incorrect mail");
        return;
    }
    if(mdp.isEmpty() ||!regex2.exactMatch(mdp))
    {
        ui->KNAME_4->setText("8 caracters 1 uppercase,lowercase,number");
        return;
    }
    if(img.isEmpty())
    {
        ui->KNAME_4->setText("veillez choisir une image");
        return;
    }

    kinees k(2,nom,prenom,email,mdp,0,img);
    bool test=k.ajouter();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("SUCESS ADD.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->KtableView->setModel(k.afficher());
        MainWindow::stats();



    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                    QObject::tr("ERROR ADD .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    ui->KlineEdit_6->setText("");
    ui->KlineEdit_7->setText("");
    ui->KlineEdit_8->setText("");
    QPixmap imagee("");
    ui->Klabel_11->setPixmap(imagee);
    ui->Klabel_11->setStyleSheet("border-image: url(:/icons/blue/bnaya.jpg);border-radius: 30px;");
    ui->stackedWidget->setCurrentWidget(ui->page_3);


}



void MainWindow::on_KDelete_clicked()
{

    // Obtenez l'ID de la ligne sélectionnée. Vous devrez peut-être ajuster cette ligne en fonction de la façon dont votre vue est configurée.
    int row = ui->KtableView->currentIndex().row();
    QModelIndex index = ui->KtableView->model()->index(row, 0); // Remplacez 0 par l'index de la colonne "id_kinees".
    int id = ui->KtableView->model()->data(index).toInt();

    bool test=k.supprimer(id);


    // Exécutez la requête. Si elle réussit, la ligne sera supprimée de la base de données.
    if (!test)
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                    QObject::tr("ERROR DELETE.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr(" DELETED SUCCESSFULLY.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    MainWindow::stats();
    ui->KtableView->setModel(k.afficher());

}







void MainWindow::on_KUpdate_clicked()
{
    ui->KNAME_5->setText("");
    ui->KNAME_6->setText("");
    ui->KNAME_7->setText("");
    ui->KNAME_8->setText("");
    ui->KNAME_9->setText("");
    ui->Kpicture_2->setText("");
    ui->Klabel_16->setStyleSheet("border-radius: 30px;");
    // Obtenez l'ID de la ligne sélectionnée. Vous devrez peut-être ajuster cette ligne en fonction de la façon dont votre vue est configurée.
    int row = ui->KtableView->currentIndex().row();
    QModelIndex index = ui->KtableView->model()->index(row, 0); // Remplacez 0 par l'index de la colonne "id_kinees".
    int id = ui->KtableView->model()->data(index).toInt();
    statsKinees(id);
    ui->stackedWidget->setCurrentWidget(ui->page_5);
    QSqlQueryModel *model=k.update(id);
    ui->KlineEdit_10->setText(model->data(model->index(0, 1)).toString());
    ui->KlineEdit_11->setText(model->data(model->index(0, 2)).toString());
    ui->KlineEdit_12->setText(model->data(model->index(0, 3)).toString());
    ui->KlineEdit_13->setText(model->data(model->index(0, 5)).toString());
    ui->KlineEdit_14->setText(model->data(model->index(0, 4)).toString());
    ui->Kimg_2->setText(model->data(model->index(0, 6)).toString());
    QPixmap image(model->data(model->index(0, 6)).toString());
    ui->Klabel_16->setPixmap(image.scaled(ui->Klabel_16->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));


}

void MainWindow::on_KAjouter_3_clicked()
{
    ui->KNAME_5->setText("");
    ui->KNAME_6->setText("");
    ui->KNAME_7->setText("");
    ui->KNAME_8->setText("");
    ui->KNAME_9->setText("");
    ui->Kpicture_2->setText("");
    int row = ui->KtableView->currentIndex().row();
    QModelIndex index = ui->KtableView->model()->index(row, 0); // Remplacez 0 par l'index de la colonne "id_kinees".
    int id = ui->KtableView->model()->data(index).toInt();
    QRegExp regex("^[a-zA-Z]+$");
    QRegExp regex1("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    QRegExp regex2("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");
    QString nom=ui->KlineEdit_10->text();
    QString prenom=ui->KlineEdit_11->text();
    QString email=ui->KlineEdit_12->text();
    QString mdp=ui->KlineEdit_13->text();
    int nb_patient=ui->KlineEdit_14->text().toInt();
    QString img=ui->Kimg_2->text();

    if(nom.isEmpty() ||!regex.exactMatch(nom))
    {
        ui->KNAME_5->setText("incorrect first name");
        return;
    }
    if(img.isEmpty())
    {
        ui->Kpicture_2->setText("veillez choisir une image");
        return;
    }

    if(prenom.isEmpty() ||!regex.exactMatch(prenom))
    {
        ui->KNAME_6->setText("incorrect last name");
        return;
    }
    if(email.isEmpty() ||!regex1.exactMatch(email))
    {
        ui->KNAME_7->setText("incorrect mail");
        return;
    }
    if(mdp.isEmpty() ||!regex2.exactMatch(mdp))
    {
        ui->KNAME_8->setText("8 caracters 1 uppercase,lowercase,number");
        return;
    }
    if(nb_patient<0)
    {
        ui->KNAME_9->setText("nb patient incorrecte");
        return;
    }


    kinees k(id,nom,prenom,email,mdp,nb_patient,img);
    bool test = k.update();
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("UPDATE SUCCESSFULL.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        MainWindow::stats();
        ui->KtableView->setModel(k.afficher());




    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                    QObject::tr("ERROR UPDATE .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    ui->stackedWidget->setCurrentWidget(ui->page_3);



}

void MainWindow::on_KPDF_clicked()
{
    generatePdf();
    QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("PDF GENERATED SUCCESSFULLY.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_KLineSearch_textChanged()
{
    ui->KtableView->setModel(k.search(ui->KLineSearch->text()));
}

void MainWindow::on_KcomboBox_currentIndexChanged()
{
     ui->KtableView->setModel(k.tri(ui->KcomboBox->currentText()));

}




QString MainWindow::generatePassword() {
    QString lowercase = "abcdefghijklmnopqrstuvwxyz";
    QString uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString digits = "0123456789";

    std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());

    QString password;
    password += lowercase[generator() % lowercase.size()];
    password += uppercase[generator() % uppercase.size()];
    password += digits[generator() % digits.size()];

    for(int i = 3; i < 8; ++i) {
        int randomSet = generator() % 3;
        if(randomSet == 0) {
            password += lowercase[generator() % lowercase.size()];
        } else if(randomSet == 1) {
            password += uppercase[generator() % uppercase.size()];
        } else {
            password += digits[generator() % digits.size()];
        }
    }

    std::random_shuffle(password.begin(), password.end());

    return password;
}


void MainWindow::on_KPICTURE_clicked()
{

    ui->Kimg->setText("");

    QString imge = QFileDialog::getOpenFileName(
        this,
        tr("Open Image"),
        "/home",
        tr("Image Files (*.png *.jpg *.bmp)")
    );
    ui->Kimg->setText(imge);
    QPixmap image(imge);
    ui->Klabel_11->setStyleSheet("border-radius: 30px;");
    ui->Klabel_11->setPixmap(image.scaled(ui->Klabel_11->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));



}

void MainWindow::on_KPICTURE_2_clicked()
{
    ui->Kimg_2->setText("");

    QString imge = QFileDialog::getOpenFileName(
        this,
        tr("Open Image"),
        "/home",
        tr("Image Files (*.png *.jpg *.bmp)")
    );
    ui->Kimg_2->setText(imge);
    QPixmap image(imge);
    ui->Klabel_16->setStyleSheet("border-radius: 30px;");
    ui->Klabel_16->setPixmap(image.scaled(ui->Klabel_16->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

void MainWindow::on_LOG_clicked()
{
    ui->mail_err->setText("");
    ui->pass_err->setText("");
    QString email=ui->EMAILL->text();
    QString password=ui->PASSWORD->text();
     QSqlQueryModel *model=k.LOGIN(email);
     if(model->rowCount()==0)
     {
         ui->mail_err->setText("email inexistant");

     }
     else if (model->rowCount()==1 && password!=model->data(model->index(0, 5)).toString())
     {
         ui->pass_err->setText("mot de passe incorrecte ");

     }
     else
     {
          ui->email_info->setText(model->data(model->index(0, 3)).toString());
          ui->nom_info->setText(model->data(model->index(0, 1)).toString());
          ui->img_info->setText(model->data(model->index(0, 6)).toString());
          k.setNom(ui->nom_info->text());
          QIcon profileIcon( ui->img_info->text());
          ui->profile->setIcon(profileIcon);
          ui->profile->setIconSize(QSize(100,100));

          ui->stackedWidget->setCurrentWidget(ui->page_3);

     }


}

void MainWindow::stats()
{


series->clear();

// Exécutez la requête SQL pour obtenir le nombre total de patients
QString queryStr = "SELECT COUNT(*) FROM kinees";
QSqlQuery query;
query.exec(queryStr);
query.next();
int totalPatients = query.value(0).toInt();

// Exécutez des requêtes séparées pour obtenir le nombre de patients pour chaque catégorie
queryStr = "SELECT COUNT(*) FROM kinees WHERE NB_PATIENT > 100";
query.exec(queryStr);
query.next();
int advancedPatients = query.value(0).toInt();

queryStr = "SELECT COUNT(*) FROM kinees WHERE NB_PATIENT >= 50 AND NB_PATIENT <= 100";
query.exec(queryStr);
query.next();
int normalPatients = query.value(0).toInt();

queryStr = "SELECT COUNT(*) FROM kinees WHERE NB_PATIENT < 50";
query.exec(queryStr);
query.next();
int beginnerPatients = query.value(0).toInt();

int advancedPercentage = qRound((double)advancedPatients / totalPatients * 100);
int normalPercentage = qRound((double)normalPatients / totalPatients * 100);
int beginnerPercentage = qRound((double)beginnerPatients / totalPatients * 100);


// Ajoutez les nouvelles données à la série
QPieSlice *slice1 = series->append("Avancé " + QString::number(advancedPercentage) + "%", advancedPatients);
QPieSlice *slice2 = series->append("Normal " + QString::number(normalPercentage) + "%", normalPatients);
QPieSlice *slice3 = series->append("Débutant " + QString::number(beginnerPercentage) + "%", beginnerPatients);

// Activez les labels pour chaque tranche
slice1->setLabelVisible(true);
slice2->setLabelVisible(true);
slice3->setLabelVisible(true);


QChart *chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("Statistiques des Kinees");
  chart->legend()->show();
  chart->setAnimationOptions(QChart::AllAnimations);
  chartView->setChart(chart);


}

void MainWindow::on_forget_clicked()
{

        // Récupérez l'e-mail saisi par l'utilisateur
        QString email = ui->EMAILL->text();

        // Préparez la requête SQL
        QSqlQuery query;
        query.prepare("SELECT MDP FROM kinees WHERE email = :email");
        query.bindValue(":email", email);



        // Exécutez la requête
        if (query.exec() && query.next()) {
            // Si l'e-mail existe dans la base de données, récupérez le mot de passe
            QString password = query.value(0).toString();
            sendMail(email,"PASSWORD RECUPERATION",password);


            // Envoyez le mot de passe à l'e-mail de l'utilisateur
            // (vous devrez utiliser une bibliothèque ou un service d'envoi d'e-mails pour cela)
        } else {
            // Si l'e-mail n'existe pas dans la base de données, affichez un message d'erreur
            QMessageBox::warning(this, "Erreur", "Cet e-mail n'existe pas dans notre base de données.");
        }


}


/*void MainWindow::sendMail(const QString &recipient, const QString &subject, const QString &body) {
    Smtp* smtp = new Smtp("rayanferjani55@gmail.com","dosgzbkpsprqnftf", "smtp.gmail.com", 465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    // Charger les informations d'identification à partir du fichier JSON
    QFile file("C:/Users/rayan/Downloads/kinees/VITALTHERA - Copie - Copie/client.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray json = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject obj = doc.object();
    QString clientId = obj["client_id"].toString();
    QString clientSecret = obj["client_secret"].toString();
    QString refreshToken = obj["refresh_token"].toString();

    // Configuration de la requête HTTP pour obtenir un jeton d'accès
    QUrl url("https://www.googleapis.com/oauth2/v4/token");
    QUrlQuery query;
    query.addQueryItem("client_id", clientId);
    query.addQueryItem("client_secret", clientSecret);
    query.addQueryItem("refresh_token", refreshToken);
    query.addQueryItem("grant_type", "refresh_token");

    // Envoi de la requête HTTP
    QNetworkAccessManager manager;
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply *reply = manager.post(request, query.toString().toUtf8());
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    // Traitement de la réponse pour obtenir le jeton d'accès
    QByteArray tokenData = reply->readAll();
    QJsonDocument tokenDoc = QJsonDocument::fromJson(tokenData);
    QString accessToken = tokenDoc.object()["access_token"].toString();

    // Utilisation du jeton d'accès pour envoyer un e-mail via l'API Gmail
    QUrl sendUrl("https://www.googleapis.com/gmail/v1/users/me/messages/send");
    QNetworkRequest sendRequest(sendUrl);
    sendRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    sendRequest.setRawHeader("Authorization", "Bearer " + accessToken.toUtf8());

    // Construction du message MIME pour l'e-mail
    QString rawMessage = "From: rayanferjani55@gmail.com\r\n"
                         "To: " + recipient + "\r\n"
                         "Subject: " + subject + "\r\n"
                         "Content-Type: text/plain; charset=\"UTF-8\"\r\n\r\n"
                         + body;

    QByteArray messageData = rawMessage.toUtf8();
    QByteArray encodedData = messageData.toBase64();
    QString base64Message = QString(encodedData);

    QJsonObject message;
    message["raw"] = base64Message;

    // Envoi de la requête HTTP pour envoyer le message
    QJsonDocument docMessage(message);
    QByteArray jsonData = docMessage.toJson();

    QNetworkReply *replySend = manager.post(sendRequest, jsonData);
    loop.connect(replySend, SIGNAL(finished()), SLOT(quit()));
    loop.exec();

    // Vérifier la réponse
    if (replySend->error() != QNetworkReply::NoError) {
        qDebug() << "Error sending email:" << replySend->errorString();
    } else {
        qDebug() << "Email sent successfully!";
    }

    delete reply;
    delete replySend;
}*/

void MainWindow::sendMail(const QString &recipient, const QString &subject, const QString &body)
{
    Smtp* smtp = new Smtp("rayanferjani55@gmail.com","dosgzbkpsprqnftf", "smtp.gmail.com",465);
   connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("rayanferjani55@gmail.com", recipient,subject,body);
    QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("MAIL SENT SUCCESSFULLY .\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);



}
void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


QMap<QString, int> MainWindow::getData(int id_kinee) {
    QMap<QString, int> dataMap;



    QSqlQuery query;
    for (int month = 1; month <= 12; ++month) {
        QString str_month = QString::number(month);
        if (str_month.length() == 1) {
            str_month = "0" + str_month;
        }

        QString sql = QString("SELECT COUNT(*) FROM seance WHERE id_kinees=%1 AND DTE LIKE '2024-%2-%%'").arg(id_kinee).arg(str_month);
        query.exec(sql);

        if (query.next()) {
            dataMap[str_month] = query.value(0).toInt();
        }
    }

    return dataMap;
}




void MainWindow::statsKinees(int id) {
    QMap<QString, int> dataMap = getData(id);


        series2->clear();

        for(auto it = dataMap.begin(); it != dataMap.end(); ++it) {
            series2->append(it.key().toInt(), it.value());
        }

        QChart *chart = new QChart();
        chart->addSeries(series2);
        chart->setTitle("Nombre de seances par mois");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QCategoryAxis *axisX = new QCategoryAxis();
        for (int i = 1; i <= 12; ++i) {
            axisX->append(QString::number(i), i);
        }
        axisX->setStartValue(1);
        axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
        chart->addAxis(axisX, Qt::AlignBottom);
        series2->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        chart->addAxis(axisY, Qt::AlignLeft);
        series2->attachAxis(axisY);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);


    chartVieww->setRenderHint(QPainter::Antialiasing);

   chartVieww->setChart(chart);
}


void MainWindow::logOut()
{
    ui->EMAILL->setText("");
    ui->PASSWORD->setText("");
     ui->stackedWidget->setCurrentWidget(ui->page);

}













void MainWindow::on_KmenuBtn_3_clicked()
{
    slider(ui->KleftMenu,ui->mainBody);
    slider(ui->KleftMenu_2,ui->mainBody_2);
     slider(ui->KleftMenu_3,ui->mainBody_3);
}

void MainWindow::on_KmenuBtn_4_clicked()
{
    slider(ui->KleftMenu,ui->mainBody);
    slider(ui->KleftMenu_2,ui->mainBody_2);
    slider(ui->KleftMenu_3,ui->mainBody_3);
}



////////////////////////////////saifeddinnnne///////////////////////////////////////////






void MainWindow::updateChart_dal()
{
    series_saif->clear();
    series_saif->append("Added", addedCount);
    series_saif->append("Updated", updatedCount);
    series_saif->append("Deleted", deletedCount);

    QPieSlice *slice_1 = series_saif->slices().at(0);
    slice_1->setExploded(true);
    slice_1->setLabelVisible(true);
    slice_1->setPen(QPen(Qt::red,1));
    slice_1->setBrush(Qt::red);

    QPieSlice *slice_2 = series_saif->slices().at(1);
    slice_2->setExploded(true);
    slice_2->setLabelVisible(true);
    slice_2->setPen(QPen(Qt::green,1));
    slice_2->setBrush(Qt::green);

    QPieSlice *slice_3 = series_saif->slices().at(2);
    slice_3->setExploded(true);
    slice_3->setLabelVisible(true);
    slice_3->setPen(QPen(Qt::blue,1));
    slice_3->setBrush(Qt::blue);



}


void MainWindow::on_Ajouter_3_dal_clicked()
{

    // Increment the added count
    addedCount++;
    updateChart_dal();

    //recuperation des information
    int id=ui->lineEdit_id_dal->text().toInt();
    QString nom=ui->lineEdit_nom_dal->text();
    QString prenom=ui->lineEdit_prenom_dal->text();
    QString tel=ui->lineEdit_tel_dal->text();
    int quantitee=ui->lineEdit_quantitee_dal->text().toInt();

    supplier S(id,nom,prenom,tel,quantitee);
    bool test=S.ajouterSupplier();

    if(test)
    {
        ui->tableView_dal->setModel(Etmp.afficherSupplier());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    ui->stackedWidget->setCurrentWidget(ui->liste_dal);

}

void MainWindow::on_ajouter_dal_clicked()
{

    ui->stackedWidget->setCurrentWidget(ui->ajout_dal);
}

void MainWindow::on_Delete_dal_clicked()
{
    deletedCount++;
    updateChart_dal();

    // Récupération de l'ID du supplier sélectionné dans le tableau
    QItemSelectionModel *select = ui->tableView_dal->selectionModel();
    QModelIndexList list = select->selectedRows();

    if(list.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                    QObject::tr("Veuillez sélectionner un fournisseur à supprimer.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return; // Sortir de la fonction car rien n'a été sélectionné
    }

    int id = list.at(0).data().toInt();

    // Appel de la fonction supprimerSupplier avec l'ID
    bool test = Etmp.supprimerSupplier(id);

    if(test)
    {
        ui->tableView_dal->setModel(Etmp.afficherSupplier());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Suppression non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    //ui->stackedWidget->setCurrentWidget(ui->liste);
}





void MainWindow::on_update_2_dal_clicked()
{

    updatedCount++;
    updateChart_dal();

    // Récupération de l'ID du fournisseur sélectionné dans le tableau
    QItemSelectionModel *select = ui->tableView_dal->selectionModel();
    QModelIndexList list = select->selectedRows();

    if(list.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                    QObject::tr("Veuillez sélectionner un fournisseur à mettre à jour.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return; // Sortir de la fonction car rien n'a été sélectionné
    }

    int id = list.at(0).data().toInt();

    // Récupération des autres informations de mise à jour
    QString nom = ui->lineEdit_nom_3_dal->text();
    QString prenom = ui->lineEdit_prenom_3_dal->text();
    QString tel = ui->lineEdit_tel_3_dal->text();
    int quantitee = ui->lineEdit_quantitee_3_dal->text().toInt();

    // Création de l'objet supplier avec les nouvelles informations
    supplier S(id, nom, prenom, tel, quantitee);

    // Appel de la fonction modifierSupplier avec l'ID et les nouvelles informations
    bool test = S.modifierSupplier();

    if(test)
    {
        ui->tableView_dal->setModel(Etmp.afficherSupplier());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Modification effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Modification non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}






void MainWindow::on_update_dal_clicked()
{
    // Récupération de l'ID du fournisseur sélectionné dans le tableau
    QItemSelectionModel *select = ui->tableView_dal->selectionModel();
    QModelIndexList list = select->selectedRows();

    if(list.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Warning"),
                    QObject::tr("Veuillez sélectionner un fournisseur à mettre à jour.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        return; // Sortir de la fonction car rien n'a été sélectionné
    }

    int id = list.at(0).data().toInt();

    // Récupération des informations du fournisseur sélectionné
    QString nom;
    QString prenom;
    QString tel;
    int quantitee;

    for (int row = 0; row < ui->tableView_dal->model()->rowCount(); ++row) {
        if (ui->tableView_dal->model()->index(row, 0).data().toInt() == id) { // Assuming the ID is in the 0th column
            nom = ui->tableView_dal->model()->index(row, 1).data().toString(); // Assuming the name is in the 1st column
            prenom = ui->tableView_dal->model()->index(row, 2).data().toString(); // Assuming the last name is in the 2nd column
            tel = ui->tableView_dal->model()->index(row, 3).data().toString(); // Assuming the phone number is in the 3rd column
            quantitee = ui->tableView_dal->model()->index(row, 4).data().toInt(); // Assuming the quantity is in the 4th column
            break;
        }
    }

    // Set the retrieved information in the line edits
    ui->lineEdit_nom_3_dal->setText(nom);
    ui->lineEdit_prenom_3_dal->setText(prenom);
    ui->lineEdit_tel_3_dal->setText(tel);
    ui->lineEdit_quantitee_3_dal->setText(QString::number(quantitee));

    ui->stackedWidget->setCurrentWidget(ui->modifier_dal);
}


void MainWindow::on_liste_s_dal_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}


void MainWindow::on_update_s_dal_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->modifier_dal);
}



void MainWindow::on_add_s_dal_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->ajout_dal);
}

void MainWindow::on_liste_s_2_dal_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}




void MainWindow::on_PDF_dal_clicked()
{
    // Get the data from the model
    QSqlQueryModel *model = static_cast<QSqlQueryModel*>(ui->tableView_dal->model());

    // Create a QTextDocument to hold the content of the PDF
    QTextDocument document;
    QString html = "<html>"
                   "<head>"
                   "<style>"
                   "body {"
                   "    font-family: Arial, sans-serif;"
                   "    text-align: center;"
                   "}"
                   "table {"
                   "    margin: 50px auto;"  // Center the table and add margin from top
                   "    width: 80%;"  // Set table width to 80% of the page
                   "    border-collapse: collapse;"
                   "}"
                   "th, td {"
                   "    border: 2px solid black;"
                   "    padding: 12px;"
                   "}"
                   "th {"
                   "    background-color: #f2f2f2;"
                   "}"
                   "</style>"
                   "</head>"
                   "<body>"
                   "<h1>Suppliers List</h1>"
                   "<table>"
                   "<tr>"
                   "<th>ID</th>"
                   "<th>Name</th>"
                   "<th>Prename</th>"
                   "<th>Tel</th>"
                   "<th>Quantity</th>"
                   "</tr>";

    for (int row = 0; row < model->rowCount(); ++row) {
        int id = model->data(model->index(row, 0)).toInt();
        QString nom = model->data(model->index(row, 1)).toString();
        QString prenom = model->data(model->index(row, 2)).toString();
        QString tel = model->data(model->index(row, 3)).toString();
        int quantitee = model->data(model->index(row, 4)).toInt();

        html += QString("<tr>"
                        "<td>%1</td>"
                        "<td>%2</td>"
                        "<td>%3</td>"
                        "<td>%4</td>"
                        "<td>%5</td>"
                        "</tr>").arg(id).arg(nom).arg(prenom).arg(tel).arg(quantitee);
    }

    html += "</table></body></html>";
    document.setHtml(html);

    // Ask the user for the filename and location to save the PDF
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Save PDF", QString(), "PDF Files (*.pdf)");

    if (!fileName.isEmpty()) {
        // Create a QPrinter object
        QPrinter printer(QPrinter::PrinterResolution);

        // Set printer properties
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        // Print the document to the printer
        document.print(&printer);

        QMessageBox::information(nullptr, "PDF Created", "PDF file has been created successfully.");
    }
}









void MainWindow::on_linesearch_dal_textChanged(const QString &arg1)
{
    // Création d'une instance de Supplier pour utiliser la méthode chercher_nom
    supplier supplier;
    QSqlQueryModel *model = supplier.chercher_nom(arg1);
    if (model) {
      ui->tableView_dal->setModel(model);
    } else {
      // Afficher un message d'erreur en cas de problème
      //qDebug() << "La recherche a échoué";
    }
}





void MainWindow::on_comboBox_dal_currentIndexChanged(int index)
{
    // Determine the sort order based on the selected index
    Qt::SortOrder order = (index == 0) ? Qt::AscendingOrder : Qt::DescendingOrder;

    // Sorting logic
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(ui->tableView_dal->model());
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setSortRole(Qt::EditRole);
    proxyModel->sort(1, order);
    ui->tableView_dal->setModel(proxyModel);
}

void MainWindow::updateProgressBar_dal()
{
    // Get the total quantity of all suppliers
    int totalQuantity = 0;
    for (int row = 0; row < ui->tableView_dal->model()->rowCount(); ++row) {
        totalQuantity += ui->tableView_dal->model()->index(row, 4).data().toInt();
    }

    // Get the quantity of the selected supplier
    int selectedId = ui->id_stat_dal->text().toInt();
    int supplierQuantity = 0;
    for (int row = 0; row < ui->tableView_dal->model()->rowCount(); ++row) {
        if (ui->tableView_dal->model()->index(row, 0).data().toInt() == selectedId) {
            supplierQuantity = ui->tableView_dal->model()->index(row, 4).data().toInt();
            break;
        }
    }

    // Calculate the percentage
    int percentage = 0;
    if (totalQuantity > 0) {
        percentage = (supplierQuantity * 100) / totalQuantity;
    }

    // Update the progress bar
    ui->progressBar_dal->setValue(percentage);

}

void MainWindow::on_supmax_dal_clicked()
{
    int maxQuantity = -1;
    QString supplierName;

    for (int row = 0; row < ui->tableView_dal->model()->rowCount(); ++row) {
        int quantity = ui->tableView_dal->model()->index(row, 4).data().toInt(); // Assuming the quantity is in the 4th column
        if (quantity > maxQuantity) {
            maxQuantity = quantity;
            supplierName = ui->tableView_dal->model()->index(row, 1).data().toString(); // Assuming the name is in the 1st column
        }
    }

    // Set the name of the supplier with the most quantity in the line edit
    ui->idmax_dal->setText(supplierName);
}

void MainWindow::on_btn_total_dal_clicked()
{
    int totalQuantity = 0;

    for (int row = 0; row < ui->tableView_dal->model()->rowCount(); ++row) {
        int quantity = ui->tableView_dal->model()->index(row, 4).data().toInt();
        totalQuantity += quantity;
    }

    // Set the total quantity in the line edit
    ui->total_dal->setText(QString::number(totalQuantity));
}

void MainWindow::on_Kevent_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}

void MainWindow::on_Kevent_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}

void MainWindow::on_Kevent_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}

void MainWindow::on_employe_dal_clicked()
{
   kinees_switch();
}

void MainWindow::on_employe_4_dal_clicked()
{
   kinees_switch();
}

void MainWindow::on_employe_6_dal_clicked()
{
   kinees_switch();
}



/////////////////////////////////SAIF BEN FARDJELKJRA///////////////////////////////////////////




void MainWindow::page1Widget() {

    ui->stackedWidget->setCurrentWidget(ui->page_sbf);
}
void MainWindow::page5Widget() {

    ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);
}

void MainWindow::page6Widget() {

    ui->stackedWidget->setCurrentWidget(ui->page_4_sbf);
}

void MainWindow::page2Widget() {

    ui->stackedWidget->setCurrentWidget(ui->page_8_sbf);
}

void MainWindow::page3Widget() {

    ui->stackedWidget->setCurrentWidget(ui->page_2_sbf);
}

void MainWindow::pageaffichercalWidget() {

    ui->stackedWidget->setCurrentWidget(ui->page_3_sbf);
}






void MainWindow::on_Update_3_sbf_clicked() {
    // Convertir le texte de lineEdit en entier
    int seanceId = ui->lineEdit_sbf->text().toInt(); // Utilisation de toInt() pour la conversion

    Seance seance;

    if (!seance.existance(seanceId)) {
        // Créer une requête SQL pour récupérer les détails de la séance à partir de la base de données
        QSqlQuery query;
        query.prepare("SELECT ID_SEANCE, DTE, DUREE, PRIX, STATUT, NOM_PATIENT, NOM_KINEES, NOM_ACTIVITY FROM SEANCE WHERE ID_SEANCE = ?");
        query.addBindValue(seanceId);

        if(query.exec() && query.next()) {
            // Récupérer les données de la requête
            int id = query.value(0).toInt();
            QString date = query.value(1).toString();
            int duree = query.value(2).toInt();
            double prix = query.value(3).toDouble();
            QString statut = query.value(4).toString();
            QString nom_patient = query.value(5).toString();
            QString nom_kinee = query.value(6).toString();
            QString nom_activite = query.value(7).toString();

            // Construire le texte à encoder dans le code QR
            QString seanceDetails = "Seance details: " + QString::number(id) + " " + date + " " + QString::number(duree) + " " + QString::number(prix) + " " + statut + " " + nom_patient + " " + nom_kinee + " " + nom_activite;

            // Générer le code QR à partir des détails de la séance
            using namespace qrcodegen;
            QrCode qr = QrCode::encodeText(seanceDetails.toUtf8().data(), QrCode::Ecc::MEDIUM);
            int scale = 10; // Facteur d'échelle pour agrandir le QR code
            int qrSize = qr.getSize() * scale; // Taille du QR code agrandi
            QImage qrImage(qrSize, qrSize, QImage::Format_RGB32);
            QRgb black = qRgb(0, 0, 0);
            QRgb white = qRgb(255, 255, 255);

            for (int y = 0; y < qrSize; ++y) {
                for (int x = 0; x < qrSize; ++x) {
                    // Mise à l'échelle de chaque module du QR code
                    int moduleX = x / scale;
                    int moduleY = y / scale;
                    qrImage.setPixel(x, y, qr.getModule(moduleX, moduleY) ? black : white);
                }
            }

            // Afficher l'image QR dans une boîte de dialogue
            QMessageBox::information(this, "QR Code Generated", "QR Code Generated Successfully!");
            QLabel *label = new QLabel();
            label->setPixmap(QPixmap::fromImage(qrImage));
            label->setFixedSize(qrSize, qrSize);
            label->show();
        } else {
            QMessageBox::warning(this, "Seance Not Found", "The specified seance was not found in the database.");
        }
    } else {
        QMessageBox::warning(this, "Seance Not Found", "The specified seance was not found in the database.");
    }
}













void MainWindow::on_AAjouter_sbf_clicked()
{
    int id = ui->AName_sbf->text().toInt();
    QString dte = ui->ADuration_3_sbf->text();
    int duree = ui->type_combobox_3_sbf->currentText().toInt();

    QString prixText = ui->ADuration_7_sbf->text();

    if (prixText.isEmpty()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez saisir un prix."));
        return;
    }

    bool prixValid = false;
    double prix = ui->ADuration_7_sbf->text().toDouble(&prixValid);

    if (!prixValid) {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez saisir un nombre pour le prix."));
        return;
    }
     QString noma = ui->type_combobox_sbf->currentText();
    if( noma.isEmpty()){
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez aller ajouter une activite."));
        return;
    }
    QString statut = ui->type_combobox_2_sbf->currentText();
    QString nom = ui->AcomboBox_2_sbf->currentText();
    QString nomk = ui->AcomboBox_sbf->currentText();



    Seance nouvelleSeance(id, dte, duree, prix, statut, nom, nomk, noma);

    bool insertionReussie = nouvelleSeance.ajouter();

    if (insertionReussie) {
        ui->tableView_sbf->setModel(Stemp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\n"
                                             "Cliquez sur Annuler pour quitter."),
                                 QMessageBox::Cancel);

        // Construction du corps du mail
        QString body = "Date: " + dte + "\n";
        body += "Durée: " + QString::number(duree) + "\n";
        body += "Prix: " + QString::number(prix) + "\n";

        // Adresse email de destination récupérée depuis AcomboBox_2_sbf
        QString toEmail = ui->AcomboBox_2_sbf->currentText();

        Smtp* smtp = new Smtp("rayanferjani55@gmail.com","dosgzbkpsprqnftf", "smtp.gmail.com",465);
       connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


        smtp->sendMail2("rayanferjani55@gmail.com", toEmail,"confirmation seance",body);
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("MAIL SENT SUCCESSFULLY.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);






        qDebug() << "Envoi du mail en cours...";

        ui->stackedWidget->setCurrentWidget(ui->page_sbf);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Cliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
    ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);
}







void MainWindow::on_ADelete_6_sbf_clicked() {
    QModelIndexList selectedIndexes = ui->tableView_sbf->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, tr("Aucune ligne sélectionnée"),
                             tr("Veuillez sélectionner une ligne à supprimer."),
                             QMessageBox::Ok);
        return;
    }

    int id = selectedIndexes.at(0).data().toInt();

    Seance Stemp;
    bool test = Stemp.supprimer(id);

    if(test) {
        // Mise à jour du modèle après la suppression
        ui->tableView_sbf->setModel(Stemp.afficher());


        QMessageBox::information(this, tr("Suppression réussie"),
                                 tr("La séance a été supprimée avec succès."),
                                 QMessageBox::Ok);
    } else {
        QMessageBox::critical(this, tr("Erreur de suppression"),
                              tr("La suppression de la séance a échoué."),
                              QMessageBox::Ok);
    }
}








void MainWindow::on_Amodifier_sbf_clicked()
{
    QString statut = ui->AcomboBox_6_sbf->currentText();
    QString nom = ui->AcomboBox_4_sbf->currentText();
    QString nomk = ui->AcomboBox_3_sbf->currentText();
    QString noma = ui->AcomboBox_5_sbf->currentText();
    int id = ui->AName_2_sbf->text().toInt();
    QString dte = ui->AName_3_sbf->text();
    int duree = ui->AcomboBox_7_sbf->currentText().toInt();


    QString prixText = ui->ADuration_5_sbf->text();


    if (prixText.isEmpty()) {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez saisir un prix."));
        return;
    }

    bool prixValid = false;
    double prix = ui->ADuration_5_sbf->text().toDouble(&prixValid);

    if (!prixValid) {
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez saisir un nombre pour le prix."));
        return;
    }
    if(noma.isEmpty()){
        QMessageBox::critical(this, tr("Erreur"), tr("Veuillez allez ajouter une activité"));
        return;
    }




    Seance Stemp;
    Stemp.setIdSeance(id);
    Stemp.setDate(dte);
    Stemp.setDuree(duree);
    Stemp.setPrix(prix);
    Stemp.setStatut(statut);
    Stemp.setnom_patient(nom);
    Stemp.setnom_kinee(nomk);
    Stemp.setnom_activite(noma);

    bool test = Stemp.modifier(id, dte, duree, prix, statut, nom, nomk, noma);
    if(statut=="annulee")
    {
        Smtp* smtp = new Smtp("rayanferjani55@gmail.com","dosgzbkpsprqnftf", "smtp.gmail.com",465);
       connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


        smtp->sendMail2("rayanferjani55@gmail.com", ui->AcomboBox_4_sbf->currentText(),"annulation seance","votre seance a ete annule");
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("MAIL SENT SUCCESSFULLY.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

    if (test)
    {

        ui->tableView_sbf->setModel(Stemp.afficher());
        QMessageBox::information(this, tr("Modification réussie"),
                                 tr("La séance a été modifiée avec succès."),
                                 QMessageBox::Ok);

        ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);
    }
    else
    {
        QMessageBox::critical(this, tr("Erreur de modification"),
                              tr("La modification de la séance a échoué."),
                              QMessageBox::Ok);
    }
}


void MainWindow::on_AAdd_6_sbf_clicked()
{
    QSqlQuery query;
    query.exec("SELECT MAX(ID_SEANCE) FROM SEANCE");
    int lastId = 0;
    if (query.next()) {
        lastId = query.value(0).toInt() + 1;
    }

    ui->AName_sbf->setText(QString::number(lastId));

    ui->AcomboBox_2_sbf->clear();
    ui->AcomboBox_sbf->clear();
    ui->type_combobox_sbf->clear();
    Seance Stemp;

    // Ajout des séances aux ComboBox
    vector<QString> patientNames = Stemp.recuperation_nom_patient();
    for (const QString& patientName : patientNames) {
        ui->AcomboBox_2_sbf->addItem(patientName);
    }
    vector<QString> kineeNames = Stemp.recuperation_nom_kinee();
    for (const QString& kineeName : kineeNames) {
        ui->AcomboBox_sbf->addItem(kineeName);
    }
    QMap<QString,QString> activiteNames = Stemp.recuperation_nom_activite(ui->AcomboBox_2_sbf->currentText());
              for(QMap<QString,QString>::iterator path=activiteNames.begin();path!=activiteNames.end();path++)
              {
                  QIcon icon(path.value());
                   ui->type_combobox_sbf->setIconSize(QSize(48,48));
                  ui->type_combobox_sbf->addItem(icon,path.key(),path.value()); // Ajoute l'image au combobox. Le deuxième paramètre est le texte, laissé vide ici.

              }
    ui->calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);


       // Récupérer les dates des séances depuis la base de données
       vector<QString> datesSeances = Stemp.recuperation_date();

       // Définir le format pour la couleur rouge (dimanche)
       QTextCharFormat rougeFormat;
       QColor couleurRouge(255, 0, 0); // Rouge
       rougeFormat.setForeground(couleurRouge);

       // Définir le format pour la couleur noire (samedi)
       QTextCharFormat noirFormat;
       QColor couleurNoire(0, 0, 0); // Noir
       noirFormat.setForeground(couleurNoire);

       // Appliquer le format rouge au dimanche et le format noir au samedi pour calendarWidget
       ui->calendarWidget->setWeekdayTextFormat(Qt::Saturday, noirFormat);
       ui->calendarWidget->setWeekdayTextFormat(Qt::Sunday, rougeFormat);



       // Parcourir les dates des séances récupérées et appliquer le format rouge à chaque date
       for (int year = ui->calendarWidget->minimumDate().year(); year <= ui->calendarWidget->maximumDate().year(); ++year) {
           for (int month = 1; month <= 12; ++month) {
               for (int day = 1; day <= QDate(year, month, 1).daysInMonth(); ++day) {
                   QDate date(year, month, day);
                   if (date.dayOfWeek() == Qt::Sunday || std::find(datesSeances.begin(), datesSeances.end(), date.toString("yyyy-MM-dd")) != datesSeances.end()) {
                       ui->calendarWidget->setDateTextFormat(date, rougeFormat);

                   } else {
                       ui->calendarWidget->setDateTextFormat(date, noirFormat);

                   }
               }
           }
       }
}




void MainWindow::on_pushButton_5_sbf_clicked()
{
    {
        Seance seance;
        QSqlQueryModel *sortedModel = seance.afficher_sort();
        ui->tableView_sbf->setModel(sortedModel);
    }
}

void MainWindow::on_pushButton_2_sbf_clicked()
{
    QString nom = ui->LineSearch_6->text();
        Seance seance;
        QSqlQueryModel *searchedModel = seance.Search(nom);
        ui->tableView_sbf->setModel(searchedModel);



}



void MainWindow::on_PDF_sbf_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT ID_SEANCE, DTE, DUREE, PRIX, STATUT, NOM_PATIENT, NOM_KINEES, NOM_ACTIVITY FROM SEANCE");
    if (!query.exec()) {
        qDebug() << "Error executing SQL query:" << query.lastError().text();
        return;
    }

    QPdfWriter pdf("C:/Users/rayan/Downloads/kinees/kinees-saifeddin/seance.pdf");


    pdf.setPageSize(QPageSize(QPageSize::A1));
    pdf.setPageOrientation(QPageLayout::Orientation::Landscape);

    QPainter painter(&pdf);
    if (!painter.isActive()) {
        qDebug() << "Error: Painter is not active.";
        return;
    }

    QFont font = painter.font();
    font.setPointSize(15);
    font.setFamily("Arial");
    painter.setFont(font);

    int y = 0;
    const int yOffset = 500;
    painter.setPen(Qt::red);
    QFont titleFont("Arial", 50, QFont::Bold);
    painter.setFont(titleFont);
    QString title="Liste des seances";
    QRect titleRect = painter.boundingRect(QRect(), Qt::AlignCenter, title);
    int titleWidth = titleRect.width();
    int titleX = (pdf.width() - titleWidth) / 2;
    int titleY = 550;
    painter.drawText(titleX, titleY, title);
    int columnWidth = 3800;
    int columnSpacing = 500;
    painter.setPen(Qt::blue);
    QFont headerFont("Arial", 18, QFont::Bold);
    painter.setFont(headerFont);
    painter.drawText(2000, 3300, "ID_SEANCE");
    painter.drawText(2000 + columnWidth + columnSpacing, 3300, "DTE");
    painter.drawText(2000 + 2 * (columnWidth + columnSpacing), 3300, "DUREE");
    painter.drawText(2000 + 3 * (columnWidth + columnSpacing), 3300, "PRIX");
    painter.drawText(2000 + 4 * (columnWidth + columnSpacing), 3300, "STATUT");
    painter.drawText(2000 + 5 * (columnWidth + columnSpacing), 3300, "NOM_PATIENT");
    painter.drawText(2000 + 6 * (columnWidth + columnSpacing), 3300, "NOM_KINEES");
    painter.drawText(2000 + 7 * (columnWidth + columnSpacing), 3300, "NOM_ACTIVITY");
    y = 3500;

    while (query.next()) {
        y += yOffset;
        painter.setPen(Qt::black);
        painter.drawText(2000, y, query.value(0).toString());
        painter.drawText(2000 + columnWidth + columnSpacing, y, query.value(1).toString());
        painter.drawText(2000 + 2 * (columnWidth + columnSpacing), y, query.value(2).toString());
        painter.drawText(2000 + 3 * (columnWidth + columnSpacing), y, query.value(3).toString());
        painter.drawText(2000 + 4 * (columnWidth + columnSpacing), y, query.value(4).toString());
        painter.drawText(2000 + 5 * (columnWidth + columnSpacing), y, query.value(5).toString());
        painter.drawText(2000 + 6 * (columnWidth + columnSpacing), y, query.value(6).toString());
        painter.drawText(2000 + 7 * (columnWidth + columnSpacing), y, query.value(7).toString());

        if (y > pdf.height() - 500) {
            if (!pdf.newPage()) {
                qDebug() << "Error: Failed to create a new page.";
                return;
            }
            y = 500;
        }
    }
    painter.end();
    QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/rayan/Downloads/kinees/kinees-saifeddin/seance.pdf"));

}




/*
       //ui->calendarWidget->setDateTextFormat(date, format); transforme en red lors du click
    //qDebug() << "selected date : " << date;

}*/











void MainWindow::on_calendarWidget_selectionChanged() {
    // Récupérer la date sélectionnée dans le calendrier
    QDate selectedDate = ui->calendarWidget->selectedDate();
    // Convertir la date en format de chaîne et la mettre dans le QLineEdit
    ui->ADuration_3_sbf->setText(selectedDate.toString("yyyy-MM-dd"));
}


void MainWindow::on_choisir_calender_sbf_clicked()
{
    QString dateString = ui->ADuration_3_sbf->text();
    QDate date = QDate::fromString(dateString, "yyyy-MM-dd");

    // Vérifier si la date est un dimanche
    if (date.dayOfWeek() == Qt::Sunday) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de planifier une séance le dimanche. Veuillez choisir une autre date."));
        return;
    } else {

        // Si la date n'est pas un dimanche, naviguer vers la page 2
        page2Widget();
    }

}



QDate MainWindow::on_calendarWidget_2_selectionChanged()
{
    // Récupérer la date sélectionnée dans le calendrier
    return ui->calendarWidget_2->selectedDate();
}







void MainWindow::on_afficher_calender_sbf_clicked() {
    // Récupérer la date sélectionnée dans le calendrier
    QDate selectedDate = ui->calendarWidget_2->selectedDate();

    // Vérifier si la date est un dimanche ou si elle est marquée en rouge
    QTextCharFormat format = ui->calendarWidget_2->dateTextFormat(selectedDate);
    if (selectedDate.dayOfWeek() == Qt::Sunday || format.foreground().color() == QColor(0, 0, 0)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Pas de séances pour cette date. Veuillez choisir une autre date."));
        return;
    }

    // Exécuter la méthode afficherPourDate pour obtenir les séances pour la date sélectionnée
    QSqlQueryModel *model = Stemp.afficherPourDate(selectedDate);

    // Vérifier si le modèle est valide
    if (model) {
        // Afficher les lignes correspondantes dans le tableau tab
        ui->tableView_sbf->setModel(model);
        ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);



    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible de récupérer les données pour la date sélectionnée."));
    }
}









void MainWindow::on_Statistics_sbf_clicked()
{
    // Effectuer les requêtes SQL pour récupérer les données
    QSqlQueryModel *model = new QSqlQueryModel();

    // Récupérer le nombre total de séances
    model->setQuery("SELECT COUNT(*) FROM SEANCE");
    int total = model->data(model->index(0, 0)).toInt();

    // Regrouper les séances par mois et récupérer le nombre de séances pour chaque mois
    model->setQuery("SELECT SUBSTR(DTE, 6, 2), COUNT(*) FROM SEANCE GROUP BY SUBSTR(DTE, 6, 2)");
    QMap<QString, int> seancesByMonth;
    while (model->canFetchMore())
        model->fetchMore();
    int rows = model->rowCount();
    for(int i = 0; i < rows; ++i) {
        QString month = model->record(i).value(0).toString();
        int count = model->record(i).value(1).toInt();
        seancesByMonth[month] = count;
    }

    // Créer les étiquettes pour les mois de l'année
    QStringList monthsLabels = {"Janvier", "Février", "Mars", "Avril", "Mai", "Juin", "Juillet", "Août", "Septembre", "Octobre", "Novembre", "Décembre"};

    // Créer la série de données pour le graphique
    QPieSeries *series = new QPieSeries();
    for (int i = 1; i <= 12; ++i) {
        QString monthKey = QString::number(i).rightJustified(2, '0'); // Pad avec un zéro à gauche si nécessaire
        QString label = monthsLabels.at(i - 1);
        int count = seancesByMonth.value(monthKey, 0);
        double percentage = (count * 100.0) / total;
        if (count > 0)
            series->append(QString("%1\n%2%").arg(label).arg(QString::number(percentage, 'f', 2)), count);
    }

    // Créer le graphique en camembert
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pourcentage de séances par mois");
    chart->setBackgroundVisible(false);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Afficher le graphique dans QChartView
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(681, 381); // Définir la taille minimale
    chartView->show();
}






void MainWindow::on_AList_6_sbf_clicked()
{
    Seance temp;
    ui->calendarWidget_2->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    // Récupérer les dates des séances depuis la base de données
    vector<QString> datesSeances = temp.recuperation_date();

    // Définir le format pour la couleur rouge (dimanche)
    QTextCharFormat rougeFormat;
    QColor couleurRouge(255, 0, 0); // Rouge
    rougeFormat.setForeground(couleurRouge);

    // Définir le format pour la couleur noire (samedi)
    QTextCharFormat noirFormat;
    QColor couleurNoire(0, 0, 0); // Noir
    noirFormat.setForeground(couleurNoire);



    // Appliquer le format rouge au dimanche et le format noir au samedi pour calendarWidget_2
    ui->calendarWidget_2->setWeekdayTextFormat(Qt::Saturday, noirFormat);
    ui->calendarWidget_2->setWeekdayTextFormat(Qt::Sunday, rougeFormat);

    // Parcourir les dates des séances récupérées et appliquer le format rouge à chaque date valide et noir sinon
    for (int year = ui->calendarWidget_2->minimumDate().year(); year <= ui->calendarWidget_2->maximumDate().year(); ++year) {
        for (int month = 1; month <= 12; ++month) {
            for (int day = 1; day <= QDate(year, month, 1).daysInMonth(); ++day) {
                QDate date(year, month, day);
                if (date.dayOfWeek() == Qt::Sunday || std::find(datesSeances.begin(), datesSeances.end(), date.toString("yyyy-MM-dd")) != datesSeances.end()) {

                    ui->calendarWidget_2->setDateTextFormat(date, rougeFormat);
                } else {

                    ui->calendarWidget_2->setDateTextFormat(date, noirFormat);
                }
            }
        }
    }
    ui->stackedWidget->setCurrentWidget(ui->page_3_sbf);
}




void MainWindow::on_AUpdate_6_sbf_clicked()
{
    Seance temp;

    ui->calendarWidget_3->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    // Récupérer les dates des séances depuis la base de données
    vector<QString> datesSeances = temp.recuperation_date();

    // Définir le format pour la couleur rouge (dimanche)
    QTextCharFormat rougeFormat;
    QColor couleurRouge(255, 0, 0); // Rouge
    rougeFormat.setForeground(couleurRouge);

    // Définir le format pour la couleur noire (samedi)
    QTextCharFormat noirFormat;
    QColor couleurNoire(0, 0, 0); // Noir
    noirFormat.setForeground(couleurNoire);



    // Appliquer le format rouge au dimanche et le format noir au samedi pour calendarWidget_3
    ui->calendarWidget_3->setWeekdayTextFormat(Qt::Saturday, noirFormat);
    ui->calendarWidget_3->setWeekdayTextFormat(Qt::Sunday, rougeFormat);


    // Parcourir les dates des séances récupérées et appliquer le format rouge à chaque date valide et noir sinon
    for (int year = ui->calendarWidget_3->minimumDate().year(); year <= ui->calendarWidget_3->maximumDate().year(); ++year) {
        for (int month = 1; month <= 12; ++month) {
            for (int day = 1; day <= QDate(year, month, 1).daysInMonth(); ++day) {
                QDate date(year, month, day);
                if (date.dayOfWeek() == Qt::Sunday || std::find(datesSeances.begin(), datesSeances.end(), date.toString("yyyy-MM-dd")) != datesSeances.end()) {

                    ui->calendarWidget_3->setDateTextFormat(date, rougeFormat);
                } else {

                    ui->calendarWidget_3->setDateTextFormat(date, noirFormat);
                }
            }
        }
    }
}

void MainWindow::on_modifier_calender_sbf_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView_sbf->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, tr("Aucune ligne sélectionnée"),
                             tr("Veuillez sélectionner une ligne à mettre à jour."),
                             QMessageBox::Ok);
        return;
    }

    // Vérifier si une date est sélectionnée dans calendarWidget_3
    if (ui->calendarWidget_3->selectedDate().isNull()) {
        QMessageBox::warning(this, tr("Aucune date sélectionnée"),
                             tr("Veuillez choisir une date."),
                             QMessageBox::Ok);
        return;
    }

    // Mettre à jour le champ de texte de la date avec la nouvelle valeur sélectionnée dans le calendarWidget_3
    QDate selectedDate = ui->calendarWidget_3->selectedDate();
    ui->AName_3_sbf->setText(selectedDate.toString("yyyy-MM-dd"));

    // Vérifier si la date choisie est un dimanche
    if (selectedDate.dayOfWeek() == Qt::Sunday) {
        QMessageBox::information(this, tr("Pas de séances le dimanche"),
                             tr("Les séances ne sont pas planifiées le dimanche."),
                             QMessageBox::Ok);
        return;
    }

    // Le reste du code reste le même que dans la fonction on_garder_date_calender_clicked()
    int id = selectedIndexes.at(0).data().toInt();
    QString acNom=ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 7).data().toString();
        QString mailpatient=ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 5).data().toString();
    ui->AcomboBox_4_sbf->clear();
    ui->AcomboBox_3_sbf->clear();
    ui->AcomboBox_5_sbf->clear();

    Seance Stemp;
    vector<QString> patientNames = Stemp.recuperation_nom_patient();
    for (const QString& patientName : patientNames) {
        ui->AcomboBox_4_sbf->addItem(patientName);
    }
    vector<QString> kineeNames = Stemp.recuperation_nom_kinee();
    for (const QString& kineeName : kineeNames) {
        ui->AcomboBox_3_sbf->addItem(kineeName);
    }
    QMap<QString,QString> activiteNames = Stemp.recuperation_nom_activite(mailpatient);
           for(QMap<QString,QString>::iterator path=activiteNames.begin();path!=activiteNames.end();path++)
           {
               QIcon icon(path.value());
                ui->AcomboBox_5_sbf->setIconSize(QSize(20,20));
               ui->AcomboBox_5_sbf->addItem(icon,path.key(),path.value()); // Ajoute l'image au combobox. Le deuxième paramètre est le texte, laissé vide ici.
                if(acNom==path.key()){
                    ui->AcomboBox_5_sbf->setItemIcon(ui->AcomboBox_5_sbf->currentIndex(),icon);
                    ui->AcomboBox_5_sbf->setCurrentText(path.key());
                }
           }

    ui->AName_2_sbf->setText(QString::number(id));
    ui->AcomboBox_7_sbf->setCurrentText(ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 2).data().toString());
    ui->ADuration_5_sbf->setText(ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 3).data().toString());
    ui->AcomboBox_6_sbf->setCurrentText(ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 4).data().toString());
    ui->AcomboBox_4_sbf->setCurrentText(mailpatient);
    ui->AcomboBox_3_sbf->setCurrentText(ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 6).data().toString());



    ui->stackedWidget->setCurrentWidget(ui->page_sbf);
}

void MainWindow::on_garder_date_calender_sbf_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView_sbf->selectionModel()->selectedRows();
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, tr("Aucune ligne sélectionnée"),
                             tr("Veuillez sélectionner une ligne à mettre à jour."),
                             QMessageBox::Ok);
        return;
    }


    int id = selectedIndexes.at(0).data().toInt();
    QString acNom=ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 7).data().toString();
        QString mailpatient=ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 5).data().toString();
    ui->AcomboBox_4_sbf->clear();
    ui->AcomboBox_3_sbf->clear();
    ui->AcomboBox_5_sbf->clear();


    Seance Stemp;
       vector<QString> patientNames = Stemp.recuperation_nom_patient();
       for (const QString& patientName : patientNames) {
           ui->AcomboBox_4_sbf->addItem(patientName);
       }
       vector<QString> kineeNames = Stemp.recuperation_nom_kinee();
       for (const QString& kineeName : kineeNames) {
           ui->AcomboBox_3_sbf->addItem(kineeName);
       }
       QMap<QString,QString> activiteNames = Stemp.recuperation_nom_activite(mailpatient);
              for(QMap<QString,QString>::iterator path=activiteNames.begin();path!=activiteNames.end();path++)
              {
                  QIcon icon(path.value());
                   ui->AcomboBox_5_sbf->setIconSize(QSize(20,20));
                  ui->AcomboBox_5_sbf->addItem(icon,path.key(),path.value()); // Ajoute l'image au combobox. Le deuxième paramètre est le texte, laissé vide ici.
                   if(acNom==path.key()){
                       ui->AcomboBox_5_sbf->setItemIcon(ui->AcomboBox_5_sbf->currentIndex(),icon);
                       ui->AcomboBox_5_sbf->setCurrentText(path.key());
                   }
              }



    ui->AName_2_sbf->setText(QString::number(id));
    ui->AName_3_sbf->setText(ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 1).data().toString());
    ui->AcomboBox_7_sbf->setCurrentText(ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 2).data().toString());
    ui->ADuration_5_sbf->setText(ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 3).data().toString());
    ui->AcomboBox_6_sbf->setCurrentText(ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 4).data().toString());
    ui->AcomboBox_4_sbf->setCurrentText(mailpatient);
    ui->AcomboBox_3_sbf->setCurrentText(ui->tableView_sbf->model()->index(selectedIndexes.at(0).row(), 6).data().toString());



    ui->stackedWidget->setCurrentWidget(ui->page_sbf);
}





void MainWindow::on_Aemploye_6_sbf_clicked()
{
    kinees_switch();

}

void MainWindow::on_Aemploye_7_sbf_clicked()
{
    kinees_switch();

}

void MainWindow::on_Aemploye_10_sbf_clicked()
{
    kinees_switch();
}

void MainWindow::on_Aemploye_11_sbf_clicked()
{
    kinees_switch();
}

void MainWindow::on_Aemploye_12_sbf_clicked()
{
    kinees_switch();
}

void MainWindow::on_Aemploye_13_sbf_clicked()
{
    kinees_switch();
}

void MainWindow::on_Kappointments_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);
}

void MainWindow::on_Kappointments_3_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);
}

void MainWindow::on_Kappointments_4_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);
}

void MainWindow::on_appointments_dal_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);
}

void MainWindow::on_appointments_4_dal_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);
}

void MainWindow::on_appointments_6_dal_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);
}

void MainWindow::on_Aevent_6_sbf_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->liste_dal);

}

void MainWindow::on_Aevent_7_sbf_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}

void MainWindow::on_Aevent_10_sbf_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}

void MainWindow::on_Aevent_11_sbf_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}

void MainWindow::on_Aevent_12_sbf_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}

void MainWindow::on_Aevent_13_sbf_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}



bool MainWindow::saisirActivity(QString nom,int duree,QString image){
    QRegExp regex("^[a-zA-Z]+$");
    bool test=true;
    if (nom.isEmpty()){
        ui->AErrorName->setText("Veuillez remplir le champ");
        test=false;
    }
    else if(!regex.exactMatch(nom)){
        ui->AErrorName->setText("Uniquement Caractéres");
        test=false;
    }
    else if(!ac.nomUnique(nom)){
        ui->AErrorName->setText("nom doit etre unique");
        test=false;
    }
    else{
        ui->AErrorName->setText("");
    }





    if (duree<=0 || duree>60){
        ui->AErrorDuration->setText("Duree invalide");
        test=false;
    }
    else{
        ui->AErrorDuration->setText("");

    }
    if(image.isEmpty()){
        QMessageBox::critical(nullptr, QObject::tr(" NOT OK"),
                              QObject::tr("ajouter une image.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        test=false;
    }

    return test;
}

bool MainWindow::saisirActivity1(QString nom,int duree){
    int row = ui->AtableView->currentIndex().row();
    QModelIndex index1 = ui->AtableView->model()->index(row, 2);
    QString name = ui->AtableView->model()->data(index1).toString();
    QRegExp regex("^[a-zA-Z]+$");
    bool test=true;
    if (nom.isEmpty()){
        ui->AErrorName_2->setText("Veuillez remplir le champ");
        test=false;
    }

    else if(!regex.exactMatch(nom)){
        ui->AErrorName_2->setText("Uniquement Caractéres");
        test=false;
    }
    else if(nom!=name){
        if(!ac.nomUnique(nom)){
            ui->AErrorName_2->setText("nom doit etre unique");
            test=false;
        }
    }
    else{
        ui->AErrorName_2->setText("");
    }




    if (duree<=0 || duree>60){
        ui->AErrorDuration_2->setText("Duree invalide");
        test=false;
    }
    else{
        ui->AErrorDuration_2->setText("");
    }


    return test;
}


void MainWindow::on_AAdd_6_clicked()
{
    //les equipements
    ui->AcomboBox_2->clear();
    QMap<QString,QString> imagePaths= ac.recuperation();
    for(QMap<QString,QString>::iterator path=imagePaths.begin();path!=imagePaths.end();path++)
    {
        QIcon icon(path.value());
        ui->AcomboBox_2->setIconSize(QSize(48,48));
        ui->AcomboBox_2->addItem(icon, path.key(),path.value()); // Ajoute l'image au combobox. Le deuxième paramètre est le texte, laissé vide ici.

    }


    ui->stackedWidget->setCurrentWidget(ui->Apage_8);
}

void MainWindow::on_Aliste_7_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Apage_7);
}

void MainWindow::on_AAjouter_clicked()
{

    QString nom=ui->AName->text();
    QString type=ui->type_combobox->currentText();
    int duree=ui->ADuration->text().toInt();
    QString degres=ui->AcomboBox->currentText();
    QString equip = ui->AcomboBox_2->currentText();
    qDebug() << equip ;
    QString image=ac.getImage();
    //qDebug() << image ;
    bool saisir=saisirActivity(nom,duree,image);

    if(saisir==true){

        Activity a(0,nom,type,degres,duree,image,equip);
        bool test=a.ajouterActivite();
        if(test){
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("ajout effectue avec succes.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
            ui->AName->setText("");
            ui->ADuration->setText("");

            ui->Aimage->clear();
            ac.afficherActivite(ui->AtableView);
            statistique();

        }
        else {
            QMessageBox::critical(nullptr, QObject::tr(" NOT OK"),
                                  QObject::tr("ajout non effectue.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }

    }
}


void MainWindow::on_ADelete_6_clicked()
{
    // Obtenez l'ID de la ligne sélectionnée. Vous devrez peut-être ajuster cette ligne en fonction de la façon dont votre vue est configurée.
    int row = ui->AtableView->currentIndex().row();
    QModelIndex index = ui->AtableView->model()->index(row, 0); // Remplacez 0 par l'index de la colonne "id".
    int id = ui->AtableView->model()->data(index).toInt();

    bool test=ac.supprimerActivite( id);


    // Exécutez la requête. Si elle réussit, la ligne sera supprimée de la base de données.
    if (!test)
    {
        QMessageBox::critical(nullptr, QObject::tr("OK"),
                              QObject::tr("supp non effectué .\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("suppression effectué .\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ac.afficherActivite(ui->AtableView);
    statistique();

}




void MainWindow::on_AUpdate_6_clicked()
{
    // Obtenir le modèle de données
    QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->AtableView->model());

    QModelIndex index = ui->AtableView->currentIndex();

    ui->AcomboBox_4->clear();

    QMap<QString,QString> imagePaths= ac.recuperation();

    QString tool = model->data(index.sibling(index.row(), 6)).toString();
    for(QMap<QString,QString>::iterator path=imagePaths.begin(); path!=imagePaths.end(); path++)
    {
        QIcon icon(path.value());
        ui->AcomboBox_4->addItem(icon, path.key(),path.value()); // Ajoute l'image au combobox. Le deuxième paramètre est le texte, laissé vide ici.
        if(path.value()==tool){
            ui->AcomboBox_4->setCurrentText(tool);
            ui->AcomboBox_4->setItemIcon(ui->AcomboBox_4->currentIndex(),icon);
        }
    }


    // Obtenir et afficher les valeurs des colonnes
    QString name = model->data(index.sibling(index.row(), 2)).toString();
    ui->AName_2->setText(name);
    QString type = model->data(index.sibling(index.row(), 3)).toString();
    ui->type_combobox_2->setCurrentText(type);
    QString duration = model->data(index.sibling(index.row(), 4)).toString();
    ui->ADuration_2->setText(duration);

    QString degres = model->data(index.sibling(index.row(), 5)).toString();
    ui->AcomboBox_3->setCurrentText(degres);



    QString image = model->data(index.sibling(index.row(), 1)).toString();
    QPixmap image1(image);

    // Ajuster la taille du label en fonction de la taille de l'image
    ui->Aimage_2->setPixmap(image1.scaled(ui->Aimage_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ac.setImage(image);

    ui->stackedWidget->setCurrentWidget(ui->Apage);
}

void MainWindow::on_Aliste_9_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Apage_7);
}

void MainWindow::on_Aadd_3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Apage_8);
}



void MainWindow::on_Amodifier_clicked()
{
    int row = ui->AtableView->currentIndex().row();
    QModelIndex index1 = ui->AtableView->model()->index(row, 0);
    int id = ui->AtableView->model()->data(index1).toInt();

    QString nom=ui->AName_2->text();
    QString type=ui->type_combobox_2->currentText();
    int duree=ui->ADuration_2->text().toInt();
    QString degres=ui->AcomboBox_3->currentText();
    QString equip = ui->AcomboBox_4->currentText();

    bool saisir=saisirActivity1(nom,duree);

    if(saisir==true){

        Activity a(id,nom,type,degres,duree,ac.getImage(),equip);
        bool test=a.UpdateActivite();
        if(test){
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Modification effectue avec succes.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
            ui->AName_2->setText("");
            ui->ADuration_2->setText("");

            ui->Aimage_2->clear();
            ac.afficherActivite(ui->AtableView);
            statistique();
            ui->stackedWidget->setCurrentWidget(ui->Apage_7);
        }


        else {
            QMessageBox::critical(nullptr, QObject::tr(" NOT OK"),
                                  QObject::tr("Modification non effectue.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
    }

}



void MainWindow::on_AimageB_clicked()
{
    // Dans votre fonction d'ajout
    QString cheminImage = QFileDialog::getOpenFileName(this, "Choisir une image", QDir::homePath(), "Images (*.png *.jpg *.jpeg)");

    if (!cheminImage.isEmpty()) {
        QPixmap image(cheminImage);

        // Ajuster la taille du label en fonction de la taille de l'image
        ui->Aimage->setPixmap(image.scaled(ui->Aimage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ac.setImage(cheminImage);
    }


}

void MainWindow::on_AimageB_2_clicked()
{
    // Dans votre fonction d'ajout
    QString cheminImage = QFileDialog::getOpenFileName(this, "Choisir une image", QDir::homePath(), "Images (*.png *.jpg *.jpeg)");

    if (!cheminImage.isEmpty()) {
        QPixmap image(cheminImage);

        // Ajuster la taille du label en fonction de la taille de l'image
        ui->Aimage_2->setPixmap(image.scaled(ui->Aimage_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ac.setImage(cheminImage);
    }
}




void MainWindow::on_Atoggle_clicked()
{
    if (checked) {


        // Rétablir le style par défaut
        ui->centralwidget->setStyleSheet(R"(*{

                                         color:#000;
                                         border:none;
                                         }

                                         #AleftMenu_2,#AleftMenu_3,#AleftMenu{
                                         background-color:#2596be;
                                         border-radius :20px;
                                         }
                                         #centralwidget{
                                         background-color:#eff9fe;
                                         }
                                         QHeaderView::section { background-color: #2596be;
                                         }
                                         QLineEdit{
                                         background:transparent;
                                         }
                                         #ASearchFrame_6,#ASearchFrame_7{
                                         border-radius :10px;
                                         border: 2px solid #2596be;
                                         }
                                         #ATriFrame_6,#ATriFrame_7{
                                         border-radius :10px;
                                         border: 2px solid #2596be;
                                         }
                                         #AAcceuil_6,#AAcceuil_7,#AAcceuil_10{
                                         color:#2596be;
                                         }
                                         #label_4{
                                         color:#2596be;
                                         }
                                         #Aadd,#Aadd_3,#Aliste_9,#AAdd_6{
                                         color:#2596be;
                                         }
                                         #AUpdate_6,#ADelete_6,#APDF_6,#AExel_6,#AStatistics_6{
                                         background-color:#2596be;
                                         color:white;
                                         border-style:outset;
                                         border-radius:10px;
                                         border-color:white;
                                         font:bold;
                                         padding:6px;
                                         min-width:10px;
                                         }
                                         #AUpdate_6:hover,#ADelete_6:hover,#APDF_6:hover,#AExel_6:hover,#AStatistics_6:hover{
                                         background-color:white;
                                         color:#2596be;
                                         border-style:outset;
                                         border-radius:10px;
                                         border-color:white;
                                         font:bold;
                                         padding:6px;
                                         min-width:10px;
                                         }

                                         #Aemploye_6:hover,
                                         #Aappointments_6:hover,
                                         #Aemploye_6:hover,
                                         #Aevent_6:hover,
                                         #Apatient_6:hover,
                                         #Aproducts_6:hover,
                                         #Aprograms_6:hover,
                                         #Aemploye_7:hover,
                                         #Aappointments_7:hover,
                                         #employe_7:hover,
                                         #Aevent_7:hover,
                                         #Apatient_7:hover,
                                         #Aproducts_7:hover,
                                         #Aprograms_7:hover,
                                         #Aemploye_10:hover,
                                         #Aappointments_10:hover,
                                         #Aemploye_10:hover,
                                         #Aevent_10:hover,
                                         #Apatient_10:hover,
                                         #Aproducts_10:hover,
                                         #Aprograms_10:hover

                                         {
                                         background-color: white;
                                         color: #2596be;
                                         border-radius:10px;
                                         border-color:white;

                                         }
                                         #AList_6,#Aadd_1{
                                         color:#2596be;
                                         background-color:white;
                                         }

                                         QTableWidget::item{
                                         background-color:#2596be;
                                         }

                                         #Aemploye_6,#Aappointments_6,#Aemploye_6,#Aevent_6,#Apatient_6,#Aproducts_6,#Aprograms_6,#Aemploye_7,#Aappointments_7,#Aemploye_7,#Aevent_7,#Apatient_7,#Aproducts_7,#Aprograms_7,#Aemploye_10,#Aappointments_10,#Aemploye_10,#Aevent_10,#Apatient_10,#Aproducts_10,#Aprograms_10{
                                         color:white;
                                         }
                                         #Aadd_1,#Aliste_7{
                                         color: #2596be;
                                         }

                                         #Atitrage,#Atitrage_3{
                                         border: 5px solid #2596be;
                                         border-radius: 25px;
                                         }
                                         #AName,#ADuration,#Aimage,#AName_2,#ADuration_2,#Aimage_2{
                                         background-color:white;
                                         border-radius:5px;
                                         border: 2px solid #2596be;

                                         }
                                         #AAjouter,#AimageB,#AimageB_2,#Amodifier{
                                         background-color:#2596be;
                                         color:white;
                                         border-style:outset;
                                         border-radius:10px;
                                         border-color:white;
                                         font:bold;
                                         padding:6px;
                                         min-width:10px;
                                         }
                                         #AAjouter:hover,
                                         #AimageB:hover,
                                         #Amodifier:hover,
                                         #AimageB_3:hover
                                         {
                                         background-color:white;
                                         color:#2596be;
                                         border-style:outset;
                                         border-radius:10px;
                                         border-color:white;
                                         font:bold;
                                         padding:6px;
                                         min-width:10px;

                                         }
                                         #Awidget_34,#Awidget_47{
                                         background-color:#d7dbda;
                                         border-radius :20px;
                                         }
                                         #Atitle,#Atitle_3{
                                         color:#2596be;
                                         }
                                         #AErrorName,#AErrorDuration,#AErrorName_2,#AErrorDuration_2{
                                         font-family: Arial;
                                         font-size: 14px;
                                         color: red;
                                         }
                                         QComboBox{
                                         background-color:white;
                                         border-radius:5px;
                                         border: 2px solid #2596be;
                                         }

                                         #AAdd_6:hover,
                                         #AList_6:hover,
                                         #AAcceuil_6:hover,
                                         #Aliste_7:hover,
                                         #AAcceuil_7:hover,
                                         #Aadd_1:hover,
                                         #Aadd_3:hover,
                                         #AAcceuil_10:hover,
                                         #Aliste_9:hover
                                         {
                                         background-color:white;
                                         }


                                         )");
        //ui->centralwidget->setStyleSheet("background-color:#eff9fe;");
        ui->Atoggle->setText("light Mode");
        checked= false;
    }
    else {


        // Appliquer le style sombre

        ui->centralwidget->setStyleSheet(R"(
                                         *{

                                         color:#000;
                                         border:none;
                                         }

                                         #AleftMenu_2,#AleftMenu_3,#AleftMenu{
                                        background-color: #0A346A;
                                         border-radius :20px;
                                         }


                                         QLineEdit{
                                         background:transparent;
                                         }
                                         #ASearchFrame_6,#ASearchFrame_7{
                                         border-radius :10px;
                                         border: 2px solid #2596be;
                                         }
                                         #ATriFrame_6,#ATriFrame_7{
                                         border-radius :10px;
                                         border: 2px solid #2596be;
                                         }
                                         #AAcceuil_6,#AAcceuil_7,#AAcceuil_10{
                                         color:white;
                                         }
                                         #label_4{
                                         color:#2596be;
                                         }
                                         #Aadd,#Aadd_3,#Aliste_9,#AAdd_6{
                                         color:white;
                                         }
                                         #AUpdate_6,#ADelete_6,#APDF_6,#AExel_6,#AStatistics_6{
                                         background-color:#2596be;
                                         color:white;
                                         border-style:outset;
                                         border-radius:10px;
                                         border-color:white;
                                         font:bold;
                                         padding:6px;
                                         min-width:10px;
                                         }
                                         #AUpdate_6:hover,#ADelete_6:hover,#APDF_6:hover,#AExel_6:hover,#AStatistics_6:hover{
                                         background-color:white;
                                         color:#2596be;
                                         border-style:outset;
                                         border-radius:10px;
                                         border-color:white;
                                         font:bold;
                                         padding:6px;
                                         min-width:10px;
                                         }

                                         #Aemploye_6:hover,
                                         #Aappointments_6:hover,
                                         #Aemploye_6:hover,
                                         #Aevent_6:hover,
                                         #Apatient_6:hover,
                                         #Aproducts_6:hover,
                                         #Aprograms_6:hover,
                                         #Aemploye_7:hover,
                                         #Aappointments_7:hover,
                                         #employe_7:hover,
                                         #Aevent_7:hover,
                                         #Apatient_7:hover,
                                         #Aproducts_7:hover,
                                         #Aprograms_7:hover,
                                         #Aemploye_10:hover,
                                         #Aappointments_10:hover,
                                         #Aemploye_10:hover,
                                         #Aevent_10:hover,
                                         #Apatient_10:hover,
                                         #Aproducts_10:hover,
                                         #Aprograms_10:hover

                                         {
                                         background-color: white;
                                         color: #2596be;
                                         border-radius:10px;
                                         border-color:white;

                                         }
                                         #AList_6,#Aadd_1{
                                         color:#2596be;
                                         background-color:white;
                                         }

                                         QTableWidget::item{
                                         background-color:#2596be;
                                         }
                                         #label_17,#label_20,#Alabel_40
                                         {
                                         color:white;
                                         }

                                         #Aemploye_6,#Aappointments_6,#Aemploye_6,#Aevent_6,#Apatient_6,#Aproducts_6,#Aprograms_6,#Aemploye_7,#Aappointments_7,#Aemploye_7,#Aevent_7,#Apatient_7,#Aproducts_7,#Aprograms_7,#Aemploye_10,#Aappointments_10,#Aemploye_10,#Aevent_10,#Apatient_10,#Aproducts_10,#Aprograms_10{
                                         color:white;
                                         }
                                         #Aadd_1,#Aliste_7{
                                         color: white;
                                         }

                                         #Atitrage,#Atitrage_3{
                                         border: 5px solid #2596be;
                                         border-radius: 25px;
                                         }
                                         #AName,#ADuration,#Aimage,#AName_2,#ADuration_2,#Aimage_2{
                                         background-color:white;
                                         border-radius:5px;
                                         border: 2px solid #2596be;

                                         }
                                         #AAjouter,#AimageB,#AimageB_2,#Amodifier{
                                         background-color:#2596be;
                                         color:white;
                                         border-style:outset;
                                         border-radius:10px;
                                         border-color:white;
                                         font:bold;
                                         padding:6px;
                                         min-width:10px;
                                         }
                                         #AAjouter:hover,
                                         #AimageB:hover,
                                         #Amodifier:hover,
                                         #AimageB_3:hover
                                         {
                                         background-color:white;
                                         color:#2596be;
                                         border-style:outset;
                                         border-radius:10px;
                                         border-color:white;
                                         font:bold;
                                         padding:6px;
                                         min-width:10px;

                                         }
                                         #Awidget_34,#Awidget_47{
                                         background-color:#d7dbda;
                                         border-radius :20px;
                                         }
                                         #Atitle,#Atitle_3{
                                         color:#2596be;
                                         }
                                         #AErrorName,#AErrorDuration,#AErrorName_2,#AErrorDuration_2{
                                         font-family: Arial;
                                         font-size: 14px;
                                         color: red;
                                         }
                                         QComboBox{
                                         background-color:white;
                                         border-radius:5px;
                                         border: 2px solid #2596be;
                                         }

                                         #AAdd_6:hover,
                                         #AList_6:hover,
                                         #AAcceuil_6:hover,
                                         #Aliste_7:hover,
                                         #AAcceuil_7:hover,
                                         #Aadd_1:hover,
                                         #Aadd_3:hover,
                                         #AAcceuil_10:hover,
                                         #Aliste_9:hover
                                         {
                                         background-color:white;
                                         }
                                         #mainBody,#mainBody_2,#mainBody_3{
                                              background-color: #0A346A; /* Noir */}


                                         })");






        ui->Atoggle->setText("Désactiver Mode Sombre");
        checked = true;
    }
    qApp->processEvents();
}

void MainWindow::statistique() {
    QSqlQuery query;

    if (query.exec("SELECT degres, type_activity, COUNT(*) AS nombre_activites FROM activity GROUP BY degres, type_activity")) {
        // Initialisation des sets pour chaque niveau de compétence
        QBarSet *setDebutant = new QBarSet("Débutant");
        setDebutant->append(QList<double>() << 0 << 0 << 0);
        QBarSet *setIntermediaire = new QBarSet("Intermédiaire");
        setIntermediaire->append(QList<double>() << 0 << 0 << 0);
        QBarSet *setAvance = new QBarSet("Avancé");
        setAvance->append(QList<double>() << 0 << 0 << 0);

        QSqlRecord record = query.record();
        int degreeIndex = record.indexOf("degres");
        int typeIndex = record.indexOf("type_activity");
        int countIndex = record.indexOf("nombre_activites");

        while (query.next()) {
            QString degree = query.value(degreeIndex).toString();
            QString type = query.value(typeIndex).toString();
            int count = query.value(countIndex).toInt();

            // Ajout des valeurs à l'ensemble de barres approprié
            if (type == "Renforcement") {
                if (degree == "Beginner")
                    setDebutant->replace(0,count);
                else if (degree == "Intermediate")
                    setIntermediaire ->replace(0,count);
                else if (degree == "Advanced")
                    setAvance ->replace(0,count);
            }  else if (type == "Etirement") {
                if (degree == "Beginner")
                    setDebutant ->replace(1,count);
                else if (degree == "Intermediate")
                    setIntermediaire ->replace(1,count);
                else if (degree == "Advanced")
                    setAvance ->replace(1,count);
            }  else if (type == "Equilibre") {
                if (degree == "Beginner")
                    setDebutant ->replace(2,count);
                else if (degree == "Intermediate")
                    setIntermediaire ->replace(2,count);
                else if (degree == "Advanced")
                    setAvance ->replace(2,count);
            }
        }

        // Création du diagramme à barres
        QChart *chart = new QChart();
        chart->setTitle("Statistiques des activités par degré et type");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // Création des séries de barres
        QBarSeries *series = new QBarSeries();
        series->append(setDebutant);
        series->append(setIntermediaire);
        series->append(setAvance);

        chart->addSeries(series);

        // Configuration de l'axe X (types d'activité)
        QStringList categories;
        categories << "Renforcement" << "Etirement" << "Equilibre";
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);

        // Configuration de l'axe Y (nombre d'activités)
        QValueAxis *axisY = new QValueAxis();
        chart->addAxis(axisY, Qt::AlignLeft);

        // Attacher les axes à la série de barres
        series->attachAxis(axisY);

        // Ajout de la série de barres au diagramme

        // Nettoyer l'ancien widget de diagramme s'il existe
        if (ChartView_amen) {
            delete ChartView_amen;
        }

        // Création d'une vue de diagramme pour afficher le graphique
        ChartView_amen = new QChartView(chart);

        // Ajout du diagramme à la fenêtre principale
        ui->Awidget_2->setLayout(new QVBoxLayout());
        ui->Awidget_2->layout()->addWidget(ChartView_amen);
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête des statistiques";
    }
}




void MainWindow::on_ALineSearch_6_textChanged(const QString &arg1)
{
    ac.rechercheAc(ui->AtableView,arg1);
}

void MainWindow::on_AExel_7_clicked()
{
    Dialogk d;
    d.exec();

}






void MainWindow::on_AcomboBox_2_sbf_currentIndexChanged(const QString &arg1)
{
    ui->type_combobox_sbf->clear();
    QMap<QString,QString> activiteNames = Stemp.recuperation_nom_activite(arg1);
    for(QMap<QString,QString>::iterator path=activiteNames.begin();path!=activiteNames.end();path++)
    {
        QIcon icon(path.value());
         ui->type_combobox_sbf->setIconSize(QSize(48,48));
        ui->type_combobox_sbf->addItem(icon,path.key(),path.value()); // Ajoute l'image au combobox. Le deuxième paramètre est le texte, laissé vide ici.

    }
}

void MainWindow::on_AcomboBox_4_sbf_currentIndexChanged(const QString &arg1)
{
    ui->AcomboBox_5_sbf->clear();
    QMap<QString,QString> activiteNames = Stemp.recuperation_nom_activite(arg1);
    for(QMap<QString,QString>::iterator path=activiteNames.begin();path!=activiteNames.end();path++)
    {
        QIcon icon(path.value());
         ui->AcomboBox_5_sbf->setIconSize(QSize(48,48));
        ui->AcomboBox_5_sbf->addItem(icon,path.key(),path.value()); // Ajoute l'image au combobox. Le deuxième paramètre est le texte, laissé vide ici.

    }

}

void MainWindow::on_Aemploye_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void MainWindow::on_Aappointments_6_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);
}


void MainWindow::on_Aevent_6_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}

void MainWindow::on_Aproducts_6_clicked()
{

}

void MainWindow::on_Apatient_6_clicked()
{

}

void MainWindow::on_Aemploye_7_clicked()
{
    on_employe_6_dal_clicked();
}


void MainWindow::on_Apatient_7_clicked()
{

}

void MainWindow::on_Aappointments_7_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);
}

void MainWindow::on_Aproducts_7_clicked()
{

}

void MainWindow::on_Aevent_7_clicked()
{
      ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}

void MainWindow::on_Aemploye_10_clicked()
{
    on_employe_6_dal_clicked();
}


void MainWindow::on_Apatient_10_clicked()
{

}

void MainWindow::on_Aappointments_10_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_7_sbf);
}

void MainWindow::on_Aproducts_10_clicked()
{

}

void MainWindow::on_Aevent_10_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->liste_dal);
}

void MainWindow::on_Kprograms_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->Apage_7);
}


void MainWindow::on_Kprograms_3_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->Apage_7);
}


void MainWindow::on_Kprograms_4_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->Apage_7);
}

void MainWindow::on_programs_dal_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Apage_7);
}

void MainWindow::on_programs_4_dal_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->Apage_7);
}


void MainWindow::on_programs_6_dal_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->Apage_7);
}

void MainWindow::on_Aprograms_6_sbf_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->Apage_7);
}


void MainWindow::on_Aprograms_7_sbf_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->Apage_7);
}


void MainWindow::on_Aprograms_10_sbf_clicked()
{
     ui->stackedWidget->setCurrentWidget(ui->Apage_7);
}
