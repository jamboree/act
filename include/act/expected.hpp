/*//////////////////////////////////////////////////////////////////////////////
    Copyright (c) 2015 Jamboree

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//////////////////////////////////////////////////////////////////////////////*/
#ifndef ACT_EXPECTED_HPP_INCLUDED
#define ACT_EXPECTED_HPP_INCLUDED

#include <boost/system/system_error.hpp>

namespace act
{
    template<class T>
    class expected
    {
        using val_t = T;
        using error_t = boost::system::error_code;
        using ref_t = std::add_lvalue_reference_t<T>;
        using cref_t = std::add_lvalue_reference_t<std::add_const_t<T>>;

    public:

        expected() : _err(), _is_err(true) {}

        expected(T val) : _val(std::forward<T>(val)), _is_err(false) {}

        explicit expected(error_t err) : _err(std::forward<error_t>(err)), _is_err(true) {}

        template<class U>
        expected(expected<U>&& other) : _is_err(other._is_err)
        {
            if (_is_err)
                _err = other._err;
            else
            {
                _err.~error_t();
                new(&_val) val_t(std::move(other._val));
            }
        }

        template<class U>
        expected(expected<U> const& other) : _is_err(other._is_err)
        {
            if (_is_err)
                _err = other._err;
            else
            {
                _err.~error_t();
                new(&_val) val_t(other._val);
            }
        }

        expected(expected&& other) : _is_err(other._is_err)
        {
            if (_is_err)
                _err = other._err;
            else
            {
                _err.~error_t();
                new(&_val) val_t(std::move(other._val));
            }
        }

        expected(expected const& other) : _is_err(other._is_err)
        {
            if (_is_err)
                _err = other._err;
            else
            {
                _err.~error_t();
                new(&_val) val_t(other._val);
            }
        }

        expected& operator=(expected other) noexcept
        {
            this->~expected();
            return *new(this) expected(std::move(other));
        }

        void set_error(error_t err) noexcept
        {
            if (_is_err)
                _err = std::forward<error_t>(err);
            else
            {
                _val.~val_t();
                new(&_err) error_t(std::forward<error_t>(err));
            }
        }

        void set_value(T val)
        {
            if (_is_err)
            {
                _err.~error_t();
                new(&_val) val_t(std::forward<T>(val));
            }
            else
                _val = std::forward<T>(val);
        }

        bool has_error() const
        {
            return _is_err;
        }

        void throw_error() const
        {
            if (_is_err)
                throw boost::system::system_error(_err);
        }

        error_t const& get_error() const
        {
            return _err;
        }

        cref_t get_value() const
        {
            return _val;
        }

        cref_t get() const
        {
            throw_error();
            return _val;
        }

        operator cref_t() const
        {
            return get();
        }

        ~expected()
        {
            if (_is_err)
                _err.~error_t();
            else
                _val.~val_t();
        }

    private:

        union
        {
            error_t _err;
            val_t _val;
        };
        bool _is_err;
    };
}

#endif