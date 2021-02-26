#pragma once

#include <QObject>

template <typename T>

class QObjectSingleton : public QObject
{
public:
   QObjectSingleton(QObject *parent = nullptr) :
       QObject(parent)
   {

   }

  static T* instance(QObject *parent = nullptr)
  {
      static T * m_instance = nullptr;
      if (!m_instance)
          m_instance = new T(parent);
      return m_instance;
  }
};
