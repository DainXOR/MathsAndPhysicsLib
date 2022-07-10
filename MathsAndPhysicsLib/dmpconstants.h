#pragma once

#include "dmptas.h"

#include "general_utilities.h"

_DMP_BEGIN

namespace dmconsts {

    constexpr double        pi  = 3.14159265358979323846264338327950288;
    constexpr double        e   = 2.71828182845904523536028747135266249;
    constexpr double        phi = 1.61803398874989484820458683436563811;
    constexpr dmt::complex  i   = { 0, 1 };
        
}

namespace dmcasts {
    inline double DegToRad(const double& degrees) noexcept { return (degrees * dmconsts::pi) / 180; }
    inline double RadToDeg(const double& radians) noexcept { return (radians * 180) / dmconsts::pi; }
}

namespace dpvars {
    constexpr float earthGravity = 9.81f;                               /* m/s^2*/;
    constexpr float airDensity = 1.21f;                                 /* Kg/m^3 15°C  - 1 Atm*/;
    constexpr float waterDensity = 1000.0f;                             /* Kg/m^3 15°C  - 1 Atm*/;
}

namespace dpconsts {
    constexpr const double gravity = 6.674E-11;
    constexpr const double gammaOneHalf = 1.772453;
}

namespace dpfuncts {
    inline double ObjectGravity(long long int mass) noexcept { return mass * dpconsts::gravity; }
}



//constexpr int G = Gravity(12);
_DMP_END