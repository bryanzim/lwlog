﻿#pragma once

#include <filesystem>

namespace lwlog::details
{
	class file_writer
	{
	private:
		static constexpr std::uint32_t s_buffer_size{ 8388608 };

	public:
		file_writer() = default;
		file_writer(std::string_view path);
		virtual ~file_writer();

	public:
		void write(std::string_view message);
		void close();
		std::FILE* handle() const;
		std::filesystem::path& filesystem_path();

	private:
		std::FILE* m_file{ nullptr };
		std::filesystem::path m_path;
	};
}