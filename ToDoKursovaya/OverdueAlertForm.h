#pragma once

namespace ToDoListGUI
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Media;

    public ref class OverdueAlertForm : public System::Windows::Forms::Form
    {
    public:
        OverdueAlertForm(List<String^>^ overdueMessages)
        {
            this->overdueMessages = overdueMessages;
            InitializeComponent();
            this->Load += gcnew System::EventHandler(this, &OverdueAlertForm::OverdueAlertForm_Load);
        }

    protected:
        ~OverdueAlertForm()
        {
            if (components) delete components;
        }

    private:
        List<String^>^ overdueMessages;
        System::Windows::Forms::PictureBox^ pictureBoxGIF;
        System::Windows::Forms::Label^ lblTitle;
        System::Windows::Forms::TextBox^ txtOverdueList;
        System::Windows::Forms::Button^ btnClose;
        System::Media::SoundPlayer^ soundPlayer;

        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->components = (gcnew System::ComponentModel::Container());
            this->pictureBoxGIF = (gcnew System::Windows::Forms::PictureBox());
            this->lblTitle = (gcnew System::Windows::Forms::Label());
            this->txtOverdueList = (gcnew System::Windows::Forms::TextBox());
            this->btnClose = (gcnew System::Windows::Forms::Button());

            this->SuspendLayout();

            this->pictureBoxGIF->Location = System::Drawing::Point(12, 12);
            this->pictureBoxGIF->Size = System::Drawing::Size(376, 240);
            this->pictureBoxGIF->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
            this->pictureBoxGIF->BorderStyle = System::Windows::Forms::BorderStyle::None;

            this->lblTitle->AutoSize = true;
            this->lblTitle->Font = gcnew System::Drawing::Font(L"Warm Pixel", 14.0F, System::Drawing::FontStyle::Bold);
            this->lblTitle->ForeColor = System::Drawing::Color::Red;
            this->lblTitle->Location = System::Drawing::Point(12, 260);
            this->lblTitle->Text = L"? ДЕДЛАЙН ИСТЁК!";

            this->txtOverdueList->Location = System::Drawing::Point(12, 295);
            this->txtOverdueList->Size = System::Drawing::Size(376, 120);
            this->txtOverdueList->Multiline = true;
            this->txtOverdueList->ReadOnly = true;
            this->txtOverdueList->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
            this->txtOverdueList->BackColor = System::Drawing::Color::FromArgb(30, 30, 30);
            this->txtOverdueList->ForeColor = System::Drawing::Color::White;

            this->btnClose->Location = System::Drawing::Point(140, 425);
            this->btnClose->Size = System::Drawing::Size(120, 40);
            this->btnClose->Text = L"Понял, закрыть";
            this->btnClose->Font = gcnew System::Drawing::Font(L"Warm Pixel", 10.0F, System::Drawing::FontStyle::Bold);
            this->btnClose->Click += gcnew System::EventHandler(this, &OverdueAlertForm::btnClose_Click);

            this->ClientSize = System::Drawing::Size(400, 480);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->TopMost = true;
            this->Text = L"ВНИМАНИЕ! Просрочка!";

            this->Controls->Add(this->pictureBoxGIF);
            this->Controls->Add(this->lblTitle);
            this->Controls->Add(this->txtOverdueList);
            this->Controls->Add(this->btnClose);

            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

    private: System::Void OverdueAlertForm_Load(System::Object^ sender, System::EventArgs^ e)
    {
        try
        {
            this->pictureBoxGIF->Image = System::Drawing::Image::FromFile("timesup.gif");
        }
        catch (...)
        {
            this->pictureBoxGIF->BackColor = System::Drawing::Color::Black;
        }

        String^ fullText = L"Просроченные задачи:\n\n";
        for each (String ^ msg in overdueMessages)
            fullText += msg + L"\n";

        txtOverdueList->Text = fullText;

        try
        {
            soundPlayer = gcnew System::Media::SoundPlayer("alarmtimesup.wav");
            soundPlayer->Play();
        }
        catch (...) {}
    }

    private: System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (soundPlayer) soundPlayer->Stop();
        this->Close();
    }
    };
}