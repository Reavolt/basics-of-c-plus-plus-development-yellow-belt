#include <iostream>
#include <string>

//--------------------------------------------------------------------------------------------------
void SendSms(const std::string& number, const std::string& message)
{
    std::cout << "Send '" << message << "' to number " << number << std::endl;
}
//--------------------------------------------------------------------------------------------------
void SendEmail(const std::string& email, const std::string& message)
{
    std::cout << "Send '" << message << "' to e-mail " << email << std::endl;
}
//--------------------------------------------------------------------------------------------------
class INotifier
{
public:
    virtual void Notify(const std::string& message) const = 0;
};
//--------------------------------------------------------------------------------------------------
class SmsNotifier : public INotifier
{
private:
    const std::string number;
public:
    SmsNotifier(const std::string& num = "+8-800-555-35-35") : number(num)
    {

    }

    void Notify(const std::string& message) const override
    {
        SendSms(number, message);
    }
};
//--------------------------------------------------------------------------------------------------
class EmailNotifier : public INotifier
{
private:
    const std::string e_mail;
public:
    EmailNotifier(const std::string& mail = "yandex@yandex.ru") : e_mail(mail)
    {

    }

    void Notify(const std::string& message) const override
    {
        SendEmail(e_mail, message);
    }
};
//--------------------------------------------------------------------------------------------------
void Notify(INotifier& notifier, const std::string& message)
{
    notifier.Notify(message);
}
//--------------------------------------------------------------------------------------------------
//int main()
//{
//    SmsNotifier sms{ "+7-495-777-77-77" };
//    EmailNotifier email{ "na-derevnyu@dedushke.ru" };
//
//    Notify(sms, "I have White belt in C++");
//    Notify(email, "And want a Yellow one");
//    return 0;
//}
//-------------------------------------------------------------------------------------------------