#ifndef MOJI_OBJEKTI
#define MOJI_OBJEKTI

#include <henigma_engine.h>
#include <CelicniAvtomat.h>
// #include "level_client.h"
// #include "level_streznik.h"

class Objekt_smeti;
class Objekt_jasek;
class Objekt_cekin;
class Objekt_jud;
class Objekt_vegovec;
class Objekt_crnc : public Objekt_anim
{
public:
    static void init();
    void nastavi(CelicniAvtomat *zemljeveid);
    void update(std::vector<Objekt_smeti *> &smece, Objekt_jasek &jaski, Objekt_vegovec &vegovc);
    bool ali_zivim;
    bool sem_pokopan;
    bool sem_mocan;
    void smrt();
    void trk_s_crnim();
    friend class Level_streznik;
    friend class Level_client;
    static void unici();
    static inline bool multiplay;
    CelicniAvtomat *m_zemljevid;

private:
    static inline uint32_t m_idle_tek_id[2];
    static inline uint32_t m_hoja_tek_id[4];
    static inline uint32_t m_plavanje_tek_id[2];
    static inline float m_hitrost = 150;
    static inline uint32_t m_grob_tekstura;
    static inline uint32_t m_duh_tekstura;
    uint32_t m_mocni_ucinek_time;

protected:
    mat::vec2 m_smer;
    bool m_sem_v_vodi;
    double m_naslednji_cas;
    double m_naslednji_cas_za_smet;

private:
    void rand_smer();
};

class Objekt_vegovec : public Objekt_anim
{
public:
    static void init();
    void nastavi(CelicniAvtomat *zemljeveid);
    void update(Objekt_jasek &jaski);
    void update_o(Objekt_jasek &jaski);
    void konec();
    void udarjen();
    bool sem_lahko_udarjen();
    static void unici();

protected:
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
    double m_nazadnje_udarjen;
};

class Objekt_smeti : public Objekt
{
public:
    static void init();
    void nastavi(CelicniAvtomat *zemljeveid, mat::vec2 poz);
    void update();
    // static void unici();
    static void unici();

private:
    static inline uint32_t m_smeti_tek;

    static inline CelicniAvtomat *m_zemljevid;

    bool m_sem_v_vodi;

    static inline float m_hitrost = 90;
    friend class Level_streznik;
    friend class Level_client;

protected:
    mat::vec2 m_smer;

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
    int update(std::vector<Objekt_smeti *> &smece, int &tocke, Objekt_jasek &jasek);
    bool ali_zivim;
    bool sem_pokopan;
    void smrt();
    friend class Level_streznik;
    friend class Level_client;
    static void unici();

private:
    static inline uint32_t m_idle_tek_id[2];
    static inline uint32_t m_hoja_tek_id[4];
    static inline uint32_t m_plavanje_tek_id[2];
    CelicniAvtomat *m_zemljevid;
    static inline float m_hitrost = 140;
    static inline uint32_t m_grob_tekstura;
    static inline uint32_t m_duh_tekstura;

protected:
    mat::vec2 m_smer;
    bool m_sem_v_vodi;
    int m_trenutna_smet;
    double m_next_time;

private:
    void nastavi_smer(Objekt_smeti *t);
    bool sem_zunaj();
    void rand_smer();
};

class Objekt_jasek : public Objekt
{
public:
    void nastavi();
    static void init();
    void naredi_juda(std::vector<Objekt_jud *> &judi, CelicniAvtomat *zemljevid);
    static void unici();

private:
    uint32_t m_nex_time;
    inline static uint32_t m_tek_id;

private:
    void rand_time();
};

class Objekt_jud : public Objekt_anim
{
public:
    static void init();
    void nastavi(CelicniAvtomat *zemljeveid, const mat::vec2 &poz);
    void update(Objekt_jasek &jasek, std::vector<Objekt_cekin *> &cekini);
    bool ali_zivim;
    bool sem_pokopan;
    void smrt();
    bool sem_lahko_ubit();
    friend class Level_streznik;
    friend class Level_client;
    static void unici();

private:
    static inline uint32_t m_idle_tek_id[2];
    static inline uint32_t m_hoja_tek_id[4];
    static inline uint32_t m_plavanje_tek_id[2];
    CelicniAvtomat *m_zemljevid;
    static inline float m_hitrost = 150;
    static inline uint32_t m_grob_tekstura;
    static inline uint32_t m_duh_tekstura;

    bool m_sem_v_vodi;

protected:
    mat::vec2 m_smer;
    double m_naslednji_cas;
    uint32_t kdaj_sem_lahko_ubit;

private:
    void rand_smer();
};

class Objekt_cekin : public Objekt
{
public:
    static void init();
    void nastavi(const mat::vec2 &poz);
    double ttl;
    static void unici();

private:
    inline static uint32_t m_tek_id;
};
class Objekt_vegovec2 : public Objekt_anim
{
public:
    static void init();
    void nastavi(CelicniAvtomat *zemljeveid);
    void update(Objekt_jasek &jaski);
    void update_o(Objekt_jasek &jaski);
    void konec();
    void udarjen();
    bool sem_lahko_udarjen();
    static void unici();

protected:
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
    double m_nazadnje_udarjen;
};
#endif