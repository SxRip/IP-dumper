/*___ ___   ___        __  __ ___  __ ___ 
 |_ _| _ \ |   \| | | |  \/  | _ \ __| _ \
  | ||  _/ | |) | |_| | |\/| |  _/ _||   /
 |___|_|   |___/ \___/|_|  |_|_| |___|_|_\
 
 THE PROGRAM USE http://ip-api.com/ API and CURL.
 CREATED BY SxRip.	  
*/



#pragma once
#include <string>
#include <curl/curl.h>
#pragma warning(disable : 26812)

struct API_IP
{
	std::string ip;
	std::string status;
	std::string country;
	std::string countryCode;
	std::string region;
	std::string regionName;
	std::string city;
	std::string zipcode;
	std::string lat, lon;
	std::string timezone;
	std::string isp;
	std::string org;
	std::string as;
	std::string reverse;

	bool mobile;
	bool proxy;
	bool hosting;
};

std::string _Parse_callback(const std::string& _Str, std::string _Find, bool _NonStr = false)
{
	std::string result;
	char expr;

	if (_NonStr)
	{
		_Find.append("\":");
		expr = ',';
	}
	else
	{
		_Find.append("\":\"");
		expr = '\"';
	}
	size_t it = _Str.find(_Find);

	if (it == std::string::npos)
		return {};

	it += _Find.size();

	for (; _Str[it] != expr; ++it)
		result.push_back(_Str[it]);
	return result;
}

API_IP ParseResponce(const std::string& _Str)
{
	API_IP API{};

	API.ip = _Parse_callback(_Str, "query");
	API.status = _Parse_callback(_Str, "status");
	API.country = _Parse_callback(_Str, "country");
	API.countryCode = _Parse_callback(_Str, "countryCode");
	API.region = _Parse_callback(_Str, "region");
	API.regionName = _Parse_callback(_Str, "regionName");
	API.city = _Parse_callback(_Str, "city");
	API.zipcode = _Parse_callback(_Str, "zip");
	API.lat = _Parse_callback(_Str, "lat", true);
	API.lon = _Parse_callback(_Str, "lon", true);
	API.timezone = _Parse_callback(_Str, "timezone");
	API.isp = _Parse_callback(_Str, "isp");
	API.org = _Parse_callback(_Str, "org");
	API.as = _Parse_callback(_Str, "as");
	API.reverse = _Parse_callback(_Str, "reverse");

	if (_Parse_callback(_Str, "mobile", true) == "true")
		API.mobile = true;

	if (_Parse_callback(_Str, "proxy", true) == "true")
		API.proxy = true;

	if (_Parse_callback(_Str, "hosting", true) == "true")
		API.hosting = true;

	return API;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	(static_cast<std::string*>(userp))->append(static_cast<const char* const>(contents), size * nmemb);
	return size * nmemb;
}

API_IP GetIPInfo(const std::string& ip)
{
	CURL* curl = curl_easy_init();

	if (!curl)
		return {};

	std::string request = "http://ip-api.com/json/" + ip + "?fields=17039359";
	std::string response;

	curl_easy_setopt(curl, CURLoption::CURLOPT_URL, request.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	curl_easy_setopt(curl, CURLOPT_HTTPGET);
	CURLcode code = curl_easy_perform(curl);

	if (code != CURLE_OK)
		return {};

	curl_easy_cleanup(curl);
	curl = nullptr;

	return ParseResponce(response);
}