/**
 *******************************************************************************
 * @file        slib.h
 * @author      ABOV R&D Division
 * @brief       
 *
 * Copyright 2023 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _SLIB_H_
#define	_SLIB_H_

#define	TERMINATE_CHAR	'\r'


void	init_slib(void);
int		getstring(void);
char	*scani(char *s, unsigned int *result);
char	*scans(char *s,char *result);

void	htod(int hvalue,int n);
void	ftod(double fvalue,int n,int e);

extern	char	InData[];
//extern	char	OutData[];
extern	int	InFlag;
//extern	int	OutFlag;
extern	int	InCount,OutCount;

#endif
