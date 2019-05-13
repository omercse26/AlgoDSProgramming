#pragma once
// ... on the left packs the parameters.
// ... on the right de-packs the parameters.

////////////////////////////////////////////////////////////////////////////
// IntVector
template <int ...Is>
struct IntVector {
	using Type = IntVector<Is...>;
};
////////////////////////////////////////////////////////////////////////////
// Front
template <typename T_Vector>
struct Front;

template <int One, int ...Is>
struct Front <IntVector<One, Is...>> {
	enum { value = One };
};

////////////////////////////////////////////////////////////////////////////
// At
template <typename T_Vector, int Index>
struct At;

template<int First, int ...Is, int I>
struct At <IntVector<First, Is...>, I> : At<IntVector<Is...>, I - 1> {

};

template<int First, int ...Is>
struct At <IntVector<First, Is...>, 0> {
	enum { value = First };
};

////////////////////////////////////////////////////////////////////////////
// PushFront
template <typename T_Vector, int New>
struct PushFront;

template <int ...Is, int New>
struct PushFront <IntVector<Is...>, New> : IntVector<New, Is...> {

};

////////////////////////////////////////////////////////////////////////////
// PushBack
template <typename T_Vector, int New>
struct PushBack;

template <int ...Is, int New>
struct PushBack <IntVector<Is...>, New> : IntVector<Is..., New> {

};

////////////////////////////////////////////////////////////////////////////
// Find
template <typename T_Vector, int Elem, int Index=0>
struct Find;

// Not yet found specialization.
template <int First, int ...Is, int Elem, int Index>
struct Find <IntVector<First, Is...>, Elem, Index> : Find <IntVector<Is...>, Elem, Index + 1>
{};

// Found specialization
template <int First, int ...Is, int Index>
struct Find <IntVector<First, Is...>, First, Index> {
	enum {value = Index};
};

// Not found specialization.
template <int Elem, int Index>
struct Find <IntVector<>, Elem, Index> {
	enum { value = -1 };
};

////////////////////////////////////////////////////////////////////////////
// Contains
template <typename T_Vector, int Elem>
struct Contains {
	enum { value = (Find<T_Vector, Elem>::value != -1) };
};

////////////////////////////////////////////////////////////////////////////
// Iota

template <typename NumElems, T_Vector = IntVector<> >
struct Iota : 
	Iota <NumElems - 1, PushFront<T_Vector, NumElems-1>> {};
