#include "uuid.h"

std::string UUID::generate() {
  std::stringstream hexstream;
  hexstream << UUID::hex(4) << "-" << UUID::hex(2) << "-"
    << UUID::hex(2) << "-" << UUID::hex(2) << "-"
    << UUID::hex(6);
  return hexstream.str();
}

std::string UUID::hex(const unsigned int len) {
  std::stringstream ss;
  for (auto i = 0; i < len; i++) {
    const auto rc = random_char();
    std::stringstream hexstream;
    hexstream << std::hex << rc;
    auto hex = hexstream.str();
    ss << (hex.length() < 2 ? '0' + hex : hex);
  }
  return ss.str();
}

unsigned int UUID::random_char() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 255);
  return dis(gen);
}

