#include "heap.h"
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;


heap::heap(const map<Key, Weight>& initial) {
	weights = {};
	place = {};
	heaps = {};

	if (!(initial.empty())) {
		int last = 0;
		//map<string, int>::iterator *it;
		//for (map<Key, Weight>::const_iterator iter = initial.begin(); iter != initial.end(); ++iter)

		for (auto kvp : initial) {
			heaps.push_back(kvp.first);
			cout << kvp.first << endl;
			weights.insert(kvp);
			place.insert(pair<Key, Weight>(kvp.first, last));
			last++;
			heapConstruct();
		}
	}
}

void heap::heapConstruct() {
	int last_parent = parent(last());
	for (int i = 0; i < last_parent; i++) {
		//swapDown(i);
	}
}

bool heap::empty() const{
	return size(heaps) == 0;
}

void heap::enqueue(Key key, int weight) {
	map<Key, int>::iterator p;
	int i;
	int old_w;
	map<Key, int> second;
	if (weights.count(key)) {
		p = weights.find(key);
		old_w = p->second;
		i = place[key];
	}
	else {
		heaps.push_back(key);
		old_w = NULL;
		i = last();
		place[key] = i;
	}
	weights[key] = weight;
	if (old_w == NULL || old_w > weight) {
		swapUp(i);
	}
	else if (old_w < weight) {
		swapDown(i);
	}
}

heap::KeyWeight heap::dequeue() {
	map<Key, int>::iterator p;
	int l = last();
	Key key;
	Weight weigth;
	if (l < 0)
		throw string("Nothing left to dequeue");
	key = heaps[0];
	p = weights.find(key);
	weights.erase(p);
	place.erase(p);
	if (l > 0){
		heaps[0] = heaps.back();
		heaps.pop_back();
		place[heaps[0]] = 0;
	}
	else {
		heaps.erase(0);
		
	}


}

heap::Weight heap::weight(int i) const {
	if (i > last())
		return 0;
	string p = heaps[i];
	return weights.at(p);
}

//returns the parent of the given index
int heap::parent(int i) const {
	return (i - 1) >> 1;
}


//returns the left child of the given index
int heap::leftChild(int p) const {
	return (2 * p);
}

//returns the right child of the given index
int heap::rightChild(int p) const {
	return (2 * p) + 1;
}

int heap::last() const {
	cout << "returning last" << endl;
	return size(heaps) -1;
}

void heap::swapUp(int i) {
	if (i > 0) {
		int p = parent(i);
		if (weight(i)< weight(p)) {
			swap(heaps[i], heaps[p]);
			place[heaps[i]] = i;
			place[heaps[p]] = p;
			swapUp(p);
		}
	}
}

void heap::swapDown(int p) {
	int leChi = leftChild(p);
	int riChi = rightChild(p);
	int largest = p;
	int riChiW = weight(riChi);
	int leChiW = weight(leChi);
	
	if (riChiW && leChiW == 0) {
		return;
	}

	riChiW = weight(riChi);
	if (riChiW != 0 && riChiW < leChiW) {
		leChi = riChi;
		leChiW = riChiW;
		if (weight(p) > riChiW) {
			swap(heaps[p], heaps[riChiW]);
			place[heaps[riChi]] = riChi;
			place[heaps[p]] = p;
			swapDown(leChi);
		}
	}
	
}








