/** 
* @file fade_log_seq.c
* @author chris sutton 
* @brief  
* @version 0.1 
* @date 18-Mar-2020 
* @copyright Copyright (c) 2020 
* Generated with Python!
*/ 

#include <fade_log_seq.h>

uint32_t fade_log_seq_data_table[FADE_LOG_SEQ_DATA_SIZE] = {
	0x7d0, 0x7e5, 0x7fc, 0x812, 0x829, 0x840, 0x857, 0x86f, 0x886, 0x89e, 
	0x8b7, 0x8cf, 0x8e8, 0x901, 0x91a, 0x934, 0x94e, 0x968, 0x983, 0x99e, 
	0x9b9, 0x9d4, 0x9f0, 0xa0c, 0xa28, 0xa45, 0xa61, 0xa7f, 0xa9c, 0xaba, 
	0xad8, 0xaf7, 0xb16, 0xb35, 0xb55, 0xb74, 0xb95, 0xbb5, 0xbd6, 0xbf8, 
	0xc19, 0xc3b, 0xc5e, 0xc81, 0xca4, 0xcc7, 0xceb, 0xd10, 0xd35, 0xd5a, 
	0xd7f, 0xda5, 0xdcc, 0xdf3, 0xe1a, 0xe42, 0xe6a, 0xe92, 0xebb, 0xee5, 
	0xf0f, 0xf39, 0xf64, 0xf8f, 0xfbb, 0xfe8, 0x1014, 0x1042, 0x106f, 0x109e, 
	0x10cd, 0x10fc, 0x112c, 0x115c, 0x118d, 0x11be, 0x11f0, 0x1223, 0x1256, 0x128a, 
	0x12be, 0x12f2, 0x1328, 0x135e, 0x1394, 0x13cb, 0x1403, 0x143c, 0x1475, 0x14ae, 
	0x14e8, 0x1523, 0x155f, 0x159b, 0x15d8, 0x1615, 0x1653, 0x1692, 0x16d2, 0x1712, 
	0x1753, 0x1795, 0x17d7, 0x181a, 0x185e, 0x18a3, 0x18e8, 0x192e, 0x1975, 0x19bd, 
	0x1a05, 0x1a4f, 0x1a99, 0x1ae4, 0x1b2f, 0x1b7c, 0x1bc9, 0x1c18, 0x1c67, 0x1cb7, 
	0x1d07, 0x1d59, 0x1dac, 0x1dff, 0x1e54, 0x1ea9, 0x1f00, 0x1f57, 0x1faf, 0x2008, 
	0x2063, 0x20be, 0x211a, 0x2177, 0x21d5, 0x2235, 0x2295, 0x22f6, 0x2359, 0x23bc, 
	0x2421, 0x2487, 0x24ee, 0x2555, 0x25bf, 0x2629, 0x2694, 0x2701, 0x276f, 0x27de, 
	0x284e, 0x28c0, 0x2932, 0x29a6, 0x2a1c, 0x2a92, 0x2b0a, 0x2b83, 0x2bfe, 0x2c7a, 
	0x2cf7, 0x2d75, 0x2df5, 0x2e77, 0x2efa, 0x2f7e, 0x3004, 0x308b, 0x3114, 0x319e, 
	0x322a, 0x32b7, 0x3346, 0x33d6, 0x3468, 0x34fb, 0x3591, 0x3627, 0x36c0, 0x375a, 
	0x37f6, 0x3894, 0x3933, 0x39d4, 0x3a77, 0x3b1b, 0x3bc2, 0x3c6a, 0x3d14, 0x3dc0, 
	0x3e6e, 0x3f1e, 0x3fd0, 0x4083, 0x4139, 0x41f0, 0x42aa, 0x4366, 0x4424, 0x44e4, 
	0x45a5, 0x466a, 0x4730, 0x47f8, 0x48c3, 0x4990, 0x4a5f, 0x4b30, 0x4c04, 0x4cda, 
	0x4db3, 0x4e8d, 0x4f6a, 0x504a, 0x512c, 0x5211, 0x52f8, 0x53e1, 0x54ce, 0x55bc, 
	0x56ae, 0x57a2, 0x5899, 0x5992, 0x5a8e, 0x5b8d, 0x5c8f, 0x5d94, 0x5e9b, 0x5fa6, 
	0x60b3, 0x61c3, 0x62d6, 0x63ed, 0x6506, 0x6623, 0x6742, 0x6865, 0x698b, 0x6ab4, 
	0x6be0, 0x6d10, 0x6e43, 0x6f7a, 0x70b4, 0x71f1, 0x7332, 0x7476, 0x75be, 0x770a, 
	0x7859, 0x79ac, 0x7b02, 0x7c5d, 0x7dbb, 0x7f1d, 0x8083, 0x81ed, 0x835a, 0x84cc, 
	0x8642, 0x87bc, 0x893a, 0x8abd, 0x8c43, 0x8dce, 0x8f5e, 0x90f1, 0x9289, 0x9426, 
	0x95c7, 0x976d, 0x9917, 0x9ac6, 0x9c7a, 0x9e33, 0x9ff0, 0xa1b2, 0xa37a, 0xa546, 
	0xa717, 0xa8ee, 0xaaca, 0xacaa, 0xae91, 0xb07c, 0xb26d, 0xb463, 0xb65f, 0xb861, 
	0xba68, 0xbc75, 0xbe88, 0xc0a0, 0xc2be, 0xc4e3, 0xc70d, 0xc93e, 0xcb74, 0xcdb1, 
	0xcff4, 0xd23e, 0xd48e, 0xd6e4, 0xd941, 0xdba5, 0xde10, 0xe081, 0xe2f9, 0xe578, 
	0xe7fe, 0xea8b, 0xed20, 0xefbb, 0xf25e, 0xf509, 0xf7bb, 0xfa74, 0xfd36, 0xfffe
};
