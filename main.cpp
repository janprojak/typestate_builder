#include <iostream>

#include "car_builder.hpp"
#include "car_builder_2.hpp"

int main()
{
    Car car = 
        CarBuilder()
            .WithBrandName("Audi")
            .WithModelName("A4")
            .WithProductionYear(2026)
            .WithMaxFuelLevel(45)
            .WithMileage(0)
            .Build();

    std::cout << car << std::endl;

    Car car2 = 
        CarBuilder2()
            .WithBrandName("Mercedes")
            .WithModelName("GLE")
            .WithProductionYear(2026)
            .WithMaxFuelLevel(50)
            .WithMileage(0)
            .Build();

    std::cout << car2 << std::endl;
    
    return 0;
}