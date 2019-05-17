// Conditional Typing if_<true,char,int>::type a;
template <bool cond, typename T1, typename T2>
struct if_
{
    typedef T1 type;
};

template <typename T1, typename T2>
struct if_<false,T1,T2>
{
    typedef T2 type;
};

// Remove const
template <class T>
struct remove_const
{
	typedef T type;
};

template <class T>
struct remove_const <T const>
{
	typedef T type;
};
