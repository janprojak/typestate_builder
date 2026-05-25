#include <iostream>

#include "car_builder.hpp"

int main()
{
    Car car = 
        CarBuilder()
            .WithBrandName("Mercedes")
            .WithModelName("GLE")
            .WithProductionYear(2026)
            .WithMaxFuelLevel(50)
            .WithMileage(0)
            .Build();

    std::cout << car << std::endl;

    return 0;
}