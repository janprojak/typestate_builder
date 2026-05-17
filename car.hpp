// ============================================================================
// Copyright (c) 2026 Yevhenii Mamontov
//
// This code is licensed under the BSD 2-Clause License.
// ============================================================================

#pragma once

#include <ostream>
#include <string>
#include <cassert>
#include <format>

template<typename ... MandatoryValues>
class CarBuilder;

class Car
{
public:
    const std::string &GetBrandName() const { return brand_name_; }
    const std::string &GetModelName() const { return model_name_; }
    unsigned GetProductionYear() const { return production_year_; }
    unsigned GetMileage() const { return mileage_; }
    unsigned GetMaxFuelLevel() const { return max_fuel_level_; }
    unsigned GetCurrentFuelLevel() const { return current_fuel_level_; };

    void SetCurrentFuelLevel(unsigned new_current_fuel_level)
    {
        assert(new_current_fuel_level <= max_fuel_level_ &&
               "New current fuel level cannot exceed maximum fuel level.");
        current_fuel_level_ = new_current_fuel_level;
    }

private:
    Car() = default;
    
    template<typename ... MandatoryValues>
    friend class CarBuilder;

    std::string brand_name_;
    std::string model_name_;
    unsigned production_year_{0u};
    unsigned max_fuel_level_{0u};
    unsigned mileage_{0u};
    unsigned current_fuel_level_{0u};
};

inline std::ostream & operator << (std::ostream & out, const Car & car)
{
    return 
        out << std::format(
                "Car(name:{}, model:{}, year:{}, mileage:{}, max_fuel:{}, current_fuel:{})"
            ,   car.GetBrandName()
            ,   car.GetModelName()
            ,   car.GetProductionYear()
            ,   car.GetMileage()
            ,   car.GetMaxFuelLevel()
            ,   car.GetCurrentFuelLevel()
        );
}