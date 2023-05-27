#pragma once
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

struct ModulePort {
	string name;
	string direction;
	string width;
	ModulePort(const string& name, const string& direction, const string& type, const string& width) : name(name), direction(direction), width(width) {}
};

struct LocalVar {
	string name;
	string width;
	string type;
	string size;
	LocalVar(const string& name, const string& width, const string& type, const string& size) : name(name), width(width), type(type), size(size) {}
};

struct Module {
	string name;
	vector<ModulePort*>* ports;
	map<string, string>* params;
	vector<LocalVar*>* localVars;
	//vector<ModuleInstance*> childs;
	Module() {}
	Module(const string& name, vector<ModulePort*>* ports, map<string, string>* params, vector<LocalVar*>* localVars) :
		name(name),
		ports(ports),
		params(params),
		localVars(localVars) {}
	~Module() {
		for (int i = 0; i < ports->size(); i++) {
			delete ports->at(i);
		}
		delete ports;
		delete params;
		delete localVars;
	}
};

struct ModuleInstance {
	string instName;
	map<string, string>* instParams;
};

struct Noc {
	int routerCount;
	int dataWidth;
	vector<ModuleInstance*> routers;
	Noc(int count, int dataWidth) : routerCount(count), dataWidth(dataWidth) {
		routers = vector<ModuleInstance*>(count);
	}
};


class VerilogParser
{
private:
	int modulesCount;
	vector<Module*> modules;
	std::string getModuleContent(const std::string& input, const std::string& firstWord, const std::string& secondWord);
	vector<ModuleInstance*>* parseNoCInstances(const string& content);
	vector<ModulePort*>* parsePorts(const string& ports_string);
	vector<LocalVar*>* parseLocals(const string& module_content);
	map<string, string>* parseParams(const string& param_string);
	map<string, pair<string, string>> parseInstancePorts(const string& ports_string);
	map<string, string> parseInstanceParams(const string& params_string);
public:
	string moduleName;
	Module* parseModule(const string& content, Module* module);
	int parseRouter(const string& content);
	Noc* parseNoc(const char content[]);
	bool parseMacros(const char filename[]);
	void printModules() const;
	int getModulesCount() const;
	VerilogParser();
	~VerilogParser();
};


