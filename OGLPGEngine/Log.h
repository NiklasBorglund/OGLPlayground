//Log.h
//A simple log
#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include "Uncopyable.h"
#include <fstream>
#include <ctime>
#include <string>

#define ACTIVE_LOG
#define LOG(message) Log::GetLog().LogMessage(message)
#define LOG_WARNING(message) Log::GetLog().LogWarning(message)
#define LOG_ERROR(message) Log::GetLog().LogError(message)

class Log: private Uncopyable
{
public:
	static Log& GetLog()
	{
		static Log thisLog;
		return thisLog;
	}
	void LogMessage(std::string message){WriteMessage(MESSAGE, message);}
	void LogWarning(std::string message){WriteMessage(WARNING, message);}
	void LogError(std::string message){WriteMessage(ERROR, message);}
private:
	enum LogType
	{
		MESSAGE = 1,
		WARNING = 2,
		ERROR = 3,
	};
	std::ofstream _myFile;

	Log(){Initialize();}
	~Log(){Shutdown();}

	void Initialize()
	{
#ifdef ACTIVE_LOG
		_myFile.open("../Logfile.html");
		_myFile << "<html><h3>LOG - " << GetCurrentTime() << "</h3><table border='1'>";
#endif
	}
	void WriteMessage(LogType type, std::string message)
	{
#ifdef ACTIVE_LOG
		_myFile << "<tr>";
		if(type == ERROR)
		{
			_myFile << "<td bgcolor='#FF6347'>ERROR</td>";
		}
		else if(type == WARNING)
		{
			_myFile << "<td bgcolor='#FFFF7E'>WARNING</td>";
		}
		else
		{
			_myFile << "<td bgcolor='#FFFFFF'>MESSAGE</td>";
		}

		//Log the time
		_myFile << "<td>" << GetCurrentTime() << "</td>";

		//Log the message
		_myFile << "<td>" << message << "</td>";

		_myFile << "</tr>";
		_myFile.flush();
#endif
	}
	void Shutdown()
	{
#ifdef ACTIVE_LOG
		_myFile << "</table>";
		_myFile << "Log closed at: " << GetCurrentTime() << "</html>";
		_myFile.close();
#endif
	}
	std::string GetCurrentTime()
	{
		time_t rawtime;
		struct tm timeInfo;
		char buffer [80];

		time ( &rawtime );
		localtime_s(&timeInfo, &rawtime );

		strftime (buffer,80,"%H:%M:%S",&timeInfo);

		std::string thisTime(buffer);
		return thisTime;
	}
};
#endif //LOG_H_INCLUDED