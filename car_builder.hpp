// ============================================================================
// Copyright (c) 2026 Yevhenii Mamontov
//
// This code is licensed under the BSD 2-Clause License.
// ============================================================================

#pragma once

#include "car.hpp"

#include <string>
#include <type_traits>

struct BrandNameTag{};
struct ModelNameTag{};
struct ProductionYearTag{};
struct MileageTag{};
struct MaxFuelLevelTag{};

template<typename Field, typename ... MandatoryValues>
concept Contains = (std::is_same_v<Field, MandatoryValues> || ...);

template<typename ... SetFields>
concept FullyAssembled = (
    Contains<BrandNameTag, SetFields...> &&
    Contains<ModelNameTag, SetFields...> &&
    Contains<ProductionYearTag, SetFields...> &&
    Contains<MileageTag, SetFields...> &&
    Contains<MaxFuelLevelTag, SetFields...>
);
    
template<typename ... MandatoryFields>
class CarBuilder
{
public:
    template<typename ... OtherFields>
    friend class CarBuilder;

    CarBuilder() = default;

    auto WithBrandName(const std::string & brand_name)
    {
        hot_potato_car_.brand_name_ = brand_name;
        return CarBuilder<MandatoryFields ..., BrandNameTag>(std::move(hot_potato_car_));
    }

    auto WithModelName(const std::string & model_name)
    {
        hot_potato_car_.model_name_ = model_name;
        return CarBuilder<MandatoryFields ..., ModelNameTag>(std::move(hot_potato_car_));
    }

    auto WithProductionYear(const unsigned production_year)
    {
        hot_potato_car_.production_year_ = production_year;
        return CarBuilder<MandatoryFields ..., ProductionYearTag>(std::move(hot_potato_car_));
    }

    auto WithMileage(const unsigned mileage)
    {
        hot_potato_car_.mileage_ = mileage;
        return CarBuilder<MandatoryFields ..., MileageTag>(std::move(hot_potato_car_));
    }

    auto WithMaxFuelLevel(const unsigned max_fuel_level)
    {
        hot_potato_car_.max_fuel_level_ = max_fuel_level;
        return CarBuilder<MandatoryFields ..., MaxFuelLevelTag>(std::move(hot_potato_car_));
    }

    Car Build() requires FullyAssembled<MandatoryFields ...>
    {
        return hot_potato_car_;
    }

private:
    explicit CarBuilder(Car && proxy_car)
        : hot_potato_car_(std::move(proxy_car))
    {}

    Car hot_potato_car_;
};