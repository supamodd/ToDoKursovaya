#pragma once
#include "MainForm.h"

namespace ToDoListGUI
{
    public ref class LoginForm : public System::Windows::Forms::Form
    {
    public:
        static bool IsDarkMode = false;

        LoginForm(void)
        {
            InitializeComponent();
            this->Font = gcnew System::Drawing::Font(L"Warm Pixel", 10.0F, FontStyle::Regular);
            this->Icon = gcnew System::Drawing::Icon("app_icon.ico");
            ApplyTheme(IsDarkMode);
        }

    protected:
        ~LoginForm()
        {
            if (components) delete components;
        }

    private: System::Windows::Forms::TextBox^ txtLogin;
    private: System::Windows::Forms::TextBox^ txtPassword;
    private: System::Windows::Forms::Button^ btnLogin;
    private: System::Windows::Forms::Button^ btnRegister;
    private: System::Windows::Forms::Button^ btnExit;
    private: System::Windows::Forms::Button^ btnTheme;
    private: System::Windows::Forms::Label^ lblLogin;
    private: System::Windows::Forms::Label^ lblPassword;

    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
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

               this->SuspendLayout();
               // 
               // lblLogin
               // 
               this->lblLogin->AutoSize = true;
               this->lblLogin->Location = System::Drawing::Point(50, 60);
               this->lblLogin->Text = L"Логин:";
               // 
               // txtLogin
               // 
               this->txtLogin->Location = System::Drawing::Point(130, 57);
               this->txtLogin->Size = System::Drawing::Size(200, 20);
               this->txtLogin->Text = L"test";
               // 
               // lblPassword
               // 
               this->lblPassword->AutoSize = true;
               this->lblPassword->Location = System::Drawing::Point(50, 100);
               this->lblPassword->Text = L"Пароль:";
               // 
               // txtPassword
               // 
               this->txtPassword->Location = System::Drawing::Point(130, 97);
               this->txtPassword->Size = System::Drawing::Size(200, 20);
               this->txtPassword->PasswordChar = '*';
               this->txtPassword->Text = L"123";
               // 
               // btnLogin
               // 
               this->btnLogin->Location = System::Drawing::Point(50, 150);
               this->btnLogin->Size = System::Drawing::Size(100, 30);
               this->btnLogin->Text = L"Войти";
               this->btnLogin->Click += gcnew System::EventHandler(this, &LoginForm::btnLogin_Click);
               // 
               // btnRegister
               // 
               this->btnRegister->Location = System::Drawing::Point(140, 150);
               this->btnRegister->Size = System::Drawing::Size(150, 30);
               this->btnRegister->Text = L"Регистрация";
               this->btnRegister->Click += gcnew System::EventHandler(this, &LoginForm::btnRegister_Click);
               // 
               // btnExit
               // 
               this->btnExit->Location = System::Drawing::Point(290, 150);
               this->btnExit->Size = System::Drawing::Size(100, 30);
               this->btnExit->Text = L"Выйти";
               this->btnExit->Click += gcnew System::EventHandler(this, &LoginForm::btnExit_Click);
               // 
               // btnTheme
               // 
               this->btnTheme->Location = System::Drawing::Point(50, 200);
               this->btnTheme->Size = System::Drawing::Size(340, 30);
               this->btnTheme->Text = L"Переключить на тёмную тему";
               this->btnTheme->Click += gcnew System::EventHandler(this, &LoginForm::btnTheme_Click);
               // 
               // LoginForm
               // 
               this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
               this->ClientSize = System::Drawing::Size(440, 280);
               this->Controls->Add(this->btnTheme);
               this->Controls->Add(this->btnExit);
               this->Controls->Add(this->btnRegister);
               this->Controls->Add(this->btnLogin);
               this->Controls->Add(this->txtPassword);
               this->Controls->Add(this->lblPassword);
               this->Controls->Add(this->txtLogin);
               this->Controls->Add(this->lblLogin);
               this->Name = L"LoginForm";
               this->Text = L"Главное меню — Вход в аккаунт";
               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion

    private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e) 
    {
        String^ login = txtLogin->Text->Trim();
        if (login->Length == 0) 
        { 
            MessageBox::Show("Введите логин!"); return; 
        }

        MainForm^ main = gcnew MainForm(login, IsDarkMode);
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
        btnTheme->Text = IsDarkMode ? L"Светлая тема" : L"Тёмная тема";
    }

    private: void ApplyTheme(bool dark) 
    {
        Color back = dark ? Color::FromArgb(30, 30, 30) : Color::White;
        Color fore = dark ? Color::White : Color::Black;
        Color accent = dark ? Color::FromArgb(60, 60, 60) : Color::LightGray;

        this->BackColor = back;
        this->ForeColor = fore;

        for each (Control ^ ctrl in this->Controls) 
        {
            ctrl->BackColor = back;
            ctrl->ForeColor = fore;
            if (dynamic_cast<Button^>(ctrl)) ctrl->BackColor = accent;
        }
    }
    };
}