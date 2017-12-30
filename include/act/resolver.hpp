/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015-2017 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_RESOLVER_HPP_INCLUDED
#define ACT_RESOLVER_HPP_INCLUDED

#include <act/awaiter.hpp>
#include <boost/asio/detail/string_view.hpp>

namespace act
{
    using ::boost::asio::string_view;

    template<class Resolver>
    inline auto resolve(Resolver& resolver, string_view host, string_view service)
    {
        ACT_RETURN_AWAITER(typename Resolver::results_type, resolver, resolve, host, service);
    }

    template<class Resolver>
    inline auto resolve(Resolver& resolver, string_view host, string_view service, error_code& ec)
    {
        ACT_RETURN_AWAITER_EC(typename Resolver::results_type, resolver, resolve, host, service);
    }

    template<class Resolver>
    inline auto resolve(Resolver& resolver, string_view host, string_view service, typename Resolver::flags resolve_flags)
    {
        ACT_RETURN_AWAITER(typename Resolver::results_type, resolver, resolve, host, service, resolve_flags);
    }

    template<class Resolver>
    inline auto resolve(Resolver& resolver, string_view host, string_view service, typename Resolver::flags resolve_flags, error_code& ec)
    {
        ACT_RETURN_AWAITER_EC(typename Resolver::results_type, resolver, resolve, host, service, resolve_flags);
    }

    template<class Resolver>
    inline auto resolve(Resolver& resolver, typename Resolver::protocol_type const& protocol, string_view host, string_view service)
    {
        ACT_RETURN_AWAITER(typename Resolver::results_type, resolver, resolve, protocol, host, service);
    }

    template<class Resolver>
    inline auto resolve(Resolver& resolver, typename Resolver::protocol_type const& protocol, string_view host, string_view service, error_code& ec)
    {
        ACT_RETURN_AWAITER_EC(typename Resolver::results_type, resolver, resolve, protocol, host, service);
    }

    template<class Resolver>
    inline auto resolve(Resolver& resolver, typename Resolver::protocol_type const& protocol, string_view host, string_view service, typename Resolver::flags resolve_flags)
    {
        ACT_RETURN_AWAITER(typename Resolver::results_type, resolver, resolve, protocol, host, service, resolve_flags);
    }

    template<class Resolver>
    inline auto resolve(Resolver& resolver, typename Resolver::protocol_type const& protocol, string_view host, string_view service, typename Resolver::flags resolve_flags, error_code& ec)
    {
        ACT_RETURN_AWAITER_EC(typename Resolver::results_type, resolver, resolve, protocol, host, service, resolve_flags);
    }

    template<class Resolver>
    inline auto resolve(Resolver& resolver, typename Resolver::endpoint_type const& endpoint)
    {
        ACT_RETURN_AWAITER(typename Resolver::results_type, resolver, resolve, endpoint);
    }

    template<class Resolver>
    inline auto resolve(Resolver& resolver, typename Resolver::endpoint_type const& endpoint, error_code& ec)
    {
        ACT_RETURN_AWAITER_EC(typename Resolver::results_type, resolver, resolve, endpoint);
    }
}

#endif