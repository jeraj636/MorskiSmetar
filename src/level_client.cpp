#include "../include/level_client.h"

Level_client::Level_client()
    : Level(),
      m_razresevalnik(m_io_kontekst),
      m_vticnik(m_io_kontekst)
{
    Objekt_vegovec2::init();
}
void Level_client::zacetek()
{
    Risalnik::aktivna_scena = this;

    m_koncna_tocka = *m_razresevalnik.resolve(asio::ip::udp::v4(), "127.0.0.1", "8080").begin();

    m_vticnik.open(asio::ip::udp::v4());
    m_vticnik.send_to(asio::buffer("\0"), m_koncna_tocka);
    log::msg("CLIENT");
    log::msg("C: POZZ SERVER");
    m_sem_povezan = false;
    m_sem_zacel = false;
}
void Level_client::zanka()
{
    if (m_vticnik.available() > 0)
    {
        char tab[128];
        size_t len = m_vticnik.receive_from(asio::buffer(tab), m_koncna_tocka);

        if (tab[0] == 1)
        {

            m_sem_povezan = true;
            log::msg("S: POZZ CLIENT");
            tab[0] = 2;
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            log::msg("C: ZELIM SEME");
        }
        else if (tab[0] == 3)
        {
            uint32_t seme = 0;
            log::msg("S: POSILJAM SEME");
            for (int i = tab[1] - 1; i >= 0; i--)
            {
                seme += tab[i + 2];
                seme *= 10;
            }
            seme /= 10;
            std::cout << seme << "\n";
            srand(seme);
            Level::zacetek();
            m_sem_zacel = true;
            m_vegovec2.nastavi(&m_zemljevid);
            m_kdaj_zelim_vegovec_poz = Cas::get_time() + 0.01;
        }
        else if (tab[0] == 4)
        {
            int x = m_vegovec2.pozicija.x;
            int y = m_vegovec2.pozicija.y;
            tab[0] = 5;
            std::string X = std::to_string(x);
            std::string Y = std::to_string(y);
            /*
            if (x < 1000)
                X.pop_back();
            if (y < 1000)
                Y.pop_back();
            */
            for (int i = 1; i < 9; i++)
                tab[i] = 0;

            for (int i = X.size() - 1; i >= 0; i--)
            {

                if (x < 1000)
                    tab[i + 2] = X[i] - '0';
                else if (x < 100)
                    tab[i + 3] = X[i] - '0';

                else
                    tab[i + 1] = X[i] - '0';
            }
            for (int i = Y.size() - 1; i >= 0; i--)
            {
                if (y < 1000)
                    tab[i + 6] = Y[i] - '0';
                else if (y < 100)
                    tab[i + 7] = Y[i] - '0';
                else
                    tab[i + 5] = Y[i] - '0';
            }
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            log::msg("S: ZELIM VEGOVEC POZICIJO");
            log::msg("C: POSILJAM VEGOVEC POZICIJO");
            // std::cout << X << Y << "\n";
        }
        else if (tab[0] == 5)
        {
            /*
            for (int i = 0; i < 9; i++)
            {
                std::cout << (int)tab[i];
            }
            std::cout << "\n";
            */
            int x = 0;
            int y = 0;
            for (int i = 0; i < 4; i++)
            {
                x += tab[i + 1];
                y += tab[i + 5];
                x *= 10;
                y *= 10;
            }
            y /= 10;
            x /= 10;
            m_vegovec.pozicija = mat::vec2(x, y);
        }
        else if (tab[0] == 127)
        {
            log::msg("S: SIGNAL ZA USTAVITAV");
            m_sem_povezan = false;
            konec();
        }
    }

    if (m_sem_zacel && m_sem_povezan)
    {
        if (m_kdaj_zelim_vegovec_poz <= Cas::get_time())
        {
            std::cout << m_vegovec2.pozicija;
            m_kdaj_zelim_vegovec_poz += 0.01;
            char tab[1];
            tab[0] = 4;
            m_vticnik.send_to(asio::buffer(tab), m_koncna_tocka);
            log::msg("C: ZELIM VEGOVEC POZICIJO");
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
            m_grete[i]->update(m_smeti, m_tocke, m_jasek);
            m_grete[i]->narisi_me();
            if (m_vegovec.trk(*m_grete[i]) && Risalnik::get_tipko_tipkovnice(' ') && m_grete[i]->ali_zivim)
            {
                m_grete[i]->smrt();
                m_tocke -= 10;
            }
        }

        for (int i = 0; i < m_judi.size(); i++)
        {
            m_judi[i]->update(m_jasek, m_cekini);
            m_judi[i]->narisi_me();
            if (m_judi[i]->ali_zivim)
            {
                if (m_judi[i]->sem_lahko_ubit())
                {

                    for (int j = 0; j < m_crnci.size(); j++)
                        if (m_crnci[j]->trk(*m_judi[i]) && m_crnci[j]->ali_zivim)
                        {
                            m_judi[i]->smrt();
                            m_st_judov--;
                        }
                    if (m_judi[i]->trk(m_vegovec) && Risalnik::get_tipko_tipkovnice(' '))
                    {

                        m_judi[i]->smrt();
                        m_st_judov--;
                        m_tocke -= 30;
                    }
                }
            }
        }

        for (int i = 0; i < m_smeti.size(); i++)
        {
            m_smeti[i]->update();
            m_smeti[i]->narisi_me();
            if (m_vegovec.trk(*m_smeti[i]))
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
        m_vegovec.update_o(m_jasek);
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
        m_vegovec2.update(m_jasek);
        m_vegovec2.narisi_me();
        Risalnik::narisi_niz(m_pisava, 0xffffffff, 0, 50, 500, "client");
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

    m_sem_povezan = false;
    m_vticnik.close();
    Level::konec();
    zacetna->zacetek();
}
