#include "json/json.h"
#include <iostream>

int main() {
	const std::string rawJson = R"({"Age": 20, "Name": "colin"})";
	const auto rawJsonLength = static_cast<int>(rawJson.length());
	constexpr bool shouldUseOldWay = false;
	JSONCPP_STRING err;
	Json::Value root;
	
	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root, &err))
	{
		std::cout << "error" << "\n";
		return EXIT_FAILURE;
	}
	
	const std::string name = root["Name"].asString();
	const int age = root["Age"].asInt();

	std::cout << root << "\n"; 

	Json::Value json;
	Json::Value meta;
	json["marks"] = 34;
	json["name"] = "Goh";
	meta["lab"] = 9.5;
	meta["subject"] = "Math";
	json["lab"] = meta;

	std::cout << json << "\n";

	Json::StreamWriterBuilder jsonBuild;
	const std::string json_file = Json::writeString(jsonBuild, json);
	std::cout << "\n" << json_file << "\n";

	Json::Value student;
	Json::CharReaderBuilder build3;
	const std::unique_ptr<Json::CharReader> readerStu(build3.newCharReader());
	if (!readerStu->parse(json_file.c_str(), json_file.c_str() + json_file.length(), &student, &err))
	{
		std::cout << "error" << "\n";
		return EXIT_FAILURE;
	}
	std::cout << "\n" << student << "\n" << student["lab"] << "\n";
	
	std::cin.get();
}
