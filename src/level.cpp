#include "../include/level.h"
Level::Level()
{
    Objekt_vegovec::init();
    Objekt_crnc::init();
    m_ploscice_tekstura = Risalnik::nalozi_teksturo("ploscica.png");
}
void Level::zacetek()
{
    m_zemljevid.Naredi(192, 108, rand() % 0xffffffff);

    m_obala.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '.', m_ploscice_tekstura, 0xfbe790ff);
    m_otoki.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '0', m_ploscice_tekstura, 0x03ac13ff);

    m_vegovec.nastavi(&m_zemljevid);
    /*
        m_muzika.nastavi("../../sredstva/zvok/theme.mp3");
        m_muzika.nastavi_loop(true);
        m_muzika.predvajaj();

    double next = Cas::get_time() + 0.05;
    while (next > Cas::get_time())
        ;
        */
    int n = rand() % 20;
    for (int i = 0; i < n; i++)
    {
        m_crnci.push_back(new Objekt_crnc);
        m_crnci.back()->nastavi(&m_zemljevid);
    }
}

void Level::zanka()
{

    m_obala.narisi_me();
    m_otoki.narisi_me();

    m_vegovec.update();
    m_vegovec.narisi_me();

    for (int i = 0; i < m_crnci.size(); i++)
    {
        m_crnci[i]->update();
        m_crnci[i]->narisi_me();
    }

    if (Risalnik::get_tipko_tipkovnice('R'))
    {
        konec();
        Risalnik::aktivna_scena = zacetna;
        zacetna->zacetek();
    }
}

void Level::konec()
{
    m_vegovec.animacije = std::vector<Animacija>{};
    m_zemljevid.Unici();

    for (int i = 0; i < m_crnci.size(); i++)
    {
        delete m_crnci.back();
        m_crnci.pop_back();
    }
}