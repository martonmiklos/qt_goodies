#include "mainwindowwithrecentlist.h"

#include <QDebug>
#include <QFileInfo>

MainWindowWithRecentList::MainWindowWithRecentList(QWidget *parent, Qt::WindowFlags flags) :
    QMainWindow(parent, flags),
    m_recentKey("recentFiles"),
    m_recentMenu(nullptr),
    m_recentListSize(10)
{
}

QString MainWindowWithRecentList::recentKey() const
{
    return m_recentKey;
}

void MainWindowWithRecentList::setRecentKey(const QString &recentKey)
{
    m_recentKey = recentKey;
}

void MainWindowWithRecentList::addRecentFileAction(const QString &fileName)
{
    QAction *action = m_recentMenu->addAction(fileName);
    connect(action, &QAction::triggered, this, [this, fileName]() {this->openFile(fileName);});
    m_recentActions << action;
}

int MainWindowWithRecentList::recentListSize() const
{
    return m_recentListSize;
}

void MainWindowWithRecentList::setRecentListSize(int recentListSize)
{
    m_recentListSize = recentListSize;
}

void MainWindowWithRecentList::loadRecentFiles(QMenu *menu)
{
    m_recentMenu = menu;

    // reinit
    m_recentMenu->clear();
    m_recentActions.clear();

    QStringList recentList;
    int count = m_settings.beginReadArray("recentFiles");
    for (int i = 0; i<count; i++) {
        m_settings.setArrayIndex(i);

        QString fn = m_settings.value("path").toString();
        QFileInfo fi(fn);
        if (fi.isReadable()) {
            addRecentFileAction(fn);
            recentList << fn;
        }
    }
    m_settings.endArray();

    recentList = recentList.mid(0, m_recentListSize);

    // rewrite the array because we have removed the unreadable files
    m_settings.beginWriteArray("recentFiles");
    int i = 0;
    foreach (QString fn, recentList) {
        m_settings.setArrayIndex(i);
        m_settings.setValue("path", fn);
        i++;
    }
    m_settings.endArray();
}

void MainWindowWithRecentList::addFilesToRecentList(const QStringList &fileNames)
{
    foreach (QString fn, fileNames) {
        addFileToRecentList(fn);
    }
}

void MainWindowWithRecentList::addFileToRecentList(const QString &fileName)
{
    if (m_recentMenu == nullptr) {
        qDebug() << "loadRecentFiles have not been called yet";
        return;
    }

    while (m_recentActions.size()) {
        QAction *action = m_recentActions.takeFirst();
        m_recentMenu->removeAction(action);
        action->deleteLater();
    }

    QStringList recentList;

    // put the new file at the beginning of the list
    recentList << fileName;

    int count = m_settings.beginReadArray("recentFiles");
    for (int i = 0; i<count; i++) {
        m_settings.setArrayIndex(i);
        QString fn = m_settings.value("path").toString();
        QFileInfo fi(fn);
        if (fi.isReadable() && fn != fileName) {
            recentList << m_settings.value("path").toString();
        }
    }
    m_settings.endArray();

    recentList = recentList.mid(0, m_recentListSize);

    // rewrite the array with the new file at the beginning
    m_settings.beginWriteArray("recentFiles");
    int i = 0;
    foreach (QString fn, recentList) {
        addRecentFileAction(fn);
        m_settings.setArrayIndex(i);
        m_settings.setValue("path", fn);
        i++;
    }
    m_settings.endArray();
}
