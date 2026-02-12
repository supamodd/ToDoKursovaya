#pragma once

namespace FIxDesign {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^ taskListBox;
	protected:
	private: System::Windows::Forms::TextBox^ descTextBox;
	private: System::Windows::Forms::ComboBox^ priorityComboBox;
	private: System::Windows::Forms::DateTimePicker^ dueDatePicker;
	private: System::Windows::Forms::Button^ addButton;
	private: System::Windows::Forms::Button^ deleteButton;
	private: System::Windows::Forms::TextBox^ searchTextBox;
	private: System::Windows::Forms::Button^ searchButton;
	private: System::Windows::Forms::Button^ checkOverdueButton;





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
			this->taskListBox = (gcnew System::Windows::Forms::ListBox());
			this->descTextBox = (gcnew System::Windows::Forms::TextBox());
			this->priorityComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->dueDatePicker = (gcnew System::Windows::Forms::DateTimePicker());
			this->addButton = (gcnew System::Windows::Forms::Button());
			this->deleteButton = (gcnew System::Windows::Forms::Button());
			this->searchTextBox = (gcnew System::Windows::Forms::TextBox());
			this->searchButton = (gcnew System::Windows::Forms::Button());
			this->checkOverdueButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// taskListBox
			// 
			this->taskListBox->FormattingEnabled = true;
			this->taskListBox->Location = System::Drawing::Point(101, 47);
			this->taskListBox->Name = L"taskListBox";
			this->taskListBox->Size = System::Drawing::Size(605, 134);
			this->taskListBox->TabIndex = 0;
			// 
			// descTextBox
			// 
			this->descTextBox->Location = System::Drawing::Point(101, 218);
			this->descTextBox->Name = L"descTextBox";
			this->descTextBox->Size = System::Drawing::Size(486, 20);
			this->descTextBox->TabIndex = 1;
			// 
			// priorityComboBox
			// 
			this->priorityComboBox->FormattingEnabled = true;
			this->priorityComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"\"low\", \"medium\", \"high\"" });
			this->priorityComboBox->Location = System::Drawing::Point(101, 274);
			this->priorityComboBox->Name = L"priorityComboBox";
			this->priorityComboBox->Size = System::Drawing::Size(173, 21);
			this->priorityComboBox->TabIndex = 2;
			// 
			// dueDatePicker
			// 
			this->dueDatePicker->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->dueDatePicker->Location = System::Drawing::Point(101, 313);
			this->dueDatePicker->Name = L"dueDatePicker";
			this->dueDatePicker->Size = System::Drawing::Size(200, 20);
			this->dueDatePicker->TabIndex = 3;
			// 
			// addButton
			// 
			this->addButton->Location = System::Drawing::Point(101, 380);
			this->addButton->Name = L"addButton";
			this->addButton->Size = System::Drawing::Size(75, 23);
			this->addButton->TabIndex = 4;
			this->addButton->Text = L"Добавить";
			this->addButton->UseVisualStyleBackColor = true;
			// 
			// deleteButton
			// 
			this->deleteButton->Location = System::Drawing::Point(182, 380);
			this->deleteButton->Name = L"deleteButton";
			this->deleteButton->Size = System::Drawing::Size(75, 23);
			this->deleteButton->TabIndex = 5;
			this->deleteButton->Text = L"Удалить";
			this->deleteButton->UseVisualStyleBackColor = true;
			// 
			// searchTextBox
			// 
			this->searchTextBox->Location = System::Drawing::Point(340, 274);
			this->searchTextBox->Name = L"searchTextBox";
			this->searchTextBox->Size = System::Drawing::Size(229, 20);
			this->searchTextBox->TabIndex = 6;
			// 
			// searchButton
			// 
			this->searchButton->Location = System::Drawing::Point(594, 270);
			this->searchButton->Name = L"searchButton";
			this->searchButton->Size = System::Drawing::Size(75, 23);
			this->searchButton->TabIndex = 7;
			this->searchButton->Text = L"Поиск";
			this->searchButton->UseVisualStyleBackColor = true;
			// 
			// checkOverdueButton
			// 
			this->checkOverdueButton->Location = System::Drawing::Point(594, 379);
			this->checkOverdueButton->Name = L"checkOverdueButton";
			this->checkOverdueButton->Size = System::Drawing::Size(112, 23);
			this->checkOverdueButton->TabIndex = 8;
			this->checkOverdueButton->Text = L"Просроченные";
			this->checkOverdueButton->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(804, 645);
			this->Controls->Add(this->checkOverdueButton);
			this->Controls->Add(this->searchButton);
			this->Controls->Add(this->searchTextBox);
			this->Controls->Add(this->deleteButton);
			this->Controls->Add(this->addButton);
			this->Controls->Add(this->dueDatePicker);
			this->Controls->Add(this->priorityComboBox);
			this->Controls->Add(this->descTextBox);
			this->Controls->Add(this->taskListBox);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
