#pragma once
#include "OverdueAlertForm.h"
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>
namespace ToDoListGUI
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace System::Globalization;
    using namespace System::Media;

    ref struct Task
    {
        String^ description;
        String^ priority;
        String^ dueDateTime;
        String^ fullDescription;
    };

    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(String^ username, bool darkMode, String^ language)
        {
            this->username = username;
            this->currentDarkMode = darkMode;
            this->currentLanguage = language;

            InitializeComponent();

            this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
        }

    protected:
        ~MainForm()
        {
            if (components) delete components;
        }

    private:
        String^ currentLanguage;
        String^ username;
        bool currentDarkMode;

        System::Windows::Forms::ListBox^ taskListBox;
        System::Windows::Forms::TextBox^ descTextBox;
        System::Windows::Forms::TextBox^ fullDescriptionTextBox;
        System::Windows::Forms::Label^ lblFullDescription;
        System::Windows::Forms::ComboBox^ priorityComboBox;
        System::Windows::Forms::DateTimePicker^ dueDatePicker;
        System::Windows::Forms::Button^ addButton;
        System::Windows::Forms::Button^ deleteButton;
        System::Windows::Forms::TextBox^ searchTextBox;
        System::Windows::Forms::Button^ searchButton;
        System::Windows::Forms::Button^ checkOverdueButton;
        System::Windows::Forms::NotifyIcon^ trayIcon;
        System::Windows::Forms::Button^ btnLogout;
        System::Windows::Forms::Timer^ notificationTimer;

        System::ComponentModel::Container^ components;
        Collections::Generic::List<Task^>^ tasks;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->taskListBox = (gcnew System::Windows::Forms::ListBox());
            this->descTextBox = (gcnew System::Windows::Forms::TextBox());
            this->fullDescriptionTextBox = (gcnew System::Windows::Forms::TextBox());
            this->lblFullDescription = (gcnew System::Windows::Forms::Label());
            this->priorityComboBox = (gcnew System::Windows::Forms::ComboBox());
            this->dueDatePicker = (gcnew System::Windows::Forms::DateTimePicker());
            this->addButton = (gcnew System::Windows::Forms::Button());
            this->deleteButton = (gcnew System::Windows::Forms::Button());
            this->searchTextBox = (gcnew System::Windows::Forms::TextBox());
            this->searchButton = (gcnew System::Windows::Forms::Button());
            this->checkOverdueButton = (gcnew System::Windows::Forms::Button());
            this->trayIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
            this->btnLogout = (gcnew System::Windows::Forms::Button());

            this->SuspendLayout();

            // ==================== taskListBox ====================
            this->taskListBox->FormattingEnabled = true;
            this->taskListBox->Location = System::Drawing::Point(100, 47);
            this->taskListBox->Size = System::Drawing::Size(605, 150);
            this->taskListBox->TabIndex = 0;
            this->taskListBox->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
            this->taskListBox->DrawItem += gcnew System::Windows::Forms::DrawItemEventHandler(this, &MainForm::taskListBox_DrawItem);
            this->taskListBox->DoubleClick += gcnew System::EventHandler(this, &MainForm::taskListBox_DoubleClick);

            // ==================== Название задачи ====================
            this->descTextBox->Location = System::Drawing::Point(101, 218);
            this->descTextBox->Size = System::Drawing::Size(486, 20);
            this->descTextBox->TabIndex = 1;
            this->descTextBox->Text = L"Введите название задачи";
            this->descTextBox->GotFocus += gcnew System::EventHandler(this, &MainForm::descTextBox_GotFocus);
            this->descTextBox->LostFocus += gcnew System::EventHandler(this, &MainForm::descTextBox_LostFocus);

            // ==================== Полное описание ====================
            this->fullDescriptionTextBox->Location = System::Drawing::Point(101, 268);
            this->fullDescriptionTextBox->Size = System::Drawing::Size(486, 80);
            this->fullDescriptionTextBox->Multiline = true;
            this->fullDescriptionTextBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
            this->fullDescriptionTextBox->TabIndex = 2;
            this->fullDescriptionTextBox->Text = L"Подробное описание (можно писать много строк)";

            // ←←← ДОБАВЬ ЭТИ ДВЕ СТРОКИ ↓↓↓
            this->fullDescriptionTextBox->GotFocus += gcnew System::EventHandler(this, &MainForm::fullDescriptionTextBox_GotFocus);
            this->fullDescriptionTextBox->LostFocus += gcnew System::EventHandler(this, &MainForm::fullDescriptionTextBox_LostFocus);

            // ==================== Остальные элементы ====================
            this->priorityComboBox->Location = System::Drawing::Point(101, 365);
            this->priorityComboBox->Size = System::Drawing::Size(173, 21);
            this->priorityComboBox->TabIndex = 3;
            this->priorityComboBox->Items->AddRange(gcnew cli::array<System::Object^>(3) { L"low", L"medium", L"high" });

            this->searchTextBox->Location = System::Drawing::Point(340, 365);
            this->searchTextBox->Size = System::Drawing::Size(229, 20);
            this->searchTextBox->TabIndex = 4;
            this->searchTextBox->Text = L"Введите ключевые слова для поиска";

            this->dueDatePicker->Location = System::Drawing::Point(101, 404);
            this->dueDatePicker->Size = System::Drawing::Size(200, 20);
            this->dueDatePicker->TabIndex = 5;
            this->dueDatePicker->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
            this->dueDatePicker->CustomFormat = L"dd.MM.yyyy HH:mm";

            this->addButton->Location = System::Drawing::Point(101, 445);
            this->addButton->Size = System::Drawing::Size(90, 23);
            this->addButton->TabIndex = 6;
            this->addButton->Text = L"Добавить";
            this->addButton->Click += gcnew System::EventHandler(this, &MainForm::addButton_Click);

            this->deleteButton->Location = System::Drawing::Point(182, 445);
            this->deleteButton->Size = System::Drawing::Size(90, 23);
            this->deleteButton->TabIndex = 7;
            this->deleteButton->Text = L"Удалить";
            this->deleteButton->Click += gcnew System::EventHandler(this, &MainForm::deleteButton_Click);

            this->searchButton->Location = System::Drawing::Point(594, 361);
            this->searchButton->Size = System::Drawing::Size(75, 23);
            this->searchButton->TabIndex = 8;
            this->searchButton->Text = L"Поиск";
            this->searchButton->Click += gcnew System::EventHandler(this, &MainForm::searchButton_Click);

            this->checkOverdueButton->Location = System::Drawing::Point(594, 444);
            this->checkOverdueButton->Size = System::Drawing::Size(112, 23);
            this->checkOverdueButton->TabIndex = 9;
            this->checkOverdueButton->Text = L"Просроченные";
            this->checkOverdueButton->Click += gcnew System::EventHandler(this, &MainForm::checkOverdueButton_Click);

            // trayIcon
            this->trayIcon->DoubleClick += gcnew System::EventHandler(this, &MainForm::trayIcon_DoubleClick);

            // ==================== Кнопка выхода ====================
            this->btnLogout->Size = System::Drawing::Size(140, 50);
            this->btnLogout->Text = L"Выйти из аккаунта";
            this->btnLogout->Location = System::Drawing::Point(660, 690);
            this->btnLogout->Click += gcnew System::EventHandler(this, &MainForm::btnLogout_Click);

            this->ClientSize = System::Drawing::Size(804, 750);

            // Добавляем ВСЕ элементы
            this->Controls->Add(this->taskListBox);
            this->Controls->Add(this->descTextBox);
            this->Controls->Add(this->lblFullDescription);
            this->Controls->Add(this->fullDescriptionTextBox);
            this->Controls->Add(this->priorityComboBox);
            this->Controls->Add(this->dueDatePicker);
            this->Controls->Add(this->addButton);
            this->Controls->Add(this->deleteButton);
            this->Controls->Add(this->searchTextBox);
            this->Controls->Add(this->searchButton);
            this->Controls->Add(this->checkOverdueButton);
            this->Controls->Add(this->btnLogout);

            this->ResumeLayout(false);
            this->PerformLayout();

            this->searchTextBox->GotFocus += gcnew System::EventHandler(this, &MainForm::searchTextBox_GotFocus);
            this->searchTextBox->LostFocus += gcnew System::EventHandler(this, &MainForm::searchTextBox_LostFocus);
        }
#pragma endregion

        // ====================== ЗАГРУЗКА ФОРМЫ ======================
    private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e)
    {
        notificationTimer = gcnew System::Windows::Forms::Timer();
        notificationTimer->Interval = 30000;
        notificationTimer->Tick += gcnew System::EventHandler(this, &MainForm::notificationTimer_Tick);
        notificationTimer->Start();

        tasks = gcnew Collections::Generic::List<Task^>();
        LoadTasks();
        UpdateListBox();

        this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);

        descTextBox->ForeColor = Color::Gray;
        fullDescriptionTextBox->ForeColor = Color::Gray;

        this->Font = gcnew System::Drawing::Font(L"Warm Pixel", 10.0F, FontStyle::Regular);

        try { this->Icon = gcnew System::Drawing::Icon("app_icon.ico"); }
        catch (...) {  }

        ApplyTheme(currentDarkMode);
        UpdateLanguage(currentLanguage);

        this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
    }
#pragma endregion

        // ====================== ВСЕ ОСТАЛЬНЫЕ МЕТОДЫ ======================
    private: void LoadTasks()
    {
        String^ filePath = "tasks_" + username + ".txt";
        if (!IO::File::Exists(filePath)) { IO::File::WriteAllText(filePath, ""); return; }
        try {
            IO::StreamReader^ reader = gcnew IO::StreamReader(filePath);
            String^ line;
            while ((line = reader->ReadLine()) != nullptr)
            {
                array<String^>^ parts = line->Split(gcnew array<wchar_t>{';'}, 4);
                if (parts->Length >= 4) {
                    Task^ task = gcnew Task();
                    task->description = parts[0];
                    task->priority = parts[1];
                    task->dueDateTime = parts[2];
                    task->fullDescription = parts[3];
                    tasks->Add(task);
                }
            }
            reader->Close();
        }
        catch (...) {}
    }

    private: void SaveTasks()
    {
        String^ filePath = "tasks_" + username + ".txt";
        IO::StreamWriter^ writer = gcnew IO::StreamWriter(filePath);
        for each(Task ^ task in tasks)
            writer->WriteLine(String::Format("{0};{1};{2};{3}", task->description, task->priority, task->dueDateTime, task->fullDescription));
        writer->Close();
    }

    private: void UpdateListBox()
    {
        taskListBox->Items->Clear();
        for each(Task ^ task in tasks)
        {
            String^ shortDesc = task->fullDescription->Length > 60
                ? task->fullDescription->Substring(0, 57) + "..."
                : task->fullDescription;
            taskListBox->Items->Add(String::Format("{0} | Приоритет: {1} | Срок: {2} | Описание: {3}",
                task->description, task->priority, task->dueDateTime, shortDesc));
        }
    }

    private: System::Void addButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (String::IsNullOrEmpty(descTextBox->Text))
        {
            MessageBox::Show("Введите название задачи!");
            return;
        }
        Task^ newTask = gcnew Task();
        newTask->description = descTextBox->Text;
        newTask->priority = priorityComboBox->SelectedItem != nullptr ? priorityComboBox->SelectedItem->ToString() : L"medium";
        newTask->dueDateTime = dueDatePicker->Value.ToString("dd.MM.yyyy HH:mm");
        newTask->fullDescription = fullDescriptionTextBox->Text;

        tasks->Add(newTask);
        UpdateListBox();
        descTextBox->Clear();
        fullDescriptionTextBox->Clear();
    }

    private: System::Void taskListBox_DoubleClick(System::Object^ sender, System::EventArgs^ e)
    {
        if (taskListBox->SelectedIndex == -1) return;
        Task^ task = tasks[taskListBox->SelectedIndex];
        MessageBox::Show(task->fullDescription, "Полное описание: " + task->description, MessageBoxButtons::OK, MessageBoxIcon::Information);
    }

    private: System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (taskListBox->SelectedIndex != -1)
        {
            tasks->RemoveAt(taskListBox->SelectedIndex);
            UpdateListBox();
        }
        else {
            MessageBox::Show("Выберите задачу!");
        }
    }

    private: System::Void searchButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        String^ keyword = searchTextBox->Text->ToLower();
        taskListBox->Items->Clear();
        for each(Task ^ task in tasks) {
            if (task->description->ToLower()->Contains(keyword)) {
                taskListBox->Items->Add(String::Format("{0} | Приоритет: {1} | Срок: {2}",
                    task->description, task->priority, task->dueDateTime));
            }
        }
    }

           // ====================== ПРОВЕРКА ПРОСРОЧЕННЫХ ======================
    private: System::Void checkOverdueButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        String^ message = L"Просроченные задачи:\n";
        bool hasOverdue = false;
        for each(Task ^ task in tasks) {
            DateTime due;
            if (DateTime::TryParseExact(task->dueDateTime, "dd.MM.yyyy HH:mm", nullptr, Globalization::DateTimeStyles::None, due))
            {
                if (due < DateTime::Now)
                {
                    message += task->description + L" (Срок: " + task->dueDateTime + L")\n";
                    hasOverdue = true;
                }
            }
        }
        if (!hasOverdue) message += L"Нет просроченных.";
        MessageBox::Show(message);
    }

    private: System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
    {
        SaveTasks();
    }

    private: System::Void descTextBox_GotFocus(System::Object^ sender, System::EventArgs^ e)
    {
        if (descTextBox->Text == L"Введите название задачи")
        {
            descTextBox->Text = L"";
            descTextBox->ForeColor = currentDarkMode ? Color::White : Color::Black;
        }
    }

    private: System::Void descTextBox_LostFocus(System::Object^ sender, System::EventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(descTextBox->Text))
        {
            descTextBox->Text = L"Введите название задачи";
            descTextBox->ForeColor = currentDarkMode ? Color::White : Color::Black;
        }
    }

    private: System::Void searchTextBox_GotFocus(System::Object^ sender, System::EventArgs^ e)
    {
        if (searchTextBox->Text == L"Введите ключевые слова для поиска")
        {
            searchTextBox->Text = L"";
            searchTextBox->ForeColor = currentDarkMode ? Color::White : Color::Black;
        }
    }

    private: System::Void searchTextBox_LostFocus(System::Object^ sender, System::EventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(searchTextBox->Text))
        {
            searchTextBox->Text = L"Введите ключевые слова для поиска";
            searchTextBox->ForeColor = currentDarkMode ? Color::White : Color::Black;
        }
    }

        private: System::Void fullDescriptionTextBox_GotFocus(System::Object^ sender, System::EventArgs^ e)
        {
            if (fullDescriptionTextBox->Text == L"Подробное описание (можно писать много строк)")
            {
                fullDescriptionTextBox->Text = L"";
                fullDescriptionTextBox->ForeColor = currentDarkMode ? Color::White : Color::Black;
            }
        }

    private: System::Void fullDescriptionTextBox_LostFocus(System::Object^ sender, System::EventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(fullDescriptionTextBox->Text))
        {
            fullDescriptionTextBox->Text = L"Подробное описание (можно писать много строк)";
            fullDescriptionTextBox->ForeColor = currentDarkMode ? Color::Gray : Color::DarkGray;
        }
    }

    private: System::Void MainForm_Resize(System::Object^ sender, System::EventArgs^ e)
    {
        if (this->WindowState == FormWindowState::Minimized)
        {
            this->Hide();
        }
    }

    private: System::Void trayIcon_DoubleClick(System::Object^ sender, System::EventArgs^ e)
    {
        this->Show();
        this->WindowState = FormWindowState::Normal;
    }

    private: System::Void btnLogout_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->Close();
    }

    private: void ApplyTheme(bool dark)
    {
        Color back = dark ? Color::FromArgb(30, 30, 30) : Color::White;
        Color fore = dark ? Color::White : Color::Black;
        Color accent = dark ? Color::FromArgb(60, 60, 60) : Color::LightGray;
        this->BackColor = back;
        this->ForeColor = fore;
        for each(Control ^ ctrl in this->Controls)
        {
            ctrl->BackColor = back;
            ctrl->ForeColor = fore;
            if (dynamic_cast<Button^>(ctrl))
                ctrl->BackColor = accent;
            if (dynamic_cast<TextBox^>(ctrl))
            {
                ctrl->ForeColor = fore;
                ctrl->BackColor = dark ? Color::FromArgb(45, 45, 45) : Color::White;
            }
        }
        descTextBox->ForeColor = dark ? Color::Gray : Color::DarkGray;
        searchTextBox->ForeColor = dark ? Color::Gray : Color::DarkGray;
        fullDescriptionTextBox->ForeColor = dark ? Color::Gray : Color::DarkGray;
    }

    private: void UpdateLanguage(String^ lang)
    {
        if (lang == "English")
        {
            this->Text = L"To-Do List";
            descTextBox->Text = L"Enter task title";
            searchTextBox->Text = L"Enter keywords for search";
            addButton->Text = L"Add";
            deleteButton->Text = L"Delete";
            searchButton->Text = L"Search";
            checkOverdueButton->Text = L"Overdue";
            btnLogout->Text = L"Logout";
        }
        else
        {
            this->Text = L"MainForm";
            descTextBox->Text = L"Введите название задачи";
            searchTextBox->Text = L"Введите ключевые слова для поиска";
            addButton->Text = L"Добавить";
            deleteButton->Text = L"Удалить";
            searchButton->Text = L"Поиск";
            checkOverdueButton->Text = L"Просроченные";
            btnLogout->Text = L"Выйти из аккаунта";
        }
    }

           // ====================== ЦВЕТОВАЯ ПОДСВЕТКА ЗАДАЧ В СПИСКЕ ======================
    private: System::Void taskListBox_DrawItem(System::Object^ sender, System::Windows::Forms::DrawItemEventArgs^ e)
    {
        if (e->Index < 0 || e->Index >= tasks->Count) return;

        Task^ task = tasks[e->Index];
        String^ text = taskListBox->Items[e->Index]->ToString();

        Color textColor = this->ForeColor;

        DateTime due;
        if (DateTime::TryParseExact(task->dueDateTime, "dd.MM.yyyy HH:mm", nullptr,
            Globalization::DateTimeStyles::None, due))
        {
            double daysLeft = (due - DateTime::Now).TotalDays;
            if (daysLeft < 0 || daysLeft <= 3)      textColor = Color::Red;           // ≤ 3 дня или просрочено
            else if (daysLeft <= 7)                 textColor = Color::Orange;        // ≤ 1 неделя
            else if (daysLeft <= 14)                textColor = Color::LimeGreen;     // ≤ 2 недели
        }

        e->DrawBackground();
        SolidBrush^ brush = gcnew SolidBrush(textColor);
        e->Graphics->DrawString(text, e->Font, brush, e->Bounds);
        e->DrawFocusRectangle();
    }

           // ====================== УВЕДОМЛЕНИЯ + ЗВУК КАЖДЫЕ 30 СЕКУНД ======================
    private: System::Void notificationTimer_Tick(System::Object^ sender, System::EventArgs^ e)
    {
        List<String^>^ overdueMessages = gcnew List<String^>();

        for each (Task ^ task in tasks)
        {
            DateTime due;
            if (DateTime::TryParseExact(task->dueDateTime, "dd.MM.yyyy HH:mm", nullptr,
                Globalization::DateTimeStyles::None, due) && due <= DateTime::Now)
            {
                overdueMessages->Add(L"• " + task->description + L" (до " + task->dueDateTime + L")");
            }
        }

        if (overdueMessages->Count > 0)
        {
            OverdueAlertForm^ alert = gcnew OverdueAlertForm(overdueMessages);
            alert->ShowDialog();
        }
    }
    };
}