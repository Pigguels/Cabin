#pragma once
#include "Maths/Maths.h"

// WARNING I HAVE YET TO PROPERLY TEST THIS CLASS- BE WARNED
// yeah i need to redo my matrix classes

struct Mat3
{
    float m[9];

    Mat3()
    {
        m[0] = 1; m[3] = 0; m[6] = 0;
        m[1] = 0; m[4] = 1; m[7] = 0;
        m[2] = 0; m[5] = 0; m[8] = 1;
    }

    Mat3(float m1, float m2, float m3,
        float m4, float m5, float m6,
        float m7, float m8, float m9)
    {
        m[0] = m1; m[1] = m2; m[2] = m3;
        m[3] = m4; m[4] = m5; m[5] = m6;
        m[6] = m7; m[7] = m8; m[8] = m9;
    }

    Mat3(const Mat3& _m)
    {
        m[0] = _m.m[0]; m[1] = _m.m[1]; m[2] = _m.m[2];
        m[3] = _m.m[3]; m[4] = _m.m[4]; m[5] = _m.m[5];
        m[6] = _m.m[6]; m[7] = _m.m[7]; m[8] = _m.m[8];
    }

    //void Translate(float x, float y)
    //{
    //    m[6] += x;
    //    m[7] += y;
    //}
    //
    //void RotateX(float angle)
    //{
    //    const float angleSin = Maths::Sin(angle);
    //    const float angleCos = Maths::Cos(angle);
    //    m[4] += angleCos; m[5] += angleSin;
    //    m[7] += -angleSin; m[8] += angleCos;
    //}
    //
    //void RotateY(float angle)
    //{
    //    const float angleSin = Maths::Sin(angle);
    //    const float angleCos = Maths::Cos(angle);
    //    m[0] += angleCos; m[2] += -angleSin;
    //    m[6] += angleSin; m[8] += angleCos;
    //}
    //
    //void RotateZ(float angle)
    //{
    //    const float angleSin = Maths::Sin(angle);
    //    const float angleCos = Maths::Cos(angle);
    //    m[0] += angleCos; m[1] += angleSin;
    //    m[3] += -angleSin; m[4] += angleCos;
    //}

    Mat3 operator*(Mat3 that) const
    {
        return Mat3(
            m[0] * that.m[0] + m[1] * that.m[3] + m[2] * that.m[6], m[0] * that.m[1] + m[1] * that.m[4] + m[2] * that.m[7], m[0] * that.m[2] + m[1] * that.m[5] + m[2] * that.m[8],
            m[3] * that.m[0] + m[4] * that.m[3] + m[5] * that.m[6], m[3] * that.m[1] + m[4] * that.m[4] + m[5] * that.m[7], m[3] * that.m[2] + m[4] * that.m[5] + m[5] * that.m[8],
            m[6] * that.m[0] + m[7] * that.m[3] + m[8] * that.m[6], m[6] * that.m[1] + m[7] * that.m[4] + m[8] * that.m[7], m[6] * that.m[2] + m[7] * that.m[5] + m[8] * that.m[8]
        );
    }
};
