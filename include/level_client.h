#ifndef LEVEL_CLIENT
#define LEVEL_CLIENT
#include "../include/level.h"
#include "../include/zacetna.h"
#define ASIO_STANDALONE
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS
#include <asio.hpp>
class Level_client : public Level
{
public:
    Level_client();
    void zacetek();
    void zanka();
    void konec();

private:
    asio::io_context m_io_kontekst;
    asio::ip::udp::resolver m_razresevalnik;
    asio::ip::udp::endpoint m_koncna_tocka;
    asio::ip::udp::socket m_vticnik;

    bool m_sem_povezan;
    bool m_sem_zacel;
    Objekt_vegovec2 m_vegovec2;
    bool m_imam_ip;
    std::string m_ip_streznika;
    double m_kdaj_zelim_vegovec_poz;
    double m_kdaj_zelim_crnce;
    double m_kdaj_zelim_smeti;
    double m_kdaj_zelim_grete;
    double m_kdaj_zelim_tocke;
};
#endif