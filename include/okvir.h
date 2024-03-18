#ifndef OKVIR_H
#define OKVIR_H

#include <vector>
#include <henigma_engine.h>
struct Okvir
{
    std::vector<mat::vec2> m_crnci;
    std::vector<mat::vec2> m_smeti;
    std::vector<mat::vec2> m_grete;
    std::vector<mat::vec2> m_judi;
    std::vector<mat::vec2> m_cekini;
    mat::vec2 m_vegovec_poz;
};

#endif