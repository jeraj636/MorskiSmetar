#ifndef ZACETNA_H
#define ZACETNA_H
#include <henigma_engine.h>
#include <CelicniAvtomat.h>
struct Igralec
{
    std::string ime = "";
    uint32_t tocke = 0;
};
class Zacetna : public Scena
{
public:
    Zacetna(Scena *level_scena, Scena *client_scena, Scena *server_scena, Scena *replay_scena);
    void zacetek() override;
    void zanka() override;
    void konec() override;
    void posodobi_igralca(int tocke);

private:
    Font m_font;

    CelicniAvtomat m_zemljevid;

    Ploscice m_obala;
    Ploscice m_otoki;

    uint32_t m_zemljevid_tek_id;

    Zvok m_glasba;

    Igralec m_vpisan_igralec;
    Igralec m_igralci[5];

    bool m_sem_vpisan;

    Objekt m_igraj_gumb;
    Objekt m_izhod_gumb;
    Objekt m_server_gumb;
    Objekt m_client_gumb;
    Objekt m_zamenjaj_ime_gumb;
    Objekt m_replay_gumb;

    Scena *m_level_scena;
    Scena *m_client_scena;
    Scena *m_server_scena;
    Scena *m_replay_scena;

    uint32_t m_zac_time;
};

#endif