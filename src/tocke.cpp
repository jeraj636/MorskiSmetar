#include "../include/tocke.h"

void Tocke::nastavi(const Objekt &o)
{
    m_tab[0] = mat::vec3(.0f, .0f, 1.0f);
    m_tab[1] = mat::vec3(o.velikost.x, .0f, 1.0f);
    m_tab[1] = mat::vec3(o.velikost.x, o.velikost.y, 1.0f);
    m_tab[1] = mat::vec3(.0f, o.velikost.y, 1.0f);

    mat::mat::mat3 rot = mat::mat::mat3(1);
    mat::mat::Vrtilna(o.rotacija, rot);
    mat::mat::mat3 poz = mat::mat::mat3(1);
    mat::mat::Premik(o.velikost, poz);
    for (int i = 0; i < 4; i++)
    {
        m_tab[i] *= rot;
        m_tab[i] *= poz;
    }
}

const mat::vec3 &Tocke::get_A()
{
    return m_tab[0];
}

const mat::vec3 &Tocke::get_B()
{
    return m_tab[1];
}

const mat::vec3 &Tocke::get_C()
{
    return m_tab[2];
}

const mat::vec3 &Tocke::get_D()
{
    return m_tab[3];
}