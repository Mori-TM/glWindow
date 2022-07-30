#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define GL_COLOR_32(R,G,B,A) (((unsigned int)(A)<<24) | ((unsigned int)(B)<<16) | ((unsigned int)(G)<<8) | ((unsigned int)(R)<<0))
#define GL_COLOR_24(R,G,B) (((unsigned int)(255)<<24) | ((unsigned int)(B)<<16) | ((unsigned int)(G)<<8) | ((unsigned int)(R)<<0))
#define GL_BYTE_FLOAT 0.003921568627451

#define gltrue 1
#define glfalse 0
typedef int glbool;

//vector
typedef struct
{
	float x;
	float y;
} glVec2;

typedef struct
{
	float x;
	float y;
	float z;
} glVec3;

typedef struct
{
	float x;
	float y;
	float z;
	float w;
} glVec4;

float glFastInverseSqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5f;

	x2 = number * 0.5f;
	y = number;
	i = *(long*)&y;              // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);   // what the fuck? 
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));   // 1st iteration
	y = y * (threehalfs - (x2 * y * y));   // 2nd iteration, this can be removed - it's for more accuracy

	return y;
}

glVec2 glNormalize2(glVec2 v)
{
	register float length = glFastInverseSqrt(v.x * v.x + v.y * v.y);
	v.x *= length;
	v.y *= length;
	return v;
}

glVec3 glNormalize3(glVec3 v)
{
	register float length = glFastInverseSqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x *= length;
	v.y *= length;
	v.z *= length;
	return v;
}

glVec4 glNormalize4(glVec4 v)
{
	register float length = glFastInverseSqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	v.x *= length;
	v.y *= length;
	v.z *= length;
	v.w *= length;
	return v;
}

void glNormalize2P(glVec2* v)
{
	register float length = glFastInverseSqrt(v->x * v->x + v->y * v->y);
	v->x *= length;
	v->y *= length;
}

void glNormalize3P(glVec3* v)
{
	register float length = glFastInverseSqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x *= length;
	v->y *= length;
	v->z *= length;
}

void glNormalize4P(glVec4* v)
{
	register float length = glFastInverseSqrt(v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w);
	v->x *= length;
	v->y *= length;
	v->z *= length;
	v->w *= length;
}

extern inline glVec3 glCross3P(glVec3* a, glVec3* b)
{
	glVec3 r;
	r.x = a->y * b->z - a->z * b->y;
	r.y = a->z * b->x - a->x * b->z;
	r.z = a->x * b->y - a->y * b->x;
	return r;
}

extern inline float glDot2P(glVec2* a, glVec2* b)
{
	return a->x * b->x + a->y * b->y;
}

extern inline float glDot3P(glVec3* a, glVec3* b)
{
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

extern inline glVec2 glAdd2P(glVec2* a, glVec2* b)
{
	glVec2 r;
	r.x = a->x + b->x;
	r.y = a->y + b->y;
	return r;
}

extern inline glVec2 glSub2P(glVec2* a, glVec2* b)
{
	glVec2 r;
	r.x = a->x - b->x;
	r.y = a->y - b->y;
	return r;
}

extern inline glVec2 glMul2P(glVec2* a, glVec2* b)
{
	glVec2 r;
	r.x = a->x * b->x;
	r.y = a->y * b->y;
	return r;
}

extern inline glVec2 glDiv2P(glVec2* a, glVec2* b)
{
	glVec2 r;
	r.x = a->x / b->x;
	r.y = a->y / b->y;
	return r;
}

extern inline glVec3 glAdd3P(glVec3* a, glVec3* b)
{
	glVec3 r;
	r.x = a->x + b->x;
	r.y = a->y + b->y;
	r.z = a->z + b->z;
	return r;
}

extern inline glVec3 glSub3P(glVec3* a, glVec3* b)
{
	glVec3 r;
	r.x = a->x - b->x;
	r.y = a->y - b->y;
	r.z = a->z - b->z;
	return r;
}

extern inline glVec3 glMul3P(glVec3* a, glVec3* b)
{
	glVec3 r;
	r.x = a->x * b->x;
	r.y = a->y * b->y;
	r.z = a->z * b->z;
	return r;
}

extern inline glVec3 glDiv3P(glVec3* a, glVec3* b)
{
	glVec3 r;
	r.x = a->x / b->x;
	r.y = a->y / b->y;
	r.z = a->z / b->z;
	return r;
}

extern inline glVec4 glAdd4P(glVec4* a, glVec4* b)
{
	glVec4 r;
	r.x = a->x + b->x;
	r.y = a->y + b->y;
	r.z = a->z + b->z;
	r.w = a->w + b->w;
	return r;
}

extern inline glVec4 glSub4P(glVec4* a, glVec4* b)
{
	glVec4 r;
	r.x = a->x - b->x;
	r.y = a->y - b->y;
	r.z = a->z - b->z;
	r.w = a->w - b->w;
	return r;
}

extern inline glVec4 glMul4P(glVec4* a, glVec4* b)
{
	glVec4 r;
	r.x = a->x * b->x;
	r.y = a->y * b->y;
	r.z = a->z * b->z;
	r.w = a->w * b->w;
	return r;
}

extern inline glVec4 glDiv4P(glVec4* a, glVec4* b)
{
	glVec4 r;
	r.x = a->x / b->x;
	r.y = a->y / b->y;
	r.z = a->z / b->z;
	r.w = a->w / b->w;
	return r;
}


extern inline glVec3 glCross3(glVec3 a, glVec3 b)
{
	glVec3 r;
	r.x = a.y * b.z - a.z * b.y;
	r.y = a.z * b.x - a.x * b.z;
	r.z = a.x * b.y - a.y * b.x;
	return r;
}

extern inline float glDot2(glVec2 a, glVec2 b)
{
	return a.x * b.x + a.y * b.y;
}

extern inline float glDot3(glVec3 a, glVec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

extern inline glVec2 glAdd2(glVec2 a, glVec2 b)
{
	glVec2 r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return r;
}

extern inline glVec2 glSub2(glVec2 a, glVec2 b)
{
	glVec2 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	return r;
}

extern inline glVec2 glMul2(glVec2 a, glVec2 b)
{
	glVec2 r;
	r.x = a.x * b.x;
	r.y = a.y * b.y;
	return r;
}

extern inline glVec2 glDiv2(glVec2 a, glVec2 b)
{
	glVec2 r;
	r.x = a.x / b.x;
	r.y = a.y / b.y;
	return r;
}

extern inline glVec3 glAdd3(glVec3 a, glVec3 b)
{
	glVec3 r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;
	return r;
}

extern inline glVec3 glSub3(glVec3 a, glVec3 b)
{
	glVec3 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	return r;
}

extern inline glVec3 glMul3(glVec3 a, glVec3 b)
{
	glVec3 r;
	r.x = a.x * b.x;
	r.y = a.y * b.y;
	r.z = a.z * b.z;
	return r;
}

extern inline glVec3 glDiv3(glVec3 a, glVec3 b)
{
	glVec3 r;
	r.x = a.x / b.x;
	r.y = a.y / b.y;
	r.z = a.z / b.z;
	return r;
}

extern inline glVec4 glAdd4(glVec4 a, glVec4 b)
{
	glVec4 r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;
	r.w = a.w + b.w;
	return r;
}

extern inline glVec4 glSub4(glVec4 a, glVec4 b)
{
	glVec4 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	r.w = a.w - b.w;
	return r;
}

extern inline glVec4 glMul4(glVec4 a, glVec4 b)
{
	glVec4 r;
	r.x = a.x * b.x;
	r.y = a.y * b.y;
	r.z = a.z * b.z;
	r.w = a.w * b.w;
	return r;
}

extern inline glVec4 glDiv4(glVec4 a, glVec4 b)
{
	glVec4 r;
	r.x = a.x / b.x;
	r.y = a.y / b.y;
	r.z = a.z / b.z;
	r.w = a.w / b.w;
	return r;
}

int glInsideViewFrustum4(glVec4* v)
{
	return fabsf(v->x) <= fabsf(v->w) &&
		   fabsf(v->y) <= fabsf(v->w) &&
		   fabsf(v->z) <= fabsf(v->w);
}

extern inline float glLength3(glVec3 v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

extern inline float glLength3P(glVec3* v)
{
	return sqrtf((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
}

extern inline glVec2 glReflect2(glVec2* v, glVec2* n)
{
	glVec2 r;
	r.x = v->x - 2 * glDot2P(v, n) * n->x;
	r.y = v->y - 2 * glDot2P(v, n) * n->y;
	return r;
}

extern inline glVec3 glReflect3(glVec3* v, glVec3* n)
{
	glVec3 r;
	r.x = v->x - 2 * glDot3P(v, n) * n->x;
	r.y = v->y - 2 * glDot3P(v, n) * n->y;
	r.z = v->z - 2 * glDot3P(v, n) * n->z;
	return r;
}

float glGetDistanceVec2(glVec2* a, glVec2* b)
{
	register float DX = a->x - b->x;
	register float DY = a->y - b->y;

	DX *= DX;
	DY *= DY;

	return sqrtf(DX + DY);
}

float glGetDistanceVec3(glVec3 a, glVec3 b)
{
	register float DX = a.x - b.x;
	register float DY = a.y - b.y;
	register float DZ = a.z - b.z;

	DX *= DX;
	DY *= DY;
	DZ *= DZ;

	return sqrtf(DX + DY + DZ);
}

float glGetDistanceVec3P(glVec3* a, glVec3* b)
{
	register float DX = a->x - b->x;
	register float DY = a->y - b->y;
	register float DZ = a->z - b->z;

	DX *= DX;
	DY *= DY;
	DZ *= DZ;

	return sqrtf(DX + DY + DZ);
}

extern inline glVec2 GLVec2(float x, float y)
{
	glVec2 r = { x, y };
	return r;
}

extern inline glVec3 GLVec3(float x, float y, float z)
{
	glVec3 r = { x, y, z };
	return r;
}

extern inline glVec4 GLVec4(float x, float y, float z, float w)
{
	glVec4 r = { x, y, z, w };
	return r;
}

extern inline glVec2 GLVec2f(float x)
{
	glVec2 r = { x, x };
	return r;
}

extern inline glVec3 GLVec3f(float x)
{
	glVec3 r = { x, x, x };
	return r;
}

extern inline glVec4 GLVec4f(float x)
{
	glVec4 r = { x, x, x, x };
	return r;
}
/*
extern inline float* GLVec2Tof(glVec2 v)
{
	return (float*)&v;
}

extern inline float* GLVec2TofP(glVec2* v)
{
	return (float*)v;
}

extern inline float* GLVec3Tof(glVec3 v)
{
	return (float*)&v;
}

extern inline float* GLVec3TofP(glVec3* v)
{
	return (float*)v;
}

extern inline float* GLVec4Tof(glVec4 v)
{
	return (float*)&v;
}

extern inline float* GLVec4TofP(glVec4* v)
{
	return (float*)v;
}
*/

extern inline glVec2 glLerp2(glVec2 a, glVec2 b, float LerpAmt)
{
	return glAdd2(glMul2(glSub2P(&b, &a), GLVec2f(LerpAmt)), a);
}

extern inline glVec2 glLerp2P(glVec2* a, glVec2* b, float LerpAmt)
{
	return glAdd2(glMul2(glSub2P(b, a), GLVec2f(LerpAmt)), *a);
}

extern inline glVec3 glLerp3(glVec3 a, glVec3 b, float LerpAmt)
{
	return glAdd3(glMul3(glSub3P(&b, &a), GLVec3f(LerpAmt)), a);
}

extern inline glVec3 glLerp3P(glVec3* a, glVec3* b, float LerpAmt)
{
	return glAdd3(glMul3(glSub3P(b, a), GLVec3f(LerpAmt)), *a);
}

extern inline glVec4 glLerp4(glVec4 a, glVec4 b, float LerpAmt)
{
	return glAdd4(glMul4(glSub4P(&b, &a), GLVec4f(LerpAmt)), a);
}

extern inline glVec4 glLerp4P(glVec4* a, glVec4* b, float LerpAmt)
{
	return glAdd4(glMul4(glSub4P(b, a), GLVec4f(LerpAmt)), *a);
}

//matrix
typedef struct
{
	float m[4][4];
} glMat4;

//fixed
void glLoadMat4IdentityP(glMat4* Matrix)
{
	Matrix->m[0][0] = 1.0;
	Matrix->m[1][0] = 0.0;
	Matrix->m[2][0] = 0.0;
	Matrix->m[3][0] = 0.0;

	Matrix->m[0][1] = 0.0;
	Matrix->m[1][1] = 1.0;
	Matrix->m[2][1] = 0.0;
	Matrix->m[3][1] = 0.0;

	Matrix->m[0][2] = 0.0;
	Matrix->m[1][2] = 0.0;
	Matrix->m[2][2] = 1.0;
	Matrix->m[3][2] = 0.0;

	Matrix->m[0][3] = 0.0;
	Matrix->m[1][3] = 0.0;
	Matrix->m[2][3] = 0.0;
	Matrix->m[3][3] = 1.0;
}

//fixed
glMat4 glLoadMat4Identity()
{
	glMat4 Matrix;
	Matrix.m[0][0] = 1.0;
	Matrix.m[1][0] = 0.0;
	Matrix.m[2][0] = 0.0;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = 0.0;
	Matrix.m[1][1] = 1.0;
	Matrix.m[2][1] = 0.0;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = 0.0;
	Matrix.m[1][2] = 0.0;
	Matrix.m[2][2] = 1.0;
	Matrix.m[3][2] = 0.0;

	Matrix.m[0][3] = 0.0;
	Matrix.m[1][3] = 0.0;
	Matrix.m[2][3] = 0.0;
	Matrix.m[3][3] = 1.0;
	return Matrix;
}

//fixed
glMat4 glInitScreenSpaceTransform(float HalfWidth, float HalfHeight)
{
	glMat4 Matrix;

	Matrix.m[0][0] = HalfWidth;
	Matrix.m[1][0] = 0.0;
	Matrix.m[2][0] = 0.0;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = 0.0;
	Matrix.m[1][1] = -HalfHeight;
	Matrix.m[2][1] = 0.0;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = 0.0;
	Matrix.m[1][2] = 0.0;
	Matrix.m[2][2] = 1.0;
	Matrix.m[3][2] = 0.0;

	Matrix.m[0][3] = HalfWidth - 0.5;
	Matrix.m[1][3] = HalfHeight - 0.5;
	Matrix.m[2][3] = 0.0;
	Matrix.m[3][3] = 1.0;

	return Matrix;
}

typedef float Vec3f[3];

inline void Add3(Vec3f Dest, Vec3f A)
{
	register float* Temp = Dest;
	register int j;
	register float Sum, Sum2;

	for (j = 0; j < 3; j++)
	{
		Sum = *A;
		A++;
		Sum2 = *Temp;
		Temp++;
		Temp[-1] = Sum + Sum2;
	}
}

//fixed
glMat4 glMultiplyMat4P(glMat4* a, glMat4* b)
{
	glMat4 r;
	//	r.m[0][0] = a->m[0][0] * b->m[0][0] + a->m[1][0] * b->m[0][1] + a->m[2][0] * b->m[0][2] + a->m[3][0] * b->m[0][3];
	//	r.m[0][1] = a->m[0][1] * b->m[0][0] + a->m[1][1] * b->m[0][1] + a->m[2][1] * b->m[0][2] + a->m[3][1] * b->m[0][3];
	//	r.m[0][2] = a->m[0][2] * b->m[0][0] + a->m[1][2] * b->m[0][1] + a->m[2][2] * b->m[0][2] + a->m[3][2] * b->m[0][3];
	//	r.m[0][3] = a->m[0][3] * b->m[0][0] + a->m[1][3] * b->m[0][1] + a->m[2][3] * b->m[0][2] + a->m[3][3] * b->m[0][3];
	//
	//	r.m[1][0] = a->m[0][0] * b->m[1][0] + a->m[1][0] * b->m[1][1] + a->m[2][0] * b->m[1][2] + a->m[3][0] * b->m[1][3];
	//	r.m[1][1] = a->m[0][1] * b->m[1][0] + a->m[1][1] * b->m[1][1] + a->m[2][1] * b->m[1][2] + a->m[3][1] * b->m[1][3];
	//	r.m[1][2] = a->m[0][2] * b->m[1][0] + a->m[1][2] * b->m[1][1] + a->m[2][2] * b->m[1][2] + a->m[3][2] * b->m[1][3];
	//	r.m[1][3] = a->m[0][3] * b->m[1][0] + a->m[1][3] * b->m[1][1] + a->m[2][3] * b->m[1][2] + a->m[3][3] * b->m[1][3];
	//
	//	r.m[2][0] = a->m[0][0] * b->m[2][0] + a->m[1][0] * b->m[2][1] + a->m[2][0] * b->m[2][2] + a->m[3][0] * b->m[2][3];
	//	r.m[2][1] = a->m[0][1] * b->m[2][0] + a->m[1][1] * b->m[2][1] + a->m[2][1] * b->m[2][2] + a->m[3][1] * b->m[2][3];
	//	r.m[2][2] = a->m[0][2] * b->m[2][0] + a->m[1][2] * b->m[2][1] + a->m[2][2] * b->m[2][2] + a->m[3][2] * b->m[2][3];
	//	r.m[2][3] = a->m[0][3] * b->m[2][0] + a->m[1][3] * b->m[2][1] + a->m[2][3] * b->m[2][2] + a->m[3][3] * b->m[2][3];
	//
	//	r.m[3][0] = a->m[0][0] * b->m[3][0] + a->m[1][0] * b->m[3][1] + a->m[2][0] * b->m[3][2] + a->m[3][0] * b->m[3][3];
	//	r.m[3][1] = a->m[0][1] * b->m[3][0] + a->m[1][1] * b->m[3][1] + a->m[2][1] * b->m[3][2] + a->m[3][1] * b->m[3][3];
	//	r.m[3][2] = a->m[0][2] * b->m[3][0] + a->m[1][2] * b->m[3][1] + a->m[2][2] * b->m[3][2] + a->m[3][2] * b->m[3][3];
	//	r.m[3][3] = a->m[0][3] * b->m[3][0] + a->m[1][3] * b->m[3][1] + a->m[2][3] * b->m[3][2] + a->m[3][3] * b->m[3][3];
	/*
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			r.m[i][j] = a->m[i][0] * b->m[0][j] +
				a->m[i][1] * b->m[1][j] +
				a->m[i][2] * b->m[2][j] +
				a->m[i][3] * b->m[3][j];
		}
	}
	*/
//	a->m[i][0] * b->m[0][j] + a->m[i][1] * b->m[1][j] + a->m[i][2] * b->m[2][j] + a->m[i][3] * b->m[3][j];
//
//	r.m[0][3] = a->m[0][3] * b->m[0][3] + a->m[0][3] * b->m[0][3] + a->m[0][3] * b->m[0][3] + a->m[0][3] * b->m[0][3];
//	r.m[1][3] = a->m[1][3] * b->m[1][3] + a->m[1][3] * b->m[1][3] + a->m[1][3] * b->m[1][3] + a->m[1][3] * b->m[1][3];
//	r.m[2][3] = a->m[2][3] * b->m[2][3] + a->m[2][3] * b->m[2][3] + a->m[2][3] * b->m[2][3] + a->m[2][3] * b->m[2][3];

//	r.m[0][3] = a->m[0][0] * b->m[0][3] + a->m[0][1] * b->m[1][3] + a->m[0][2] * b->m[2][3] + a->m[0][3] * b->m[3][3];
//	r.m[1][3] = a->m[1][0] * b->m[0][3] + a->m[1][1] * b->m[1][3] + a->m[1][2] * b->m[2][3] + a->m[1][3] * b->m[3][3];
//	r.m[2][3] = a->m[2][0] * b->m[0][3] + a->m[2][1] * b->m[1][3] + a->m[2][2] * b->m[2][3] + a->m[2][3] * b->m[3][3];
//	r.m[3][3] = a->m[3][0] * b->m[0][3] + a->m[3][1] * b->m[1][3] + a->m[3][2] * b->m[2][3] + a->m[3][3] * b->m[3][3];
	/*
	register float Entry0;
	register float Entry1;
	register float Entry2;
	register float Entry3;
	register float* Temp = (float*)a->m;
	register float* Temp2 = (float*)r.m;
	register float* Temp3;
	register int i;

	for (i = 0; i < 16; i++)
	{
		Entry0 = Temp[0];
		Entry1 = Temp[1];
		Entry2 = Temp[2];
		Entry3 = Temp[3];
		Temp3 = (float*)b->m;

		for (; (i & 3) != 3; i++)
		{
			*Temp2 = Entry0 * Temp3[0] + Entry1 * Temp3[4] + Entry2 * Temp3[8];
			Temp2++;
			Temp3++;
		}
		
		*Temp2 = Entry0 * Temp3[0] + Entry1 * Temp3[4] + Entry2 * Temp3[8] + Entry3 * Temp3[12];
		Temp += 4;
		Temp2++;
	}

	Add3((float*)&r.m[3][0], (float*)&b->m[3][0]);
	*/
	r.m[0][0] = a->m[0][0] * b->m[0][0] + a->m[0][1] * b->m[1][0] + a->m[0][2] * b->m[2][0];
	r.m[1][0] = a->m[1][0] * b->m[0][0] + a->m[1][1] * b->m[1][0] + a->m[1][2] * b->m[2][0];
	r.m[2][0] = a->m[2][0] * b->m[0][0] + a->m[2][1] * b->m[1][0] + a->m[2][2] * b->m[2][0];
	r.m[3][0] = a->m[3][0] * b->m[0][0] + a->m[3][1] * b->m[1][0] + a->m[3][2] * b->m[2][0];

	r.m[0][1] = a->m[0][0] * b->m[0][1] + a->m[0][1] * b->m[1][1] + a->m[0][2] * b->m[2][1];
	r.m[1][1] = a->m[1][0] * b->m[0][1] + a->m[1][1] * b->m[1][1] + a->m[1][2] * b->m[2][1];
	r.m[2][1] = a->m[2][0] * b->m[0][1] + a->m[2][1] * b->m[1][1] + a->m[2][2] * b->m[2][1];
	r.m[3][1] = a->m[3][0] * b->m[0][1] + a->m[3][1] * b->m[1][1] + a->m[3][2] * b->m[2][1];

	r.m[0][2] = a->m[0][0] * b->m[0][2] + a->m[0][1] * b->m[1][2] + a->m[0][2] * b->m[2][2];
	r.m[1][2] = a->m[1][0] * b->m[0][2] + a->m[1][1] * b->m[1][2] + a->m[1][2] * b->m[2][2];
	r.m[2][2] = a->m[2][0] * b->m[0][2] + a->m[2][1] * b->m[1][2] + a->m[2][2] * b->m[2][2];
	r.m[3][2] = a->m[3][0] * b->m[0][2] + a->m[3][1] * b->m[1][2] + a->m[3][2] * b->m[2][2];

	r.m[0][3] = a->m[0][0] * b->m[0][3] + a->m[0][1] * b->m[1][3] + a->m[0][2] * b->m[2][3] + a->m[0][3] * b->m[3][3];
	r.m[1][3] = a->m[1][0] * b->m[0][3] + a->m[1][1] * b->m[1][3] + a->m[1][2] * b->m[2][3] + a->m[1][3] * b->m[3][3];
	r.m[2][3] = a->m[2][0] * b->m[0][3] + a->m[2][1] * b->m[1][3] + a->m[2][2] * b->m[2][3] + a->m[2][3] * b->m[3][3];
	r.m[3][3] = a->m[3][0] * b->m[0][3] + a->m[3][1] * b->m[1][3] + a->m[3][2] * b->m[2][3] + a->m[3][3] * b->m[3][3];
	glAdd3P((glVec3*)&r.m[3][0], (glVec3*)&b->m[3][0]);
//	Add3((float*)&r.m[3][0], (float*)&b->m[3][0]);

	return r;
}

//fixed
glMat4 glMultiplyMat4(glMat4 a, glMat4 b)
{
	glMat4 r;

	//	r.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[1][0] * b.m[0][1] + a.m[2][0] * b.m[0][2] + a.m[3][0] * b.m[0][3];
	//	r.m[0][1] = a.m[0][1] * b.m[0][0] + a.m[1][1] * b.m[0][1] + a.m[2][1] * b.m[0][2] + a.m[3][1] * b.m[0][3];
	//	r.m[0][2] = a.m[0][2] * b.m[0][0] + a.m[1][2] * b.m[0][1] + a.m[2][2] * b.m[0][2] + a.m[3][2] * b.m[0][3];
	//	r.m[0][3] = a.m[0][3] * b.m[0][0] + a.m[1][3] * b.m[0][1] + a.m[2][3] * b.m[0][2] + a.m[3][3] * b.m[0][3];
	//
	//	r.m[1][0] = a.m[0][0] * b.m[1][0] + a.m[1][0] * b.m[1][1] + a.m[2][0] * b.m[1][2] + a.m[3][0] * b.m[1][3];
	//	r.m[1][1] = a.m[0][1] * b.m[1][0] + a.m[1][1] * b.m[1][1] + a.m[2][1] * b.m[1][2] + a.m[3][1] * b.m[1][3];
	//	r.m[1][2] = a.m[0][2] * b.m[1][0] + a.m[1][2] * b.m[1][1] + a.m[2][2] * b.m[1][2] + a.m[3][2] * b.m[1][3];
	//	r.m[1][3] = a.m[0][3] * b.m[1][0] + a.m[1][3] * b.m[1][1] + a.m[2][3] * b.m[1][2] + a.m[3][3] * b.m[1][3];
	//
	//	r.m[2][0] = a.m[0][0] * b.m[2][0] + a.m[1][0] * b.m[2][1] + a.m[2][0] * b.m[2][2] + a.m[3][0] * b.m[2][3];
	//	r.m[2][1] = a.m[0][1] * b.m[2][0] + a.m[1][1] * b.m[2][1] + a.m[2][1] * b.m[2][2] + a.m[3][1] * b.m[2][3];
	//	r.m[2][2] = a.m[0][2] * b.m[2][0] + a.m[1][2] * b.m[2][1] + a.m[2][2] * b.m[2][2] + a.m[3][2] * b.m[2][3];
	//	r.m[2][3] = a.m[0][3] * b.m[2][0] + a.m[1][3] * b.m[2][1] + a.m[2][3] * b.m[2][2] + a.m[3][3] * b.m[2][3];
	//
	//	r.m[3][0] = a.m[0][0] * b.m[3][0] + a.m[1][0] * b.m[3][1] + a.m[2][0] * b.m[3][2] + a.m[3][0] * b.m[3][3];
	//	r.m[3][1] = a.m[0][1] * b.m[3][0] + a.m[1][1] * b.m[3][1] + a.m[2][1] * b.m[3][2] + a.m[3][1] * b.m[3][3];
	//	r.m[3][2] = a.m[0][2] * b.m[3][0] + a.m[1][2] * b.m[3][1] + a.m[2][2] * b.m[3][2] + a.m[3][2] * b.m[3][3];
	//	r.m[3][3] = a.m[0][3] * b.m[3][0] + a.m[1][3] * b.m[3][1] + a.m[2][3] * b.m[3][2] + a.m[3][3] * b.m[3][3];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			r.m[i][j] = a.m[i][0] * b.m[0][j] +
				a.m[i][1] * b.m[1][j] +
				a.m[i][2] * b.m[2][j] +
				a.m[i][3] * b.m[3][j];
		}
	}

	return r;
}

//fixed
glVec4 glMultiplyVec4Mat4P(glMat4* m, glVec4* v)
{
	glVec4 r;
	r.x = v->x * m->m[0][0] + v->y * m->m[0][1] + v->z * m->m[0][2] + v->w * m->m[0][3];
	r.y = v->x * m->m[1][0] + v->y * m->m[1][1] + v->z * m->m[1][2] + v->w * m->m[1][3];
	r.z = v->x * m->m[2][0] + v->y * m->m[2][1] + v->z * m->m[2][2] + v->w * m->m[2][3];
	r.w = v->x * m->m[3][0] + v->y * m->m[3][1] + v->z * m->m[3][2] + v->w * m->m[3][3];

	return r;
}

glVec3 glMultiplyVec3Mat4P(glMat4* m, glVec3* v)
{
	glVec3 r;
	r.x = v->x * m->m[0][0] + v->y * m->m[0][1] + v->z * m->m[0][2];
	r.y = v->x * m->m[1][0] + v->y * m->m[1][1] + v->z * m->m[1][2];
	r.z = v->x * m->m[2][0] + v->y * m->m[2][1] + v->z * m->m[2][2];
	return r;
}

//fixed
glVec4 glMultiplyVec4Mat4(glMat4 m, glVec4 v)
{
	glVec4 r;
	r.x = v.x * m.m[0][0] + v.y * m.m[0][1] + v.z * m.m[0][2] + v.w * m.m[0][3];
	r.y = v.x * m.m[1][0] + v.y * m.m[1][1] + v.z * m.m[1][2] + v.w * m.m[1][3];
	r.z = v.x * m.m[2][0] + v.y * m.m[2][1] + v.z * m.m[2][2] + v.w * m.m[2][3];
	r.w = v.x * m.m[3][0] + v.y * m.m[3][1] + v.z * m.m[3][2] + v.w * m.m[3][3];
	return r;
}

//fixed
glMat4 glTranslateMat4P(glMat4* m, glVec3* v)
{
	glMat4 Matrix;

	Matrix.m[0][0] = 1.0;
	Matrix.m[1][0] = 0.0;
	Matrix.m[2][0] = 0.0;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = 0.0;
	Matrix.m[1][1] = 1.0;
	Matrix.m[2][1] = 0.0;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = 0.0;
	Matrix.m[1][2] = 0.0;
	Matrix.m[2][2] = 1.0;
	Matrix.m[3][2] = 0.0;

	Matrix.m[0][3] = v->x;
	Matrix.m[1][3] = v->y;
	Matrix.m[2][3] = v->z;
	Matrix.m[3][3] = 1.0;

	return glMultiplyMat4P(&Matrix, m);
}
//fixed
glMat4 glTranslateMat4(glMat4 m, glVec3 v)
{
	glMat4 Matrix;

	Matrix.m[0][0] = 1.0;
	Matrix.m[1][0] = 0.0;
	Matrix.m[2][0] = 0.0;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = 0.0;
	Matrix.m[1][1] = 1.0;
	Matrix.m[2][1] = 0.0;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = 0.0;
	Matrix.m[1][2] = 0.0;
	Matrix.m[2][2] = 1.0;
	Matrix.m[3][2] = 0.0;

	Matrix.m[0][3] = v.x;
	Matrix.m[1][3] = v.y;
	Matrix.m[2][3] = v.z;
	Matrix.m[3][3] = 1.0;

	return glMultiplyMat4P(&Matrix, &m);
}

//fixed
glMat4 glScaleMat4P(glMat4* m, glVec3* v)
{
	glMat4 Matrix;

	Matrix.m[0][0] = v->x;
	Matrix.m[1][0] = 0.0;
	Matrix.m[2][0] = 0.0;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = 0.0;
	Matrix.m[1][1] = v->y;
	Matrix.m[2][1] = 0.0;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = 0.0;
	Matrix.m[1][2] = 0.0;
	Matrix.m[2][2] = v->z;
	Matrix.m[3][2] = 0.0;

	Matrix.m[0][3] = 0.0;
	Matrix.m[1][3] = 0.0;
	Matrix.m[2][3] = 0.0;
	Matrix.m[3][3] = 1.0;

	return glMultiplyMat4P(&Matrix, m);
}

//fixed
glMat4 glScaleMat4(glMat4 m, glVec3 v)
{
	glMat4 Matrix;

	Matrix.m[0][0] = v.x;
	Matrix.m[1][0] = 0.0;
	Matrix.m[2][0] = 0.0;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = 0.0;
	Matrix.m[1][1] = v.y;
	Matrix.m[2][1] = 0.0;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = 0.0;
	Matrix.m[1][2] = 0.0;
	Matrix.m[2][2] = v.z;
	Matrix.m[3][2] = 0.0;

	Matrix.m[0][3] = 0.0;
	Matrix.m[1][3] = 0.0;
	Matrix.m[2][3] = 0.0;
	Matrix.m[3][3] = 1.0;

	return glMultiplyMat4P(&Matrix, &m);
}
/*
void glRotateMat4(glMat4* m, float Angle, float x, float y, float z)
{
	glMat4 Matrix;
	glMat4 Tmp = *m;

	float Sin = sinf(Angle);
	float Cos = cosf(Angle);

	Matrix.m[0][0] = Cos + x * x * (1 - Cos);
	Matrix.m[0][1] = x * y * (1 - Cos) - z * Sin;
	Matrix.m[0][2] = x * z * (1 - Cos) + y * Sin;
	Matrix.m[0][3] = 0;

	Matrix.m[1][0] = y * x * (1 - Cos) + z * Sin;
	Matrix.m[1][1] = Cos + y * y * (1 - Cos);
	Matrix.m[1][2] = y * z * (1 - Cos) - x * Sin;
	Matrix.m[1][3] = 0;

	Matrix.m[2][0] = z * x * (1 - Cos) - y * Sin;
	Matrix.m[2][1] = z * y * (1 - Cos) + x * Sin;
	Matrix.m[2][2] = Cos + z * z * (1 - Cos);
	Matrix.m[2][3] = 0;

	Matrix.m[3][0] = 0;
	Matrix.m[3][1] = 0;
	Matrix.m[3][2] = 0;
	Matrix.m[3][3] = 1;

	MultiplyMat4P(&Matrix, &Tmp, m);
}
*/
//fixed?????
glMat4 glRotateXMat4P(glMat4* m, float Angle)
{
	glMat4 Matrix;

	register float Cos = cosf(Angle);
	register float Sin = sinf(Angle);

	Matrix.m[0][0] = 1.0;
	Matrix.m[1][0] = 0.0;
	Matrix.m[2][0] = 0.0;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = 0.0;
	Matrix.m[1][1] = Cos;
	Matrix.m[2][1] = -Sin;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = 0.0;
	Matrix.m[1][2] = Sin;
	Matrix.m[2][2] = Cos;
	Matrix.m[3][2] = 0.0;

	Matrix.m[0][3] = 0.0;
	Matrix.m[1][3] = 0.0;
	Matrix.m[2][3] = 0.0;
	Matrix.m[3][3] = 1.0;

	return glMultiplyMat4P(&Matrix, m);
}
//fixed?????
glMat4 glRotateYMat4P(glMat4* m, float Angle)
{
	glMat4 Matrix;

	register float Cos = cosf(Angle);
	register float Sin = sinf(Angle);

	Matrix.m[0][0] = Cos;
	Matrix.m[1][0] = 0.0;
	Matrix.m[2][0] = Sin;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = 0.0;
	Matrix.m[1][1] = 1.0;
	Matrix.m[2][1] = 0.0;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = -Sin;
	Matrix.m[1][2] = 0.0;
	Matrix.m[2][2] = Cos;
	Matrix.m[3][2] = 0.0;

	Matrix.m[0][3] = 0.0;
	Matrix.m[1][3] = 0.0;
	Matrix.m[2][3] = 0.0;
	Matrix.m[3][3] = 1.0;

	return glMultiplyMat4P(&Matrix, m);
}
//fixed?????
glMat4 glRotateZMat4P(glMat4* m, float Angle)
{
	glMat4 Matrix;

	register float Cos = cosf(Angle);
	register float Sin = sinf(Angle);

	Matrix.m[0][0] = Cos;
	Matrix.m[1][0] = -Sin;
	Matrix.m[2][0] = 0.0;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = Sin;
	Matrix.m[1][1] = Cos;
	Matrix.m[2][1] = 0.0;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = 0.0;
	Matrix.m[1][2] = 0.0;
	Matrix.m[2][2] = 1.0;
	Matrix.m[3][2] = 0.0;

	Matrix.m[0][3] = 0.0;
	Matrix.m[1][3] = 0.0;
	Matrix.m[2][3] = 0.0;
	Matrix.m[3][3] = 1.0;

	return glMultiplyMat4P(&Matrix, m);
}
//fixed?????
glMat4 glRotateXMat4(glMat4 m, float Angle)
{
	glMat4 Matrix;

	register float Cos = cosf(Angle);
	register float Sin = sinf(Angle);

	Matrix.m[0][0] = 1.0;
	Matrix.m[1][0] = 0.0;
	Matrix.m[2][0] = 0.0;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = 0.0;
	Matrix.m[1][1] = Cos;
	Matrix.m[2][1] = -Sin;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = 0.0;
	Matrix.m[1][2] = Sin;
	Matrix.m[2][2] = Cos;
	Matrix.m[3][2] = 0.0;

	Matrix.m[0][3] = 0.0;
	Matrix.m[1][3] = 0.0;
	Matrix.m[2][3] = 0.0;
	Matrix.m[3][3] = 1.0;

	return glMultiplyMat4P(&Matrix, &m);
}
//fixed?????
glMat4 glRotateYMat4(glMat4 m, float Angle)
{
	glMat4 Matrix;

	register float Cos = cosf(Angle);
	register float Sin = sinf(Angle);

	Matrix.m[0][0] = Cos;
	Matrix.m[1][0] = 0.0;
	Matrix.m[2][0] = Sin;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = 0.0;
	Matrix.m[1][1] = 1.0;
	Matrix.m[2][1] = 0.0;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = -Sin;
	Matrix.m[1][2] = 0.0;
	Matrix.m[2][2] = Cos;
	Matrix.m[3][2] = 0.0;

	Matrix.m[0][3] = 0.0;
	Matrix.m[1][3] = 0.0;
	Matrix.m[2][3] = 0.0;
	Matrix.m[3][3] = 1.0;

	return glMultiplyMat4P(&Matrix, &m);
}
//fixed?????
glMat4 glRotateZMat4(glMat4 m, float Angle)
{
	glMat4 Matrix;

	register float Cos = cosf(Angle);
	register float Sin = sinf(Angle);

	Matrix.m[0][0] = Cos;
	Matrix.m[1][0] = -Sin;
	Matrix.m[2][0] = 0.0;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = Sin;
	Matrix.m[1][1] = Cos;
	Matrix.m[2][1] = 0.0;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = 0.0;
	Matrix.m[1][2] = 0.0;
	Matrix.m[2][2] = 1.0;
	Matrix.m[3][2] = 0.0;

	Matrix.m[0][3] = 0.0;
	Matrix.m[1][3] = 0.0;
	Matrix.m[2][3] = 0.0;
	Matrix.m[3][3] = 1.0;

	return glMultiplyMat4P(&Matrix, &m);
}

//fixed?
glMat4 glLookAtMat4(glVec3 Pos, glVec3 LookAt, glVec3 Up)
{
	glMat4 Matrix;
	glLoadMat4IdentityP(&Matrix);

	glVec3 F = glNormalize3(glSub3P(&LookAt, &Pos));
	glVec3 S = glNormalize3(glCross3P(&F, &Up));
	glVec3 U = glCross3P(&S, &F);

//	Z.x *= -1;
//	Z.y *= -1;
//	Z.z *= -1;

	Matrix.m[0][0] = S.x;
	Matrix.m[1][0] = S.y;
	Matrix.m[2][0] = S.z;
	Matrix.m[0][1] = U.x;
	Matrix.m[1][1] = U.y;
	Matrix.m[2][1] = U.z;
	Matrix.m[0][2] = -F.x;
	Matrix.m[1][2] = -F.y;
	Matrix.m[2][2] = -F.z;
	Matrix.m[3][0] = -glDot3P(&S, &Pos);
	Matrix.m[3][1] = -glDot3P(&U, &Pos);
	Matrix.m[3][2] =  glDot3P(&F, &Pos);

	return Matrix;
}

//fixed?
glMat4 glLookAtMat4P(glVec3* Pos, glVec3* LookAt, glVec3* Up)
{
	glMat4 Matrix;

	glVec3 Z = glNormalize3(glSub3P(LookAt, Pos));
	glVec3 X = glNormalize3(glCross3P(&Z, Up));
	glVec3 Y = glCross3P(&X, &Z);

	Z.x *= -1;
	Z.y *= -1;
	Z.z *= -1;

	Matrix.m[0][0] = X.x;
	Matrix.m[0][1] = X.y;
	Matrix.m[0][2] = X.z;
	Matrix.m[0][3] = -glDot3P(&X, Pos);
	Matrix.m[1][0] = Y.x;
	Matrix.m[1][1] = Y.y;
	Matrix.m[1][2] = Y.z;
	Matrix.m[1][3] = -glDot3P(&Y, Pos);
	Matrix.m[2][0] = Z.x;
	Matrix.m[2][1] = Z.y;
	Matrix.m[2][2] = Z.z;
	Matrix.m[2][3] = -glDot3P(&Z, Pos);
	Matrix.m[3][0] = 0;
	Matrix.m[3][1] = 0;
	Matrix.m[3][2] = 0;
	Matrix.m[3][3] = 1.0;

	return Matrix;
}

glVec4 glPerspectiveDivide(glVec4 v)
{
	glVec4 r = { v.x / v.w, v.y / v.w, v.z / v.w, v.w };
	return r;
}

//fixed
glMat4 glPerspectiveMat4(float Aspect, float FOV, float NearPlane, float FarPlane)
{
	register float F = tanf(FOV * 0.5);
	register float RangeZ = NearPlane - FarPlane;

	glMat4 Matrix;
	Matrix.m[0][0] = 1.0 / (F * Aspect);
	Matrix.m[1][0] = 0.0;
	Matrix.m[2][0] = 0.0;
	Matrix.m[3][0] = 0.0;

	Matrix.m[0][1] = 0.0;
	Matrix.m[1][1] = 1.0 / F;
	Matrix.m[2][1] = 0.0;
	Matrix.m[3][1] = 0.0;

	Matrix.m[0][2] = 0.0;
	Matrix.m[1][2] = 0.0;
	Matrix.m[2][2] = (-NearPlane - FarPlane) / RangeZ;
	Matrix.m[3][2] = 1.0;

	Matrix.m[0][3] = 0.0;
	Matrix.m[1][3] = 0.0;
	Matrix.m[2][3] = 2 * FarPlane * NearPlane / RangeZ;
	Matrix.m[3][3] = 0.0;

	return Matrix;
}

//fixed
void glPerspectiveMat4P(float Aspect, float FOV, float NearPlane, float FarPlane, glMat4* m)
{
	register float F = tanf(FOV * 0.5);
	register float RangeZ = NearPlane - FarPlane;

	m->m[0][0] = 1.0 / (F * Aspect);
	m->m[1][0] = 0.0;
	m->m[2][0] = 0.0;
	m->m[3][0] = 0.0;

	m->m[0][1] = 0.0;
	m->m[1][1] = 1.0 / F;
	m->m[2][1] = 0.0;
	m->m[3][1] = 0.0;

	m->m[0][2] = 0.0;
	m->m[1][2] = 0.0;
	m->m[2][2] = (-NearPlane - FarPlane) / RangeZ;
	m->m[3][2] = 1.0;

	m->m[0][3] = 0.0;
	m->m[1][3] = 0.0;
	m->m[2][3] = 2 * FarPlane * NearPlane / RangeZ;
	m->m[3][3] = 0.0;
}

glMat4 glOrthoMat4(float Left, float Right, float Bottom, float Top, float NearZ, float FarZ)
{
	glMat4 m;

	m.m[0][0] = 2 / (Right - Left);
	m.m[1][0] = 0.0;
	m.m[2][0] = 0.0;
	m.m[3][0] = -(Right + Left) / (Right - Left);

	m.m[0][1] = 0.0;
	m.m[1][1] = 2 / (Top - Bottom);
	m.m[2][1] = 0.0;
	m.m[3][1] = -(Top + Bottom) / (Top - Bottom);

	m.m[0][2] = 0.0;
	m.m[1][2] = 0.0;
	m.m[2][2] = -1 / (FarZ - NearZ);
	m.m[3][2] = -NearZ / (FarZ - NearZ);

	m.m[0][3] = 0.0;
	m.m[1][3] = 0.0;
	m.m[2][3] = 0.0;
	m.m[3][3] = 1.0;

	return m;
}

void glOrthoMat4P(float Left, float Right, float Bottom, float Top, float NearZ, float FarZ, glMat4* m)
{
	m->m[0][0] = 2 / (Right - Left);
	m->m[1][0] = 0.0;
	m->m[2][0] = 0.0;
	m->m[3][0] = -(Right + Left) / (Right - Left);

	m->m[0][1] = 0.0;
	m->m[1][1] = 2 / (Top - Bottom);
	m->m[2][1] = 0.0;
	m->m[3][1] = -(Top + Bottom) / (Top - Bottom);

	m->m[0][2] = 0.0;
	m->m[1][2] = 0.0;
	m->m[2][2] = -1 / (FarZ - NearZ);
	m->m[3][2] = -NearZ / (FarZ - NearZ);

	m->m[0][3] = 0.0;
	m->m[1][3] = 0.0;
	m->m[2][3] = 0.0;
	m->m[3][3] = 1.0;
}

glMat4 glMulMat4Float(glMat4 m, float f)
{
	glMat4 Result;

	Result.m[0][0] = m.m[0][0] * f;
	Result.m[0][1] = m.m[0][1] * f;
	Result.m[0][2] = m.m[0][2] * f;
	Result.m[0][3] = m.m[0][3] * f;

	Result.m[1][0] = m.m[1][0] * f;
	Result.m[1][1] = m.m[1][1] * f;
	Result.m[1][2] = m.m[1][2] * f;
	Result.m[1][3] = m.m[1][3] * f;

	Result.m[2][0] = m.m[2][0] * f;
	Result.m[2][1] = m.m[2][1] * f;
	Result.m[2][2] = m.m[2][2] * f;
	Result.m[2][3] = m.m[2][3] * f;

	Result.m[3][0] = m.m[3][0] * f;
	Result.m[3][1] = m.m[3][1] * f;
	Result.m[3][2] = m.m[3][2] * f;
	Result.m[3][3] = m.m[3][3] * f;

	return Result;
}

glMat4 glSetMat4Vec4(glVec4 a, glVec4 b, glVec4 c, glVec4 d)
{
	glMat4 Result;

	Result.m[0][0] = a.x;
	Result.m[0][1] = a.y;
	Result.m[0][2] = a.z;
	Result.m[0][3] = a.w;

	Result.m[1][0] = b.x;
	Result.m[1][1] = b.y;
	Result.m[1][2] = b.z;
	Result.m[1][3] = b.w;

	Result.m[2][0] = c.x;
	Result.m[2][1] = c.y;
	Result.m[2][2] = c.z;
	Result.m[2][3] = c.w;

	Result.m[3][0] = d.x;
	Result.m[3][1] = d.y;
	Result.m[3][2] = d.z;
	Result.m[3][3] = d.w;

	return Result;
}

glMat4 glInverseMat4(glMat4 m)
{
	float Coef00 = m.m[2][2] * m.m[3][3] - m.m[3][2] * m.m[2][3];
	float Coef02 = m.m[1][2] * m.m[3][3] - m.m[3][2] * m.m[1][3];
	float Coef03 = m.m[1][2] * m.m[2][3] - m.m[2][2] * m.m[1][3];

	float Coef04 = m.m[2][1] * m.m[3][3] - m.m[3][1] * m.m[2][3];
	float Coef06 = m.m[1][1] * m.m[3][3] - m.m[3][1] * m.m[1][3];
	float Coef07 = m.m[1][1] * m.m[2][3] - m.m[2][1] * m.m[1][3];

	float Coef08 = m.m[2][1] * m.m[3][2] - m.m[3][1] * m.m[2][2];
	float Coef10 = m.m[1][1] * m.m[3][2] - m.m[3][1] * m.m[1][2];
	float Coef11 = m.m[1][1] * m.m[2][2] - m.m[2][1] * m.m[1][2];

	float Coef12 = m.m[2][0] * m.m[3][3] - m.m[3][0] * m.m[2][3];
	float Coef14 = m.m[1][0] * m.m[3][3] - m.m[3][0] * m.m[1][3];
	float Coef15 = m.m[1][0] * m.m[2][3] - m.m[2][0] * m.m[1][3];

	float Coef16 = m.m[2][0] * m.m[3][2] - m.m[3][0] * m.m[2][2];
	float Coef18 = m.m[1][0] * m.m[3][2] - m.m[3][0] * m.m[1][2];
	float Coef19 = m.m[1][0] * m.m[2][2] - m.m[2][0] * m.m[1][2];

	float Coef20 = m.m[2][0] * m.m[3][1] - m.m[3][0] * m.m[2][1];
	float Coef22 = m.m[1][0] * m.m[3][1] - m.m[3][0] * m.m[1][1];
	float Coef23 = m.m[1][0] * m.m[2][1] - m.m[2][0] * m.m[1][1];

	glVec4 Fac0 = GLVec4(Coef00, Coef00, Coef02, Coef03);
	glVec4 Fac1 = GLVec4(Coef04, Coef04, Coef06, Coef07);
	glVec4 Fac2 = GLVec4(Coef08, Coef08, Coef10, Coef11);
	glVec4 Fac3 = GLVec4(Coef12, Coef12, Coef14, Coef15);
	glVec4 Fac4 = GLVec4(Coef16, Coef16, Coef18, Coef19);
	glVec4 Fac5 = GLVec4(Coef20, Coef20, Coef22, Coef23);

	glVec4 Vec0 = GLVec4(m.m[1][0], m.m[0][0], m.m[0][0], m.m[0][0]);
	glVec4 Vec1 = GLVec4(m.m[1][1], m.m[0][1], m.m[0][1], m.m[0][1]);
	glVec4 Vec2 = GLVec4(m.m[1][2], m.m[0][2], m.m[0][2], m.m[0][2]);
	glVec4 Vec3 = GLVec4(m.m[1][3], m.m[0][3], m.m[0][3], m.m[0][3]);

	glVec4 Inv0 = glAdd4(glSub4(glMul4(Vec1, Fac0), glMul4(Vec2, Fac1)), glMul4(Vec3, Fac2));
	glVec4 Inv1 = glAdd4(glSub4(glMul4(Vec0, Fac0), glMul4(Vec2, Fac3)), glMul4(Vec3, Fac4));
	glVec4 Inv2 = glAdd4(glSub4(glMul4(Vec0, Fac1), glMul4(Vec1, Fac3)), glMul4(Vec3, Fac5));
	glVec4 Inv3 = glAdd4(glSub4(glMul4(Vec0, Fac2), glMul4(Vec1, Fac4)), glMul4(Vec2, Fac5));

	glVec4 SignA = GLVec4(+1, -1, +1, -1);
	glVec4 SignB = GLVec4(-1, +1, -1, +1);
	glMat4 Inverse = glSetMat4Vec4(glMul4(Inv0, SignA), glMul4(Inv1, SignB), glMul4(Inv2, SignA), glMul4(Inv3, SignB));

	glVec4 Row0 = GLVec4(Inverse.m[0][0], Inverse.m[1][0], Inverse.m[2][0], Inverse.m[3][0]);

	//???
	glVec4 Dot0 = glMul4(GLVec4(m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3]), Row0);

	float Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

	float OneOverDeterminant = 1 / Dot1;

	//???
	return glMulMat4Float(Inverse, OneOverDeterminant);
}

//helper
extern inline void glPrintVec2(glVec2* a)
{
	printf("%f %f\n", a->x, a->y);
}

extern inline void glPrintVec3(glVec3* a)
{
	printf("%f %f %f\n", a->x, a->y, a->z);
}

extern inline void glPrintVec4(glVec4* a)
{
	printf("%f %f %f %f\n", a->x, a->y, a->z, a->w);
}

extern inline int glRandomInt(int Min, int Max)
{
	return (rand() % (Max - Min + 1)) + Min;
}

extern inline float glToRadians(float Angle)
{
	return 0.01745329251 * Angle;
}

typedef struct
{
	int Width;
	int Height;
	float Aspect;
	int Flags;

	SDL_Window* Window;
	SDL_Surface* Surface;
	SDL_Renderer* Renderer;
	SDL_Texture* Swapchain;
	SDL_Event Event;
} glWindow;

typedef struct
{
	int Width;
	int Height;
	int Size;
	int ImageType;
	unsigned char* Data;
} glImage;

typedef enum
{
	GL_IMAGE_RGB = 0x3,
	GL_IMAGE_RGBA = 0x4,
	GL_IMAGE_DEPTH_BUFFER = GL_IMAGE_RGBA,
	GL_IMAGE_FRAME_BUFFER = GL_IMAGE_RGBA,
} glImageType;

typedef enum
{
	GL_WINDOW_DYNAMIC_ASPECT = 0x0,
	GL_WINDOW_ASPECT_16_9 = 0x1,
	GL_WINDOW_ASPECT_4_3 = 0x2,
} glWindowFlags;

void glCreateWindow(const char* Title, int x, int y, int Width, int Height, int WindowFlags, glWindow* Window)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	Window->Width = Width;
	Window->Height = Height;
	Window->Flags = WindowFlags;

	switch (WindowFlags)
	{
	case GL_WINDOW_DYNAMIC_ASPECT:
		Window->Aspect = (float)Width / (float)Height;
		break;

	case GL_WINDOW_ASPECT_16_9:
		Window->Aspect = 1.777777777777778;
		break;

	case GL_WINDOW_ASPECT_4_3:
		Window->Aspect = 1.333333333333333;
		break;

	default:
		break;
	}

	Window->Window = SDL_CreateWindow(Title, x, y, Width, Height, SDL_WINDOW_RESIZABLE);
	Window->Surface = SDL_GetWindowSurface(Window->Window);
	Window->Renderer = SDL_CreateRenderer(Window->Window, -1, SDL_RENDERER_SOFTWARE);
	Window->Swapchain = SDL_CreateTexture(Window->Renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, Width, Height);
}

void glDestroy(glWindow* Window)
{
	SDL_DestroyTexture(Window->Swapchain);
	SDL_DestroyRenderer(Window->Renderer);
	SDL_DestroyWindow(Window->Window);
	SDL_Quit();
}

typedef enum
{
	GL_EVENT_QUIT = 0x1,
	GL_EVENT_RESIZE = 0x2
} glEventType;

int glPollEvent(glWindow* Window)
{
	while (SDL_PollEvent(&Window->Event))
	{
		if (Window->Event.type == SDL_QUIT ||
			Window->Event.type == SDL_WINDOWEVENT && Window->Event.window.event == SDL_WINDOWEVENT_CLOSE)
			return GL_EVENT_QUIT;

		if (Window->Event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			SDL_GetWindowSize(Window->Window, &Window->Width, &Window->Height);

			if (Window->Flags != GL_WINDOW_DYNAMIC_ASPECT)
			{
				Window->Height = Window->Width / Window->Aspect;
				SDL_SetWindowSize(Window->Window, Window->Width, Window->Height);
			}				
			else
			{
				Window->Aspect = (float)Window->Width / (float)Window->Height;
			}
			
			SDL_FlushEvent(SDL_WINDOWEVENT_RESIZED);

			SDL_DestroyRenderer(Window->Renderer);
			Window->Renderer = SDL_CreateRenderer(Window->Window, -1, SDL_RENDERER_SOFTWARE);
			SDL_RenderSetLogicalSize(Window->Renderer, Window->Width, Window->Height);
			SDL_Rect Rect;
			Rect.x = 0;
			Rect.y = 0;
			Rect.w = Window->Width;
			Rect.h = Window->Height;
			SDL_RenderSetViewport(Window->Renderer, &Rect);
			SDL_DestroyTexture(Window->Swapchain);
			Window->Swapchain = SDL_CreateTexture(Window->Renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, Window->Width, Window->Height);
			return GL_EVENT_RESIZE;
		}

		return 0;
	}

	return 0;
}

extern inline void glSetWindowTitle(glWindow* Window, const char* Title)
{
	SDL_SetWindowTitle(Window->Window, Title);
}

extern inline void glGetWindowSize(glWindow* Window, int* Width, int* Height)
{
	SDL_GetWindowSize(Window->Window, Width, Height);
}

extern inline void glSetWindowSize(glWindow* Window, int Width, int Height)
{
	SDL_SetWindowSize(Window->Window, Width, Height);
}

extern inline int glGetWindowFocus(glWindow* Window)
{
	return (SDL_GetWindowFlags(Window->Window) & SDL_WINDOW_INPUT_FOCUS);
}

void glCreateImage(int Width, int Height, int ImageType, glImage* Image)
{
	Image->Width = Width;
	Image->Height = Height;
	Image->ImageType = ImageType;
	Image->Size = Width * Height * Image->ImageType;
	Image->Data = (unsigned char*)malloc(Image->Size);
	memset(Image->Data, 255, Image->Size);
}

void glResizeImage(int Width, int Height, glImage* Image)
{
	Image->Width = Width;
	Image->Height = Height;
	Image->Size = Width * Height * Image->ImageType;
	Image->Data = (unsigned char*)realloc(Image->Data, Image->Size);
	memset(Image->Data, 255, Image->Size);
}

void glFreeImage(glImage* Image)
{
	Image->ImageType = 0;
	Image->Width = 0;
	Image->Height = 0;
	free(Image->Data);
	Image->Data = NULL;
}

void glClearImage(int Shade, glImage* Image)
{
	memset(Image->Data, Shade, Image->Size);
}

void glRescaleImage(glImage* Image, int NewWidth, int NewHeight)
{
	glImage NewImage;
	NewImage.ImageType = Image->ImageType;
	NewImage.Width = NewWidth;
	NewImage.Height = NewHeight;
	NewImage.Size = NewWidth * NewHeight * Image->ImageType;
	NewImage.Data = (unsigned char*)malloc(NewImage.Size);

	float ImageX = 0;
	float ImageY = 0;

	float ImageW = (float)Image->Width / (float)NewWidth;
	float ImageH = (float)Image->Height / (float)NewHeight;

	for (int x = 0; x < NewWidth; x++)
	{
		for (int y = 0; y < NewHeight; y++)
		{
			int Index0 = ((int)ImageX + (int)ImageY * Image->Width) * Image->ImageType;
			int Index1 = (x + y * NewWidth) * Image->ImageType;

			NewImage.Data[Index1] = Image->Data[Index0];
			NewImage.Data[Index1 + 1] = Image->Data[Index0 + 1];
			NewImage.Data[Index1 + 2] = Image->Data[Index0 + 2];
			if (Image->ImageType == GL_IMAGE_RGBA)
				NewImage.Data[Index1 + 3] = Image->Data[Index0 + 3];

			ImageY += ImageH;
		}

		ImageY = 0;
		ImageX += ImageW;
	}

	free(Image->Data);
	*Image = NewImage;
}

void glImageRGB(glImage* Image, unsigned int AlphaColor)
{
	if (Image->ImageType == GL_IMAGE_RGB)
		return;

	glImage NewImage = *Image;
	NewImage.ImageType = GL_IMAGE_RGB;
	NewImage.Size = NewImage.Width * NewImage.Height * NewImage.ImageType;
	NewImage.Data = (unsigned char*)malloc(NewImage.Size);

	int j = 0;
	for (int i = 0; i < Image->Size; i += 4)
	{
		unsigned int* Color = (unsigned int*)(NewImage.Data + j);
		if (Image->Data[i + 3] == 0)
		{
			memcpy(Color, &AlphaColor, 3);
		}
		else
		{
			NewImage.Data[j] = Image->Data[i];
			NewImage.Data[j + 1] = Image->Data[i + 1];
			NewImage.Data[j + 2] = Image->Data[i + 2];
		}
		
		j += 3;
	}

	free(Image->Data);
	*Image = NewImage;
}

void glImageRGBA(glImage* Image, unsigned int AlphaColor)
{
	if (Image->ImageType == GL_IMAGE_RGBA)
		return;

	glImage NewImage = *Image;
	NewImage.ImageType = GL_IMAGE_RGBA;
	NewImage.Size = NewImage.Width * NewImage.Height * NewImage.ImageType;
	NewImage.Data = (unsigned char*)malloc(NewImage.Size);

	int j = 0;
	for (int i = 0; i < Image->Size; i += 3)
	{
	//	unsigned int* Color = (unsigned int*)((Image->Data + i));
	//	if (*Color == AlphaColor)
		if (Image->Data[i	 ] == ((AlphaColor >> 0) & 0xFF) &&
			Image->Data[i + 1] == ((AlphaColor >> 8) & 0xFF) &&
			Image->Data[i + 2] == ((AlphaColor >>16) & 0xFF))
			NewImage.Data[j + 3] = 0;
		else
			NewImage.Data[j + 3] = 255;

		NewImage.Data[j] = Image->Data[i];
		NewImage.Data[j + 1] = Image->Data[i + 1];
		NewImage.Data[j + 2] = Image->Data[i + 2];
		
		j += 4;
	}

	free(Image->Data);
	*Image = NewImage;
}

//mul with GL_FLOAT_BYTE
glVec3 glGetColor3(unsigned int Color)
{
	glVec3 RGB;
	RGB.z = ((Color >> 16) & 0xFF);
	RGB.y = ((Color >> 8) & 0xFF);
	RGB.x = ((Color >> 0) & 0xFF);

	return RGB;
}

//mul with GL_FLOAT_BYTE
glVec4 glGetColor4(unsigned int Color)
{
	glVec4 RGBA;
	RGBA.w = ((Color >> 24) & 0xFF);
	RGBA.z = ((Color >> 16) & 0xFF);
	RGBA.y = ((Color >> 8) & 0xFF);
	RGBA.x = ((Color >> 0) & 0xFF);

	return RGBA;
}

inline unsigned int glGetColor24(glVec3* Color)
{
	return GL_COLOR_24(Color->x * 255.0, Color->y * 255.0, Color->z * 255.0);
}

inline unsigned int glGetColor32(glVec4* Color)
{
	return GL_COLOR_32(Color->x * 255.0, Color->y * 255.0, Color->z * 255.0, Color->w * 255.0);
}

extern inline void glImageBrightness(float Brightness, glImage* Image)
{
	for (int i = 0; i < Image->Size; i++)
		Image->Data[i] = ((float)Image->Data[i] * Brightness);
}

void glDrawFramebuffer(glWindow* Window, glImage* Framebuffer)
{
	void* Pixels;
	int Pitch;

	SDL_LockTexture(Window->Swapchain, NULL, &Pixels, &Pitch);
	memcpy(Pixels, Framebuffer->Data, Pitch * Framebuffer->Height);
	SDL_UnlockTexture(Window->Swapchain);

	SDL_RenderClear(Window->Renderer);
	SDL_RenderCopy(Window->Renderer, Window->Swapchain, NULL, NULL);
//	SDL_RenderCopyEx(Window->Renderer, Window->Swapchain, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
	SDL_RenderPresent(Window->Renderer);
}

//must be equal to framebuffer
void glDrawBackground(glImage* Image, glImage* Framebuffer)
{
	memcpy(Framebuffer->Data, Image->Data, Framebuffer->Size);
}

void glDrawLayer(glImage* Image, glImage* Framebuffer)
{
	for (int i = 0; i < Framebuffer->Size; i += 4)
	{
		if (Image->Data[i + 3] != 0)
		{
			Framebuffer->Data[i] = Image->Data[i];
			Framebuffer->Data[i + 1] = Image->Data[i + 1];
			Framebuffer->Data[i + 2] = Image->Data[i + 2];
			Framebuffer->Data[i + 3] = Image->Data[i + 3];
		}
	}
}

extern inline void glDrawPixel(int x, int y, unsigned int Color, glImage* Framebuffer)
{
	int Index = (x + y * Framebuffer->Width) * Framebuffer->ImageType;
	if (((Color >> 24) & 0xFF) != 0)
		memcpy(Framebuffer->Data + Index, &Color, Framebuffer->ImageType);
	/*
	if (Index >= 0 && Index < Framebuffer->Size &&
		x >= 0 && x < Framebuffer->Width &&
		y >= 0 && y < Framebuffer->Height)
	{
		if (((Color >> 24) & 0xFF) != 0)
		{
			memcpy(Framebuffer->Data + Index, &Color, Framebuffer->ImageType);
		//	Framebuffer->Data[Index] = ((Color >> 0) & 0xFF);
		//	Framebuffer->Data[Index + 1] = ((Color >> 8) & 0xFF);
		//	Framebuffer->Data[Index + 2] = ((Color >> 16) & 0xFF);
		//	Framebuffer->Data[Index + 3] = ((Color >> 24) & 0xFF);
		}
	}
	*/
}

extern inline void glDrawRect(int MinX, int MinY, int MaxX, int MaxY, unsigned int Color, glImage* Framebuffer)
{
	for (int x = MinX; x < MaxX; x++)
	{
		for (int y = MinY; y < MaxY; y++)
		{
			glDrawPixel(x, y, Color, Framebuffer);
		}
	}
}

extern inline void glDrawQuad(int PosX, int PosY, int ScaleX, int ScaleY, unsigned int Color, glImage* Framebuffer)
{
	glDrawRect(PosX, PosY, PosX + ScaleX, PosY + ScaleY, Color, Framebuffer);
}

extern inline void glDrawPoint(int Scale, int PosX, int PosY, unsigned int Color, glImage* Framebuffer)
{
	float Half = Scale * 0.5;

	glDrawRect(PosX - Half, PosY - Half, PosX + Half, PosY + Half, Color, Framebuffer);
}

void glDrawSubTexture(int PosX, int PosY, int ScaleX, int ScaleY, int StartX, int StartY, int EndX, int EndY, glImage* Image, int FlipVert, int FlipHorz, glImage* Framebuffer)
{
	float ImageX;
	float ImageY;

	float ImageW;
	float ImageH;

	float ImageStartY;

	if (FlipHorz)
	{
		ImageX = StartX + EndX - (1.0 / (float)ScaleX);
		ImageW = -(float)EndX / (float)ScaleX;
	}
	else
	{
		ImageX = StartX;
		ImageW = (float)EndX / (float)ScaleX;
	}

	if (FlipVert)
	{
		ImageStartY = StartY + EndY - (1.0 / (float)ScaleY);
		ImageY = ImageStartY;
		ImageH = -(float)EndY / (float)ScaleY;
	}
	else
	{
		ImageStartY = 0;
		ImageY = StartY;
		ImageH = (float)EndY / (float)ScaleY;
	}

	for (int x = PosX; x < PosX + ScaleX; x++)
	{
		for (int y = PosY; y < PosY + ScaleY; y++)
		{
			int Index = ((int)ImageX + (int)ImageY * Image->Width) * Image->ImageType;

			ImageY += ImageH;

			if (Image->ImageType == GL_IMAGE_RGB)
				glDrawPixel(x, y, GL_COLOR_24(Image->Data[Index], Image->Data[Index + 1], Image->Data[Index + 2]), Framebuffer);
			else
				glDrawPixel(x, y, GL_COLOR_32(Image->Data[Index], Image->Data[Index + 1], Image->Data[Index + 2], Image->Data[Index + 3]), Framebuffer);
		}

		ImageY = ImageStartY;
		ImageX += ImageW;
	}
}


extern inline void glDrawTexture(int PosX, int PosY, int ScaleX, int ScaleY, glImage* Image, int FlipVert, int FlipHorz, glImage* Framebuffer)
{
	glDrawSubTexture(PosX, PosY, ScaleX, ScaleY, 0, 0, Image->Width, Image->Height, Image, FlipVert, FlipHorz, Framebuffer);
}

void glDrawLine(int x1, int y1, int x2, int y2, unsigned int Color, glImage* Framebuffer)
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = fabs(dx);
	dy1 = fabs(dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		glDrawPixel(x, y, Color, Framebuffer);
		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			glDrawPixel(x, y, Color, Framebuffer);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}
		glDrawPixel(x, y, Color, Framebuffer);
		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			glDrawPixel(x, y, Color, Framebuffer);
		}
	}
}

typedef struct
{
	glVec4 Pos;
	glVec2 TexCoord;
	glVec3 Color;
	glVec3 Normal;
} glVertex;

typedef enum
{
	GL_TRIANGLE_COLOR = 1,
	GL_TRIANGLE_TEXTURE = 16,
	GL_TRIANGLE_LIGHTING = 32,
	GL_TRIANGLE_DEPTHTEST = 64,
} glTriangleFlags;

typedef struct
{
	int Flags;
	float Ambient;
	glVec3 LightDir;
	glVertex v0;
	glVertex v1;
	glVertex v2;
	glImage* Texture;
	glImage* Depthbuffer;
	glImage* Framebuffer;
} glTriangle;

glVertex glLerpVertex(glVertex* a, glVertex* b, float LerpAmt)
{
	glVertex Res;
	Res.Pos = glLerp4P(&a->Pos, &b->Pos, LerpAmt);
	Res.TexCoord = glLerp2P(&a->TexCoord, &b->TexCoord, LerpAmt);
	Res.Color = glLerp3P(&a->Color, &b->Color, LerpAmt);
	Res.Normal = glLerp3P(&a->Normal, &b->Normal, LerpAmt);
	return Res;
}

typedef struct
{
	float TexCoordDX[3];
	float TexCoordDY[3];
	float OneOverZ[3];
	float Depth[3];
	float LightAmt[3];

	float TexCoordStepXX;
	float TexCoordStepXY;
	float TexCoordStepYX;
	float TexCoordStepYY;

	float OneOverStepZX;
	float OneOverStepZY;

	float DepthStepX;
	float DepthStepY;

	float LightAmtStepX;
	float LightAmtStepY;

	glVec3 Color[3];
	glVec3 ColorStepX;
	glVec3 ColorStepY;
} glGradientsData;

float glCalcStepX(float* Values, glVertex* MinVertY, glVertex* MidVertY, glVertex* MaxVertY, float OneOverDX)
{
	return (((Values[1] - Values[2]) *
		(MinVertY->Pos.y - MaxVertY->Pos.y)) -
		((Values[0] - Values[2]) *
			(MidVertY->Pos.y - MaxVertY->Pos.y))) * OneOverDX;
}

float glCalcStepY(float* Values, glVertex* MinVertY, glVertex* MidVertY, glVertex* MaxVertY, float OneOverDY)
{
	return (((Values[1] - Values[2]) *
		(MinVertY->Pos.x - MaxVertY->Pos.x)) -
		((Values[0] - Values[2]) *
			(MidVertY->Pos.x - MaxVertY->Pos.x))) * OneOverDY;
}

inline float glSaturate(float Val)
{
	if (Val < 0.0)
		return 0.0;
	if (Val > 1.0)
		return 1.0;
	
	return Val;
}

void glGradients(glTriangle* Triangle, glVertex* MinVertY, glVertex* MidVertY, glVertex* MaxVertY, glGradientsData* Data)
{
	Data->Color[0] = MinVertY->Color;
	Data->Color[1] = MidVertY->Color;
	Data->Color[2] = MaxVertY->Color;

	float OneOverDX = 1.0 / (((MidVertY->Pos.x - MaxVertY->Pos.x) *
							  (MinVertY->Pos.y - MaxVertY->Pos.y)) -
							 ((MinVertY->Pos.x - MaxVertY->Pos.x) *
							  (MidVertY->Pos.y - MaxVertY->Pos.y)));

	float OneOverDY = -OneOverDX;

	if (Triangle->Flags & GL_TRIANGLE_DEPTHTEST)
	{
		Data->Depth[0] = MinVertY->Pos.z;
		Data->Depth[1] = MidVertY->Pos.z;
		Data->Depth[2] = MaxVertY->Pos.z;

		Data->DepthStepX = glCalcStepX(Data->Depth, MinVertY, MidVertY, MaxVertY, OneOverDX);
		Data->DepthStepY = glCalcStepY(Data->Depth, MinVertY, MidVertY, MaxVertY, OneOverDY);
	}	

	if (Triangle->Flags & GL_TRIANGLE_LIGHTING)
	{
	//	glVec3 LightDir = GLVec3(-0.711, 0.627, -0.319);
		float Ambient = (1.0 - Triangle->Ambient);
		Data->LightAmt[0] = glSaturate(glDot3P(&MinVertY->Normal, &Triangle->LightDir)) * Triangle->Ambient + Ambient;
		Data->LightAmt[1] = glSaturate(glDot3P(&MidVertY->Normal, &Triangle->LightDir)) * Triangle->Ambient + Ambient;
		Data->LightAmt[2] = glSaturate(glDot3P(&MaxVertY->Normal, &Triangle->LightDir)) * Triangle->Ambient + Ambient;

		Data->LightAmtStepX = glCalcStepX(Data->LightAmt, MinVertY, MidVertY, MaxVertY, OneOverDX);
		Data->LightAmtStepY = glCalcStepY(Data->LightAmt, MinVertY, MidVertY, MaxVertY, OneOverDY);
	}
	
	if (Triangle->Flags & GL_TRIANGLE_TEXTURE)
	{
		Data->OneOverZ[0] = 1.0 / MinVertY->Pos.w;
		Data->OneOverZ[1] = 1.0 / MidVertY->Pos.w;
		Data->OneOverZ[2] = 1.0 / MaxVertY->Pos.w;

		Data->TexCoordDX[0] = MinVertY->TexCoord.x * Data->OneOverZ[0];
		Data->TexCoordDX[1] = MidVertY->TexCoord.x * Data->OneOverZ[1];
		Data->TexCoordDX[2] = MaxVertY->TexCoord.x * Data->OneOverZ[2];

		Data->TexCoordDY[0] = MinVertY->TexCoord.y * Data->OneOverZ[0];
		Data->TexCoordDY[1] = MidVertY->TexCoord.y * Data->OneOverZ[1];
		Data->TexCoordDY[2] = MaxVertY->TexCoord.y * Data->OneOverZ[2];

		Data->TexCoordStepXX = glCalcStepX(Data->TexCoordDX, MinVertY, MidVertY, MaxVertY, OneOverDX);
		Data->TexCoordStepXY = glCalcStepY(Data->TexCoordDX, MinVertY, MidVertY, MaxVertY, OneOverDY);
		Data->TexCoordStepYX = glCalcStepX(Data->TexCoordDY, MinVertY, MidVertY, MaxVertY, OneOverDX);
		Data->TexCoordStepYY = glCalcStepY(Data->TexCoordDY, MinVertY, MidVertY, MaxVertY, OneOverDY);		

		Data->OneOverStepZX = glCalcStepX(Data->OneOverZ, MinVertY, MidVertY, MaxVertY, OneOverDX);
		Data->OneOverStepZY = glCalcStepY(Data->OneOverZ, MinVertY, MidVertY, MaxVertY, OneOverDY);
	}
	if (Triangle->Flags & GL_TRIANGLE_COLOR)
	{
		glVec3 x = glMul3(glSub3(Data->Color[1], Data->Color[2]), GLVec3f(MinVertY->Pos.y - MaxVertY->Pos.y));
		glVec3 y = glMul3(glSub3(Data->Color[0], Data->Color[2]), GLVec3f(MidVertY->Pos.y - MaxVertY->Pos.y));
		Data->ColorStepX = glMul3(glSub3(x, y), GLVec3f(OneOverDX));

		x = glMul3(glSub3(Data->Color[1], Data->Color[2]), GLVec3f(MinVertY->Pos.x - MaxVertY->Pos.x));
		y = glMul3(glSub3(Data->Color[0], Data->Color[2]), GLVec3f(MidVertY->Pos.x - MaxVertY->Pos.x));
		Data->ColorStepY = glMul3(glSub3(x, y), GLVec3f(OneOverDY));
	}
}

typedef struct
{
	float EdgeStepX;
	float EdgeX;
	int EdgeStartY;
	int EdgeEndY;

	float TexCoordDX;
	float TexCoordStepX;

	float TexCoordDY;
	float TexCoordStepY;

	float OneOverZ;
	float OneOverStepZ;

	float Depth;
	float DepthStep;

	float LightAmt;
	float LightAmtStep;

	glVec3 Color;
	glVec3 ColorStep;
} glEdgeData;

void glEdge(glTriangle* Triangle, glGradientsData* Gradients, glVertex* MinVertY, glVertex* MaxVertY, int MinYVertIndex, glEdgeData* Data)
{
	Data->EdgeStartY = (int)ceilf(MinVertY->Pos.y);
	Data->EdgeEndY = (int)ceilf(MaxVertY->Pos.y);

	Data->EdgeStepX = (MaxVertY->Pos.x - MinVertY->Pos.x) / (MaxVertY->Pos.y - MinVertY->Pos.y);
	float PrestepY = (float)Data->EdgeStartY - MinVertY->Pos.y;
	Data->EdgeX = MinVertY->Pos.x + PrestepY * Data->EdgeStepX;

	float PrestepX = Data->EdgeX - MinVertY->Pos.x;

	if (Triangle->Flags & GL_TRIANGLE_DEPTHTEST)
	{
		Data->Depth = Gradients->Depth[MinYVertIndex] +
					  Gradients->DepthStepX * PrestepX +
					  Gradients->DepthStepY * PrestepY;
		Data->DepthStep = Gradients->DepthStepY + Gradients->DepthStepX * Data->EdgeStepX;
	}	

	if (Triangle->Flags & GL_TRIANGLE_LIGHTING)
	{
		Data->LightAmt = Gradients->LightAmt[MinYVertIndex] +
						 Gradients->LightAmtStepX * PrestepX +
						 Gradients->LightAmtStepY * PrestepY;
		Data->LightAmtStep = Gradients->LightAmtStepY + Gradients->LightAmtStepX * Data->EdgeStepX;
	}	

	if (Triangle->Flags & GL_TRIANGLE_TEXTURE)
	{
		Data->TexCoordDX = Gradients->TexCoordDX[MinYVertIndex] +
						   Gradients->TexCoordStepXX * PrestepX +
						   Gradients->TexCoordStepXY * PrestepY;
		Data->TexCoordStepX = Gradients->TexCoordStepXY + Gradients->TexCoordStepXX * Data->EdgeStepX;

		Data->TexCoordDY = Gradients->TexCoordDY[MinYVertIndex] +
						   Gradients->TexCoordStepYX * PrestepX +
						   Gradients->TexCoordStepYY * PrestepY;
		Data->TexCoordStepY = Gradients->TexCoordStepYY + Gradients->TexCoordStepYX * Data->EdgeStepX;

		Data->OneOverZ = Gradients->OneOverZ[MinYVertIndex] +
						 Gradients->OneOverStepZX * PrestepX +
						 Gradients->OneOverStepZY * PrestepY;
		Data->OneOverStepZ = Gradients->OneOverStepZY + Gradients->OneOverStepZX * Data->EdgeStepX;
	}

	if (Triangle->Flags & GL_TRIANGLE_COLOR)
	{
		Data->Color = glAdd3(glAdd3(Gradients->Color[MinYVertIndex], glMul3(Gradients->ColorStepY, GLVec3f(PrestepY))), glMul3(Gradients->ColorStepX, GLVec3f(PrestepX)));
		Data->ColorStep = glAdd3(Gradients->ColorStepY, glMul3(Gradients->ColorStepX, GLVec3f(Data->EdgeStepX)));
	}
}

inline void glStepEdge(glTriangle* Triangle, glEdgeData* d)
{
	d->EdgeX += d->EdgeStepX;
	if (Triangle->Flags & GL_TRIANGLE_DEPTHTEST) d->Depth += d->DepthStep;
	if (Triangle->Flags & GL_TRIANGLE_LIGHTING)	 d->LightAmt += d->LightAmtStep;
	if (Triangle->Flags & GL_TRIANGLE_COLOR)	 d->Color = glAdd3P(&d->Color, &d->ColorStep);
	if (Triangle->Flags & GL_TRIANGLE_TEXTURE)
	{
		d->TexCoordDX += d->TexCoordStepX;
		d->TexCoordDY += d->TexCoordStepY;
		d->OneOverZ += d->OneOverStepZ;
	}
}

inline float glTriangleAreaTimesTwo(glVertex* a, glVertex* b, glVertex* c)
{
	return ((b->Pos.x - a->Pos.x) * (c->Pos.y - a->Pos.y) - (c->Pos.x - a->Pos.x) * (b->Pos.y - a->Pos.y));
}

int glIsInDepthRange(float Depth, int x, int y, glImage* Depthbuffer)
{
	int DepthIndex = (x + y * Depthbuffer->Width) * Depthbuffer->ImageType;
	if (DepthIndex >= 0 && DepthIndex < Depthbuffer->Size)
	{
		float* Buffer = (float*)(Depthbuffer->Data + DepthIndex);
		if (Depth < *Buffer)
		{
			memcpy((Depthbuffer->Data + DepthIndex), &Depth, Depthbuffer->ImageType);
			return 1;
		}			
	}

	return 0;
}
/*
void glDrawColorScanline(glGradientsData* Gradients, glEdgeData* Left, glEdgeData* Right, int y, glImage* Depthbuffer, glImage* Framebuffer)
{
	int MinX = (int)ceilf(Left->EdgeX);
	int MaxX = (int)ceilf(Right->EdgeX);
	float PrestepX = MinX - Left->EdgeX;

	glVec3 Color = glAdd3(Left->Color, glMul3(Gradients->ColorStepX, GLVec3f(PrestepX)));

	float Depth = Left->Depth + Gradients->DepthStepX * PrestepX;
	float LightAmt = Left->LightAmt + Gradients->LightAmtStepX * PrestepX;

	for (int x = MinX; x < MaxX; x++)
	{
		if (glIsInDepthRange(Depth, x, y, Depthbuffer))
		{
			glVec3 MixedColor = glMul3(Color, GLVec3f(LightAmt));

			glDrawPixel(x, y, glGetColor24(&MixedColor), Framebuffer);
		}
			
		
		Color = glAdd3(Color, Gradients->ColorStepX);
		Depth += Gradients->DepthStepX;
		LightAmt += Gradients->LightAmtStepX;
	}
}

void glDrawTextureScanline(glGradientsData* Gradients, glEdgeData* Left, glEdgeData* Right, int y, glImage* Texture, glImage* Depthbuffer, glImage* Framebuffer)
{
	int MinX = (int)ceilf(Left->EdgeX);
	int MaxX = (int)ceilf(Right->EdgeX);

	float PrestepX = MinX - Left->EdgeX;
//	float OneOverStepZX = (Right->OneOverZ - Left->OneOverZ) / (Right->EdgeX - Left->EdgeX);
	float OneOverZ = Left->OneOverZ + Gradients->OneOverStepZX * PrestepX;

	glVec2 TexCoord =
	{
		Left->TexCoordDX + Gradients->TexCoordStepXX * PrestepX,
		Left->TexCoordDY + Gradients->TexCoordStepYX * PrestepX
	};

	float Depth = Left->Depth + Gradients->DepthStepX * PrestepX;
	float LightAmt = Left->LightAmt + Gradients->LightAmtStepX * PrestepX;

	for (int x = MinX; x < MaxX; x++)
	{
		if (glIsInDepthRange(Depth, x, y, Depthbuffer))
		{
			float z = 1.0 / OneOverZ;
			int SrcX = (int)((TexCoord.x * z) * (Texture->Width - 1) + 0.5);
			int SrcY = (int)((TexCoord.y * z) * (Texture->Height - 1) + 0.5);

			int Index = (SrcX + SrcY * Texture->Width) * Texture->ImageType;
			if (Index >= 0 && Index < Texture->Size)
			{
				glVec3 MixedColor = glMul3(GLVec3f(LightAmt), GLVec3(Texture->Data[Index] * GL_BYTE_FLOAT, Texture->Data[Index + 1] * GL_BYTE_FLOAT, Texture->Data[Index + 2] * GL_BYTE_FLOAT));
				glDrawPixel(x, y, glGetColor24(&MixedColor), Framebuffer);
			}				
		}

		TexCoord.x += Gradients->TexCoordStepXX;
		TexCoord.y += Gradients->TexCoordStepYX;
		OneOverZ += Gradients->OneOverStepZX;
		Depth += Gradients->DepthStepX;
		LightAmt += Gradients->LightAmtStepX;
	}
}

void glDrawColorTextureScanline(glGradientsData* Gradients, glEdgeData* Left, glEdgeData* Right, int y, glImage* Texture, glImage* Depthbuffer, glImage* Framebuffer)
{
	int MinX = (int)ceilf(Left->EdgeX);
	int MaxX = (int)ceilf(Right->EdgeX);
	
	float PrestepX = MinX - Left->EdgeX;
	float OneOverZ = Left->OneOverZ + Gradients->OneOverStepZX * PrestepX;

	glVec2 TexCoord =
	{
		Left->TexCoordDX + Gradients->TexCoordStepXX * PrestepX,
		Left->TexCoordDY + Gradients->TexCoordStepYX * PrestepX
	};

	float Depth = Left->Depth + Gradients->DepthStepX * PrestepX;

	glVec3 Color = glAdd3(Left->Color, glMul3(Gradients->ColorStepX, GLVec3f(PrestepX)));

	for (int x = MinX; x < MaxX; x++)
	{
		if (glIsInDepthRange(Depth, x, y, Depthbuffer))
		{
			float z = 1.0 / OneOverZ;
			int SrcX = (int)((TexCoord.x * z) * (Texture->Width - 1) + 0.5);
			int SrcY = (int)((TexCoord.y * z) * (Texture->Height - 1) + 0.5);

			int Index = (SrcX + SrcY * Texture->Width) * Texture->ImageType;

			if (Index >= 0 && Index < Texture->Size)
			{
				glVec3 MixedColor = glMul3(Color, GLVec3(Texture->Data[Index] * GL_BYTE_FLOAT, Texture->Data[Index + 1] * GL_BYTE_FLOAT, Texture->Data[Index + 2] * GL_BYTE_FLOAT));
				glDrawPixel(x, y, glGetColor24(&MixedColor), Framebuffer);
			}
		}
			
		TexCoord.x += Gradients->TexCoordStepXX;
		TexCoord.y += Gradients->TexCoordStepYX;
		OneOverZ += Gradients->OneOverStepZX;
		Depth += Gradients->DepthStepX;

		Color = glAdd3(Color, Gradients->ColorStepX);
	}
}

void glDrawScanline(int UseColor, int UseTexture, glGradientsData* Gradients, glEdgeData* Left, glEdgeData* Right, int y, glImage* Texture, glImage* Depthbuffer, glImage* Framebuffer)
{
	if (UseColor && !UseTexture)
		glDrawColorScanline(Gradients, Left, Right, y, Depthbuffer, Framebuffer);
	else if (!UseColor && UseTexture)
		glDrawTextureScanline(Gradients, Left, Right, y, Texture, Depthbuffer, Framebuffer);
	else
		glDrawColorTextureScanline(Gradients, Left, Right, y, Texture, Depthbuffer, Framebuffer);
}
*/

#define modn(x, N) (((x < 0) ? ((x % N) + N) : x) % N)
/*
void glDrawTextureScanline(glTriangle* Triangle, glGradientsData* Gradients, glEdgeData* Left, glEdgeData* Right, int y)
{
	int MinX = (int)ceilf(Left->EdgeX);
	int MaxX = (int)ceilf(Right->EdgeX);

	float PrestepX = MinX - Left->EdgeX;
	//	float OneOverStepZX = (Right->OneOverZ - Left->OneOverZ) / (Right->EdgeX - Left->EdgeX);
	float OneOverZ = Left->OneOverZ + Gradients->OneOverStepZX * PrestepX;

	glVec2 TexCoord =
	{
		Left->TexCoordDX + Gradients->TexCoordStepXX * PrestepX,
		Left->TexCoordDY + Gradients->TexCoordStepYX * PrestepX
	};

	float Depth = Left->Depth + Gradients->DepthStepX * PrestepX;
	float LightAmt = Left->LightAmt + Gradients->LightAmtStepX * PrestepX;

	for (int x = MinX; x < MaxX; x++)
	{
		if (glIsInDepthRange(Depth, x, y, Triangle->Depthbuffer))
		{
			float z = 1.0 / OneOverZ;
			int SrcX = modn((int)((TexCoord.x * z) * (Triangle->Texture->Width - 1) + 0.5), Triangle->Texture->Width);
			int SrcY = modn((int)((TexCoord.y * z) * (Triangle->Texture->Height - 1) + 0.5), Triangle->Texture->Height);
			int Index = (SrcX + SrcY * Triangle->Texture->Width) * Triangle->Texture->ImageType;

			if (Index >= 0 && Index < Triangle->Texture->Size)
			{
				glVec3 MixedColor = glMul3(GLVec3f(LightAmt), GLVec3(Triangle->Texture->Data[Index] * GL_BYTE_FLOAT, Triangle->Texture->Data[Index + 1] * GL_BYTE_FLOAT, Triangle->Texture->Data[Index + 2] * GL_BYTE_FLOAT));
				glDrawPixel(x, y, glGetColor24(&MixedColor), Triangle->Framebuffer);
			}
		}

		TexCoord.x += Gradients->TexCoordStepXX;
		TexCoord.y += Gradients->TexCoordStepYX;
		OneOverZ += Gradients->OneOverStepZX;
		Depth += Gradients->DepthStepX;
		LightAmt += Gradients->LightAmtStepX;
	}
}
*/
void glDrawScanline(glTriangle* Triangle, glGradientsData* Gradients, glEdgeData* Left, glEdgeData* Right, int y)
{
	int MinX = (int)ceilf(Left->EdgeX);
	int MaxX = (int)ceilf(Right->EdgeX);

	float PrestepX = MinX - Left->EdgeX;

	float OneOverZ;
	glVec2 TexCoord;
	if (Triangle->Flags & GL_TRIANGLE_TEXTURE)
	{
		TexCoord = GLVec2(Left->TexCoordDX + Gradients->TexCoordStepXX * PrestepX,
			Left->TexCoordDY + Gradients->TexCoordStepYX * PrestepX);

		OneOverZ = Left->OneOverZ + Gradients->OneOverStepZX * PrestepX;
	}

	float Depth;
	if (Triangle->Flags & GL_TRIANGLE_DEPTHTEST)
		Depth = Left->Depth + Gradients->DepthStepX * PrestepX;

	float LightAmt;
	if (Triangle->Flags & GL_TRIANGLE_LIGHTING)
		LightAmt = Left->LightAmt + Gradients->LightAmtStepX * PrestepX;

	glVec3 Color;
	if (Triangle->Flags & GL_TRIANGLE_COLOR)
		Color = glAdd3(Left->Color, glMul3(Gradients->ColorStepX, GLVec3f(PrestepX)));

	glVec3 MixedColor;

	for (int x = MinX; x < MaxX; x++)
	{
		MixedColor = GLVec3f(1.0);

		//i guess works
		if (!(Triangle->Flags & GL_TRIANGLE_DEPTHTEST) ||
			glIsInDepthRange(Depth, x, y, Triangle->Depthbuffer))
		{
			if (Triangle->Flags & GL_TRIANGLE_TEXTURE)
			{
				float z = 1.0 / OneOverZ;
				int SrcX = modn((int)((TexCoord.x * z) * (Triangle->Texture->Width - 1) + 0.5), Triangle->Texture->Width);
				int SrcY = modn((int)((TexCoord.y * z) * (Triangle->Texture->Height - 1) + 0.5), Triangle->Texture->Height);
				int Index = (SrcX + SrcY * Triangle->Texture->Width) * Triangle->Texture->ImageType;

				if (Index >= 0 && Index < Triangle->Texture->Size)
					MixedColor = glMul3(MixedColor, GLVec3(Triangle->Texture->Data[Index] * GL_BYTE_FLOAT, Triangle->Texture->Data[Index + 1] * GL_BYTE_FLOAT, Triangle->Texture->Data[Index + 2] * GL_BYTE_FLOAT));
			}
			if (Triangle->Flags & GL_TRIANGLE_COLOR)
				MixedColor = glMul3P(&MixedColor, &Color);
			if (Triangle->Flags & GL_TRIANGLE_LIGHTING)
				MixedColor = glMul3(MixedColor, GLVec3f(LightAmt));
			
			glDrawPixel(x, y, glGetColor24(&MixedColor), Triangle->Framebuffer);
		}

		if (Triangle->Flags & GL_TRIANGLE_TEXTURE)
		{
			TexCoord.x += Gradients->TexCoordStepXX;
			TexCoord.y += Gradients->TexCoordStepYX;
			OneOverZ += Gradients->OneOverStepZX;
		}

		if (Triangle->Flags & GL_TRIANGLE_DEPTHTEST)
			Depth += Gradients->DepthStepX;
		if (Triangle->Flags & GL_TRIANGLE_LIGHTING)
			LightAmt += Gradients->LightAmtStepX;
		if (Triangle->Flags & GL_TRIANGLE_COLOR)
			Color = glAdd3(Color, Gradients->ColorStepX);
	}
}

void glScanEdge(glTriangle* Triangle, glGradientsData* Gradients, glEdgeData* a, glEdgeData* b, int Handedness)
{
	glEdgeData* Left = a;
	glEdgeData* Right = b;

	if (Handedness)
	{
		glEdgeData* Temp = Left;
		Left = Right;
		Right = Temp;
	}

	for (int y = b->EdgeStartY; y < b->EdgeEndY; y++)
	{
		glDrawScanline(Triangle, Gradients, Left, Right, y);

		glStepEdge(Triangle, Left);
		glStepEdge(Triangle, Right);
	}
}

void glDrawTriangle2D(glTriangle* Triangle)
{
	if (glTriangleAreaTimesTwo(&Triangle->v0, &Triangle->v2, &Triangle->v1) >= 0)
		return;

	glVertex TmpVert;
	if (Triangle->v2.Pos.y < Triangle->v1.Pos.y)
	{
		TmpVert = Triangle->v2;
		Triangle->v2 = Triangle->v1;
		Triangle->v1 = TmpVert;
	}

	if (Triangle->v1.Pos.y < Triangle->v0.Pos.y)
	{
		TmpVert = Triangle->v1;
		Triangle->v1 = Triangle->v0;
		Triangle->v0 = TmpVert;
	}

	if (Triangle->v2.Pos.y < Triangle->v1.Pos.y)
	{
		TmpVert = Triangle->v2;
		Triangle->v2 = Triangle->v1;
		Triangle->v1 = TmpVert;
	}

	glGradientsData Gradiants;
	glGradients(Triangle, &Triangle->v0, &Triangle->v1, &Triangle->v2, &Gradiants);

	glEdgeData TopToBottom;
	glEdge(Triangle, &Gradiants, &Triangle->v0, &Triangle->v2, 0, &TopToBottom);

	float TriArea = glTriangleAreaTimesTwo(&Triangle->v0, &Triangle->v2, &Triangle->v1);

	if (Triangle->v1.Pos.y == Triangle->v2.Pos.y)
	{
		glEdgeData TopToMiddle;
		glEdge(Triangle, &Gradiants, &Triangle->v0, &Triangle->v1, 0, &TopToMiddle);
		glScanEdge(Triangle, &Gradiants, &TopToBottom, &TopToMiddle, TriArea >= 0);
	}
	else if (Triangle->v0.Pos.y == Triangle->v1.Pos.y)
	{
		glEdgeData MiddleToBottom;
		glEdge(Triangle, &Gradiants, &Triangle->v1, &Triangle->v2, 1, &MiddleToBottom);
		glScanEdge(Triangle, &Gradiants, &TopToBottom, &MiddleToBottom, TriArea >= 0);
	}
	else
	{
		glEdgeData TopToMiddle;
		glEdge(Triangle, &Gradiants, &Triangle->v0, &Triangle->v1, 0, &TopToMiddle);
		glEdgeData MiddleToBottom;
		glEdge(Triangle, &Gradiants, &Triangle->v1, &Triangle->v2, 1, &MiddleToBottom);

		glScanEdge(Triangle, &Gradiants, &TopToBottom, &TopToMiddle, TriArea >= 0);
		glScanEdge(Triangle, &Gradiants, &TopToBottom, &MiddleToBottom, TriArea >= 0);
	}
}

void glDrawTriangle3D(glTriangle* Triangle)
{
	glMat4 ScreenSpaceTransform = glInitScreenSpaceTransform(Triangle->Framebuffer->Width * 0.5, Triangle->Framebuffer->Height * 0.5);

	Triangle->v0.Pos = glPerspectiveDivide(glMultiplyVec4Mat4P(&ScreenSpaceTransform, &Triangle->v0.Pos));
	Triangle->v1.Pos = glPerspectiveDivide(glMultiplyVec4Mat4P(&ScreenSpaceTransform, &Triangle->v1.Pos));
	Triangle->v2.Pos = glPerspectiveDivide(glMultiplyVec4Mat4P(&ScreenSpaceTransform, &Triangle->v2.Pos));

	/*
	* glDrawLine(Triangle->v0.Pos.x, Triangle->v0.Pos.y, Triangle->v1.Pos.x, Triangle->v1.Pos.y, glGetColor24(&Triangle->v0.Color), Triangle->Framebuffer);
	* glDrawLine(Triangle->v1.Pos.x, Triangle->v1.Pos.y, Triangle->v2.Pos.x, Triangle->v2.Pos.y, glGetColor24(&Triangle->v1.Color), Triangle->Framebuffer);
	* glDrawLine(Triangle->v2.Pos.x, Triangle->v2.Pos.y, Triangle->v0.Pos.x, Triangle->v0.Pos.y, glGetColor24(&Triangle->v2.Color), Triangle->Framebuffer);
	*/
//	glDrawLine(Triangle->v0.Pos.x, Triangle->v0.Pos.y, Triangle->v1.Pos.x, Triangle->v1.Pos.y, GL_COLOR_24(255, 0, 0), Triangle->Framebuffer);
//	glDrawLine(Triangle->v1.Pos.x, Triangle->v1.Pos.y, Triangle->v2.Pos.x, Triangle->v2.Pos.y, GL_COLOR_24(0, 255, 0), Triangle->Framebuffer);
//	glDrawLine(Triangle->v2.Pos.x, Triangle->v2.Pos.y, Triangle->v0.Pos.x, Triangle->v0.Pos.y, GL_COLOR_24(0, 0, 255), Triangle->Framebuffer);
	glDrawTriangle2D(Triangle);
}

void glClipPolygonComponent(int InSize, glVertex* InVertices, int ComponentIndex, float ComponentFactor, int* OutSize, glVertex* OutVertices)
{
	glVertex PrevVertex = InVertices[InSize - 1];
	float PrevComponent = (((float*)&(PrevVertex.Pos))[ComponentIndex]) * ComponentFactor;
	int PrevInside = PrevComponent <= PrevVertex.Pos.w;

	for (int i = 0; i < InSize; i++)
	{
		glVertex CurVertex = InVertices[i];
		float CurComponent = (((float*)&(CurVertex.Pos))[ComponentIndex]) * ComponentFactor;
		int CurInside = CurComponent <= CurVertex.Pos.w;

		if (CurInside ^ PrevInside)
		{
			float LerpAmt = (PrevVertex.Pos.w - PrevComponent) /
				((PrevVertex.Pos.w - PrevComponent) -
					(CurVertex.Pos.w - CurComponent));

			OutVertices[*OutSize] = glLerpVertex(&PrevVertex, &CurVertex, LerpAmt);
			*OutSize = *OutSize + 1;
		}

		if (CurInside)
		{
			OutVertices[*OutSize] = CurVertex;
			*OutSize = *OutSize + 1;
		}

		PrevVertex = CurVertex;
		PrevComponent = CurComponent;
		PrevInside = CurInside;
	}
}

int glClipPolygonAxis(int* InVertexSize, glVertex* InVertices, int* AuxillarySize, glVertex* AuxillaryList, int ComponentIndex)
{
	glClipPolygonComponent(*InVertexSize, InVertices, ComponentIndex, 1.0, AuxillarySize, AuxillaryList);
	*InVertexSize = 0;

	if (*AuxillarySize == 0)
		return 0;
	
	glClipPolygonComponent(*AuxillarySize, AuxillaryList, ComponentIndex, -1.0, InVertexSize, InVertices);
	*AuxillarySize = 0;

	if (*InVertexSize == 0)
		return 0;

	return 1;
}

void glDrawTriangle3DClipped(glTriangle* Triangle)
{
	int Inside0 = glInsideViewFrustum4(&Triangle->v0.Pos);
	int Inside1 = glInsideViewFrustum4(&Triangle->v1.Pos);
	int Inside2 = glInsideViewFrustum4(&Triangle->v2.Pos);
	if (Inside0 && Inside1 && Inside2)
	{
		glDrawTriangle3D(Triangle);
		return;
	}

//	if (!Inside0 && !Inside1 && !Inside2)
//		return;

	int VertexSize = 3;
	glVertex Vertices[9] = { Triangle->v0, Triangle->v1, Triangle->v2 };
	int AuxillarySize = 0;
	glVertex AuxillaryList[9];

	if (glClipPolygonAxis(&VertexSize, Vertices, &AuxillarySize, AuxillaryList, 0) &&
		glClipPolygonAxis(&VertexSize, Vertices, &AuxillarySize, AuxillaryList, 1) &&
		glClipPolygonAxis(&VertexSize, Vertices, &AuxillarySize, AuxillaryList, 2))
	{
		glVertex InitVertex = Vertices[0];

		for (int i = 1; i < VertexSize - 1; i++)
		{
			Triangle->v0 = InitVertex;
			Triangle->v1 = Vertices[i];
			Triangle->v2 = Vertices[i + 1];
			glDrawTriangle3D(Triangle);
		}
	}
}

//Image
#pragma pack(push, 1)

typedef struct
{
	uint16_t Type;
	uint32_t Size;
	uint16_t Resv1;
	uint16_t Resv2;
	uint32_t OffBits;
} BitmapFileHeader;

typedef struct
{
	uint32_t Size;
	int32_t Width;
	int32_t Height;
	uint16_t Planes;
	uint16_t Bits;
	uint32_t Compression;
	uint32_t SizeImage;
	int32_t XPelsPerMeter;
	int32_t YPelsPerMeter;
	uint32_t ClrUsed;
	uint32_t ClrImportant;
} BitmapInfoHeader;

typedef struct
{
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
	uint8_t Alpha;
} BitmapColorHeader;

#pragma pack(pop)

glImage glLoadImage(const char* Filename, int FlipVertical)
{
	BitmapFileHeader ImageHeader;
	BitmapInfoHeader ImageInfo;
	uint8_t* ImageData;

	FILE* File = fopen(Filename, "rb");
	if (!File)
		printf("Not Able to Load: %s\n", Filename);

	fread(&ImageHeader, sizeof(BitmapFileHeader), 1, File);
	fread(&ImageInfo, sizeof(BitmapInfoHeader), 1, File);

	fseek(File, ImageHeader.OffBits, SEEK_SET);

	uint32_t ImageSize = ImageInfo.Width * ImageInfo.Height * (ImageInfo.Bits == 32 ? 4 : 3);
	ImageInfo.SizeImage = ImageSize;

	ImageData = (uint8_t*)malloc(ImageSize);
	fread(ImageData, ImageSize, 1, File);

	fclose(File);

	/*
	printf("Width: %d\n", ImageInfo.Width);
	printf("Height: %d\n", ImageInfo.Height);
	printf("Size: %d\n", ImageInfo.SizeImage);
	printf("Bits: %d\n", ImageInfo.Bits);
	*/

	for (int32_t i = 0; i < ImageInfo.Width * ImageInfo.Height; i++)
	{
		int32_t Index = i * (ImageInfo.Bits == 32 ? 4 : 3);

		uint8_t B = ImageData[Index];
		uint8_t R = ImageData[Index + 2];

		ImageData[Index] = R;
		ImageData[Index + 2] = B;
	}

	if (FlipVertical)
	{
		const size_t Stride = ImageInfo.Width * (ImageInfo.Bits == 32 ? 4 : 3);
		unsigned char* Row = (unsigned char*)malloc(Stride);
		unsigned char* Low = ImageData;
		unsigned char* High = &ImageData[(ImageInfo.Height - 1) * Stride];

		for (; Low < High; Low += Stride, High -= Stride)
		{
			memcpy(Row, Low, Stride);
			memcpy(Low, High, Stride);
			memcpy(High, Row, Stride);
		}
		free(Row);
	}

	glImage Image;
	Image.Width = ImageInfo.Width;
	Image.Height = ImageInfo.Height;
	Image.ImageType = (ImageInfo.Bits == 32 ? 4 : 3);
	Image.Size = ImageSize;
	Image.Data = ImageData;

	return Image;
}