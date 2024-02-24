#include "../include/zacetna.h"
#include <fstream>
#include <sstream>
Zacetna::Zacetna(Scena *level_scena, Scena *client_scena, Scena *server_scena)
{
    m_level_scena = level_scena;
    m_server_scena = server_scena;
    m_client_scena = client_scena;

    m_sem_vpisan = false;
    m_glasba = Risalnik::nalozi_zvok("zvok/theme.mp3");

    m_vpisan_igralec.tocke = 0;

    Risalnik::trenutni_buffer_za_vpisovanje = &m_vpisan_igralec.ime;
}
void Zacetna::zacetek()
{
    m_font = Risalnik::nalozi_font("FixedDays.ttf", 40);
    // samo za testiranje
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

    m_izhod_gumb.nastavi(mat::vec2(Risalnik::get_velikost_okna().x / 2 - 110, 800), mat::vec2(100, 100), 0, 0xffffffff, 0);
    m_izhod_gumb.id_teksture = Risalnik::nalozi_teksturo("ui/izhod_gumb.png");

    m_zamenjaj_ime_gumb.nastavi(mat::vec2(Risalnik::get_velikost_okna().x / 2 + 110, 800), mat::vec2(100, 100), 0, 0xffffffff, 0);
    m_zamenjaj_ime_gumb.id_teksture = Risalnik::nalozi_teksturo("ui/zamenjaj_ime.png");

    m_igraj_gumb.aktiven = true;
    m_izhod_gumb.aktiven = true;
    m_server_gumb.aktiven = true;
    m_client_gumb.aktiven = true;

    m_zac_time = Cas::get_time() + 1;
    Risalnik::aktivna_scena = this;
}

void Zacetna::zanka()
{
    if (m_sem_vpisan)
    {

        m_igraj_gumb.pozicija.x = Risalnik::get_velikost_okna().x / 2 - 110;
        m_izhod_gumb.pozicija.x = Risalnik::get_velikost_okna().x / 2 - 60;
        m_server_gumb.pozicija.x = Risalnik::get_velikost_okna().x / 2;
        m_client_gumb.pozicija.x = Risalnik::get_velikost_okna().x / 2 + 110;
        m_zamenjaj_ime_gumb.pozicija.x = Risalnik::get_velikost_okna().x / 2 + 60;
        m_obala.narisi_me();
        m_otoki.narisi_me();

        m_igraj_gumb.narisi_me();
        m_izhod_gumb.narisi_me();
        m_server_gumb.narisi_me();
        m_client_gumb.narisi_me();
        m_zamenjaj_ime_gumb.narisi_me();
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
                    konec();
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
            if (m_zamenjaj_ime_gumb.je_miska_gor())
            {
                m_zamenjaj_ime_gumb.barva_objekta.set_a(0x55);
                if (Risalnik::get_miskin_gumb() == Gumb::levi)
                {
                    m_sem_vpisan = false;
                    m_vpisan_igralec.tocke = 0;
                    m_vpisan_igralec.ime = "";
                    Risalnik::trenutni_buffer_za_vpisovanje = &m_vpisan_igralec.ime;
                }
            }
            else
            {
                m_zamenjaj_ime_gumb.barva_objekta.set_a(0xff);
            }
        }
        Risalnik::narisi_niz(m_font, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y - 400, 400, "Morski smetar");
        Risalnik::narisi_niz(m_font, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y - 500, 400, m_vpisan_igralec.ime + "  " + std::to_string(m_vpisan_igralec.tocke));

        for (int i = 0; i < 5; i++)
        {

            std::string s = m_igralci[i].ime;
            s = s + "  ";
            s = s + std::to_string(m_igralci[i].tocke);
            Risalnik::narisi_niz(m_font, 0xffffffff, 0, mat::vec2(1500, 400 - i * 50), 600, s);
        }
    }
    else
    {
        m_obala.narisi_me();
        m_otoki.narisi_me();
        Risalnik::narisi_niz(m_font, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y - 400, 400, "vpisi ime igralca");
        Risalnik::narisi_niz(m_font, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y - 500, 400, m_vpisan_igralec.ime);
        if (Risalnik::get_tipko_tipkovnice(257))
        {
            m_sem_vpisan = true;

            Risalnik::trenutni_buffer_za_vpisovanje = nullptr;
            m_vpisan_igralec.ime.pop_back();

            std::ifstream datoteka("../../sredstva/podatki_o_igralcih.txt");
            std::string s;
            int i = 0;
            while (std::getline(datoteka, s) && i < 5)
            {
                std::stringstream str(s);
                str >> m_igralci[i].ime;
                str >> m_igralci[i].tocke;
                if (m_igralci[i].ime == m_vpisan_igralec.ime)
                {
                    m_vpisan_igralec.tocke = m_igralci[i].tocke;
                }
                i++;
            }
        }
    }
}

void Zacetna::konec()
{
    std::ofstream datoteka("../../sredstva/podatki_o_igralcih.txt", std::ios::trunc);
    for (int i = 0; i < 5; i++)
    {
        datoteka << m_igralci[i].ime << "  " << m_igralci[i].tocke << std::endl;
    }

    datoteka.close();

    m_glasba.stop();

    m_font.unici();
    m_obala.unici();
    m_otoki.unici();
    m_igraj_gumb.unici();
    m_izhod_gumb.unici();
    m_server_gumb.unici();
    m_client_gumb.unici();
    m_zamenjaj_ime_gumb.unici();
}
void Zacetna::posodobi_igralca(int tocke)
{
    m_vpisan_igralec.tocke += tocke;
    bool sem_notri = false;
    for (int i = 0; i < 5; i++)
        if (m_igralci[i].ime == m_vpisan_igralec.ime)
        {
            m_igralci[i].tocke += tocke;
            for (int j = i; j >= 1 && m_vpisan_igralec.tocke >= m_igralci[j - 1].tocke; j--)
            {
                Igralec i = m_igralci[j];
                m_igralci[j] = m_igralci[j - 1];
                m_igralci[j - 1] = i;
            }
            sem_notri = true;
            break;
        }
    if (!sem_notri)
        for (int i = 0; i < 5; i++)
        {

            if (m_vpisan_igralec.tocke > m_igralci[i].tocke)
            {
                for (int j = 4; j > i; j--)
                {
                    m_igralci[j] = m_igralci[j - 1];
                }
                m_igralci[i] = m_vpisan_igralec;
                break;
            }
        }
}