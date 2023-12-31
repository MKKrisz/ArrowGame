#include "gcfg.h"
#include "../debugmalloc.h"
#include "bullet.h"

Gcfg gcfg_Defaults(){
    return (Gcfg){
        .Values = {
            {SINGLE, 2},
            {DOUBLE, 150, 300},
            {DOUBLE, 10, 15},
            {DOUBLE, 0.2f, 0.5f},
            {DOUBLE, 100, 350},
            {SINGLE, BULLETTYPE_LENGTH},
            {DOUBLE, 0.1f, 3},
            {DOUBLE, 10, 1200},
            {DOUBLE, 0, 1.5},
            {DOUBLE, 0, 0.5},
            {DOUBLE, 0, 1},
            {DOUBLE, 11, 1000}
        }
    };
}
Gcfg gcfg_Load(const char* path){
    FILE* f = fopen(path, "r");
    Gcfg ret;
    int n;
    if(f == NULL) {
        ret = gcfg_Defaults();
        gcfg_Save(path, &ret);
        return ret;
    }
    for(int i = 0; i<GCFG_COUNT; i++){
        n = fscanf(f, "%f-%f\n", &ret.Values[i].min, &ret.Values[i].max);
        ret.Values[i].type = n;
    }
    fclose(f);
    return ret;
}
void gcfg_Save(const char* path, Gcfg* cfg){
    FILE* f = fopen(path, "w");
    for(int i = 0; i<GCFG_COUNT; i++){
        if (cfg->Values[i].type == SINGLE) fprintf(f, "%f\n", cfg->Values[i].min);
        else fprintf(f, "%f-%f\n", cfg->Values[i].min, cfg->Values[i].max);
    }
    fclose(f);
}
