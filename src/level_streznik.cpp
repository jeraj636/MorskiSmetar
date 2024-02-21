#include "../include/level_streznik.h"
#include <iostream>
Level_streznik::Level_streznik()
    : Level(),
      m_vticnik(m_io_kontekst)
{
    Objekt_vegovec2::init();
}
void Level_streznik::zacetek()
{
    m_vticnik = asio::ip::udp::socket(m_io_kontekst, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8080));

    log::msg("STREZNIK");
    Risalnik::aktivna_scena = this;
    m_sem_zacel = false;
    m_sem_povezan = false;
    // Cas::nastavi_staticen_delta_time(true, 0.03);
    //  m_naslednje_posiljanje = Cas::get_time() + 0.1f;
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

            m_sem_povezan = true;
            tab[0] = 1;
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka, 0, ignorirana_napaka);
            log::msg("C: POZZ SERVER");
            log::msg("S: POZZ CLIENT");
        }
        else if (tab[0] == 2)
        {
            log::msg("C: ZELIM SEME");
            log::msg("S: POSLJEM SEME");
            uint32_t seme = rand() % 0xffffffff;
            srand(seme);
            Level::zacetek();
            std::cout << seme << "\n";
            tab[0] = 3;
            int i = 2;
            while (seme >= 1)
            {
                tab[i] = seme % 10;
                i++;
                seme /= 10;
            }
            i -= 2;
            tab[1] = i;
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            m_sem_zacel = true;
            m_vegovec2.nastavi(&m_zemljevid);
            m_kdaj_zelim_vegovec_poz = Cas::get_time() + 0.01;
        }
        else if (tab[0] == 4)
        {

            tab[0] = 5;
            void *tmp = tab;
            tmp = (char *)tmp + 1;
            memcpy(tmp, &m_vegovec.pozicija.x, 4);
            tmp = (char *)tmp + 4;
            memcpy(tmp, &m_vegovec.pozicija.y, 4);
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            log::msg("S: ZELIM VEGOVEC POZICIJO");
            log::msg("C: POSILJAM VEGOVEC POZICIJO");
        }
        else if (tab[0] == 5)
        {

            void *tmp = tab;
            tmp = (char *)tmp + 1;
            memcpy(&m_vegovec2.pozicija.x, tmp, 4);
            tmp = (char *)tmp + 4;
            memcpy(&m_vegovec2.pozicija.y, tmp, 4);
        }
        else if (tab[0] == 6)
        {
            log::msg("C: ZELIM CRNC POZ");
            tab[0] = 7;
            tab[1] = m_crnci.size();
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            log::msg("S: POSILJAM CRMC POZ");
            for (int i = 0; i < m_crnci.size(); i++)
            {
                tab[0] = 8;
                tab[1] = i;
                void *tmp = tab;
                tmp = (char *)tmp + 2;
                memcpy(tmp, &m_crnci[i]->pozicija.x, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_crnci[i]->pozicija.y, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_crnci[i]->m_smer.x, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_crnci[i]->m_smer.y, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_crnci[i]->ali_zivim, 1);

                tmp = (char *)tmp + 1;
                memcpy(tmp, &m_crnci[i]->sem_pokopan, 1);

                tmp = (char *)tmp + 1;
                memcpy(tmp, &m_crnci[i]->m_naslednji_cas, 8);

                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            }
        }
        else if (tab[0] == 10)
        {
            m_crnci[tab[1]]->smrt();
        }
        else if (tab[0] == 11)
        {
            log::msg("C: ZELIM SMETI");
            tab[0] = 12;
            // tab[1] = m_smeti.size();
            int i = m_smeti.size();
            void *tmp = tab;
            tmp = (char *)tmp + 1;
            memcpy(tmp, &i, 4);
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            std::cout << "tukaj1" << std::endl;
            for (int i = 0; i < m_smeti.size(); i++)
            {
                tab[0] = 13;
                tmp = tab;
                tmp = (char *)tmp + 1;
                memcpy(tmp, &i, 4);
                std::cout << i << m_smeti.size() << "\n";
                // std::cout << i << "\n";

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_smeti[i]->pozicija.x, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_smeti[i]->pozicija.y, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_smeti[i]->m_smer.x, 4);
                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_smeti[i]->m_smer.y, 4);
                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            }
        }
        else if (tab[0] == 15)
        {
            log::msg("C: ZELIM GRETA POZ");
            tab[0] = 16;
            tab[1] = m_grete.size();
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            log::msg("S: POSILJAM GRETA POZ");
            for (int i = 0; i < m_grete.size(); i++)
            {
                tab[0] = 17;
                tab[1] = i;
                void *tmp = tab;
                tmp = (char *)tmp + 2;
                memcpy(tmp, &m_grete[i]->pozicija.x, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_grete[i]->pozicija.y, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_grete[i]->m_smer.x, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_grete[i]->m_smer.y, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_grete[i]->ali_zivim, 1);

                tmp = (char *)tmp + 1;
                memcpy(tmp, &m_grete[i]->sem_pokopan, 1);

                tmp = (char *)tmp + 1;
                memcpy(tmp, &m_grete[i]->m_next_time, 8);

                tmp = (char *)tmp + 8;
                memcpy(tmp, &m_grete[i]->m_trenutna_smet, 4);

                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            }
        }
        else if (tab[0] == 18)
        {
            m_grete[tab[1]]->smrt();
        }
        else if (tab[0] == 19)
        {
            log::msg("C: ZELIM JUDE POZ");
            tab[0] = 20;
            tab[1] = m_judi.size();
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            for (int i = 0; i < m_judi.size(); i++)
            {
                tab[0] = 21;
                tab[1] = i;
                void *tmp = tab;
                tmp = (char *)tmp + 2;
                memcpy(tmp, &m_judi[i]->pozicija.x, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_judi[i]->pozicija.y, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_judi[i]->m_smer.x, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_judi[i]->m_smer.y, 4);

                tmp = (char *)tmp + 4;
                memcpy(tmp, &m_judi[i]->ali_zivim, 1);

                tmp = (char *)tmp + 1;
                memcpy(tmp, &m_judi[i]->sem_pokopan, 1);

                tmp = (char *)tmp + 1;
                memcpy(tmp, &m_judi[i]->m_naslednji_cas, 8);

                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            }
        }
        else if (tab[0] == 22)
        {
            m_judi[tab[1]]->smrt();
            m_st_judov--;
            m_tocke -= 30;
        }
        else if (tab[0] == 127)
        {
            log::msg("C: SIGNAL ZA USTAVITAV");
            m_sem_povezan = false;
            m_sem_zacel = false;
            konec();
        }
    }

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
        // Level::zanka();
        m_obala.narisi_me();
        m_otoki.narisi_me();
        m_ura.narisi_me();
        m_tocke_obj.narisi_me();

        m_jasek.narisi_me();

        m_je_se_kaksen_crn = false;
        for (int i = 0; i < m_crnci.size(); i++)
        {
            m_crnci[i]->update(m_smeti, m_jasek);
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
                m_tocke++;
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

        for (int i = 0; i < m_judi.size(); i++)
        {
            m_judi[i]->update(m_jasek, m_cekini);
            m_judi[i]->narisi_me();
            if (m_judi[i]->ali_zivim)
            {
                if (m_judi[i]->sem_lahko_ubit() && m_judi[i]->ali_zivim)
                {

                    for (int j = 0; j < m_crnci.size(); j++)
                        if (m_crnci[j]->trk(*m_judi[i]) && m_crnci[j]->ali_zivim)
                        {
                            m_judi[i]->smrt();
                            m_st_judov--;
                            char tab[2];
                            tab[0] = 22;
                            tab[1] = i;
                            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
                        }
                    if (m_judi[i]->trk(m_vegovec) && Risalnik::get_tipko_tipkovnice(' '))
                    {
                        /*
                        na tej tocki nevem ali bi sploh se bil programer
                        veliko lažje bi bilo pomivati posoda v domu za ostarele
                        ali pa streči hrano v kakšni beznici
                        */
                        m_judi[i]->smrt();
                        m_st_judov--;
                        m_tocke -= 30;
                        char tab[2];
                        tab[0] = 22;
                        tab[1] = i;
                        m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
                    }
                }
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

        for (int i = 0; i < m_cekini.size(); i++)
        {
            m_cekini[i]->narisi_me();
            if (m_vegovec.trk(*m_cekini[i]))
            {
                if (!konec_igre())
                    m_tocke += 20;
                std::swap(m_cekini[i], m_cekini.back());
                delete m_cekini.back();
                m_cekini.pop_back();
                break;
            }

            if (m_cekini[i]->ttl <= Cas::get_time())
            {
                std::swap(m_cekini[i], m_cekini.back());
                delete m_cekini.back();
                m_cekini.pop_back();
                break;
            }
        }

        //! Jaz sem zabit!!!!
        m_vegovec.update(m_jasek);
        m_vegovec.narisi_me();

        Risalnik::narisi_niz(m_pisava, 0x000000ff, 0, mat::vec2(70, Risalnik::get_velikost_okna().y - 115), 500, std::to_string(m_tocke));

        if (Risalnik::get_tipko_tipkovnice('R'))
        {
            konec();
            zacetna->zacetek();
            Risalnik::aktivna_scena = zacetna;
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

        if (m_st_judov < m_st_judov_const) // preverjanje števeila judov
        {
            m_jasek.naredi_juda(m_judi, &m_zemljevid);
            m_st_judov++;
        }
        m_vegovec2.update_o(m_jasek);
        m_vegovec2.narisi_me();
        Risalnik::narisi_niz(m_pisava, 0xffffffff, 0, 50, 500, "streznik");
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
    zacetna->zacetek();
}
