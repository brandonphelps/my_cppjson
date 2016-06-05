

#include <iostream>
#include <fstream>
#include <vector>

std::ifstream infile;

char current_char;

int get_char();

bool start_token();
bool char_token();
bool hello_token();
bool world_token();
bool space_token();
bool num_token();
bool string_token();
bool key_token();

void print_current_char();

const std::string l_lbrace = "{";
const std::string l_rbrace = "}";
const std::string l_colon  = ":";
const std::string l_comma  = ",";

const int string_symbol_id = 0;

std::vector<const std::string> symbol_vector;

std::string current_symbol = "";

int get_char()
{
  int code = infile.get(current_char);
  return code;
}

bool is_string(const std::string& sym)
{
  if(sym.size() >= 3 && sym[0] == '"' && sym[sym.size()-1] == '"')
  {
    return true;
  }
  return false;
}

bool is_symbol(const std::string& sym)
{
  for(int i = 0; i < symbol_vector.size(); i++)
  {
    if(symbol_vector[i] == sym)
    {
      return true;
    }
  }

  if(is_string(sym))
  {
    return true;
  }
  
  return false;
}

void get_next_symbol()
{
  std::cout << "Getting next lexeme" << std::endl;

  current_symbol = "";

  bool symbol_found = false;

  while(!symbol_found)
  {
    if(get_char())
    {
      current_symbol += current_char;
      if(current_symbol == " " || current_symbol == "\n")
      {
        current_symbol = "";
      }
      else
      {
        if(is_symbol(current_symbol))
        {
          symbol_found = true;
        }
      }
    }
    else
    {
      break;
    }
  }
  std::cout << "<<< Obtained symbol: " << current_symbol << std::endl;
}

bool accept(const std::string& symbol)
{
  std::cout << "Accept" << std::endl;
  std::cout << "S: " << symbol << std::endl;
  std::cout << "Current: " << current_symbol << std::endl;
  if(current_symbol == symbol)
  {
    get_next_symbol();
    return true;
  }
  return false;
}

bool accept(int symbol_id)
{
  std::cout << "Accepting by id: " << symbol_id << std::endl;
  std::cout << "Current: " << current_symbol << std::endl;
  std::cout << is_string(current_symbol) << std::endl;
  std::cout << "Symbol id: " << symbol_id << std::endl;
  if(is_string(current_symbol) && symbol_id == string_symbol_id)
  {
    get_next_symbol();
    return true;
  }
  return false;
}

bool lbrace_symbol()
{
  std::cout << "+++ lbrace symbol" << std::endl;
  if(accept(l_lbrace))
  {
    return true;
  }
  return false;
}

bool rbrace_symbol()
{
  std::cout << "+++ rbrace symbol" << std::endl;
  if(accept(l_rbrace))
  {
    return true;
  }
  return false;
}

bool string_symbol()
{
  std::cout << "+++ string symbol" << std::endl;
  if(accept(string_symbol_id))
  {
    return true;
  }
  return false;
}

bool key_symbol()
{
  std::cout << "+++ Key symbol" << std::endl;
  return string_symbol();
}

bool colon_symbol()
{
  std::cout << "+++ Colon symbol" << std::endl;
  if(accept(l_colon))
  {
    return true;
  }
  return false;
}

bool value_symbol()
{
  std::cout << "+++ Value Symbol" << std::endl;
  return string_symbol();
}

bool dict_entry_symbol()
{
  std::cout << "+++ dict entry symbol" << std::endl;
  if(key_symbol())
  {
    if(colon_symbol())
    {
      if(value_symbol())
      {
        return true;
      }
    }
  }
  return false;
}

bool dict_entry_list_symbol()
{
  std::cout << "+++ dict entry list symbol" << std::endl;
  if(dict_entry_symbol())
  {
    std::cout << "+++ comma symbol" << std::endl;
    if(accept(l_comma))
    {
      std::cout << "--- level deeper " << std::endl;
      return dict_entry_list_symbol();
    }
    else
    {
      return true;
    }
  }
  std::cout << "--- false from dict entry list" << std::endl;
  return false;
}

bool dictionary_symbol()
{
  std::cout << "+++ dictionary symbol" << std::endl;
  bool success = true;
  success &= lbrace_symbol();
  success &= dict_entry_list_symbol();
  success &= rbrace_symbol();
  return success;
}

void print_current_char()
{
  std::cout << current_char << std::endl;
}

bool start_token()
{
  symbol_vector.push_back(l_lbrace);
  symbol_vector.push_back(l_rbrace);
  symbol_vector.push_back(l_colon);
  symbol_vector.push_back(l_comma);

  get_next_symbol();
  bool success = true;

  success = dictionary_symbol();

  return success;
}

bool char_token()
{
  get_char();
  if(current_char == 'e')
  {
    char_token();
  }
  else if(current_char == 'l')
  {
    char_token();
  }
}

bool space_token()
{
  get_char();
  if(current_char == ' ')
  {
    return true;
  }
  return false;
}

int main(int argc, char* argv[])
{
  if(argc != 2)
  {
    std::cout << "Please provide a filename" << std::endl;
  }
  else
  {
    infile.open(argv[1]);
    if(infile.is_open())
    {
      if(start_token())
      {
        std::cout << "--- Success" << std::endl;
      }
      else
      {
        std::cout << "--- Failed" << std::endl;
      }
    }
  }

  return 0;
}
