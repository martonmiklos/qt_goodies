# Qt goodies

Some common code what I use across my Qt based projects

## Duration formatter

Format duration numbers to "01:56:42.112" or "1 day 12 hours 3 minutes" strings.

## QMetaEnumComboBox

Wanna select an enum item from a QComboBox? QMetaEnumComboBox to the rescue!

![QMetaEnumComboBox in action](https://raw.githubusercontent.com/martonmiklos/qt_goodies/master/images/qmetaenumcombobox_example.png)

A comfortable constructor is added to being able to trim prefix an trailing strings easily.


## QMetaEnumMenu

This template provides similar functionality to the QMetaEnumComboBox just with QMenu: it populates the menu with checkable QActions which acts as radio buttons (only one could be selected).


## widgetactions (SpinBox,LineEdit,PushButtonAction)

Widgets which could be added as a QAction to menus

## restorable_header_widget

A template class for creating widgets having QHeaderView (QTableView, QTreeView) which has:

* Saveable/restorable: 
  * Column widths
  * Column visibility
  * Column order (drag 'n drop)
  
![RestorableHeaderWidget in action](https://raw.githubusercontent.com/martonmiklos/qt_goodies/master/images/restorable_header_widget.png)

![RestorableHeaderWidget drag 'n drop in action](https://raw.githubusercontent.com/martonmiklos/qt_goodies/master/images/restorable_header_widget_drag_n_drop.png)

## Inflector
Helping class to lowerFirst,upperFirst, de_underscore and humanize QStrings. 
Inspired by the [CakePHP's Inflector](https://book.cakephp.org/3/en/core-libraries/inflector.html)
