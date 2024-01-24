#ifndef TOCKE_H
#define TOCKE_H
#include <henigma_engine.h>
class Tocke
{
public:
    void nastavi(const Objekt &o);
    const mat::vec3 &get_A();
    const mat::vec3 &get_B();
    const mat::vec3 &get_C();
    const mat::vec3 &get_D();

private:
    mat::vec3 m_tab[4];
};

#endif