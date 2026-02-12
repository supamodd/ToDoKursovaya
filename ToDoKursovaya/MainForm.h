#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
namespace ToDoListGUI {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace System::Globalization; 
    ref struct Task {
        String^ description;
        String^ priority;
        String^ dueDate;
    };
    /// <summary>
    /// Summary for MainForm
    /// </summary>
    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(void)
        {
            InitializeComponent();
            tasks = gcnew Collections::Generic::List<Task^>();
            LoadTasks();
            UpdateListBox();
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
            descTextBox->ForeColor = Color::Gray;
                                                                    // ШРИФТ
            this->Font = gcnew System::Drawing::Font(L"Warm Pixel", 10.0F, FontStyle::Regular);
                                                                     // ИКОНКА
            this->Icon = gcnew System::Drawing::Icon("app_icon.ico");
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
    private: System::Windows::Forms::TextBox^ descTextBox;
    private: System::Windows::Forms::ComboBox^ priorityComboBox;
    private: System::Windows::Forms::DateTimePicker^ dueDatePicker;
    private: System::Windows::Forms::Button^ addButton;
    private: System::Windows::Forms::Button^ deleteButton;
    private: System::Windows::Forms::TextBox^ searchTextBox;
    private: System::Windows::Forms::Button^ searchButton;
    private: System::Windows::Forms::Button^ checkOverdueButton;
    private: System::Windows::Forms::NotifyIcon^ trayIcon; 
    private:
        /// <summary>
        /// Required designer variable.
        /// </summary>
        System::ComponentModel::Container^ components;
    private: Collections::Generic::List<Task^>^ tasks;
#pragma region Windows Form Designer generated code
           /// <summary>
           /// Required method for Designer support - do not modify
           /// the contents of this method with the code editor.
           /// </summary>
           void InitializeComponent(void)
           {
               this->components = (gcnew System::ComponentModel::Container());
               this->taskListBox = (gcnew System::Windows::Forms::ListBox());
               this->descTextBox = (gcnew System::Windows::Forms::TextBox());
               this->priorityComboBox = (gcnew System::Windows::Forms::ComboBox());
               this->dueDatePicker = (gcnew System::Windows::Forms::DateTimePicker());
               this->addButton = (gcnew System::Windows::Forms::Button());
               this->deleteButton = (gcnew System::Windows::Forms::Button());
               this->searchTextBox = (gcnew System::Windows::Forms::TextBox());
               this->searchButton = (gcnew System::Windows::Forms::Button());
               this->checkOverdueButton = (gcnew System::Windows::Forms::Button());
               this->trayIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
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
               this->descTextBox->Text = L"Введите название задачи";
               this->descTextBox->GotFocus += gcnew System::EventHandler(this, &MainForm::descTextBox_GotFocus);
               this->descTextBox->LostFocus += gcnew System::EventHandler(this, &MainForm::descTextBox_LostFocus);
               //
               // priorityComboBox
               //
               this->priorityComboBox->FormattingEnabled = true;
               this->priorityComboBox->Items->AddRange(gcnew cli::array< System::Object^ >(3) { L"low", L"medium", L"high" }); 
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
               this->addButton->Click += gcnew System::EventHandler(this, &MainForm::addButton_Click); 
               //
               // deleteButton
               //
               this->deleteButton->Location = System::Drawing::Point(182, 380);
               this->deleteButton->Name = L"deleteButton";
               this->deleteButton->Size = System::Drawing::Size(75, 23);
               this->deleteButton->TabIndex = 5;
               this->deleteButton->Text = L"Удалить";
               this->deleteButton->UseVisualStyleBackColor = true;
               this->deleteButton->Click += gcnew System::EventHandler(this, &MainForm::deleteButton_Click);
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
               this->searchButton->Click += gcnew System::EventHandler(this, &MainForm::searchButton_Click); 
               //
               // checkOverdueButton
               //
               this->checkOverdueButton->Location = System::Drawing::Point(594, 379);
               this->checkOverdueButton->Name = L"checkOverdueButton";
               this->checkOverdueButton->Size = System::Drawing::Size(112, 23);
               this->checkOverdueButton->TabIndex = 8;
               this->checkOverdueButton->Text = L"Просроченные";
               this->checkOverdueButton->UseVisualStyleBackColor = true;
               this->checkOverdueButton->Click += gcnew System::EventHandler(this, &MainForm::checkOverdueButton_Click); 
               //
               // trayIcon
               //
               this->trayIcon->DoubleClick += gcnew System::EventHandler(this, &MainForm::trayIcon_DoubleClick);
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
               this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize); 
               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion
    private: void LoadTasks() {
        String^ filePath = "tasks.txt";
        if (!IO::File::Exists(filePath))    // Создание пустого файла, если его нет
        {
            IO::File::WriteAllText(filePath, "");
            MessageBox::Show("Файл tasks.txt не найден. Создан новый пустой файл.");
            return;
        }
        try {
            IO::StreamReader^ reader = gcnew IO::StreamReader(filePath);
            String^ line;
            while ((line = reader->ReadLine()) != nullptr) {
                array<String^>^ parts = line->Split(';');
                if (parts->Length == 3) {
                    Task^ task = gcnew Task();
                    task->description = parts[0];
                    task->priority = parts[1];
                    task->dueDate = parts[2];
                    tasks->Add(task);
                }
            }
            reader->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при загрузке задач: " + ex->Message);
        }
    }
    private: void SaveTasks() {
        IO::StreamWriter^ writer = gcnew IO::StreamWriter("tasks.txt");
        for each (Task ^ task in tasks) {
            writer->WriteLine(String::Format("{0};{1};{2}", task->description, task->priority, task->dueDate));
        }
        writer->Close();
    }
    private: void UpdateListBox() {
        taskListBox->Items->Clear();
        for each (Task ^ task in tasks) {
            taskListBox->Items->Add(String::Format("{0} | Приоритет: {1} | Срок: {2}", task->description, task->priority, task->dueDate));
        }
    }
    private: System::Void addButton_Click(System::Object^ sender, System::EventArgs^ e) {
        if (String::IsNullOrEmpty(descTextBox->Text) || priorityComboBox->SelectedItem == nullptr) {
            MessageBox::Show("Заполните все поля!");
            return;
        }
        Task^ newTask = gcnew Task();
        newTask->description = descTextBox->Text;
        newTask->priority = priorityComboBox->SelectedItem->ToString();
        newTask->dueDate = dueDatePicker->Value.ToString("dd.MM.yyyy");
        tasks->Add(newTask);
        UpdateListBox();
        descTextBox->Clear();
    }
    private: System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e) {
        if (taskListBox->SelectedIndex != -1) {
            tasks->RemoveAt(taskListBox->SelectedIndex);
            UpdateListBox();
        }
        else {
            MessageBox::Show("Выберите задачу!");
        }
    }
    private: System::Void searchButton_Click(System::Object^ sender, System::EventArgs^ e) {
        String^ keyword = searchTextBox->Text->ToLower();
        taskListBox->Items->Clear();
        for each (Task ^ task in tasks) {
            if (task->description->ToLower()->Contains(keyword)) {
                taskListBox->Items->Add(String::Format("{0} | Приоритет: {1} | Срок: {2}", task->description, task->priority, task->dueDate));
            }
        }
    }
    private: System::Void checkOverdueButton_Click(System::Object^ sender, System::EventArgs^ e) {
        DateTime today = DateTime::Now;
        String^ message = "Просроченные задачи:\n";
        bool hasOverdue = false;
        for each (Task ^ task in tasks) {
            DateTime due;
            if (DateTime::TryParseExact(task->dueDate, "dd.MM.yyyy", nullptr, Globalization::DateTimeStyles::None, due)) {
                if (due < today) {
                    message += task->description + " (Срок: " + task->dueDate + ")\n";
                    hasOverdue = true;
                }
            }
        }
        if (!hasOverdue) message += "Нет просроченных.";
        MessageBox::Show(message);
    }
    private: System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
        SaveTasks();
    }
    private: System::Void descTextBox_GotFocus(System::Object^ sender, System::EventArgs^ e) {
        if (descTextBox->Text == L"Введите название задачи") {
            descTextBox->Text = L"";
            descTextBox->ForeColor = Color::Black;
        }
    }
    private: System::Void descTextBox_LostFocus(System::Object^ sender, System::EventArgs^ e) {
        if (String::IsNullOrWhiteSpace(descTextBox->Text)) {
            descTextBox->Text = L"Введите название задачи";
            descTextBox->ForeColor = Color::Gray;
        }
    }
    private: System::Void MainForm_Resize(System::Object^ sender, System::EventArgs^ e) {
        if (this->WindowState == FormWindowState::Minimized) {
            this->Hide();
        }
    }
    private: System::Void trayIcon_DoubleClick(System::Object^ sender, System::EventArgs^ e) {
        this->Show();
        this->WindowState = FormWindowState::Normal;
    }
    };
}