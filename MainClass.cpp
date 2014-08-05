/*
 * MainClass.cpp
 *
 *  Created on: Jun 16, 2012
 *      Author: zhangbo
 */

#include <cpputils/Util.h>
#include <iostream>
#include <string>
using namespace std;

#define LOCAL_PATH "C:\\Program Files\\bank\\reboot.txt"
#define REMOTE_PATH "/bank/reboot.txt"
#define TIME_SLEEP 1*60*1000
#define REMOTE_IP "192.168.0.100"
#define REMOTE_PORT 8088

int main(int argc, char* argv[]) {
	string reboot = LOCAL_PATH;
	string old = Util::ReadFile(reboot, 36);
	while (true) {
		if (Util::Download(REMOTE_IP, REMOTE_PATH, REMOTE_PORT, reboot)) {
			string now = Util::ReadFile(reboot, 36);
			if (old != now) {
				Util::Reboot();
			}
		}
		Sleep(TIME_SLEEP);
	}

	return (0);
}
