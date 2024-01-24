#include "../include/level.h"
Level::Level()
{
    Objekt_vegovec::init();
    Objekt_ladja::init();
    m_ploscice_tekstura = Risalnik::nalozi_teksturo("ploscica.png");
}
void Level::zacetek()
{
    m_zemljevid.Naredi(192, 108, time(NULL));

    m_obala.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '.', m_ploscice_tekstura, 0xfbe790ff);
    m_otoki.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '0', m_ploscice_tekstura, 0x03ac13ff);

    /*
        m_muzika.nastavi("../../sredstva/zvok/theme.mp3");
        m_muzika.nastavi_loop(true);
        m_muzika.predvajaj();
    */
    m_vegovec.nastavi();
    m_ladja.nastavi(&m_zemljevid);
}

void Level::zanka()
{
    if (Risalnik::get_tipko_tipkovnice('R'))
    {
        konec();
        zacetek();
    }
    m_obala.narisi_me();
    m_otoki.narisi_me();
    m_vegovec.narisi_me();
    m_ladja.narisi_me();
}

void Level::konec()
{
    m_vegovec.animacije = std::vector<Animacija>{};
    m_zemljevid.Unici();
}