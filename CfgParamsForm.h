#pragma once
#include "VerilogParser.h"
#include <msclr\marshal_cppstd.h>
#include "ConfigParams.h"
#include <string>
#include <set>
namespace CLRNoCIntegrator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for CfgParamsForm
	/// </summary>
	public ref class CfgParamsForm : public System::Windows::Forms::Form
	{
	public:
		CfgParamsForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->TopologyCbx->SelectedIndex = 0;
			this->routingAlgorithmCbx->SelectedIndex = 0;
		}
		CfgParamsForm(Module* module, Module* nocModule, Module* routerModule, ConfigParams* configParams) {
			InitializeComponent();

			this->module = module;
			this->nocModule = nocModule;
			this->routerModule = routerModule;
			this->configParams = configParams;

			this->TopologyCbx->SelectedIndex = 0;
			this->routingAlgorithmCbx->SelectedIndex = 0;

			this->ipInstanceNameTextBox->Text = "ext_ip";
			this->routerNameTextbox->Text = "ext_r";

			this->payloadWidthCbx->Items->Add("8");
			this->payloadWidthCbx->SelectedIndex = 0;
			int nocSize = 9;
			this->nSizeTextbox->Text = (nocSize + 1).ToString();
			// Поиск максимального размера порта и установка значения по умолчанию для размера порта данных
			int maxIndex = 0;
			int max = 1;
			if (module->ports->size() > 0) {

				std::set<std::string> uniqueDataWidth;
				for (int i = 0; i < module->ports->size(); i++) {
					uniqueDataWidth.insert(module->ports->at(i)->width);

					String^ nameStr = msclr::interop::marshal_as<String^>(module->ports->at(i)->name);
					if (module->ports->at(i)->direction == "input") {
						this->inputIpPortCbx->Items->Add(nameStr);
					}
					else {
						this->outputIpPortCbx->Items->Add(nameStr);
					}
				}

				int j = 0;
				for (const std::string& w : uniqueDataWidth) {
					String^ widthStr = msclr::interop::marshal_as<String^>(w);
					this->DataWidthCbx->Items->Add(widthStr);

					int width = -1;
					
					try {
						width = std::stoi(w);
					} catch(exception& e) {}
					if (width != -1 && width > max) {
						max = width;
						maxIndex = j;
					}
					j++;
				}

				
				this->DataWidthCbx->SelectedIndex = maxIndex;
				auto it = uniqueDataWidth.begin();
				std::advance(it, maxIndex);
				int iCount = 0, oCount = 0;
				for (int i = 0; i < module->ports->size(); i++) {
					if (module->ports->at(i)->direction == "input") {
						if (module->ports->at(i)->width == *it) 
							this->inputIpPortCbx->SelectedIndex = iCount;
						iCount++;
					}
					else if (module->ports->at(i)->direction == "output") {
						
						if (module->ports->at(i)->width == *it)
							this->outputIpPortCbx->SelectedIndex = oCount;
						oCount++;
					}
				}
			}
			else {
				this->DataWidthCbx->Enabled = false;
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CfgParamsForm()
		{
			if (components)
			{
				delete components;
			}
		}

	public: Module* module;
	public: Module* routerModule;
	public: Module* nocModule;
	public: ConfigParams* configParams;

	private: System::Windows::Forms::Label^ nSizeDesc;
	private: System::Windows::Forms::ComboBox^ DataWidthCbx;
	private: System::Windows::Forms::Label^ DataWidthLabel;

	private: System::Windows::Forms::ComboBox^ payloadWidthCbx;
	private: System::Windows::Forms::TextBox^ PayloadWidthTextBox;
	private: System::Windows::Forms::TextBox^ ipInstanceNameTextBoxDesc;
	private: System::Windows::Forms::TextBox^ ipInstanceNameTextBox;
	private: System::Windows::Forms::TextBox^ routerNameTextbox;

	private: System::Windows::Forms::TextBox^ routerNameDesc;
	private: System::Windows::Forms::TextBox^ generateAssignmentTableDesc;


	private: System::Windows::Forms::CheckBox^ GenerateAssignmentsTableCheckbox;
	private: System::Windows::Forms::ComboBox^ TopologyCbx;
	private: System::Windows::Forms::TextBox^ TopogyDesc;
	private: System::Windows::Forms::TextBox^ RoutingAlgorithmDesc;
	private: System::Windows::Forms::ComboBox^ routingAlgorithmCbx;
	private: System::Windows::Forms::CheckBox^ defaultIPInstanceNameCheckbox;
	private: System::Windows::Forms::CheckBox^ defaultRouterNameCheckbox;


	private: System::Windows::Forms::Label^ sCountDesc;
	private: System::Windows::Forms::TextBox^ sCountTextbox;
	private: System::Windows::Forms::Button^ cancelButton;

	private: System::Windows::Forms::Button^ saveButton;

	private: System::Windows::Forms::TextBox^ nSizeTextbox;
private: System::Windows::Forms::Label^ InputIpPortDesc;
private: System::Windows::Forms::ComboBox^ inputIpPortCbx;
private: System::Windows::Forms::Label^ OutputIpPortDesc;
private: System::Windows::Forms::ComboBox^ outputIpPortCbx;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->nSizeDesc = (gcnew System::Windows::Forms::Label());
			this->DataWidthCbx = (gcnew System::Windows::Forms::ComboBox());
			this->DataWidthLabel = (gcnew System::Windows::Forms::Label());
			this->payloadWidthCbx = (gcnew System::Windows::Forms::ComboBox());
			this->PayloadWidthTextBox = (gcnew System::Windows::Forms::TextBox());
			this->ipInstanceNameTextBoxDesc = (gcnew System::Windows::Forms::TextBox());
			this->ipInstanceNameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->routerNameTextbox = (gcnew System::Windows::Forms::TextBox());
			this->routerNameDesc = (gcnew System::Windows::Forms::TextBox());
			this->generateAssignmentTableDesc = (gcnew System::Windows::Forms::TextBox());
			this->GenerateAssignmentsTableCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->TopologyCbx = (gcnew System::Windows::Forms::ComboBox());
			this->TopogyDesc = (gcnew System::Windows::Forms::TextBox());
			this->RoutingAlgorithmDesc = (gcnew System::Windows::Forms::TextBox());
			this->routingAlgorithmCbx = (gcnew System::Windows::Forms::ComboBox());
			this->defaultIPInstanceNameCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->defaultRouterNameCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->sCountDesc = (gcnew System::Windows::Forms::Label());
			this->sCountTextbox = (gcnew System::Windows::Forms::TextBox());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->saveButton = (gcnew System::Windows::Forms::Button());
			this->nSizeTextbox = (gcnew System::Windows::Forms::TextBox());
			this->InputIpPortDesc = (gcnew System::Windows::Forms::Label());
			this->inputIpPortCbx = (gcnew System::Windows::Forms::ComboBox());
			this->OutputIpPortDesc = (gcnew System::Windows::Forms::Label());
			this->outputIpPortCbx = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// nSizeDesc
			// 
			this->nSizeDesc->AutoSize = true;
			this->nSizeDesc->Location = System::Drawing::Point(9, 130);
			this->nSizeDesc->Name = L"nSizeDesc";
			this->nSizeDesc->Size = System::Drawing::Size(221, 13);
			this->nSizeDesc->TabIndex = 0;
			this->nSizeDesc->Text = L"Количество узлов сети после интегарции:";
			// 
			// DataWidthCbx
			// 
			this->DataWidthCbx->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->DataWidthCbx->Enabled = false;
			this->DataWidthCbx->FormatString = L"N0";
			this->DataWidthCbx->FormattingEnabled = true;
			this->DataWidthCbx->Location = System::Drawing::Point(206, 221);
			this->DataWidthCbx->Name = L"DataWidthCbx";
			this->DataWidthCbx->Size = System::Drawing::Size(63, 21);
			this->DataWidthCbx->TabIndex = 1;
			this->DataWidthCbx->SelectedIndexChanged += gcnew System::EventHandler(this, &CfgParamsForm::DataWidthCbx_SelectedIndexChanged);
			// 
			// DataWidthLabel
			// 
			this->DataWidthLabel->AutoSize = true;
			this->DataWidthLabel->Location = System::Drawing::Point(9, 225);
			this->DataWidthLabel->Name = L"DataWidthLabel";
			this->DataWidthLabel->Size = System::Drawing::Size(166, 13);
			this->DataWidthLabel->TabIndex = 2;
			this->DataWidthLabel->Text = L"Размер данных IP-компонента:";
			this->DataWidthLabel->Click += gcnew System::EventHandler(this, &CfgParamsForm::label2_Click);
			// 
			// payloadWidthCbx
			// 
			this->payloadWidthCbx->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->payloadWidthCbx->Enabled = false;
			this->payloadWidthCbx->FormatString = L"N0";
			this->payloadWidthCbx->FormattingEnabled = true;
			this->payloadWidthCbx->Location = System::Drawing::Point(206, 258);
			this->payloadWidthCbx->Name = L"payloadWidthCbx";
			this->payloadWidthCbx->Size = System::Drawing::Size(63, 21);
			this->payloadWidthCbx->TabIndex = 3;
			// 
			// PayloadWidthTextBox
			// 
			this->PayloadWidthTextBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->PayloadWidthTextBox->Location = System::Drawing::Point(12, 252);
			this->PayloadWidthTextBox->Multiline = true;
			this->PayloadWidthTextBox->Name = L"PayloadWidthTextBox";
			this->PayloadWidthTextBox->ReadOnly = true;
			this->PayloadWidthTextBox->Size = System::Drawing::Size(163, 32);
			this->PayloadWidthTextBox->TabIndex = 5;
			this->PayloadWidthTextBox->Text = L"Размер поля нагрузки маршрутизатора: ";
			// 
			// ipInstanceNameTextBoxDesc
			// 
			this->ipInstanceNameTextBoxDesc->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->ipInstanceNameTextBoxDesc->Location = System::Drawing::Point(9, 301);
			this->ipInstanceNameTextBoxDesc->Multiline = true;
			this->ipInstanceNameTextBoxDesc->Name = L"ipInstanceNameTextBoxDesc";
			this->ipInstanceNameTextBoxDesc->ReadOnly = true;
			this->ipInstanceNameTextBoxDesc->Size = System::Drawing::Size(260, 21);
			this->ipInstanceNameTextBoxDesc->TabIndex = 6;
			this->ipInstanceNameTextBoxDesc->Text = L"Имя экземпляра IP-компонента:";
			// 
			// ipInstanceNameTextBox
			// 
			this->ipInstanceNameTextBox->Enabled = false;
			this->ipInstanceNameTextBox->Location = System::Drawing::Point(9, 319);
			this->ipInstanceNameTextBox->Name = L"ipInstanceNameTextBox";
			this->ipInstanceNameTextBox->Size = System::Drawing::Size(260, 20);
			this->ipInstanceNameTextBox->TabIndex = 7;
			// 
			// routerNameTextbox
			// 
			this->routerNameTextbox->Enabled = false;
			this->routerNameTextbox->Location = System::Drawing::Point(9, 386);
			this->routerNameTextbox->Name = L"routerNameTextbox";
			this->routerNameTextbox->Size = System::Drawing::Size(260, 20);
			this->routerNameTextbox->TabIndex = 9;
			this->routerNameTextbox->TextChanged += gcnew System::EventHandler(this, &CfgParamsForm::routerNameTextbox_TextChanged);
			// 
			// routerNameDesc
			// 
			this->routerNameDesc->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->routerNameDesc->Location = System::Drawing::Point(9, 368);
			this->routerNameDesc->Multiline = true;
			this->routerNameDesc->Name = L"routerNameDesc";
			this->routerNameDesc->ReadOnly = true;
			this->routerNameDesc->Size = System::Drawing::Size(260, 21);
			this->routerNameDesc->TabIndex = 8;
			this->routerNameDesc->Text = L"Имя экземпляра маршрутизатора:";
			// 
			// generateAssignmentTableDesc
			// 
			this->generateAssignmentTableDesc->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->generateAssignmentTableDesc->Location = System::Drawing::Point(9, 435);
			this->generateAssignmentTableDesc->Multiline = true;
			this->generateAssignmentTableDesc->Name = L"generateAssignmentTableDesc";
			this->generateAssignmentTableDesc->ReadOnly = true;
			this->generateAssignmentTableDesc->Size = System::Drawing::Size(221, 36);
			this->generateAssignmentTableDesc->TabIndex = 10;
			this->generateAssignmentTableDesc->Text = L"Сгенерировать файл рассчёта маршрутизации: ";
			// 
			// GenerateAssignmentsTableCheckbox
			// 
			this->GenerateAssignmentsTableCheckbox->AutoSize = true;
			this->GenerateAssignmentsTableCheckbox->Checked = true;
			this->GenerateAssignmentsTableCheckbox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->GenerateAssignmentsTableCheckbox->Location = System::Drawing::Point(254, 446);
			this->GenerateAssignmentsTableCheckbox->Name = L"GenerateAssignmentsTableCheckbox";
			this->GenerateAssignmentsTableCheckbox->Size = System::Drawing::Size(15, 14);
			this->GenerateAssignmentsTableCheckbox->TabIndex = 11;
			this->GenerateAssignmentsTableCheckbox->UseVisualStyleBackColor = true;
			// 
			// TopologyCbx
			// 
			this->TopologyCbx->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->TopologyCbx->FormattingEnabled = true;
			this->TopologyCbx->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"Циркулянт" });
			this->TopologyCbx->Location = System::Drawing::Point(148, 12);
			this->TopologyCbx->Name = L"TopologyCbx";
			this->TopologyCbx->Size = System::Drawing::Size(121, 21);
			this->TopologyCbx->TabIndex = 12;
			this->TopologyCbx->SelectedIndexChanged += gcnew System::EventHandler(this, &CfgParamsForm::TopologyCbx_SelectedIndexChanged);
			// 
			// TopogyDesc
			// 
			this->TopogyDesc->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->TopogyDesc->Location = System::Drawing::Point(12, 15);
			this->TopogyDesc->Multiline = true;
			this->TopogyDesc->Name = L"TopogyDesc";
			this->TopogyDesc->ReadOnly = true;
			this->TopogyDesc->Size = System::Drawing::Size(120, 21);
			this->TopogyDesc->TabIndex = 13;
			this->TopogyDesc->Text = L"Топология СтнК: ";
			// 
			// RoutingAlgorithmDesc
			// 
			this->RoutingAlgorithmDesc->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->RoutingAlgorithmDesc->Location = System::Drawing::Point(12, 50);
			this->RoutingAlgorithmDesc->Multiline = true;
			this->RoutingAlgorithmDesc->Name = L"RoutingAlgorithmDesc";
			this->RoutingAlgorithmDesc->ReadOnly = true;
			this->RoutingAlgorithmDesc->Size = System::Drawing::Size(120, 29);
			this->RoutingAlgorithmDesc->TabIndex = 15;
			this->RoutingAlgorithmDesc->Text = L"Алгоритм маршрутизации: ";
			// 
			// routingAlgorithmCbx
			// 
			this->routingAlgorithmCbx->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->routingAlgorithmCbx->FormattingEnabled = true;
			this->routingAlgorithmCbx->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"APO" });
			this->routingAlgorithmCbx->Location = System::Drawing::Point(148, 58);
			this->routingAlgorithmCbx->Name = L"routingAlgorithmCbx";
			this->routingAlgorithmCbx->Size = System::Drawing::Size(121, 21);
			this->routingAlgorithmCbx->TabIndex = 14;
			// 
			// defaultIPInstanceNameCheckbox
			// 
			this->defaultIPInstanceNameCheckbox->AutoSize = true;
			this->defaultIPInstanceNameCheckbox->Checked = true;
			this->defaultIPInstanceNameCheckbox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->defaultIPInstanceNameCheckbox->Location = System::Drawing::Point(9, 345);
			this->defaultIPInstanceNameCheckbox->Name = L"defaultIPInstanceNameCheckbox";
			this->defaultIPInstanceNameCheckbox->Size = System::Drawing::Size(173, 17);
			this->defaultIPInstanceNameCheckbox->TabIndex = 16;
			this->defaultIPInstanceNameCheckbox->Text = L"Использовать по умолчанию";
			this->defaultIPInstanceNameCheckbox->UseVisualStyleBackColor = true;
			this->defaultIPInstanceNameCheckbox->CheckedChanged += gcnew System::EventHandler(this, &CfgParamsForm::defaultIPInstanceNameCheckbox_CheckedChanged);
			// 
			// defaultRouterNameCheckbox
			// 
			this->defaultRouterNameCheckbox->AutoSize = true;
			this->defaultRouterNameCheckbox->Checked = true;
			this->defaultRouterNameCheckbox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->defaultRouterNameCheckbox->Location = System::Drawing::Point(9, 412);
			this->defaultRouterNameCheckbox->Name = L"defaultRouterNameCheckbox";
			this->defaultRouterNameCheckbox->Size = System::Drawing::Size(173, 17);
			this->defaultRouterNameCheckbox->TabIndex = 17;
			this->defaultRouterNameCheckbox->Text = L"Использовать по умолчанию";
			this->defaultRouterNameCheckbox->UseVisualStyleBackColor = true;
			this->defaultRouterNameCheckbox->CheckedChanged += gcnew System::EventHandler(this, &CfgParamsForm::defaultRouterNameCheckbox_CheckedChanged);
			// 
			// sCountDesc
			// 
			this->sCountDesc->AutoSize = true;
			this->sCountDesc->Location = System::Drawing::Point(9, 97);
			this->sCountDesc->Name = L"sCountDesc";
			this->sCountDesc->Size = System::Drawing::Size(138, 13);
			this->sCountDesc->TabIndex = 18;
			this->sCountDesc->Text = L"Количество образующих: ";
			this->sCountDesc->Visible = false;
			// 
			// sCountTextbox
			// 
			this->sCountTextbox->Enabled = false;
			this->sCountTextbox->Location = System::Drawing::Point(148, 94);
			this->sCountTextbox->Name = L"sCountTextbox";
			this->sCountTextbox->Size = System::Drawing::Size(39, 20);
			this->sCountTextbox->TabIndex = 19;
			this->sCountTextbox->Visible = false;
			// 
			// cancelButton
			// 
			this->cancelButton->Location = System::Drawing::Point(155, 509);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(117, 23);
			this->cancelButton->TabIndex = 20;
			this->cancelButton->Text = L"Отмена";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &CfgParamsForm::cancelButton_Click);
			// 
			// saveButton
			// 
			this->saveButton->Location = System::Drawing::Point(9, 509);
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(123, 23);
			this->saveButton->TabIndex = 21;
			this->saveButton->Text = L"Сохранить";
			this->saveButton->UseVisualStyleBackColor = true;
			this->saveButton->Click += gcnew System::EventHandler(this, &CfgParamsForm::saveButton_Click);
			// 
			// nSizeTextbox
			// 
			this->nSizeTextbox->BackColor = System::Drawing::SystemColors::Control;
			this->nSizeTextbox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->nSizeTextbox->Location = System::Drawing::Point(230, 130);
			this->nSizeTextbox->Name = L"nSizeTextbox";
			this->nSizeTextbox->ReadOnly = true;
			this->nSizeTextbox->Size = System::Drawing::Size(39, 13);
			this->nSizeTextbox->TabIndex = 22;
			// 
			// InputIpPortDesc
			// 
			this->InputIpPortDesc->AutoSize = true;
			this->InputIpPortDesc->Location = System::Drawing::Point(9, 159);
			this->InputIpPortDesc->Name = L"InputIpPortDesc";
			this->InputIpPortDesc->Size = System::Drawing::Size(158, 13);
			this->InputIpPortDesc->TabIndex = 24;
			this->InputIpPortDesc->Text = L"Входной порт IP-компонента: ";
			// 
			// inputIpPortCbx
			// 
			this->inputIpPortCbx->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->inputIpPortCbx->FormatString = L"N0";
			this->inputIpPortCbx->FormattingEnabled = true;
			this->inputIpPortCbx->Location = System::Drawing::Point(206, 155);
			this->inputIpPortCbx->Name = L"inputIpPortCbx";
			this->inputIpPortCbx->Size = System::Drawing::Size(63, 21);
			this->inputIpPortCbx->TabIndex = 23;
			this->inputIpPortCbx->SelectedIndexChanged += gcnew System::EventHandler(this, &CfgParamsForm::inputIpPortCbx_SelectedIndexChanged);
			// 
			// OutputIpPortDesc
			// 
			this->OutputIpPortDesc->AutoSize = true;
			this->OutputIpPortDesc->Location = System::Drawing::Point(9, 191);
			this->OutputIpPortDesc->Name = L"OutputIpPortDesc";
			this->OutputIpPortDesc->Size = System::Drawing::Size(163, 13);
			this->OutputIpPortDesc->TabIndex = 26;
			this->OutputIpPortDesc->Text = L"Выходной порт IP-компонента:";
			// 
			// outputIpPortCbx
			// 
			this->outputIpPortCbx->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->outputIpPortCbx->FormatString = L"N0";
			this->outputIpPortCbx->FormattingEnabled = true;
			this->outputIpPortCbx->Location = System::Drawing::Point(206, 187);
			this->outputIpPortCbx->Name = L"outputIpPortCbx";
			this->outputIpPortCbx->Size = System::Drawing::Size(63, 21);
			this->outputIpPortCbx->TabIndex = 25;
			this->outputIpPortCbx->SelectedIndexChanged += gcnew System::EventHandler(this, &CfgParamsForm::outputIpPortCbx_SelectedIndexChanged);
			// 
			// CfgParamsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 547);
			this->Controls->Add(this->OutputIpPortDesc);
			this->Controls->Add(this->outputIpPortCbx);
			this->Controls->Add(this->InputIpPortDesc);
			this->Controls->Add(this->inputIpPortCbx);
			this->Controls->Add(this->nSizeTextbox);
			this->Controls->Add(this->saveButton);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->sCountTextbox);
			this->Controls->Add(this->sCountDesc);
			this->Controls->Add(this->defaultRouterNameCheckbox);
			this->Controls->Add(this->defaultIPInstanceNameCheckbox);
			this->Controls->Add(this->RoutingAlgorithmDesc);
			this->Controls->Add(this->routingAlgorithmCbx);
			this->Controls->Add(this->TopogyDesc);
			this->Controls->Add(this->TopologyCbx);
			this->Controls->Add(this->GenerateAssignmentsTableCheckbox);
			this->Controls->Add(this->generateAssignmentTableDesc);
			this->Controls->Add(this->routerNameTextbox);
			this->Controls->Add(this->routerNameDesc);
			this->Controls->Add(this->ipInstanceNameTextBox);
			this->Controls->Add(this->ipInstanceNameTextBoxDesc);
			this->Controls->Add(this->PayloadWidthTextBox);
			this->Controls->Add(this->payloadWidthCbx);
			this->Controls->Add(this->DataWidthLabel);
			this->Controls->Add(this->DataWidthCbx);
			this->Controls->Add(this->nSizeDesc);
			this->Name = L"CfgParamsForm";
			this->Text = L"CfgParamsForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void DataWidthCbx_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void PayloadWidthLabel_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void TopologyCbx_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void defaultIPInstanceNameCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	CheckBox^ checkBox = dynamic_cast<CheckBox^>(sender);
	if (checkBox->Checked)
	{
		// Checkbox is checked, perform desired actions
		this->ipInstanceNameTextBox->Text = "ext_ip";
		this->ipInstanceNameTextBox->Enabled = false;
	}
	else
	{
		this->ipInstanceNameTextBox->Text = "";
		this->ipInstanceNameTextBox->Enabled = true;
	}
}

private: System::Void defaultRouterNameCheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	CheckBox^ checkBox = dynamic_cast<CheckBox^>(sender);
	if (checkBox->Checked)
	{
		// Checkbox is checked, perform desired actions
		this->routerNameTextbox->Text = "ext_r";
		this->routerNameTextbox->Enabled = false;
	}
	else
	{
		this->routerNameTextbox->Text = "";
		this->routerNameTextbox->Enabled = true;
	}
}
	   private: System::Void routerNameTextbox_TextChanged(System::Object^ sender, System::EventArgs^ e) {

	   }
private: System::Void inputIpPortCbx_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

	System::Windows::Forms::ComboBox^ comboBox = dynamic_cast<System::Windows::Forms::ComboBox^>(sender);
	System::Object^ selectedItem = comboBox->SelectedItem;

	if (selectedItem != nullptr) {
		std::string strValue = msclr::interop::marshal_as<std::string>(Convert::ToString(selectedItem));
		if (module->ports->size() > 0) {
			for (int i = 0; i < module->ports->size(); i++) {
				if (module->ports->at(i)->name == strValue) {
					int foundIndex = 0;
					int index = 0;
					for each (Object ^ item in this->DataWidthCbx->Items) {
						String^ listItem = item->ToString();
						if (listItem == msclr::interop::marshal_as<String^>(module->ports->at(i)->width)) {
							foundIndex = index;
						}
						index++;
					}
					this->DataWidthCbx->SelectedIndex = foundIndex;
				}
			}
		}
	}
}
private: System::Void outputIpPortCbx_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	System::Windows::Forms::ComboBox^ comboBox = dynamic_cast<System::Windows::Forms::ComboBox^>(sender);
	System::Object^ selectedItem = comboBox->SelectedItem;

	if (selectedItem != nullptr) {
		std::string strValue = msclr::interop::marshal_as<std::string>(Convert::ToString(selectedItem));
		if (module->ports->size() > 0) {
			for (int i = 0; i < module->ports->size(); i++) {
				if (module->ports->at(i)->name == strValue) {
					int foundIndex = 0;
					int index = 0;
					for each (Object ^ item in this->DataWidthCbx->Items) {
						String^ listItem = item->ToString();
						if (listItem == msclr::interop::marshal_as<String^>(module->ports->at(i)->width)) {
							foundIndex = index;
						}
						index++;
					}
					this->DataWidthCbx->SelectedIndex = foundIndex;
				}
			}
		}
	}
}
private: System::Void cancelButton_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();
}
	private: System::Void saveButton_Click(System::Object^ sender, System::EventArgs^ e) {
		int inWidth = 0, oWidth = 0;
		auto& it = module->ports->begin();
		while (it != module->ports->end()) {
			ModulePort* port = *it;
			if (msclr::interop::marshal_as<String^>(port->name) == this->inputIpPortCbx->Text) {
				try {
					inWidth = std::stoi(port->width);
				}
				catch (exception& e) {}
			}
			else if (msclr::interop::marshal_as<String^>(port->name) == this->outputIpPortCbx->Text) {
				try {
					oWidth = std::stoi(port->width);
				}
				catch (exception& e) {}
			}
			it++;
		}

		if (inWidth == 0 || oWidth == 0 || inWidth != oWidth) {
			MessageBox::Show("Ошибка конфигурирования. Порты данных имеют разную размерность.");
			return;
		}

		if (System::String::IsNullOrEmpty(this->ipInstanceNameTextBox->Text)) {
			MessageBox::Show("Ошибка конфигурирования. Задано неверное название экземпляра компонента.");
			return;
		}

		if (System::String::IsNullOrEmpty(this->routerNameTextbox->Text)) {
			MessageBox::Show("Ошибка конфигурирования. Задано неверное название экземпляра маршрутизатора.");
			return;
		}

		this->configParams->dataWidth = Convert::ToInt32(this->DataWidthCbx->Text);
		this->configParams->payloadWidth = Convert::ToInt32(this->payloadWidthCbx->Text);
		this->configParams->nocSize = Convert::ToInt32(this->nSizeTextbox->Text);
		this->configParams->coreName = msclr::interop::marshal_as<std::string>(this->ipInstanceNameTextBox->Text);
		this->configParams->routerName = msclr::interop::marshal_as<std::string>(this->routerNameTextbox->Text);
		this->configParams->generateIntegrationTable = this->GenerateAssignmentsTableCheckbox->Checked;

		this->Close();
	}
};
}
