#include <henigma_engine.h>

#include "../include/zacetna.h"
#include "../include/level.h"
#include "../include/level_streznik.h"
#include "../include/level_client.h"
#include "../include/replay.h"
int main()
{
    Risalnik::init("Morski smetar");

    Risalnik::barva_odzadja = 0x0000ffff;
    Risalnik::sredstva_pot = "../sredstva";

    Objekt_vegovec2::init();
    Objekt_vegovec::init();
    Objekt_crnc::init();
    Objekt_smeti::init();
    Objekt_greta::init();
    Objekt_jasek::init();
    Objekt_jud::init();
    Objekt_cekin::init();

    Muzika::init();

    Level level;
    Level_streznik s_level;
    Level_client c_level;
    Replay replay;
    Zacetna zacetna(&level, &c_level, &s_level, &replay);
    zacetna.zacetek();

    replay.zacetna = &zacetna;
    level.zacetna = &zacetna;
    s_level.zacetna = &zacetna;
    c_level.zacetna = &zacetna;

    Risalnik::aktivna_scena = &zacetna;

    while (!Risalnik::ali_se_moram_zapreti())
    {
        Risalnik::zacetek_okvir();
        Risalnik::aktivna_scena->zanka();
        Risalnik::konec_okvir();
    }

    Objekt_vegovec2::unici();
    Objekt_vegovec::unici();
    Objekt_crnc::unici();
    Objekt_smeti::unici();
    Objekt_greta::unici();
    Objekt_jasek::unici();
    Objekt_jud::unici();
    Objekt_cekin::unici();
    Risalnik::konec();
}
