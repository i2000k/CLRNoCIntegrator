#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include "CfgParamsForm.h"
#include "ConfigParams.h"
#include "VerilogParser.h"
#include "IntegrationGenerator.h"
#include <msclr\marshal_cppstd.h>


namespace CLRNoCIntegrator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			parsedModule = new Module();
			parsedRouter = new Module();
			parsedNoC = new Module();
			configParams = new ConfigParams();
		}

	public: void ProcessModuleFileUpload(String^ selectedFile, std::string* fileContent, CLRNoCIntegrator::MyForm^ myForm);
	public: void ProcessRouterFileUpload(String^ selectedFile, std::string* fileContent, CLRNoCIntegrator::MyForm^ myForm);
	public: void ProcessNoCFileUpload(String^ selectedFile, std::string* fileContent);
	public: void ParseModule(std::string* fileContent, Module* module);
	public: void ParseRouter(std::string* fileContent, Module* module);
	public: void ParseNoC(std::string* fileContent, Module* module);
	public: void CfgParamsWindowClosedHandler(Object^ sender, FormClosingEventArgs^ e);
	public: void CreateAssignmentsTable(ConfigParams* configParams);
	public: void GenerateIntermediate(String^ filePath, ConfigParams* configParams);
	public: void ProcessIntegration(ConfigParams* configParams);

	public: bool moduleFileUploaded;
	public: bool routerFileUploaded;
	public: bool nocFileUploaded;
	public: bool moduleFileParsed;
	public: bool nocFileParsed;
	public: bool routerFileParsed;

	public: Module* parsedModule;
	public: Module* parsedRouter;
	public: Module* parsedNoC;
	public: ConfigParams* configParams;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			delete fileContent;
			delete parsedModule;
			delete parsedNoC;
			delete parsedRouter;
			delete configParams;
		}

	public: System::Windows::Forms::Button^ button1;
	public: System::Windows::Forms::Button^ button2;
	public: System::Windows::Forms::Button^ button3;
	public: System::Windows::Forms::Button^ button4;
	public: System::Windows::Forms::Button^ button5;
	public: System::Windows::Forms::Button^ button6;
	public: System::Windows::Forms::Button^ button7;
	public: System::Windows::Forms::Button^ button8;
	public: System::Windows::Forms::Button^ button9;
	public: System::Windows::Forms::Button^ button10;
	public: System::Windows::Forms::BindingSource^ bindingSource1;


	public: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::ComponentModel::IContainer^ components;



	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::GroupBox^ ModuleParseGroup;

	private: System::Windows::Forms::Label^ moduleNameLabelDesc;
	public: System::Windows::Forms::Label^ moduleNameLabel;
	public: System::Windows::Forms::DataGridView^ ModulePortsDataView;
	private: System::Windows::Forms::BindingSource^ bindingSource2;
	private: System::Windows::Forms::DataGridView^ ModuleParamsDataView;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ParamName;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ParamValue;
	private: System::Windows::Forms::Label^ ModuleParamsLabelDesc;
	private: System::Windows::Forms::Label^ ModuleParamsLabelCount;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Direction;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ PortName;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Width;
	private: System::Windows::Forms::GroupBox^ RouterParseGroup;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::DataGridView^ RouterParamsDataView;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn2;
	public: System::Windows::Forms::DataGridView^ RouterPortsDataView;

	private:
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn3;
	public:
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn5;
	public: System::Windows::Forms::Label^ RouterParamsCountLabel;
	private: System::Windows::Forms::Label^ RouterNameLabelDesc;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::GroupBox^ NocGroupBox;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ NoCRouterNameLabel;

	private: System::Windows::Forms::Label^ NoCIPNameLabel;

	private: System::Windows::Forms::Label^ NocNodesCountLabel;

	private: System::Windows::Forms::GroupBox^ AssignmentsGroupBox;
	private: System::Windows::Forms::DataGridView^ AssignmentsDataView;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Rindex;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ minL;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ maxL;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ minR;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ maxR;
	private: System::Windows::Forms::Label^ RouterNameLabel;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog2;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog3;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	public: std::string* fileContent = new std::string();
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->bindingSource1 = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->ModuleParseGroup = (gcnew System::Windows::Forms::GroupBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->ModuleParamsLabelCount = (gcnew System::Windows::Forms::Label());
			this->ModuleParamsLabelDesc = (gcnew System::Windows::Forms::Label());
			this->ModuleParamsDataView = (gcnew System::Windows::Forms::DataGridView());
			this->ParamName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ParamValue = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->moduleNameLabel = (gcnew System::Windows::Forms::Label());
			this->moduleNameLabelDesc = (gcnew System::Windows::Forms::Label());
			this->ModulePortsDataView = (gcnew System::Windows::Forms::DataGridView());
			this->Direction = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PortName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Width = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->bindingSource2 = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->RouterParseGroup = (gcnew System::Windows::Forms::GroupBox());
			this->RouterNameLabel = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->RouterParamsDataView = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->RouterPortsDataView = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->RouterParamsCountLabel = (gcnew System::Windows::Forms::Label());
			this->RouterNameLabelDesc = (gcnew System::Windows::Forms::Label());
			this->NocGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->NoCRouterNameLabel = (gcnew System::Windows::Forms::Label());
			this->NoCIPNameLabel = (gcnew System::Windows::Forms::Label());
			this->NocNodesCountLabel = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->AssignmentsGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->AssignmentsDataView = (gcnew System::Windows::Forms::DataGridView());
			this->Rindex = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->minL = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->maxL = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->minR = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->maxR = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openFileDialog3 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->ModuleParseGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ModuleParamsDataView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ModulePortsDataView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource2))->BeginInit();
			this->RouterParseGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RouterParamsDataView))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RouterPortsDataView))->BeginInit();
			this->NocGroupBox->SuspendLayout();
			this->AssignmentsGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AssignmentsDataView))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(9, 19);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(200, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Загрузить описание компонента";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(9, 48);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(200, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Начать анализ компонента";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Location = System::Drawing::Point(9, 77);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(200, 37);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Загрузить описание маршрутизатора";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Enabled = false;
			this->button4->Location = System::Drawing::Point(9, 120);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(200, 23);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Запустить анализ маршрутизатора";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Enabled = false;
			this->button5->Location = System::Drawing::Point(9, 149);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(200, 23);
			this->button5->TabIndex = 4;
			this->button5->Text = L"Загрузить описание сети";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// button6
			// 
			this->button6->Enabled = false;
			this->button6->Location = System::Drawing::Point(9, 178);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(200, 23);
			this->button6->TabIndex = 5;
			this->button6->Text = L"Запустить анализ сети";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// button7
			// 
			this->button7->Enabled = false;
			this->button7->Location = System::Drawing::Point(17, 19);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(184, 23);
			this->button7->TabIndex = 6;
			this->button7->Text = L"Параметры конфигурации";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// button8
			// 
			this->button8->Enabled = false;
			this->button8->Location = System::Drawing::Point(17, 48);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(184, 34);
			this->button8->TabIndex = 7;
			this->button8->Text = L"Рассчёт назначений маршрутизации";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click);
			// 
			// button9
			// 
			this->button9->Enabled = false;
			this->button9->Location = System::Drawing::Point(17, 88);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(184, 34);
			this->button9->TabIndex = 8;
			this->button9->Text = L"Генерация адаптера связи";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// button10
			// 
			this->button10->Enabled = false;
			this->button10->Location = System::Drawing::Point(17, 128);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(184, 34);
			this->button10->TabIndex = 9;
			this->button10->Text = L"Интеграция компонента";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &MyForm::button10_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Filter = L"Verilog Files (*.v)|*.v";
			this->openFileDialog1->Title = L"Выберите файл с описанием сети";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Controls->Add(this->button6);
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Controls->Add(this->button5);
			this->groupBox1->Controls->Add(this->button4);
			this->groupBox1->Location = System::Drawing::Point(36, 11);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(222, 229);
			this->groupBox1->TabIndex = 12;
			this->groupBox1->TabStop = false;
			this->groupBox1->Enter += gcnew System::EventHandler(this, &MyForm::groupBox1_Enter);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->button9);
			this->groupBox2->Controls->Add(this->button7);
			this->groupBox2->Controls->Add(this->button10);
			this->groupBox2->Controls->Add(this->button8);
			this->groupBox2->Location = System::Drawing::Point(36, 265);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(221, 187);
			this->groupBox2->TabIndex = 13;
			this->groupBox2->TabStop = false;
			// 
			// ModuleParseGroup
			// 
			this->ModuleParseGroup->Controls->Add(this->label5);
			this->ModuleParseGroup->Controls->Add(this->ModuleParamsLabelCount);
			this->ModuleParseGroup->Controls->Add(this->ModuleParamsLabelDesc);
			this->ModuleParseGroup->Controls->Add(this->ModuleParamsDataView);
			this->ModuleParseGroup->Controls->Add(this->moduleNameLabel);
			this->ModuleParseGroup->Controls->Add(this->moduleNameLabelDesc);
			this->ModuleParseGroup->Controls->Add(this->ModulePortsDataView);
			this->ModuleParseGroup->Location = System::Drawing::Point(282, 11);
			this->ModuleParseGroup->Name = L"ModuleParseGroup";
			this->ModuleParseGroup->Size = System::Drawing::Size(414, 441);
			this->ModuleParseGroup->TabIndex = 14;
			this->ModuleParseGroup->TabStop = false;
			this->ModuleParseGroup->Text = L"Анализ Модуля";
			this->ModuleParseGroup->Visible = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(6, 53);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(125, 13);
			this->label5->TabIndex = 6;
			this->label5->Text = L"Информация о портах: ";
			this->label5->Visible = false;
			this->label5->Click += gcnew System::EventHandler(this, &MyForm::label5_Click);
			// 
			// ModuleParamsLabelCount
			// 
			this->ModuleParamsLabelCount->AutoSize = true;
			this->ModuleParamsLabelCount->Location = System::Drawing::Point(148, 266);
			this->ModuleParamsLabelCount->Name = L"ModuleParamsLabelCount";
			this->ModuleParamsLabelCount->Size = System::Drawing::Size(0, 13);
			this->ModuleParamsLabelCount->TabIndex = 5;
			// 
			// ModuleParamsLabelDesc
			// 
			this->ModuleParamsLabelDesc->AutoSize = true;
			this->ModuleParamsLabelDesc->Location = System::Drawing::Point(6, 266);
			this->ModuleParamsLabelDesc->Name = L"ModuleParamsLabelDesc";
			this->ModuleParamsLabelDesc->Size = System::Drawing::Size(136, 13);
			this->ModuleParamsLabelDesc->TabIndex = 4;
			this->ModuleParamsLabelDesc->Text = L"Количество параметров: ";
			this->ModuleParamsLabelDesc->Click += gcnew System::EventHandler(this, &MyForm::label1_Click_1);
			// 
			// ModuleParamsDataView
			// 
			this->ModuleParamsDataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->ModuleParamsDataView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->ParamName,
					this->ParamValue
			});
			this->ModuleParamsDataView->Enabled = false;
			this->ModuleParamsDataView->Location = System::Drawing::Point(9, 290);
			this->ModuleParamsDataView->Name = L"ModuleParamsDataView";
			this->ModuleParamsDataView->Size = System::Drawing::Size(213, 126);
			this->ModuleParamsDataView->TabIndex = 3;
			this->ModuleParamsDataView->Visible = false;
			// 
			// ParamName
			// 
			this->ParamName->Frozen = true;
			this->ParamName->HeaderText = L"Название параметра";
			this->ParamName->Name = L"ParamName";
			this->ParamName->ReadOnly = true;
			this->ParamName->Width = 90;
			// 
			// ParamValue
			// 
			this->ParamValue->HeaderText = L"Значение параметра";
			this->ParamValue->Name = L"ParamValue";
			this->ParamValue->ReadOnly = true;
			this->ParamValue->Width = 80;
			// 
			// moduleNameLabel
			// 
			this->moduleNameLabel->AutoSize = true;
			this->moduleNameLabel->Location = System::Drawing::Point(112, 24);
			this->moduleNameLabel->Name = L"moduleNameLabel";
			this->moduleNameLabel->Size = System::Drawing::Size(0, 13);
			this->moduleNameLabel->TabIndex = 1;
			this->moduleNameLabel->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// moduleNameLabelDesc
			// 
			this->moduleNameLabelDesc->AutoSize = true;
			this->moduleNameLabelDesc->Location = System::Drawing::Point(6, 24);
			this->moduleNameLabelDesc->Name = L"moduleNameLabelDesc";
			this->moduleNameLabelDesc->Size = System::Drawing::Size(100, 13);
			this->moduleNameLabelDesc->TabIndex = 0;
			this->moduleNameLabelDesc->Text = L"Название модуля:";
			this->moduleNameLabelDesc->Visible = false;
			this->moduleNameLabelDesc->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// ModulePortsDataView
			// 
			this->ModulePortsDataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->ModulePortsDataView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Direction,
					this->PortName, this->Width
			});
			this->ModulePortsDataView->Enabled = false;
			this->ModulePortsDataView->Location = System::Drawing::Point(9, 77);
			this->ModulePortsDataView->Name = L"ModulePortsDataView";
			this->ModulePortsDataView->Size = System::Drawing::Size(387, 181);
			this->ModulePortsDataView->TabIndex = 2;
			this->ModulePortsDataView->Visible = false;
			// 
			// Direction
			// 
			this->Direction->HeaderText = L"Направление";
			this->Direction->Name = L"Direction";
			this->Direction->ReadOnly = true;
			this->Direction->Width = 115;
			// 
			// PortName
			// 
			this->PortName->HeaderText = L"Название";
			this->PortName->Name = L"PortName";
			this->PortName->ReadOnly = true;
			this->PortName->Width = 120;
			// 
			// Width
			// 
			this->Width->HeaderText = L"Размер";
			this->Width->Name = L"Width";
			this->Width->ReadOnly = true;
			this->Width->Width = 110;
			// 
			// RouterParseGroup
			// 
			this->RouterParseGroup->Controls->Add(this->RouterNameLabel);
			this->RouterParseGroup->Controls->Add(this->label6);
			this->RouterParseGroup->Controls->Add(this->label1);
			this->RouterParseGroup->Controls->Add(this->label2);
			this->RouterParseGroup->Controls->Add(this->RouterParamsDataView);
			this->RouterParseGroup->Controls->Add(this->RouterPortsDataView);
			this->RouterParseGroup->Controls->Add(this->RouterParamsCountLabel);
			this->RouterParseGroup->Controls->Add(this->RouterNameLabelDesc);
			this->RouterParseGroup->Location = System::Drawing::Point(718, 11);
			this->RouterParseGroup->Name = L"RouterParseGroup";
			this->RouterParseGroup->Size = System::Drawing::Size(414, 441);
			this->RouterParseGroup->TabIndex = 15;
			this->RouterParseGroup->TabStop = false;
			this->RouterParseGroup->Text = L"Анализ Маршрутизатора";
			this->RouterParseGroup->Visible = false;
			this->RouterParseGroup->Enter += gcnew System::EventHandler(this, &MyForm::groupBox3_Enter);
			// 
			// RouterNameLabel
			// 
			this->RouterNameLabel->AutoSize = true;
			this->RouterNameLabel->Location = System::Drawing::Point(112, 24);
			this->RouterNameLabel->Name = L"RouterNameLabel";
			this->RouterNameLabel->Size = System::Drawing::Size(0, 13);
			this->RouterNameLabel->TabIndex = 7;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 58);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(125, 13);
			this->label6->TabIndex = 6;
			this->label6->Text = L"Информация о портах: ";
			this->label6->Visible = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(141, 247);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 13);
			this->label1->TabIndex = 5;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 266);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(136, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Количество параметров: ";
			// 
			// RouterParamsDataView
			// 
			this->RouterParamsDataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->RouterParamsDataView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				this->dataGridViewTextBoxColumn1,
					this->dataGridViewTextBoxColumn2
			});
			this->RouterParamsDataView->Enabled = false;
			this->RouterParamsDataView->Location = System::Drawing::Point(9, 290);
			this->RouterParamsDataView->Name = L"RouterParamsDataView";
			this->RouterParamsDataView->Size = System::Drawing::Size(213, 126);
			this->RouterParamsDataView->TabIndex = 3;
			this->RouterParamsDataView->Visible = false;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->Frozen = true;
			this->dataGridViewTextBoxColumn1->HeaderText = L"Название параметра";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			this->dataGridViewTextBoxColumn1->ReadOnly = true;
			this->dataGridViewTextBoxColumn1->Width = 90;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->HeaderText = L"Значение параметра";
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			this->dataGridViewTextBoxColumn2->ReadOnly = true;
			this->dataGridViewTextBoxColumn2->Width = 80;
			// 
			// RouterPortsDataView
			// 
			this->RouterPortsDataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->RouterPortsDataView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->dataGridViewTextBoxColumn3,
					this->dataGridViewTextBoxColumn4, this->dataGridViewTextBoxColumn5
			});
			this->RouterPortsDataView->Enabled = false;
			this->RouterPortsDataView->Location = System::Drawing::Point(9, 77);
			this->RouterPortsDataView->Name = L"RouterPortsDataView";
			this->RouterPortsDataView->Size = System::Drawing::Size(387, 181);
			this->RouterPortsDataView->TabIndex = 2;
			this->RouterPortsDataView->Visible = false;
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->HeaderText = L"Направление";
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			this->dataGridViewTextBoxColumn3->ReadOnly = true;
			this->dataGridViewTextBoxColumn3->Width = 115;
			// 
			// dataGridViewTextBoxColumn4
			// 
			this->dataGridViewTextBoxColumn4->HeaderText = L"Название";
			this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
			this->dataGridViewTextBoxColumn4->ReadOnly = true;
			this->dataGridViewTextBoxColumn4->Width = 120;
			// 
			// dataGridViewTextBoxColumn5
			// 
			this->dataGridViewTextBoxColumn5->HeaderText = L"Размер";
			this->dataGridViewTextBoxColumn5->Name = L"dataGridViewTextBoxColumn5";
			this->dataGridViewTextBoxColumn5->ReadOnly = true;
			this->dataGridViewTextBoxColumn5->Width = 110;
			// 
			// RouterParamsCountLabel
			// 
			this->RouterParamsCountLabel->AutoSize = true;
			this->RouterParamsCountLabel->Location = System::Drawing::Point(141, 266);
			this->RouterParamsCountLabel->Name = L"RouterParamsCountLabel";
			this->RouterParamsCountLabel->Size = System::Drawing::Size(0, 13);
			this->RouterParamsCountLabel->TabIndex = 1;
			// 
			// RouterNameLabelDesc
			// 
			this->RouterNameLabelDesc->AutoSize = true;
			this->RouterNameLabelDesc->Location = System::Drawing::Point(6, 24);
			this->RouterNameLabelDesc->Name = L"RouterNameLabelDesc";
			this->RouterNameLabelDesc->Size = System::Drawing::Size(100, 13);
			this->RouterNameLabelDesc->TabIndex = 0;
			this->RouterNameLabelDesc->Text = L"Название модуля:";
			this->RouterNameLabelDesc->Visible = false;
			// 
			// NocGroupBox
			// 
			this->NocGroupBox->Controls->Add(this->NoCRouterNameLabel);
			this->NocGroupBox->Controls->Add(this->NoCIPNameLabel);
			this->NocGroupBox->Controls->Add(this->NocNodesCountLabel);
			this->NocGroupBox->Controls->Add(this->label9);
			this->NocGroupBox->Controls->Add(this->label8);
			this->NocGroupBox->Controls->Add(this->label7);
			this->NocGroupBox->Location = System::Drawing::Point(718, 472);
			this->NocGroupBox->Name = L"NocGroupBox";
			this->NocGroupBox->Size = System::Drawing::Size(414, 255);
			this->NocGroupBox->TabIndex = 16;
			this->NocGroupBox->TabStop = false;
			this->NocGroupBox->Text = L"Анализ Сети";
			this->NocGroupBox->Visible = false;
			// 
			// NoCRouterNameLabel
			// 
			this->NoCRouterNameLabel->AutoSize = true;
			this->NoCRouterNameLabel->Location = System::Drawing::Point(181, 78);
			this->NoCRouterNameLabel->Name = L"NoCRouterNameLabel";
			this->NoCRouterNameLabel->Size = System::Drawing::Size(0, 13);
			this->NoCRouterNameLabel->TabIndex = 19;
			this->NoCRouterNameLabel->Visible = false;
			// 
			// NoCIPNameLabel
			// 
			this->NoCIPNameLabel->AutoSize = true;
			this->NoCIPNameLabel->Location = System::Drawing::Point(181, 54);
			this->NoCIPNameLabel->Name = L"NoCIPNameLabel";
			this->NoCIPNameLabel->Size = System::Drawing::Size(0, 13);
			this->NoCIPNameLabel->TabIndex = 18;
			this->NoCIPNameLabel->Visible = false;
			// 
			// NocNodesCountLabel
			// 
			this->NocNodesCountLabel->AutoSize = true;
			this->NocNodesCountLabel->Location = System::Drawing::Point(181, 30);
			this->NocNodesCountLabel->Name = L"NocNodesCountLabel";
			this->NocNodesCountLabel->Size = System::Drawing::Size(0, 13);
			this->NocNodesCountLabel->TabIndex = 17;
			this->NocNodesCountLabel->Visible = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(6, 78);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(149, 13);
			this->label9->TabIndex = 2;
			this->label9->Text = L"Название Маршрутизатора:";
			this->label9->Click += gcnew System::EventHandler(this, &MyForm::label9_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(6, 54);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(73, 13);
			this->label8->TabIndex = 1;
			this->label8->Text = L"Название IP:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(6, 30);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(127, 13);
			this->label7->TabIndex = 0;
			this->label7->Text = L"Количество узлов сети:";
			// 
			// AssignmentsGroupBox
			// 
			this->AssignmentsGroupBox->Controls->Add(this->AssignmentsDataView);
			this->AssignmentsGroupBox->Location = System::Drawing::Point(36, 472);
			this->AssignmentsGroupBox->Name = L"AssignmentsGroupBox";
			this->AssignmentsGroupBox->Size = System::Drawing::Size(660, 255);
			this->AssignmentsGroupBox->TabIndex = 17;
			this->AssignmentsGroupBox->TabStop = false;
			this->AssignmentsGroupBox->Text = L"Назначения образующих";
			this->AssignmentsGroupBox->Visible = false;
			// 
			// AssignmentsDataView
			// 
			this->AssignmentsDataView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->AssignmentsDataView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				this->Rindex,
					this->minL, this->maxL, this->minR, this->maxR
			});
			this->AssignmentsDataView->Location = System::Drawing::Point(9, 39);
			this->AssignmentsDataView->Name = L"AssignmentsDataView";
			this->AssignmentsDataView->Size = System::Drawing::Size(633, 210);
			this->AssignmentsDataView->TabIndex = 0;
			// 
			// Rindex
			// 
			this->Rindex->HeaderText = L"Номер Маршрутизатора";
			this->Rindex->Name = L"Rindex";
			this->Rindex->ReadOnly = true;
			this->Rindex->Width = 110;
			// 
			// minL
			// 
			this->minL->HeaderText = L"Младшая левая образующая";
			this->minL->Name = L"minL";
			this->minL->Width = 120;
			// 
			// maxL
			// 
			this->maxL->HeaderText = L"Старшая левая образующая";
			this->maxL->Name = L"maxL";
			this->maxL->Width = 120;
			// 
			// minR
			// 
			this->minR->HeaderText = L"Младшая правая образующая";
			this->minR->Name = L"minR";
			this->minR->Width = 120;
			// 
			// maxR
			// 
			this->maxR->HeaderText = L"Старшая правая образующая";
			this->maxR->Name = L"maxR";
			this->maxR->Width = 120;
			// 
			// openFileDialog2
			// 
			this->openFileDialog2->FileName = L"openFileDialog2";
			this->openFileDialog2->Title = L"Выберите файл с описанием маршрутизатора";
			this->openFileDialog2->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog2_FileOk);
			// 
			// openFileDialog3
			// 
			this->openFileDialog3->FileName = L"openFileDialog3";
			this->openFileDialog3->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog3_FileOk);
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = L"Verilog Files|*.v";
			this->saveFileDialog1->Title = L"Сохранить промежуточный компонент";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1151, 745);
			this->Controls->Add(this->AssignmentsGroupBox);
			this->Controls->Add(this->RouterParseGroup);
			this->Controls->Add(this->ModuleParseGroup);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->NocGroupBox);
			this->Name = L"MyForm";
			this->Padding = System::Windows::Forms::Padding(30);
			this->Text = L"NoCIntegrator";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->ModuleParseGroup->ResumeLayout(false);
			this->ModuleParseGroup->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ModuleParamsDataView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ModulePortsDataView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource2))->EndInit();
			this->RouterParseGroup->ResumeLayout(false);
			this->RouterParseGroup->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RouterParamsDataView))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RouterPortsDataView))->EndInit();
			this->NocGroupBox->ResumeLayout(false);
			this->NocGroupBox->PerformLayout();
			this->AssignmentsGroupBox->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->AssignmentsDataView))->EndInit();
			this->ResumeLayout(false);

		}
	#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			this->openFileDialog1->ShowDialog();
		}
		catch (Exception^ ex) {
			{
				MessageBox::Show("Произошла ошибка загрузки: Файл не был загружен.");
			}
		}
		
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		ParseModule(this->fileContent, this->parsedModule);
	}
	// Загрузка маршрутизатора 
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			this->openFileDialog2->ShowDialog();
		}
		catch (Exception^ ex) {
			{
				MessageBox::Show("Произошла ошибка загрузки: Файл не был загружен.");
			}
		}
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		ParseRouter(this->fileContent, this->parsedRouter);
	}
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			this->openFileDialog3->ShowDialog();
		}
		catch (Exception^ ex) {
			{
				MessageBox::Show("Произошла ошибка загрузки: Файл не был загружен.");
			}
		}
	}
	// Параметры конфигурации
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
		CfgParamsForm^ cfgParamsForm = gcnew CfgParamsForm(parsedModule, parsedNoC, parsedRouter, configParams);
		cfgParamsForm->FormClosing += gcnew FormClosingEventHandler(this, &MyForm::CfgParamsWindowClosedHandler);
		//cfgParamsForm->module = parsedModule;
		//cfgParamsForm->routerModule = parsedRouter;
		//cfgParamsForm->nocModule = parsedNoC;
		cfgParamsForm->Show();
	}
	// Рассчёт таблицы назначений
	private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
		CreateAssignmentsTable(configParams);
	}
	void openFileDialog1_FileOk(Object^ sender, System::ComponentModel::CancelEventArgs^ e)
	{
		ProcessModuleFileUpload(this->openFileDialog1->FileName, fileContent, this);
	}

	void openFileDialog2_FileOk(Object^ sender, System::ComponentModel::CancelEventArgs^ e)
	{
		ProcessRouterFileUpload(this->openFileDialog2->FileName, fileContent, this);
	}
	void openFileDialog3_FileOk(Object^ sender, System::ComponentModel::CancelEventArgs^ e)
	{
		ProcessNoCFileUpload(this->openFileDialog3->FileName, fileContent);
	}
	private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void toolStripContainer1_ContentPanel_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void modulePortsListView_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void groupBox3_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label9_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
		ParseNoC(this->fileContent, this->parsedNoC);
	}
	private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			String^ filePath = saveFileDialog1->FileName;
			GenerateIntermediate(filePath, configParams);
			// Save the file using the selected filePath
			// Example:
			// File.WriteAllText(filePath, "Hello, world!");
		}
		else
		{
			MessageBox::Show("Не удалось сгенерировать адаптер связи.");
		}
	}
	private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {
		ProcessIntegration(configParams);
	}
	};
}
