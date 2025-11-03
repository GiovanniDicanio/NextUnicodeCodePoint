//////////////////////////////////////////////////////////////////////////
// FILE: NextCodePoint.cpp
//
// DESC: Implementations of functions to find the next Unicode code point
//       in UTF-8 and UTF-16 encoded strings.
//
// AUTHOR: Giovanni Dicanio & AI
//////////////////////////////////////////////////////////////////////////


#include "NextCodePoint.hpp"    // public header

#include <stdint.h>             // for uint8_t


std::pair<char32_t, size_t> NextCodePointUtf16(const std::wstring& input, size_t index) {
    if (index >= input.size()) {
        throw std::out_of_range("Index out of range");
    }

    wchar_t first = input[index];

    // UTF-16 surrogate range: D800–DFFF
    if (first >= 0xD800 && first <= 0xDBFF) {
        // High surrogate
        if (index + 1 >= input.size()) {
            throw std::out_of_range("Truncated surrogate pair");
        }
        wchar_t second = input[index + 1];
        if (second < 0xDC00 || second > 0xDFFF) {
            throw std::invalid_argument("Invalid surrogate pair");
        }

        // Combine surrogates into a single code point
        char32_t high = first - 0xD800;
        char32_t low = second - 0xDC00;
        char32_t codePoint = (high << 10) + low + 0x10000;

        return { codePoint, 2 };
    }
    else if (first >= 0xDC00 && first <= 0xDFFF) {
        // Low surrogate without preceding high surrogate
        throw std::invalid_argument("Unpaired low surrogate");
    }
    else {
        // BMP character (1 code unit)
        return { static_cast<char32_t>(first), 1 };
    }
}



//
// *** Code generated and reviewed by the AI (ChatGPT, Perplexity, and Claude) ***
//

std::pair<char32_t, size_t> NextCodePointUtf8(const std::string& str, size_t index) {
    if (index >= str.size())
        throw std::out_of_range("Index out of range");

    uint8_t first = static_cast<uint8_t>(str[index]);
    char32_t codepoint;
    size_t length;

    if (first < 0x80) {         // 1-byte sequence (0xxxxxxx)
        return { first, 1 };
    }
    else if ((first & 0xE0) == 0xC0) { // 2-byte sequence (110xxxxx 10xxxxxx)
        if (first < 0xC2)  // Reject overlong encodings (C0, C1)
            throw std::invalid_argument("Overlong UTF-8 sequence");

        if (index + 1 >= str.size())
            throw std::out_of_range("Incomplete UTF-8 sequence");

        uint8_t second = static_cast<uint8_t>(str[index + 1]);
        if ((second & 0xC0) != 0x80)
            throw std::invalid_argument("Invalid UTF-8 continuation byte");

        codepoint = ((first & 0x1F) << 6) | (second & 0x3F);
        length = 2;
    }
    else if ((first & 0xF0) == 0xE0) { // 3-byte sequence (1110xxxx 10xxxxxx 10xxxxxx)
        if (index + 2 >= str.size())
            throw std::out_of_range("Incomplete UTF-8 sequence");

        uint8_t second = static_cast<uint8_t>(str[index + 1]);
        uint8_t third = static_cast<uint8_t>(str[index + 2]);

        if ((second & 0xC0) != 0x80 || (third & 0xC0) != 0x80)
            throw std::invalid_argument("Invalid UTF-8 continuation byte");

        codepoint = ((first & 0x0F) << 12) |
            ((second & 0x3F) << 6) |
            (third & 0x3F);

        // Reject overlong sequences
        if (codepoint < 0x800)
            throw std::invalid_argument("Overlong UTF-8 sequence");

        // Reject UTF-16 surrogates (U+D800 to U+DFFF)
        if (codepoint >= 0xD800 && codepoint <= 0xDFFF)
            throw std::invalid_argument("UTF-16 surrogate in UTF-8");

        length = 3;
    }
    else if ((first & 0xF8) == 0xF0) { // 4-byte sequence (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx)
        if (first > 0xF4)  // Maximum valid is F4 (for U+10FFFF)
            throw std::invalid_argument("Code point exceeds Unicode maximum");

        if (index + 3 >= str.size())
            throw std::out_of_range("Incomplete UTF-8 sequence");

        uint8_t second = static_cast<uint8_t>(str[index + 1]);
        uint8_t third = static_cast<uint8_t>(str[index + 2]);
        uint8_t fourth = static_cast<uint8_t>(str[index + 3]);

        if ((second & 0xC0) != 0x80 || (third & 0xC0) != 0x80 || (fourth & 0xC0) != 0x80)
            throw std::invalid_argument("Invalid UTF-8 continuation byte");

        codepoint = ((first & 0x07) << 18) |
            ((second & 0x3F) << 12) |
            ((third & 0x3F) << 6) |
            (fourth & 0x3F);

        // Reject overlong sequences
        if (codepoint < 0x10000)
            throw std::invalid_argument("Overlong UTF-8 sequence");

        // Reject code points beyond U+10FFFF
        if (codepoint > 0x10FFFF)
            throw std::invalid_argument("Code point exceeds Unicode maximum");

        length = 4;
    }
    else {
        throw std::invalid_argument("Invalid UTF-8 leading byte");
    }

    return { codepoint, length };
}
