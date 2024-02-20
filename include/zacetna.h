#ifndef ZACETNA_H
#define ZACETNA_H
#include <henigma_engine.h>
#include <CelicniAvtomat.h>
class Zacetna : public Scena
{
public:
    Zacetna(Scena *level_scena, Scena *client_scena, Scena *server_scena);
    void zacetek() override;
    void zanka() override;
    void konec() override;

private:
    Font m_font;

    CelicniAvtomat m_zemljevid;

    Ploscice m_obala;
    Ploscice m_otoki;

    uint32_t m_zemljevid_tek_id;

    Zvok m_glasba;

    Objekt m_igraj_gumb;
    Objekt m_izhod_gumb;
    Objekt m_server_gumb;
    Objekt m_client_gumb;

    Scena *m_level_scena;
    Scena *m_client_scena;
    Scena *m_server_scena;

    uint32_t m_zac_time;
};

#endif