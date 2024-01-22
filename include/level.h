#ifndef LEVEL_H
#define LEVEL_H
#include <henigma_engine.h>
#include <CelicniAvtomat.h>
class Level : public Scena
{
public:
    void zacetek() override;
    void zanka() override;
    void konec() override;

private:
    CelicniAvtomat m_zemljevid;

    Ploscice m_obala;
    Ploscice m_otoki;
    uint32_t m_ploscice_tekstura;

    Zvok m_muzika;
};

#endif