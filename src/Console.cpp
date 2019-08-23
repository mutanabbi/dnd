#include <readline/readline.h>
#include <readline/history.h>
#include <Console.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cassert>

Console::cmd_status Console::operator()() const
{
  char* line = ::readline(m_prompt.c_str());
  if (!(line && *line))
    return cmd_status::OK;
  add_history(line);
  std::string cmd(line);
  free(line);
  return execute_command(std::move(cmd));
}

Console::cmd_status Console::execute_command(std::string&& cmd) const
{
  assert("At least cmd name should exist" && !cmd.empty());
  std::stringstream ss(std::move(cmd));
  std::vector<std::string> args;
  std::copy(
      std::istream_iterator<std::string>(ss)
    , std::istream_iterator<std::string>()
    , std::back_inserter(args)
  );
  if (args[0] == "exit" || args[0] == "quit")
    return cmd_status::QUIT;
  auto it = m_commands.find(args[0]);
  if (it == m_commands.end())
  {
    if (m_default_handler)
    {
      m_default_handler(std::move(args));
      return cmd_status::OK;
    }
    return cmd_status::NOT_REGISTRED;
  }
  it->second(std::move(args));
  return cmd_status::OK;
}

