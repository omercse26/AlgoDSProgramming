#pragma once
template<unsigned...> struct index_tuple {};

template<unsigned I, typename IndexTuple, typename... Types>
struct make_indices_impl;

template<unsigned I, unsigned... Indices, typename T, typename... Types>
struct make_indices_impl<I, index_tuple<Indices...>, T, Types...>
{
	typedef typename
		make_indices_impl<I + 1,
		index_tuple<Indices..., I>,
		Types...>::type type;
};

template<unsigned I, unsigned... Indices>
struct make_indices_impl<I, index_tuple<Indices...> >
{
	typedef index_tuple<Indices...> type;
};

template<typename... Types>
struct make_indices
	: make_indices_impl<0, index_tuple<>, Types...>
{};

template <unsigned... Indices, class... Args, class Ret>
Ret forward_impl(index_tuple<Indices...>,
	std::tuple<Args...> tuple,
	Ret(*fptr) (Args...))
{
	return fptr(std::get<Indices>(tuple)...);
}

template<class... Args, class Ret>
Ret forward(std::tuple<Args...> tuple, Ret(*fptr) (Args...))
{
	typedef typename make_indices<Args...>::type Indices;
	return forward_impl(Indices(), tuple, fptr);
}

int myfunc(int i, bool, double)
{
	return 5 + i;
}