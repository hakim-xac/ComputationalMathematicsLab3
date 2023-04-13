#include "NumericalDifferentiation.h"
#include "Functions.h"
#include <iomanip>
void KHAS::NumericalDifferentiation::loop() const noexcept
{
    size_t cmd{};
    while (cmd != 3) {
        system("cls");
        showHeader();

        if (!menu_.runCommand(cmd)) showUnknownCommand();

        menu_.show();

        cmd = showReadCommand();
    }
}

void KHAS::NumericalDifferentiation::init() noexcept
{
    menu_.insert("Вывод таблицы значений функции с рассчитанным шагом", [&]() { printValueTable(); });
    menu_.insert("Вывод таблицы точных и приближенных значений производных", [&] { std::cout << "22222222222\n"; });
    menu_.insert("Выход", [] {});
}

void KHAS::NumericalDifferentiation::showHeader(std::ostream& out) const noexcept
{
    auto delim{ delimiter('-', data_.width_screen) };
    std::string subject_header{ "Дисциплина:" };
    std::string subject_name{ "Вычислительная математика" };
    std::string student_header{ "Студент:" };
    std::string student_name{ "Хакимов А.С." };
    std::string group_header{ "Группа:" };
    std::string group_name{ "ПБ-11" };
    std::string variant_header{ "Вариант:" };
    std::string variant_name{ "№1" };
    std::string theme_header{ "Тема:" };
    std::string theme_name{ "Численное дифференцирование" };

    size_t width{ (data_.width_screen - 3) / 2 - 2 };
    size_t offset{ data_.width_screen % 2 == 0 };
    assert(width >= 0 && "you need to increase the width of the output on the screen");
    assert(subject_header.size() <= width && subject_name.size() <= width);
    assert(student_header.size() <= width && student_name.size() <= width);
    assert(group_header.size() <= width && group_name.size() <= width);
    assert(variant_header.size() <= width && variant_name.size() <= width);
    assert(theme_header.size() <= width && theme_name.size() <= width);


    out << delim << "\n";
    out << "| " << std::setw(width) << std::left << subject_header << " | " << std::setw(width + offset) << std::right << subject_name << " |\n";
    out << "| " << std::setw(width) << std::left << student_header << " | " << std::setw(width + offset) << std::right << student_name << " |\n";
    out << "| " << std::setw(width) << std::left << group_header << " | " << std::setw(width + offset) << std::right << group_name << " |\n";
    out << "| " << std::setw(width) << std::left << variant_header << " | " << std::setw(width + offset) << std::right << variant_name << " |\n";
    out << "| " << std::setw(width) << std::left << theme_header << " | " << std::setw(width + offset) << std::right << theme_name << " |\n";
    out << delim << "\n";
}

void KHAS::NumericalDifferentiation::showUnknownCommand(std::ostream& out) const noexcept
{
    auto delim{ delimiter('-', data_.width_screen) };
    out << delim << "\n";
    out << generateString("Неизвестная команда", data_.width_screen) << "\n";
    out << delim << "\n";
}

void KHAS::NumericalDifferentiation::printValueTable(std::ostream& out) const noexcept
{
    size_t width{ (data_.width_screen - 3) / 2 - 2 };
    size_t width_left{ width >> 1 };
    size_t width_right{ width_left+3 };
    size_t offset{ data_.width_screen % 2 == 0 };

    auto delim{ delimiter('-', data_.width_screen) };
    out << delim << "\n";
    out << generateString("Таблицы значений функции с рассчитанным шагом", data_.width_screen) << "\n";
    out << delim << "\n";
    out << "| " << std::setw(width_left) << std::right << " Xi " << std::setw(width_right) << " | "
        << std::setw(width_left) << std::right << "f(Xi)" << std::setw(width_right+offset) << " |\n"
        << delim << "\n";

    for (auto&& [xi, fxi] : value_table_) {
        out << "| " << std::fixed << std::setprecision(4)
            << std::setw(width_left) << std::right << xi << std::setw(width_right) << " | "
            << std::setw(width_left) << std::right << fxi << std::setw(width_right+offset) << " |\n";
        out << delim << "\n";
    }
}

double KHAS::NumericalDifferentiation::mathFunc(double x) const noexcept
{
    return 0.0;
}

size_t KHAS::NumericalDifferentiation::showReadCommand(std::istream& in) const noexcept
{
    size_t cmd;
    std::string cmd_name{ "Введите команду:" };
    std::cout << cmd_name << delimiter('_', data_.width_screen - cmd_name.size())
        << delimiter('\b', data_.width_screen - cmd_name.size());

    if (!(in >> cmd)) cmd = -1;
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return cmd;
}
