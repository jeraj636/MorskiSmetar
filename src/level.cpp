#include "../include/level.h"

void Level::zacetek()
{
    m_zemljevid.Naredi(192, 108, time(NULL));

    m_ploscice_tekstura = Risalnik::nalozi_teksturo("ploscica.png");

    m_obala.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '.', m_ploscice_tekstura, 0xfbe790ff);
    m_otoki.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '0', m_ploscice_tekstura, 0x03ac13ff);

    m_muzika.nastavi("../../sredstva/zvok/theme.mp3");
    m_muzika.nastavi_loop(true);
    m_muzika.predvajaj();
}

void Level::zanka()
{
    m_obala.narisi_me();
    m_otoki.narisi_me();
}

void Level::konec()
{
}