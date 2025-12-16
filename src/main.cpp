#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>


int main() {
    std::ifstream file("test.bin", std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::vector<uint8_t> bytes(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    std::cout << "Read " << bytes.size() << " bytes\n";

    return 0;

}