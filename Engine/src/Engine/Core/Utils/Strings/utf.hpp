#pragma once

namespace Engine::Utils {
    char32_t UTF8toChar32_t(const char* bytes) {
        char32_t codepoint;

        if ((bytes[0] & 0b10000000) == 0) {
            // 1 byte code point, ASCII
            codepoint = (bytes[0] & 0b01111111);
        }
        else if ((bytes[0] & 0b11100000) == 0b11000000) {
            // 2 byte code point
            codepoint = (bytes[0] & 0b00011111) << 6 | (bytes[0 + 1] & 0b00111111);
        }
        else if ((bytes[0] & 0b11110000) == 0b11100000) {
            // 3 byte code point
            codepoint = (bytes[0] & 0b00001111) << 12 | (bytes[0 + 1] & 0b00111111) << 6 | (bytes[0 + 2] & 0b00111111);
        }
        else {
            // 4 byte code point
            codepoint = (bytes[0] & 0b00000111) << 18 | (bytes[0 + 1] & 0b00111111) << 12 | (bytes[0 + 2] & 0b00111111) << 6 | (bytes[0 + 3] & 0b00111111);
        }

        return codepoint;
    }
}