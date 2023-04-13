#include "NumericalDifferentiation.h"
#include "Functions.h"
#include <iomanip>
#include <cassert>
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
    assert(data_.right_range > data_.left_range);
    assert(data_.step > 0);

    size_t size_data{ static_cast<size_t>(std::round((data_.right_range - data_.left_range) / data_.step)) };
    assert(size_data > 0);

    fillValueTable(size_data);
    fillExcatlyAndApproximatlyValueTable();

    menu_.insert("Вывод таблицы значений функции с рассчитанным шагом", [&]() { printValueTable(); });
    menu_.insert("Вывод таблицы точных и приближенных значений производных", [&] { printExactAndApproximateValues(); });
    menu_.insert("Выход", [] {});
}

void KHAS::NumericalDifferentiation::fillValueTable(size_t size) noexcept
{
    constexpr const size_t prec{ 4 };
    value_table_.reserve(size);
    for (auto i{ data_.left_range }, ie{ data_.right_range }, step{ data_.step }; i < ie; i += step) {
        value_table_.emplace_back(i, precision(mathFunc(i), prec), 0);
    }
}

void KHAS::NumericalDifferentiation::fillExcatlyAndApproximatlyValueTable() noexcept
{
    constexpr const size_t prec{ 4 };
    size_t size{ value_table_.size() };

    excatly_and_approximatly_value_table_.reserve(size-2);
    assert(size > 2);
    for (size_t i{}, ie{ size-2 }; i != ie; ++i) {
        double x{ 2 + data_.step * (i) };
        double x_excatly{ mathFuncExcatly(x) };
        double x_aproximatly{ mathNumericalDifferentiation(value_table_[i].dfx_excatly, value_table_[i+2].dfx_excatly) };

        excatly_and_approximatly_value_table_.emplace_back(x, precision(x_excatly, prec), precision(x_aproximatly, prec));
    }
}

void KHAS::NumericalDifferentiation::showHeader(std::ostream& out) const noexcept
{
    auto delim{ delimiter('-', width_screen_) };
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

    std::string left_range_header{ "Минимальная граница:" };
    std::string left_range_name{ typeToString(data_.left_range, 4).first };
    std::string right_range_header{ "Максимальная граница:" };
    std::string right_range_name{ typeToString(data_.right_range, 4ull).first };
    std::string step_header{ "Шаг:" };
    std::string step_name{ typeToString(data_.step, 4ull).first };
    std::string error_header{ "Погрешность:" };
    std::string error_name{ typeToString(data_.error, 4ull).first };

    size_t width{ (width_screen_ - 3) / 2 - 2 };
    size_t offset{ width_screen_ % 2 == 0 };
    assert(width >= 0 && "you need to increase the width of the output on the screen");
    assert(subject_header.size() <= width && subject_name.size() <= width);
    assert(student_header.size() <= width && student_name.size() <= width);
    assert(group_header.size() <= width && group_name.size() <= width);
    assert(variant_header.size() <= width && variant_name.size() <= width);
    assert(theme_header.size() <= width && theme_name.size() <= width);

    assert(left_range_header.size() <= width && left_range_name.size() <= width);
    assert(right_range_header.size() <= width && right_range_name.size() <= width);
    assert(step_header.size() <= width && step_name.size() <= width);
    assert(error_header.size() <= width && error_name.size() <= width);


    out << delim << "\n";
    out << "| " << std::setw(width) << std::left << subject_header << " | " << std::setw(width + offset) << std::right << subject_name << " |\n";
    out << "| " << std::setw(width) << std::left << student_header << " | " << std::setw(width + offset) << std::right << student_name << " |\n";
    out << "| " << std::setw(width) << std::left << group_header << " | " << std::setw(width + offset) << std::right << group_name << " |\n";
    out << "| " << std::setw(width) << std::left << variant_header << " | " << std::setw(width + offset) << std::right << variant_name << " |\n";
    out << "| " << std::setw(width) << std::left << theme_header << " | " << std::setw(width + offset) << std::right << theme_name << " |\n";
    out << delim << "\n";
    out << "| " << std::setw(width) << std::left << left_range_header << " | " << std::setw(width + offset) << std::right << left_range_name << " |\n";
    out << "| " << std::setw(width) << std::left << right_range_header << " | " << std::setw(width + offset) << std::right << right_range_name << " |\n";
    out << "| " << std::setw(width) << std::left << step_header << " | " << std::setw(width + offset) << std::right << step_name << " |\n";
    out << "| " << std::setw(width) << std::left << error_header << " | " << std::setw(width + offset) << std::right << error_name << " |\n";
    
    out << delim << "\n";
}

void KHAS::NumericalDifferentiation::showUnknownCommand(std::ostream& out) const noexcept
{
    auto delim{ delimiter('-', width_screen_) };
    out << delim << "\n";
    out << generateString("Неизвестная команда", width_screen_) << "\n";
    out << delim << "\n";
}

void KHAS::NumericalDifferentiation::printValueTable(std::ostream& out) const noexcept
{
    constexpr const size_t precision{ 4 };
    constexpr const size_t width_step{ 8 };
    size_t width{ (width_screen_ - width_step) >> 1 };
    size_t offset{ width_screen_ - width_step - (width << 1) };

    auto delim{ delimiter('-', width_screen_) };
    out << delim << "\n";
    out << generateString("Таблица значений функции с рассчитанным шагом", width_screen_) << "\n";
    out << delim << "\n";
    out << generateString ("шаг", width_step) << generateString("Xi", width) << generateString("f(Xi)", width + offset) << "\n";
    out << delim << "\n";

    for (size_t i{}; auto && elem : value_table_) {
        out << generateString(typeToString(++i).first, width_step)
            << generateString(typeToString(elem.x, precision).first, width)
            << generateString(typeToString(elem.dfx_excatly, precision).first, width + offset)
            << "\n" << delim << "\n";
    }
}

void KHAS::NumericalDifferentiation::printExactAndApproximateValues(std::ostream& out) const noexcept
{
    constexpr const size_t width_step{ 8 };
    constexpr const size_t precision{ 4 };
    size_t width{ (width_screen_ - width_step) / 3 };
    size_t div_width{ width_screen_ - width_step - width * 3 };

    size_t first_offset{ div_width == 1 || div_width == 2 ? 1ull : 0ull };
    size_t second_offset{ div_width == 2 ? 1ull : 0ull };

    auto delim{ delimiter('-', width_screen_) };
    out << delim << "\n";
    out << generateString("Таблица точных и приближенных значений производных", width_screen_) << "\n";
    out << delim << "\n";
    out << generateString("шаг", width_step)
        << generateString("Xi", width+first_offset) 
        << generateString("f'(x) точн.", width) 
        << generateString("f'(x) прибл.", width + second_offset) 
        << "\n";
    out << delim << "\n";


    for (size_t i{};  auto && elem : excatly_and_approximatly_value_table_) {
        out << generateString(typeToString(++i).first, width_step)
            << generateString(typeToString(elem.x, precision).first, width+first_offset)
            << generateString(typeToString(elem.dfx_excatly, precision).first, width)
            << generateString(typeToString(elem.dfx_approximately, precision).first, width+second_offset)
            << "\n" << delim << "\n";
    }
}

double KHAS::NumericalDifferentiation::mathFunc(double x) const noexcept
{
    return 0.5 * sin(2 * x);
}

double KHAS::NumericalDifferentiation::mathFuncExcatly(double x) const noexcept
{
    return cos(2 * x);
}

double KHAS::NumericalDifferentiation::mathNumericalDifferentiation(double fx, double fx2) const noexcept
{
    return (fx2 - fx) / (2 * data_.step);
}

size_t KHAS::NumericalDifferentiation::showReadCommand(std::istream& in) const noexcept
{
    size_t cmd;
    std::string cmd_name{ "Введите команду:" };
    std::cout << cmd_name << delimiter('_', width_screen_ - cmd_name.size())
        << delimiter('\b', width_screen_ - cmd_name.size());

    if (!(in >> cmd)) cmd = -1;
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return cmd;
}
