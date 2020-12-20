#pragma once
#include <map>
#include <memory>

template <class T>
class MarkovNode
{
public:
	MarkovNode<T>(T data);

	std::shared_ptr<MarkovNode<T>> ProgressChain() const;

	inline T GetData() const { return payload; };

	void AddLink(std::shared_ptr<MarkovNode<T>> node, int probabiltyPercent);

	inline void ClearLinks() { links.clear(); };

	inline bool IsValidDistribution() const { return accumulativeProbablity == 100; };

	void MarkTerminus();

	//void NormaliseProbablility();

private:
	T payload;

	std::map<const int, std::shared_ptr<MarkovNode<T>>> links;

	int accumulativeProbablity;

};

template<class T>
inline MarkovNode<T>::MarkovNode(T data)
	: payload(data)
	, accumulativeProbablity(0)
{

}


template<class T>
inline std::shared_ptr<MarkovNode<T>> MarkovNode<T>::ProgressChain() const
{
	// accumulative probabllity should be 100, or this class is malformed and calling this has unpredictable results

	int val = rand() % accumulativeProbablity +1;

	for (auto ittr = links.begin(); ittr != links.end(); ittr++) 
	{
		if (ittr->first >= val) {
			return ittr->second;
		}
	}

	return std::shared_ptr<MarkovNode<T>>(nullptr);
}

template<class T>
inline void MarkovNode<T>::AddLink(std::shared_ptr<MarkovNode<T>> node, int probabiltyPecent)
{
	if (probabiltyPecent <= 0) { //invalid, return
		return;
	}
	accumulativeProbablity += probabiltyPecent;

	links.insert({ accumulativeProbablity,node });

}

template<class T>
inline void MarkovNode<T>::MarkTerminus()
{
	ClearLinks();
	accumulativeProbablity = 100;
}

//template<class T>
//inline void MarkovNode<T>::NormaliseProbablility()
//{
//
//}
