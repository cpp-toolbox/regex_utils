#ifndef REGEX_UTILS_HPP
#define REGEX_UTILS_HPP

#include <regex>
#include <unordered_map>

#include "sbpt_generated_includes.hpp"

namespace regex_utils {

inline std::string surround_with(const std::string &s, const std::string &w) { return w + s + w; }
inline std::string capture(const std::string &s) { return "(" + s + ")"; }
inline std::vector<std::string> capture(const std::vector<std::string> &s) {
    std::vector<std::string> result;
    result.reserve(s.size());
    for (const auto &elem : s) {
        result.push_back(capture(elem));
    }
    return result;
}
inline std::string character_class(const std::vector<std::string> &chars) {
    std::string result = "[";
    for (const auto &ch : chars) {
        result += ch;
    }
    result += "]";
    return result;
}

inline std::string one_or_more(const std::string &character_class) { return character_class + "+"; }

inline const std::string start_of_line = R"(^)";
inline const std::string end_of_line = R"($)";
inline const std::string any_char = R"(.)";
inline const std::string any_char_greedy = R"(.*)";
inline const std::string any_char_nongreedy = R"(.*?)";

inline const std::string right_parenthesis = R"(\))";
inline const std::string left_parenthesis = R"(\()";

inline std::string wrap_parentheses(const std::string &s) { return left_parenthesis + s + right_parenthesis; }

inline const std::string ws_char = R"(\s)";
inline const std::string optional_ws = R"(\s*)";
inline const std::string one_or_more_ws = R"(\s+)";
inline const std::string digit = R"(\d)";
inline const std::string nonzero_digit = R"([1-9])";
inline const std::string binary_digit = R"([0-1])";
inline const std::string lowercase_letter = R"([a-z])";
inline const std::string uppercase_letter = R"([A-Z])";
inline const std::string letter = R"([A-Za-z])";
inline const std::string word_char = R"(\w)";
inline const std::string word = R"(\w+)";
inline const std::string identifier = R"([A-Za-z_]\w*)";

inline const std::string string_literal(R"("(?:[^"\\]|\\.)*")");

inline const std::string optional_ws_comma = surround_with(",", optional_ws);

inline std::string tuple_of(const std::vector<std::string> &regexes) {
    return surround_with(wrap_parentheses(surround_with(text_utils::join(regexes, optional_ws_comma), optional_ws)),
                         optional_ws);
}

inline const std::string int_regex = R"(-?\d+)";
inline const std::string unsigned_int_regex = R"(\d+)";
inline const std::string float_regex = R"(-?\d+(?:\.\d+)?)";
inline const std::string captured_float_regex = capture(float_regex);

inline const std::string float_tuple = surround_with(
    wrap_parentheses(surround_with(text_utils::join({float_regex, float_regex}, optional_ws_comma), optional_ws)),
    optional_ws);

inline const std::string captured_float_tuple =
    surround_with(wrap_parentheses(surround_with(
                      text_utils::join({capture(float_regex), capture(float_regex)}, optional_ws_comma), optional_ws)),
                  optional_ws);

inline const std::string float_triplet =
    surround_with(wrap_parentheses(surround_with(
                      text_utils::join({float_regex, float_regex, float_regex}, optional_ws_comma), optional_ws)),
                  optional_ws);

inline const std::string captured_float_triplet = surround_with(
    wrap_parentheses(surround_with(
        text_utils::join({capture(float_regex), capture(float_regex), capture(float_regex)}, optional_ws_comma),
        optional_ws)),
    optional_ws);

inline std::regex function_signature_re(R"(^\s*([\w:<>]+(?:\s*[*&])?)\s+(\w+)\s*\((.*)\)\s*$)");

inline const std::string type_char_class = character_class({word_char, ws_char, ":", "<", ">", ","});
inline const std::string simple_template_type =
    text_utils::join({capture(word), "<", capture(one_or_more(type_char_class)), ">"}, optional_ws);

// std::string return_type = match[1];
// std::string func_name = match[2];
// std::string args_str = match[3];

}; // namespace regex_utils

#endif // REGEX_UTILS_HPP
