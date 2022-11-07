#include <iostream>
#include "dumper.hpp"

int main()
{
	std::string ip;
	std::cout << "Enter an IP: ";
	std::cin >> ip;

	API_IP api = GetIPInfo(ip);

	std::cout << "[IP]\t" << api.ip << std::endl;
	std::cout << "[STATUS]\t" << api.status << std::endl;
	std::cout << "[COUNTRY]\t" << api.country << std::endl;
	std::cout << "[COUNTRY CODE]\t" << api.countryCode << std::endl;
	std::cout << "[REGION]\t" << api.region << std::endl;
	std::cout << "[REGION NAME]\t" << api.regionName << std::endl;
	std::cout << "[CITY]\t" << api.city << std::endl;
	std::cout << "[ZIP CODE]\t" << api.zipcode << std::endl;
	std::cout << "[LAT]\t" << api.lat << std::endl;
	std::cout << "[LON]\t" << api.lon << std::endl;
	std::cout << "[TIME ZONE]\t" << api.timezone << std::endl;
	std::cout << "[ISP]\t" << api.isp << std::endl;
	std::cout << "[ORG]\t" << api.org << std::endl;
	std::cout << "[AS]\t" << api.as << std::endl;
	std::cout << "[REVERSE]\t" << api.reverse << std::endl;
	std::cout << "[MOBIELE?]\t" << api.mobile << std::endl;
	std::cout << "[PROXY?]\t" << api.proxy << std::endl;
	std::cout << "[HOSTING?]\t" << api.hosting << std::endl;

	system("pause");
	return 0;
}