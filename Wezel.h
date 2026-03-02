#ifndef NODE_H
#define NODE_H

#include "Material.h"

struct Wezel {
    struct Material* material;
    struct Wezel* next;
    struct Wezel* prev;
};

struct Wezel* createWezel(struct Material* mat);
void freeWezel(struct Wezel* wezel);

#endif
