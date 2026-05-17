#include <iostream>

#include "car_builder.hpp"

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
    
    return 0;
}