#include "../include/replay.h"
Replay::Replay()
{
    m_pisava = Risalnik::nalozi_font("FixedDays.ttf", 40);
    m_ploscice_tekstura = Risalnik::nalozi_teksturo("ploscica.png");

    m_muzika = Risalnik::nalozi_zvok("zvok/theme.mp3");
}
void Replay::zacetek()
{
    Risalnik::aktivna_scena = this;

    m_izhod_tek = Risalnik::nalozi_teksturo("ui/izhod_gumb.png");
    uint32_t seme;
    i_dat.open("../../sredstva/replay.ms", std::ios::binary);
    i_dat.read((char *)&seme, sizeof(uint32_t));

    m_zemljevid.Naredi(Risalnik::get_velikost_okna().x / 8, Risalnik::get_velikost_okna().y / 8, seme);

    m_izhod_gumb.nastavi(mat::vec2(Risalnik::get_velikost_okna().x / 2, 600), mat::vec2(100, 100), 180, 0xffffffff, 0);
    m_izhod_gumb.id_teksture = m_izhod_tek;

    m_obala.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '.', m_ploscice_tekstura, 0xfbe790ff);
    m_otoki.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '0', m_ploscice_tekstura, 0x03ac13ff);

    m_vegovec.nastavi(&m_zemljevid);
    m_jasek.nastavi();
    m_muzika.zacetek();
    m_muzika.nastavi_loop(true);
    m_muzika.predvajaj();
    m_naslednj_bralni_cas = Cas::get_time() + 0.05;
}

void Replay::zanka()
{
    m_obala.narisi_me();
    m_otoki.narisi_me();

    if (m_ali_predvajam && m_naslednj_bralni_cas <= Cas::get_time())
    {
        m_naslednj_bralni_cas = Cas::get_time() + 0.05;
        if (!i_dat.read((char *)&m_vegovec.pozicija, sizeof(mat::vec2)))
            m_ali_predvajam = false;
    }
    m_vegovec.update(m_jasek);
    m_vegovec.narisi_me();
    m_jasek.narisi_me();
    if (!m_ali_predvajam)
    {
        m_izhod_gumb.narisi_me();
        if (m_izhod_gumb.je_miska_gor())
        {
            m_izhod_gumb.barva_objekta.set_a(0xaa);
            if (Risalnik::get_miskin_gumb() == Gumb::levi)
            {
                konec();
                zacetna->zacetek();
            }
        }
        else
        {
            m_izhod_gumb.barva_objekta.set_a(0xff);
        }
    }
}

void Replay::konec()
{
    i_dat.close();
    m_vegovec.animacije = std::vector<Animacija>{};
    m_izhod_gumb.unici();
    m_zemljevid.Unici();
    m_muzika.stop();
    m_pisava.unici();
}