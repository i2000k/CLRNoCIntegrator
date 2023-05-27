#pragma once
#include <string>
class IntegrationGenerator
{
public:
    int generate_assignment_table_file(const std::string& filepath, int n, int sc, int s[]);

    int generate_intermediate(
        const std::string& filename, 
        const int& data_width,
        const int& payload_width, 
        const std::string& coreName, 
        const std::string& routerName);

    int registerIP(
        const std::string& filename,
        const std::string& adapterName,
        const std::string& moduleName,
        const std::string& instName,
        const std::string& routerName,
        const int& data_width,
        const int& payload_width,
        const int& nocSize);
};

