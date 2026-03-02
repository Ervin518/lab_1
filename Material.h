#ifndef MATERIAL_H
#define MATERIAL_H

struct Material {
    char nazwa[100];
    double gestosc;
    char flaga;
};

struct Material* createMaterial(const char* nazwa, double gestosc, char flaga);
void freeMaterial(struct Material* mat);

#endif
