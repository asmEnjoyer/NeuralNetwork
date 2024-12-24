#include "Log.h"

void log::operator()(LogLevel level, std::string text)
{
	if ((_level & level) != level||text=="")
		return;
	std::thread thread(&log::LOG,this, text,level);
	thread.detach();
}

void log::operator()(std::string text)
{
	Log(Log.info,text);
}

void log::Level(short level)
{
	_level = level;
}

void log::LOG(std::string text,LogLevel level)
{
	
	std::chrono::system_clock::time_point td = std::chrono::system_clock::now();
	auto td_days = std::chrono::time_point_cast<std::chrono::duration<int, std::ratio<86400>>>(td);
	auto now = td - td_days;
	auto h = std::chrono::duration_cast<std::chrono::hours>(now);
	now -= h;
	auto m = std::chrono::duration_cast<std::chrono::minutes>(now);
	now -= m;
	auto s = std::chrono::duration_cast<std::chrono::seconds>(now);
	now -= s;
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now);

	std::lock_guard<std::mutex> guard(_mutex);

	printf
	(	
		"(%02d:%02d:%02d.%03d) [%s]\b\t %s\n",
		h.count(),
		m.count(),
		(int)s.count(),
		(int)ms.count(),
		logLevelToText(level).c_str(),
		text.c_str()
	);

}

std::string log::logLevelToText(LogLevel level)
{
	std::string ans;
	switch (level)
	{
	case log::info:
		return "\x1B[34mInfo\033[0m";
		break;
	case log::warning:
		return "\x1B[33mWarning\033[0m";
		break;
	case log::error:
		return "\x1B[31mError\033[0m";
		break;
	case log::debug:
		return "\x1B[32mDebug\033[0m";
		break;
	case log::memory:
		return "\x1B[35mMemory\033[0m";
		break;
	default:
		return "Unknown Type";
		break;
	}
}