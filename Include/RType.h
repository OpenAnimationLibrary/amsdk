//BC  4/13/2004  \Bob110\Include\RType.h
#pragma once

constexpr UCHAR RSPHERE = 5U;
constexpr UCHAR RCONE = 6U;
constexpr UCHAR RCYLINDER = 7U;
constexpr UCHAR RBOX = 8U;
constexpr UCHAR SEGMENTOBJ = 9U;
constexpr UCHAR FIGUREOBJ = 10U;
constexpr UCHAR RPROP = 11U;
constexpr UCHAR BINNODE = 12U;
constexpr UCHAR PATCHBOUND = 13U;
constexpr UCHAR SUBPATCHBOUND = 14U;
constexpr UCHAR PROPPATCHBOUND = 15U;
constexpr UCHAR LINEGEOM = 16U;
constexpr UCHAR PARTICLESYSTEM = 17U;
constexpr UCHAR PARTICLE = 18U;
constexpr UCHAR BLOBBYSYSTEM = 19U;
constexpr UCHAR BLOBBY = 20U;
constexpr UCHAR FLOCKSYSTEM = 21U;
constexpr UCHAR VOLUMETRIC = 22U;
constexpr UCHAR SPRITESYSTEM = 23U;
constexpr UCHAR SPRITE = 24U;
constexpr UCHAR SHAG = 25U;
constexpr UCHAR STRAND = 26U;
constexpr UCHAR FOLLICLE = 27U;
constexpr UCHAR HAIR = 28U;
constexpr UCHAR HAIRQUAD = 29U;
constexpr UCHAR HAIRSEGMENT = 30U;
constexpr UCHAR HAIRFOLLICLE = 31U;
constexpr UCHAR GUIDEPATCH = 32U;
constexpr UCHAR HAIRCUBIC = 33U;
constexpr UCHAR FLUIDSYSTEM = 34U;
constexpr UCHAR FLUIDPARTICLE = 35U;
constexpr UCHAR STREAKSYSTEM = 36U;
constexpr UCHAR STREAK = 37U;
constexpr UCHAR LIGHT = 38U;

constexpr UCHAR FUNDAMENTAL_DELIMETER = 50U;
constexpr UCHAR PROPQUADRANGLE = 51U;
constexpr UCHAR QUADRANGLE = 52U; //this must be the last two entries, Hsp.cpp  ThreadInfo::Intersect

/*
#define RSPHERE        5
#define RCONE          6
#define RCYLINDER      7
#define RBOX           8
#define SEGMENTOBJ     9
#define FIGUREOBJ      10
#define RPROP          11
#define BINNODE        12
#define PATCHBOUND     13
#define SUBPATCHBOUND  14
#define PROPPATCHBOUND 15
#define LINEGEOM       16
#define PARTICLESYSTEM 17
#define PARTICLE       18
#define BLOBBYSYSTEM   19
#define BLOBBY         20
#define FLOCKSYSTEM    21
#define VOLUMETRIC     22
#define SPRITESYSTEM   23
#define SPRITE         24
#define SHAG           25
#define STRAND         26
#define FOLLICLE       27
#define HAIR           28
#define HAIRQUAD       29
#define HAIRSEGMENT    30
#define HAIRFOLLICLE   31
#define GUIDEPATCH     32
#define HAIRCUBIC      33
#define FLUIDSYSTEM    34
#define FLUIDPARTICLE  35
#define STREAKSYSTEM   36
#define STREAK         37
#define LIGHT          38

#define PROPQUADRANGLE 51
#define QUADRANGLE     52        //this must be the last two entries, Hsp.cpp  ThreadInfo::Intersect
*/
