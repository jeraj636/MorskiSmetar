#include "../include/level_client.h"
#include <fstream>

Level_client::Level_client()
    : Level(),
      m_razresevalnik(m_io_kontekst),
      m_vticnik(m_io_kontekst)
{
}
void Level_client::zacetek()
{
    Risalnik::aktivna_scena = this;

    m_imam_ip = false;
    m_sem_povezan = false;
    m_sem_zacel = false;
    Risalnik::trenutni_buffer_za_vpisovanje = &m_ip_streznika;
}
void Level_client::zanka()
{
    if (m_imam_ip)
    {

        if (m_vticnik.available() > 0)
        {
            char tab[128];
            size_t len = m_vticnik.receive_from(asio::buffer(tab), m_koncna_tocka);

            if (tab[0] == 1)
            {

                log::msg("S: POZZ CLIENT");
                m_sem_povezan = true;

                double t;
                memcpy(&t, &tab[1], 8);
                Cas::sin_cas = Cas::get_time() - t;

                tab[0] = 2;
                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);

                log::msg("C: ZELIM SEME");
            }

            else if (tab[0] == 3)
            {
                uint32_t seme = 0;
                log::msg("S: POSILJAM SEME");
                memcpy(&seme, &tab[1], 4);

                srand(seme);
                Level::zacetek();
                m_jasek.pozicija = mat::vec2(-100, -100);
                m_sem_zacel = true;
                m_vegovec2.nastavi(&m_zemljevid);

                m_kdaj_zelim_vegovec_poz = Cas::get_time() + 0.01;
                m_kdaj_zelim_crnce = Cas::get_time() + 0.1;
                m_kdaj_zelim_smeti = Cas::get_time() + 0.2;
                m_kdaj_zelim_grete = Cas::get_time() + 0.3;
                m_kdaj_zelim_tocke = Cas::get_time() + 0.5;
            }

            else if (tab[0] == 4)
            {

                tab[0] = 5;

                memcpy(&tab[1], &m_vegovec2.pozicija.x, 4);
                memcpy(&tab[5], &m_vegovec2.pozicija.y, 4);

                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
                log::msg("S: ZELIM VEGOVEC POZICIJO");
                log::msg("C: POSILJAM VEGOVEC POZICIJO");
            }

            else if (tab[0] == 5)
            {

                memcpy(&m_vegovec.pozicija.x, &tab[1], 4);
                memcpy(&m_vegovec.pozicija.y, &tab[5], 4);
                log::msg("S: POSILJAM VEGOVEC POZICIJO");
            }

            else if (tab[0] == 7)
            {
                log::msg("S: POSILJAM CRNC VEL");
                // m_crnci.resize(tab[1]);
                if (m_crnci.size() != tab[1])
                    log::err("NOT GOOD");
            }

            else if (tab[0] == 8)
            {
                int i = tab[1];
                int j = 2;
                memcpy(&m_crnci[i]->pozicija.x, &tab[j], 4);

                j += 4;
                memcpy(&m_crnci[i]->pozicija.y, &tab[j], 4);

                j += 4;
                memcpy(&m_crnci[i]->m_smer.x, &tab[j], 4);

                j += 4;
                memcpy(&m_crnci[i]->m_smer.y, &tab[j], 4);

                j += 4;
                memcpy(&m_crnci[i]->ali_zivim, &tab[j], 1);

                j += 1;
                memcpy(&m_crnci[i]->sem_pokopan, &tab[j], 1);

                j += 1;
                memcpy(&m_crnci[i]->m_naslednji_cas, &tab[j], 8);

                j += 8;
                memcpy(&m_crnci[i]->sem_mocan, &tab[j], 1);

                log::msg("S: POSILJAM CRNC" + std::to_string(tab[1]));
            }

            else if (tab[0] == 10)
            {
                m_crnci[tab[1]]->smrt();
                log::msg("S: UBIL CRNEGA " + std::to_string(tab[1]));
            }

            else if (tab[0] == 12)
            {
                int i = m_smeti.size();
                int k;

                memcpy(&k, &tab[1], 4);
                log::msg("S: POSILJAM VEL SMETI " + std::to_string(k));
                if (i < k)
                {
                    while (m_smeti.size() != i)
                    {
                        m_smeti.push_back(new Objekt_smeti);
                        m_smeti.back()->nastavi(&m_zemljevid, mat::vec2(0, 0));
                    }
                }

                else if (i > k)
                {
                    while (m_smeti.size() != i)
                    {
                        delete m_smeti.back();
                        m_smeti.pop_back();
                    }
                }
            }

            else if (tab[0] == 13)
            {

                int i;
                int j = 1;
                memcpy(&i, &tab[j], 4);
                if (i < m_smeti.size())
                {

                    j += 4;
                    memcpy(&m_smeti[i]->pozicija.x, &tab[j], 4);

                    j += 4;
                    memcpy(&m_smeti[i]->pozicija.y, &tab[j], 4);

                    j += 4;
                    memcpy(&m_smeti[i]->m_smer.x, &tab[j], 4);

                    j += 4;
                    memcpy(&m_smeti[i]->m_smer.y, &tab[j], 4);
                }
                log::msg("S: POSILJAM POZICIJO SMETI " + std::to_string(i));
            }

            else if (tab[0] == 16)
            {
                log::msg("S: POSILJAM GRETE VEL " + std::to_string(tab[1]));
                if (tab[1] != m_grete.size())
                    log::err("NOT GOOD");
            }

            else if (tab[0] == 17)
            {
                int i = tab[1];
                int j = 2;
                memcpy(&m_grete[i]->pozicija.x, &tab[j], 4);

                j += 4;
                memcpy(&m_grete[i]->pozicija.y, &tab[j], 4);

                j += 4;
                memcpy(&m_grete[i]->m_smer.x, &tab[j], 4);

                j += 4;
                memcpy(&m_grete[i]->m_smer.y, &tab[j], 4);

                j += 4;
                memcpy(&m_grete[i]->ali_zivim, &tab[j], 1);

                j += 1;
                memcpy(&m_grete[i]->sem_pokopan, &tab[j], 1);

                j += 1;
                memcpy(&m_grete[i]->m_next_time, &tab[j], 8);

                j += 8;
                memcpy(&m_grete[i]->m_trenutna_smet, &tab[j], 4);
                log::msg("S: POSILJAM POZICIJO GRETE " + std::to_string(i));
            }

            else if (tab[0] == 18)
            {
                m_grete[tab[1]]->smrt();
                log::msg("S: UBIL SEM GRETO");
            }

            else if (tab[0] == 20)
            {

                memcpy(&m_tocke, &tab[1], 4);
                memcpy(&m_next_tocke_odboj, &tab[5], 8);
                log::msg("S: POSILJAM TOCKE");
            }

            else if (tab[0] == 127)
            {
                log::msg("S: SIGNAL ZA USTAVITAV");
                m_sem_povezan = false;
                m_sem_zacel = false;
                konec();
            }
        }

        if (m_sem_zacel && m_sem_povezan)
        {
            if (m_kdaj_zelim_vegovec_poz <= Cas::get_time())
            {
                // std::cout << m_vegovec2.pozicija;
                m_kdaj_zelim_vegovec_poz += 0.01;
                char tab[1];
                tab[0] = 4;
                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
                log::msg("C: ZELIM VEGOVEC POZICIJO");
            }
            if (m_kdaj_zelim_crnce <= Cas::get_time())
            {
                // std::cout << m_vegovec2.pozicija;
                m_kdaj_zelim_crnce += .07;
                char tab[1];
                tab[0] = 6;
                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
                log::msg("C: ZELIM CRNC POZ");
            }
            if (m_kdaj_zelim_smeti <= Cas::get_time())
            {
                // std::cout << m_vegovec2.pozicija;
                m_kdaj_zelim_smeti += .07;
                char tab[1];
                tab[0] = 11;
                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
                log::msg("C: ZELIM SMETI POZ");
            }
            if (m_kdaj_zelim_grete <= Cas::get_time())
            {
                // std::cout << m_vegovec2.pozicija;
                m_kdaj_zelim_grete += .07;
                char tab[1];
                tab[0] = 15;
                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
                log::msg("C: ZELIM GRETE POZ");
            }
            if (m_kdaj_zelim_tocke <= Cas::get_time())
            {
                // std::cout << m_vegovec2.pozicija;
                m_kdaj_zelim_tocke += .7;
                char tab[1];
                tab[0] = 19;
                m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
                log::msg("C: ZELIM TOCKE POZ");
            }

            m_obala.narisi_me();
            m_otoki.narisi_me();

            m_ura.narisi_me();
            m_tocke_obj.narisi_me();

            // Risalnik::narisi_niz(m_pisava, 0xffffffff, 0, 200, 400, std::to_string(Cas::get_time()));
            //  m_jasek.narisi_me();

            m_je_se_kaksen_crn = false;
            for (int i = 0; i < m_crnci.size(); i++)
            {
                m_crnci[i]->update(m_smeti, m_jasek);
                m_crnci[i]->narisi_me();

                if (m_crnci[i]->ali_zivim)
                    m_je_se_kaksen_crn = true;
                if (m_vegovec2.trk(*m_crnci[i]))
                {
                    if (Risalnik::get_tipko_tipkovnice(' ') && m_crnci[i]->ali_zivim)
                    {

                        m_crnci[i]->smrt();
                        m_tocke += 10;
                        char tab[2];
                        tab[0] = 9;
                        tab[1] = i;
                        m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
                    }
                    if (m_crnci[i]->sem_mocan && m_vegovec2.sem_lahko_udarjen())
                    {
                        m_tocke -= 30;
                        m_crnci[i]->sem_mocan = false;
                        m_vegovec2.udarjen();
                        char tab[2];
                        tab[0] = 10;
                        tab[1] = i;
                        m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
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
                    /*
                        char tab[2];
                        tab[0] = 14;
                        tab[1] = t;
                        m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
                    */
                }
                m_grete[i]->narisi_me();
                if (m_vegovec2.trk(*m_grete[i]) && Risalnik::get_tipko_tipkovnice(' ') && m_grete[i]->ali_zivim)
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

                if (m_vegovec2.trk(*m_smeti[i]))
                {
                    std::swap(m_smeti[i], m_smeti.back());
                    delete m_smeti.back();
                    m_smeti.pop_back();
                    m_tocke += 5;
                }
            }

            //! Jaz sem zabit!!!!
            m_vegovec.update_o(m_jasek);
            m_vegovec.narisi_me();

            m_vegovec2.update(m_jasek);
            m_vegovec2.narisi_me();

            Risalnik::narisi_niz(m_pisava, 0x000000ff, 0, mat::vec2(70, Risalnik::get_velikost_okna().y - 115), 500, std::to_string(m_tocke));
            if (!konec_igre())
                Risalnik::narisi_niz(m_pisava, 0x000000ff, Barva(0), mat::vec2(70, Risalnik::get_velikost_okna().y - 55), 500, std::to_string((int)floor(m_next_tocke_odboj)));

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
                    }
                }
                else
                {
                    m_izhod_gumb.barva_objekta.set_a(0xff);
                }
            }

            Risalnik::narisi_niz(m_pisava, 0xffffffff, 0, 50, 500, "client");
        }
    }
    else
    {
        Risalnik::narisi_niz(m_pisava, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y - 400, 400, "vpisi ip streznika");
        Risalnik::narisi_niz(m_pisava, Barva(0xffffffff), Barva(0), Risalnik::get_velikost_okna().y - 500, 400, m_ip_streznika);
        if (Risalnik::get_tipko_tipkovnice(257))
        {
            m_ip_streznika.pop_back();
            m_koncna_tocka = *m_razresevalnik.resolve(asio::ip::udp::v4(), m_ip_streznika, "8080").begin();
            Risalnik::trenutni_buffer_za_vpisovanje = nullptr;

            m_vticnik.open(asio::ip::udp::v4());
            m_vticnik.send_to(asio::buffer("\0"), m_koncna_tocka);
            log::msg("CLIENT");
            log::msg("C: POZZ SERVER");
            m_imam_ip = true;
        }
    }
}
void Level_client::konec()
{
    if (m_sem_povezan)
    {
        char tab[8];
        tab[0] = 127;
        m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
    }
    Cas::sin_cas = 0;
    m_sem_povezan = false;
    m_vticnik.close();
    Level::konec();
    zacetna->zacetek();
}
