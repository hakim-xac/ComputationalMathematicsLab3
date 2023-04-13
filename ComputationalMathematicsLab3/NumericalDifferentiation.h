#pragma once
#include "Menu.h"
#include "InputData.h"

namespace KHAS {

    class NumericalDifferentiation
    {
    public:
        template <typename Data>
            requires std::is_convertible_v<Data, InputData>
        NumericalDifferentiation(Data&& data);
        void loop() const noexcept;
    private:
        void init() noexcept;
        void showHeader(std::ostream& out = std::cout) const noexcept;
        void showUnknownCommand(std::ostream& out = std::cout) const noexcept;
        void printValueTable(std::ostream& out = std::cout) const noexcept;
        double mathFunc(double x) const noexcept;
        size_t showReadCommand(std::istream& in = std::cin) const noexcept;
    private:
        InputData data_;
        Menu menu_;
        std::vector<std::pair<double, double>> value_table_;
    };



    template <typename Data>
        requires std::is_convertible_v<Data, InputData>
    NumericalDifferentiation::NumericalDifferentiation(Data&& data)
        : data_{ std::forward<Data>(data) }
        , menu_{ data_.width_screen } {

        init();
    }
}