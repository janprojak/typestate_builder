#include <iostream>
#include <ostream>
#include <string>
#include <type_traits>
#include <format>
#include <utility>

struct User
{
    std::string name_;
    int age_;
};

std::ostream & operator << (std::ostream & out, const User & user)
{
    return 
        out << std::format("User(name: {}, age: {})", user.name_, user.age_);
}

struct Missing{};
struct Present{};

template<typename TNameState, typename TAgeState>
concept FullyAssembled = 
    std::is_same_v<TNameState, Present> && std::is_same_v<TAgeState, Present>;

template<typename TNameState = Missing, typename TAgeState = Missing>
class UserBuilder
{
public:

    UserBuilder() = default;
    UserBuilder(const std::string & name, int age)
        :   name_(name), age_(age)
    {}

    auto SetName(const std::string & name)
    {
        return UserBuilder<Present, TAgeState>{name, age_};
    }

    auto SetAge(int age)
    {
        return UserBuilder<TNameState, Present>{name_, age};
    }

    User Build() requires FullyAssembled<TNameState, TAgeState>
    {
        return User(name_, age_);
    }

private:
    std::string name_;
    int age_;
};

auto Foo(UserBuilder<> && builder)
{
    return builder.SetName("User_Foo");
}

int main()
{
    const User user_1 = UserBuilder().SetName("User_1").SetAge(22).Build();
    std::cout << user_1 << std::endl;

    auto ub_2 = UserBuilder().SetAge(44);
    const User user_2 = ub_2.SetName("User_2").Build();
    std::cout << user_2 << std::endl;

    auto ub_3 = UserBuilder();
    auto ub_3_copy = Foo(std::move(ub_3));
    const User user_3 = ub_3_copy.SetAge(66).Build();
    std::cout << user_3 << std::endl;

    return 0;
}