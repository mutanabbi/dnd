#pragma once

#include <unordered_map>
#include <vector>
#include <string>

class Console
{
public:
  enum class cmd_status : unsigned short
  {
    NOT_REGISTRED, OK, QUIT
  };

  using command_type = std::function<void(std::vector<std::string>)>;

  explicit Console(std::string prompt) : m_prompt(std::move(prompt))
  {
  }

  void register_command(
    const std::string& name,
    command_type cmd
  )
  {
    m_commands[name] = cmd;
  }

  void register_default_handler(
    command_type cmd
  )
  {
    m_default_handler = cmd;
  }

  cmd_status operator()() const;

private:
  cmd_status execute_command(std::string&& cmd) const;

  const std::string m_prompt;
  command_type m_default_handler;
  std::unordered_map<std::string, command_type> m_commands;
};

