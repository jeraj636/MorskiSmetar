#ifndef MOJI_OBJEKTI
#define MOJI_OBJEKTI

#include <henigma_engine.h>
#include <CelicniAvtomat.h>
class Objekt_crnc : public Objekt_anim
{
public:
private:
};

class Objekt_vegovec : public Objekt_anim
{
public:
    static void init();
    void nastavi();

private:
    static inline uint32_t m_idle_tek_id[2];
    static inline uint32_t m_hoja_tek_id[4];
    static inline uint32_t m_udarec_tek_id[10];
};

class Objekt_ladja : public Objekt
{
public:
    static void init();
    void nastavi(CelicniAvtomat *zemljevid);
    void update();

private:
    static inline uint32_t m_ladja_tek_id;
    CelicniAvtomat *m_zemljevid;

private:
    bool trk(char c);
};

#endif