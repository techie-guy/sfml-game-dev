#pragma once

#include <string>

class Action
{
public:
    std::string m_name;
    std::string m_type;

    Action();
    Action(const std::string& name, const std::string& type) : m_name(name), m_type(type) {}

    const std::string& name() const { return m_name; }
    const std::string& type() const { return m_type; }
};