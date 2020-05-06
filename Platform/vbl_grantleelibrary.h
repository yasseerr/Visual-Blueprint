/***************************************************************************
 *                                                                         *
 *   Copyright (C) 2020                                                  *
 *                                                                         *
 *   Authors:  Yasser Grimes                                               *
 *   Develeped as a Graduation Project                                     *
 *   School: National School of Computer Science Sidi-Bel-Abbes Algeria    *
 *   Supervisor: Bendaoud Faysal                                           *
 ***************************************************************************/
#ifndef VBL_GRANTLEELIBRARY_H
#define VBL_GRANTLEELIBRARY_H

#include <QDebug>
#include <QObject>
#include <QStringLiteral>

#include <grantlee/taglibraryinterface.h>

#include <Platform/Python/renderimportfilter.h>


class VBL_GrantLeeLibrary : public QObject,public Grantlee::TagLibraryInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.vbl.vbl_library")
    Q_INTERFACES(Grantlee::TagLibraryInterface)
    //QHash<QString, Grantlee::Filter *> m_filters;
public:
     VBL_GrantLeeLibrary(QObject *parent = nullptr) : QObject(parent)
    {

        //m_filters.insert("renderImport",new RenderImportFilter());
    }

    // TagLibraryInterface interface
public:
    virtual QHash<QString, Grantlee::AbstractNodeFactory *> nodeFactories(const QString &name) override
    {
        Q_UNUSED(name);
        QHash<QString, Grantlee::AbstractNodeFactory *> nodeFactories;
        return nodeFactories;
    }
    virtual QHash<QString, Grantlee::Filter *> filters(const QString &name) override
    {
        Q_UNUSED(name);
        QHash<QString, Grantlee::Filter *> m_filters;
        m_filters.insert(QStringLiteral("renderImport"),new RenderImportFilter());
        m_filters.insert(QStringLiteral("renderParameter"),new RenderParameterFilter());
        m_filters.insert(QStringLiteral("indentString"),new IndentFilter());
        qDebug() << "filter requested";
        return m_filters;
    }
};

#endif // VBL_GRANTLEELIBRARY_H
