#include "tempreader.h"

#include "json.h"


using namespace boost::asio;
using json = nlohmann::json;


TempReader::TempReader(std::string_view portName)
: io(io_context())
, port(io, std::string(portName)) {
    port.set_option(serial_port_base::baud_rate(9600));
    port.set_option(serial_port_base::character_size(8));
    port.set_option(serial_port_base::parity(serial_port_base::parity::none));
    port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
    port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
}

TempReader::~TempReader() {
    stop();
}

void TempReader::start() {
    stop();
    threadFlag = true;
    thread = std::thread(&TempReader::threadFunc, this, std::ref(threadFlag));
}

void TempReader::stop() {
    threadFlag = false;
    if (thread.joinable()) {
        thread.join();
    }
}

std::pair<QDateTime, float> TempReader::getLastValue() {
    if (!buffer.size()) {
        return std::make_pair(QDateTime(), 0);
    }
    auto lastIt = --buffer.end();
    return *lastIt;
}

std::map<QDateTime, float> TempReader::getBuffer() {
    return buffer;
}

void TempReader::threadFunc(bool &threadFlag) {
    while (true) {
        if (!threadFlag) {
            break;
        }

        boost::asio::streambuf buffer;
        boost::system::error_code ec;

        try {
            read_until(port, buffer, '\n', ec);
            if (ec) {
                throw std::runtime_error(ec.message());
            }
            std::istream is(&buffer);
            std::string line;

            getline(is, line);
            json jsonObj = json::parse(line);

            QDateTime dateTime = QDateTime::fromString(
                                 QString::fromStdString((std::string)jsonObj["Time"]),
                                 "dd.MM.yyyy HH:mm:ss");
            float temp = jsonObj["Temp"];

            this->buffer.insert(std::make_pair(dateTime, temp));
            emit updateInfo(dateTime, temp);
        } catch (const std::exception &e) {

        } catch (...) {}
    }
}
