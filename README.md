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
