/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#include "bp_platformmanager.h"

#include <QApplication>
#include <QDebug>

BP_PlatformManager::BP_PlatformManager(QObject *parent) : QObject(parent)
{
    QCoreApplication::addLibraryPath(QApplication::applicationDirPath()+"/grantlee/5.2");
    grantleeEngine = new Grantlee::Engine(this);
    grantleeEngine->addDefaultLibrary("grantlee_VBL_plugin");
    //grantleeEngine->loadLibrary("vbl_plugin");
    //grantleeEngine->addPluginPath(QApplication::applicationDirPath()+"/grantlee/5.2");
    auto loader = QSharedPointer<Grantlee::FileSystemTemplateLoader>::create();
    loader->setTemplateDirs(QStringList{QApplication::applicationDirPath()+"/templates",QApplication::applicationDirPath()+"/Platform"});
    //auto t = grantleEngin->newTemplate("my name is as usual {{ name }}","template1");
    grantleeEngine->addTemplateLoader(loader);
    auto t = grantleeEngine->loadByName("template1.txt");
    QVariantHash mapping ;
    mapping.insert("name","visual blueprint");
    Grantlee::Context c(mapping);
    qDebug() <<"template" << t->render(&c);

}


