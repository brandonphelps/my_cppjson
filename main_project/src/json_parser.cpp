
#include "token_id.h"
#include "json_parser.h"

#include <stdio.h>
#include <iostream>

JsonParser::JsonParser()
{
  m_symbol_vector.push_back(TokenId::lbrace);
  m_symbol_vector.push_back(TokenId::rbrace);
  m_symbol_vector.push_back(TokenId::colon);
  m_symbol_vector.push_back(TokenId::comma);
}

std::map<std::string, std::string> JsonParser::parse(const std::string& filename)
{
  m_data = std::map<std::string, std::string>();

  m_instream.open(filename.c_str());

  if(m_instream.is_open())
  {
    if(start_symbol())
    {
      std::cout << "--- Success" << std::endl;
      return m_data;
    }
    else
    {
      std::cout << "--- Failure" << std::endl;
    }
  }
  else
  {
    std::cout << "Error Reading file: " << filename << std::endl;
  }

  m_instream.close();

  return std::map<std::string, std::string>();
}

int JsonParser::get_char()
{
  int code = m_instream.get();
  std::cout << "Code: " << code << std::endl;
  m_current_char = char(code);
  if(code == -1)
  {
	  code = 0;
  }
  return code;
}

bool JsonParser::is_symbol(const std::string& symbol)
{
  for(int i = 0; i < m_symbol_vector.size(); i++)
  {
    if(m_symbol_vector[i] == symbol)
    {
      return true;
    }
  }

  if(is_string(symbol))
  {
    return true;
  }
  return false;
}

void JsonParser::get_next_symbol()
{
  m_prev_symbol = m_current_symbol;
  m_current_symbol = "";

  bool symbol_found = false;
  while(!symbol_found)
  {
    if(get_char()) // get next character
    {
      m_current_symbol += m_current_char;
      if(m_current_symbol == " " || m_current_symbol == "\n") // if we pulled a white space and have no preceding characters
      {
        m_current_symbol = "";
      }
      else
      {
        if(is_symbol(m_current_symbol))
        {
          symbol_found = true;
        }
      }
    }
    else // no next character 
    {
      break;
    }
  }
}

bool JsonParser::is_string(const std::string& symbol)
{
  if(symbol.size() >= 3 && symbol[0] == '"' && symbol[symbol.size()-1] == '"')
  {
    return true;
  }
  return false;
}

bool JsonParser::accept(const std::string& symbol)
{
  if(m_current_symbol == symbol)
  {
    get_next_symbol();
    return true;
  }
  return false;
}

bool JsonParser::accept(int symbol_id)
{
  if(is_string(m_current_symbol) && symbol_id == TokenId::string_symbol_id)
  {
    // Remove the quotes from the symbol
    m_current_symbol.erase(0, 1);
    m_current_symbol.erase(m_current_symbol.size()-1, m_current_symbol.size());
    get_next_symbol();
    return true;
  }
  return false;
}

bool JsonParser::lbrace_symbol()
{
  return accept(TokenId::lbrace);
}

bool JsonParser::rbrace_symbol()
{
  return accept(TokenId::rbrace);
}

bool JsonParser::string_symbol()
{
  return accept(TokenId::string_symbol_id);
}

bool JsonParser::key_symbol()
{
  bool success = string_symbol();
  m_current_key = m_prev_symbol;
  return success;
}

bool JsonParser::colon_symbol()
{
  return accept(TokenId::colon);
}

bool JsonParser::value_symbol()
{
  bool success = string_symbol();
  m_current_value = m_prev_symbol;
  return success;
}

bool JsonParser::dict_entry_symbol()
{
  if(key_symbol())
  {
    if(colon_symbol())
    {
      if(value_symbol())
      {
        m_data[m_current_key] = m_current_value;
        return true;
      }
    }
  }
  return false;
}

bool JsonParser::dict_entry_list_symbol()
{
  if(dict_entry_symbol())
  {
    if(accept(TokenId::comma))
    {
      return dict_entry_list_symbol();
    }
    else
    {
      return true;
    }
  }
  return false;
}

bool JsonParser::dictionary_symbol()
{
  bool success = true;
  success &= lbrace_symbol();
  success &= dict_entry_list_symbol();
  success &= rbrace_symbol();
  return success;
}

bool JsonParser::start_symbol()
{
  get_next_symbol();
  return dictionary_symbol();
}
