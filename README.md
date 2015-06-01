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
std::task<void> session(asio::ip::tcp::socket sock)
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
                return;
            await act::write(sock, asio::buffer(buf, len));
        }
    }
    catch (std::exception& e)
    {
        std::cout << "error: " << sock.remote_endpoint() << ": " << e.what() << std::endl;
    }
}

std::task<void> server(asio::io_service& io)
{
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), 8823);
    asio::ip::tcp::acceptor acceptor(io, endpoint);
    std::cout << "server running at: " << endpoint << std::endl;
    for ( ; ; )
    {
        session(await act::accept(acceptor));
    }
}

int main(int argc, char *argv[])
{
    asio::io_service io;
    server(io);
    io.run();

    return EXIT_SUCCESS;
}
```

## License

    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
