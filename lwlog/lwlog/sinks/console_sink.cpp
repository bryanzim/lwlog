#include "console_sink.h"

#include "../formatter.h"
#include "../print.h"

namespace lwlog::sinks
{
	console_sink::console_sink()
		: m_pattern("[%d, %x] [%l] [%n]: %v")
		, m_level(level::all)
	{
		set_level_visibility(m_level);
	}

	void console_sink::log(std::string_view message, level log_level)
	{
		if (static_cast<std::underlying_type_t<level>>(m_level)
			& static_cast<std::underlying_type_t<level>>(log_level))
		{
			lwlog::print("{0} \n", formatter::format(m_pattern));
		}
	}

	void console_sink::set_level_visibility(level log_level)
	{
		if (log_level == level::all) {
			m_level = level::info | level::warning
				| level::error | level::critical | level::debug;
		}
		else if (log_level == level::none) {
			m_level = level::none;
		}
		else {
			m_level = log_level;
		}
	}

	void console_sink::set_pattern(std::string_view pattern)
	{
		m_pattern = pattern;
	}
}