#ifndef REPLAY_h
#define REPLAY_H
#include <henigma_engine.h>
#include <CelicniAvtomat.h>
#include "moji_objekti.h"
#include <fstream>

class Zacetna;
class Replay : public Scena
{
public:
    Replay();
    void zacetek();
    void zanka();
    void konec();
    Scena *zacetna;

private:
    CelicniAvtomat m_zemljevid;

    Ploscice m_obala;
    Ploscice m_otoki;

    uint32_t m_ploscice_tekstura;
    uint32_t m_izhod_tek;
    Zvok m_muzika;

    Objekt_vegovec m_vegovec;
    Objekt_jasek m_jasek;
    Objekt m_izhod_gumb;

    std::vector<Objekt_crnc> m_crnci;
    std::vector<Objekt_smeti> m_smeti;
    std::vector<Objekt_greta> m_grete;
    std::vector<Objekt_jud> m_judi;
    std::vector<Objekt_cekin> m_cekini;

    Font m_pisava;
    std::ifstream i_dat;
    uint32_t m_naslednj_bralni_cas;
    bool m_ali_predvajam;
};

#endif