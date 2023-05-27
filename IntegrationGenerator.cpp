#include "IntegrationGenerator.h"
#include <fstream>
#include <cmath>
#include <bitset>



int IntegrationGenerator::generate_assignment_table_file(const std::string& filePath, int n, int sc, int s[])
{

    size_t lastSlashPos = filePath.find_last_of("/\\");
    std::string cwd = filePath.substr(lastSlashPos + 1);

    std::ofstream file(cwd + "\\assignments_table.txt");

    if (!file.is_open())
    {
        return -1;
    }

    file << "Index\trminR\trmaxR\trminL\trmaxR\n";

    for (int i = 0; i < n; i++)
    {
        file << i << ":\t";
        // right
        for (int j = 0; j < sc; j++)
        {
            file << (i + s[j]) % n << "\t";
        }
        // left
        for (int j = 0; j < sc; j++)
        {
            file << (n + i - s[j]) % n << "\t";
        }
        file << "\n";
    }

    file.close();
    return 0;
}


int IntegrationGenerator::generate_intermediate(
    const std::string& filename,
    const int& data_width, 
    const int& payload_width, 
    const std::string& coreName = "ext_ip",
    const std::string& routerName = "ext_ip")
{

    //std::filesystem::path currentPath = std::filesystem::current_path();

    /*std::string fileName = "converter.v";*/

    //std::filesystem::path filePath = currentPath / filename;

    std::ofstream file(filename);

    if (!file.is_open())
    {
        return -1;
    }

    int num_of_chunks = data_width / payload_width;

    size_t lastSlashPos = filename.find_last_of("/\\");
    std::string moduleName = filename.substr(lastSlashPos + 1);
    size_t lastDotPos = moduleName.find_last_of(".");
    if (lastDotPos != std::string::npos) {
        moduleName = moduleName.substr(0, lastDotPos);
    }

    file << "module ext_" << moduleName << " (\n";
    file << "\tclk,\n";
    file << "\trst,\n";
    file << "\tf_c,\n";
    file << "\tto_c,\n";
    file << "\tf_r,\n";
    file << "\tto_r,\n";
    file << "\tr_name\n";
    file << ");\n";
    file << "\n";

    file << "\tinput clk, rst;\n";
    file << "\treg wr_en, rd_en;\n";
    file << "\tinput [" << data_width - 1 << ":0] f_c; \n";
    file << "\tinput [" << payload_width << ":0] f_r;\n";
    file << "\tinput [3:0] r_name;\n";
    file << "\toutput reg[" << data_width - 1 << ":0] to_c; \n";
    file << "\toutput reg[" << payload_width + 8 << ":0] to_r;\n";
    file << "\treg empty, full;\n";
    file << "\treg [" << log2(num_of_chunks) << ":0] counter;\n";
    file << "\treg [" << log2(num_of_chunks) << ":0] rd_ptr_r;\n";
    file << "\treg [" << payload_width + 8 << ":0] mem[" << num_of_chunks - 1 << ":0];\n";
    file << "\treg [" << data_width - 1 << ":0] suppl_data;\n";
    file << "\treg [" << log2(num_of_chunks) << ":0] suppl_counter;\n";

    file << "\talways @(counter) begin\n";
    file << "\t\tempty <= (counter == 0);\n";
    file << "\t\tfull <= (counter == " << num_of_chunks << ");\n";
    file << "\tend\n\n";


    file << "\talways @(posedge clk) begin\n";
    file << "\t\tif (f_c != 0 && empty) begin\n";
    file << "\t\t\tempty <= 0;\n";
    file << "\t\t\tcounter <= " << num_of_chunks << ";\n";

    int count = num_of_chunks - 1;
    for (int i = 0; i < num_of_chunks; i++) {
        file << "\t\t\tmem[" << count-- << "] <= {1'b1, 4'b0, r_name, f_c[" << (i + 1) * payload_width - 1 
            << ":" << i * payload_width << "] }; \n";
    }

    file << "\t\tend\n";
    file << "\tend\n\n";

    file << "\talways @(posedge clk) begin\n";
    file << "\t\tif (!empty) begin\n";
    file << "\t\t\tto_r <= mem[rd_ptr_r];\n";
    file << "\t\t\trd_ptr_r <= rd_ptr_r + 1;\n";
    file << "\t\t\tcounter <= counter - 1;\n";
    file << "\t\tend\n";
    file << "\t\telse begin\n";
    file << "\t\t\tto_r <= 0;\n";
    file << "\t\t\trd_ptr_r <= 0;\n";
    file << "\t\tend\n";
    file << "\tend\n";


    file << "\talways @(posedge clk) begin\n";
    file << "\t\tif (f_r != 0) begin\n";
    file << "\t\t\tsuppl_data <= (suppl_data << " << payload_width << ") + f_r[" << payload_width - 1 << ":0]; \n";
    file << "\t\t\tsuppl_counter <= suppl_counter + 1;\n";
    file << "\t\tend\n";
    file << "\t\tif (suppl_counter == " << num_of_chunks << ")begin\n";
    file << "\t\t\tsuppl_counter <= 0;\n";
    file << "\t\t\tsuppl_data <= 0;\n";
    file << "\t\t\tto_c <= suppl_data;\n";
    file << "\t\tend else begin\n";
    file << "\t\t\tto_c <= 0;\n";
    file << "\t\tend\n";
    file << "\tend\n\n";
    file << "endmodule\n";
    file.close();
    return 0;
}

int IntegrationGenerator::registerIP(
    const std::string& filename, 
    const std::string& adapterName,
    const std::string& moduleName,
    const std::string& instName,
    const std::string& routerName,
    const int& data_width,
    const int& payload_width,
    const int& nocSize) {


    std::fstream file(filename, std::ios::in | std::ios::out);


    if (file.is_open()) {
        std::string line;
        std::streampos linePosition = 0;
        std::string wordToFind = "endmodule";

        std::string word;
        std::streampos previousWordPosition = 0;
        while (file >> word) {
            if (word == wordToFind) {
                file.seekg(previousWordPosition, std::ios::beg);
                break;
            }

            previousWordPosition = file.tellg();
        }

        file << "\n";
        file << "\n";
        file << "\twire [3:0] r_name;\n";
        file << "\twire [" << data_width - 1 << ":0] cpu_c;\n";
        file << "\twire [" << data_width - 1 << ":0] c_cpu;\n";
        file << "\twire [" << payload_width + 8 << ":0] c_r;\n";
        file << "\twire [" << payload_width + 8 << ":0] r_c;\n";


        file << "\t"<< adapterName << " " << adapterName << "_inst (\n";
        file << "\t\t.clk(clk),\n";
        file << "\t\t.rst(!rst_n),\n";
        file << "\t\t.f_c(cpu_c),\n";
        file << "\t\t.to_r(c_r),\n";
        file << "\t\t.f_r(r_c),\n";
        file << "\t\t.to_c(c_cpu),\n";
        file << "\t\t.r_name(r_name)\n";
        file << "\t);\n";

        file << "\t" << moduleName << " " << instName << "_" << nocSize << " (";
        file << ".clk(clk), .rst_n(rst_n), .inject(c_cpu), eject(cpu_c), .router_name(r_name));\n";
        file << "\n";

        std::bitset<4> binary(nocSize - 1);

        file << "\t" << routerName << " " << "r" << nocSize << " (.clk(clk), .rst_n(rst_n), .router_name(4'b" 
            << binary.to_string() << "), .in_free(c_r), ";
        file << ".in_r1R(r_minL[" << (nocSize - 1 + 2) % (nocSize) << "]), ";
        file << ".in_r2R(r_maxL[" << (nocSize - 1+ 3) % (nocSize) << "]), ";
        file << ".in_r1L(r_minR[" << (nocSize - 1+ nocSize - 2) % (nocSize) << "]), ";
        file << ".in_r2L(r_maxR[" << (nocSize - 1+ nocSize - 3) % (nocSize) << "]), ";

        file << ".out_r1R(r_minR[" << nocSize - 1<< "]), ";
        file << ".out_r2R(r_maxR[" << nocSize - 1<< "]), ";
        file << ".out_r1L(r_minL[" << nocSize - 1<< "]), ";
        file << ".out_r2L(r_maxL[" << nocSize - 1<< "]), ";
        file << ".out_data(r_c));\n";
        file << "endmodule\n";
    }
    else {
        return -1;
    }
    file.close();
    return 0;
}