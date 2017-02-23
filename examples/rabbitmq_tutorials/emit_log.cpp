#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "tools.h"
#include "asiohandler.h"
#include "testcredentials.h"

int main(int argc, const char* argv[])
{
    try {
        const std::string msg =
            argc > 1 ? join(&argv[1], &argv[argc], " ") : "info: Hello World!";

        boost::asio::io_service ioService;
        AsioHandler handler(ioService);
        handler.connect(AMQP_TEST_HOST, AMQP_TEST_PORT);

        AMQP::Connection connection(&handler, AMQP::Login(AMQP_TEST_LOGIN, AMQP_TEST_PASSWORD), AMQP_TEST_VIRTUALHOST);

        std::string exchangeName = "logs";

        boost::asio::deadline_timer t(ioService, boost::posix_time::millisec(100));
        AMQP::Channel channel(&connection);
        channel.declareExchange(exchangeName, AMQP::fanout).onSuccess([&]()
        {
            channel.publish(exchangeName, "", msg);
            std::cout << " [x] Sent "<<msg<< std::endl;
            t.async_wait([&](const boost::system::error_code&) {ioService.stop(); });
        });

        ioService.run();
    }
    catch (std::exception &) {

    }
    return 0;
}
