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
/** @file Common.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 *
 * Very common stuff (i.e. that every other header needs except vector_ref.h).
 *
 * @author wheatli
 * @date 2018.8.27
 * @modify add owning_bytes_ref
 *
 * @author yujiechen
 * @date 2018.9.5
 * @modify: remove useless micro-definition 'DEV_IF_THROWS'
 *          remove useless functions: toLog2, inUnits
 */

#pragma once

#include "vector_ref.h"
#include <sys/time.h>
#include <chrono>
#include <functional>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// BCOS log format
#define LOG_BADGE(_NAME) "[" << _NAME << "]"
#define LOG_DESC(_DESCRIPTION) _DESCRIPTION
#define LOG_KV(_K, _V) "," << _K << "=" << _V

// CryptoPP defines byte in the global namespace, so must we.
using byte = uint8_t;

// catch exceptions
#define DEV_IGNORE_EXCEPTIONS(X) \
    try                          \
    {                            \
        X;                       \
    }                            \
    catch (...)                  \
    {                            \
    }

namespace dev
{
extern char const* Version;

extern std::string const EmptyString;

//------ Common Type Definitions--------------
// vector of byte data
using bytes = std::vector<byte>;
using bytesRef = vector_ref<byte>;
using bytesConstRef = vector_ref<byte const>;
// manage vector securely in memory

// Map types.
using StringMap = std::map<std::string, std::string>;
using BytesMap = std::map<bytes, bytes>;
using HexMap = std::map<bytes, bytes>;

// Hash types.
using StringHashMap = std::unordered_map<std::string, std::string>;

// String types.
using strings = std::vector<std::string>;
using string64 = std::array<char, 64>;
// Fixed-length string types.
using string32 = std::array<char, 32>;

// Null/Invalid values for convenience.
extern bytes const NullBytes;

inline int stringCmpIgnoreCase(const std::string& lhs, const std::string& rhs)
{
#if defined(_WIN32)
    return _stricmp(lhs.c_str(), rhs.c_str());
#else
    return strcasecmp(lhs.c_str(), rhs.c_str());
#endif
}

/// @returns the absolute distance between _a and _b.
template <class N>
inline N diff(N const& _a, N const& _b)
{
    return std::max(_a, _b) - std::min(_a, _b);
}

/// Get the current time in seconds since the epoch in UTC(ms)
uint64_t utcTime();

}  // namespace dev
