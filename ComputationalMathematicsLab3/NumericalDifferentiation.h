#pragma once
#include "Menu.h"
#include "InputData.h"

namespace KHAS {

    class NumericalDifferentiation
    {
    private:
        struct Data_ { double x, dfx_excatly, dfx_approximately; };
    public:
        template <typename TData>
            requires std::is_convertible_v<TData, InputData>
        NumericalDifferentiation(TData&& data, size_t width_screen);
        void loop() const noexcept;
    private:
        void init() noexcept;
        void fillValueTable(size_t size) noexcept;
        void fillExcatlyAndApproximatlyValueTable() noexcept;
        void showHeader(std::ostream& out = std::cout) const noexcept;
        void showUnknownCommand(std::ostream& out = std::cout) const noexcept;
        void printValueTable(std::ostream& out = std::cout) const noexcept;
        void printExactAndApproximateValues(std::ostream& out = std::cout) const noexcept;
        double mathFunc(double x) const noexcept;
        double mathFuncExcatly(double x) const noexcept;
        double mathNumericalDifferentiation(double fx, double fx2) const noexcept;
        size_t showReadCommand(std::istream& in = std::cin) const noexcept;
    private:
        size_t width_screen_;
        InputData data_;
        Menu menu_;
        std::vector<Data_> value_table_;
        std::vector<Data_> excatly_and_approximatly_value_table_;
    };



    template <typename TData>
        requires std::is_convertible_v<TData, InputData>
    NumericalDifferentiation::NumericalDifferentiation(TData&& data, size_t width_screen)
        : width_screen_{ width_screen }
        , data_ { std::forward<TData>(data) }
        , menu_{ width_screen } 
    {
        init();
    }
}