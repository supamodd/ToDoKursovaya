#include "LoginForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    ToDoListGUI::LoginForm^ login = gcnew ToDoListGUI::LoginForm();
    Application::Run(login);

    return 0;
}