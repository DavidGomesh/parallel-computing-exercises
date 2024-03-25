#ifndef ANT_C_INCLUDED
#define ANT_C_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Ant.h"
#include "../Path.h"

#include "../../adt/graph/Vertex.h"
#include "../../adt/graph/Edge.h"

#include "../../utils/Printters.h"
#include "../../utils/Structure.h"

Ant* newAnt(char id[], Vertex* location) {
    Ant* ant = (Ant*) newStructure(sizeof(Ant));
    ant->location = location;
    strcpy(ant->id, id);
    
    return ant;
}

void printAnt(Ant* ant, void (*fl)(void*)) {
    if (ant == NULL) {
        printf("[NULL Ant]");
        return;
    }
    printf("Ant(ID=");
    printStr(ant->id);
    printf(",L=");
    printVertex(ant->location, fl);
    printf(")");
}

#endif // ANT_C_INCLUDED