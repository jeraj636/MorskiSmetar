#ifndef MOJI_OBJEKTI
#define MOJI_OBJEKTI

#include <henigma_engine.h>
#include <CelicniAvtomat.h>
class Objekt_smeti;
class Objekt_crnc : public Objekt_anim
{
public:
    static void init();
    void nastavi(CelicniAvtomat *zemljeveid);
    void update(std::vector<Objekt_smeti *> &smece);

private:
    static inline uint32_t m_idle_tek_id[2];
    static inline uint32_t m_hoja_tek_id[4];
    static inline uint32_t m_plavanje_tek_id[2];
    CelicniAvtomat *m_zemljevid;
    static inline float m_hitrost = 150;

private:
    mat::vec2 m_smer;
    bool m_sem_v_vodi;
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
    void konec();

private:
    static inline uint32_t m_idle_tek_id[2];
    static inline uint32_t m_hoja_tek_id[4];
    static inline uint32_t m_udarec_tek_id[10];
    static inline uint32_t m_plavanje_tek_id[2];
    static inline uint32_t m_plavanje_udraec_tek_id[10];
    static inline float m_hitrost = 200;

private:
    void premakni();

private:
    CelicniAvtomat *m_zemljevid;
    bool m_sem_v_vodi;
    mat::vec2 m_smer;
};

class Objekt_smeti : public Objekt
{
public:
    static void init();
    void nastavi(CelicniAvtomat *zemljeveid, mat::vec2 poz);
    void update();
    // static void unici();

private:
    static inline uint32_t m_smeti_tek;

private:
    static inline CelicniAvtomat *m_zemljevid;
    bool m_sem_v_vodi;
    mat::vec2 m_smer;
    static inline float m_hitrost = 90;

private:
    bool trk(char c);
    bool sem_zunaj();
    void rand_smer();
};

class Objekt_greta : public Objekt_anim
{
public:
    static void init();
    void nastavi(CelicniAvtomat *zemljeveid, std::vector<Objekt_smeti *> &smece);
    void update(std::vector<Objekt_smeti *> &smece, int &tocke);

private:
    static inline uint32_t m_idle_tek_id[2];
    static inline uint32_t m_hoja_tek_id[4];
    static inline uint32_t m_plavanje_tek_id[2];
    CelicniAvtomat *m_zemljevid;
    static inline float m_hitrost = 300;

private:
    mat::vec2 m_smer;
    bool m_sem_v_vodi;
    int m_trenutna_smet;

private:
    void nastavi_smer(Objekt_smeti *t);
    bool sem_zunaj();
};

#endif