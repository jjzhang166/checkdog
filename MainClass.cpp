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

#define REMOTE_HOST "192.168.0.100"
#define REMOTE_PORT 8088
#define REMOTE_PATH "/bank/reboot.txt"
#define INTERVAL 1*60*1000

int main(int argc, char* argv[]) {
	Properties property;
	property.SafeLoad(Util::GetCurrentPath() + "\\checkdog.cfg");

	string reboot = Util::GetCurrentPath() + "\\reboot.txt";
	string old = Util::ReadFile(reboot, 36);
	while (true) {
		if (Util::Download(property.GetString("host", REMOTE_HOST),
				property.GetString("path", REMOTE_PATH),
				property.GetInteger("port", REMOTE_PORT), reboot)) {
			string now = Util::ReadFile(reboot, 36);
			if (old != now) {
				Util::Reboot();
			}
		}
		Sleep(property.GetInteger("interval", INTERVAL));
	}

	return (0);
}
