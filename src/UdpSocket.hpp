/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 EnyxSA
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/system/error_code.hpp>

#include "SessionConfiguration.hpp"
#include "Socket.hpp"

namespace enyx {
namespace net_tester {

class UdpSocket : public Socket
{
public:
    using socket_type = boost::asio::ip::udp::socket;
    using protocol_type = socket_type::protocol_type;
    using endpoint_type = socket_type::endpoint_type;

public:
    explicit
    UdpSocket(boost::asio::io_service & io_service,
              const SessionConfiguration & configuration);

    template<typename MutableBufferSequence, typename ReadHandler>
    void
    async_receive(const MutableBufferSequence & buffers, ReadHandler handler)
    {
        socket_.async_receive_from(buffers, discarded_endpoint_, handler);
    }

    template<typename ConstBufferSequence, typename WriteHandler>
    void
    async_send(const ConstBufferSequence & buffers, WriteHandler handler)
    {
        socket_.async_send_to(buffers, peer_endpoint_, handler);
    }

    void
    close();

private:
    void
    connect(const SessionConfiguration & configuration);

    void
    listen(const SessionConfiguration & configuration,
           const boost::posix_time::time_duration & timeout);

private:
    socket_type socket_;
    endpoint_type discarded_endpoint_;
    endpoint_type peer_endpoint_;
};

} // namespace net_tester
} // namespace enyx

