#include "mainwindow.h"
#include <KWindowSystem>
#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QGuiApplication>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScreen>
#include <QSpacerItem>
#include <QTime>
#include <QtNetwork/QNetworkConfiguration>
#include <QtNetwork/QNetworkConfigurationManager>
#define WID_WIDTH 32
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  wifi = new wifiapplet(this);
  QScreen *screen = QGuiApplication::primaryScreen();
  //  setScreen(screen->geometry());
  setFixedSize(QSize(screen->geometry().width(), WID_WIDTH));
  qDebug() << layout() << endl;
  setStrut();
  // declare variable
  QWidget *mainWidget = new QWidget;
  QTimer *time = new QTimer(this);
  connect(time, &QTimer::timeout, this, &MainWindow::timefunction);
  time->start(60000);
  setCentralWidget(mainWidget);
  QToolButton *startMenuBtn = new QToolButton(this);
  QToolButton *wifiBtn = new QToolButton(this);
  QToolButton *batterBtn = new QToolButton(this);
  soundBtn = new QToolButton(this);
  panelDate = new QLabel(this);
  QToolButton *actionCenter = new QToolButton(this);
  QHBoxLayout *panelLayout = new QHBoxLayout(mainWidget);
  //    QLabel * panelDate = new QLabel(this);
  startMenuBtn->resize(24, 24);
  startMenuBtn->setIcon(QIcon::fromTheme("breeze-settings"));
  startMenuBtn->autoRaise();
  startMenuBtn->setPopupMode(QToolButton::ToolButtonPopupMode::DelayedPopup);
  startMenuBtn->setIconSize(QSize(24, 24));
  wifiBtn->setIconSize(QSize(24, 24));
  batterBtn->setIconSize(QSize(24, 24));
  soundBtn->setIconSize(QSize(24, 24));
  actionCenter->setIconSize(QSize(24, 24));
  startMenuBtn->move(4, 2);
  // Datatime setup
  // hello world my name is Ma Veasna
  // time
  panelDate->setText(QTime::currentTime().toString("hh:mm"));
  mainWidget->setLayout(panelLayout);
  panelLayout->addWidget(startMenuBtn);
  panelLayout->addStretch(1000);
  panelLayout->addWidget(setPanelButton(wifiBtn, "network-wireless-acquiring"));
  panelLayout->addWidget(setPanelButton(batterBtn, "battery-100"));
  panelLayout->addWidget(setPanelButton(soundBtn, "audio-volume-high"));
  panelLayout->addWidget(panelDate);
  panelLayout->addWidget(setPanelButton(actionCenter, "systemsettings"));
  //  connect(startMenuBtn, &QToolButton::clicked, [&]() { QApplication::quit();
  //  });
  connect(startMenuBtn, &QPushButton::clicked, this,
          &MainWindow::showStartMenu);
  connect(batterBtn, &QToolButton::clicked, []() { QApplication::exit(); });

  connect(wifiBtn, &QToolButton::clicked, wifi, &wifiapplet::showWifiList);

  connect(soundBtn, &QToolButton::clicked, this, &MainWindow::showSoundPopup);
}

MainWindow::~MainWindow() {}
// below is used to set a preserved space for the window panel. ex. width of the
// panel
void MainWindow::setStrut() {
  try {

    if (KWindowSystem::isPlatformWayland()) {
      throw QString("Your platform is not supported");
    }
    move(0, 0);
    KWindowSystem::setType(this->winId(), NET::Dock);
    WId wid = effectiveWinId();
    // this function is used to allocate preserving space which is strut for
    // taskbar
    KWindowSystem::setExtendedStrut(wid, 0, 0, 0, 0, 0, 0, WID_WIDTH, 0, 0, 0,
                                    0, 0);
    qDebug() << "set up sucessfully" << endl;

  } catch (QString &error) {
    qDebug() << error << endl;
  }
}

QToolButton *MainWindow::setPanelButton(QToolButton *trayButton,
                                        const QString &icon) {
  trayButton->setIcon(QIcon::fromTheme(icon));
  trayButton->resize(24, 24);
  trayButton->setStyleSheet("border: 0px;");
  return trayButton;
}

bool MainWindow::showStartMenu() {
  QProcess startMenu;
  startMenu.setProgram("qml-launcher");
  startMenu.startDetached();
  startMenu.waitForFinished(-1);
  startMenu.close();
  qInfo() << "Start Menu closed" << endl;
  return true;
}

void MainWindow::timefunction() {
  QTime time = QTime::currentTime();
  qInfo() << time << endl;
  QString time_text = time.toString("hh:mm");
  panelDate->setText(time_text);
}

void MainWindow::setTime(QString value) { panelDate->setText(value); }

void MainWindow::showSoundPopup() {
  if (!sound) {
    sound = new soundapplet(this);
  }
  QRect screen1 = QGuiApplication::primaryScreen()->geometry();
  qDebug() << sound->width();
  int perfectSize = screen1.width() - sound->width();
  sound->move(perfectSize, WID_WIDTH + 2);
  sound->show();
  this->activateWindow();
}

bool MainWindow::event(QEvent *event) {
  this->activateWindow();
  if (event->type() == QEvent::ToolTip) {
    qDebug() << "you hover on widget";
  }
  return QWidget::event(event);
}