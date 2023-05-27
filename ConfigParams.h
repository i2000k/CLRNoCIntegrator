#pragma once
#include <string>
struct ConfigParams {
	int nocSize;
	int dataWidth;
	int payloadWidth;
	std::string coreName;
	std::string routerName;
	bool generateIntegrationTable;
	ConfigParams(const int& nocSize, const int& dataWidth, const int& payloadWidth,
		const std::string& coreName, const std::string& routerName, bool generateIntegrationTable) {
		this->nocSize = nocSize;
		this->dataWidth = dataWidth;
		this->payloadWidth = payloadWidth;
		this->coreName = coreName;
		this->routerName = routerName;
		this->generateIntegrationTable = generateIntegrationTable;
	}
	ConfigParams() {
		this->nocSize = 0;
		this->dataWidth = 0;
		this->payloadWidth = 0;
		this->generateIntegrationTable = true;
		this->coreName = "";
		this->routerName = "";
	}
};
