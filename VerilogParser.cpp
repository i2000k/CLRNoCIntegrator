#include "VerilogParser.h"
#include <iostream>
#include <fstream>
#include <iostream>

std::string VerilogParser::getModuleContent(const std::string& input, const std::string& firstWord, const std::string& secondWord)
{
	std::size_t firstPos = input.find(firstWord);
	if (firstPos == std::string::npos)
	{
		// First word not found
		return "";
	}

	std::size_t secondPos = input.find(secondWord, firstPos + firstWord.length()) + secondWord.length();
	if (secondPos == std::string::npos)
	{
		// Second word not found
		return "";
	}

	std::size_t startPos = firstPos + firstWord.length();
	std::size_t length = secondPos - startPos;

	return input.substr(startPos, length);
}

Module* VerilogParser::parseModule(const string& content, Module* module)
{
	string content_str(content);
	string strip_content(content);
	string module_content(content);
	if (module_content.size() == 0)
	{
		throw std::runtime_error("The file is empty");
	}


	//regex module_regex(R"(^(?!\/\/)\bmodule\s+(\w+)\s*)"); // CORRECT
	//regex port_regex(R"(^(?!\/\/)\s*(input|inout|output)\s*(reg|wire)?\s*(\[[^\]]+\])?\s*(\w+)\s*([,;])?)"); // CORRECT

	//regex module_decl(R"(^(?!\/\/)module\s+(\w+)\s*(#\s*\(\s*(parameter\s+(\w+)\s*(=\s*(\d+)?)?[,]?\s*)+\))?\s*\((\s*((input|inout|output)\s*(reg|wire)?\s*(\[[^\]]+\])?\s*(\w+)\s*([,])?\s*(?:\/\/.*)?\s*)*)\);(?=[\s\S+]*?endmodule))");
	regex module_decl(R"((?!\/\/)\bmodule\s+(\w+)\s*(#[\s\S+]*?\))?([\s\S+]*?[;])([\s\S+]*?endmodule))");

	//regex parameter_regex(R"((?!parameter)\s+(\w+)\s*=\s*(\d+))");	// CORRECT
	//regex params_string_regex(R"(#\s*\(\s*(parameter\s+(\w+)\s*(=\s*(\d+)?)?[,]?\s*)+\))");
	//regex param_regex(R"(parameter\s+(\w+)\s*(=\s*(\d+))?)");
	//regex macros_regex(R"(^`define (\w+) (\d+))");	// CORRECT
	//regex inst_regex(R"(^(?!\/\/)\s*\b(\w+)\s+(#\((\s*.((\w+)\s*\((\d+)\)+\)\s*)))?(\w+)\s*\((.*)\); )");

	//regex inst_string_regex(R"(^(?!\/\/)\s*(\w+)\s+(#\s*\((\s*.((\w+)\s*\(\s*(\w+)\s*)\)\s*[,]?\s*)+\))?\s*(\w+)\s*\(\s*(.(\w+)\s*\(.*\)[,]?\s*)*\);)");

	auto regex_iter_end = sregex_iterator();
	auto module_decl_iter = sregex_iterator(content_str.begin(), content_str.end(), module_decl);
	//auto module_decl_iter = sregex_iterator(content_str.begin(), content_str.end(), module_decl);
	//if (module_decl_iter == regex_iter_end) {
	//	module_decl_iter = sregex_iterator(content_str.begin(), content_str.end(), module_decl);
	//}
	vector<Module*> localmodules;
	//smatch match;
	//while (regex_search(content_str, match, module_decl)) {
	//	string module_name = match[1];
	//	string params_string = match[2];
	//	string ports_string = match[3];
	//	string module_content = match[4];
	//	vector<ModulePort*>* module_ports = parsePorts(ports_string);
	//	map<string, string>* module_params = parseParams(params_string);
	//	vector<Module*>* instances = parseInstances(module_content);
	//	modules.push_back(Module(module_name, module_ports, module_params));
	//}
	smatch match;
	if (regex_search(content_str, match, module_decl)) {
		string module_name = match[1];
		this->moduleName = match[1];
		string params_string = match[2];
		string ports_string = match[3];
		module_content = match[4];
		//string module_content = module_decl_iter->str(14);

		vector<ModulePort*>* module_ports = parsePorts(ports_string);
		map<string, string>* module_params = parseParams(params_string);
		vector<LocalVar*>* module_locals = parseLocals(module_content);

		module->name = module_name;
		module->ports = module_ports;
		module->params = module_params;
		//module->locals = module_locals;


		for (auto it = module->params->begin(); it != module->params->end(); it++)
		{
			string param_name = it->first;
			string param_value = it->second;
			for (int i = 0; i < module->ports->size(); i++) {
				ModulePort* port = module->ports->at(i);
				smatch param_match;
				if (regex_search(port->width, param_match, regex(param_name))) {
					size_t found = port->width.find(param_name);
					if (found != std::string::npos) {
						port->width.replace(found, param_name.length(), param_value);
					}
				}
			}

			for (int i = 0; i < module->localVars->size(); i++) {
				LocalVar* port = module->localVars->at(i);
				smatch param_match;
				if (regex_search(port->width, param_match, regex(param_name))) {
					size_t found = port->width.find(param_name);
					if (found != std::string::npos) {
						port->width.replace(found, param_name.length(), param_value);
					}
				}
			}

		}
	}

	////main loop
	/*while (module_decl_iter != regex_iter_end) {
		string module_name = module_decl_iter->str(1);
		string params_string = module_decl_iter->str(2);
		string ports_string = module_decl_iter->str(3);
		module_content = module_decl_iter->str(4);
		string module_content = module_decl_iter->str(14);

		vector<ModulePort*>* module_ports = parsePorts(ports_string);
		map<string, string>* module_params = parseParams(params_string);
		Module* module = new Module(module_name, module_ports, module_params);
		localmodules.push_back(module);
		vector<Module*>* instances = parseInstances(module_content);
		++module_decl_iter;
	}
	return localmodules;*/
	return module;
}

vector<ModuleInstance*>* VerilogParser::parseNoCInstances(const string& content) {
	vector<ModuleInstance*>* instances = new vector<ModuleInstance*>();
	regex inst_string_regex(R"(^(?!(\/\/))\s*(?!module|case|if)(\w+)\s*(\w+)\s*\([\s\S+]*?;)");

	regex inst_decl(R"(^(?!(\/\/))\s*(?!module|case|if)(\w+)\s*(#\s*\([\s\S+]*?\))?\s*(\w+)\s*\(([\s\S+]*?;))");
	auto regex_iter_end = sregex_iterator();
	auto instances_iter = sregex_iterator(content.begin(), content.end(), inst_decl);
	//auto regex_iter_end = sregex_iterator();
	////regex inst_regex(R"(\s*(\w+)\s*(#\s*\([\s\S+]*?\))?\s*(\w+)\s*\(([\s\S+]*?;)");
	////regex inst_string_regex(R"(^(?!\/\/)\s*(\w+)\s+(#\s*\((\s*.((\w+)\s*\(\s*(\w+)\s*)\)\s*[,]?\s*)+\))?\s*(\w+)\s*\(\s*(.(\w+)\s*\(.*\)[,]?\s*)*\);)");
	//regex inst_string_regex(R"(^(?!(\/\/))\s*(?!module|case|if)(\w+)\s*(\w+)\s*\([\s\S+]*?;)");

	//regex inst_decl(R"(^(?!(\/\/))\s*(?!module|case|if)(\w+)\s*(#\s*\([\s\S+]*?\))?\s*(\w+)\s*\(([\s\S+]*?;))");
	//auto instances_iter = sregex_iterator(content.begin(), content.end(), inst_decl);

	while (instances_iter != regex_iter_end)
	{
		string inst_module = instances_iter->str(2);
		//string inst_params_string = instances_iter->str(3);
		string inst_name = instances_iter->str(4);
		//string inst_ports_string = instances_iter->str(5);
		map<string, pair<string, string>> inst_module_ports = parseInstancePorts(instances_iter->str(5));
		map<string, string> inst_module_params = parseInstanceParams(instances_iter->str(3));
		/*instances->push_back(new Module(instances_iter->str(1), inst_module_ports, inst_module_params));*/
		++instances_iter;
	}
	return instances;
}

vector<ModulePort*>* VerilogParser::parsePorts(const string& ports_string) {
	vector<ModulePort*>* module_ports = new vector<ModulePort*>();
	regex port_regex(R"(^(?!\/\/)\s*(input|inout|output)\s*(reg|wire)?\s*(\[[^\]]+\])?\s*(\w+)\s*([,;])?)"); // CORRECT
	auto regex_iter_end = sregex_iterator();
	auto port_iter = sregex_iterator(ports_string.begin(), ports_string.end(), port_regex);

	while (port_iter != regex_iter_end) {
		//string port_direction = port_iter->str(1);
		//string port_type = port_iter->str(2);
		//string port_size = port_iter->str(3);
		//string port_name = port_iter->str(4);
		string widthStr = port_iter->str(3);
		smatch match;
		string width;
		if (regex_search(widthStr, match, regex(R"(\s*(\w+)\s*([-]\s*(\w+))?\s*:)"))) {
			width = match[1];
		}
		if (width.empty()) {
			width = "1";
		}
		else {
			try {
				int iWidth = stoi(width);
				iWidth++;
				width = to_string(iWidth);
			}
			catch (exception& e) { }
		}
		module_ports->push_back(new ModulePort(port_iter->str(4), port_iter->str(1), port_iter->str(2), width));
		++port_iter;
	}

	return module_ports;
}

map<string, string>* VerilogParser::parseParams(const string& param_string) {
	map<string, string>* module_params = new map<string, string>();
	regex param_regex(R"(parameter\s+(\w+)\s*(=\s*(\d+))?)");
	auto regex_iter_end = sregex_iterator();
	auto param_iter = sregex_iterator(param_string.begin(), param_string.end(), param_regex);

	while (param_iter != regex_iter_end) {
		//string param_name = param_iter->str(1);
		//string param_value = param_iter->str(3);
		//pair<string, string> param = make_pair(param_iter->str(1), param_iter->str(3));
		module_params->insert(make_pair(param_iter->str(1), param_iter->str(3)));
		++param_iter;
	}


	return module_params;
}

vector<LocalVar*>* VerilogParser::parseLocals(const string& module_content) {
	vector<LocalVar*>* locals = new vector<LocalVar*>();
	regex local_regex(R"((?!\s*\/\/)(wire|reg)\s*(\[([^\]]+)\])?\s*(\w+)\s*(\[([^\]]+)\])?)"); // CORRECT
	auto regex_iter_end = sregex_iterator();
	auto local_iter = sregex_iterator(module_content.begin(), module_content.end(), local_regex);

	while (local_iter != regex_iter_end) {
		smatch arr_match;
		string width_string = local_iter->str(3);
		string size_string = local_iter->str(4);
		string width;
		if (regex_search(width_string, arr_match, regex(R"(\s*(\w+)\s*([-]\s*(\w+))?\s*:)"))) {
			width = arr_match[1];
		}
		if (width == "") {
			width = "1";
		}
		string size;
		if (regex_search(size_string, arr_match, regex(R"(\s*(\w+)\s*([-]\s*(\w+))?\s*:)"))) {
			size = arr_match[1];
		}
		if (size == "") {
			size = "1";
		}

		locals->push_back(new LocalVar(local_iter->str(4), width, local_iter->str(1), size));
		++local_iter;
	}

	return locals;

}



map<string, pair<string, string>> VerilogParser::parseInstancePorts(const string& ports_string) {
	map<string, pair<string, string>> ports;
	regex inst_port_regex(R"((\s*((\.\w+)\s*\(\s*(\w+)\s*(\[\s*(.*)?\]\s*)?\)[,]?)))");
	smatch match;
	while (regex_search(ports_string, match, inst_port_regex)) {
		string port_name = match[3];
		string port_wire = match[4];
		string port_width = match[5];
		pair<string, string> port = make_pair(port_wire, port_width);
		ports.insert(make_pair(port_name, port));
	}
	return ports;
}

map<string, string> VerilogParser::parseInstanceParams(const string& params_string) {
	map<string, string> params;
	regex inst_param_regex;
	smatch match;
	while (regex_search(params_string, match, inst_param_regex)) {
		string param_name = match[1];
		string param_value = match[2];
		params.insert(make_pair(param_name, param_value));
	}
	return params;
}

bool VerilogParser::parseMacros(const char filename[])
{
	map<string, int> macros;
	regex macros_regex(R"(^`define (\w+) (\d+))"); // CORRECT
	smatch macro_match;

	ifstream infile;
	infile.open(filename, ios::in);
	// Open the file in input and output mode
	if (!infile.is_open())
	{
		throw runtime_error("Could not open file");
	}
	std::string content;

	// Read the contents of the file
	while (getline(infile, content))
	{
		if (regex_search(content, macro_match, macros_regex))
		{
			string macro_name = macro_match.str(1);
			string macro_value_str = macro_match.str(2);
			int macro_value;
			try
			{
				macro_value = stoi(macro_value_str);
				macros[macro_name] = macro_value;
			}
			catch (exception& e)
			{
				// parse int error: ignore
			}
		}
	}

	infile.close();

	// ofstream ofile(filename, ios::out);
	// if (!ofile.is_open()) {
	//	throw runtime_error("Could not open file");
	// }
	//// Read the contents of the file
	// while (getline(infile, content)) {
	//	for(auto & m : macros) {
	//		int found = content.find(m.first);
	//		if (found != string::npos) {
	//			content.replace(found, m.first.length(), to_string(m.second));
	//		}
	//	}
	// }
}

int VerilogParser::getModulesCount() const
{
	return modulesCount;
}

void VerilogParser::printModules() const
{
	for (auto module : modules)
	{
		cout << "Module name: "
			<< "\t" << module->name << endl;
		cout << "Module ports: " << endl;
		for (int i = 0; i < module->ports->size(); i++)
		{
			cout << "\t" << module->ports->at(i)->direction << "\t" << module->ports->at(i)->width << "\t" << module->ports->at(i)->name << endl;
		}
		cout << "Module Params: " << endl;
		for (auto pair : *(module->params))
		{
			cout << "\t" << pair.first << "\t" << pair.second << endl;
		}
	}
}

int VerilogParser::parseRouter(const string& content) {
	return 0;
}

Noc* VerilogParser::parseNoc(const char content[]) {
	string content_str(content);
	string strip_content(content);
	string module_content(content);
	if (module_content.size() == 0)
	{
		throw std::runtime_error("The file is empty");
	}

}

VerilogParser::VerilogParser()
{
	modulesCount = 0;
	/*vector<Module *> modules();*/
}

VerilogParser::~VerilogParser()
{
	for (Module* module : modules)
	{
		delete module;
	}
}
