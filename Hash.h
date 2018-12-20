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
/** @file SHA3.h
 * @author Gav Wood <i@gavwood.com>
 * @date 2014
 *
 * The FixedHash fixed-size "hash" container type.
 */

#pragma once

#include "Common.h"
#include "CommonData.h"
#include <string>

namespace dev
{
// SHA-3 convenience routines.

/// Calculate SHA3-256 hash of the given input and load it into the given output.
/// @returns false if o_output.size() != 32.
bool sha3(bytesConstRef _input, bytesRef o_output);

/// Calculate SHA3-256 hash of the given input, returning as a 256-bit hash.
inline bytes sha3(bytesConstRef _input)
{
    bytes ret(32, 0);
    sha3(_input, ref(ret));
    return ret;
}

inline bytes sha3(std::string const& _input)
{
    return sha3(bytesConstRef(_input));
}

}