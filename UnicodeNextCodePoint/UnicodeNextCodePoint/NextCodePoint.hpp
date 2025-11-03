//////////////////////////////////////////////////////////////////////////
// FILE: NextCodePoint.hpp
//
// DESC: Declarations of functions to find the next Unicode code point
//       in UTF-8 and UTF-16 encoded strings.
//
// AUTHOR: Giovanni Dicanio
//////////////////////////////////////////////////////////////////////////


#pragma once

#include <stddef.h>     // for size_t
#include <string>       // for std::string, std::wstring
#include <stdexcept>    // for std::invalid_argument, std::out_of_range
#include <utility>      // for std::pair


// Returns the next Unicode code point and number of bytes consumed.
// Throws std::out_of_range if index is out of bounds or string ends prematurely.
// Throws std::invalid_argument on invalid UTF-8 sequence.
[[nodiscard]] std::pair<char32_t, size_t> NextCodePointUtf8(const std::string& str, size_t index);


// Returns the next Unicode code point and the number of UTF-16 code units consumed.
// Throws std::out_of_range if index is out of bounds or string ends prematurely.
// Throws std::invalid_argument on invalid UTF-16 sequence.
[[nodiscard]] std::pair<char32_t, size_t> NextCodePointUtf16(const std::wstring& input, size_t index);
