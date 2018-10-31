#include "ReplyTimeout.h"

ReplyTimeout::ReplyTimeout(QNetworkReply *reply, const int timeout) : QObject(reply) {
    Q_ASSERT(reply);
    if (reply && reply->isRunning())
        timer.start(timeout, this);

    connect(reply, &QNetworkReply::finished, this, [&](){ timer.stop(); });
}

void ReplyTimeout::timerEvent(QTimerEvent *ev) {
    if (!timer.isActive() || ev->timerId() != timer.timerId())
        return;

    emit timeout();

    auto reply = static_cast<QNetworkReply*>(parent());
    if (reply->isRunning())
        reply->close();
    timer.stop();
}
