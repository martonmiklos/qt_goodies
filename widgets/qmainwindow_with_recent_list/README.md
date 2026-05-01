This class is derived from the QMainWindow and provides easy method for storing/loading the recently opened files through the QSettings class.

# Usage:

Include the pri file in your project:
```
include(qmainwindow_with_recent_list/qmainwindow_with_recent_list.pri)
```

Subclass your main window from the MainWindowWithRecentList:

```
class MainWindow : public MainWindowWithRecentList
```

Create a QMenu for your recent files in your menu bar, and call the loadRecentFiles method: 
```
loadRecentFiles(ui->menuRecent_files);
```

Reimplement the openFile method, and call the addFileToRecentList if your open operation was successful.

```
bool MainWindow::openFile(const QString &fileName) 
{
    ....
    addFileToRecentList(fileName);
    ....
    return true;
}
```
