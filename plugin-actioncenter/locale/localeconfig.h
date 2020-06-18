#ifndef LOCALECONFIG_H
#define LOCALECONFIG_H

#include <QObject>
#include <QSettings>
#include <QComboBox>
#include <QFile>
#include <QDebug>
#include <QString>

class localeConfig: public QObject
{
    Q_OBJECT
public:
    explicit localeConfig(QList<QComboBox * > comboxs,QObject *parent = nullptr);
public slots:
    void saveSettings();
    void loadSettings();
    void updateSettings(QList<QComboBox* > combox);
    void resetSettings();
    bool isCreated();

signals:
private:
    QSettings * settings;
    QList<QComboBox * > list_combos;

};

#endif // LOCALECONFIG_H
