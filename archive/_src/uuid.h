#ifndef UUID_H
#define UUID_H

#include <random>
#include <sstream>
#include <string>

// Random generation courtesy of https://lowrey.me/guid-generation-in-c-11/

class UUID {
public:
  /**
   * @brief Generates a uuid string in the form
   * b9317db-02a2-4882-9b94-d1e1defe8c56
   *
   * @return std::string
   */
  static std::string generate();

  /**
   * @brief
   *
   * @param len Length in bytes
   * @return std::string  String random hex chars (2x length of the bytes)
   */
  static std::string hex(const unsigned int len);

private:
  /**
   * @brief Generates a safe pseudo-random character
   *
   * @return unsigned int
   */
  static unsigned int random_char();
};


#endif

