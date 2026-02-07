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

    ref struct Task {
        String^ description;
        String^ priority;
        String^ dueDate;
    };

    public ref class MainForm : public System::Windows::Forms::Form {
    public:
        MainForm(void) {
            InitializeComponent();
            tasks = gcnew Collections::Generic::List<Task^>();
            LoadTasks();
        }

    protected:
        ~MainForm() {
            if (components) {
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

    private: Collections::Generic::List<Task^>^ tasks;

    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void) {
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
               this->taskListBox->Location = System::Drawing::Point(12, 12);
               this->taskListBox->Name = L"taskListBox";
               this->taskListBox->Size = System::Drawing::Size(760, 200);
               this->taskListBox->TabIndex = 0;
               // 
               // descTextBox
               // 
               this->descTextBox->Location = System::Drawing::Point(12, 220);
               this->descTextBox->Name = L"descTextBox";
               this->descTextBox->Size = System::Drawing::Size(300, 20);
               this->descTextBox->TabIndex = 1;
               this->descTextBox->Text = L"Описание задачи";
               // 
               // priorityComboBox
               // 
               this->priorityComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"low", L"medium", L"high" });
               this->priorityComboBox->Location = System::Drawing::Point(320, 220);
               this->priorityComboBox->Name = L"priorityComboBox";
               this->priorityComboBox->Size = System::Drawing::Size(100, 21);
               this->priorityComboBox->TabIndex = 2;
               // 
               // dueDatePicker
               // 
               this->dueDatePicker->Location = System::Drawing::Point(430, 220);
               this->dueDatePicker->Name = L"dueDatePicker";
               this->dueDatePicker->Size = System::Drawing::Size(200, 20);
               this->dueDatePicker->TabIndex = 3;
               // 
               // addButton
               // 
               this->addButton->Location = System::Drawing::Point(640, 220);
               this->addButton->Name = L"addButton";
               this->addButton->Size = System::Drawing::Size(75, 23);
               this->addButton->TabIndex = 4;
               this->addButton->Text = L"Добавить";
               this->addButton->Click += gcnew System::EventHandler(this, &MainForm::addButton_Click);
               // 
               // deleteButton
               // 
               this->deleteButton->Location = System::Drawing::Point(12, 250);
               this->deleteButton->Name = L"deleteButton";
               this->deleteButton->Size = System::Drawing::Size(75, 23);
               this->deleteButton->TabIndex = 5;
               this->deleteButton->Text = L"Удалить";
               this->deleteButton->Click += gcnew System::EventHandler(this, &MainForm::deleteButton_Click);
               // 
               // searchTextBox
               // 
               this->searchTextBox->Location = System::Drawing::Point(100, 250);
               this->searchTextBox->Name = L"searchTextBox";
               this->searchTextBox->Size = System::Drawing::Size(200, 20);
               this->searchTextBox->TabIndex = 6;
               this->searchTextBox->Text = L"Ключевое слово";
               // 
               // searchButton
               // 
               this->searchButton->Location = System::Drawing::Point(310, 250);
               this->searchButton->Name = L"searchButton";
               this->searchButton->Size = System::Drawing::Size(75, 23);
               this->searchButton->TabIndex = 7;
               this->searchButton->Text = L"Поиск";
               this->searchButton->Click += gcnew System::EventHandler(this, &MainForm::searchButton_Click);
               // 
               // checkOverdueButton
               // 
               this->checkOverdueButton->Location = System::Drawing::Point(400, 250);
               this->checkOverdueButton->Name = L"checkOverdueButton";
               this->checkOverdueButton->Size = System::Drawing::Size(120, 23);
               this->checkOverdueButton->TabIndex = 8;
               this->checkOverdueButton->Text = L"Просроченные";
               this->checkOverdueButton->Click += gcnew System::EventHandler(this, &MainForm::checkOverdueButton_Click);
               // 
               // MainForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
               this->ClientSize = System::Drawing::Size(784, 300);
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
               this->Text = L"To-Do List";
               this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
               this->ResumeLayout(false);
               this->PerformLayout();

           }
#pragma endregion

private: void LoadTasks() {
    String^ filePath = "tasks.txt";

    if (!IO::File::Exists(filePath))       // Создаём пустой файл, если его нет
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
    };
}