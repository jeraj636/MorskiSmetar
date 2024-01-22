#ifndef LEVEL_H
#define LEVEL_H
#include <henigma_engine.h>
#include <CelicniAvtomat.h>
class Level : public Scena
{
public:
    void zacetek() override;
    void zanka() override;
    void konec() override;

private:
};

#endif