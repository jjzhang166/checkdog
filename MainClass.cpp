/*
 * MainClass.cpp
 *
 *  Created on: Jun 16, 2012
 *      Author: zhangbo
 */

#include <cpputils/Util.h>
#include <iostream>
#include <string>
#include <cpputils/Properties.h>
using namespace std;

#define REMOTE_IP "192.168.0.100"
#define REMOTE_PORT 8088
#define REMOTE_PATH "/bank/reboot.txt"
#define TIME_SLEEP 1*60*1000

int main(int argc, char* argv[]) {
	Properties property;
	property.SafeLoad(Util::GetCurrentPath() + "\\checkdog.cfg");
//	Logger::SetDefault(Util::GetCurrentPath() + "\\checkdog.log", Logger::LOG_DEBUG);
//	Logger::Default()->Debug(Util::GetCurrentPath());
//	Logger::Default()->Debug(property.GetString("REMOTE_HOST"));
//	Logger::Default()->Debug(property.GetString("REMOTE_PORT"));
//	Logger::Default()->Debug(property.GetString("REMOTE_PATH"));

	string reboot = Util::GetCurrentPath() + "\\reboot.txt";
	string old = Util::ReadFile(reboot, 36);
	while (true) {
		if (Util::Download(property.GetString("REMOTE_IP", REMOTE_IP),
				property.GetString("REMOTE_PATH", REMOTE_PATH),
				property.GetInteger("REMOTE_PORT", REMOTE_PORT), reboot)) {
			string now = Util::ReadFile(reboot, 36);
			if (old != now) {
				Util::Reboot();
			}
		}
		Sleep(property.GetInteger("TIME_SLEEP", TIME_SLEEP));
	}

	return (0);
}
