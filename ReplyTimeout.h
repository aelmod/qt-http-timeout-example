#ifndef REPLYTIMEOUT_H
#define REPLYTIMEOUT_H

#include <QBasicTimer>
#include <QNetworkReply>
#include <QObject>
#include <QTimerEvent>

class ReplyTimeout : public QObject {
  Q_OBJECT
private:
  QBasicTimer timer;
public:
  ReplyTimeout(QNetworkReply* reply, const int timeout);
protected:
  void timerEvent(QTimerEvent * ev);
signals:
  void timeout();
};

#endif // REPLYTIMEOUT_H
