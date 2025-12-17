#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <stdexcept>


struct ByteReader {
    std::vector<uint8_t> data;
    size_t offset = 0;

    uint8_t readU1() {
        if (offset >= data.size()) {
            throw std::runtime_error("Out of bounds readU1");
        }
        return data[offset++];
    }

    uint16_t readU2() {
        uint16_t value = 0;
        value  |= static_cast<uint16_t>(readU1()) << 8;
        value  |= static_cast<uint16_t>(readU1());
        return value;
    }

     uint32_t readU4() {
        uint32_t value = 0;
        value  |= static_cast<uint32_t>(readU1()) << 24;
        value  |= static_cast<uint32_t>(readU1()) << 16;
        value  |= static_cast<uint32_t>(readU1()) << 8;
        value  |= static_cast<uint32_t>(readU1());
        return value;
    }
};


int main() {
    std::ifstream file("test.bin", std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    ByteReader reader;
    reader.data = std::vector<uint8_t>(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    uint32_t magic = reader.readU4();
    uint16_t minor = reader.readU2();
    uint16_t major = reader.readU2();

    std::cout << std::hex;
    std::cout << "magic: 0x" << magic << "\n";
    std::cout << "minor: " << minor << "\n";
    std::cout << "major: " << major << "\n";

    return 0;

}