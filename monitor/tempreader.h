#ifndef TEMPREADER_H
#define TEMPREADER_H


#include <QObject>
#include <string>
#include <map>
#include <QDateTime>
#include <thread>

#include <boost/asio.hpp>


class TempReader final : public QObject {
    Q_OBJECT

public:
    TempReader(std::string_view portName);
    TempReader(const TempReader &other) = delete;
    TempReader(TempReader &&other) = delete;
    ~TempReader();

    TempReader &operator=(const TempReader &other) = delete;
    TempReader &operator=(TempReader &&other) = delete;

    void start();
    void stop();

    std::pair<QDateTime, float> getLastValue();
    std::map<QDateTime, float> getBuffer();

private:
    bool threadFlag = false;
    std::thread thread;
    void threadFunc(bool &threadFlag);

    boost::asio::io_context io;
    boost::asio::serial_port port;

    std::map<QDateTime, float> buffer;

signals:
    void updateInfo(QDateTime dateTime, float temp);
};


#endif // TEMPREADER_H
