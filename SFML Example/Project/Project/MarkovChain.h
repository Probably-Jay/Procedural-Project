#pragma once
#include "MarkovNode.h"


using std::make_shared;

#define Element(E) {E, make_shared<MarkovNode<T>>(E) }

template <class T>
class MarkovChain
{
public:
	MarkovChain<T>();

	T GetNext();

	inline T PeekNext() const { return currentNode->GetData(); };
	inline void ProgressChain() { currentNode = currentNode->ProgressChain(); };

	inline void SetAxiom(T axiom) { currentNode = nodes.at(axiom); };

	inline void AddState(T data) { nodes.insert({ data, make_shared<MarkovNode<T>>(data) }); };
	inline void AddLink(T from, T to, float probability) { nodes.at(from)->AddLink(nodes.at(to), probability); };
//	inline void NormaliseProbability(T node,) { nodes.at(node)-> };
	inline void MarkTerminus(T terminus) { nodes.at(terminus)->MarkTerminus(); };

	
	inline bool HasReachedTerminus() const { return currentNode == nullptr; };


private:
	std::shared_ptr<MarkovNode<T>> currentNode;
	std::map<const T, std::shared_ptr<MarkovNode<T>>> nodes;
	
};

template<class T>
inline MarkovChain<T>::MarkovChain()
	: currentNode(nullptr)
{
	srand(time(NULL));
}

template<class T>
inline T MarkovChain<T>::GetNext()
{
	T currentVal = PeekNext();
	ProgressChain();
	return currentVal;
}
