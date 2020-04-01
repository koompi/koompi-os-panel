#ifndef BLUETOOTHUI_H
#define BLUETOOTHUI_H

#include "bluetoothitem.h"
#include "bluetoothservice.h"
#include <QtBluetooth/QBluetoothDeviceInfo>
#include <QtBluetooth/QBluetoothLocalDevice>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
class bluetoothui : public QWidget {
  Q_OBJECT
public:
  explicit bluetoothui(QWidget *parent = nullptr);
  void setupUi(QWidget *FormBluetooth);
  void retranslateUi(QWidget *FormBluetooth);
public Q_SLOTS:
  void onShowBluetoothItem(const QBluetoothDeviceInfo &blueName);
private slots:
  void slotOncheckbluetooth(bool state);
  void slotOnrefreshblutooth();

private:
  void init();
  void initAction();

private:
  QVBoxLayout *verticalLayout;
  QStackedWidget *bluetoothStack;
  QWidget *bluetoothPageOne;
  QWidget *layoutWidget;
  QVBoxLayout *firstBlueLayout;
  QLabel *topTitleBluetooth;
  QToolButton *enableBluetoothBtn;
  QWidget *bluetoothPageTwo;
  QListWidget *listWidget;
  QWidget *layoutWidget1;
  QHBoxLayout *layoutTop;
  QCheckBox *checkBox;
  QHBoxLayout *layoutRight;
  QToolButton *refreshBluetooth;
  QToolButton *bluetoothSetting;
  QLabel *availableTitle;
  QLabel *bluetoothTitle;
  QToolButton *bluetoothBack;
  bluetoothservice *bluetoothService = nullptr;
  bluetoothitem *bluetoothItem;
  QMovie *loadingAnimation;
  QBluetoothLocalDevice m_localDevice;

signals:
  void notifyEnableBluetoothClicked();
};

#endif // BLUETOOTHUI_H
