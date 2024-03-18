#ifndef LEVEL_H
#define LEVEL_H

#include <henigma_engine.h>
#include <CelicniAvtomat.h>
#include <fstream>
#include "../include/moji_objekti.h"
#include "okvir.h"
class Zacetna;

class Level : public Scena
{
public:
    Level();
    void zacetek() override;
    void zanka() override;
    void konec() override;
    Zacetna *zacetna;

protected:
    CelicniAvtomat m_zemljevid;

    Ploscice m_obala;
    Ploscice m_otoki;

    uint32_t m_ploscice_tekstura;
    uint32_t m_tocke_tek;
    uint32_t m_ura_tek;
    uint32_t m_izhod_gumb_tek;
    Zvok m_muzika;

    Objekt_vegovec m_vegovec;
    Objekt_jasek m_jasek;
    Objekt m_izhod_gumb;
    Objekt m_tocke_obj;
    Objekt m_ura;

    std::vector<Objekt_crnc *> m_crnci;
    std::vector<Objekt_smeti *> m_smeti;
    std::vector<Objekt_greta *> m_grete;
    std::vector<Objekt_jud *> m_judi;
    std::vector<Objekt_cekin *> m_cekini;

    Font m_pisava;

    int m_tocke;
    double m_next_tocke_odboj;

    uint32_t m_st_judov_const;
    uint32_t m_st_judov;
    bool m_je_se_kaksen_crn;

protected:
    bool konec_igre();

private:
    uint32_t m_naslednj_okvir_cas;
    std::ofstream o_dat;
};

#endif