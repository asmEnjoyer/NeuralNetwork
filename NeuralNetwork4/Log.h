#pragma once
#include <string>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <chrono>

inline class log
{
	public:
		enum LogLevel
		{
			info	=	0x01,
			warning =	0x02,
			error	=	0x04,
			debug	=	0x08,
			memory	=	0x10
		};

	private:
		short _level = info|warning|error|debug|memory;
		std::mutex _mutex;
	public:
		/// <summary>
		/// Write a log message to the console.
		/// </summary>
		/// <param name="level">The level of the log message</param>
		/// <param name="text">The text of the log message</param>
		void operator()(LogLevel level,std::string text);

		/// <summary>
		/// Write a log message with the log level of info to the console.
		/// </summary>
		/// <param name="text">The text of the log message</param>		
		void operator()(std::string text);

		/// <summary>
		/// Set the level of the log messages that will be written to the console.
		/// </summary>
		/// <param name="level">The level(s) of the log messages that will be shown in console</param>
		void Level(short level);

	private:

		/// <summary>
		/// Write a log message to the console.
		/// </summary>
		/// <param name="text">The text of the log message</param>
		/// <param name="level">The level of the log message</param>
		void LOG(std::string text, LogLevel level);

		/// <summary>
		/// Convert the log level to a string.
		/// </summary>
		/// <param name="level">The level of the log message</param>
		/// <returns>The string representation of the log level</returns>
		std::string logLevelToText(LogLevel);
}Log;

