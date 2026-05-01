#ifndef MAINWINDOWWITHRECENTLIST_H
#define MAINWINDOWWITHRECENTLIST_H

#include <QMainWindow>
#include <QMenu>
#include <QSettings>
#include <QSignalMapper>

class MainWindowWithRecentList : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindowWithRecentList(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    int recentListSize() const;
    void setRecentListSize(int recentListSize);

public slots:
    virtual bool openFile(const QString & fileName) = 0;

protected:
    QString recentKey() const;
    void setRecentKey(const QString &recentKey);

    void loadRecentFiles(QMenu *menu);
    void addFileToRecentList(const QString & fileName);
    void addFilesToRecentList(const QStringList & fileNames);

    QSettings m_settings;

private:
    void addRecentFileAction(const QString &fileName);

    QString m_recentKey;
    QList<QAction*> m_recentActions;
    QMenu *m_recentMenu;

    int m_recentListSize;
};

#endif // MAINWINDOWWITHRECENTLIST_H
