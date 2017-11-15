#include "stdafx.h"
#include "SPLine.h"
#include "BaseReturn_def.h"

CSPLine::CSPLine()
{
}


CSPLine::~CSPLine()
{
}

//-------------------------------------------------------------------------------------------------
// 高斯列主元消去法解线性方程组
//-------------------------------------------------------------------------------------------------
// n		方程个数
// pA		方程组系数，n行，n+1列 
// pResult	方程组的解
//-------------------------------------------------------------------------------------------------

short CSPLine::Gauss(long n, double *pA, double *pResult)
{
	long i, j, k, maxLine;
	double maxData, temp, coef;

	// 消元
	for (i = 1; i < n; ++i)												// 遍历列
	{
		maxLine = i - 1;												// 寻找列主元
		maxData = pA[(i - 1)*(n + 1) + (i - 1)];
		for (j = i; j<n; ++j)
		{
			if (pA[j*(n + 1) + (i - 1)] > maxData)
			{
				maxLine = j;
				maxData = pA[j*(n + 1) + (i - 1)];
			}
		}

		if (0 == maxData)
		{
			return CMD_ERROR_PARAMETER;
		}

		if (maxLine != i - 1)										// 交换行
		{
			for (j = i - 1; j <= n; ++j)
			{
				temp = pA[(i - 1)*(n + 1) + j];
				pA[(i - 1)*(n + 1) + j] = pA[maxLine*(n + 1) + j];
				pA[maxLine*(n + 1) + j] = temp;
			}
		}

		for (j = i; j < n; ++j)											// 遍历行
		{
			for (k = i; k <= n; ++k)										// 遍历元素
			{
				coef = pA[j*(n + 1) + (i - 1)] / pA[(i - 1)*(n + 1) + (i - 1)];
				pA[j*(n + 1) + k] -= coef * pA[(i - 1)*(n + 1) + k];
			}
		}
	}

	// 回代
	for (i = n - 1; i >= 0; --i)												// 反向遍历行
	{
		pResult[i] = pA[i*(n + 1) + n];
		for (j = n - 1; j > i; --j)											// 反向遍历元素
		{
			pResult[i] -= pResult[j] * pA[i*(n + 1) + j];
		}

		if (0 == pA[i*(n + 1) + i])
		{
			return 1;
		}

		pResult[i] /= pA[i*(n + 1) + i];
	}

	return CMD_SUCCESS;
}

//-------------------------------------------------------------------------------------------------
// 3次样条插值，指定边界的一阶导数
//-------------------------------------------------------------------------------------------------
// y = yn + an(x-xn) + bn(x-xn)^2 + cn(x-xn)^3
//-------------------------------------------------------------------------------------------------
// n			点数
// pX,pY		节点坐标
// dy0,dyn		起点和终点的一阶导数
// pG			计算结果，3次样条的系数a
// pMu			计算结果，3次样条的系数b
// pLambda		计算结果，3次样条的系数c
//-------------------------------------------------------------------------------------------------

short CSPLine::SplineComplete(long n, const double *pX, const double *pY, double *pG, double *pMu, double *pLambda, double dy0, double dyn)
{
	double h, hi, s, b, c;
	long i;

	if (n < 2)
	{
		return CMD_ERROR_PARAMETER;
	}

	// pX必须单调增
	for (i = 0; i < n - 1; ++i)
	{
		if (pX[i + 1] <= pX[i])
		{
			return CMD_ERROR_PARAMETER;
		}
	}

	if (2 == n)
	{
		goto lbl_spline_first_get_abc;
	}

	// 计算中间n-2个点[1..n-2]的lambda, mu, g,
	h = pX[1] - pX[0];

	for (i = 1; i <= (n - 2); ++i)
	{
		hi = pX[i + 1] - pX[i];
		pLambda[i] = hi / (hi + h);
		pMu[i] = 1 - pLambda[i];
		pG[i] = 3 * (pMu[i] * (pY[i + 1] - pY[i]) / hi + pLambda[i] * (pY[i] - pY[i - 1]) / h);

		h = hi;
	}

	pG[1] = pG[1] - pLambda[1] * dy0;
	pG[(n - 2)] = pG[(n - 2)] - pMu[(n - 2)] * dyn;

	// 计算中间n-2个点[1..n-2]的速度, 计算结果存储在pG中
	pMu[1] = pMu[1] / 2;
	pG[1] = pG[1] / 2;

	if (3 == n)
	{
		goto lbl_spline_first_get_abc;
	}

	// 消元
	for (i = 2; i <= (n - 2) - 1; ++i)
	{
		s = 2 - pLambda[i] * pMu[i - 1];
		pMu[i] = pMu[i] / s;
		pG[i] = (pG[i] - pLambda[i] * pG[i - 1]) / s;
	}

	// 计算m(n-2)
	s = 2 - pLambda[(n - 2)] * pMu[(n - 2) - 1];
	pG[(n - 2)] = (pG[(n - 2)] - pLambda[(n - 2)] * pG[(n - 2) - 1]) / s;

	// 回代
	for (i = (n - 2) - 1; i >= 1; --i)
	{
		pG[i] = pG[i] - pMu[i] * pG[i + 1];
	}

lbl_spline_first_get_abc:

	pG[0] = dy0;
	pG[n - 1] = dyn;

	// 计算各段的a,b,c
	for (i = 0; i <= (n - 2); ++i)
	{
		hi = pX[i + 1] - pX[i];
		b = (3 * (pY[i + 1] - pY[i]) / hi - pG[i + 1] - 2 * pG[i]) / hi;
		c = (pG[i + 1] + pG[i] - 2 * (pY[i + 1] - pY[i]) / hi) / (hi*hi);

		pMu[i] = b;
		pLambda[i] = c;
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------
// 3次样条插值，周期函数
//-------------------------------------------------------------------------------------------------
// y = yn + an(x-xn) + bn(x-xn)^2 + cn(x-xn)^3
//-------------------------------------------------------------------------------------------------
// n			点数
// pX,pY		节点坐标
// pLambda		计算结果，3次样条的系数c
// pMu			计算结果，3次样条的系数b
// pG			计算结果，3次样条的系数a
//-------------------------------------------------------------------------------------------------

short CSPLine::SplinePeriodic(long n, const double *pX, const double *pY, double *pG, double *pMu, double *pLambda)
{
	double h, hi, s, last, b, c;
	double coef[3][4];
	long i;
	short rtn;

	if (n < 2)
	{
		return CMD_ERROR_PARAMETER;
	}

	// pX必须单调增
	for (i = 0; i < n - 1; ++i)
	{
		if (pX[i + 1] <= pX[i])
		{
			return CMD_ERROR_PARAMETER;
		}
	}

	// pY[0] = pY[n-1]
	if (pY[0] != pY[n - 1])
	{
		return CMD_ERROR_PARAMETER;
	}

	if (2 == n)
	{
		pG[0] = pG[1] = 0;
		goto lbl_spline_periodic_get_abc;
	}

	// 计算中间n-1个点[1..n-1]的lambda, mu, g
	h = pX[1] - pX[0];

	for (i = 1; i <= (n - 2); ++i)
	{
		hi = pX[i + 1] - pX[i];
		pLambda[i] = hi / (hi + h);
		pMu[i] = 1 - pLambda[i];
		pG[i] = 3 * (pMu[i] * (pY[i + 1] - pY[i]) / hi + pLambda[i] * (pY[i] - pY[i - 1]) / h);

		h = hi;
	}

	// 计算终点的lambda,mu,g
	h = pX[1] - pX[0];
	hi = pX[(n - 1)] - pX[(n - 1) - 1];

	// lambda(n)=h(0)/(h(0)+h(n-1))
	pLambda[(n - 1)] = h / (h + hi);

	// m(n)=h(n-1)/(h(0)+h(n-1))
	pMu[(n - 1)] = 1 - pLambda[(n - 1)];

	// g(n)=3*( mu(n)*(y(1)-y(0))/(x(1)-x(0)) + lambda(n)*(y(n)-y(n-1))/(x(n)-x(n-1)) )
	pG[(n - 1)] = 3 * (pMu[(n - 1)] * (pY[1] - pY[0]) / h + pLambda[(n - 1)] * (pY[(n - 1)] - pY[(n - 1) - 1]) / hi);

	if (3 == n)
	{
		pG[0] = (2 * pG[2] - pG[1]) / 3;
		pG[1] = (2 * pG[1] - pG[2]) / 3;
		pG[2] = pG[0];
		goto lbl_spline_periodic_get_abc;
	}

	// 计算中间n-1个点[1..n-2]的导数, 计算结果存储在pG中
	pMu[1] = pMu[1] / 2;
	pG[1] = pG[1] / 2;
	pLambda[1] = pLambda[1] / 2;

	last = 2;

	// 消元
	for (i = 2; i <= (n - 1) - 2; ++i)
	{
		// 第i行消元
		s = 2 - pLambda[i] * pMu[i - 1];
		pMu[i] = pMu[i] / s;								// 主对角线系数归1
		pG[i] = (pG[i] - pLambda[i] * pG[i - 1]) / s;
		pLambda[i] = -pLambda[i] * pLambda[i - 1] / s;			// 注意，当前行lambda改为存储最后一列系数

		// 最后一行消元
		pG[(n - 1)] = pG[(n - 1)] - pMu[(n - 1)] * pG[i - 1];
		last = last - pMu[(n - 1)] * pLambda[i - 1];				// last表示矩阵右下角
		pMu[(n - 1)] = -pMu[(n - 1)] * pMu[i - 1];				// 注意，最后一行mu表示第i列的系数
	}

	// 得到m(n-2), m(n-1), m(n)的线性方程组
	coef[0][0] = 1;					coef[0][1] = pMu[(n - 1) - 2];	coef[0][2] = pLambda[(n - 1) - 2];	coef[0][3] = pG[(n - 1) - 2];
	coef[1][0] = pLambda[(n - 1) - 1];	coef[1][1] = 2;				coef[1][2] = pMu[(n - 1) - 1];		coef[1][3] = pG[(n - 1) - 1];;
	coef[2][0] = pMu[(n - 1)];			coef[2][1] = pLambda[(n - 1)];	coef[2][2] = last;				coef[2][3] = pG[(n - 1)];

	rtn = Gauss(3, &(coef[0][0]), &(pG[n - 3]));

	if (0 != rtn)
	{
		return rtn;
	}

	pG[0] = pG[(n - 1)];

	// 回代
	for (i = (n - 1) - 3; i >= 1; --i)
	{
		pG[i] = pG[i] - pLambda[i] * pG[(n - 1)] - pMu[i] * pG[i + 1];
	}

lbl_spline_periodic_get_abc:

	// 计算各段的a,b,c
	for (i = 0; i <= (n - 2); ++i)
	{
		hi = pX[i + 1] - pX[i];
		b = (3 * (pY[i + 1] - pY[i]) / hi - pG[i + 1] - 2 * pG[i]) / hi;
		c = (pG[i + 1] + pG[i] - 2 * (pY[i + 1] - pY[i]) / hi) / (hi*hi);

		pMu[i] = b;
		pLambda[i] = c;
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------
// 3次样条插值，Hermite
//-------------------------------------------------------------------------------------------------
// y = yn + an(x-xn) + bn(x-xn)^2 + cn(x-xn)^3
//-------------------------------------------------------------------------------------------------
// n			点数
// pX,pY		节点坐标
// pV			节点一阶导数
// pC,pB,pA		计算结果，3次样条的系数
//-------------------------------------------------------------------------------------------------

short CSPLine::Hermite(long n, const double *pX, const double *pY, const double *pV, double *pA, double *pB, double *pC)
{
	long i;
	double deltaX, deltaY;

	if (n < 2)
	{
		return CMD_ERROR_PARAMETER;;
	}

	// pX必须单调增
	for (i = 0; i < n - 1; ++i)
	{
		if (pX[i + 1] <= pX[i])
		{
			return CMD_ERROR_PARAMETER;;
		}
	}

	for (i = 0; i < n - 1; ++i)
	{
		deltaY = pY[i + 1] - pY[i];
		deltaX = pX[i + 1] - pX[i];

		pA[i] = pV[i];
		pB[i] = (3 * deltaY / deltaX - pV[i + 1] - 2 * pV[i]) / deltaX;
		pC[i] = (pV[i + 1] + pV[i] - 2 * deltaY / deltaX) / (deltaX*deltaX);
	}

	return CMD_SUCCESS;
}

// 速度前瞻，调整各借节点速度
short CSPLine::PvLookahead(long n, double *pPos, double *pVel, double *pAcc, double *pDec)
{
	long i, index;
	double s, v1, v2, acc, dec;
	double sabs, v1abs, v2abs;

	for (i = 0; i < n - 1; ++i)
	{
		index = i;

		while (1)
		{
			if (index < 0)
			{
				break;;
			}

			s = pPos[index + 1] - pPos[index];

			v1 = pVel[index];
			v2 = pVel[index + 1];

			acc = pAcc[index];
			dec = pDec[index];

			sabs = fabs(s);

			v1abs = fabs(v1);
			v2abs = fabs(v2);

			// 如果方向相反，总是有解
			if (v1*v2 < 0)
			{
				break;
			}

			// 如果速度相同，只要段长不是0，总是有解
			if (v1 == v2)
			{
				break;
			}

			// 方向相同
			if (v1abs < v2abs)
			{
				// 段长足够
				if (2 * acc*sabs >= v2*v2 - v1*v1)
				{
					break;
				}

				v2 = sqrt(2 * acc*sabs - v1*v1);

				if (s < 0)
				{
					v2 = -v2;
				}

				pVel[index + 1] = v2;

				break;
			}
			else
			{
				// 段长足够
				if (2 * dec*sabs >= v1*v1 - v2*v2)
				{
					break;
				}

				v1 = sqrt(2 * dec*sabs - v2*v2);

				if (s < 0)
				{
					v1 = -v1;
				}

				pVel[index] = v1;

				--index;
			}
		}
	}

	return 0;
}

//-----------------------------------------------------------------------------
// 删除x相同的数据点
//-----------------------------------------------------------------------------
// 如果float(x[i]) == float(x[i+1])，删除x[i+1]
//-----------------------------------------------------------------------------
short CSPLine::DeleteRedundant(long n, double *pX, double *pY, double *pV, long *pCount)
{
	long i, j, count;
	float x1, x2;

	count = n;

	i = 0;

	while (i < count - 1)
	{
		x1 = (float)pX[i];
		x2 = (float)pX[i + 1];

		if (x1 == x2)
		{
			for (j = i + 1; j < count - 1; ++j)
			{
				pX[j] = pX[j + 1];
				pY[j] = pY[j + 1];
				pV[j] = pV[j + 1];
			}

			--count;
		}
		else
		{
			++i;
		}
	}

	*pCount = count;

	return 0;
}


//-----------------------------------------------------------------------------
// 根据百分比将梯形曲线转换为S曲线
//-----------------------------------------------------------------------------
// 输入2个点的PVT
// 输出2、3、4个点的PVT
//-----------------------------------------------------------------------------
short CSPLine::PercentSplit(long n, double *pTime, double *pPos, double *pVel, double *pPercent, long *pCount, double *pOutTime, double *pOutPos, double *pOutVel)
{
	long i, index;
	double p;
	double v1, v2;
	double dx, dy, dv;
	double deltaXa, deltaXb;
	double deltaYa, deltaYb;
	double xa, xb, ya, yb, va, vb;

	if (n < 2)
	{
		return CMD_ERROR_PARAMETER;
	}

	index = 0;

	pOutTime[index] = pTime[0];
	pOutPos[index] = pPos[0];
	pOutVel[index] = pVel[0];

	++index;

	for (i = 0; i < n - 1; ++i)
	{
		p = pPercent[i] / 100;

		if (0 == p)
		{
			pOutTime[index] = pTime[i + 1];
			pOutPos[index] = pPos[i + 1];
			pOutVel[index] = pVel[i + 1];

			++index;

			continue;
		}

		v1 = pVel[i];
		v2 = pVel[i + 1];

		dv = v2 - v1;
		if (0 == dv)
		{
			pOutTime[index] = pTime[i + 1];
			pOutPos[index] = pPos[i + 1];
			pOutVel[index] = pVel[i + 1];

			++index;

			continue;
		}

		dx = pTime[i + 1] - pTime[i];
		dy = pPos[i + 1] - pPos[i];

		deltaXa = p*dx / 2;
		deltaXb = (1 - p)*dx;

		xa = pTime[i] + deltaXa;
		xb = xa + deltaXb;

		va = ((4 - 3 * p)*v1 + p*v2) / (4 - 2 * p);
		vb = (p*v1 + (4 - 3 * p)*v2) / (4 - 2 * p);

		deltaYa = v1*deltaXa + p*p / (2 - p) / 12 * dv*dx;
		deltaYb = (1 - p) / 2 * (v1 + v2)*dx;

		ya = pPos[i] + deltaYa;
		yb = ya + deltaYb;

		pOutTime[index] = xa;
		pOutPos[index] = ya;
		pOutVel[index] = va;

		++index;

		if (deltaXb > 0)
		{
			pOutTime[index] = xb;
			pOutPos[index] = yb;
			pOutVel[index] = vb;

			++index;
		}

		pOutTime[index] = pTime[i + 1];
		pOutPos[index] = pPos[i + 1];
		pOutVel[index] = pVel[i + 1];

		++index;
	}

	// 删除冗余数据
	DeleteRedundant(index, pOutTime, pOutPos, pOutVel, pCount);

	return 0;
}

//-----------------------------------------------------------------------------
// v1和v2符号相同
//-----------------------------------------------------------------------------
// s相邻2点之间的位移，可正可负
// v1起点速度，v2终点速度，可正可负
// v相邻2点之间的最大速度，正数
// acc相邻2点之间的加速度
// dec相邻2点之间的减速度
// pTime拆分出的各段时间增量
// pPos拆分出的各段位移增量
// pVel拆分出的各段终点速度
// 返回拆分出的段数
//-----------------------------------------------------------------------------
short CSPLine::PvSplitSame(double s, double v1, double v2, double v, double acc, double dec, long *pCount, double *pTime, double *pPos, double *pVel)
{
	double sa, sd;
	double sabs, v1abs, v2abs;

	sabs = fabs(s);
	v1abs = fabs(v1);
	v2abs = fabs(v2);

	sa = (v*v - v1*v1) / 2 / acc;
	sd = (v*v - v2*v2) / 2 / dec;

	// 能够达到最大速度
	if (sabs > sa + sd)
	{
		// 只有匀速段
		if ((v1abs == v) && (v2abs == v))
		{
			pTime[0] = sabs / v;
			pPos[0] = s;
			pVel[0] = v1;

			*pCount = 1;
			return 0;
		}

		// 加速段、匀速段
		if ((v1abs < v) && (v2abs == v))
		{
			pTime[0] = (v - v1abs) / acc;
			pTime[1] = (sabs - sa) / v;

			pVel[0] = v2;
			pVel[1] = v2;

			if (s > 0)
			{
				pPos[0] = sa;
				pPos[1] = sabs - sa;
			}
			else
			{
				pPos[0] = -sa;
				pPos[1] = -(sabs - sa);
			}

			*pCount = 2;
			return 0;
		}

		// 匀速段、减速段
		if ((v1abs == v) && (v2abs < v))
		{
			pTime[0] = (sabs - sd) / v;
			pTime[1] = (v - v2abs) / dec;

			pVel[0] = v1;
			pVel[1] = v2;

			if (s > 0)
			{
				pPos[0] = sabs - sd;
				pPos[1] = sd;
			}
			else
			{
				pPos[0] = -(sabs - sd);
				pPos[1] = -sd;
			}

			*pCount = 2;
			return 0;
		}

		// 加速段、匀速段、减速段
		pTime[0] = (v - v1abs) / acc;
		pTime[1] = (sabs - sa - sd) / v;
		pTime[2] = (v - v2abs) / dec;

		if (s > 0)
		{
			pPos[0] = sa;
			pPos[1] = sabs - sa - sd;
			pPos[2] = sd;

			pVel[0] = v;
			pVel[1] = v;
			pVel[2] = v2;
		}
		else
		{
			pPos[0] = -sa;
			pPos[1] = -(sabs - sa - sd);
			pPos[2] = -sd;

			pVel[0] = -v;
			pVel[1] = -v;
			pVel[2] = v2;
		}

		*pCount = 3;
		return 0;
	}

	// 计算实际能够达到的最大速度
	v = sqrt((dec*v1*v1 + acc*v2*v2 + 2 * acc*dec*sabs) / (acc + dec));

	pTime[0] = (v - v1abs) / acc;
	pTime[1] = (v - v2abs) / dec;

	sa = (v*v - v1*v1) / 2 / acc;

	if (s > 0)
	{
		pPos[0] = sa;
		pPos[1] = sabs - sa;

		pVel[0] = v;
	}
	else
	{
		pPos[0] = -sa;
		pPos[1] = -(sabs - sa);

		pVel[0] = -v;
	}

	pVel[1] = v2;

	*pCount = 2;
	return 0;
}


//-----------------------------------------------------------------------------
// v1和v2符号相反
//-----------------------------------------------------------------------------
// s相邻2点之间的位移，可正可负
// v1起点速度，v2终点速度，可正可负
// v相邻2点之间的最大速度，正数
// acc相邻2点之间的加速度
// dec相邻2点之间的减速度
// pTime拆分出的各段时间增量
// pPos拆分出的各段位移增量
// pVel拆分出的各段终点速度
// 返回拆分出的段数
//-----------------------------------------------------------------------------
short CSPLine::PvSplitDifferent(double s, double v1, double v2, double v, double acc, double dec, long *pCount, double *pTime, double *pPos, double *pVel)
{
	double sabs, v1abs, v2abs;
	double s1, s2;
	long count;

	sabs = fabs(s);
	v1abs = fabs(v1);
	v2abs = fabs(v2);

	if (v1 > 0)
	{
		s1 = v1*v1 / 2 / dec;
		s2 = -v2*v2 / 2 / acc;

		if (s > s1 + s2)
		{
			s1 = s - s2;
			PvSplitSame(s1, v1, 0, v, acc, dec, &count, pTime, pPos, pVel);

			pTime[count] = fabs(v2) / acc;
			pPos[count] = s2;
			pVel[count] = v2;

			*pCount = count + 1;

			return 0;
		}
		else if (s < s1 + s2)
		{
			pTime[0] = v1 / dec;
			pPos[0] = s1;
			pVel[0] = 0;

			s2 = s - s1;
			PvSplitSame(s2, 0, v2, v, acc, dec, &count, &pTime[1], &pPos[1], &pVel[1]);

			*pCount = count + 1;
			return 0;
		}
	}
	else
	{
		s1 = -v1*v1 / 2 / dec;
		s2 = v2*v2 / 2 / acc;

		if (s > s1 + s2)
		{
			pTime[0] = fabs(v1) / dec;
			pPos[0] = s1;
			pVel[0] = 0;

			s2 = s - s1;
			PvSplitSame(s2, 0, v2, v, acc, dec, &count, &pTime[1], &pPos[1], &pVel[1]);

			*pCount = count + 1;
			return 0;
		}
		else if (s < s1 + s2)
		{
			s1 = s - s2;
			PvSplitSame(s1, v1, 0, v, acc, dec, &count, pTime, pPos, pVel);

			pTime[count] = v2 / acc;
			pPos[count] = s2;
			pVel[count] = v2;

			*pCount = count + 1;
			return 0;
		}
	}

	pTime[0] = fabs(v1) / dec;
	pTime[1] = fabs(v2) / acc;

	pPos[0] = s1;
	pPos[1] = s2;

	pVel[0] = 0;
	pVel[1] = v2;

	*pCount = 2;
	return 0;
}

//-----------------------------------------------------------------------------
// 计算相邻2点之间的加减速曲线
//-----------------------------------------------------------------------------
// 输入n个点的PVT
// 拆出count个点的PVT，相邻2点之间速度都是线性
//-----------------------------------------------------------------------------
short CSPLine::PvSplit(long n, double time, double *pPos, double *pVel, double *pVelMax, double *pAcc, double *pDec, long *pCount, double *pOutTime, double *pOutPos, double *pOutVel)
{
	long i, j, index, count;
	double s, v1, v2, v, acc, dec;
	double dt[4], ds[4], vel[4];

	pOutTime[0] = time;
	pOutPos[0] = pPos[0];
	pOutVel[0] = pVel[0];

	index = 1;

	for (i = 0; i < n - 1; ++i)
	{
		s = pPos[i + 1] - pPos[i];

		v1 = pVel[i];
		v2 = pVel[i + 1];

		v = pVelMax[i];

		acc = pAcc[i];
		dec = pDec[i];

		// 方向相反
		if (v1*v2 < 0)
		{
			PvSplitDifferent(s, v1, v2, v, acc, dec, &count, dt, ds, vel);
		}
		// 方向相同
		else
		{
			PvSplitSame(s, v1, v2, v, acc, dec, &count, dt, ds, vel);
		}

		for (j = 0; j < count; ++j)
		{
			pOutTime[index] = pOutTime[index - 1] + dt[j];
			pOutPos[index] = pOutPos[index - 1] + ds[j];
			pOutVel[index] = vel[j];

			++index;
		}
	}

	DeleteRedundant(index, pOutTime, pOutPos, pOutVel, pCount);

	return 0;
}