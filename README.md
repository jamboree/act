act
===

[ASIO](http://www.boost.org/doc/libs/release/doc/html/boost_asio.html) Cooperative Task

## Requirements

- Compiler that implements [N4286](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4286.pdf)
- Or emulation library like [CO2](https://github.com/jamboree/co2)

## Dependencies

- [Boost](http://www.boost.org/)

## Example

async echo server
```c++
task<void> session(asio::ip::tcp::socket sock)
{
    try
    {
        char buf[1024];
        std::cout << "connected: " << sock.remote_endpoint() << std::endl;
        for ( ; ; )
        {
            act::error_code ec;
            auto len = await act::read_some(sock, asio::buffer(buf), ec);
            if (ec == asio::error::eof)
                co_return;
            co_await act::write(sock, asio::buffer(buf, len));
        }
    }
    catch (std::exception& e)
    {
        std::cout << "error: " << sock.remote_endpoint() << ": " << e.what() << std::endl;
    }
}

task<void> server(asio::io_service& io, unsigned short port)
{
    asio::ip::tcp::endpoint endpoint{asio::ip::tcp::v4(), port};
    asio::ip::tcp::acceptor acceptor{io, endpoint};
    asio::ip::tcp::socket sock{io};
    std::cout << "server running at: " << endpoint << std::endl;
    for ( ; ; )
    {
        co_await act::accept(acceptor, sock);
        session(std::move(sock));
    }
}

int main(int argc, char *argv[])
{
    asio::io_service io;
    server(io, std::atoi(argv[1]));
    io.run();

    return EXIT_SUCCESS;
}
```

## License

    Copyright (c) 2015-2017 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
