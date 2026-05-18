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
concept Contains2 = ((Value == Values) || ...);

template<MandatoryValues... Values>
concept FullyAssembled2 = (
    Contains2<MandatoryValues::kBrandName, Values...> &&
    Contains2<MandatoryValues::kModelName, Values...> &&
    Contains2<MandatoryValues::kProductionYear, Values...> &&
    Contains2<MandatoryValues::kMileage, Values...> &&
    Contains2<MandatoryValues::kMaxFuelLevel, Values...>
);


template<MandatoryValues ... MandatoryFields>
class CarBuilder2
{
public:
    template<MandatoryValues ... OtherFields>
    friend class CarBuilder2;

    CarBuilder2() = default;

    auto WithBrandName(const std::string & brand_name)
    {
        car_.brand_name_ = brand_name;
        return CarBuilder2<MandatoryFields ..., MandatoryValues::kBrandName>(std::move(car_));
    }

    auto WithModelName(const std::string & model_name)
    {
        car_.model_name_ = model_name;
        return CarBuilder2<MandatoryFields ..., MandatoryValues::kModelName>(std::move(car_));
    }

    auto WithProductionYear(const unsigned production_year)
    {
        car_.production_year_ = production_year;
        return CarBuilder2<MandatoryFields ..., MandatoryValues::kProductionYear>(std::move(car_));
    }

    auto WithMileage(const unsigned mileage)
    {
        car_.mileage_ = mileage;
        return CarBuilder2<MandatoryFields ..., MandatoryValues::kMileage>(std::move(car_));
    }

    auto WithMaxFuelLevel(const unsigned max_fuel_level)
    {
        car_.max_fuel_level_ = max_fuel_level;
        return CarBuilder2<MandatoryFields ..., MandatoryValues::kMaxFuelLevel>(std::move(car_));
    }

    Car Build() requires FullyAssembled2<MandatoryFields ...>
    {
        return car_;
    }

private:
    explicit CarBuilder2(Car && proxy_car)
        : car_(std::move(proxy_car))
    {}

private:
    Car car_;
};