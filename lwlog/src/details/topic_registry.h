#pragma once

#include <stack>
#include <string>

#include "configuration.h"

namespace lwlog::details
{
	struct topic_registry_base
	{
		virtual std::string_view current_topic() const = 0;
		virtual std::string full_topic() const = 0;
	};

	template<typename TopicPolicy>
	class topic_registry : public topic_registry_base {};

	template<>
	class topic_registry<enable_topics> : public topic_registry_base
	{
	public:
		void set_separator(std::string_view separator);
		void start_topic(std::string_view topic);
		void end_topic();

		std::string_view current_topic() const;
		std::string full_topic() const;
		
	private:
		std::string_view m_current_topic;
		std::string_view m_separator;
		std::vector<std::string_view> m_topics;
	};

	template<>
	struct topic_registry<disable_topics> : public topic_registry_base
	{
		void set_separator(std::string_view);
		void start_topic(std::string_view);
		void end_topic();

		std::string_view current_topic() const;
		std::string full_topic() const;
	};
}

#include "topic_registry_impl.h"