#ifndef LEVEL_STREZNIK
#define LEVEL_STREZNIK
#include <thread>
#include "level.h"
#include "../include/zacetna.h"
#define ASIO_STANDALONE
#define ASIO_HAS_STD_ADDRESSOF
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_TYPE_TRAITS
#include <asio.hpp>
class Level_streznik : public Level
{
public:
    Level_streznik();
    void zacetek();
    void zanka();
    void konec();

private:
    asio::io_context m_io_kontekst;
    asio::ip::udp::socket m_vticnik;
    asio::ip::udp::endpoint m_koncna_tocka;
    bool m_sem_povezan;
    bool m_sem_zacel;
    double m_kdaj_zelim_vegovec_poz;
    Objekt_vegovec2 m_vegovec2;
};
#endif
