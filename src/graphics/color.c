#include "color.h"
#include "../control/random.h"

sRGB CreateColor(float r, float g, float b, float a){
    return (sRGB){.r = r, .g = g, .b = b, .alpha = a};
}

sRGB FromSDL_Color(SDL_Color c){
    return (sRGB){.r = c.r / 255.0f, .g = c.g / 255.0f, .b = c.b/255.0f, .alpha = c.a / 255.0f};
}

SDL_Color ToSDL_Color(sRGB c){
    return (SDL_Color){.r = (Uint8)(c.r*255), .g = (Uint8)(c.g*255), .b = (Uint8)(c.b*255), .a = (Uint8)(c.alpha*255)};
}

OKLab ToOKLab(sRGB c)
{
    float l = 0.4122214708f * c.r + 0.5363325363f * c.g + 0.0514459929f * c.b;
    float m = 0.2119034982f * c.r + 0.6806995451f * c.g + 0.1073969566f * c.b;
    float s = 0.0883024619f * c.r + 0.2817188376f * c.g + 0.6299787005f * c.b;

    float l_ = cbrtf(l);
    float m_ = cbrtf(m);
    float s_ = cbrtf(s);

    return (OKLab){
            .r = 0.2104542553f*l_ + 0.7936177850f*m_ - 0.0040720468f*s_,
            .g = 1.9779984951f*l_ - 2.4285922050f*m_ + 0.4505937099f*s_,
            .b = 0.0259040371f*l_ + 0.7827717662f*m_ - 0.8086757660f*s_,
    };
}
sRGB TosRGB(OKLab c)
{
    float l_ = c.L + 0.3963377774f * c.a + 0.2158037573f * c.b;
    float m_ = c.L - 0.1055613458f * c.a - 0.0638541728f * c.b;
    float s_ = c.L - 0.0894841775f * c.a - 1.2914855480f * c.b;

    float l = l_*l_*l_;
    float m = m_*m_*m_;
    float s = s_*s_*s_;

    return (sRGB){
            .r = +4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
            .g = -1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
            .b = -0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    };
}

OKLab* GenerateMonochromePalette(int count){
    OKLab*  output = malloc(sizeof(OKLab) * count);
    float baseLuminance = RandomFR(0.0f, 0.2f);
    float baseA = RandomFR(-1.0f, 1.0f);
    float baseB = RandomFR(-1.0f, 1.0f);
    float increment = RandomFR(0.0f, 0.8f)/(float)count;

    for(int i = 0; i<count; i++){
        output[i] = (OKLab){.L = baseLuminance + i*increment, .a = baseA, .b = baseB, .alpha = 255};
    }
    return output;
}

SDL_Color* GeneratePaletteM(int count){
    OKLab* OKPalette = GenerateMonochromePalette(count);
    SDL_Color* rop = malloc(sizeof(SDL_Color) * count);
    for(int i = 0; i<count; i++){
        rop[i] = ToSDL_Color(TosRGB(OKPalette[i]));
    }
    free(OKPalette);
    return rop;
}
