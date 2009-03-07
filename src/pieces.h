/*
 * TEsTris
 *
 * Created by Simon Busard 22.08.2007
 * 
 * pieces.h
 * --------
 * Pieces definition 
 */

/* 
 * Copyright (C) 2008 Busard Simon
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef PIECES
#define PIECES

enum Piece_bloc
{
    PCMPTY,SQR1,BAR1,BAR2,L1,L2,L3,L4,LINV1,LINV2,LINV3,LINV4,
    S1,S2,SINV1,SINV2,DP1,DP2,DP3,DP4
};
enum Color
{
    CL_MPT,CL_GREY1,CL_GREY2,CL_GREY3,CL_RED1,CL_RED2,CL_RED3,
    CL_GREEN1,CL_GREEN2,CL_GREEN3,CL_YELL1,CL_YELL2,CL_YELL3,
    CL_VIO1,CL_VIO2,CL_VIO3,CL_LBLU1,CL_LBLU2,CL_LBLU3,
    CL_BLUE1,CL_BLUE2,CL_BLUE3
};

// Useful for turn and display
#define PC_ASS_SIZE 20
#define PC_ASSOC {	{PCMPTY,PCMPTY,PCMPTY,CL_MPT,CL_MPT,CL_MPT},	\
			{SQR1,SQR1,SQR1,CL_GREY1,CL_GREY2,CL_GREY3},	\
			{BAR2,BAR1,BAR2,CL_RED1,CL_RED2,CL_RED3}, 	\
			{BAR1,BAR2,BAR1,CL_RED1,CL_RED2,CL_RED3},	\
			{L4,L1,L2,CL_GREEN1,CL_GREEN2,CL_GREEN3},	\
			{L1,L2,L3,CL_GREEN1,CL_GREEN2,CL_GREEN3},	\
			{L2,L3,L4,CL_GREEN1,CL_GREEN2,CL_GREEN3},	\
			{L3,L4,L1,CL_GREEN1,CL_GREEN2,CL_GREEN3},	\
			{LINV4,LINV1,LINV2,CL_YELL1,CL_YELL2,CL_YELL3},	\
			{LINV1,LINV2,LINV3,CL_YELL1,CL_YELL2,CL_YELL3},	\
			{LINV2,LINV3,LINV4,CL_YELL1,CL_YELL2,CL_YELL3},	\
			{LINV3,LINV4,LINV1,CL_YELL1,CL_YELL2,CL_YELL3},	\
			{S2,S1,S2,CL_VIO1,CL_VIO2,CL_VIO3},		\
			{S1,S2,S1,CL_VIO1,CL_VIO2,CL_VIO3},		\
			{SINV2,SINV1,SINV2,CL_LBLU1,CL_LBLU2,CL_LBLU3},	\
			{SINV1,SINV2,SINV1,CL_LBLU1,CL_LBLU2,CL_LBLU3},	\
			{DP4,DP1,DP2,CL_BLUE1,CL_BLUE2,CL_BLUE3},	\
			{DP1,DP2,DP3,CL_BLUE1,CL_BLUE2,CL_BLUE3},	\
			{DP2,DP3,DP4,CL_BLUE1,CL_BLUE2,CL_BLUE3},	\
			{DP3,DP4,DP1,CL_BLUE1,CL_BLUE2,CL_BLUE3}	}

#define NB_COLORS 22
#define COLORS {	{CL_MPT,0,0,0},		\
			{CL_GREY1,255,255,255},	\
			{CL_GREY2,180,180,180},	\
			{CL_GREY3,50,50,50},	\
			{CL_RED1,255,0,0},	\
			{CL_RED2,180,0,0},	\
			{CL_RED3,50,0,0},	\
			{CL_GREEN1,0,255,0},	\
			{CL_GREEN2,0,180,0},	\
			{CL_GREEN3,0,50,0},	\
			{CL_YELL1,255,255,0},	\
			{CL_YELL2,180,180,0},	\
			{CL_YELL3,50,50,0},	\
			{CL_VIO1,255,0,255},	\
			{CL_VIO2,180,0,180},	\
			{CL_VIO3,50,0,50},	\
			{CL_LBLU1,0,255,255},	\
			{CL_LBLU2,0,180,180},	\
			{CL_LBLU3,0,50,50},	\
			{CL_BLUE1,0,0,255},	\
			{CL_BLUE2,0,0,180},	\
			{CL_BLUE3,0,0,75}	}
			

// Pieces
#define PC_NB_LBLC 4
#define PC_NB_HBLC 4
#define PC_NB_BLC PC_NB_LBLC * PC_NB_HBLC
#define PC_NB 28	// Useful for add
#define PC_REAL_NB 20	// Useful for pc_init
// Empty
#define PC_EMPTY {	{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
// Square
#define PC_SQR1 {	{CL_MPT,CL_GREY1,CL_GREY1,CL_MPT}, 	\
			{CL_MPT,CL_GREY1,CL_GREY1,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
// Bar
#define PC_BAR1 {	{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_RED1,CL_RED1,CL_RED1,CL_RED1}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
#define PC_BAR2 {	{CL_MPT,CL_RED1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_RED1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_RED1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_RED1,CL_MPT,CL_MPT}  	}
// L
#define PC_L1 {		{CL_MPT,CL_GREEN1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_GREEN1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_GREEN1,CL_GREEN1,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
#define PC_L2 {		{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_GREEN1,CL_GREEN1,CL_GREEN1}, \
			{CL_MPT,CL_GREEN1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
#define PC_L3 {		{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_GREEN1,CL_GREEN1,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_GREEN1,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_GREEN1,CL_MPT}  	}
#define PC_L4 {		{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_MPT,CL_GREEN1,CL_MPT}, 	\
			{CL_GREEN1,CL_GREEN1,CL_GREEN1,CL_MPT}, \
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
// L inv
#define PC_LINV1 {	{CL_MPT,CL_MPT,CL_YELL1,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_YELL1,CL_MPT}, 	\
			{CL_MPT,CL_YELL1,CL_YELL1,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
#define PC_LINV2 {	{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_YELL1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_YELL1,CL_YELL1,CL_YELL1}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
#define PC_LINV3 {	{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_YELL1,CL_YELL1,CL_MPT}, 	\
			{CL_MPT,CL_YELL1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_YELL1,CL_MPT,CL_MPT}  	}
#define PC_LINV4 {	{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_YELL1,CL_YELL1,CL_YELL1,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_YELL1,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
// S
#define PC_S1 {		{CL_MPT,CL_VIO1,CL_VIO1,CL_MPT}, 	\
			{CL_VIO1,CL_VIO1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
#define PC_S2 {		{CL_MPT,CL_VIO1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_VIO1,CL_VIO1,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_VIO1,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
// S inv
#define PC_SINV1 {	{CL_LBLU1,CL_LBLU1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_LBLU1,CL_LBLU1,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
#define PC_SINV2 {	{CL_MPT,CL_MPT,CL_LBLU1,CL_MPT}, 	\
			{CL_MPT,CL_LBLU1,CL_LBLU1,CL_MPT}, 	\
			{CL_MPT,CL_LBLU1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
// demi plus
#define PC_DP1 {	{CL_MPT,CL_BLUE1,CL_MPT,CL_MPT}, 	\
			{CL_BLUE1,CL_BLUE1,CL_BLUE1,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}, 		\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
#define PC_DP2 {	{CL_MPT,CL_BLUE1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_BLUE1,CL_BLUE1,CL_MPT}, 	\
			{CL_MPT,CL_BLUE1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}
#define PC_DP3 {	{CL_MPT,CL_MPT,CL_MPT,CL_MPT},		\
			{CL_BLUE1,CL_BLUE1,CL_BLUE1,CL_MPT},	\
			{CL_MPT,CL_BLUE1,CL_MPT,CL_MPT},	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}		}
#define PC_DP4 {	{CL_MPT,CL_BLUE1,CL_MPT,CL_MPT}, 	\
			{CL_BLUE1,CL_BLUE1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_BLUE1,CL_MPT,CL_MPT}, 	\
			{CL_MPT,CL_MPT,CL_MPT,CL_MPT}  		}

#endif

