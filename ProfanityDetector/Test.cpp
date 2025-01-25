/*

#include <iostream>
#include <string>

#include "ProfanityDetector.h"

int main() {
	std::string message;

	std::cout << "word: " << "\n";
	std::cin >> message;

	if (BProfanity::check(message)) {
		std::cout << "contains blacklisted word";
	}
	else {
		std::cout << "doesnt contain blacklisted word.";
	}

	return EXIT_SUCCESS;
} */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <zlib.h>

// Helper function to compress data
std::string compressData(const std::string& data) {
  uLong sourceLen = data.size();
  uLong destLen = compressBound(sourceLen);
  std::vector<Bytef> compressedData(destLen);

  if (compress(compressedData.data(), &destLen, reinterpret_cast<const Bytef*>(data.data()), sourceLen) != Z_OK) {
    throw std::runtime_error("Failed to compress data.");
  }

  return std::string(reinterpret_cast<char*>(compressedData.data()), destLen);
}

// Helper function to decompress data
std::string decompressData(const std::string& compressedData, uLong originalSize) {
  std::vector<Bytef> decompressedData(originalSize);

  if (uncompress(decompressedData.data(), &originalSize, reinterpret_cast<const Bytef*>(compressedData.data()), compressedData.size()) != Z_OK) {
    throw std::runtime_error("Failed to decompress data.");
  }

  return std::string(reinterpret_cast<char*>(decompressedData.data()), originalSize);
}

// Function to write SSTable with compression
void writeSSTable(const std::string& dataFile, const std::map<std::string, std::string>& data) {
  std::ofstream dataStream(dataFile, std::ios::binary);

  if (!dataStream) {
    throw std::runtime_error("Failed to open file for writing.");
  }

  for (const auto& entry : data) {
    const std::string& key = entry.first;
    const std::string& value = entry.second;

    // Compress the value
    std::string compressedValue = compressData(value);

    // Write key and compressed value size
    dataStream.write(key.c_str(), key.size());
    dataStream.put('\0'); // Null terminator
    uLong compressedSize = compressedValue.size();
    uLong originalSize = value.size();
    dataStream.write(reinterpret_cast<const char*>(&compressedSize), sizeof(compressedSize));
    dataStream.write(reinterpret_cast<const char*>(&originalSize), sizeof(originalSize));

    // Write the compressed value
    dataStream.write(compressedValue.c_str(), compressedValue.size());
  }

  dataStream.close();
}

// Function to read SSTable with decompression
std::string readSSTable(const std::string& dataFile, const std::string& keyToFind) {
  std::ifstream dataStream(dataFile, std::ios::binary);

  if (!dataStream) {
    throw std::runtime_error("Failed to open file for reading.");
  }

  while (true) {
    // Read key
    std::string key;
    char c;
    while (dataStream.get(c) && c != '\0') {
      key.push_back(c);
    }

    if (dataStream.eof()) {
      break;
    }

    // Read compressed size and original size
    uLong compressedSize, originalSize;
    dataStream.read(reinterpret_cast<char*>(&compressedSize), sizeof(compressedSize));
    dataStream.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));

    // Read compressed value
    std::vector<char> compressedData(compressedSize);
    dataStream.read(compressedData.data(), compressedSize);

    // Decompress value
    std::string value = decompressData(std::string(compressedData.begin(), compressedData.end()), originalSize);

    if (key == keyToFind) {
      return value;
    }
  }

  return ""; // Key not found
}

int main() {
  std::map<std::string, std::string> data = {
      {"key1", "This is a sample value for key1."},
      {"key2", "Another value for key2."},
      {"key3", "Key3 has a longer and more detailed value."} };

  const std::string filename = "compressed_data.sst";

  try {
    // Write SSTable
    writeSSTable(filename, data);

    // Read a specific key
    std::string value = readSSTable(filename, "key2");
    if (!value.empty()) {
      std::cout << "Found value for key2: " << value << "\n";
    }
    else {
      std::cout << "Key not found.\n";
    }
  }
  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
  }

  return 0;
}
