#include <algorithm>
#include <cassert>
#include <string>

// All of the following functions operate on little-endian numbers.
// That is, the opposite of how they are usually written.
std::string multiply(const std::string& left, const std::string& right);
std::string multiply(const std::string& num, char digit);
std::string add(const std::string& left, const std::string& right);
std::string shift_up(const std::string& num, int places);

std::string add(const std::string& left, const std::string& right) {
  std::string result;
  int carry = 0;
  const int n = std::max(left.size(), right.size());

  for (int i = 0; i < n; ++i) {
    const int L = (i < left.size() ? left[i] - '0' : 0);
    const int R = (i < right.size() ? right[i] - '0' : 0);
    const int sum = L + R + carry;
    const int digit = sum % 10;
    carry = sum / 10;
    result += '0' + digit;
  }

  if (carry) {
    result += '0' + carry;
  }

  return result;
}

std::string shift_up(const std::string& number, int places) {
  assert(places >= 0);

  if (number == "0") {
    return number;
  }

  std::string result;
  result.append(places, '0');
  result += number;
  return result;
}

std::string multiply(const std::string& num, char digit) {
  // Redundant, but I feel like it.
  if (digit == '0') {
    return "0";
  }
  if (digit == '1') {
    return num;
  }

  std::string result;
  int carry = 0;
  for (int i = 0; i < num.size(); ++i) {
    const int product = (num[i] - '0') * (digit - '0') + carry;
    const int digit_out = product % 10;
    carry = product / 10;
    result.push_back('0' + digit_out);
  }

  if (carry) {
    result.push_back('0' + carry);
  }

  return result;
}

std::string multiply(const std::string& left, const std::string& right) {
  std::string result = "0";
  for (int i = 0; i < int(left.size()); ++i) {
    const char digit = left[i];
    std::string product = multiply(right, digit);
    result = add(result, shift_up(product, i));
  }
  return result;
}

#include <cstdlib>
#include <cstring>
#include <iostream>

void test_add(std::string left, std::string right) {
  std::reverse(left.begin(), left.end());
  std::reverse(right.begin(), right.end());
  std::string result = add(left, right);
  std::reverse(result.begin(), result.end());
  std::cout << result << '\n';
}

void test_shift_up(std::string number, const char *places_raw) {
  std::reverse(number.begin(), number.end());
  const int places = std::atoi(places_raw);
  std::string result = shift_up(number, places);
  std::reverse(result.begin(), result.end());
  std::cout << result << '\n';
}

void test_multiply_digit(std::string number, const char *digit_raw) {
  assert(std::strlen(digit_raw) == 1);

  const char digit = digit_raw[0];
  std::reverse(number.begin(), number.end());
  std::string result = multiply(number, digit);
  std::reverse(result.begin(), result.end());
  std::cout << result << '\n';
}

void test_multiply_numbers(std::string left, std::string right) {
  std::reverse(left.begin(), left.end());
  std::reverse(right.begin(), right.end());
  std::string result = multiply(left, right);
  std::reverse(result.begin(), result.end());
  std::cout << result << '\n';
}

int main(int, char *argv[]) {
  // test_add(argv[1], argv[2]);
  // test_shift_up(argv[1], argv[2]);
  // test_multiply_digit(argv[1], argv[2]);
  test_multiply_numbers(argv[1], argv[2]);
}