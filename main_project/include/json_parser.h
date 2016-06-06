

#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <fstream>
#include <string>
#include <map>
#include <vector>

class JsonParser
{
public:
  JsonParser();

  std::map<std::string, std::string> parse(const std::string& filename);

private:
  int get_char();

  bool is_symbol(const std::string& symbol);

  void get_next_symbol();

  bool is_string(const std::string& symbol);

  bool accept(const std::string& symbol);
  bool accept(int symbol_id);

  bool lbrace_symbol();
  bool rbrace_symbol();
  bool string_symbol();
  bool key_symbol();
  bool colon_symbol();
  bool value_symbol();

  bool dict_entry_symbol();
  bool dict_entry_list_symbol();
  bool dictionary_symbol();

  bool start_symbol();

private:

  std::string m_current_symbol;
  std::string m_prev_symbol;
  char m_current_char;

  std::vector<std::string> m_symbol_vector;

  std::string m_current_key;
  std::string m_current_value;

  std::map<std::string, std::string> m_data;

private:
  std::ifstream m_instream;
};

#endif
