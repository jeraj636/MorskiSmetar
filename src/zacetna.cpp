#include "../include/zacetna.h"
Zacetna::Zacetna(Scena *level_scena)
{
    m_level_scena = level_scena;
}
void Zacetna::zacetek()
{
    m_font = Risalnik::nalozi_font("FixedDays.ttf", 40);

    m_zemljevid_tek_id = Risalnik::nalozi_teksturo("ploscica.png");
    m_zemljevid.Naredi(192, 108, time(NULL));

    m_obala.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '.', m_zemljevid_tek_id, 0xfbe790ff);
    m_otoki.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '0', m_zemljevid_tek_id, 0x03ac13ff);

    m_glasba.nastavi("../../sredstva/zvok/theme.mp3");
    m_glasba.nastavi_loop(true);
    m_glasba.predvajaj();

    m_igraj_gumb.nastavi(mat::vec2(Risalnik::get_velikost_okna().x / 2, 600), mat::vec2(100, 100), 0, 0xffffffff, 0);
    m_igraj_gumb.id_teksture = Risalnik::nalozi_teksturo("ui/igraj_gumb.png");
    m_izhod_gumb.nastavi(mat::vec2(Risalnik::get_velikost_okna().x / 2, 800), mat::vec2(100, 100), 0, 0xffffffff, 0);
    m_izhod_gumb.id_teksture = Risalnik::nalozi_teksturo("ui/izhod_gumb.png");
    m_igraj_gumb.aktiven = true;
    m_izhod_gumb.aktiven = true;
}

void Zacetna::zanka()
{
    m_obala.narisi_me();
    m_otoki.narisi_me();

    m_igraj_gumb.narisi_me();
    m_izhod_gumb.narisi_me();
    if (m_igraj_gumb.je_miska_gor())
    {
        m_igraj_gumb.barva_objekta.set_a(0x55);
        if (Risalnik::get_miskin_gumb() == Gumb::levi)
        {
            m_level_scena->zacetek();
            Risalnik::aktivna_scena = m_level_scena;
            konec();
        }
    }
    else
    {
        m_igraj_gumb.barva_objekta.set_a(0xff);
    }
    if (m_izhod_gumb.je_miska_gor())
    {
        m_izhod_gumb.barva_objekta.set_a(0x55);
        if (Risalnik::get_miskin_gumb() == Gumb::levi)
        {
            Risalnik::konec();
        }
    }
    else
    {
        m_izhod_gumb.barva_objekta.set_a(0xff);
    }
    Risalnik::narisi_niz(m_font, Barva(0xffffffff), Barva(0), 1080 - 400, 400, "Morski smetar");
}

void Zacetna::konec()
{
    m_glasba.stop();

    m_obala.unici();
    m_otoki.unici();

    m_igraj_gumb.unici();
    m_izhod_gumb.unici();
}