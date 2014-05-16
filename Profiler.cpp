#include "Profiler.h"
#include "UVEditeur.h"
#include "UTProfiler.h"
#include "CursusEditeur.h"
#include "Cursus.h"
#include "UVCreateur.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>

Profiler::Profiler(QWidget *parent):QMainWindow(parent){
    setMinimumSize(300,300);
    setWindowTitle("UT-Profiler");
    QMenu* mFichier = menuBar()->addMenu("&Fichier");
    QMenu* mCharger=mFichier->addMenu("&Charger");

    QAction *actionChargerUV=mCharger->addAction("Catalogue UVs");
    QAction *actionChargerCursus=mCharger->addAction("Catalogue Cursus");
    mFichier->addSeparator();

    QAction *actionQuitter = mFichier->addAction("&Quitter");
    QMenu* mEdition = menuBar()->addMenu("&Edition");
    QAction* actionUV=mEdition->addAction("&UV");
    QAction* actionCursus=mEdition->addAction("&Cursus");
    QAction* actionUV2=mEdition->addAction("&Ajout UV");

    // connections
    connect(actionChargerUV, SIGNAL(triggered()),this,SLOT(openChargerUV()));
    connect(actionChargerCursus, SIGNAL(triggered()),this,SLOT(openChargerCursus()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionUV, SIGNAL(triggered()),this,SLOT(openUV()));
    connect(actionCursus, SIGNAL(triggered()),this,SLOT(openCursus()));
    connect(actionUV2, SIGNAL(triggered()),this, SLOT(nouvelleUV()));
}

void Profiler::openChargerUV(){
    QString chemin = QFileDialog::getOpenFileName();
    try {
        if (chemin!="")UVManager::getInstance().load(chemin);
        QMessageBox::information(this, "Chargement Catalogue", "Le catalogue d’UVs a été chargé.");
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Chargement Catalogue", "Erreur lors du chargement du fichier (non valide ?)");
    }
}

void Profiler::openChargerCursus(){
    QString chemin = QFileDialog::getOpenFileName();
    try {
        if (chemin!="")CursusManager::getInstance().load(chemin);
        QMessageBox::information(this, "Chargement Catalogue", "Le catalogue de Cursus a été chargé.");
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Chargement Catalogue", "Erreur lors du chargement du fichier (non valide ?)");
    }
}

void Profiler::openCursus(){
    QString code=QInputDialog::getText(this,"Entrez le code du Cursus à éditer","Cursus");
    if (code!="")
    try {
        Cursus& cur=CursusManager::getInstance().getCursus(code);
        CursusEditeur* fenetre=new CursusEditeur(cur,this);
        setCentralWidget(fenetre);
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Edition Cursus", QString("Erreur : le Cursus ")+code+" n’existe pas.");
    }
}

void Profiler::openUV(){
    QString code=QInputDialog::getText(this,"Entrez le code de l'UV' à éditer","UV");
    if (code!="")
    try {
        UV& uv=UVManager::getInstance().getUV(code);
        UVEditeur* fenetre=new UVEditeur(uv,this);
        setCentralWidget(fenetre);
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Edition UV", QString("Erreur : l’UV ")+code+" n’existe pas.");
    }
}

void Profiler::nouvelleUV(){
    QString code="";
    try {
        UV& uv=UVManager::getInstance().creatUV();
        UVCreateur* fenetre=new UVCreateur(uv,this);
        setCentralWidget(fenetre);
    }catch(UTProfilerException& e){
        QMessageBox::warning(this, "Ajout UV", QString("Impossible de créer une UV"));

}
}



