#ifndef MOJI_OBJEKTI
#define MOJI_OBJEKTI

#include <henigma_engine.h>
#include <CelicniAvtomat.h>
class Objekt_crnc : public Objekt_anim
{
public:
    static void init();
    void nastavi(CelicniAvtomat *zemljeveid);
    void update();

private:
    static inline uint32_t m_idle_tek_id[2];
    static inline uint32_t m_hoja_tek_id[4];
    static inline uint32_t m_plavanje_tek_id[2];
    CelicniAvtomat *m_zemljevid;
    static inline float m_hitrost = 90;

private:
    mat::vec2 m_smer;
    double m_naslednji_cas;

private:
    void rand_smer();
};

class Objekt_vegovec : public Objekt_anim
{
public:
    static void init();
    void nastavi(CelicniAvtomat *zemljeveid);
    void update();

private:
    static inline uint32_t m_idle_tek_id[2];
    static inline uint32_t m_hoja_tek_id[4];
    static inline uint32_t m_udarec_tek_id[10];
    static inline uint32_t m_plavanje_tek_id[2];
    static inline uint32_t m_plavanje_udraec_tek_id[10];
    static inline float m_hitrost;

private:
    void premakni();

private:
    CelicniAvtomat *m_zemljevid;
    bool m_sem_v_vodi;
    mat::vec2 m_smer;
};

#endif