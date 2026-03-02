#ifndef MATERIAL_H
#define MATERIAL_H

struct Material {
    char nazwa[100];
    double gestosc;
    char flaga;
};

struct Material* create_material(const char* nazwa, double gestosc, char flaga);
void free_material(struct Material* mat);

#endif
