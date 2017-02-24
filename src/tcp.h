/**
 *  tcp.h
 *
 *  Abstraction for windows and bsd sockets
 */

#pragma once

/**
 *  Dependencies
 */
#include "includes.h"

/**
 *  Set up namespace
 */
namespace AMQP {

namespace tcp
{
    /**
    *  Gets current networking error
    */
    int Errno();

    /**
    *  Formats network error code
    *  @param  errorCode  error code from errno
    */
    const char * const StrError(int errorCode);

    /**
    *  Closes socket
    *  @param  socket  to close
    */
    int Close(tcp::Socket socket);

};

/**
 *  End of namespace
 */
}

