#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

bool moduleFileUploaded;

[STAThreadAttribute]
int main(cli::array<String^> ^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	CLRNoCIntegrator::MyForm form;
	Application::Run(% form);
}

void CLRNoCIntegrator::MyForm::ProcessModuleFileUpload(
	String^ selectedFile, 
	std::string* fileContent, 
	CLRNoCIntegrator::MyForm^ myForm) {

	if (!selectedFile->IsNullOrEmpty(selectedFile))
	{
		myForm->button2->Enabled = true;
		myForm->moduleFileUploaded = true;
		myForm->routerFileUploaded = false;
		myForm->nocFileUploaded = false;

		MessageBox::Show("Файл: " + selectedFile + " Успешно загружен.");
		/*fileContent = File::ReadAllText(selectedFile);*/
		String^ mfileContent = System::IO::File::ReadAllText(selectedFile);
		*fileContent = msclr::interop::marshal_as<std::string>(mfileContent);
	}
	else
	{
		moduleFileUploaded = false;
	}
}

void CLRNoCIntegrator::MyForm::ParseModule(std::string* fileContent, Module* module) {
	if (moduleFileUploaded) {
		VerilogParser vp;
		module = vp.parseModule(*fileContent, CLRNoCIntegrator::MyForm::parsedModule);
		if (module == nullptr) {
			MessageBox::Show("Не удалось выполнить анализ. Ошибка в описании модуля.");
			return;
		}
		MessageBox::Show("Анализ модуля: " + msclr::interop::marshal_as<String^>(module->name) + " успешно выполнен.");
		CLRNoCIntegrator::MyForm::moduleNameLabel->Text = msclr::interop::marshal_as<String^>(module->name);
		CLRNoCIntegrator::MyForm::moduleNameLabelDesc->Visible = true;
		CLRNoCIntegrator::MyForm::ModuleParseGroup->Visible = true;
		CLRNoCIntegrator::MyForm::ModulePortsDataView->Enabled= true;
		CLRNoCIntegrator::MyForm::ModulePortsDataView->Visible= true;
		if (CLRNoCIntegrator::MyForm::ModuleParamsDataView->Rows->Count > 0) {
			CLRNoCIntegrator::MyForm::ModuleParamsDataView->Rows->Clear();
		}

		for (int i = 0; i < module->ports->size(); i++) {
			String^ portName = msclr::interop::marshal_as<String^>(module->ports->at(i)->name);
			String^ portDirection = msclr::interop::marshal_as<String^>(module->ports->at(i)->direction);
			String^ portWidth = msclr::interop::marshal_as<String^>(module->ports->at(i)->width);
			cli::array<String^>^ rowValues = { portDirection, portName, portWidth };
			CLRNoCIntegrator::MyForm::ModulePortsDataView->Rows->Add(rowValues);
		}

		if (module->params->size() > 0) {
			CLRNoCIntegrator::MyForm::ModuleParamsDataView->Enabled = true;
			CLRNoCIntegrator::MyForm::ModuleParamsDataView->Visible = true;
			CLRNoCIntegrator::MyForm::ModuleParamsLabelCount->Text = 
				msclr::interop::marshal_as<String^>(std::to_string(module->params->size()));

			for (auto& it = module->params->begin(); it != module->params->end(); it++) {
				String^ paramName = msclr::interop::marshal_as<String^>(it->first);
				String^ paramValue = msclr::interop::marshal_as<String^>(it->second);
				cli::array<String^>^ rowValues = { paramName, paramValue };
				CLRNoCIntegrator::MyForm::ModuleParamsDataView->Rows->Add(rowValues);
			}
		}
		else {
			CLRNoCIntegrator::MyForm::ModuleParamsDataView->Enabled = false;
			CLRNoCIntegrator::MyForm::ModuleParamsDataView->Visible = false;
			CLRNoCIntegrator::MyForm::ModuleParamsLabelCount->Text = "0";
		}
		CLRNoCIntegrator::MyForm::moduleFileParsed = true;
		CLRNoCIntegrator::MyForm::button3->Enabled = true;
	}
	else {
		MessageBox::Show("Не удалось выполнить анализ. Файл с описанием модуля не был загружен");
	}
}

void CLRNoCIntegrator::MyForm::ParseRouter(std::string* fileContent, Module* module) {
	if (routerFileUploaded) {
		VerilogParser vp;
		module = vp.parseModule(*fileContent, parsedRouter);
		if (module == nullptr) {
			MessageBox::Show("Не удалось выполнить анализ. Ошибка в описании модуля.");
			return;
		}

		MessageBox::Show("Анализ модуля: " + msclr::interop::marshal_as<String^>(module->name) + " успешно выполнен.");
		CLRNoCIntegrator::MyForm::RouterParseGroup->Visible = true;
		CLRNoCIntegrator::MyForm::RouterNameLabel->Visible = true;
		CLRNoCIntegrator::MyForm::RouterNameLabel->Text = msclr::interop::marshal_as<String^>(module->name);
		CLRNoCIntegrator::MyForm::RouterNameLabelDesc->Visible = true;
		CLRNoCIntegrator::MyForm::RouterPortsDataView->Enabled = true;
		CLRNoCIntegrator::MyForm::RouterPortsDataView->Visible = true;

		if (CLRNoCIntegrator::MyForm::RouterPortsDataView->Rows->Count > 0) {
			CLRNoCIntegrator::MyForm::RouterPortsDataView->Rows->Clear();
		}

		for (int i = 0; i < module->ports->size(); i++) {
			String^ portName = msclr::interop::marshal_as<String^>(module->ports->at(i)->name);
			String^ portDirection = msclr::interop::marshal_as<String^>(module->ports->at(i)->direction);
			String^ portWidth = msclr::interop::marshal_as<String^>(module->ports->at(i)->width);
			cli::array<String^>^ rowValues = { portDirection, portName, portWidth };
			CLRNoCIntegrator::MyForm::RouterPortsDataView->Rows->Add(rowValues);
		}

		if (module->params->size() > 0) {
			CLRNoCIntegrator::MyForm::RouterParamsDataView->Enabled = true;
			CLRNoCIntegrator::MyForm::RouterParamsDataView->Visible = true;
			CLRNoCIntegrator::MyForm::RouterParamsDataView->Text = 
				msclr::interop::marshal_as<String^>(std::to_string(module->params->size()));

			for (auto& it = module->params->begin(); it != module->params->end(); it++) {
				String^ paramName = msclr::interop::marshal_as<String^>(it->first);
				String^ paramValue = msclr::interop::marshal_as<String^>(it->second);
				cli::array<String^>^ rowValues = { paramName, paramValue };
				CLRNoCIntegrator::MyForm::RouterParamsDataView->Rows->Add(rowValues);
			}
		}
		else {
			CLRNoCIntegrator::MyForm::RouterParamsDataView->Enabled = false;
			CLRNoCIntegrator::MyForm::RouterParamsDataView->Visible = false;
			CLRNoCIntegrator::MyForm::RouterParamsCountLabel->Text = "0";
		}
		CLRNoCIntegrator::MyForm::routerFileParsed = true;
		CLRNoCIntegrator::MyForm::button5->Enabled = true;
	}
}


void CLRNoCIntegrator::MyForm::ParseNoC(std::string* fileContent, Module* module) {
	if (nocFileUploaded) {
		VerilogParser vp;
		module = vp.parseModule(*fileContent, parsedNoC);
		if (module == nullptr) {
			MessageBox::Show("Не удалось выполнить анализ. Ошибка в описании модуля.");
			return;
		}

		MessageBox::Show("Анализ сети: " + msclr::interop::marshal_as<String^>(module->name) + " успешно выполнен.");
		CLRNoCIntegrator::MyForm::NocGroupBox->Visible = true;
		CLRNoCIntegrator::MyForm::NoCIPNameLabel->Visible = true;
		CLRNoCIntegrator::MyForm::NocNodesCountLabel->Visible = true;
		CLRNoCIntegrator::MyForm::NoCRouterNameLabel->Visible = true;
		CLRNoCIntegrator::MyForm::NoCIPNameLabel->Text = 
			msclr::interop::marshal_as<String^>(CLRNoCIntegrator::MyForm::parsedModule->name);
		CLRNoCIntegrator::MyForm::NocNodesCountLabel->Text = 
			msclr::interop::marshal_as<String^>(std::to_string(9));
		CLRNoCIntegrator::MyForm::NoCRouterNameLabel->Text = 
			msclr::interop::marshal_as<String^>(CLRNoCIntegrator::MyForm::parsedRouter->name);

		CLRNoCIntegrator::MyForm::nocFileParsed = true;
		CLRNoCIntegrator::MyForm::button7->Enabled = true;
	}
}

void  CLRNoCIntegrator::MyForm::ProcessRouterFileUpload(String^ selectedFile, std::string* fileContent, 
	CLRNoCIntegrator::MyForm^ myForm) {
	if (!selectedFile->IsNullOrEmpty(selectedFile))
	{
		myForm->button4->Enabled = true;
		myForm->button2->Enabled = false;
		myForm->routerFileUploaded = true;
		myForm->moduleFileUploaded = false;
		myForm->nocFileUploaded = false;

		MessageBox::Show("Файл: " + selectedFile + " Успешно загружен.");
		/*fileContent = File::ReadAllText(selectedFile);*/
		String^ mfileContent = System::IO::File::ReadAllText(selectedFile);
		*fileContent = msclr::interop::marshal_as<std::string>(mfileContent);
	}
	else
	{
		moduleFileUploaded = false;
	}
}

void CLRNoCIntegrator::MyForm::ProcessNoCFileUpload(String^ selectedFile, std::string* fileContent) {
	if (!selectedFile->IsNullOrEmpty(selectedFile))
	{
		CLRNoCIntegrator::MyForm::button6->Enabled = true;
		CLRNoCIntegrator::MyForm::button4->Enabled = false;
		CLRNoCIntegrator::MyForm::routerFileUploaded = false;
		CLRNoCIntegrator::MyForm::moduleFileUploaded = false;
		CLRNoCIntegrator::MyForm::nocFileUploaded = true;

		MessageBox::Show("Файл: " + selectedFile + " Успешно загружен.");
		/*fileContent = File::ReadAllText(selectedFile);*/
		String^ mfileContent = System::IO::File::ReadAllText(selectedFile);
		*fileContent = msclr::interop::marshal_as<std::string>(mfileContent);
	}
	else
	{
		CLRNoCIntegrator::MyForm::nocFileUploaded = false;
	}
}

void CLRNoCIntegrator::MyForm::CfgParamsWindowClosedHandler(Object^ sender, FormClosingEventArgs^ e) {
	auto configParams = this->configParams;
	if (!configParams->coreName.empty() && !configParams->routerName.empty() && 
		configParams->dataWidth > 0 && configParams->payloadWidth > 0) {
		CLRNoCIntegrator::MyForm::button8->Enabled = true;
		CLRNoCIntegrator::MyForm::button9->Enabled = true;
		CLRNoCIntegrator::MyForm::button10->Enabled = true;
	}
}

void CLRNoCIntegrator::MyForm::CreateAssignmentsTable(ConfigParams* configParams) {
	if (configParams->nocSize > 0) {
		CLRNoCIntegrator::MyForm::AssignmentsGroupBox->Visible = true;
		for (int i = 0; i < configParams->nocSize; i++) {
			int minL = (configParams->nocSize + i - 2) % configParams->nocSize;
			int maxL = (configParams->nocSize + i - 3) % configParams->nocSize;
			int minR = (i + 2) % configParams->nocSize;
			int maxR = (i + 3) % configParams->nocSize;

			cli::array<String^>^ rowValues = 
			{ 
				Convert::ToString(i + 1), 
				Convert::ToString(minL), 
				Convert::ToString(maxL),  
				Convert::ToString(minR), 
				Convert::ToString(maxR) 
			};

			CLRNoCIntegrator::MyForm::AssignmentsDataView->Rows->Add(rowValues);
		}
	}
}

void CLRNoCIntegrator::MyForm::GenerateIntermediate(String^ filePath, ConfigParams* configParams) {
	IntegrationGenerator ig;
	std::string filePathStr = msclr::interop::marshal_as<std::string>(filePath);
	int result = ig.generate_intermediate(
		filePathStr, 
		configParams->dataWidth, 
		configParams->payloadWidth, 
		configParams->coreName, 
		configParams->routerName
	);
	if (result != -1) {
		MessageBox::Show("Файл адаптера связи был успешно создан");
	}
	else {
		MessageBox::Show("Ошибка создания файла.");
	}
}


void CLRNoCIntegrator::MyForm::ProcessIntegration(ConfigParams* configParams) {
	
	if (!CLRNoCIntegrator::MyForm::nocFileUploaded) {
		MessageBox::Show("Ошибка загрузки файла сети. Выполните повторный анализ сети.");
		return;
	}
	IntegrationGenerator ig;

	String^ topFilePath = this->openFileDialog3->FileName;
	std::string filePathStr = msclr::interop::marshal_as<std::string>(topFilePath);

	if (configParams->generateIntegrationTable) {
		int s[] = { 2,3 };
		ig.generate_assignment_table_file(filePathStr, configParams->nocSize, 2, s);
	}

	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ filePath = saveFileDialog1->FileName;
		GenerateIntermediate(filePath, configParams);
	}
	else
	{
		MessageBox::Show("Не удалось сгенерировать адаптер связи.");
	}
	String^ adapterFilePath = this->saveFileDialog1->FileName;
	std::string adapterFilePathStr = msclr::interop::marshal_as<std::string>(adapterFilePath);
	size_t lastSlashPos = adapterFilePathStr.find_last_of("/\\");
	std::string adapterName = adapterFilePathStr.substr(lastSlashPos + 1);
	size_t lastDotPos = adapterName.find_last_of(".");
	if (lastDotPos != std::string::npos) {
		adapterName = adapterName.substr(0, lastDotPos);
	}
	if (!configParams->coreName.empty() && !configParams->routerName.empty() &&
		configParams->dataWidth > 0 && configParams->payloadWidth > 0) {
		int result = ig.registerIP(
			filePathStr,
			adapterName,
			CLRNoCIntegrator::MyForm::parsedModule->name,
			configParams->coreName,
			configParams->routerName,
			configParams->dataWidth,
			configParams->payloadWidth,
			configParams->nocSize);
		if (result != -1) {
			MessageBox::Show("Добавление компонента в структуру СтнК успешно выполнено. Изменения были внесены в файл: "+ this->openFileDialog3->FileName);
		}
	}
}