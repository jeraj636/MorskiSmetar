#include "../include/zacetna.h"
Zacetna::Zacetna(Scena *level_scena, Scena *client_scena, Scena *server_scena)
{
    m_level_scena = level_scena;
    m_server_scena = server_scena;
    m_client_scena = client_scena;

    m_sem_vpisan = false;
    m_glasba = Risalnik::nalozi_zvok("zvok/theme.mp3");
}
void Zacetna::zacetek()
{
    m_font = Risalnik::nalozi_font("FixedDays.ttf", 40);

    m_zemljevid_tek_id = Risalnik::nalozi_teksturo("ploscica.png");
    m_zemljevid.Naredi(240, 135, time(NULL));
    m_obala.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '.', m_zemljevid_tek_id, 0xfbe790ff);
    m_otoki.nastavi(m_zemljevid.GetTab(), m_zemljevid.GetX(), m_zemljevid.GetY(), '0', m_zemljevid_tek_id, 0x03ac13ff);

    m_glasba.zacetek();
    m_glasba.nastavi_loop(true);
    m_glasba.predvajaj();

    m_igraj_gumb.nastavi(mat::vec2(Risalnik::get_velikost_okna().x / 2 - 110, 600), mat::vec2(100, 100), 0, 0xffffffff, 0);
    m_igraj_gumb.id_teksture = Risalnik::nalozi_teksturo("ui/igraj_gumb.png");

    m_server_gumb.nastavi(mat::vec2(Risalnik::get_velikost_okna().x / 2, 600), mat::vec2(100, 100), 180, 0xffffffff, 0);
    m_server_gumb.id_teksture = Risalnik::nalozi_teksturo("ui/omrezje.png");

    m_client_gumb.nastavi(mat::vec2(Risalnik::get_velikost_okna().x / 2 + 110, 600), mat::vec2(100, 100), 180, 0xffffffff, 0);
    m_client_gumb.id_teksture = Risalnik::nalozi_teksturo("ui/omrezje.png");

    m_izhod_gumb.nastavi(mat::vec2(Risalnik::get_velikost_okna().x / 2, 800), mat::vec2(100, 100), 0, 0xffffffff, 0);
    m_izhod_gumb.id_teksture = Risalnik::nalozi_teksturo("ui/izhod_gumb.png");

    m_igraj_gumb.aktiven = true;
    m_izhod_gumb.aktiven = true;
    m_server_gumb.aktiven = true;
    m_client_gumb.aktiven = true;

    m_zac_time = Cas::get_time() + 1;
    Risalnik::aktivna_scena = this;
    Risalnik::trenutni_buffer_za_vpisovanje = &m_vpisan_igralec;
}

void Zacetna::zanka()
{
    if (m_sem_vpisan)
    {

        m_igraj_gumb.pozicija.x = Risalnik::get_velikost_okna().x / 2 - 110;
        m_izhod_gumb.pozicija.x = Risalnik::get_velikost_okna().x / 2;
        m_server_gumb.pozicija.x = Risalnik::get_velikost_okna().x / 2;
        m_client_gumb.pozicija.x = Risalnik::get_velikost_okna().x / 2 + 110;

        m_obala.narisi_me();
        m_otoki.narisi_me();

        m_igraj_gumb.narisi_me();
        m_izhod_gumb.narisi_me();
        m_server_gumb.narisi_me();
        m_client_gumb.narisi_me();
        if (m_zac_time <= Cas::get_time())
        {

            if (m_igraj_gumb.je_miska_gor())
            {
                m_igraj_gumb.barva_objekta.set_a(0x55);
                if (Risalnik::get_miskin_gumb() == Gumb::levi)
                {
                    m_level_scena->zacetek();
                    // Risalnik::aktivna_scena = m_level_scena;
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
            if (m_server_gumb.je_miska_gor())
            {
                m_server_gumb.barva_objekta.set_a(0x55);
                if (Risalnik::get_miskin_gumb() == Gumb::levi)
                {
                    m_server_scena->zacetek();
                    // Risalnik::aktivna_scena = m_server_scena;
                    konec();
                }
            }
            else
            {
                m_server_gumb.barva_objekta.set_a(0xff);
            }
            if (m_client_gumb.je_miska_gor())
            {
                m_client_gumb.barva_objekta.set_a(0x55);
                if (Risalnik::get_miskin_gumb() == Gumb::levi)
                {
                    m_client_scena->zacetek();
                    // Risalnik::aktivna_scena = m_client_scena;
                    konec();
                }
            }
            else
            {
                m_client_gumb.barva_objekta.set_a(0xff);
            }
        }
        Risalnik::narisi_niz(m_font, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y - 400, 400, "Morski smetar");
        Risalnik::narisi_niz(m_font, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y - 500, 400, m_vpisan_igralec);
    }
    else
    {
        Risalnik::narisi_niz(m_font, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y - 400, 400, "vpisi ime igralca");
        Risalnik::narisi_niz(m_font, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y - 500, 400, m_vpisan_igralec);
        if (Risalnik::get_tipko_tipkovnice(257))
        {
            m_sem_vpisan = true;
            Risalnik::trenutni_buffer_za_vpisovanje = nullptr;
            m_vpisan_igralec.pop_back();
        }
    }
}

void Zacetna::konec()
{
    m_glasba.stop();

    m_obala.unici();
    m_otoki.unici();
    m_igraj_gumb.unici();
    m_izhod_gumb.unici();
}