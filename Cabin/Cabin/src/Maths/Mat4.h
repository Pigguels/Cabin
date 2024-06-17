#pragma once
#include "Maths/Maths.h"
#include "Maths/Vec3.h"

struct Mat4
{
    float m[16];

    Mat4()
    {
        m[0] = 0.0f;  m[1] = 0.0f; m[2] = 0.0f; m[3] = 0.0f;
        m[4] = 0.0f;  m[5] = 0.0f; m[6] = 0.0f; m[7] = 0.0f;
        m[8] = 0.0f;  m[9] = 0.0f; m[10] = 0.0f; m[11] = 0.0f;
        m[12] = 0.0f;  m[13] = 0.0f; m[14] = 0.0f; m[15] = 0.0f;
    }

    Mat4(float m1, float m2, float m3, float m4,
        float m5, float m6, float m7, float m8,
        float m9, float m10, float m11, float m12,
        float m13, float m14, float m15, float m16)
    {
        m[0] = m1; m[1] = m2; m[2] = m3; m[3] = m4;
        m[4] = m5; m[5] = m6; m[6] = m7; m[7] = m8;
        m[8] = m9; m[9] = m10; m[10] = m11; m[11] = m12;
        m[12] = m13; m[13] = m14; m[14] = m15; m[15] = m16;
    }

    Mat4(const Mat4& _m)
    {
        m[0] = _m.m[0]; m[1] = _m.m[1]; m[2] = _m.m[2]; m[3] = _m.m[3];
        m[4] = _m.m[4]; m[5] = _m.m[5]; m[6] = _m.m[6]; m[7] = _m.m[7];
        m[8] = _m.m[8]; m[9] = _m.m[9]; m[10] = _m.m[10]; m[11] = _m.m[11];
        m[12] = _m.m[12]; m[13] = _m.m[13]; m[14] = _m.m[14]; m[15] = _m.m[15];
    }

    //void Translate(const Vec3& translation)
    //{
    //    m[12] += translation.x;
    //    m[13] += translation.y;
    //    m[14] += translation.z;
    //}
    //
    //void SetRotateX(float angle)
    //{
    //    const float angleSin = Maths::Sin(angle);
    //    const float angleCos = Maths::Cos(angle);
    //    m[5] = angleCos; m[6] = angleSin;
    //    m[9] = -angleSin; m[10] = angleCos;
    //}
    //
    //void SetRotateY(float angle)
    //{
    //    const float angleSin = Maths::Sin(angle);
    //    const float angleCos = Maths::Cos(angle);
    //    m[0] = angleCos; m[2] = -angleSin;
    //    m[8] = angleSin; m[10] = angleCos;
    //}
    //
    //void SetRotateZ(float angle)
    //{
    //    const float angleSin = Maths::Sin(angle);
    //    const float angleCos = Maths::Cos(angle);
    //    m[0] = angleCos; m[1] = angleSin;
    //    m[4] = -angleSin; m[5] = angleCos;
    //}
    //
    //void SetScale(const Vec3& scale)
    //{
    //    m[0] = scale.x;
    //    m[5] = scale.y;
    //    m[10] = scale.z;
    //}

    Mat4 operator*(Mat4 that) const
    {
        return Mat4(
            m[0] * that.m[0] + m[4] * that.m[1] + m[8] * that.m[2] + m[12] * that.m[3],
            m[1] * that.m[0] + m[5] * that.m[1] + m[9] * that.m[2] + m[13] * that.m[3],
            m[2] * that.m[0] + m[6] * that.m[1] + m[10] * that.m[2] + m[14] * that.m[3],
            m[3] * that.m[0] + m[7] * that.m[1] + m[11] * that.m[2] + m[15] * that.m[3],

            m[0] * that.m[4] + m[4] * that.m[5] + m[8] * that.m[6] + m[12] * that.m[7],
            m[1] * that.m[4] + m[5] * that.m[5] + m[9] * that.m[6] + m[13] * that.m[7],
            m[2] * that.m[4] + m[6] * that.m[5] + m[10] * that.m[6] + m[14] * that.m[7],
            m[3] * that.m[4] + m[7] * that.m[5] + m[11] * that.m[6] + m[15] * that.m[7],

            m[0] * that.m[8] + m[4] * that.m[9] + m[8] * that.m[10] + m[12] * that.m[11],
            m[1] * that.m[8] + m[5] * that.m[9] + m[9] * that.m[10] + m[13] * that.m[11],
            m[2] * that.m[8] + m[6] * that.m[9] + m[10] * that.m[10] + m[14] * that.m[11],
            m[3] * that.m[8] + m[7] * that.m[9] + m[11] * that.m[10] + m[15] * that.m[11],

            m[0] * that.m[12] + m[4] * that.m[13] + m[8] * that.m[14] + m[12] * that.m[15],
            m[1] * that.m[12] + m[5] * that.m[13] + m[9] * that.m[14] + m[13] * that.m[15],
            m[2] * that.m[12] + m[6] * that.m[13] + m[10] * that.m[14] + m[14] * that.m[15],
            m[3] * that.m[12] + m[7] * that.m[13] + m[11] * that.m[14] + m[15] * that.m[15]
        );
    }

    static Mat4 Identity()
    {
        return Mat4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    static Mat4 Translation(const Vec3& translation)
    {
        Mat4 res = Identity();
        res.m[12] = translation.x;
        res.m[13] = translation.y;
        res.m[14] = translation.z;
        return res;
    }
    static Mat4 Translation(const Mat4& m, const Vec3& translation)
    {
        Mat4 tran = Translation(translation);
        return m * tran;
    }

    static Mat4 Rotation(const Vec3& axis, float angle)
    {
        const float c = Maths::Cos(angle);
        const float s = Maths::Sin(angle);
        const float onenc = 1.0f - c;
        const Vec3 naxis = axis.GetNormalised();
        const Vec3 temp = axis * (1.0f - c);

        Mat4 res = Mat4();

        res.m[0] = c + temp.x * naxis.x;
        res.m[1] = temp.x * naxis.y + s * naxis.z;
        res.m[2] = temp.x * naxis.z - s * naxis.y;
        res.m[3] = 0.0f;

        res.m[4] = temp.y * naxis.x - s * naxis.z;
        res.m[5] = c + temp.y * naxis.y;
        res.m[6] = temp.y * naxis.z + s * naxis.x;
        res.m[7] = 0.0f;

        res.m[8] = temp.z * naxis.x + s * naxis.y;
        res.m[9] = temp.z * naxis.y - s * naxis.x;
        res.m[10] = c + temp.z * naxis.z;
        res.m[11] = 0.0f;

        res.m[12] = 0.0f;
        res.m[13] = 0.0f;
        res.m[14] = 0.0f;
        res.m[15] = 1.0f;

        return res;
    }
    static Mat4 Rotation(const Mat4& m, const Vec3& axis, float angle)
    {
        Mat4 rot = Rotation(axis, angle);
        return m * rot;
    }

    static Mat4 Scale(const Vec3& scale)
    {
        Mat4 res = Identity();
        res.m[0] = scale.x;
        res.m[5] = scale.y;
        res.m[10] = scale.z;
        return res;
    }
    static Mat4 Scale(const Mat4& m, const Vec3& scale)
    {
        Mat4 res = Mat4(m);
        res.m[0] *= scale.x;
        res.m[5] *= scale.y;
        res.m[10] *= scale.z;
        return res;
    }

    static Mat4 Ortho(float left, float right, float top, float bottom, float nearClip, float farClip)
    {
        const float horizRange = right - left;
        const float vertiRange = top - bottom;
        const float clipRange = farClip - nearClip;
        Mat4 ortho = Identity();
        ortho.m[0] = 2.0f / horizRange;
        ortho.m[5] = 2.0f / vertiRange;
        ortho.m[10] = -2.0f / clipRange;
        ortho.m[12] = -(left + right) / horizRange;
        ortho.m[13] = -(top + bottom) / vertiRange;
        ortho.m[14] = -(nearClip + farClip) / clipRange;
        return ortho;
    }

    static Mat4 Perspective(float fovY, float aspect, float nearClip, float farClip)
    {
        const float halfTanFov = Maths::Tan(fovY * 0.5f);
        const float clipRange = farClip - nearClip;
        Mat4 persp = Mat4();
        persp.m[0] = 1.0f / (aspect * halfTanFov);
        persp.m[5] = 1.0f / halfTanFov;
        persp.m[10] = -(nearClip + farClip) / clipRange;
        persp.m[11] = -1.0f;
        persp.m[14] = -(2.0f * farClip * nearClip) / clipRange;
        return persp;
    }

    static Mat4 LookAt(const Vec3& fromPoint, const Vec3& focusPoint, const Vec3& up)
    {
        const Vec3 forward = Vec3(focusPoint - fromPoint).GetNormalised();
        const Vec3 horiz = Vec3::Cross(forward, up).GetNormalised();
        const Vec3 newUp = Vec3::Cross(horiz, forward);
        Mat4 view = Identity();
        view.m[0] = horiz.x;
        view.m[4] = horiz.y;
        view.m[8] = horiz.z;
        view.m[1] = newUp.x;
        view.m[5] = newUp.y;
        view.m[9] = newUp.z;
        view.m[2] = -forward.x;
        view.m[6] = -forward.y;
        view.m[10] = -forward.z;
        view.m[12] = -Vec3::Dot(horiz, fromPoint);
        view.m[13] = -Vec3::Dot(newUp, fromPoint);
        view.m[14] = Vec3::Dot(forward, fromPoint);
        return view;
    }
};
