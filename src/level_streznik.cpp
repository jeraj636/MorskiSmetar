#include "../include/level_streznik.h"
#include <iostream>

/*
Pred uporabo natančno preberite navodilo!
O tveganju in neželenih učinkih se posvetujte
z zdravnikom ali s farmacevtom.
*/
Level_streznik::Level_streznik()
    : Level(),
      m_vticnik(m_io_kontekst)
{
}
void Level_streznik::zacetek()
{
    Risalnik::aktivna_scena = this;

    m_vticnik = asio::ip::udp::socket(m_io_kontekst, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8080));

    log::msg("STREZNIK");

    m_sem_zacel = false;
    m_sem_povezan = false;
}
/*
mea culpa
mea culpa
mea maxima culpa
*/
void Level_streznik::zanka()
{
    if (m_vticnik.available() > 0)
    {
        char tab[128];

        size_t len = m_vticnik.receive_from(asio::buffer(tab), m_koncna_tocka);

        asio::error_code ignorirana_napaka;
        if (tab[0] == 0)
        {
            log::msg("C: POZZ SERVER");

            m_sem_povezan = true;

            tab[0] = 1;
            double t = Cas::get_time();
            memcpy(&tab[1], &t, 8);
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka, 0, ignorirana_napaka);

            log::msg("S: POZZ CLIENT");
        }
        else if (tab[0] == 2)
        {
            log::msg("C: ZELIM SEME");
            log::msg("S: POSLJEM SEME");

            uint32_t seme = rand() % 0xffffffff;

            m_jasek.pozicija = mat::vec2(-100, -100);

            tab[0] = 3;
            memcpy(&tab[1], &seme, 4);

            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            m_sem_zacel = true;

            srand(seme);
            Level::zacetek();
            Objekt_crnc::multiplay = true;
            m_vegovec2.nastavi(&m_zemljevid);
            m_kdaj_zelim_vegovec_poz = Cas::get_time() + 0.01;
        }
        else if (tab[0] == 4)
        {

            tab[0] = 5;

            memcpy(&tab[1], &m_vegovec.pozicija.x, 4);
            memcpy(&tab[5], &m_vegovec.pozicija.y, 4);

            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            log::msg("C: ZELIM VEGOVEC POZICIJO");
            log::msg("S: POSILJAM VEGOVEC POZICIJO");
        }
        else if (tab[0] == 5)
        {

            memcpy(&m_vegovec2.pozicija.x, &tab[1], 4);
            memcpy(&m_vegovec2.pozicija.y, &tab[5], 4);
            log::msg("C: POSILJAM VEGOVEC POZICIJO");
        }
        else if (tab[0] == 6)
        {
            log::msg("C: ZELIM CRNC POZ");
            tab[0] = 7;
            tab[1] = m_crnci.size();
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            log::msg("S: POSILJAM CRMC VEL");
            for (int i = 0; i < m_crnci.size(); i++)
            {
                log::msg("S: POSILJAM CRMC POZ " + std::to_string(i));
                tab[0] = 8;
                tab[1] = i;

                int j = 2;
                memcpy(&tab[j], &m_crnci[i]->pozicija.x, 4);

                j += 4;
                memcpy(&tab[j], &m_crnci[i]->pozicija.y, 4);

                j += 4;
                memcpy(&tab[j], &m_crnci[i]->m_smer.x, 4);

                j += 4;
                memcpy(&tab[j], &m_crnci[i]->m_smer.y, 4);

                j += 4;
                memcpy(&tab[j], &m_crnci[i]->ali_zivim, 1);

                j += 1;
                memcpy(&tab[j], &m_crnci[i]->sem_pokopan, 1);

                j += 1;
                memcpy(&tab[j], &m_crnci[i]->m_naslednji_cas, 8);

                j += 8;
                memcpy(&tab[j], &m_crnci[i]->sem_mocan, 1);

                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            }
        }
        else if (tab[0] == 9)
        {
            m_crnci[tab[1]]->smrt();
            m_tocke += 10;
            log::msg("C: UBIT CRNC " + std::to_string(tab[1]));
        }
        else if (tab[0] == 10)
        {
            m_crnci[tab[1]]->sem_mocan = false;
            m_tocke -= 30;
            log::msg("C: BIL SEM UDARNJEN");
        }
        else if (tab[0] == 11)
        {
            log::msg("C: ZELIM SMETI");

            tab[0] = 12;
            int i = m_smeti.size();

            memcpy(&tab[1], &i, 4);
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            log::msg("S: POSILJAM VEL SMETI");
            for (int i = 0; i < m_smeti.size(); i++)
            {
                log::msg("S: POSILJAM POZ SMETI " + std::to_string(i));
                tab[0] = 13;
                int j = 1;
                memcpy(&tab[j], &i, 4);

                j += 4;
                memcpy(&tab[j], &m_smeti[i]->pozicija.x, 4);

                j += 4;
                memcpy(&tab[j], &m_smeti[i]->pozicija.y, 4);

                j += 4;
                memcpy(&tab[j], &m_smeti[i]->m_smer.x, 4);

                j += 4;
                memcpy(&tab[j], &m_smeti[i]->m_smer.y, 4);

                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            }
        }
        else if (tab[0] == 14) //! se ne uporablja
        {
            std::swap(m_smeti[tab[1]], m_smeti.back());
            delete m_smeti.back();
            m_smeti.pop_back();

            log::msg("C: POBRAL SEM SMET " + std::to_string(tab[1]));
        }
        else if (tab[0] == 15)
        {
            log::msg("C: ZELIM GRETA POZ");
            tab[0] = 16;
            tab[1] = m_grete.size();
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            log::msg("S: POSILJAM GRETA VEL");
            for (int i = 0; i < m_grete.size(); i++)
            {
                log::msg("S: POSILJAM GRETA POZ " + std::to_string(i));

                tab[0] = 17;
                tab[1] = i;
                int j = 2;
                memcpy(&tab[j], &m_grete[i]->pozicija.x, 4);

                j += 4;
                memcpy(&tab[j], &m_grete[i]->pozicija.y, 4);

                j += 4;
                memcpy(&tab[j], &m_grete[i]->m_smer.x, 4);

                j += 4;
                memcpy(&tab[j], &m_grete[i]->m_smer.y, 4);

                j += 4;
                memcpy(&tab[j], &m_grete[i]->ali_zivim, 1);

                j += 1;
                memcpy(&tab[j], &m_grete[i]->sem_pokopan, 1);

                j += 1;
                memcpy(&tab[j], &m_grete[i]->m_next_time, 8);

                j += 8;
                memcpy(&tab[j], &m_grete[i]->m_trenutna_smet, 4);

                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            }
        }
        else if (tab[0] == 18)
        {
            m_grete[tab[1]]->smrt();
            m_tocke -= 10;
            log::msg("C: UBIL SEM GRETO " + std::to_string(tab[1]));
        }
        else if (tab[0] == 19)
        {
            tab[0] = 20;
            void *tmp = tab;
            tmp = (char *)tmp + 1;
            memcpy(tmp, &m_tocke, 4);
            tmp = (char *)tmp + 4;
            double t = m_next_tocke_odboj - Cas::get_time();
            memcpy(tmp, &t, 8);

            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            log::war("C: ZELIM TOCKE");
        }

        else if (tab[0] == 127)
        {
            log::msg("C: SIGNAL ZA USTAVITAV");
            m_sem_povezan = false;
            m_sem_zacel = false;
            konec();
        }
    }
    /*
    Ko bi ne bil delal napak v preteklosti, bi .....
    */
    if (m_sem_zacel && m_sem_povezan)
    {
        if (m_kdaj_zelim_vegovec_poz <= Cas::get_time())

        {
            m_kdaj_zelim_vegovec_poz += 0.01;
            char tab[1];
            tab[0] = 4;
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            log::msg("S: ZELIM VEGOVEC POZICIJO");
        }
        m_obala.narisi_me();
        m_otoki.narisi_me();
        m_ura.narisi_me();
        m_tocke_obj.narisi_me();

        m_je_se_kaksen_crn = false;
        for (int i = 0; i < m_crnci.size(); i++)
        {
            m_crnci[i]->update(m_smeti, m_jasek, m_vegovec);
            m_crnci[i]->narisi_me();

            if (m_crnci[i]->ali_zivim)
                m_je_se_kaksen_crn = true;
            if (m_vegovec.trk(*m_crnci[i]))
            {
                if (Risalnik::get_tipko_tipkovnice(' ') && m_crnci[i]->ali_zivim)
                {
                    m_crnci[i]->smrt();
                    char tab[2];
                    tab[0] = 10;
                    tab[1] = i;
                    m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
                    m_tocke += 10;
                }
                if (m_crnci[i]->sem_mocan && m_vegovec.sem_lahko_udarjen())
                {
                    m_tocke -= 30;
                    m_crnci[i]->sem_mocan = false;
                    m_vegovec.udarjen();
                }
            }
            for (int j = 0; j < m_crnci.size(); j++) // ce se dva crnca zadaneta
            {
                if (m_crnci[i]->ali_zivim && m_crnci[j]->ali_zivim && j != i && m_crnci[i]->trk(*m_crnci[j]))
                {
                    m_crnci[j]->trk_s_crnim();
                }
            }
        }

        for (int i = 0; i < m_grete.size(); i++)
        {
            int t = m_grete[i]->update(m_smeti, m_tocke, m_jasek);
            if (t != -1)
            {
                std::swap(m_smeti[t], m_smeti.back());
                delete m_smeti.back();
                m_smeti.pop_back();
                m_tocke += 5;
            }
            m_grete[i]->narisi_me();
            if (m_vegovec.trk(*m_grete[i]) && Risalnik::get_tipko_tipkovnice(' ') && m_grete[i]->ali_zivim)
            {
                m_grete[i]->smrt();
                m_tocke -= 10;
                char tab[2];
                tab[0] = 18;
                tab[1] = i;
                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            }
        }

        for (int i = 0; i < m_smeti.size(); i++)
        {
            m_smeti[i]->update();
            m_smeti[i]->narisi_me();
            if (m_vegovec.trk(*m_smeti[i]) || m_vegovec2.trk(*m_smeti[i]))
            {
                std::swap(m_smeti[i], m_smeti.back());
                delete m_smeti.back();
                m_smeti.pop_back();
                m_tocke += 5;
            }
        }

        //! Jaz sem zabit!!!!
        m_vegovec.update(m_jasek);
        m_vegovec.narisi_me();

        m_vegovec2.update_o(m_jasek);
        m_vegovec2.narisi_me();

        Risalnik::narisi_niz(m_pisava, 0x000000ff, 0, mat::vec2(70, Risalnik::get_velikost_okna().y - 115), 500, std::to_string(m_tocke));

        if (Risalnik::get_tipko_tipkovnice('R'))
        {
            konec();
        }

        if (konec_igre()) // konec igre
        {
            Risalnik::narisi_niz(m_pisava, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y / 2, 400, "BRAVO!");
            m_izhod_gumb.narisi_me();
            if (m_izhod_gumb.je_miska_gor())
            {
                m_izhod_gumb.barva_objekta.set_a(0xaa);
                if (Risalnik::get_miskin_gumb() == Gumb::levi)
                {
                    konec();
                    zacetna->zacetek();
                    Risalnik::aktivna_scena = zacetna;
                }
            }
            else
            {
                m_izhod_gumb.barva_objekta.set_a(0xff);
            }
        }
        else
        {
            Risalnik::narisi_niz(m_pisava, 0x000000ff, Barva(0), mat::vec2(70, Risalnik::get_velikost_okna().y - 55), 500, std::to_string((int)floor(m_next_tocke_odboj - Cas::get_time())));
            if (m_next_tocke_odboj <= Cas::get_time())
            {
                if (m_tocke <= 0)
                    m_tocke -= rand() % 10;
                else
                {
                    m_tocke -= rand() % m_tocke / 2 + m_tocke / 6;
                }
                m_next_tocke_odboj = Cas::get_time() + rand() % 10;
            }
        }

        Risalnik::narisi_niz(m_pisava, 0xffffffff, 0, 50, 500, "STREZNIK");
    }
}

void Level_streznik::konec()
{

    if (m_sem_povezan)
    {
        char tab[8];
        tab[0] = 127;
        m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
    }
    m_sem_povezan = false;
    m_vticnik.close();
    Level::konec();
    // zacetna->zacetek();
}
