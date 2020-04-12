#pragma once

#include <unordered_map>
#include <memory>
#include <functional>

#include "core.h"
#include "fwd.h"

namespace lwlog
{
	class LWLOG_API registry
	{
		registry(const registry&) = delete;
		registry(registry&&) = delete;
		registry& operator=(const registry&) = delete;
		registry& operator=(registry&&) = delete;

	public:
		static registry& instance();
		void register_logger(interface::logger_ptr logger);
		void set_automatic_registry(bool automatic);
		void drop(std::string_view logger_name);
		void drop_all();
		void apply_to_all(const std::function<void(interface::logger_ptr)>& fn);
		inline bool is_registry_automatic();

		interface::logger_ptr get(std::string_view logger_name);
		std::unordered_map<std::string, interface::logger_ptr> loggers();
		std::shared_ptr<interface::logger> default_logger();

	private:
		registry() = default;

	private:
		bool m_automatic_registry{ true };
		std::unordered_map<std::string, interface::logger_ptr> m_loggers;
		static std::shared_ptr<interface::logger> m_default_logger;
	};
}
