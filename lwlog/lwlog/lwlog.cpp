#include "lwlog.h"
#include "formatter.h"

namespace lwlog
{
	logger::logger(std::string_view logger_name)
		: m_loggerName(logger_name), m_pattern("[%d, %x] [%l] [%n]: %v"),
		m_logLevelVisibility(log_level::all)
	{
		formatter::update_pattern_data("%n", m_loggerName);

		if (registry::is_registry_automatic() == true)
		{
			registry::register_logger(*this);
		}
	}

	void logger::set_logLevel_visibility(log_level logLevel)
	{
		if (logLevel == log_level::all)
		{
			m_logLevelVisibility = log_level::info | log_level::warning | log_level::error
				| log_level::critical | log_level::debug;
		}
		else if (logLevel == log_level::none)
		{
			m_logLevelVisibility = log_level::none;
		}
		else
		{
			m_logLevelVisibility = logLevel;
		}
	}

	void logger::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}

	void logger::log(std::string_view message, log_level logLevel)
	{
		m_message = message;

		formatter::update_pattern_data("%v", m_message);
		formatter::update_pattern_data("%l", m_logLevel);
		formatter::update_pattern_data("%L", std::string(1, toupper(m_logLevel[0])));

		if (static_cast<std::underlying_type_t<log_level>>(m_logLevelVisibility)
			& static_cast<std::underlying_type_t<log_level>>(logLevel))
		{
			lwlog::print("{0} \n", formatter::format(m_message, m_pattern));
		}
	}

	void logger::info(std::string_view message)
	{
		m_logLevel = "info";
		log(message, log_level::info);
	}

	void logger::warning(std::string_view message)
	{
		m_logLevel = "warning";
		log(message, log_level::warning);
	}

	void logger::error(std::string_view message)
	{
		m_logLevel = "error";
		log(message, log_level::error);
	}

	void logger::critical(std::string_view message)
	{
		m_logLevel = "critical";
		log(message, log_level::critical);
	}

	void logger::debug(std::string_view message)
	{
		m_logLevel = "debug";
		log(message, log_level::debug);
	}
}