//////////////////////////////////////////////////////////////////////////
// FILE: TestNextCodePoint.cpp
//
// DESC: This file contains the 'main' function. Tests the functions
//       declared in the NextCodePoint.hpp header.
//
// AUTHOR: Giovanni Dicanio
//
//////////////////////////////////////////////////////////////////////////

#include "NextCodePoint.hpp"    // public header for functions to test

#include <exception>            // for std::exception
#include <iostream>             // for std::cout, std::cerr


void TestNextCodePointUtf16() {
    std::cout << "\n\n--- Testing NextCodePointUtf16 ---\n\n";

    std::wstring text = L"A\xD834\xDD1E!"; // A + U+1D11E (𝄞) + !

    size_t index = 0;

    try {
        while (index < text.size()) {
            auto [codepoint, units] = NextCodePointUtf16(text, index);
            std::cout << "Codepoint: U+" << std::hex << codepoint
                      << " (" << units << " units)\n";
            index += units;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error at index " << index << ": " << e.what() << "\n";
    }
}


void TestNextCodePointUtf8() {
    std::cout << "\n\n--- Testing NextCodePointUtf8 ---\n\n";

    // This doesn't seem to work with VS 2019:
    //
    //    std::string text = "Hello 世界 🌍";
    //
    // So I wrote the explicit UTF-8 byte sequence in hex:
    //
    std::string text = "Hello \xE4\xB8\x96\xE7\x95\x8C \xF0\x9F\x8C\x8D";

    size_t index = 0;
    try {
        while (index < text.size()) {
            auto [codepoint, bytes] = NextCodePointUtf8(text, index);
            std::cout << "U+" << std::hex << codepoint
                      << " (" << bytes << " bytes)\n";
            index += bytes;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error at index " << index << ": " << e.what() << "\n";
    }
}

int main()
{
    TestNextCodePointUtf16();
    TestNextCodePointUtf8();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
