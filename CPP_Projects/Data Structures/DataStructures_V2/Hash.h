#include <iostream>
#include <string>

using namespace std;

class Map
{
	struct Pair
	{
		int key;
		string name;
		Pair* next;
		Pair(int key, string name): key(key), name(name), next(0) {}
	};

	struct Proxy
	{
		Map* map;
		Pair* pair;
		int key;
		string name;

		Proxy(Map *m, Pair* p, int k, string name) : map(m), pair(p), key(k), name(name) {}

		void operator = (string new_name)
		{
			cout << "Inside Proxy = " << endl;
			if (pair)
				pair->name = new_name;	
			else
			{
				Pair* new_pair = new Pair(key, new_name);
				int hash = map->hashme(new_pair->key);
				
				if (map->table[hash])
				{
					Pair* curr = map->table[hash];
					for (; curr->next != 0; curr=curr->next)
					{	}
					curr->next = new_pair;
				}
				else
					map->table[hash] = new_pair;	
			}
		}

		operator string()
		{
			return name;
		}
		//friend ostream& operator<< (ostream &out, Proxy &proxy);
	};
		
	friend ostream& operator<< (ostream &out, Proxy &proxy); 

	Pair** table; // Pair[] *table;	

	int hashme(int key)
	{
		return key%100;
	}

public:
	Map()	
	{
		cout << "Map::Map start" << endl;
		table = new Pair* [100];

		for (int i=0; i<100; i++)
			table[i] = 0;

		cout << "Map::Map End" << endl;
	}

	Proxy  operator[](int key)
	{
		cout << "Inside Map operator[]" << endl;
		int hash = hashme(key);
		
		if (table[hash]	!= 0)
		{
			for (Pair* curr = table[hash]; curr != 0; curr=curr->next)
			{
				if (curr->key == key)
					return Proxy(this, curr, curr->key,  curr->name); 
			}
		}
		return Proxy(this, 0,key, string(""));
	}
		
						
};

ostream& operator<< (ostream &out, Map::Proxy &proxy)
{
	out << proxy.name << endl;
	return out;
}

	
