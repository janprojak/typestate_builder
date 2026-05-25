// ============================================================================
// Copyright (c) 2026 Yevhenii Mamontov
//
// This code is licensed under the BSD 2-Clause License.
// ============================================================================

#pragma once

#include "car.hpp"
#include "mandatory_values.hpp"

#include <string>

template<MandatoryValues Value, MandatoryValues... Values>
concept Contains = ((Value == Values) || ...);

template<MandatoryValues... Values>
concept FullyAssembled = (
    Contains<MandatoryValues::kBrandName, Values...> &&
    Contains<MandatoryValues::kModelName, Values...> &&
    Contains<MandatoryValues::kProductionYear, Values...> &&
    Contains<MandatoryValues::kMileage, Values...> &&
    Contains<MandatoryValues::kMaxFuelLevel, Values...>
);


template<MandatoryValues ... MandatoryFields>
class CarBuilder
{
public:
    template<MandatoryValues ... OtherFields>
    friend class CarBuilder;

    CarBuilder() = default;

    auto WithBrandName(const std::string & brand_name)
    {
        car_.brand_name_ = brand_name;
        return CarBuilder<MandatoryFields ..., MandatoryValues::kBrandName>(std::move(car_));
    }

    auto WithModelName(const std::string & model_name)
    {
        car_.model_name_ = model_name;
        return CarBuilder<MandatoryFields ..., MandatoryValues::kModelName>(std::move(car_));
    }

    auto WithProductionYear(const unsigned production_year)
    {
        car_.production_year_ = production_year;
        return CarBuilder<MandatoryFields ..., MandatoryValues::kProductionYear>(std::move(car_));
    }

    auto WithMileage(const unsigned mileage)
    {
        car_.mileage_ = mileage;
        return CarBuilder<MandatoryFields ..., MandatoryValues::kMileage>(std::move(car_));
    }

    auto WithMaxFuelLevel(const unsigned max_fuel_level)
    {
        car_.max_fuel_level_ = max_fuel_level;
        return CarBuilder<MandatoryFields ..., MandatoryValues::kMaxFuelLevel>(std::move(car_));
    }

    Car Build() requires FullyAssembled<MandatoryFields ...>
    {
        return car_;
    }

private:
    explicit CarBuilder(Car && proxy_car)
        : car_(std::move(proxy_car))
    {}

private:
    Car car_;
};