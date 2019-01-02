/*
    This file is part of cpp-ethereum.

    cpp-ethereum is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cpp-ethereum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @brief define common Exceptions
 * @file Exceptions.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 */

#pragma once

#include <exception>
#include <string>

namespace dev
{
/**
 * @brief : Base class for all exceptions
 */
struct Exception : virtual std::exception
{
    Exception(std::string _message = std::string()) : m_message(std::move(_message)) {}
    const char* what() const noexcept override
    {
        return m_message.empty() ? std::exception::what() : m_message.c_str();
    }

private:
    std::string m_message;
};

/// construct a new exception class overidding Exception
#define DEV_SIMPLE_EXCEPTION(X)  \
    struct X : virtual Exception \
    {                            \
    }

/// Base class for all RLP exceptions.
struct RLPException : virtual Exception
{
};

/// construct a new exception class overriding RLPException
#define DEV_SIMPLE_EXCEPTION_RLP(X) \
    struct X : virtual RLPException \
    {                               \
    }


DEV_SIMPLE_EXCEPTION(BadHexCharacter);
DEV_SIMPLE_EXCEPTION(FailedInvariant);
DEV_SIMPLE_EXCEPTION(ConfigureFileError);
DEV_SIMPLE_EXCEPTION(AESKeyLengthError);

}  // namespace dev
