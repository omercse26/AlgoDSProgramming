#pragma once
#include <utility>
#include <map>
#include <tuple>

template <int I, typename ReturnType, typename... Args>
decltype(auto) memoize (ReturnType(*func)(Args...))
{
	auto memoized_function = [=](Args... args) {
		static std::map<tuple<Args...>, int> cache;
		std::tuple<Args...> arglist(args...);
		if (cache.find(arglist) == cache.end()) {
			cache.insert(std::make_pair(arglist, func(args...)));
		}
		return cache[arglist];
	};
	return memoized_function;
}
