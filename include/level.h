#ifndef LEVEL_H
#define LEVEL_H

#include <henigma_engine.h>
#include <CelicniAvtomat.h>

#include "../include/moji_objekti.h"

class Level : public Scena
{
public:
    Level();
    void zacetek() override;
    void zanka() override;
    void konec() override;
    Scena *zacetna;

private:
    CelicniAvtomat m_zemljevid;

    Ploscice m_obala;
    Ploscice m_otoki;
    uint32_t m_ploscice_tekstura;

    Zvok m_muzika;

    Objekt_vegovec m_vegovec;

    std::vector<Objekt_crnc *> m_crnci;
};

#endif