# NextUnicodeCodePoint
C++ code to find the next Unicode code point in UTF-8 and UTF-16 encoded strings.

The `NextCodePoint.hpp` header declares the public interfaces of two functions: `NextCodePointUtf8` and `NextCodePointUtf16`.
As their names suggest, they are used to find the next code point in UTF-8 and UTF-16 encoded strings.
Think of them like the "Unicode evolution" of increasing a character position index when iterating through characters of pure ASCII strings:

```cpp
std::string name = "Connie";

for (size_t index = 0; index < name.size(); index++) {
    std::cout << name[index];
}
```

The function declarations are the following:

```cpp
// Returns the next Unicode code point and number of bytes consumed.
// Throws std::out_of_range if index is out of bounds or string ends prematurely.
// Throws std::invalid_argument on invalid UTF-8 sequence.
[[nodiscard]] std::pair<char32_t, size_t> NextCodePointUtf8(const std::string& str, size_t index);


// Returns the next Unicode code point and the number of UTF-16 code units consumed.
// Throws std::out_of_range if index is out of bounds or string ends prematurely.
// Throws std::invalid_argument on invalid UTF-16 sequence.
[[nodiscard]] std::pair<char32_t, size_t> NextCodePointUtf16(const std::wstring& input, size_t index);
```

These functions can be used like this:

```cpp
std::wstring text = L"A\xD834\xDD1E!"; // A + U+1D11E (𝄞) + !

size_t index = 0;
while (index < text.size()) {
    auto [codepoint, units] = NextCodePointUtf16(text, index);
    std::cout << "Codepoint: U+" << std::hex << codepoint
              << " (" << units << " units)\n";
    index += units;
}
```
