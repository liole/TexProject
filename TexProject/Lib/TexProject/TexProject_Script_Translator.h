#pragma once
#include <TexProject/TexProject_Header.h>


#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Textures.h>


#include <vector>


#include <TexProject/TexProject_Script_Parser.h>


namespace TexProject
{
	namespace ASM86
	{
		const uint8		RETURN					= 0xC3;

		const uint8		JMP						= 0xE9; // X32

		const uint8		PUSH32					= 0x68; // X32

		const uint8		PUSH_LOC[]				={0xFF,0x35}; // X32
		const uint8		POP_LOC[]				={0x8F,0x05}; // X32

		const uint8		PUSH_EAX				= 0x50;
		const uint8		PUSH_EBX				= 0x53;
		const uint8		PUSH_ECX				= 0x51;
		const uint8		PUSH_EDX				= 0x52;
		const uint8		PUSH_ESP				= 0x54;
		const uint8		PUSH_EBP				= 0x55;
		const uint8		PUSH_ESI				= 0x56;
		const uint8		PUSH_EDI				= 0x57;

		const uint8		POP_EAX					= 0x58;
		const uint8		POP_EBX					= 0x5B;
		const uint8		POP_ECX					= 0x59;
		const uint8		POP_EDX					= 0x5A;
		const uint8		POP_ESP					= 0x5c;
		const uint8		POP_EBP					= 0x5d;
		const uint8		POP_ESI					= 0x5e;
		const uint8		POP_EDI					= 0x5f;

		const uint8		PUSH_LOC_EAX[]			={0xFF,0x30};
		const uint8		PUSH_LOC_EBX[]			={0xFF,0x33};
		const uint8		PUSH_LOC_ECX[]			={0xFF,0x31};
		const uint8		PUSH_LOC_EDX[]			={0xFF,0x32};
		const uint8		PUSH_LOC_ESP[]			={0xFF,0x34,0x24};
		const uint8		PUSH_LOC_EBP[]			={0xFF,0x75,0x00};
		const uint8		PUSH_LOC_ESI[]			={0xFF,0x36};
		const uint8		PUSH_LOC_EDI[]			={0xFF,0x37};

		const uint8		PUSH_LOC_EAXP8[]		={0xFF,0x70};		// X8
		const uint8		PUSH_LOC_EBXP8[]		={0xFF,0x73};		// X8
		const uint8		PUSH_LOC_ECXP8[]		={0xFF,0x71};		// X8
		const uint8		PUSH_LOC_EDXP8[]		={0xFF,0x72};		// X8
		const uint8		PUSH_LOC_ESPP8[]		={0xFF,0x74,0x24};	// X8
		const uint8		PUSH_LOC_EBPP8[]		={0xFF,0x75};		// X8
		const uint8		PUSH_LOC_ESIP8[]		={0xFF,0x76};		// X8
		const uint8		PUSH_LOC_EDIP8[]		={0xFF,0x77};		// X8

		const uint8		PUSH_LOC_EAXP32[]		={0xFF,0xB0};		// X32
		const uint8		PUSH_LOC_EBXP32[]		={0xFF,0xB3};		// X32
		const uint8		PUSH_LOC_ECXP32[]		={0xFF,0xB1};		// X32
		const uint8		PUSH_LOC_EDXP32[]		={0xFF,0xB2};		// X32
		const uint8		PUSH_LOC_ESPP32[]		={0xFF,0xB4,0x24};	// X32
		const uint8		PUSH_LOC_EBPP32[]		={0xFF,0xB5};		// X32
		const uint8		PUSH_LOC_ESIP32[]		={0xFF,0xB6};		// X32
		const uint8		PUSH_LOC_EDIP32[]		={0xFF,0xB7};		// X32

		const uint8		MOV_LOC_EAX[]			={0xC7,0x00}; // X32
		const uint8		MOV_LOC_EBX[]			={0xC7,0x03}; // X32
		const uint8		MOV_LOC_ECX[]			={0xC7,0x01}; // X32
		const uint8		MOV_LOC_EDX[]			={0xC7,0x02}; // X32

		const uint8		MOV_LOC_EAXP8[]			={0xC7,0x40}; // X8(offset), X32(value)
		const uint8		MOV_LOC_EBXP8[]			={0xC7,0x43}; // X8(offset), X32(value)
		const uint8		MOV_LOC_ECXP8[]			={0xC7,0x41}; // X8(offset), X32(value)
		const uint8		MOV_LOC_EDXP8[]			={0xC7,0x42}; // X8(offset), X32(value)

		const uint8		MOV_EAX_LOC[]			={0xA1};
		const uint8		MOV_EBX_LOC[]			={0x8B,0x1D};
		const uint8		MOV_ECX_LOC[]			={0x8B,0x0D};
		const uint8		MOV_EDX_LOC[]			={0x8B,0x15};
		const uint8		MOV_ESP_LOC[]			={0x8B,0x25};
		const uint8		MOV_EBP_LOC[]			={0x8B,0x2D};
		const uint8		MOV_ESI_LOC[]			={0x8B,0x35};
		const uint8		MOV_EDI_LOC[]			={0x8B,0x3D};

		const uint8		MOV_EAX_EAX[]			={0x89,0xC0};
		const uint8		MOV_EAX_EBX[]			={0x89,0xD8};
		const uint8		MOV_EAX_ECX[]			={0x89,0xC8};
		const uint8		MOV_EAX_EDX[]			={0x89,0xD0};
		const uint8		MOV_EAX_ESP[]			={0x89,0xE0};
		const uint8		MOV_EAX_EBP[]			={0x89,0xE8};
		const uint8		MOV_EAX_ESI[]			={0x89,0xF0};
		const uint8		MOV_EAX_EDI[]			={0x89,0xF8};

		const uint8		MOV_EBX_EAX[]			={0x89,0xC3};
		const uint8		MOV_EBX_EBX[]			={0x89,0xDB};
		const uint8		MOV_EBX_ECX[]			={0x89,0xCB};
		const uint8		MOV_EBX_EDX[]			={0x89,0xD3};
		const uint8		MOV_EBX_ESP[]			={0x89,0xE3};
		const uint8		MOV_EBX_EBP[]			={0x89,0xEB};
		const uint8		MOV_EBX_ESI[]			={0x89,0xF3};
		const uint8		MOV_EBX_EDI[]			={0x89,0xFB};

		const uint8		MOV_ECX_EAX[]			={0x89,0xC1};
		const uint8		MOV_ECX_EBX[]			={0x89,0xD9};
		const uint8		MOV_ECX_ECX[]			={0x89,0xC9};
		const uint8		MOV_ECX_EDX[]			={0x89,0xD1};
		const uint8		MOV_ECX_ESP[]			={0x89,0xE1};
		const uint8		MOV_ECX_EBP[]			={0x89,0xE9};
		const uint8		MOV_ECX_ESI[]			={0x89,0xF1};
		const uint8		MOV_ECX_EDI[]			={0x89,0xF9};

		const uint8		MOV_EDX_EAX[]			={0x89,0xC2};
		const uint8		MOV_EDX_EBX[]			={0x89,0xDA};
		const uint8		MOV_EDX_ECX[]			={0x89,0xCA};
		const uint8		MOV_EDX_EDX[]			={0x89,0xD2};
		const uint8		MOV_EDX_ESP[]			={0x89,0xE2};
		const uint8		MOV_EDX_EBP[]			={0x89,0xEA};
		const uint8		MOV_EDX_ESI[]			={0x89,0xF2};
		const uint8		MOV_EDX_EDI[]			={0x89,0xFA};

		const uint8		MOV_ESP_EAX[]			={0x89,0xC4};
		const uint8		MOV_ESP_EBX[]			={0x89,0xDC};
		const uint8		MOV_ESP_ECX[]			={0x89,0xCC};
		const uint8		MOV_ESP_EDX[]			={0x89,0xD4};
		const uint8		MOV_ESP_ESP[]			={0x89,0xE4};
		const uint8		MOV_ESP_EBP[]			={0x89,0xEC};
		const uint8		MOV_ESP_ESI[]			={0x89,0xF4};
		const uint8		MOV_ESP_EDI[]			={0x89,0xFC};

		const uint8		MOV_EBP_EAX[]			={0x89,0xC5};
		const uint8		MOV_EBP_EBX[]			={0x89,0xDD};
		const uint8		MOV_EBP_ECX[]			={0x89,0xCD};
		const uint8		MOV_EBP_EDX[]			={0x89,0xD5};
		const uint8		MOV_EBP_ESP[]			={0x89,0xE5};
		const uint8		MOV_EBP_EBP[]			={0x89,0xED};
		const uint8		MOV_EBP_ESI[]			={0x89,0xF5};
		const uint8		MOV_EBP_EDI[]			={0x89,0xFD};

		const uint8		MOV_ESI_EAX[]			={0x89,0xC6};
		const uint8		MOV_ESI_EBX[]			={0x89,0xDE};
		const uint8		MOV_ESI_ECX[]			={0x89,0xCE};
		const uint8		MOV_ESI_EDX[]			={0x89,0xD6};
		const uint8		MOV_ESI_ESP[]			={0x89,0xE6};
		const uint8		MOV_ESI_EBP[]			={0x89,0xEE};
		const uint8		MOV_ESI_ESI[]			={0x89,0xF6};
		const uint8		MOV_ESI_EDI[]			={0x89,0xFE};

		const uint8		MOV_EDI_EAX[]			={0x89,0xC7};
		const uint8		MOV_EDI_EBX[]			={0x89,0xDF};
		const uint8		MOV_EDI_ECX[]			={0x89,0xCF};
		const uint8		MOV_EDI_EDX[]			={0x89,0xD7};
		const uint8		MOV_EDI_ESP[]			={0x89,0xE7};
		const uint8		MOV_EDI_EBP[]			={0x89,0xEF};
		const uint8		MOV_EDI_ESI[]			={0x89,0xF7};
		const uint8		MOV_EDI_EDI[]			={0x89,0xFF};


		const uint8		MOV_EAX_LOC_EAX[]		={0x8B,0x00};
		const uint8		MOV_EAX_LOC_EBX[]		={0x8B,0x03};
		const uint8		MOV_EAX_LOC_ECX[]		={0x8B,0x01};
		const uint8		MOV_EAX_LOC_EDX[]		={0x8B,0x02};
		const uint8		MOV_EAX_LOC_ESP[]		={0x8B,0x04,0x24};
		const uint8		MOV_EAX_LOC_EBP[]		={0x8B,0x45,0x00};
		const uint8		MOV_EAX_LOC_ESI[]		={0x8B,0x06};
		const uint8		MOV_EAX_LOC_EDI[]		={0x8B,0x07};

		const uint8		MOV_EBX_LOC_EAX[]		={0x8B,0x18};
		const uint8		MOV_EBX_LOC_EBX[]		={0x8B,0x1B};
		const uint8		MOV_EBX_LOC_ECX[]		={0x8B,0x19};
		const uint8		MOV_EBX_LOC_EDX[]		={0x8B,0x1A};
		const uint8		MOV_EBX_LOC_ESP[]		={0x8B,0x1C,0x24};
		const uint8		MOV_EBX_LOC_EBP[]		={0x8B,0x5D,0x00};
		const uint8		MOV_EBX_LOC_ESI[]		={0x8B,0x1E};
		const uint8		MOV_EBX_LOC_EDI[]		={0x8B,0x1F};

		const uint8		MOV_ECX_LOC_EAX[]		={0x8B,0x08};
		const uint8		MOV_ECX_LOC_EBX[]		={0x8B,0x0B};
		const uint8		MOV_ECX_LOC_ECX[]		={0x8B,0x09};
		const uint8		MOV_ECX_LOC_EDX[]		={0x8B,0x0A};
		const uint8		MOV_ECX_LOC_ESP[]		={0x8B,0x0C,0x24};
		const uint8		MOV_ECX_LOC_EBP[]		={0x8B,0x4D,0x00};
		const uint8		MOV_ECX_LOC_ESI[]		={0x8B,0x0E};
		const uint8		MOV_ECX_LOC_EDI[]		={0x8B,0x0F};

		const uint8		MOV_EDX_LOC_EAX[]		={0x8B,0x10};
		const uint8		MOV_EDX_LOC_EBX[]		={0x8B,0x13};
		const uint8		MOV_EDX_LOC_ECX[]		={0x8B,0x11};
		const uint8		MOV_EDX_LOC_EDX[]		={0x8B,0x12};
		const uint8		MOV_EDX_LOC_ESP[]		={0x8B,0x14,0x24};
		const uint8		MOV_EDX_LOC_EBP[]		={0x8B,0x55,0x00};
		const uint8		MOV_EDX_LOC_ESI[]		={0x8B,0x16};
		const uint8		MOV_EDX_LOC_EDI[]		={0x8B,0x17};

		const uint8		MOV_LOC_EAX_EAX[]		={0x89,0x00};
		const uint8		MOV_LOC_EAX_EBX[]		={0x89,0x18};
		const uint8		MOV_LOC_EAX_ECX[]		={0x89,0x08};
		const uint8		MOV_LOC_EAX_EDX[]		={0x89,0x10};
		const uint8		MOV_LOC_EBX_EAX[]		={0x89,0x03};
		const uint8		MOV_LOC_EBX_EBX[]		={0x89,0x1B};
		const uint8		MOV_LOC_EBX_ECX[]		={0x89,0x0B};
		const uint8		MOV_LOC_EBX_EDX[]		={0x89,0x13};
		const uint8		MOV_LOC_ECX_EAX[]		={0x89,0x01};
		const uint8		MOV_LOC_ECX_EBX[]		={0x89,0x19};
		const uint8		MOV_LOC_ECX_ECX[]		={0x89,0x09};
		const uint8		MOV_LOC_ECX_EDX[]		={0x89,0x11};
		const uint8		MOV_LOC_EDX_EAX[]		={0x89,0x02};
		const uint8		MOV_LOC_EDX_EBX[]		={0x89,0x1A};
		const uint8		MOV_LOC_EDX_ECX[]		={0x89,0x0A};
		const uint8		MOV_LOC_EDX_EDX[]		={0x89,0x12};

		// mov [eax + 0xFF], eax ...
		const uint8		MOV_EAX_LOC_EAXP8[]		={0x8B,0x40};		// 1000 1011 1000 0000 X32
		const uint8		MOV_EAX_LOC_EBXP8[]		={0x8B,0x43};		// 1000 1011 1000 0000 X32
		const uint8		MOV_EAX_LOC_ECXP8[]		={0x8B,0x41};		// 1000 1011 1000 0000 X32
		const uint8		MOV_EAX_LOC_EDXP8[]		={0x8B,0x42};		// 1000 1011 1000 0000 X32
		const uint8		MOV_EBX_LOC_EAXP8[]		={0x8B,0x58};
		const uint8		MOV_EBX_LOC_EBXP8[]		={0x8B,0x5B};
		const uint8		MOV_EBX_LOC_ECXP8[]		={0x8B,0x59};
		const uint8		MOV_EBX_LOC_EDXP8[]		={0x8B,0x5A};
		const uint8		MOV_ECX_LOC_EAXP8[]		={0x8B,0x48};
		const uint8		MOV_ECX_LOC_EBXP8[]		={0x8B,0x4B};
		const uint8		MOV_ECX_LOC_ECXP8[]		={0x8B,0x49};
		const uint8		MOV_ECX_LOC_EDXP8[]		={0x8B,0x4A};
		const uint8		MOV_EDX_LOC_EAXP8[]		={0x8B,0x50};
		const uint8		MOV_EDX_LOC_EBXP8[]		={0x8B,0x53};
		const uint8		MOV_EDX_LOC_ECXP8[]		={0x8B,0x51};
		const uint8		MOV_EDX_LOC_EDXP8[]		={0x8B,0x52};

		// mov [eax + 0xFF], eax ...
		const uint8		MOV_LOC_EAXP8_EAX[]		={0x89,0x40};		// xxxx xxxx X8
		const uint8		MOV_LOC_EAXP8_EBX[]		={0x89,0x58};
		const uint8		MOV_LOC_EAXP8_ECX[]		={0x89,0x48};
		const uint8		MOV_LOC_EAXP8_EDX[]		={0x89,0x50};
		const uint8		MOV_LOC_EBXP8_EAX[]		={0x89,0x43};
		const uint8		MOV_LOC_EBXP8_EBX[]		={0x89,0x5B};
		const uint8		MOV_LOC_EBXP8_ECX[]		={0x89,0x4B};
		const uint8		MOV_LOC_EBXP8_EDX[]		={0x89,0x53};
		const uint8		MOV_LOC_ECXP8_EAX[]		={0x89,0x41};
		const uint8		MOV_LOC_ECXP8_EBX[]		={0x89,0x59};
		const uint8		MOV_LOC_ECXP8_ECX[]		={0x89,0x49};
		const uint8		MOV_LOC_ECXP8_EDX[]		={0x89,0x51};
		const uint8		MOV_LOC_EDXP8_EAX[]		={0x89,0x42};
		const uint8		MOV_LOC_EDXP8_EBX[]		={0x89,0x5A};
		const uint8		MOV_LOC_EDXP8_ECX[]		={0x89,0x4A};
		const uint8		MOV_LOC_EDXP8_EDX[]		={0x89,0x52};

		// mov [eax + 0xFF FF FF FF], eax ...
		const uint8		MOV_EAX_LOC_EAXP32[]	={0x8B,0x80};		// 1000 1011 1000 0000 X32
		const uint8		MOV_EAX_LOC_EBXP32[]	={0x8B,0x83};		// 1000 1011 1000 0000 X32
		const uint8		MOV_EAX_LOC_ECXP32[]	={0x8B,0x81};		// 1000 1011 1000 0000 X32
		const uint8		MOV_EAX_LOC_EDXP32[]	={0x8B,0x82};		// 1000 1011 1000 0000 X32
		const uint8		MOV_EAX_LOC_ESPP32[]	={0x8B,0x84,0x24};
		const uint8		MOV_EAX_LOC_EBPP32[]	={0x8B,0x85};
		const uint8		MOV_EAX_LOC_ESIP32[]	={0x8B,0x86};
		const uint8		MOV_EAX_LOC_EDIP32[]	={0x8B,0x87};

		const uint8		MOV_EBX_LOC_EAXP32[]	={0x8B,0x98};
		const uint8		MOV_EBX_LOC_EBXP32[]	={0x8B,0x9B};
		const uint8		MOV_EBX_LOC_ECXP32[]	={0x8B,0x99};
		const uint8		MOV_EBX_LOC_EDXP32[]	={0x8B,0x9A};
		const uint8		MOV_EBX_LOC_ESPP32[]	={0x8B,0x9C,0x24};
		const uint8		MOV_EBX_LOC_EBPP32[]	={0x8B,0x9D};
		const uint8		MOV_EBX_LOC_ESIP32[]	={0x8B,0x9E};
		const uint8		MOV_EBX_LOC_EDIP32[]	={0x8B,0x9F};

		const uint8		MOV_ECX_LOC_EAXP32[]	={0x8B,0x88};
		const uint8		MOV_ECX_LOC_EBXP32[]	={0x8B,0x8B};
		const uint8		MOV_ECX_LOC_ECXP32[]	={0x8B,0x89};
		const uint8		MOV_ECX_LOC_EDXP32[]	={0x8B,0x8A};
		const uint8		MOV_ECX_LOC_ESPP32[]	={0x8B,0x8C,0x24};
		const uint8		MOV_ECX_LOC_EBPP32[]	={0x8B,0x8D};
		const uint8		MOV_ECX_LOC_ESIP32[]	={0x8B,0x8E};
		const uint8		MOV_ECX_LOC_EDIP32[]	={0x8B,0x8F};

		const uint8		MOV_EDX_LOC_EAXP32[]	={0x8B,0x98};
		const uint8		MOV_EDX_LOC_EBXP32[]	={0x8B,0x9B};
		const uint8		MOV_EDX_LOC_ECXP32[]	={0x8B,0x99};
		const uint8		MOV_EDX_LOC_EDXP32[]	={0x8B,0x9A};
		const uint8		MOV_EDX_LOC_ESPP32[]	={0x8B,0x94,0x24};
		const uint8		MOV_EDX_LOC_EBPP32[]	={0x8B,0x95};
		const uint8		MOV_EDX_LOC_ESIP32[]	={0x8B,0x96};
		const uint8		MOV_EDX_LOC_EDIP32[]	={0x8B,0x97};

		/*
		0	0000
		1	0001
		2	0010
		3	0011
		4	0100
		5	0101
		6	0110
		7	0111
		8	1000
		9	1001
		A	1010
		B	1011
		C	1100
		D	1101
		E	1110
		F	1111
		*/

		const uint8		MOV_EAX					= 0xB8;				// 1011 1000 X32 // move to eax 32-bit literal
		const uint8		MOV_EBX					= 0xBB;				// 1011 1011 X32
		const uint8		MOV_ECX					= 0xB9;				// 1011 1001 X32
		const uint8		MOV_EDX					= 0xBA;				// 1011 1010 X32
		const uint8		MOV_ESP					= 0xBC;
		const uint8		MOV_EBP					= 0xBD;
		const uint8		MOV_ESI					= 0xBE;
		const uint8		MOV_EDI					= 0xBF;


		// EAX EBX ECX EDX ESP EBP ESI EDI

		// *+
		// 1000 1011 00RR R100 XXYY Y101
		// XX: 00 - *1, 01 - *2, 10 - *4, 11 - *4
		// YYY: 000 - EAX, 001 - ECX, 010 - EDX, 011 - EBX (source reg)
		// RRR: 000 - EAX, 001 - ECX, 010 - EDX, 011 - EBX (destination reg)
		// to EAX * +
		const uint8	MOV_EAX_EAX1_PLUS[]			={0x8B,0x04,0x05}; // 1000 1011 0000 0100 0000 0101 X32
		const uint8	MOV_EAX_EAX2_PLUS[]			={0x8B,0x04,0x45}; // 1000 1011 0000 0100 0100 0101 X32
		const uint8	MOV_EAX_EAX4_PLUS[]			={0x8B,0x04,0x85}; // 1000 1011 0000 0100 1000 0101 X32
		const uint8	MOV_EAX_EAX8_PLUS[]			={0x8B,0x04,0xC5}; // 1000 1011 0000 0100 1100 0101 X32
		const uint8	MOV_EAX_EBX1_PLUS[]			={0x8B,0x04,0x1D}; // 1000 1011 0000 0100 0001 1101 X32
		const uint8	MOV_EAX_EBX2_PLUS[]			={0x8B,0x04,0x5D}; // 1000 1011 0000 0100 0101 1101 X32
		const uint8	MOV_EAX_EBX4_PLUS[]			={0x8B,0x04,0x9D}; // 1000 1011 0000 0100 1001 1101 X32
		const uint8	MOV_EAX_EBX8_PLUS[]			={0x8B,0x04,0xDD}; // 1000 1011 0000 0100 1101 1101 X32
		const uint8	MOV_EAX_ECX1_PLUS[]			={0x8B,0x04,0x0D}; // 1000 1011 0000 0100 0000 1101 X32
		const uint8	MOV_EAX_ECX2_PLUS[]			={0x8B,0x04,0x4D}; // 1000 1011 0000 0100 0100 1101 X32
		const uint8	MOV_EAX_ECX4_PLUS[]			={0x8B,0x04,0x8D}; // 1000 1011 0000 0100 1000 1101 X32
		const uint8	MOV_EAX_ECX8_PLUS[]			={0x8B,0x04,0xCD}; // 1000 1011 0000 0100 1100 1101 X32
		const uint8	MOV_EAX_EDX1_PLUS[]			={0x8B,0x04,0x15}; // 1000 1011 0000 0100 0001 0101 X32
		const uint8	MOV_EAX_EDX2_PLUS[]			={0x8B,0x04,0x55}; // 1000 1011 0000 0100 0101 0101 X32
		const uint8	MOV_EAX_EDX4_PLUS[]			={0x8B,0x04,0x95}; // 1000 1011 0000 0100 1001 0101 X32
		const uint8	MOV_EAX_EDX8_PLUS[]			={0x8B,0x04,0xD5}; // 1000 1011 0000 0100 1101 0101 X32
		// to EBX * +
		const uint8	MOV_EBX_EAX1_PLUS[]			={0x8B,0x1C,0x05}; // 1000 1011 0000 0100 0000 0101 X32
		const uint8	MOV_EBX_EAX2_PLUS[]			={0x8B,0x1C,0x45}; // 1000 1011 0000 0100 0100 0101 X32
		const uint8	MOV_EBX_EAX4_PLUS[]			={0x8B,0x1C,0x85}; // 1000 1011 0000 0100 1000 0101 X32
		const uint8	MOV_EBX_EAX8_PLUS[]			={0x8B,0x1C,0xC5}; // 1000 1011 0000 0100 1100 0101 X32
		const uint8	MOV_EBX_EBX1_PLUS[]			={0x8B,0x1C,0x1D}; // 1000 1011 0000 0100 0001 1101 X32
		const uint8	MOV_EBX_EBX2_PLUS[]			={0x8B,0x1C,0x5D}; // 1000 1011 0000 0100 0101 1101 X32
		const uint8	MOV_EBX_EBX4_PLUS[]			={0x8B,0x1C,0x9D}; // 1000 1011 0000 0100 1001 1101 X32
		const uint8	MOV_EBX_EBX8_PLUS[]			={0x8B,0x1C,0xDD}; // 1000 1011 0000 0100 1101 1101 X32
		const uint8	MOV_EBX_ECX1_PLUS[]			={0x8B,0x1C,0x0D}; // 1000 1011 0000 0100 0000 1101 X32
		const uint8	MOV_EBX_ECX2_PLUS[]			={0x8B,0x1C,0x4D}; // 1000 1011 0000 0100 0100 1101 X32
		const uint8	MOV_EBX_ECX4_PLUS[]			={0x8B,0x1C,0x8D}; // 1000 1011 0000 0100 1000 1101 X32
		const uint8	MOV_EBX_ECX8_PLUS[]			={0x8B,0x1C,0xCD}; // 1000 1011 0000 0100 1100 1101 X32
		const uint8	MOV_EBX_EDX1_PLUS[]			={0x8B,0x1C,0x15}; // 1000 1011 0000 0100 0001 0101 X32
		const uint8	MOV_EBX_EDX2_PLUS[]			={0x8B,0x1C,0x55}; // 1000 1011 0000 0100 0101 0101 X32
		const uint8	MOV_EBX_EDX4_PLUS[]			={0x8B,0x1C,0x95}; // 1000 1011 0000 0100 1001 0101 X32
		const uint8	MOV_EBX_EDX8_PLUS[]			={0x8B,0x1C,0xD5}; // 1000 1011 0000 0100 1101 0101 X32
		// to ECX * +
		const uint8	MOV_EÑX_EAX1_PLUS[]			={0x8B,0x0C,0x05}; // 1000 1011 0000 0100 0000 0101 X32
		const uint8	MOV_EÑX_EAX2_PLUS[]			={0x8B,0x0C,0x45}; // 1000 1011 0000 0100 0100 0101 X32
		const uint8	MOV_EÑX_EAX4_PLUS[]			={0x8B,0x0C,0x85}; // 1000 1011 0000 0100 1000 0101 X32
		const uint8	MOV_EÑX_EAX8_PLUS[]			={0x8B,0x0C,0xC5}; // 1000 1011 0000 0100 1100 0101 X32
		const uint8	MOV_EÑX_EBX1_PLUS[]			={0x8B,0x0C,0x1D}; // 1000 1011 0000 0100 0001 1101 X32
		const uint8	MOV_EÑX_EBX2_PLUS[]			={0x8B,0x0C,0x5D}; // 1000 1011 0000 0100 0101 1101 X32
		const uint8	MOV_EÑX_EBX4_PLUS[]			={0x8B,0x0C,0x9D}; // 1000 1011 0000 0100 1001 1101 X32
		const uint8	MOV_EÑX_EBX8_PLUS[]			={0x8B,0x0C,0xDD}; // 1000 1011 0000 0100 1101 1101 X32
		const uint8	MOV_EÑX_ECX1_PLUS[]			={0x8B,0x0C,0x0D}; // 1000 1011 0000 0100 0000 1101 X32
		const uint8	MOV_EÑX_ECX2_PLUS[]			={0x8B,0x0C,0x4D}; // 1000 1011 0000 0100 0100 1101 X32
		const uint8	MOV_EÑX_ECX4_PLUS[]			={0x8B,0x0C,0x8D}; // 1000 1011 0000 0100 1000 1101 X32
		const uint8	MOV_EÑX_ECX8_PLUS[]			={0x8B,0x0C,0xCD}; // 1000 1011 0000 0100 1100 1101 X32
		const uint8	MOV_EÑX_EDX1_PLUS[]			={0x8B,0x0C,0x15}; // 1000 1011 0000 0100 0001 0101 X32
		const uint8	MOV_EÑX_EDX2_PLUS[]			={0x8B,0x0C,0x55}; // 1000 1011 0000 0100 0101 0101 X32
		const uint8	MOV_EÑX_EDX4_PLUS[]			={0x8B,0x0C,0x95}; // 1000 1011 0000 0100 1001 0101 X32
		const uint8	MOV_EÑX_EDX8_PLUS[]			={0x8B,0x0C,0xD5}; // 1000 1011 0000 0100 1101 0101 X32
		// to EÂX * +
		const uint8	MOV_EDX_EAX1_PLUS[]			={0x8B,0x14,0x05}; // 1000 1011 0000 0100 0000 0101 X32
		const uint8	MOV_EDX_EAX2_PLUS[]			={0x8B,0x14,0x45}; // 1000 1011 0000 0100 0100 0101 X32
		const uint8	MOV_EDX_EAX4_PLUS[]			={0x8B,0x14,0x85}; // 1000 1011 0000 0100 1000 0101 X32
		const uint8	MOV_EDX_EAX8_PLUS[]			={0x8B,0x14,0xC5}; // 1000 1011 0000 0100 1100 0101 X32
		const uint8	MOV_EDX_EBX1_PLUS[]			={0x8B,0x14,0x1D}; // 1000 1011 0000 0100 0001 1101 X32
		const uint8	MOV_EDX_EBX2_PLUS[]			={0x8B,0x14,0x5D}; // 1000 1011 0000 0100 0101 1101 X32
		const uint8	MOV_EDX_EBX4_PLUS[]			={0x8B,0x14,0x9D}; // 1000 1011 0000 0100 1001 1101 X32
		const uint8	MOV_EDX_EBX8_PLUS[]			={0x8B,0x14,0xDD}; // 1000 1011 0000 0100 1101 1101 X32
		const uint8	MOV_EDX_ECX1_PLUS[]			={0x8B,0x14,0x0D}; // 1000 1011 0000 0100 0000 1101 X32
		const uint8	MOV_EDX_ECX2_PLUS[]			={0x8B,0x14,0x4D}; // 1000 1011 0000 0100 0100 1101 X32
		const uint8	MOV_EDX_ECX4_PLUS[]			={0x8B,0x14,0x8D}; // 1000 1011 0000 0100 1000 1101 X32
		const uint8	MOV_EDX_ECX8_PLUS[]			={0x8B,0x14,0xCD}; // 1000 1011 0000 0100 1100 1101 X32
		const uint8	MOV_EDX_EDX1_PLUS[]			={0x8B,0x14,0x15}; // 1000 1011 0000 0100 0001 0101 X32
		const uint8	MOV_EDX_EDX2_PLUS[]			={0x8B,0x14,0x55}; // 1000 1011 0000 0100 0101 0101 X32
		const uint8	MOV_EDX_EDX4_PLUS[]			={0x8B,0x14,0x95}; // 1000 1011 0000 0100 1001 0101 X32
		const uint8	MOV_EDX_EDX8_PLUS[]			={0x8B,0x14,0xD5}; // 1000 1011 0000 0100 1101 0101 X32


		const uint8 LEA_EAX_LOC_EAXP32[]		={0x8D,0x80};
		const uint8 LEA_EAX_LOC_EBXP32[]		={0x8D,0x83};
		const uint8 LEA_EAX_LOC_ECXP32[]		={0x8D,0x81};
		const uint8 LEA_EAX_LOC_EDXP32[]		={0x8D,0x82};
		const uint8 LEA_EAX_LOC_ESPP32[]		={0x8D,0x84};
		const uint8 LEA_EAX_LOC_EBPP32[]		={0x8D,0x85};
		const uint8 LEA_EAX_LOC_ESIP32[]		={0x8D,0x86};
		const uint8 LEA_EAX_LOC_EDIP32[]		={0x8D,0x87};

		const uint8 LEA_EBX_LOC_EAXP32[]		={0x8D,0x98};
		const uint8 LEA_EBX_LOC_EBXP32[]		={0x8D,0x9B};
		const uint8 LEA_EBX_LOC_ECXP32[]		={0x8D,0x99};
		const uint8 LEA_EBX_LOC_EDXP32[]		={0x8D,0x9A};
		const uint8 LEA_EBX_LOC_ESPP32[]		={0x8D,0x9C};
		const uint8 LEA_EBX_LOC_EBPP32[]		={0x8D,0x9D};
		const uint8 LEA_EBX_LOC_ESIP32[]		={0x8D,0x9E};
		const uint8 LEA_EBX_LOC_EDIP32[]		={0x8D,0x9F};

		const uint8 LEA_ECX_LOC_EAXP32[]		={0x8D,0x88};
		const uint8 LEA_ECX_LOC_EBXP32[]		={0x8D,0x8B};
		const uint8 LEA_ECX_LOC_ECXP32[]		={0x8D,0x89};
		const uint8 LEA_ECX_LOC_EDXP32[]		={0x8D,0x8A};
		const uint8 LEA_ECX_LOC_ESPP32[]		={0x8D,0x8C};
		const uint8 LEA_ECX_LOC_EBPP32[]		={0x8D,0x8D};
		const uint8 LEA_ECX_LOC_ESIP32[]		={0x8D,0x8E};
		const uint8 LEA_ECX_LOC_EDIP32[]		={0x8D,0x8F};

		const uint8 LEA_EDX_LOC_EAXP32[]		={0x8D,0x90};
		const uint8 LEA_EDX_LOC_EBXP32[]		={0x8D,0x93};
		const uint8 LEA_EDX_LOC_ECXP32[]		={0x8D,0x91};
		const uint8 LEA_EDX_LOC_EDXP32[]		={0x8D,0x92};
		const uint8 LEA_EDX_LOC_ESPP32[]		={0x8D,0x94};
		const uint8 LEA_EDX_LOC_EBPP32[]		={0x8D,0x95};
		const uint8 LEA_EDX_LOC_ESIP32[]		={0x8D,0x96};
		const uint8 LEA_EDX_LOC_EDIP32[]		={0x8D,0x97};

		const uint8 LEA_ESP_LOC_EAXP8[]			={0x8D,0x60};
		const uint8 LEA_ESP_LOC_EBXP8[]			={0x8D,0x63};
		const uint8 LEA_ESP_LOC_ECXP8[]			={0x8D,0x61};
		const uint8 LEA_ESP_LOC_EDXP8[]			={0x8D,0x62};
		const uint8 LEA_ESP_LOC_ESPP8[]			={0x8D,0x64,0x24};
		const uint8 LEA_ESP_LOC_EBPP8[]			={0x8D,0x65};
		const uint8 LEA_ESP_LOC_ESIP8[]			={0x8D,0x66};
		const uint8 LEA_ESP_LOC_EDIP8[]			={0x8D,0x67};
		const uint8 LEA_ESP_LOC_EAXP32[]		={0x8D,0xA0};
		const uint8 LEA_ESP_LOC_EBXP32[]		={0x8D,0xA3};
		const uint8 LEA_ESP_LOC_ECXP32[]		={0x8D,0xA1};
		const uint8 LEA_ESP_LOC_EDXP32[]		={0x8D,0xA2};
		const uint8 LEA_ESP_LOC_ESPP32[]		={0x8D,0xA4,0x24};
		const uint8 LEA_ESP_LOC_EBPP32[]		={0x8D,0xA5};
		const uint8 LEA_ESP_LOC_ESIP32[]		={0x8D,0xA6};
		const uint8 LEA_ESP_LOC_EDIP32[]		={0x8D,0xA7};

		const uint8 LEA_EBP_LOC_EAXP32[]		={0x8D,0xA8};
		const uint8 LEA_EBP_LOC_EBXP32[]		={0x8D,0xAB};
		const uint8 LEA_EBP_LOC_ECXP32[]		={0x8D,0xA9};
		const uint8 LEA_EBP_LOC_EDXP32[]		={0x8D,0xAA};
		const uint8 LEA_EBP_LOC_ESPP32[]		={0x8D,0xAC,0x24};
		const uint8 LEA_EBP_LOC_EBPP32[]		={0x8D,0xAD};
		const uint8 LEA_EBP_LOC_ESIP32[]		={0x8D,0xAE};
		const uint8 LEA_EBP_LOC_EDIP32[]		={0x8D,0xAF};

		const uint8 LEA_ESI_LOC_EAXP32[]		={0x8D,0xB0};
		const uint8 LEA_ESI_LOC_EBXP32[]		={0x8D,0xB3};
		const uint8 LEA_ESI_LOC_ECXP32[]		={0x8D,0xB1};
		const uint8 LEA_ESI_LOC_EDXP32[]		={0x8D,0xB2};
		const uint8 LEA_ESI_LOC_ESPP32[]		={0x8D,0xB4,0x24};
		const uint8 LEA_ESI_LOC_EBPP32[]		={0x8D,0xB5};
		const uint8 LEA_ESI_LOC_ESIP32[]		={0x8D,0xB6};
		const uint8 LEA_ESI_LOC_EDIP32[]		={0x8D,0xB7};

		const uint8 LEA_EDI_LOC_EAXP32[]		={0x8D,0xB8};
		const uint8 LEA_EDI_LOC_EBXP32[]		={0x8D,0xBB};
		const uint8 LEA_EDI_LOC_ECXP32[]		={0x8D,0xB9};
		const uint8 LEA_EDI_LOC_EDXP32[]		={0x8D,0xBA};
		const uint8 LEA_EDI_LOC_ESPP32[]		={0x8D,0xBC,0x24};
		const uint8 LEA_EDI_LOC_EBPP32[]		={0x8D,0xBD};
		const uint8 LEA_EDI_LOC_ESIP32[]		={0x8D,0xBE};
		const uint8 LEA_EDI_LOC_EDIP32[]		={0x8D,0xBF};


		const uint8	ADD_EAX						= 0x05; // X32
		const uint8	ADD_EBX[]					={0x81,0xC3}; // X32
		const uint8	ADD_ECX[]					={0x81,0xC1}; // X32
		const uint8	ADD_EDX[]					={0x81,0xC2}; // X32
		const uint8	ADD_ESP[]					={0x81,0xC4}; // X32
		const uint8	ADD_EBP[]					={0x81,0xC5}; // X32
		const uint8	ADD_ESI[]					={0x81,0xC6}; // X32
		const uint8	ADD_EDI[]					={0x81,0xC7}; // X32

		const uint8	ADD_EAX8[]					={0x83,0xC0}; // X8
		const uint8	ADD_EBX8[]					={0x83,0xC3}; // X8
		const uint8	ADD_ECX8[]					={0x83,0xC1}; // X8
		const uint8	ADD_EDX8[]					={0x83,0xC2}; // X8
		const uint8	ADD_ESP8[]					={0x83,0xC4}; // X8
		const uint8	ADD_EBP8[]					={0x83,0xC5}; // X8
		const uint8	ADD_ESI8[]					={0x83,0xC6}; // X8
		const uint8	ADD_EDI8[]					={0x83,0xC7}; // X8

		const uint8	SUB_EAX						= 0x2D; // X32
		const uint8	SUB_EBX[]					={0x81,0xEB}; // X32
		const uint8	SUB_ECX[]					={0x81,0xE9}; // X32
		const uint8	SUB_EDX[]					={0x81,0xEA}; // X32
		const uint8	SUB_ESP[]					={0x81,0xEC}; // X32
		const uint8	SUB_EBP[]					={0x81,0xED}; // X32
		const uint8	SUB_ESI[]					={0x81,0xEE}; // X32
		const uint8	SUB_EDI[]					={0x81,0xEF}; // X32

		const uint8	SUB_EAX8[]					={0x83,0xE8}; // X8
		const uint8	SUB_EBX8[]					={0x83,0xEB}; // X8
		const uint8	SUB_ECX8[]					={0x83,0xE9}; // X8
		const uint8	SUB_EDX8[]					={0x83,0xEA}; // X8
		const uint8	SUB_ESP8[]					={0x83,0xEC}; // X8
		const uint8	SUB_EBP8[]					={0x83,0xED}; // X8
		const uint8	SUB_ESI8[]					={0x83,0xEE}; // X8
		const uint8	SUB_EDI8[]					={0x83,0xEF}; // X8

		// ????
		const uint8 REP_STOS_ED_ESI_EAX[]		={0xF3,0xAB};


		const uint8	FLDZ[]						={0xD9,0xEE}; // 1101 1001 1110 1110 
		const uint8	FLD1[]						={0xD9,0xE8}; // 1101 1001 1110 1000 
		const uint8	FLDPI[]						={0xD9,0xEB}; // 1101 1001 1110 1011 

		const uint8	FLD_EAX_32[]				={0xD9,0x00}; // 1101 1001 0000 0000 
		const uint8	FLD_EBX_32[]				={0xD9,0x03}; // 1101 1001 0000 0000 
		const uint8	FLD_ECX_32[]				={0xD9,0x01}; // 1101 1001 0000 0000 
		const uint8	FLD_EDX_32[]				={0xD9,0x02}; // 1101 1001 0000 0000 

		const uint8	FLD_EAX_64[]				={0xDF,0x28}; // 1101 1111 0010 1011 
		const uint8	FLD_EBX_64[]				={0xDF,0x2B}; // 1101 1111 0010 1011 
		const uint8	FLD_ECX_64[]				={0xDF,0x29}; // 1101 1111 0010 1011 
		const uint8	FLD_EDX_64[]				={0xDF,0x2A}; // 1101 1111 0010 1011 

		const uint8	FILD_EAX_32[]				={0xDB,0x00}; // 1101 1011 0000 0000 
		const uint8	FILD_EBX_32[]				={0xDB,0x03}; // 1101 1011 0000 0000 
		const uint8	FILD_ECX_32[]				={0xDB,0x01}; // 1101 1011 0000 0000 
		const uint8	FILD_EDX_32[]				={0xDB,0x02}; // 1101 1011 0000 0000 

		const uint8	FST_EAX_32[]				={0xD9,0x10}; // 1101 1001 0001 0000 
		const uint8	FST_EBX_32[]				={0xD9,0x13}; // 1101 1001 0001 0011 
		const uint8	FST_ECX_32[]				={0xD9,0x11}; // 1101 1001 0001 0001 
		const uint8	FST_EDX_32[]				={0xD9,0x12}; // 1101 1001 0001 0010 

		const uint8	FST_EAXP8_32[]				={0xD9,0x50}; // 1101 1001 0001 0000 X8
		const uint8	FST_EBXP8_32[]				={0xD9,0x53}; // 1101 1001 0001 0011 X8 
		const uint8	FST_ECXP8_32[]				={0xD9,0x51}; // 1101 1001 0001 0001 X8
		const uint8	FST_EDXP8_32[]				={0xD9,0x52}; // 1101 1001 0001 0010 X8

		const uint8	FSTP_EAX_32[]				={0xD9,0x18}; // 1101 1001 0001 1000 
		const uint8	FSTP_EBX_32[]				={0xD9,0x1B}; // 1101 1001 0001 1011 
		const uint8	FSTP_ECX_32[]				={0xD9,0x19}; // 1101 1001 0001 1001 
		const uint8	FSTP_EDX_32[]				={0xD9,0x1A}; // 1101 1001 0001 1010 

		const uint8	FSTP_EAXP8_32[]				={0xD9,0x58}; // 1101 1001 0001 0000 X8
		const uint8	FSTP_EBXP8_32[]				={0xD9,0x5B}; // 1101 1001 0001 0011 X8 
		const uint8	FSTP_ECXP8_32[]				={0xD9,0x59}; // 1101 1001 0001 0001 X8
		const uint8	FSTP_EDXP8_32[]				={0xD9,0x5A}; // 1101 1001 0001 0010 X8

		const uint8	FIST_EAX_32[]				={0xDB,0x10}; // 0001 0000 1101 1101 
		const uint8	FIST_EBX_32[]				={0xDB,0x13}; // 0001 0011 1101 1101 
		const uint8	FIST_ECX_32[]				={0xDB,0x11}; // 0001 0001 1101 1101 
		const uint8	FIST_EDX_32[]				={0xDB,0x12}; // 0001 0010 1101 1101 

		const uint8	FISTP_EAX_32[]				={0xDB,0x18}; // 0001 1000 1101 1101 
		const uint8	FISTP_EBX_32[]				={0xDB,0x1B}; // 0001 1011 1101 1101 
		const uint8	FISTP_ECX_32[]				={0xDB,0x19}; // 0001 1001 1101 1101 
		const uint8	FISTP_EDX_32[]				={0xDB,0x1A}; // 0001 1010 1101 1101 

		const uint8	FIST_EAXP8_32[]				={0xDB,0x50};
		const uint8	FIST_EBXP8_32[]				={0xDB,0x53};
		const uint8	FIST_ECXP8_32[]				={0xDB,0x51};
		const uint8	FIST_EDXP8_32[]				={0xDB,0x52};

		const uint8	FISTP_EAXP8_32[]			={0xDB,0x58};
		const uint8	FISTP_EBXP8_32[]			={0xDB,0x5B};
		const uint8	FISTP_ECXP8_32[]			={0xDB,0x59};
		const uint8	FISTP_EDXP8_32[]			={0xDB,0x5A};

		const uint8	FADDP[]						={0xDE,0xC1}; // 1101 1110 1100 0001
		const uint8	FSUBP[]						={0xDE,0xE9}; // 1101 1110 1110 1001
		const uint8	FMULP[]						={0xDE,0xC9}; // 1101 1110 1100 1001
		const uint8	FDIVP[]						={0xDE,0xF9}; // 1101 1110 1111 1001
		const uint8	FDIVRP[]					={0xDE,0xF1}; // 1101 1110 1111 0001

		const uint8	FABS[]						={0xD9,0xE1}; // 1101 1001 1111 0001
		const uint8	FSQRT[]						={0xD9,0xFA}; // 1101 1001 1111 1010
		const uint8	FSIN[]						={0xD9,0xFE}; // 1101 1001 1111 1110
		const uint8	FCOS[]						={0xD9,0xFF}; // 1101 1001 1111 1111


		const uint8	MOVUPS_XMM0_EAX[]			={0x0F,0x10,0x00};
		const uint8	MOVUPS_XMM0_EBX[]			={0x0F,0x10,0x03};
		const uint8	MOVUPS_XMM0_ECX[]			={0x0F,0x10,0x01};
		const uint8	MOVUPS_XMM0_EDX[]			={0x0F,0x10,0x02};
		const uint8	MOVUPS_XMM0_ESP[]			={0x0F,0x10,0x04,0x24};
		const uint8	MOVUPS_XMM0_EBP[]			={0x0F,0x10,0x45,0x00};
		const uint8	MOVUPS_XMM0_ESI[]			={0x0F,0x10,0x06};
		const uint8	MOVUPS_XMM0_EDI[]			={0x0F,0x10,0x07};

		const uint8	MOVUPS_XMM0_ESPP32[]		={0x0F,0x10,0x84,0x24};
		const uint8	MOVUPS_XMM0_EBPP32[]		={0x0F,0x10,0x85};
		const uint8	MOVUPS_XMM0_ESIP32[]		={0x0F,0x10,0x86};
		const uint8	MOVUPS_XMM0_EDIP32[]		={0x0F,0x10,0x87};

		const uint8	MOVUPS_EAX_XMM0[]			={0x0F,0x11,0x00};
		const uint8	MOVUPS_EBX_XMM0[]			={0x0F,0x11,0x03};
		const uint8	MOVUPS_ECX_XMM0[]			={0x0F,0x11,0x01};
		const uint8	MOVUPS_EDX_XMM0[]			={0x0F,0x11,0x02};
		const uint8	MOVUPS_ESP_XMM0[]			={0x0F,0x11,0x04,0x24};
		const uint8	MOVUPS_EBP_XMM0[]			={0x0F,0x11,0x45,0x00};
		const uint8	MOVUPS_ESI_XMM0[]			={0x0F,0x11,0x06};
		const uint8	MOVUPS_EDI_XMM0[]			={0x0F,0x11,0x07};


		inline uint8 loc1(void* data)
		{
			return reinterpret_cast<uint32>(data);
		}
		inline uint8 loc2(void* data)
		{
			return uint8(reinterpret_cast<uint32>(data) >> 8);
		}
		inline uint8 loc3(void* data)
		{
			return uint8(reinterpret_cast<uint32>(data) >> 16);
		}
		inline uint8 loc4(void* data)
		{
			return uint8(reinterpret_cast<uint32>(data) >> 24);
		}
		inline uint8 val1(void* data)
		{
			return (uint8)((*(uint32*)(data)) >> 0);
		}
		inline uint8 val2(void* data)
		{
			return (uint8)((*(uint32*)(data)) >> 8);
		}
		inline uint8 val3(void* data)
		{
			return (uint8)((*(uint32*)(data)) >> 16);
		}
		inline uint8 val4(void* data)
		{
			return (uint8)((*(uint32*)(data)) >> 24);
		}
	}


	struct Translator
	{
	protected:

		enum class Operation
		{
			None,
			Receiving,
			Assignation,
			InitializationVariable
		};

		Instructions::Expressions::Storage::Type operationType;
		Operation								operation = Operation::None;
		std::vector<uint8>*						code;
		uint32									stack = 0;

	public:
		void translate(Instruction* root);
		void translate(Instructions::Block* root);
		void translate(Instructions::Definition* root);
		void translate(Instructions::Expression* root);
		void translate(Instructions::Expressions::Operator* root);
		void translate(Instructions::Expressions::Operators::Binary::Assignment* root);
		void translate(Instructions::Expressions::Storage* root);
		void translate(Instructions::Expressions::Storages::Literal* root);
		void translate(Instructions::Expressions::Storages::Variable* root);
		void translate(Instructions::Expressions::Storages::In* root);
		void translate(Instructions::Expressions::Storages::Out* root);

		std::vector<uint8> TranslateToASM86(Instruction* root);
	};
}




















