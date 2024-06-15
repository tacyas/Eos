#ifndef EOS_LIST_H
#define EOS_LIST_H

typedef struct eosList eosList;
struct eosList {
	void*    node;
	eosList* prev;
	eosList* next;
} eosList;


#endif /* EOS_LIST_H */
