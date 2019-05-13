#pragma once
#include <iostream>
#include <map>
#include <functional>

using namespace std;

struct Person
{
	std::string firstName;
	std::string lastName;
	int age;
	std::string fullName() const
	{
		return firstName + " " + lastName;
	}

	void setAge(int a)
	{
		age = a;
	}
};

template<typename Key, typename Model>
using P2Mem = Key Model::*;

template<typename Key, typename Model>
Key deduceKeyType(P2Mem<Key, Model> pMember);

template<typename Key, typename Model>
Model deduceModelType(P2Mem<Key, Model> pMember);

template<typename Key, typename Model>
using P2MemFn = Key Model::*();

template<typename Key, typename Model>
Model deduceModelType(P2MemFn<Key, Model> pMember);

template<auto pMember>
struct Index
{
	using Key = decltype (deduceKeyType(pMember));
	using Model = decltype (deduceModelType(pMember));
	std::map<Key, int> data;
	Key extractKey(Model const& model)
	{
		return std::invoke(pMember, model);
	}

	void insert(Key k, int id)
	{
		data.insert(std::pair(k, id));
	}
};

using AgeIndex = Index<&Person::age>;

template<typename Model, typename... Indices>
struct Table
{
	static int id;
	std::map<int, Model> data;
	std::tuple<Indices...> indices;

	int insert(Model const& model)
	{
		++id;
		data.insert(std::pair(id, model));
		for_each(indices, [&](auto& index)
		{
			index.insert(index.extractKey(model), id);
		}
		);
	}
};

template<typename Model, typename... Indices>
int Table<Model, Indices...>::id = 0;

int mainfunc()
{
	Table<Person, AgeIndex> t;
	return 0;
}
