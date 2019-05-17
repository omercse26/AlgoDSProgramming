#pragma once
#include <utility>
#include <functional>

template<std::size_t Idx>
struct Placeholder {};

template<typename T>
struct Bind
{
	constexpr decltype(auto) operator()(auto && ... param) const {
		return t(std::forward<decltype(param)>(param)...);
	}

	T t;
};

template<typename T> Bind(T)->Bind<T>;

template<std::size_t Idx, typename T>
constexpr decltype(auto) get_param(const Placeholder<Idx> &, T &&t)
{
	return std::get<Idx>(t);
}

template<typename Param, typename T>
constexpr decltype(auto) get_param(Param &&param, T &&)
{
	return std::forward<Param>(param);
}

template<typename Param, typename T>
constexpr decltype(auto) get_param(const Bind<Param> &b, T &&t)
{
	return std::apply(b, std::forward<T>(t));
}

constexpr auto bind = [](auto && callable, auto && ... param)
{
	return Bind{
		[callable = std::forward<decltype(callable)>(callable),
		...xs = std::forward<decltype(param)>(param)](auto && ... values) {
		auto passed_params = std::forward_as_tuple(std::forward<decltype(values)>(values)...);
		return std::invoke(callable, get_param(xs, passed_params)...);
	}
	};
};

int mainfunc()
{
	constexpr auto _0 = Placeholder<0>{};
	constexpr auto _1 = Placeholder<1>{};
	constexpr auto _2 = Placeholder<2>{};
	constexpr auto _3 = Placeholder<3>{};


	auto add = [](auto && ... param) {
		return (param + ...);
	};

	auto f = bind(add, 2, _1, bind(add, _0, 3));
	return f(9, 1);
}



