#pragma once
#include "MainForm.h"

namespace ToDoListGUI
{
    public ref class LoginForm : public System::Windows::Forms::Form
    {
    public:
        // ==================== ГЛОБАЛЬНЫЕ НАСТРОЙКИ (для всей программы) ====================
        static bool IsDarkMode = false;           // Текущая тема (тёмная/светлая)
        static String^ CurrentLanguage = "Russian"; // Текущий язык интерфейса

        LoginForm(void)
        {
            InitializeComponent();
            this->Font = gcnew System::Drawing::Font(L"Warm Pixel", 10.0F, FontStyle::Regular);
            this->Icon = gcnew System::Drawing::Icon("app_icon.ico");

            ApplyTheme(IsDarkMode);          // Применяем тему сразу при запуске
            UpdateLanguage(CurrentLanguage); // Применяем язык сразу при запуске
        }

    protected:
        ~LoginForm()
        {
            if (components) delete components;
        }

    private:
        // ==================== ЭЛЕМЕНТЫ УПРАВЛЕНИЯ ====================
        System::Windows::Forms::TextBox^ txtLogin;
        System::Windows::Forms::TextBox^ txtPassword;
        System::Windows::Forms::Button^ btnLogin;
        System::Windows::Forms::Button^ btnRegister;
        System::Windows::Forms::Button^ btnExit;
        System::Windows::Forms::Button^ btnTheme;
        System::Windows::Forms::ComboBox^ cmbLanguage;
        System::Windows::Forms::PictureBox^ pictureBoxLogo;   // ← Логотип 600×240
        System::Windows::Forms::Label^ lblLogin;
        System::Windows::Forms::Label^ lblPassword;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        // ==================== DESIGNER КОД (автогенерированный + наши правки) ====================
        void InitializeComponent(void)
        {
            this->lblLogin = (gcnew System::Windows::Forms::Label());
            this->txtLogin = (gcnew System::Windows::Forms::TextBox());
            this->lblPassword = (gcnew System::Windows::Forms::Label());
            this->txtPassword = (gcnew System::Windows::Forms::TextBox());
            this->btnLogin = (gcnew System::Windows::Forms::Button());
            this->btnRegister = (gcnew System::Windows::Forms::Button());
            this->btnExit = (gcnew System::Windows::Forms::Button());
            this->btnTheme = (gcnew System::Windows::Forms::Button());
            this->cmbLanguage = (gcnew System::Windows::Forms::ComboBox());
            this->pictureBoxLogo = (gcnew System::Windows::Forms::PictureBox());

            this->SuspendLayout();

            // ====================== ЛОГОТИП ======================
            this->pictureBoxLogo->Location = System::Drawing::Point(20, 20);
            this->pictureBoxLogo->Size = System::Drawing::Size(600, 240);
            this->pictureBoxLogo->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
            this->pictureBoxLogo->Image = System::Drawing::Image::FromFile("logo.png");
            this->pictureBoxLogo->BorderStyle = System::Windows::Forms::BorderStyle::None;
            // =================================================================================

            // ====================== ВЫБОР ЯЗЫКА ======================
            this->cmbLanguage->Location = System::Drawing::Point(480, 280);
            this->cmbLanguage->Size = System::Drawing::Size(140, 21);
            this->cmbLanguage->Items->AddRange(gcnew cli::array<System::Object^>(2) { L"Русский", L"English" });
            this->cmbLanguage->SelectedIndex = 0;
            this->cmbLanguage->SelectedIndexChanged += gcnew System::EventHandler(this, &LoginForm::cmbLanguage_SelectedIndexChanged);

            // ====================== ЭЛЕМЕНТЫ ФОРМЫ ======================
            this->lblLogin->AutoSize = true; this->lblLogin->Location = System::Drawing::Point(50, 330);
            this->txtLogin->Location = System::Drawing::Point(130, 327); this->txtLogin->Size = System::Drawing::Size(200, 20);
            this->lblPassword->AutoSize = true; this->lblPassword->Location = System::Drawing::Point(50, 370);
            this->txtPassword->Location = System::Drawing::Point(130, 367); this->txtPassword->Size = System::Drawing::Size(200, 20);
            this->txtPassword->PasswordChar = '*';

            this->btnLogin->Location = System::Drawing::Point(50, 420); this->btnLogin->Size = System::Drawing::Size(100, 30);
            this->btnRegister->Location = System::Drawing::Point(170, 420); this->btnRegister->Size = System::Drawing::Size(130, 30);
            this->btnExit->Location = System::Drawing::Point(290, 420); this->btnExit->Size = System::Drawing::Size(100, 30);
            this->btnTheme->Location = System::Drawing::Point(50, 470); this->btnTheme->Size = System::Drawing::Size(540, 30);

            this->ClientSize = System::Drawing::Size(640, 550);

            // Подписываем события кнопок (ОБЯЗАТЕЛЬНО после gcnew!)
            this->btnLogin->Click += gcnew System::EventHandler(this, &LoginForm::btnLogin_Click);
            this->btnRegister->Click += gcnew System::EventHandler(this, &LoginForm::btnRegister_Click);
            this->btnExit->Click += gcnew System::EventHandler(this, &LoginForm::btnExit_Click);
            this->btnTheme->Click += gcnew System::EventHandler(this, &LoginForm::btnTheme_Click);

            this->Controls->Add(this->pictureBoxLogo);
            this->Controls->Add(this->cmbLanguage);
            this->Controls->Add(this->btnTheme);
            this->Controls->Add(this->btnExit);
            this->Controls->Add(this->btnRegister);
            this->Controls->Add(this->btnLogin);
            this->Controls->Add(this->txtPassword);
            this->Controls->Add(this->lblPassword);
            this->Controls->Add(this->txtLogin);
            this->Controls->Add(this->lblLogin);

            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

        // ==================== ОБРАБОТЧИКИ СОБЫТИЙ ====================

    private: System::Void cmbLanguage_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
    {
        CurrentLanguage = (cmbLanguage->SelectedIndex == 0) ? "Russian" : "English";
        UpdateLanguage(CurrentLanguage);   // Меняем только текст, без входа в программу
    }

    private: void UpdateLanguage(String^ lang)
    {
        // ====================== МУЛЬТИЯЗЫЧНОСТЬ ======================
        if (lang == "English")
        {
            this->Text = L"Login Screen";
            lblLogin->Text = L"Username:"; lblPassword->Text = L"Password:";
            btnLogin->Text = L"Login"; btnRegister->Text = L"Register";
            btnExit->Text = L"Exit";
            btnTheme->Text = IsDarkMode ? L"Switch to Light Theme" : L"Switch to Dark Theme";
        }
        else // Russian
        {
            this->Text = L"Главное меню — Вход в аккаунт";
            lblLogin->Text = L"Логин:"; lblPassword->Text = L"Пароль:";
            btnLogin->Text = L"Войти"; btnRegister->Text = L"Регистрация";
            btnExit->Text = L"Выйти";
            btnTheme->Text = IsDarkMode ? L"Светлая тема" : L"Тёмная тема";
        }
    }

    private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e)
    {
        // ====================== ВХОД В ПРОГРАММУ ======================
        String^ login = txtLogin->Text->Trim();
        if (login->Length == 0)
        {
            MessageBox::Show("Введите логин!"); return;
        }
        MainForm^ main = gcnew MainForm(login, IsDarkMode, CurrentLanguage);
        this->Hide();
        main->ShowDialog();
        this->Show();
    }

    private: System::Void btnRegister_Click(System::Object^ sender, System::EventArgs^ e)
    {
        MessageBox::Show("Пока регистрация упрощённая.\n\nЛогин: test\nПароль: любой");
    }

    private: System::Void btnExit_Click(System::Object^ sender, System::EventArgs^ e)
    {
        Application::Exit();
    }

    private: System::Void btnTheme_Click(System::Object^ sender, System::EventArgs^ e)
    {
        IsDarkMode = !IsDarkMode;
        ApplyTheme(IsDarkMode);
        // Обновляем текст кнопки под текущий язык
        if (CurrentLanguage == "English")
            btnTheme->Text = IsDarkMode ? L"Switch to Light Theme" : L"Switch to Dark Theme";
        else
            btnTheme->Text = IsDarkMode ? L"Светлая тема" : L"Тёмная тема";
    }

    private: void ApplyTheme(bool dark)
    {
        // ====================== ТЁМНАЯ/СВЕТЛАЯ ТЕМА ======================
        Color back = dark ? Color::FromArgb(30, 30, 30) : Color::White;
        Color fore = dark ? Color::White : Color::Black;
        Color accent = dark ? Color::FromArgb(60, 60, 60) : Color::LightGray;

        this->BackColor = back;
        this->ForeColor = fore;

        for each(Control ^ ctrl in this->Controls)
        {
            ctrl->BackColor = back;
            ctrl->ForeColor = fore;
            if (dynamic_cast<Button^>(ctrl)) ctrl->BackColor = accent;
        }
    }
    };
}