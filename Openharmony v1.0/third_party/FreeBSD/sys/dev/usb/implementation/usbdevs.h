/* $FreeBSD: releng/11.3/sys/dev/usb/usbdevs 346655 2019-04-25 00:56:11Z gonzo $ */
/* $NetBSD: usbdevs,v 1.392 2004/12/29 08:38:44 imp Exp $ */

/*
 * Copyright (c) 1998-2004 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Lennart Augustsson (lennart@augustsson.net) at
 * Carlstedt Research & Technology.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.    IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * List of known #define    USB_vendors
 *
 * USB.org publishes a VID list of USB-IF member companies at
 * http://www.usb.org/developers/tools
 * Note that it does not show companies that have obtained a Vendor ID
 * without becoming full members.
 *
 * Please note that these IDs do not do anything. Adding an ID here and
 * regenerating the usbdevs.h and usbdevs data.h only makes a symbolic name
 * available to the source code and does not change any functionality, nor
 * does it make your device available to a specific driver.
 * It will however make the descriptive string available if a device does not
 * provide the string itself.
 *
 * After adding a #define    USB_VENDOR_ID VNDR and a #define    USB_PRODUCT_ID PRDCT you will have the
 * following extra defines:
 * #define    #define    USB_VENDOR_VNDR            0x????
 * #define    #define    USB_PRODUCT_VNDR PRDCT     0x????
 *
 * You may have to add these defines to the respective probe routines to
 * make the device recognised by the appropriate device driver.
 */

#define	USB_VENDOR_UNKNOWN1		0x0053	/* Unknown vendor */
#define	USB_VENDOR_UNKNOWN2		0x0105	/* Unknown vendor */
#define	USB_VENDOR_EGALAX2		0x0123	/* eGalax, Inc. */
#define	USB_VENDOR_CHIPSBANK_	0x0204	/* Chipsbank Microelectronics Co. */
#define	USB_VENDOR_HUMAX		0x02ad	/* HUMAX */
#define	USB_VENDOR_INTENSO		0x2109	/* INTENSO */
#define	USB_VENDOR_LTS			0x0386	/* LTS */
#define	USB_VENDOR_BWCT			0x03da	/* Bernd Walter Computer Technology */
#define	USB_VENDOR_AOX			0x03e8	/* AOX */
#define	USB_VENDOR_THESYS		0x03e9	/* Thesys */
#define	USB_VENDOR_DATABROADCAST	0x03ea	/* Data Broadcasting */
#define	USB_VENDOR_ATMEL_		0x03eb	/* Atmel */
#define	USB_VENDOR_IWATSU		0x03ec	/* Iwatsu America */
#define	USB_VENDOR_MITSUMI		0x03ee	/* Mitsumi */
#define	USB_VENDOR_HP			0x03f0	/* Hewlett Packard */
#define	USB_VENDOR_GENOA		0x03f1	/* Genoa */
#define	USB_VENDOR_OAK			0x03f2	/* Oak */
#define	USB_VENDOR_ADAPTEC		0x03f3	/* Adaptec */
#define	USB_VENDOR_DIEBOLD		0x03f4	/* Diebold */
#define	USB_VENDOR_SIEMENSELECTRO	0x03f5	/* Siemens Electromechanical */
#define	USB_VENDOR_EPSONIMAGING	0x03f8	/* Epson Imaging */
#define	USB_VENDOR_KEYTRONIC	0x03f9	/* KeyTronic */
#define	USB_VENDOR_OPTI			0x03fb	/* OPTi */
#define	USB_VENDOR_ELITEGROUP	0x03fc	/* Elitegroup */
#define	USB_VENDOR_XILINX		0x03fd	/* Xilinx */
#define	USB_VENDOR_FARALLON		0x03fe	/* Farallon Communications */
#define	USB_VENDOR_NATIONAL		0x0400	/* National Semiconductor */
#define	USB_VENDOR_NATIONALREG	0x0401	/* National Registry */
#define	USB_VENDOR_ACERLABS		0x0402	/* Acer Labs */
#define	USB_VENDOR_FTDI_		0x0403	/* Future Technology Devices */
#define	USB_VENDOR_NCR			0x0404	/* NCR */
#define	USB_VENDOR_SYNOPSYS2	0x0405	/* Synopsys */
#define	USB_VENDOR_FUJITSUICL	0x0406	/* Fujitsu-ICL */
#define	USB_VENDOR_FUJITSU2		0x0407	/* Fujitsu Personal Systems */
#define	USB_VENDOR_QUANTA		0x0408	/* Quanta */
#define	USB_VENDOR_NEC			0x0409	/* NEC */
#define	USB_VENDOR_KODAK_		0x040a	/* Eastman Kodak */
#define	USB_VENDOR_WELTREND		0x040b	/* Weltrend */
#define	USB_VENDOR_VIA			0x040d	/* VIA */
#define	USB_VENDOR_MCCI			0x040e	/* MCCI */
#define	USB_VENDOR_MELCO		0x0411	/* Melco */
#define	USB_VENDOR_LEADTEK		0x0413	/* Leadtek */
#define	USB_VENDOR_WINBOND		0x0416	/* Winbond */
#define	USB_VENDOR_PHOENIX		0x041a	/* Phoenix */
#define	USB_VENDOR_CREATIVE		0x041e	/* Creative Labs */
#define	USB_VENDOR_NOKIA		0x0421	/* Nokia */
#define	USB_VENDOR_ADI			0x0422	/* ADI Systems */
#define	USB_VENDOR_CATC			0x0423	/* Computer Access Technology */
#define	USB_VENDOR_SMC2			0x0424	/* Standard Microsystems */
#define	USB_VENDOR_MOTOROLA_HK	0x0425	/* Motorola HK */
#define	USB_VENDOR_GRAVIS		0x0428	/* Advanced Gravis Computer */
#define	USB_VENDOR_CIRRUSLOGIC	0x0429	/* Cirrus Logic */
#define	USB_VENDOR_INNOVATIVE	0x042c	/* Innovative Semiconductors */
#define	USB_VENDOR_MOLEX		0x042f	/* Molex */
#define	USB_VENDOR_SUN			0x0430	/* Sun Microsystems */
#define	USB_VENDOR_UNISYS		0x0432	/* Unisys */
#define	USB_VENDOR_TAUGA		0x0436	/* Taugagreining HF */
#define	USB_VENDOR_AMD			0x0438	/* Advanced Micro Devices */
#define	USB_VENDOR_LEXMARK		0x043d	/* Lexmark International */
#define	USB_VENDOR_LG			0x043e	/* LG Electronics */
#define	USB_VENDOR_NANAO		0x0440	/* NANAO */
#define	USB_VENDOR_GATEWAY		0x0443	/* Gateway 2000 */
#define	USB_VENDOR_NMB			0x0446	/* NMB */
#define	USB_VENDOR_ALPS			0x044e	/* Alps Electric */
#define	USB_VENDOR_THRUST		0x044f	/* Thrustmaster */
#define	USB_VENDOR_TI			0x0451	/* Texas Instruments */
#define	USB_VENDOR_ANALOGDEVICES	0x0456	/* Analog Devices */
#define	USB_VENDOR_SIS			0x0457	/* Silicon Integrated Systems Corp. */
#define	USB_VENDOR_KYE			0x0458	/* KYE Systems */
#define	USB_VENDOR_DIAMOND2		0x045a	/* Diamond (Supra) */
#define	USB_VENDOR_RENESAS		0x045b	/* Renesas */
#define	USB_VENDOR_MICROSOFT	0x045e	/* Microsoft */
#define	USB_VENDOR_PRIMAX		0x0461	/* Primax Electronics */
#define	USB_VENDOR_MGE			0x0463	/* MGE UPS Systems */
#define	USB_VENDOR_AMP			0x0464	/* AMP */
#define	USB_VENDOR_CHERRY_		0x046a	/* Cherry Mikroschalter */
#define	USB_VENDOR_MEGATRENDS	0x046b	/* American Megatrends */
#define	USB_VENDOR_LOGITECH		0x046d	/* Logitech */
#define	USB_VENDOR_BTC			0x046e	/* Behavior Tech. Computer */
#define	USB_VENDOR_PHILIPS_		0x0471	/* Philips */
#define	USB_VENDOR_SUN2			0x0472	/* Sun Microsystems (official) */
#define	USB_VENDOR_SANYO		0x0474	/* Sanyo Electric */
#define	USB_VENDOR_SEAGATE		0x0477	/* Seagate */
#define	USB_VENDOR_CONNECTIX	0x0478	/* Connectix */
#define	USB_VENDOR_SEMTECH		0x047a	/* Semtech */
#define	USB_VENDOR_KENSINGTON	0x047d	/* Kensington */
#define	USB_VENDOR_LUCENT		0x047e	/* Lucent */
#define	USB_VENDOR_PLANTRONICS	0x047f	/* Plantronics */
#define	USB_VENDOR_KYOCERA		0x0482	/* Kyocera Wireless Corp. */
#define	USB_VENDOR_STMICRO		0x0483	/* STMicroelectronics */
#define	USB_VENDOR_FOXCONN		0x0489	/* Foxconn */
#define	USB_VENDOR_MEIZU		0x0492	/* Meizu Electronics */
#define	USB_VENDOR_YAMAHA		0x0499	/* YAMAHA */
#define	USB_VENDOR_COMPAQ		0x049f	/* Compaq */
#define	USB_VENDOR_HITACHI		0x04a4	/* Hitachi */
#define	USB_VENDOR_ACERP		0x04a5	/* Acer Peripherals */
#define	USB_VENDOR_DAVICOM		0x04a6	/* Davicom */
#define	USB_VENDOR_VISIONEER	0x04a7	/* Visioneer */
#define	USB_VENDOR_CANON		0x04a9	/* Canon */
#define	USB_VENDOR_NIKON		0x04b0	/* Nikon */
#define	USB_VENDOR_PAN			0x04b1	/* Pan International */
#define	USB_VENDOR_IBM			0x04b3	/* IBM */
#define	USB_VENDOR_CYPRESS		0x04b4	/* Cypress Semiconductor */
#define	USB_VENDOR_ROHM			0x04b5	/* ROHM */
#define	USB_VENDOR_COMPAL		0x04b7	/* Compal */
#define	USB_VENDOR_EPSON		0x04b8	/* Seiko Epson */
#define	USB_VENDOR_RAINBOW		0x04b9	/* Rainbow Technologies */
#define	USB_VENDOR_IODATA		0x04bb	/* I-O Data */
#define	USB_VENDOR_TDK			0x04bf	/* TDK */
#define	USB_VENDOR_3COMUSR		0x04c1	/* U.S. Robotics */
#define	USB_VENDOR_METHODE		0x04c2	/* Methode Electronics Far East */
#define	USB_VENDOR_MAXISWITCH	0x04c3	/* Maxi Switch */
#define	USB_VENDOR_LOCKHEEDMER	0x04c4	/* Lockheed Martin Energy Research */
#define	USB_VENDOR_FUJITSU		0x04c5	/* Fujitsu */
#define	USB_VENDOR_TOSHIBAAM	0x04c6	/* Toshiba America */
#define	USB_VENDOR_MICROMACRO	0x04c7	/* Micro Macro Technologies */
#define	USB_VENDOR_KONICA		0x04c8	/* Konica */
#define	USB_VENDOR_LITEON		0x04ca	/* Lite-On Technology */
#define	USB_VENDOR_FUJIPHOTO	0x04cb	/* Fuji Photo Film */
#define	USB_VENDOR_PHILIPSSEMI	0x04cc	/* Philips Semiconductors */
#define	USB_VENDOR_TATUNG		0x04cd	/* Tatung Co. Of America */
#define	USB_VENDOR_SCANLOGIC	0x04ce	/* ScanLogic */
#define	USB_VENDOR_MYSON		0x04cf	/* Myson Technology */
#define	USB_VENDOR_DIGI2		0x04d0	/* Digi */
#define	USB_VENDOR_ITTCANON		0x04d1	/* ITT Canon */
#define	USB_VENDOR_ALTEC		0x04d2	/* Altec Lansing */
#define	USB_VENDOR_LSI			0x04d4	/* LSI */
#define	USB_VENDOR_MENTORGRAPHICS	0x04d6	/* Mentor Graphics */
#define	USB_VENDOR_ITUNERNET	0x04d8	/* I-Tuner Networks */
#define	USB_VENDOR_HOLTEK		0x04d9	/* Holtek Semiconductor, Inc. */
#define	USB_VENDOR_PANASONIC	0x04da	/* Panasonic (Matsushita) */
#define	USB_VENDOR_HUANHSIN		0x04dc	/* Huan Hsin */
#define	USB_VENDOR_SHARP		0x04dd	/* Sharp */
#define	USB_VENDOR_IIYAMA		0x04e1	/* Iiyama */
#define	USB_VENDOR_SHUTTLE		0x04e6	/* Shuttle Technology */
#define	USB_VENDOR_ELO			0x04e7	/* Elo TouchSystems */
#define	USB_VENDOR_SAMSUNG		0x04e8	/* Samsung Electronics */
#define	USB_VENDOR_NORTHSTAR	0x04eb	/* Northstar */
#define	USB_VENDOR_TOKYOELECTRON	0x04ec	/* Tokyo Electron */
#define	USB_VENDOR_ANNABOOKS	0x04ed	/* Annabooks */
#define	USB_VENDOR_JVC			0x04f1	/* JVC */
#define	USB_VENDOR_CHICONY		0x04f2	/* Chicony Electronics */
#define	USB_VENDOR_ELAN			0x04f3	/* Elan */
#define	USB_VENDOR_NEWNEX		0x04f7	/* Newnex */
#define	USB_VENDOR_BROTHER		0x04f9	/* Brother Industries */
#define	USB_VENDOR_DALLAS		0x04fa	/* Dallas Semiconductor */
#define	USB_VENDOR_AIPTEK2		0x04fc	/* AIPTEK International */
#define	USB_VENDOR_PFU			0x04fe	/* PFU */
#define	USB_VENDOR_FUJIKURA		0x0501	/* Fujikura/DDK */
#define	USB_VENDOR_ACER			0x0502	/* Acer */
#define	USB_VENDOR_3COM			0x0506	/* 3Com */
#define	USB_VENDOR_HOSIDEN		0x0507	/* Hosiden Corporation */
#define	USB_VENDOR_AZTECH		0x0509	/* Aztech Systems */
#define	USB_VENDOR_BELKIN		0x050d	/* Belkin Components */
#define	USB_VENDOR_KAWATSU		0x050f	/* Kawatsu Semiconductor */
#define	USB_VENDOR_FCI			0x0514	/* FCI */
#define	USB_VENDOR_LONGWELL		0x0516	/* Longwell */
#define	USB_VENDOR_COMPOSITE	0x0518	/* Composite */
#define	USB_VENDOR_STAR			0x0519	/* Star Micronics */
#define	USB_VENDOR_APC			0x051d	/* American Power Conversion */
#define	USB_VENDOR_SCIATLANTA	0x051e	/* Scientific Atlanta */
#define	USB_VENDOR_TSM			0x0520	/* TSM */
#define	USB_VENDOR_CONNECTEK	0x0522	/* Advanced Connectek USA */
#define	USB_VENDOR_NETCHIP		0x0525	/* NetChip Technology */
#define	USB_VENDOR_ALTRA		0x0527	/* ALTRA */
#define	USB_VENDOR_ATI			0x0528	/* ATI Technologies */
#define	USB_VENDOR_AKS			0x0529	/* Aladdin Knowledge Systems */
#define	USB_VENDOR_TEKOM		0x052b	/* Tekom */
#define	USB_VENDOR_CANONDEV		0x052c	/* Canon */
#define	USB_VENDOR_WACOMTECH	0x0531	/* Wacom */
#define	USB_VENDOR_INVENTEC		0x0537	/* Inventec */
#define	USB_VENDOR_SHYHSHIUN	0x0539	/* Shyh Shiun Terminals */
#define	USB_VENDOR_PREHWERKE	0x053a	/* Preh Werke Gmbh & Co. KG */
#define	USB_VENDOR_SYNOPSYS		0x053f	/* Synopsys */
#define	USB_VENDOR_UNIACCESS	0x0540	/* Universal Access */
#define	USB_VENDOR_VIEWSONIC	0x0543	/* ViewSonic */
#define	USB_VENDOR_XIRLINK		0x0545	/* Xirlink */
#define	USB_VENDOR_ANCHOR		0x0547	/* Anchor Chips */
#define	USB_VENDOR_SONY			0x054c	/* Sony */
#define	USB_VENDOR_FUJIXEROX	0x0550	/* Fuji Xerox */
#define	USB_VENDOR_VISION		0x0553	/* VLSI Vision */
#define	USB_VENDOR_ASAHIKASEI	0x0556	/* Asahi Kasei Microsystems */
#define	USB_VENDOR_ATEN_		0x0557	/* ATEN International */
#define	USB_VENDOR_SAMSUNG2		0x055d	/* Samsung Electronics */
#define	USB_VENDOR_MUSTEK_		0x055f	/* Mustek Systems */
#define	USB_VENDOR_TELEX		0x0562	/* Telex Communications */
#define	USB_VENDOR_CHINON		0x0564	/* Chinon */
#define	USB_VENDOR_PERACOM		0x0565	/* Peracom Networks */
#define	USB_VENDOR_ALCOR2		0x0566	/* Alcor Micro */
#define	USB_VENDOR_XYRATEX		0x0567	/* Xyratex */
#define	USB_VENDOR_WACOM		0x056a	/* WACOM */
#define	USB_VENDOR_ETEK			0x056c	/* e-TEK Labs */
#define	USB_VENDOR_EIZO			0x056d	/* EIZO */
#define	USB_VENDOR_ELECOM		0x056e	/* Elecom */
#define	USB_VENDOR_CONEXANT		0x0572	/* Conexant */
#define	USB_VENDOR_HAUPPAUGE	0x0573	/* Hauppauge Computer Works */
#define	USB_VENDOR_BAFO			0x0576	/* BAFO/Quality Computer Accessories */
#define	USB_VENDOR_YEDATA		0x057b	/* Y-E Data */
#define	USB_VENDOR_AVM			0x057c	/* AVM */
#define	USB_VENDOR_QUICKSHOT	0x057f	/* Quickshot */
#define	USB_VENDOR_ROLAND		0x0582	/* Roland */
#define	USB_VENDOR_ROCKFIRE		0x0583	/* Rockfire */
#define	USB_VENDOR_RATOC		0x0584	/* RATOC Systems */
#define	USB_VENDOR_ZYXEL		0x0586	/* ZyXEL Communication */
#define	USB_VENDOR_INFINEON		0x058b	/* Infineon */
#define	USB_VENDOR_MICREL		0x058d	/* Micrel */
#define	USB_VENDOR_ALCOR		0x058f	/* Alcor Micro */
#define	USB_VENDOR_OMRON		0x0590	/* OMRON */
#define	USB_VENDOR_ZORAN		0x0595	/* Zoran Microelectronics */
#define	USB_VENDOR_NIIGATA		0x0598	/* Niigata */
#define	USB_VENDOR_IOMEGA		0x059b	/* Iomega */
#define	USB_VENDOR_ATREND		0x059c	/* A-Trend Technology */
#define	USB_VENDOR_AID			0x059d	/* Advanced Input Devices */
#define	USB_VENDOR_LACIE		0x059f	/* LaCie */
#define	USB_VENDOR_FUJIFILM		0x05a2	/* Fuji Film */
#define	USB_VENDOR_ARC			0x05a3	/* ARC */
#define	USB_VENDOR_ORTEK		0x05a4	/* Ortek */
#define	USB_VENDOR_CISCOLINKSYS3	0x05a6	/* Cisco-Linksys */
#define	USB_VENDOR_BOSE			0x05a7	/* Bose */
#define	USB_VENDOR_OMNIVISION	0x05a9	/* OmniVision */
#define	USB_VENDOR_INSYSTEM		0x05ab	/* In-System Design */
#define	USB_VENDOR_APPLE		0x05ac	/* Apple Computer */
#define	USB_VENDOR_YCCABLE		0x05ad	/* Y.C. Cable */
#define	USB_VENDOR_DIGITALPERSONA	0x05ba	/* DigitalPersona */
#define	USB_VENDOR_3G			0x05bc	/* 3G Green Green Globe */
#define	USB_VENDOR_RAFI			0x05bd	/* RAFI */
#define	USB_VENDOR_TYCO			0x05be	/* Tyco */
#define	USB_VENDOR_KAWASAKI		0x05c1	/* Kawasaki */
#define	USB_VENDOR_DIGI			0x05c5	/* Digi International */
#define	USB_VENDOR_QUALCOMM2	0x05c6	/* Qualcomm */
#define	USB_VENDOR_QTRONIX		0x05c7	/* Qtronix */
#define	USB_VENDOR_FOXLINK		0x05c8	/* Foxlink */
#define	USB_VENDOR_RICOH		0x05ca	/* Ricoh */
#define	USB_VENDOR_ELSA			0x05cc	/* ELSA */
#define	USB_VENDOR_SCIWORX		0x05ce	/* sci-worx */
#define	USB_VENDOR_BRAINBOXES	0x05d1	/* Brainboxes Limited */
#define	USB_VENDOR_ULTIMA		0x05d8	/* Ultima */
#define	USB_VENDOR_AXIOHM		0x05d9	/* Axiohm Transaction Solutions */
#define	USB_VENDOR_MICROTEK		0x05da	/* Microtek */
#define	USB_VENDOR_SUNTAC		0x05db	/* SUN Corporation */
#define	USB_VENDOR_LEXAR		0x05dc	/* Lexar Media */
#define	USB_VENDOR_ADDTRON		0x05dd	/* Addtron */
#define	USB_VENDOR_SYMBOL		0x05e0	/* Symbol Technologies */
#define	USB_VENDOR_SYNTEK		0x05e1	/* Syntek */
#define	USB_VENDOR_GENESYS		0x05e3	/* Genesys Logic */
#define	USB_VENDOR_FUJI			0x05e5	/* Fuji Electric */
#define	USB_VENDOR_KEITHLEY		0x05e6	/* Keithley Instruments */
#define	USB_VENDOR_EIZONANAO	0x05e7	/* EIZO Nanao */
#define	USB_VENDOR_KLSI			0x05e9	/* Kawasaki LSI */
#define	USB_VENDOR_FFC			0x05eb	/* FFC */
#define	USB_VENDOR_ANKO			0x05ef	/* Anko Electronic */
#define	USB_VENDOR_PIENGINEERING	0x05f3	/* P.I. Engineering */
#define	USB_VENDOR_AOC			0x05f6	/* AOC International */
#define	USB_VENDOR_CHIC			0x05fe	/* Chic Technology */
#define	USB_VENDOR_BARCO		0x0600	/* Barco Display Systems */
#define	USB_VENDOR_BRIDGE		0x0607	/* Bridge Information */
#define	USB_VENDOR_SOLIDYEAR	0x060b	/* Solid Year */
#define	USB_VENDOR_BIORAD		0x0614	/* Bio-Rad Laboratories */
#define	USB_VENDOR_MACALLY		0x0618	/* Macally */
#define	USB_VENDOR_ACTLABS		0x061c	/* Act Labs */
#define	USB_VENDOR_ALARIS		0x0620	/* Alaris */
#define	USB_VENDOR_APEX			0x0624	/* Apex */
#define	USB_VENDOR_CREATIVE3	0x062a	/* Creative Labs */
#define	USB_VENDOR_MICRON		0x0634	/* Micron Technology */
#define	USB_VENDOR_VIVITAR		0x0636	/* Vivitar */
#define	USB_VENDOR_GUNZE		0x0637	/* Gunze Electronics USA */
#define	USB_VENDOR_AVISION		0x0638	/* Avision */
#define	USB_VENDOR_TEAC			0x0644	/* TEAC */
#define	USB_VENDOR_ACTON		0x0647	/* Acton Research Corp. */
#define	USB_VENDOR_OPTO			0x065a	/* Optoelectronics Co., Ltd */
#define	USB_VENDOR_SGI			0x065e	/* Silicon Graphics */
#define	USB_VENDOR_SANWASUPPLY	0x0663	/* Sanwa Supply */
#define	USB_VENDOR_MEGATEC		0x0665	/* Megatec */
#define	USB_VENDOR_LINKSYS		0x066b	/* Linksys */
#define	USB_VENDOR_ACERSA		0x066e	/* Acer Semiconductor America */
#define	USB_VENDOR_SIGMATEL		0x066f	/* Sigmatel */
#define	USB_VENDOR_DRAYTEK		0x0675	/* DrayTek */
#define	USB_VENDOR_AIWA			0x0677	/* Aiwa */
#define	USB_VENDOR_ACARD		0x0678	/* ACARD Technology */
#define	USB_VENDOR_PROLIFIC		0x067b	/* Prolific Technology */
#define	USB_VENDOR_SIEMENS		0x067c	/* Siemens */
#define	USB_VENDOR_AVANCELOGIC	0x0680	/* Avance Logic */
#define	USB_VENDOR_SIEMENS2		0x0681	/* Siemens */
#define	USB_VENDOR_MINOLTA		0x0686	/* Minolta */
#define	USB_VENDOR_CHPRODUCTS	0x068e	/* CH Products */
#define	USB_VENDOR_HAGIWARA		0x0693	/* Hagiwara Sys-Com */
#define	USB_VENDOR_CTX			0x0698	/* Chuntex */
#define	USB_VENDOR_ASKEY		0x069a	/* Askey Computer */
#define	USB_VENDOR_SAITEK		0x06a3	/* Saitek */
#define	USB_VENDOR_ALCATELT		0x06b9	/* Alcatel Telecom */
#define	USB_VENDOR_AGFA			0x06bd	/* AGFA-Gevaert */
#define	USB_VENDOR_ASIAMD		0x06be	/* Asia Microelectronic Development */
#define	USB_VENDOR_BIZLINK		0x06c4	/* Bizlink International */
#define	USB_VENDOR_KEYSPAN		0x06cd	/* Keyspan / InnoSys Inc. */
#define	USB_VENDOR_CONTEC		0x06ce	/* Contec products */
#define	USB_VENDOR_AASHIMA		0x06d6	/* Aashima Technology */
#define	USB_VENDOR_LIEBERT		0x06da	/* Liebert */
#define	USB_VENDOR_MULTITECH	0x06e0	/* MultiTech */
#define	USB_VENDOR_ADS			0x06e1	/* ADS Technologies */
#define	USB_VENDOR_ALCATELM		0x06e4	/* Alcatel Microelectronics */
#define	USB_VENDOR_SIRIUS		0x06ea	/* Sirius Technologies */
#define	USB_VENDOR_GUILLEMOT	0x06f8	/* Guillemot */
#define	USB_VENDOR_BOSTON		0x06fd	/* Boston Acoustics */
#define	USB_VENDOR_SMC			0x0707	/* Standard Microsystems */
#define	USB_VENDOR_PUTERCOM		0x0708	/* Putercom */
#define	USB_VENDOR_MCT			0x0711	/* MCT */
#define	USB_VENDOR_IMATION		0x0718	/* Imation */
#define	USB_VENDOR_TECLAST		0x071b	/* Teclast */
#define	USB_VENDOR_SONYERICSSON	0x0731	/* Sony Ericsson */
#define	USB_VENDOR_EICON		0x0734	/* Eicon Networks */
#define	USB_VENDOR_SYNTECH		0x0745	/* Syntech Information */
#define	USB_VENDOR_DIGITALSTREAM	0x074e	/* Digital Stream */
#define	USB_VENDOR_AUREAL		0x0755	/* Aureal Semiconductor */
#define	USB_VENDOR_MAUDIO		0x0763	/* M-Audio */
#define	USB_VENDOR_CYBERPOWER	0x0764	/* Cyber Power Systems, Inc. */
#define	USB_VENDOR_SURECOM		0x0769	/* Surecom Technology */
#define	USB_VENDOR_HIDGLOBAL	0x076b	/* HID Global */
#define	USB_VENDOR_LINKSYS2		0x077b	/* Linksys */
#define	USB_VENDOR_GRIFFIN		0x077d	/* Griffin Technology */
#define	USB_VENDOR_SANDISK		0x0781	/* SanDisk */
#define	USB_VENDOR_JENOPTIK		0x0784	/* Jenoptik */
#define	USB_VENDOR_LOGITEC		0x0789	/* Logitec */
#define	USB_VENDOR_NOKIA2		0x078b	/* Nokia */
#define	USB_VENDOR_BRIMAX		0x078e	/* Brimax */
#define	USB_VENDOR_AXIS			0x0792	/* Axis Communications */
#define	USB_VENDOR_ABL			0x0794	/* ABL Electronics */
#define	USB_VENDOR_SAGEM		0x079b	/* Sagem */
#define	USB_VENDOR_SUNCOMM		0x079c	/* Sun Communications, Inc. */
#define	USB_VENDOR_ALFADATA		0x079d	/* Alfadata Computer */
#define	USB_VENDOR_NATIONALTECH	0x07a2	/* National Technical Systems */
#define	USB_VENDOR_ONNTO		0x07a3	/* Onnto */
#define	USB_VENDOR_BE			0x07a4	/* Be */
#define	USB_VENDOR_ADMTEK		0x07a6	/* ADMtek */
#define	USB_VENDOR_COREGA		0x07aa	/* Corega */
#define	USB_VENDOR_FREECOM		0x07ab	/* Freecom */
#define	USB_VENDOR_MICROTECH	0x07af	/* Microtech */
#define	USB_VENDOR_GENERALINSTMNTS	0x07b2	/* General Instruments (Motorola) */
#define	USB_VENDOR_OLYMPUS			0x07b4	/* Olympus */
#define	USB_VENDOR_ABOCOM			0x07b8	/* AboCom Systems */
#define	USB_VENDOR_KEISOKUGIKEN		0x07c1	/* Keisokugiken */
#define	USB_VENDOR_ONSPEC			0x07c4	/* OnSpec */
#define	USB_VENDOR_APG				0x07c5	/* APG Cash Drawer */
#define	USB_VENDOR_BUG				0x07c8	/* B.U.G. */
#define	USB_VENDOR_ALLIEDTELESYN	0x07c9	/* Allied Telesyn International */
#define	USB_VENDOR_AVERMEDIA	0x07ca	/* AVerMedia Technologies */
#define	USB_VENDOR_SIIG			0x07cc	/* SIIG */
#define	USB_VENDOR_CASIO		0x07cf	/* CASIO */
#define	USB_VENDOR_DLINK2		0x07d1	/* D-Link */
#define	USB_VENDOR_APTIO		0x07d2	/* Aptio Products */
#define	USB_VENDOR_ARASAN		0x07da	/* Arasan Chip Systems */
#define	USB_VENDOR_ALLIEDCABLE	0x07e6	/* Allied Cable */
#define	USB_VENDOR_STSN			0x07ef	/* STSN */
#define	USB_VENDOR_CENTURY		0x07f7	/* Century Corp */
#define	USB_VENDOR_NEWLINK		0x07ff	/* NEWlink */
#define	USB_VENDOR_MAGTEK		0x0801	/* Mag-Tek */
#define	USB_VENDOR_ZOOM			0x0803	/* Zoom Telephonics */
#define	USB_VENDOR_PCS			0x0810	/* Personal Communication Systems */
#define	USB_VENDOR_ALPHASMART	0x081e	/* AlphaSmart, Inc. */
#define	USB_VENDOR_BROADLOGIC	0x0827	/* BroadLogic */
#define	USB_VENDOR_HANDSPRING	0x082d	/* Handspring */
#define	USB_VENDOR_PALM			0x0830	/* Palm Computing */
#define	USB_VENDOR_SOURCENEXT	0x0833	/* SOURCENEXT */
#define	USB_VENDOR_ACTIONSTAR	0x0835	/* Action Star Enterprise */
#define	USB_VENDOR_SAMSUNG_TECHWIN	0x0839	/* Samsung Techwin */
#define	USB_VENDOR_ACCTON			0x083a	/* Accton Technology */
#define	USB_VENDOR_DIAMOND			0x0841	/* Diamond */
#define	USB_VENDOR_NETGEAR			0x0846	/* BayNETGEAR */
#define	USB_VENDOR_TOPRE			0x0853	/* Topre Corporation */
#define	USB_VENDOR_ACTIVEWIRE		0x0854	/* ActiveWire */
#define	USB_VENDOR_BBELECTRONICS	0x0856	/* B&B Electronics */
#define	USB_VENDOR_PORTGEAR			0x085a	/* PortGear */
#define	USB_VENDOR_NETGEAR2			0x0864	/* Netgear */
#define	USB_VENDOR_SYSTEMTALKS		0x086e	/* System Talks */
#define	USB_VENDOR_METRICOM			0x0870	/* Metricom */
#define	USB_VENDOR_ADESSOKBTEK		0x087c	/* ADESSO/Kbtek America */
#define	USB_VENDOR_JATON			0x087d	/* Jaton */
#define	USB_VENDOR_APT				0x0880	/* APT Technologies */
#define	USB_VENDOR_BOCARESEARCH		0x0885	/* Boca Research */
#define	USB_VENDOR_ANDREA			0x08a8	/* Andrea Electronics */
#define	USB_VENDOR_BURRBROWN		0x08bb	/* Burr-Brown Japan */
#define	USB_VENDOR_2WIRE			0x08c8	/* 2Wire */
#define	USB_VENDOR_AIPTEK			0x08ca	/* AIPTEK International */
#define	USB_VENDOR_SMARTBRIDGES		0x08d1	/* SmartBridges */
#define	USB_VENDOR_FUJITSUSIEMENS	0x08d4	/* Fujitsu-Siemens */
#define	USB_VENDOR_BILLIONTON		0x08dd	/* Billionton Systems */
#define	USB_VENDOR_GEMALTO			0x08e6	/* Gemalto SA */
#define	USB_VENDOR_EXTENDED			0x08e9	/* Extended Systems */
#define	USB_VENDOR_MSYSTEMS			0x08ec	/* M-Systems */
#define	USB_VENDOR_DIGIANSWER		0x08fd	/* Digianswer */
#define	USB_VENDOR_AUTHENTEC		0x08ff	/* AuthenTec */
#define	USB_VENDOR_AUDIOTECHNICA	0x0909	/* Audio-Technica */
#define	USB_VENDOR_TRUMPION			0x090a	/* Trumpion Microelectronics */
#define	USB_VENDOR_FEIYA			0x090c	/* Feiya */
#define	USB_VENDOR_ALATION			0x0910	/* Alation Systems */
#define	USB_VENDOR_GLOBESPAN		0x0915	/* Globespan */
#define	USB_VENDOR_CONCORDCAMERA	0x0919	/* Concord Camera */
#define	USB_VENDOR_GARMIN		0x091e	/* Garmin International */
#define	USB_VENDOR_GOHUBS		0x0921	/* GoHubs */
#define	USB_VENDOR_DYMO			0x0922	/* DYMO */
#define	USB_VENDOR_XEROX		0x0924	/* Xerox */
#define	USB_VENDOR_BIOMETRIC	0x0929	/* American Biometric Company */
#define	USB_VENDOR_TOSHIBA		0x0930	/* Toshiba */
#define	USB_VENDOR_PLEXTOR		0x093b	/* Plextor */
#define	USB_VENDOR_INTREPIDCS	0x093c	/* Intrepid */
#define	USB_VENDOR_YANO			0x094f	/* Yano */
#define	USB_VENDOR_KINGSTON		0x0951	/* Kingston Technology */
#define	USB_VENDOR_BLUEWATER	0x0956	/* BlueWater Systems */
#define	USB_VENDOR_AGILENT		0x0957	/* Agilent Technologies */
#define	USB_VENDOR_GUDE			0x0959	/* Gude ADS */
#define	USB_VENDOR_PORTSMITH	0x095a	/* Portsmith */
#define	USB_VENDOR_ACERW		0x0967	/* Acer */
#define	USB_VENDOR_ADIRONDACK	0x0976	/* Adirondack Wire & Cable */
#define	USB_VENDOR_BECKHOFF		0x0978	/* Beckhoff */
#define	USB_VENDOR_MINDSATWORK	0x097a	/* Minds At Work */
#define	USB_VENDOR_POINTCHIPS	0x09a6	/* PointChips */
#define	USB_VENDOR_INTERSIL		0x09aa	/* Intersil */
#define	USB_VENDOR_ALTIUS		0x09b3	/* Altius Solutions */
#define	USB_VENDOR_ARRIS		0x09c1	/* Arris Interactive */
#define	USB_VENDOR_ACTIVCARD	0x09c3	/* ACTIVCARD */
#define	USB_VENDOR_ACTISYS		0x09c4	/* ACTiSYS */
#define	USB_VENDOR_NOVATEL2		0x09d7	/* Novatel Wireless */
#define	USB_VENDOR_AFOURTECH	0x09da	/* A-FOUR TECH */
#define	USB_VENDOR_AIMEX		0x09dc	/* AIMEX */
#define	USB_VENDOR_ADDONICS		0x09df	/* Addonics Technologies */
#define	USB_VENDOR_AKAI			0x09e8	/* AKAI professional M.I. */
#define	USB_VENDOR_ARESCOM		0x09f5	/* ARESCOM */
#define	USB_VENDOR_BAY			0x09f9	/* Bay Associates */
#define	USB_VENDOR_ALTERA		0x09fb	/* Altera */
#define	USB_VENDOR_CSR			0x0a12	/* Cambridge Silicon Radio */
#define	USB_VENDOR_TREK			0x0a16	/* Trek Technology */
#define	USB_VENDOR_ASAHIOPTICAL	0x0a17	/* Asahi Optical */
#define	USB_VENDOR_BOCASYSTEMS	0x0a43	/* Boca Systems */
#define	USB_VENDOR_SHANTOU		0x0a46	/* ShanTou */
#define	USB_VENDOR_MEDIAGEAR	0x0a48	/* MediaGear */
#define	USB_VENDOR_PLOYTEC		0x0a4a	/* Ploytec GmbH */
#define	USB_VENDOR_BROADCOM		0x0a5c	/* Broadcom */
#define	USB_VENDOR_GREENHOUSE	0x0a6b	/* GREENHOUSE */
#define	USB_VENDOR_MEDELI		0x0a67	/* Medeli */
#define	USB_VENDOR_GEOCAST		0x0a79	/* Geocast Network Systems */
#define	USB_VENDOR_EGO			0x0a92	/* EGO systems */
#define	USB_VENDOR_IDQUANTIQUE	0x0aba	/* ID Quantique */
#define	USB_VENDOR_IDTECH		0x0acd	/* ID TECH */
#define	USB_VENDOR_ZYDAS		0x0ace	/* Zydas Technology Corporation */
#define	USB_VENDOR_NEODIO		0x0aec	/* Neodio */
#define	USB_VENDOR_OPTION		0x0af0	/* Option N.V. */
#define	USB_VENDOR_ASUS			0x0b05	/* ASUSTeK Computer */
#define	USB_VENDOR_TODOS		0x0b0c	/* Todos Data System */
#define	USB_VENDOR_SIIG2		0x0b39	/* SIIG */
#define	USB_VENDOR_TEKRAM		0x0b3b	/* Tekram Technology */
#define	USB_VENDOR_HAL			0x0b41	/* HAL Corporation */
#define	USB_VENDOR_EMS			0x0b43	/* EMS Production */
#define	USB_VENDOR_NEC2			0x0b62	/* NEC */
#define	USB_VENDOR_ADLINK		0x0b63	/* ADLINK Technoligy, Inc. */
#define	USB_VENDOR_ATI2			0x0b6f	/* ATI */
#define	USB_VENDOR_ZEEVO		0x0b7a	/* Zeevo, Inc. */
#define	USB_VENDOR_KURUSUGAWA	0x0b7e	/* Kurusugawa Electronics, Inc. */
#define	USB_VENDOR_SMART		0x0b8c	/* Smart Technologies */
#define	USB_VENDOR_ASIX_		0x0b95	/* ASIX Electronics */
#define	USB_VENDOR_O2MICRO		0x0b97	/* O2 Micro, Inc. */
#define	USB_VENDOR_USR			0x0baf	/* U.S. Robotics */
#define	USB_VENDOR_AMBIT		0x0bb2	/* Ambit Microsystems */
#define	USB_VENDOR_HTC			0x0bb4	/* HTC */
#define	USB_VENDOR_REALTEK		0x0bda	/* Realtek */
#define	USB_VENDOR_ERICSSON2	0x0bdb	/* Ericsson */
#define	USB_VENDOR_MEI			0x0bed	/* MEI */
#define	USB_VENDOR_ADDONICS2	0x0bf6	/* Addonics Technology */
#define	USB_VENDOR_FSC			0x0bf8	/* Fujitsu Siemens Computers */
#define	USB_VENDOR_AGATE		0x0c08	/* Agate Technologies */
#define	USB_VENDOR_DMI			0x0c0b	/* DMI */
#define	USB_VENDOR_CANYON		0x0c10	/* Canyon */
#define	USB_VENDOR_ICOM			0x0c26	/* Icom Inc. */
#define	USB_VENDOR_GNOTOMETRICS	0x0c33	/* GN Otometrics */
#define	USB_VENDOR_CHICONY2		0x0c45	/* Chicony / Microdia / Sonix Technology Co., Ltd. */
#define	USB_VENDOR_REINERSCT	0x0c4b	/* Reiner-SCT */
#define	USB_VENDOR_SEALEVEL		0x0c52	/* Sealevel System */
#define	USB_VENDOR_JETI			0x0c6c	/* Jeti */
#define	USB_VENDOR_LUWEN		0x0c76	/* Luwen */
#define	USB_VENDOR_ELEKTOR		0x0c7d	/* ELEKTOR Electronics */
#define	USB_VENDOR_KYOCERA2		0x0c88	/* Kyocera Wireless Corp. */
#define	USB_VENDOR_ZCOM			0x0cde	/* Z-Com */
#define	USB_VENDOR_ATHEROS2		0x0cf3	/* Atheros Communications */
#define	USB_VENDOR_POSIFLEX		0x0d3a	/* POSIFLEX */
#define	USB_VENDOR_TANGTOP		0x0d3d	/* Tangtop */
#define	USB_VENDOR_KOBIL		0x0d46	/* KOBIL */
#define	USB_VENDOR_SMC3			0x0d5c	/* Standard Microsystems */
#define	USB_VENDOR_ADDON		0x0d7d	/* Add-on Technology */
#define	USB_VENDOR_ACDC			0x0d7e	/* American Computer & Digital Components */
#define	USB_VENDOR_CMEDIA		0x0d8c	/* CMEDIA */
#define	USB_VENDOR_CONCEPTRONIC	0x0d8e	/* Conceptronic */
#define	USB_VENDOR_SKANHEX		0x0d96	/* Skanhex Technology, Inc. */
#define	USB_VENDOR_MSI			0x0db0	/* Micro Star International */
#define	USB_VENDOR_ELCON		0x0db7	/* ELCON Systemtechnik */
#define	USB_VENDOR_UNKNOWN4		0x0dcd	/* Unknown vendor */
#define	USB_VENDOR_NETAC		0x0dd8	/* Netac */
#define	USB_VENDOR_SITECOMEU	0x0df6	/* Sitecom Europe */
#define	USB_VENDOR_MOBILEACTION	0x0df7	/* Mobile Action */
#define	USB_VENDOR_AMIGO		0x0e0b	/* Amigo Technology */
#define	USB_VENDOR_SPEEDDRAGON	0x0e55	/* Speed Dragon Multimedia */
#define	USB_VENDOR_HAWKING		0x0e66	/* Hawking */
#define	USB_VENDOR_FOSSIL		0x0e67	/* Fossil, Inc */
#define	USB_VENDOR_GMATE		0x0e7e	/* G.Mate, Inc */
#define	USB_VENDOR_MEDIATEK		0x0e8d	/* MediaTek, Inc. */
#define	USB_VENDOR_OTI			0x0ea0	/* Ours Technology */
#define	USB_VENDOR_YISO			0x0eab	/* Yiso Wireless Co. */
#define	USB_VENDOR_PILOTECH		0x0eaf	/* Pilotech */
#define	USB_VENDOR_NOVATECH		0x0eb0	/* NovaTech */
#define	USB_VENDOR_ITEGNO		0x0eba	/* iTegno */
#define	USB_VENDOR_WINMAXGROUP	0x0ed1	/* WinMaxGroup */
#define	USB_VENDOR_TOD			0x0ede	/* TOD */
#define	USB_VENDOR_EGALAX		0x0eef	/* eGalax, Inc. */
#define	USB_VENDOR_AIRPRIME		0x0f3d	/* AirPrime, Inc. */
#define	USB_VENDOR_MICROTUNE	0x0f4d	/* Microtune */
#define	USB_VENDOR_VTECH		0x0f88	/* VTech */
#define	USB_VENDOR_FALCOM		0x0f94	/* Falcom Wireless Communications GmbH */
#define	USB_VENDOR_RIM			0x0fca	/* Research In Motion */
#define	USB_VENDOR_DYNASTREAM_	0x0fcf	/* Dynastream Innovations */
#define	USB_VENDOR_LARSENBRUSGAARD	0x0fd8	/* Larsen and Brusgaard */
#define	USB_VENDOR_OWL			0x0fde	/* OWL */
#define	USB_VENDOR_KONTRON		0x0fe6	/* Kontron AG */
#define	USB_VENDOR_QUALCOMM		0x1004	/* Qualcomm */
#define	USB_VENDOR_APACER		0x1005	/* Apacer */
#define	USB_VENDOR_MOTOROLA4	0x100d	/* Motorola */
#define	USB_VENDOR_HP3			0x103c	/* Hewlett Packard */
#define	USB_VENDOR_AIRPLUS		0x1011	/* Airplus */
#define	USB_VENDOR_DESKNOTE		0x1019	/* Desknote */
#define	USB_VENDOR_NEC3			0x1033	/* NEC */
#define	USB_VENDOR_TTI			0x103e	/* Thurlby Thandar Instruments */
#define	USB_VENDOR_GIGABYTE		0x1044	/* GIGABYTE */
#define	USB_VENDOR_WESTERN		0x1058	/* Western Digital */
#define	USB_VENDOR_MOTOROLA		0x1063	/* Motorola */
#define	USB_VENDOR_CCYU			0x1065	/* CCYU Technology */
#define	USB_VENDOR_CURITEL		0x106c	/* Curitel Communications Inc */
#define	USB_VENDOR_SILABS2		0x10a6	/* SILABS2 */
#define	USB_VENDOR_USI			0x10ab	/* USI */
#define	USB_VENDOR_LIEBERT2		0x10af	/* Liebert */
#define	USB_VENDOR_PLX			0x10b5	/* PLX */
#define	USB_VENDOR_ASANTE		0x10bd	/* Asante */
#define	USB_VENDOR_SILABS		0x10c4	/* Silicon Labs */
#define	USB_VENDOR_SILABS3		0x10c5	/* Silicon Labs */
#define	USB_VENDOR_SILABS4		0x10ce	/* Silicon Labs */
#define	USB_VENDOR_ACTIONS		0x10d6	/* Actions */
#define	USB_VENDOR_ANALOG		0x1110	/* Analog Devices */
#define	USB_VENDOR_TENX			0x1130	/* Ten X Technology, Inc. */
#define	USB_VENDOR_ISSC			0x1131	/* Integrated System Solution Corp. */
#define	USB_VENDOR_JRC			0x1145	/* Japan Radio Company */
#define	USB_VENDOR_SPHAIRON		0x114b	/* Sphairon Access Systems GmbH */
#define	USB_VENDOR_DELORME		0x1163	/* DeLorme */
#define	USB_VENDOR_SERVERWORKS	0x1166	/* ServerWorks */
#define	USB_VENDOR_DLINK3		0x1186	/* Dlink */
#define	USB_VENDOR_ACERCM		0x1189	/* Acer Communications & Multimedia */
#define	USB_VENDOR_SIERRA		0x1199	/* Sierra Wireless */
#define	USB_VENDOR_SANWA		0x11ad	/* Sanwa Electric Instrument Co., Ltd. */
#define	USB_VENDOR_TOPFIELD		0x11db	/* Topfield Co., Ltd */
#define	USB_VENDOR_SIEMENS3		0x11f5	/* Siemens */
#define	USB_VENDOR_NETINDEX		0x11f6	/* NetIndex */
#define	USB_VENDOR_ALCATEL		0x11f7	/* Alcatel */
#define	USB_VENDOR_INTERBIOMETRICS	0x1209	/* Interbiometrics */
#define	USB_VENDOR_UNKNOWN3		0x1233	/* Unknown vendor */
#define	USB_VENDOR_TSUNAMI		0x1241	/* Tsunami */
#define	USB_VENDOR_PHEENET		0x124a	/* Pheenet */
#define	USB_VENDOR_TARGUS		0x1267	/* Targus */
#define	USB_VENDOR_TWINMOS		0x126f	/* TwinMOS */
#define	USB_VENDOR_TENDA		0x1286	/* Tenda */
#define	USB_VENDOR_TESTO		0x128d	/* Testo products */
#define	USB_VENDOR_CREATIVE2	0x1292	/* Creative Labs */
#define	USB_VENDOR_BELKIN2		0x1293	/* Belkin Components */
#define	USB_VENDOR_CYBERTAN		0x129b	/* CyberTAN Technology */
#define	USB_VENDOR_HUAWEI		0x12d1	/* Huawei Technologies */
#define	USB_VENDOR_ARANEUS		0x12d8	/* Araneus Information Systems */
#define	USB_VENDOR_TAPWAVE		0x12ef	/* Tapwave */
#define	USB_VENDOR_AINCOMM		0x12fd	/* Aincomm */
#define	USB_VENDOR_MOBILITY		0x1342	/* Mobility */
#define	USB_VENDOR_DICKSMITH	0x1371	/* Dick Smith Electronics */
#define	USB_VENDOR_NETGEAR3		0x1385	/* Netgear */
#define	USB_VENDOR_BALTECH		0x13ad	/* Baltech */
#define	USB_VENDOR_CISCOLINKSYS	0x13b1	/* Cisco-Linksys */
#define	USB_VENDOR_SHARK		0x13d2	/* Shark */
#define	USB_VENDOR_AZUREWAVE_	0x13d3	/* AsureWave */
#define	USB_VENDOR_INITIO		0x13fd	/* Initio Corporation */
#define	USB_VENDOR_EMTEC		0x13fe	/* Emtec */
#define	USB_VENDOR_NOVATEL		0x1410	/* Novatel Wireless */
#define	USB_VENDOR_MERLIN		0x1416	/* Merlin */
#define	USB_VENDOR_REDOCTANE	0x1430	/* RedOctane */
#define	USB_VENDOR_WISTRONNEWEB	0x1435	/* Wistron NeWeb */
#define	USB_VENDOR_RADIOSHACK	0x1453	/* Radio Shack */
#define	USB_VENDOR_FIC			0x1457	/* FIC / OpenMoko */
#define	USB_VENDOR_HUAWEI3COM	0x1472	/* Huawei-3Com */
#define	USB_VENDOR_ABOCOM2		0x1482	/* AboCom Systems */
#define	USB_VENDOR_SILICOM		0x1485	/* Silicom */
#define	USB_VENDOR_RALINK		0x148f	/* Ralink Technology */
#define	USB_VENDOR_IMAGINATION	0x149a	/* Imagination Technologies */
#define	USB_VENDOR_ATP			0x14af	/* ATP Electronics */
#define	USB_VENDOR_CONCEPTRONIC2	0x14b2	/* Conceptronic */
#define	USB_VENDOR_SUPERTOP			0x14cd	/* Super Top */
#define	USB_VENDOR_PLANEX3			0x14ea	/* Planex Communications */
#define	USB_VENDOR_SILICONPORTALS	0x1527	/* Silicon Portals */
#define	USB_VENDOR_UBIQUAM		0x1529	/* UBIQUAM Co., Ltd. */
#define	USB_VENDOR_JMICRON		0x152d	/* JMicron */
#define	USB_VENDOR_UBLOX		0x1546	/* U-blox */
#define	USB_VENDOR_PNY			0x154b	/* PNY */
#define	USB_VENDOR_OWEN			0x1555	/* Owen */
#define	USB_VENDOR_OQO			0x1557	/* OQO */
#define	USB_VENDOR_UMEDIA		0x157e	/* U-MEDIA Communications */
#define	USB_VENDOR_FIBERLINE	0x1582	/* Fiberline */
#define	USB_VENDOR_FREESCALE	0x15a2	/* Freescale Semiconductor, Inc. */
#define	USB_VENDOR_AFATECH		0x15a4	/* Afatech Technologies, Inc. */
#define	USB_VENDOR_SPARKLAN		0x15a9	/* SparkLAN */
#define	USB_VENDOR_OLIMEX		0x15ba	/* Olimex */
#define	USB_VENDOR_SOUNDGRAPH	0x15c2	/* Soundgraph, Inc. */
#define	USB_VENDOR_AMIT2		0x15c5	/* AMIT */
#define	USB_VENDOR_TEXTECH		0x15ca	/* Textech International Ltd. */
#define	USB_VENDOR_SOHOWARE		0x15e8	/* SOHOware */
#define	USB_VENDOR_ABIT			0x15eb	/* ABIT Corporation */
#define	USB_VENDOR_UMAX			0x1606	/* UMAX Data Systems */
#define	USB_VENDOR_INSIDEOUT	0x1608	/* Inside Out Networks */
#define	USB_VENDOR_AMOI			0x1614	/* Amoi Electronics */
#define	USB_VENDOR_GOODWAY		0x1631	/* Good Way Technology */
#define	USB_VENDOR_ENTREGA		0x1645	/* Entrega */
#define	USB_VENDOR_ACTIONTEC	0x1668	/* Actiontec Electronics */
#define	USB_VENDOR_CLIPSAL		0x166a	/* Clipsal */
#define	USB_VENDOR_CISCOLINKSYS2	0x167b	/* Cisco-Linksys */
#define	USB_VENDOR_ATHEROS			0x168c	/* Atheros Communications */
#define	USB_VENDOR_GIGASET			0x1690	/* Gigaset */
#define	USB_VENDOR_GLOBALSUN		0x16ab	/* Global Sun Technology */
#define	USB_VENDOR_ANYDATA			0x16d5	/* AnyDATA Corporation */
#define	USB_VENDOR_JABLOTRON		0x16d6	/* Jablotron */
#define	USB_VENDOR_CMOTECH			0x16d8	/* C-motech */
#define	USB_VENDOR_WIENERPLEINBAUS	0x16dc	/* WIENER Plein & Baus GmbH. */
#define	USB_VENDOR_AXESSTEL		0x1726	/* Axesstel Co., Ltd. */
#define	USB_VENDOR_LINKSYS4		0x1737	/* Linksys */
#define	USB_VENDOR_SENAO		0x1740	/* Senao */
#define	USB_VENDOR_ASUS2		0x1761	/* ASUS */
#define	USB_VENDOR_SWEEX2		0x177f	/* Sweex */
#define	USB_VENDOR_METAGEEK		0x1781	/* MetaGeek */
#define	USB_VENDOR_KAMSTRUP		0x17a8	/* Kamstrup A/S */
#define	USB_VENDOR_DISPLAYLINK_	0x17e9	/* DisplayLink */
#define	USB_VENDOR_LENOVO		0x17ef	/* Lenovo */
#define	USB_VENDOR_WAVESENSE	0x17f4	/* WaveSense */
#define	USB_VENDOR_VAISALA		0x1843	/* Vaisala */
#define	USB_VENDOR_AMIT			0x18c5	/* AMIT */
#define	USB_VENDOR_GOOGLE		0x18d1	/* Google */
#define	USB_VENDOR_QCOM			0x18e8	/* Qcom */
#define	USB_VENDOR_ELV			0x18ef	/* ELV */
#define	USB_VENDOR_LINKSYS3		0x1915	/* Linksys */
#define	USB_VENDOR_QUALCOMMINC	0x19d2	/* Qualcomm, Incorporated */
#define	USB_VENDOR_QUALCOMM3	0x19f5	/* Qualcomm, Inc. */
#define	USB_VENDOR_BAYER		0x1a79	/* Bayer */
#define	USB_VENDOR_WCH2			0x1a86	/* QinHeng Electronics */
#define	USB_VENDOR_STELERA		0x1a8d	/* Stelera Wireless */
#define	USB_VENDOR_SEL			0x1adb	/* Schweitzer Engineering Laboratories */
#define	USB_VENDOR_CORSAIR		0x1b1c	/* Corsair */
#define	USB_VENDOR_ASM			0x1b21	/* ASMedia Technology */
#define	USB_VENDOR_MATRIXORBITAL	0x1b3d	/* Matrix Orbital */
#define	USB_VENDOR_OVISLINK		0x1b75	/* OvisLink */
#define	USB_VENDOR_TML			0x1b91	/* The Mobility Lab */
#define	USB_VENDOR_TCTMOBILE	0x1bbb	/* TCT Mobile */
#define	USB_VENDOR_ALTI2		0x1bc9	/* Alti-2 products */
#define	USB_VENDOR_SUNPLUS		0x1bcf	/* Sunplus Innovation Technology Inc. */
#define	USB_VENDOR_WAGO			0x1be3	/* WAGO Kontakttechnik GmbH. */
#define	USB_VENDOR_TELIT		0x1bc7	/* Telit */
#define	USB_VENDOR_IONICS		0x1c0c	/* Ionics PlugComputer */
#define	USB_VENDOR_LONGCHEER	0x1c9e	/* Longcheer Holdings, Ltd. */
#define	USB_VENDOR_MPMAN		0x1cae	/* MpMan */
#define	USB_VENDOR_DRESDENELEKTRONIK	0x1cf1 /* dresden elektronik */
#define	USB_VENDOR_NEOTEL		0x1d09	/* Neotel */
#define	USB_VENDOR_DREAMLINK	0x1d34	/* Dream Link */
#define	USB_VENDOR_PEGATRON		0x1d4d	/* Pegatron */
#define	USB_VENDOR_QISDA		0x1da5	/* Qisda */
#define	USB_VENDOR_METAGEEK2	0x1dd5	/* MetaGeek */
#define	USB_VENDOR_ALINK		0x1e0e	/* Alink */
#define	USB_VENDOR_AIRTIES		0x1eda	/* AirTies */
#define	USB_VENDOR_FESTO		0x1e29	/* Festo */
#define	USB_VENDOR_LAKESHORE	0x1fb9	/* Lake Shore Cryotronics, Inc. */
#define	USB_VENDOR_VERTEX		0x1fe7	/* Vertex Wireless Co., Ltd. */
#define	USB_VENDOR_DLINK		0x2001	/* D-Link */
#define	USB_VENDOR_PLANEX2		0x2019	/* Planex Communications */
#define	USB_VENDOR_HAUPPAUGE2	0x2040	/* Hauppauge Computer Works */
#define	USB_VENDOR_TLAYTECH		0x20b9	/* Tlay Tech */
#define	USB_VENDOR_ENCORE		0x203d	/* Encore */
#define	USB_VENDOR_QIHARDWARE	0x20b7	/* QI-hardware */
#define	USB_VENDOR_PARA			0x20b8	/* PARA Industrial */
#define	USB_VENDOR_SIMTEC		0x20df	/* Simtec Electronics */
#define	USB_VENDOR_TRENDNET		0x20f4	/* TRENDnet */
#define	USB_VENDOR_RTSYSTEMS	0x2100	/* RTSYSTEMS */
#define	USB_VENDOR_VIALABS		0x2109	/* VIA Labs */
#define	USB_VENDOR_ERICSSON		0x2282	/* Ericsson */
#define	USB_VENDOR_MOTOROLA2	0x22b8	/* Motorola */
#define	USB_VENDOR_WETELECOM	0x22de	/* WeTelecom */
#define	USB_VENDOR_TPLINK		0x2357	/* TP-Link */
#define	USB_VENDOR_WESTMOUNTAIN	0x2405	/* West Mountain Radio */
#define	USB_VENDOR_TRIPPLITE	0x2478	/* Tripp-Lite */
#define	USB_VENDOR_HIROSE		0x2631	/* Hirose Electric */
#define	USB_VENDOR_NHJ			0x2770	/* NHJ */
#define	USB_VENDOR_PLANEX		0x2c02	/* Planex Communications */
#define	USB_VENDOR_QUECTEL		0x2c7c	/* Quectel Wireless Solutions */
#define	USB_VENDOR_VIDZMEDIA	0x3275	/* VidzMedia Pte Ltd */
#define	USB_VENDOR_LINKINSTRUMENTS	0x3195	/* Link Instruments Inc. */
#define	USB_VENDOR_AEI			0x3334	/* AEI */
#define	USB_VENDOR_HANK			0x3353	/* Hank Connection */
#define	USB_VENDOR_PQI			0x3538	/* PQI */
#define	USB_VENDOR_DAISY		0x3579	/* Daisy Technology */
#define	USB_VENDOR_NI			0x3923	/* National Instruments */
#define	USB_VENDOR_MICRONET		0x3980	/* Micronet Communications */
#define	USB_VENDOR_IODATA2		0x40bb	/* I-O Data */
#define	USB_VENDOR_IRIVER		0x4102	/* iRiver */
#define	USB_VENDOR_DELL			0x413c	/* Dell */
#define	USB_VENDOR_WCH			0x4348	/* QinHeng Electronics */
#define	USB_VENDOR_ACEECA		0x4766	/* Aceeca */
#define	USB_VENDOR_FEIXUN		0x4855	/* FeiXun Communication */
#define	USB_VENDOR_PAPOUCH		0x5050	/* Papouch products */
#define	USB_VENDOR_AVERATEC		0x50c2	/* Averatec */
#define	USB_VENDOR_SWEEX		0x5173	/* Sweex */
#define	USB_VENDOR_PROLIFIC2	0x5372	/* Prolific Technologies */
#define	USB_VENDOR_ONSPEC2		0x55aa	/* OnSpec Electronic Inc. */
#define	USB_VENDOR_ZINWELL		0x5a57	/* Zinwell */
#define	USB_VENDOR_SITECOM		0x6189	/* Sitecom */
#define	USB_VENDOR_ARKMICRO		0x6547	/* Arkmicro Technologies Inc. */
#define	USB_VENDOR_3COM2		0x6891	/* 3Com */
#define	USB_VENDOR_EDIMAX		0x7392	/* Edimax */
#define	USB_VENDOR_INTEL		0x8086	/* Intel */
#define	USB_VENDOR_INTEL2		0x8087	/* Intel */
#define	USB_VENDOR_ALLWIN		0x8516	/* ALLWIN Tech */
#define	USB_VENDOR_SITECOM2		0x9016	/* Sitecom */
#define	USB_VENDOR_MOSCHIP		0x9710	/* MosChip Semiconductor */
#define	USB_VENDOR_NETGEAR4		0x9846	/* Netgear */
#define	USB_VENDOR_MARVELL		0x9e88	/* Marvell Technology Group Ltd. */
#define	USB_VENDOR_3COM3		0xa727	/* 3Com */
#define	USB_VENDOR_CACE			0xcace	/* CACE Technologies */
#define	USB_VENDOR_EVOLUTION	0xdeee	/* Evolution Robotics products */
#define	USB_VENDOR_DATAAPEX		0xdaae	/* DataApex */
#define	USB_VENDOR_HP2			0xf003	/* Hewlett Packard */
#define	USB_VENDOR_LOGILINK		0xfc08	/* LogiLink */
#define	USB_VENDOR_USRP			0xfffe	/* GNU Radio USRP */

/*
 * List of known products.	Grouped by vendor.
 */

/* 3Com products */
#define	USB_PRODUCT_3COM_HOMECONN		0x009d	/* HomeConnect Camera */
#define	USB_PRODUCT_3COM_3CREB96		0x00a0	/* Bluetooth #define	USB_Adapter */
#define	USB_PRODUCT_3COM_3C19250		0x03e8	/* 3C19250 Ethernet Adapter */
#define	USB_PRODUCT_3COM_3CRSHEW696		0x0a01	/* 3CRSHEW696 Wireless Adapter */
#define	USB_PRODUCT_3COM_3C460			0x11f8	/* HomeConnect 3C460 */
#define	USB_PRODUCT_3COM_USR56K			0x3021	/* U.S.Robotics 56000 Voice FaxModem Pro */
#define	USB_PRODUCT_3COM_3C460B			0x4601	/* HomeConnect 3C460B */
#define	USB_PRODUCT_3COM2_3CRUSB10075	0xa727	/* 3CRUSB10075 */
#define	USB_PRODUCT_3COM3_AR5523_1		0x6893	/* AR5523 */
#define	USB_PRODUCT_3COM3_AR5523_2		0x6895	/* AR5523 */
#define	USB_PRODUCT_3COM3_AR5523_3		0x6897	/* AR5523 */

#define	USB_PRODUCT_3COMUSR_OFFICECONN	0x0082	/* 3Com OfficeConnect Analog Modem */
#define	USB_PRODUCT_3COMUSR_USRISDN		0x008f	/* 3Com U.S. Robotics Pro ISDN TA */
#define	USB_PRODUCT_3COMUSR_HOMECONN	0x009d	/* 3Com HomeConnect Camera */
#define	USB_PRODUCT_3COMUSR_USR56K		0x3021	/* U.S. Robotics 56000 Voice FaxModem Pro */

/* ABIT products */
#define	USB_PRODUCT_ABIT_AK_020			0x7d0e	/* 3G modem */

/* AboCom products */
#define	USB_PRODUCT_ABOCOM_XX1			0x110c	/* XX1 */
#define	USB_PRODUCT_ABOCOM_XX2			0x200c	/* XX2 */
#define	USB_PRODUCT_ABOCOM_RT2770		0x2770	/* RT2770 */
#define	USB_PRODUCT_ABOCOM_RT2870		0x2870	/* RT2870 */
#define	USB_PRODUCT_ABOCOM_RT3070		0x3070	/* RT3070 */
#define	USB_PRODUCT_ABOCOM_RT3071		0x3071	/* RT3071 */
#define	USB_PRODUCT_ABOCOM_RT3072		0x3072	/* RT3072 */
#define	USB_PRODUCT_ABOCOM2_RT2870_1	0x3c09	/* RT2870 */
#define	USB_PRODUCT_ABOCOM_URE450		0x4000	/* URE450 Ethernet Adapter */
#define	USB_PRODUCT_ABOCOM_UFE1000		0x4002	/* UFE1000 Fast Ethernet Adapter */
#define	USB_PRODUCT_ABOCOM_DSB650TX_PNA	0x4003	/* 1/10/100 Ethernet Adapter */
#define	USB_PRODUCT_ABOCOM_XX4			0x4004	/* XX4 */
#define	USB_PRODUCT_ABOCOM_XX5			0x4007	/* XX5 */
#define	USB_PRODUCT_ABOCOM_XX6			0x400b	/* XX6 */
#define	USB_PRODUCT_ABOCOM_XX7			0x400c	/* XX7 */
#define	USB_PRODUCT_ABOCOM_RTL8151		0x401a	/* RTL8151 */
#define	USB_PRODUCT_ABOCOM_XX8			0x4102	/* XX8 */
#define	USB_PRODUCT_ABOCOM_XX9			0x4104	/* XX9 */
#define	USB_PRODUCT_ABOCOM_UF200		0x420a	/* UF200 Ethernet */
#define	USB_PRODUCT_ABOCOM_WL54			0x6001	/* WL54 */
#define	USB_PRODUCT_ABOCOM_XX10			0xabc1	/* XX10 */
#define	USB_PRODUCT_ABOCOM_BWU613		0xb000	/* BWU613 */
#define	USB_PRODUCT_ABOCOM_HWU54DM		0xb21b	/* HWU54DM */
#define	USB_PRODUCT_ABOCOM_RT2573_2		0xb21c	/* RT2573 */
#define	USB_PRODUCT_ABOCOM_RT2573_3		0xb21d	/* RT2573 */
#define	USB_PRODUCT_ABOCOM_RT2573_4		0xb21e	/* RT2573 */
#define	USB_PRODUCT_ABOCOM_RTL8188CU_1	0x8188	/* RTL8188CU */
#define	USB_PRODUCT_ABOCOM_RTL8188CU_2	0x8189	/* RTL8188CU */
#define	USB_PRODUCT_ABOCOM_RTL8192CU	0x8178	/* RTL8192CU */
#define	USB_PRODUCT_ABOCOM_RTL8188EU	0x8179	/* RTL8188EU */
#define	USB_PRODUCT_ABOCOM_WUG2700		0xb21f	/* WUG2700 */

/* Acton Research Corp. */
#define	USB_PRODUCT_ACTON_SPECTRAPRO	0x0100	/* FTDI compatible adapter */

/* Accton products */
#define	USB_PRODUCT_ACCTON_USB320_EC	0x1046	/* USB320-EC Ethernet Adapter */
#define	USB_PRODUCT_ACCTON_2664W		0x3501	/* 2664W */
#define	USB_PRODUCT_ACCTON_111			0x3503	/* T-Sinus 111 Wireless Adapter */
#define	USB_PRODUCT_ACCTON_SMCWUSBG_NF	0x4505	/* SMCWUSB-G (no firmware) */
#define	USB_PRODUCT_ACCTON_SMCWUSBG		0x4506	/* SMCWUSB-G */
#define	USB_PRODUCT_ACCTON_SMCWUSBTG2_NF	0x4507	/* SMCWUSBT-G2 (no firmware) */
#define	USB_PRODUCT_ACCTON_SMCWUSBTG2	0x4508	/* SMCWUSBT-G2 */
#define	USB_PRODUCT_ACCTON_PRISM_GT		0x4521	/* PrismGT #define	USB_2.0 WLAN */
#define	USB_PRODUCT_ACCTON_SS1001		0x5046	/* SpeedStream Ethernet Adapter */
#define	USB_PRODUCT_ACCTON_RT2870_2		0x6618	/* RT2870 */
#define	USB_PRODUCT_ACCTON_RT3070		0x7511	/* RT3070 */
#define	USB_PRODUCT_ACCTON_RT2770		0x7512	/* RT2770 */
#define	USB_PRODUCT_ACCTON_RT2870_3		0x7522	/* RT2870 */
#define	USB_PRODUCT_ACCTON_RT2870_5		0x8522	/* RT2870 */
#define	USB_PRODUCT_ACCTON_RT3070_4		0xa512	/* RT3070 */
#define	USB_PRODUCT_ACCTON_RT2870_4		0xa618	/* RT2870 */
#define	USB_PRODUCT_ACCTON_RT3070_1		0xa701	/* RT3070 */
#define	USB_PRODUCT_ACCTON_RT3070_2		0xa702	/* RT3070 */
#define	USB_PRODUCT_ACCTON_RT2870_1		0xb522	/* RT2870 */
#define	USB_PRODUCT_ACCTON_RT3070_3		0xc522	/* RT3070 */
#define	USB_PRODUCT_ACCTON_RT3070_5		0xd522	/* RT3070 */
#define	USB_PRODUCT_ACCTON_RTL8192SU	0xc512	/* RTL8192SU */
#define	USB_PRODUCT_ACCTON_ZD1211B		0xe501	/* ZD1211B */
#define	USB_PRODUCT_ACCTON_WN7512		0xf522	/* WN7512 */

/* Aceeca products */
#define	USB_PRODUCT_ACEECA_MEZ1000		0x0001	/* MEZ1000 RDA */

/* Acer Communications & Multimedia (oemd by Surecom) */
#define	USB_PRODUCT_ACERCM_EP1427X2		0x0893	/* EP-1427X-2 Ethernet Adapter */

/* Acer Labs products */
#define	USB_PRODUCT_ACERLABS_M5632		0x5632	/* #define	USB_2.0 Data Link */

/* Acer Peripherals, Inc. products */
#define	USB_PRODUCT_ACERP_ACERSCAN_C310U	0x12a6	/* Acerscan C310U */
#define	USB_PRODUCT_ACERP_ACERSCAN_320U		0x2022	/* Acerscan 320U */
#define	USB_PRODUCT_ACERP_ACERSCAN_640U		0x2040	/* Acerscan 640U */
#define	USB_PRODUCT_ACERP_ACERSCAN_620U		0x2060	/* Acerscan 620U */
#define	USB_PRODUCT_ACERP_ACERSCAN_4300U	0x20b0	/* Benq 3300U/4300U */
#define	USB_PRODUCT_ACERP_ACERSCAN_640BT	0x20be	/* Acerscan 640BT */
#define	USB_PRODUCT_ACERP_ACERSCAN_1240U	0x20c0	/* Acerscan 1240U */
#define	USB_PRODUCT_ACERP_S81				0x4027	/* BenQ S81 phone */
#define	USB_PRODUCT_ACERP_H10				0x4068	/* AWL400 Wireless Adapter */
#define	USB_PRODUCT_ACERP_ATAPI				0x6003	/* ATA/ATAPI Adapter */
#define	USB_PRODUCT_ACERP_AWL300			0x9000	/* AWL300 Wireless Adapter */
#define	USB_PRODUCT_ACERP_AWL400			0x9001	/* AWL400 Wireless Adapter */

/* Acer Warp products */
#define	USB_PRODUCT_ACERW_WARPLINK		0x0204	/* Warplink */

/* Actions products */
#define	USB_PRODUCT_ACTIONS_MP4			0x1101	/* Actions MP4 Player */

/* Actiontec, Inc. products */
#define	USB_PRODUCT_ACTIONTEC_PRISM_25	0x0408	/* Prism2.5 Wireless Adapter */
#define	USB_PRODUCT_ACTIONTEC_PRISM_25A	0x0421	/* Prism2.5 Wireless Adapter A */
#define	USB_PRODUCT_ACTIONTEC_FREELAN	0x6106	/* ROPEX FreeLan 802.11b */
#define	USB_PRODUCT_ACTIONTEC_UAT1		0x7605	/* UAT1 Wireless Ethernet Adapter */

/* ACTiSYS products */
#define	USB_PRODUCT_ACTISYS_IR2000U		0x0011	/* ACT-IR2000U FIR */

/* ActiveWire, Inc. products */
#define	USB_PRODUCT_ACTIVEWIRE_IOBOARD		0x0100	/* I/O Board */
#define	USB_PRODUCT_ACTIVEWIRE_IOBOARD_FW1	0x0101	/* I/O Board, rev. 1 firmware */

/* Adaptec products */
#define	USB_PRODUCT_ADAPTEC_AWN8020			0x0020	/* AWN-8020 WLAN */

/* Addtron products */
#define	USB_PRODUCT_ADDTRON_AWU120			0xff31	/* AWU-120 */

/* ADLINK Texhnology products */
#define	USB_PRODUCT_ADLINK_ND6530			0x6530	/* ND-6530 USB-Serial */

/* ADMtek products */
#define	USB_PRODUCT_ADMTEK_PEGASUSII_4	0x07c2	/* AN986A Ethernet */
#define	USB_PRODUCT_ADMTEK_PEGASUS		0x0986	/* AN986 Ethernet */
#define	USB_PRODUCT_ADMTEK_PEGASUSII	0x8511	/* AN8511 Ethernet */
#define	USB_PRODUCT_ADMTEK_PEGASUSII_2	0x8513	/* AN8513 Ethernet */
#define	USB_PRODUCT_ADMTEK_PEGASUSII_3	0x8515	/* AN8515 Ethernet */

/* ADDON products */
/* PNY OEMs these */
#define	USB_PRODUCT_ADDON_ATTACHE		0x1300	/* #define	USB_2.0 Flash Drive */
#define	USB_PRODUCT_ADDON_ATTACHE		0x1300	/* #define	USB_2.0 Flash Drive */
#define	USB_PRODUCT_ADDON_A256MB		0x1400	/* Attache 256MB #define	USB_2.0 Flash Drive */

/* #define	USB_2.0 Flash Drive (DANE-ELEC zMate 512MB #define	USB_flash drive) */
#define	USB_PRODUCT_ADDON_DISKPRO512	0x1420

/* Addonics products */
#define	USB_PRODUCT_ADDONICS2_CABLE_205	0xa001	/* Cable 205 */

/* ADS products */
#define	USB_PRODUCT_ADS_UBS10BT			0x0008	/* UBS-10BT Ethernet */
#define	USB_PRODUCT_ADS_UBS10BTX		0x0009	/* UBS-10BT Ethernet */

/* AEI products */
#define	USB_PRODUCT_AEI_FASTETHERNET	0x1701	/* Fast Ethernet */

/* Afatech Technologies, Inc. */
#define	USB_PRODUCT_AFATECH_AFATECH1336	0x1336	/* Flash Card Reader */

/* Agate Technologies products */
#define	USB_PRODUCT_AGATE_QDRIVE		0x0378	/* Q-Drive */

/* AGFA products */
#define	USB_PRODUCT_AGFA_SNAPSCAN1212U	0x0001	/* SnapScan 1212U */
#define	USB_PRODUCT_AGFA_SNAPSCAN1236U	0x0002	/* SnapScan 1236U */
#define	USB_PRODUCT_AGFA_SNAPSCANTOUCH	0x0100	/* SnapScan Touch */
#define	USB_PRODUCT_AGFA_SNAPSCAN1212U2	0x2061	/* SnapScan 1212U */
#define	USB_PRODUCT_AGFA_SNAPSCANE40	0x208d	/* SnapScan e40 */
#define	USB_PRODUCT_AGFA_SNAPSCANE50	0x208f	/* SnapScan e50 */
#define	USB_PRODUCT_AGFA_SNAPSCANE20	0x2091	/* SnapScan e20 */
#define	USB_PRODUCT_AGFA_SNAPSCANE25	0x2095	/* SnapScan e25 */
#define	USB_PRODUCT_AGFA_SNAPSCANE26	0x2097	/* SnapScan e26 */
#define	USB_PRODUCT_AGFA_SNAPSCANE52	0x20fd	/* SnapScan e52 */

/* Ain Communication Technology products */
#define	USB_PRODUCT_AINCOMM_AWU2000B		0x1001	/* AWU2000B Wireless Adapter */

/* AIPTEK products */
#define	USB_PRODUCT_AIPTEK_POCKETCAM3M		0x2011	/* PocketCAM 3Mega */
#define	USB_PRODUCT_AIPTEK2_PENCAM_MEGA_1_3	0x504a	/* PenCam Mega 1.3 */
#define	USB_PRODUCT_AIPTEK2_SUNPLUS_TECH	0x0c15	/* Sunplus Technology Inc. */

/* AirPlis products */
#define	USB_PRODUCT_AIRPLUS_MCD650		0x3198	/* MCD650 modem */

/* AirPrime products */
#define	USB_PRODUCT_AIRPRIME_PC5220		0x0112	/* CDMA Wireless PC Card */
#define	USB_PRODUCT_AIRPRIME_USB308		0x68A3	/* USB308 HSPA+ #define	USB_Modem */
#define	USB_PRODUCT_AIRPRIME_AC313U		0x68aa	/* Sierra Wireless AirCard 313U */

/* AirTies products */
#define	USB_PRODUCT_AIRTIES_RT3070		0x2310	/* RT3070 */

/* AKS products */
#define	USB_PRODUCT_AKS_USBHASP			0x0001	/* USB-HASP 0.06 */

/* Alcatel products */
#define	USB_PRODUCT_ALCATEL_OT535		0x02df	/* One Touch 535/735 */

/* Alcor Micro, Inc. products */
#define	USB_PRODUCT_ALCOR2_KBD_HUB		0x2802	/* Kbd Hub */

#define	USB_PRODUCT_ALCOR_DUMMY			0x0000	/* Dummy product */
#define	USB_PRODUCT_ALCOR_SDCR_6335		0x6335	/* SD/MMC Card Reader */
#define	USB_PRODUCT_ALCOR_SDCR_6362		0x6362	/* SD/MMC Card Reader */
#define	USB_PRODUCT_ALCOR_SDCR_6366		0x6366	/* SD/MMC Card Reader */
#define	USB_PRODUCT_ALCOR_TRANSCEND		0x6387	/* Transcend JetFlash Drive */
#define	USB_PRODUCT_ALCOR_MA_KBD_HUB	0x9213	/* MacAlly Kbd Hub */
#define	USB_PRODUCT_ALCOR_AU9814		0x9215	/* AU9814 Hub */
#define	USB_PRODUCT_ALCOR_UMCR_9361		0x9361	/* #define	USB_Multimedia Card Reader */
#define	USB_PRODUCT_ALCOR_SM_KBD		0x9410	/* MicroConnectors/StrongMan Keyboard */
#define	USB_PRODUCT_ALCOR_NEC_KBD_HUB	0x9472	/* NEC Kbd Hub */
#define	USB_PRODUCT_ALCOR_AU9720		0x9720	/* USB2 - RS-232 */
#define	USB_PRODUCT_ALCOR_AU6390		0x6390	/* AU6390 USB-IDE converter */

/* Alink products */
#define	USB_PRODUCT_ALINK_DWM652U5	0xce16	/* DWM-652 */
#define	USB_PRODUCT_ALINK_3G		0x9000	/* 3G modem */
#define	USB_PRODUCT_ALINK_SIM7600E	0x9001	/* LTE modem */
#define	USB_PRODUCT_ALINK_3GU		0x9200	/* 3G modem */

/* Altec Lansing products */
#define	USB_PRODUCT_ALTEC_ADA70		0x0070	/* ADA70 Speakers */
#define	USB_PRODUCT_ALTEC_ASC495	0xff05	/* ASC495 Speakers */

/* Alti-2 products */
#define	USB_PRODUCT_ALTI2_N3		0x6001	/* FTDI compatible adapter */

/* Allied Telesyn International products */
#define	USB_PRODUCT_ALLIEDTELESYN_ATUSB100	0xb100	/* AT-USB100 */

/* ALLWIN Tech products */
#define	USB_PRODUCT_ALLWIN_RT2070		0x2070	/* RT2070 */
#define	USB_PRODUCT_ALLWIN_RT2770		0x2770	/* RT2770 */
#define	USB_PRODUCT_ALLWIN_RT2870		0x2870	/* RT2870 */
#define	USB_PRODUCT_ALLWIN_RT3070		0x3070	/* RT3070 */
#define	USB_PRODUCT_ALLWIN_RT3071		0x3071	/* RT3071 */
#define	USB_PRODUCT_ALLWIN_RT3072		0x3072	/* RT3072 */
#define	USB_PRODUCT_ALLWIN_RT3572		0x3572	/* RT3572 */

/* AlphaSmart, Inc. products */
#define	USB_PRODUCT_ALPHASMART_DANA_KB		0xdbac	/* AlphaSmart Dana Keyboard */
#define	USB_PRODUCT_ALPHASMART_DANA_SYNC	0xdf00	/* AlphaSmart Dana HotSync */

/* Amoi products */
#define	USB_PRODUCT_AMOI_H01		0x0800	/* H01 3G modem */
#define	USB_PRODUCT_AMOI_H01A		0x7002	/* H01A 3G modem */
#define	USB_PRODUCT_AMOI_H02		0x0802	/* H02 3G modem */

/* American Power Conversion products */
#define	USB_PRODUCT_APC_UPS			0x0002	/* Uninterruptible Power Supply */

/* Ambit Microsystems products */
#define	USB_PRODUCT_AMBIT_WLAN		0x0302	/* WLAN */
#define	USB_PRODUCT_AMBIT_NTL_250	0x6098	/* NTL 250 cable modem */

/* Apacer products */
#define	USB_PRODUCT_APACER_HT202	0xb113	/* #define	USB_2.0 Flash Drive */

/* American Power Conversion products */
#define	USB_PRODUCT_APC_UPS			0x0002	/* Uninterruptible Power Supply */

/* Amigo Technology products */
#define	USB_PRODUCT_AMIGO_RT2870_1		0x9031	/* RT2870 */
#define	USB_PRODUCT_AMIGO_RT2870_2		0x9041	/* RT2870 */

/* AMIT products */
#define	USB_PRODUCT_AMIT_CGWLUSB2GO		0x0002	/* CG-WLUSB2GO */
#define	USB_PRODUCT_AMIT_CGWLUSB2GNR	0x0008	/* CG-WLUSB2GNR */
#define	USB_PRODUCT_AMIT_RT2870_1		0x0012	/* RT2870 */

/* AMIT(2) products */
#define	USB_PRODUCT_AMIT2_RT2870		0x0008	/* RT2870 */

/* Analog Devices products */
#define	USB_PRODUCT_ANALOGDEVICES_GNICE		0xf000	/* FTDI compatible adapter */
#define	USB_PRODUCT_ANALOGDEVICES_GNICEPLUS	0xf001	/* FTDI compatible adapter */

/* Anchor products */
#define	USB_PRODUCT_ANCHOR_SERIAL		0x2008	/* Serial */
#define	USB_PRODUCT_ANCHOR_EZUSB		0x2131	/* EZUSB */
#define	USB_PRODUCT_ANCHOR_EZLINK		0x2720	/* EZLINK */

/* AnyData products */
#define	USB_PRODUCT_ANYDATA_ADU_620UW	0x6202	/* CDMA 2000 EV-DO #define	USB_Modem */
#define	USB_PRODUCT_ANYDATA_ADU_E100X	0x6501	/* CDMA 2000 1xRTT/EV-DO #define	USB_Modem */
#define	USB_PRODUCT_ANYDATA_ADU_500A	0x6502	/* CDMA 2000 EV-DO #define	USB_Modem */

/* AOX, Inc. products */
#define	USB_PRODUCT_AOX_USB101			0x0008	/* Ethernet */

/* American Power Conversion products */
#define	USB_PRODUCT_APC_UPS				0x0002	/* Uninterruptible Power Supply */

/* Apple Computer products */
#define	USB_PRODUCT_APPLE_DUMMY			0x0000	/* Dummy product */
#define	USB_PRODUCT_APPLE_IMAC_KBD		0x0201	/* USB iMac Keyboard */
#define	USB_PRODUCT_APPLE_KBD			0x0202	/* USB Keyboard M2452 */
#define	USB_PRODUCT_APPLE_EXT_KBD		0x020c	/* Apple Extended USB Keyboard */
/* MacbookAir, aka wellspring */
#define	USB_PRODUCT_APPLE_WELLSPRING_ANSI	0x0223	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING_ISO	0x0224	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING_JIS	0x0225	/* Apple Internal Keyboard/Trackpad */
/* MacbookProPenryn, aka wellspring2 */
#define	USB_PRODUCT_APPLE_WELLSPRING2_ANSI	0x0230	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING2_ISO	0x0231	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING2_JIS	0x0232	/* Apple Internal Keyboard/Trackpad */
/* Macbook5,1 (unibody), aka wellspring3 */
#define	USB_PRODUCT_APPLE_WELLSPRING3_ANSI	0x0236	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING3_ISO	0x0237	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING3_JIS	0x0238	/* Apple Internal Keyboard/Trackpad */
/* MacbookAir3,2 (unibody), aka wellspring4 */
#define	USB_PRODUCT_APPLE_WELLSPRING4_ANSI	0x023f	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING4_ISO	0x0240	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING4_JIS	0x0241	/* Apple Internal Keyboard/Trackpad */
/* MacbookAir3,1 (unibody), aka wellspring4 */
#define	USB_PRODUCT_APPLE_WELLSPRING4A_ANSI	0x0242	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING4A_ISO	0x0243	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING4A_JIS	0x0244	/* Apple Internal Keyboard/Trackpad */
/* Macbook8 (unibody, March 2011) */
#define	USB_PRODUCT_APPLE_WELLSPRING5_ANSI	0x0245	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING5_ISO	0x0246	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING5_JIS	0x0247	/* Apple Internal Keyboard/Trackpad */
/* MacbookAir4,1 (unibody, July 2011) */
#define	USB_PRODUCT_APPLE_WELLSPRING6A_ANSI	0x0249	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING6A_ISO	0x024a	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING6A_JIS	0x024b	/* Apple Internal Keyboard/Trackpad */
/* MacbookAir4,2 (unibody, July 2011) */
#define	USB_PRODUCT_APPLE_WELLSPRING6_ANSI	0x024c	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING6_ISO	0x024d	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING6_JIS	0x024e	/* Apple Internal Keyboard/Trackpad */
/* Macbook8,2 (unibody) */
#define	USB_PRODUCT_APPLE_WELLSPRING5A_ANSI	0x0252	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING5A_ISO	0x0253	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING5A_JIS	0x0254	/* Apple Internal Keyboard/Trackpad */
/* MacbookPro10,1 (unibody, June 2012) */
#define	USB_PRODUCT_APPLE_WELLSPRING7_ANSI	0x0262	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING7_ISO	0x0263	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING7_JIS	0x0264	/* Apple Internal Keyboard/Trackpad */
/* MacbookPro10,2 (unibody, October 2012) */
#define	USB_PRODUCT_APPLE_WELLSPRING7A_ANSI	0x0259	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING7A_ISO	0x025a	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING7A_JIS	0x025b	/* Apple Internal Keyboard/Trackpad */
/* MacbookAir6,2 (unibody, June 2013) */
#define	USB_PRODUCT_APPLE_WELLSPRING8_ANSI	0x0290	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING8_ISO	0x0291	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING8_JIS	0x0292	/* Apple Internal Keyboard/Trackpad */
/* MacbookPro12,1 */
#define	USB_PRODUCT_APPLE_WELLSPRING9_ANSI	0x0272	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING9_ISO	0x0273	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_WELLSPRING9_JIS	0x0274	/* Apple Internal Keyboard/Trackpad */
#define	USB_PRODUCT_APPLE_MOUSE			0x0301	/* Mouse M4848 */
#define	USB_PRODUCT_APPLE_OPTMOUSE		0x0302	/* Optical mouse */
#define	USB_PRODUCT_APPLE_MIGHTYMOUSE	0x0304	/* Mighty Mouse */
#define	USB_PRODUCT_APPLE_KBD_HUB		0x1001	/* Hub in Apple #define	USB_Keyboard */
#define	USB_PRODUCT_APPLE_EXT_KBD_HUB	0x1003	/* Hub in Apple Extended #define	USB_Keyboard */
#define	USB_PRODUCT_APPLE_SPEAKERS		0x1101	/* Speakers */
#define	USB_PRODUCT_APPLE_IPOD			0x1201	/* iPod */
#define	USB_PRODUCT_APPLE_IPOD2G		0x1202	/* iPod 2G */
#define	USB_PRODUCT_APPLE_IPOD3G		0x1203	/* iPod 3G */
#define	USB_PRODUCT_APPLE_IPOD_04		0x1204	/* iPod '04' */
#define	USB_PRODUCT_APPLE_IPODMINI		0x1205	/* iPod Mini */
#define	USB_PRODUCT_APPLE_IPOD_06		0x1206	/* iPod '06' */
#define	USB_PRODUCT_APPLE_IPOD_07		0x1207	/* iPod '07' */
#define	USB_PRODUCT_APPLE_IPOD_08		0x1208	/* iPod '08' */
#define	USB_PRODUCT_APPLE_IPODVIDEO		0x1209	/* iPod Video */
#define	USB_PRODUCT_APPLE_IPODNANO		0x120a	/* iPod Nano */
#define	USB_PRODUCT_APPLE_IPHONE		0x1290	/* iPhone */
#define	USB_PRODUCT_APPLE_IPOD_TOUCH	0x1291	/* iPod Touch */
#define	USB_PRODUCT_APPLE_IPHONE_3G		0x1292	/* iPhone 3G */
#define	USB_PRODUCT_APPLE_IPHONE_3GS	0x1294	/* iPhone 3GS */
#define	USB_PRODUCT_APPLE_IPHONE_4		0x1297	/* iPhone 4 */
#define	USB_PRODUCT_APPLE_IPHONE_4S		0x12a0	/* iPhone 4S */
#define	USB_PRODUCT_APPLE_IPHONE_5		0x12a8	/* iPhone 5 */
#define	USB_PRODUCT_APPLE_IPAD			0x129a	/* iPad */
#define	USB_PRODUCT_APPLE_ETHERNET		0x1402	/* Ethernet A1277 */
#define	USB_PRODUCT_APPLE_BLUETOOTH2	0x8205	 /* Bluetooth */
#define	USB_PRODUCT_APPLE_BLUETOOTH		0x8300	 /* Bluetooth */
#define	USB_PRODUCT_APPLE_ISIGHT_1		0x8501	 /* iSight */
#define	USB_PRODUCT_APPLE_ISIGHT		0x8502	 /* iSight */

/* Arkmicro Technologies */
#define	USB_PRODUCT_ARKMICRO_ARK3116		0x0232	/* ARK3116 Serial */

/* Asahi Optical products */
#define	USB_PRODUCT_ASAHIOPTICAL_OPTIO230	0x0004	/* Digital camera */
#define	USB_PRODUCT_ASAHIOPTICAL_OPTIO330	0x0006	/* Digital camera */

/* Asante products */
#define	USB_PRODUCT_ASANTE_EA				0x1427	/* Ethernet */

/* ASIX Electronics products */
#define	USB_PRODUCT_ASIX_AX88172		0x1720	/* 10/100 Ethernet */
#define	USB_PRODUCT_ASIX_AX88178		0x1780	/* AX88178 */
#define	USB_PRODUCT_ASIX_AX88178A		0x178a	/* AX88178A #define	USB_2.0 10/100/1000 Ethernet */
#define	USB_PRODUCT_ASIX_AX88179		0x1790	/* AX88179 #define	USB_3.0 10/100/1000 Ethernet */
#define	USB_PRODUCT_ASIX_AX88772		0x7720	/* AX88772 */
#define	USB_PRODUCT_ASIX_AX88772A		0x772a	/* AX88772A #define	USB_2.0 10/100 Ethernet */
#define	USB_PRODUCT_ASIX_AX88772B		0x772b	/* AX88772B #define	USB_2.0 10/100 Ethernet */
#define	USB_PRODUCT_ASIX_AX88772B_1		0x7e2b	/* AX88772B #define	USB_2.0 10/100 Ethernet */

/* ASUS products */
#define	USB_PRODUCT_ASUS2_USBN11		0x0b05	/* USB-N11 */
#define	USB_PRODUCT_ASUS_RT2570			0x1706	/* RT2500#define	USB_Wireless Adapter */
#define	USB_PRODUCT_ASUS_WL167G			0x1707	/* WL-167g Wireless Adapter */
#define	USB_PRODUCT_ASUS_WL159G			0x170c	/* WL-159g */
#define	USB_PRODUCT_ASUS_A9T_WIFI		0x171b	/* A9T wireless */
#define	USB_PRODUCT_ASUS_P5B_WIFI		0x171d	/* P5B wireless */
#define	USB_PRODUCT_ASUS_RT2573_1		0x1723	/* RT2573 */
#define	USB_PRODUCT_ASUS_RT2573_2		0x1724	/* RT2573 */
#define	USB_PRODUCT_ASUS_LCM			0x1726	/* LCM display */
#define	USB_PRODUCT_ASUS_RT2870_1		0x1731	/* RT2870 */
#define	USB_PRODUCT_ASUS_RT2870_2		0x1732	/* RT2870 */
#define	USB_PRODUCT_ASUS_RT2870_3		0x1742	/* RT2870 */
#define	USB_PRODUCT_ASUS_RT2870_4		0x1760	/* RT2870 */
#define	USB_PRODUCT_ASUS_RT2870_5		0x1761	/* RT2870 */
#define	USB_PRODUCT_ASUS_USBN13			0x1784	/* USB-N13 */
#define	USB_PRODUCT_ASUS_USBN10			0x1786	/* USB-N10 */
#define	USB_PRODUCT_ASUS_RT3070_1		0x1790	/* RT3070 */
#define	USB_PRODUCT_ASUS_RTL8192SU		0x1791	/* RTL8192SU */
#define	USB_PRODUCT_ASUS_USB_N53		0x179d	/* ASUS Black Diamond Dual Band USB-N53 */
#define	USB_PRODUCT_ASUS_RTL8192CU		0x17ab	/* RTL8192CU */
#define	USB_PRODUCT_ASUS_USBN66			0x17ad	/* USB-N66 */
#define	USB_PRODUCT_ASUS_USBN10NANO		0x17ba	/* USB-N10 Nano */
#define	USB_PRODUCT_ASUS_USBAC51		0x17d1	/* USB-AC51 */
#define	USB_PRODUCT_ASUS_A730W			0x4202	/* ASUS MyPal A730W */
#define	USB_PRODUCT_ASUS_P535			0x420f	/* ASUS P535 PDA */
#define	USB_PRODUCT_ASUS_GMSC			0x422f	/* ASUS Generic Mass Storage */

/* ATen products */
#define	USB_PRODUCT_ATEN_UC1284		0x2001	/* Parallel printer */
#define	USB_PRODUCT_ATEN_UC10T		0x2002	/* 10Mbps Ethernet */
#define	USB_PRODUCT_ATEN_UC110T		0x2007	/* UC-110T Ethernet */
#define	USB_PRODUCT_ATEN_UC232A		0x2008	/* Serial */
#define	USB_PRODUCT_ATEN_UC210T		0x2009	/* UC-210T Ethernet */
#define	USB_PRODUCT_ATEN_DSB650C	0x4000	/* DSB-650C */

/* ATP Electronics products */
#define	USB_PRODUCT_ATP_EUSB				0xaf01	/* ATP IG e#define	USB_SSD */

/* Atheros Communications products */
#define	USB_PRODUCT_ATHEROS_AR5523			0x0001	/* AR5523 */
#define	USB_PRODUCT_ATHEROS_AR5523_NF		0x0002	/* AR5523 (no firmware) */
#define	USB_PRODUCT_ATHEROS2_AR5523_1		0x0001	/* AR5523 */
#define	USB_PRODUCT_ATHEROS2_AR5523_1_NF	0x0002	/* AR5523 (no firmware) */
#define	USB_PRODUCT_ATHEROS2_AR5523_2		0x0003	/* AR5523 */
#define	USB_PRODUCT_ATHEROS2_AR5523_2_NF	0x0004	/* AR5523 (no firmware) */
#define	USB_PRODUCT_ATHEROS2_AR5523_3		0x0005	/* AR5523 */
#define	USB_PRODUCT_ATHEROS2_AR5523_3_NF	0x0006	/* AR5523 (no firmware) */
#define	USB_PRODUCT_ATHEROS2_TG121N			0x1001	/* TG121N */
#define	USB_PRODUCT_ATHEROS2_WN821NV2		0x1002	/* WN821NV2 */
#define	USB_PRODUCT_ATHEROS2_3CRUSBN275		0x1010	/* 3CRUSBN275 */
#define	USB_PRODUCT_ATHEROS2_WN612			0x1011	/* WN612 */
#define	USB_PRODUCT_ATHEROS2_AR9170			0x9170	/* AR9170 */

/* Atmel Comp. products */
#define	USB_PRODUCT_ATMEL_STK541		0x2109	/* Zigbee Controller */
#define	USB_PRODUCT_ATMEL_UHB124		0x3301	/* UHB124 hub */
#define	USB_PRODUCT_ATMEL_DWL120		0x7603	/* DWL-120 Wireless Adapter */
#define	USB_PRODUCT_ATMEL_BW002			0x7605	/* BW002 Wireless Adapter */
#define	USB_PRODUCT_ATMEL_WL1130USB		0x7613	/* WL-1130 USB */
#define	USB_PRODUCT_ATMEL_AT76C505A		0x7614	/* AT76c505a Wireless Adapter */

/* AuthenTec products */
#define	USB_PRODUCT_AUTHENTEC_AES1610	0x1600	/* AES1610 Fingerprint Sensor */

/* Avision products */
#define	USB_PRODUCT_AVISION_1200U		0x0268	/* 1200U scanner */

/* AVM products */
#define	USB_PRODUCT_AVM_FRITZWLAN		0x8401	/* FRITZ!WLAN N */

/* Axesstel products */
#define	USB_PRODUCT_AXESSTEL_DATAMODEM	0x1000	/* Data Modem */

/* AsureWave products */
#define	USB_PRODUCT_AZUREWAVE_RT2870_1		0x3247	/* RT2870 */
#define	USB_PRODUCT_AZUREWAVE_RT2870_2		0x3262	/* RT2870 */
#define	USB_PRODUCT_AZUREWAVE_RT3070_1		0x3273	/* RT3070 */
#define	USB_PRODUCT_AZUREWAVE_RT3070_2		0x3284	/* RT3070 */
#define	USB_PRODUCT_AZUREWAVE_RT3070_3		0x3305	/* RT3070 */
#define	USB_PRODUCT_AZUREWAVE_RTL8188CU		0x3357	/* RTL8188CU */
#define	USB_PRODUCT_AZUREWAVE_RTL8188CE_1	0x3358	/* RTL8188CE */
#define	USB_PRODUCT_AZUREWAVE_RTL8188CE_2	0x3359	/* RTL8188CE */
#define	USB_PRODUCT_AZUREWAVE_RTL8192SU_1	0x3306	/* RTL8192SU */
#define	USB_PRODUCT_AZUREWAVE_RTL8192SU_2	0x3309	/* RTL8192SU */
#define	USB_PRODUCT_AZUREWAVE_RTL8192SU_3	0x3310	/* RTL8192SU */
#define	USB_PRODUCT_AZUREWAVE_RTL8192SU_4	0x3311	/* RTL8192SU */
#define	USB_PRODUCT_AZUREWAVE_RTL8192SU_5	0x3325	/* RTL8192SU */

/* Baltech products */
#define	USB_PRODUCT_BALTECH_CARDREADER		0x9999	/* Card reader */

/* Bayer products */
#define	USB_PRODUCT_BAYER_CONTOUR_CABLE		0x6001	/* FTDI compatible adapter */

/* B&B Electronics products */
#define	USB_PRODUCT_BBELECTRONICS_USOTL4		0xAC01	/* RS-422/485 */
#define	USB_PRODUCT_BBELECTRONICS_232USB9M		0xac27	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_485USB9F_2W	0xac25	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_485USB9F_4W	0xac26	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_485USBTB_2W	0xac33	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_485USBTB_4W	0xac34	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_TTL3USB9M		0xac50	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_TTL5USB9M		0xac49	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_USO9ML2		0xac03	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_USO9ML2DR		0xac17	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_USO9ML2DR_2	0xac16	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_USOPTL4		0xac11	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_USOPTL4DR		0xac19	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_USOPTL4DR2	0xac18	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_USPTL4		0xac12	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_USTL4			0xac02	/* FTDI compatible adapter */
#define	USB_PRODUCT_BBELECTRONICS_ZZ_PROG1_USB	0xba02	/* FTDI compatible adapter */

/* Belkin products */
/*#define	USB_PRODUCT_BELKIN_F5U111		0x????	F5U111 Ethernet*/
#define	USB_PRODUCT_BELKIN_F5D6050		0x0050	/* F5D6050 802.11b Wireless Adapter */
#define	USB_PRODUCT_BELKIN_FBT001V		0x0081	/* FBT001v2 Bluetooth */
#define	USB_PRODUCT_BELKIN_FBT003V		0x0084	/* FBT003v2 Bluetooth */
#define	USB_PRODUCT_BELKIN_F5U103		0x0103	/* F5U103 Serial */
#define	USB_PRODUCT_BELKIN_F5U109		0x0109	/* F5U109 Serial */
#define	USB_PRODUCT_BELKIN_USB2SCSI		0x0115	/* #define	USB_to SCSI */
#define	USB_PRODUCT_BELKIN_F8T012		0x0121	/* F8T012xx1 Bluetooth #define	USB_Adapter */
#define	USB_PRODUCT_BELKIN_USB2LAN		0x0121	/* #define	USB_to LAN */
#define	USB_PRODUCT_BELKIN_F5U208		0x0208	/* F5U208 VideoBus II */
#define	USB_PRODUCT_BELKIN_F5U237		0x0237	/* F5U237 #define	USB_2.0 7-Port Hub */
#define	USB_PRODUCT_BELKIN_F5U257		0x0257	/* F5U257 Serial */
#define	USB_PRODUCT_BELKIN_F5U409		0x0409	/* F5U409 Serial */
#define	USB_PRODUCT_BELKIN_F6C550AVR	0x0551	/* F6C550-AVR UPS */
#define	USB_PRODUCT_BELKIN_F5U120		0x1203	/* F5U120-PC Hub */
#define	USB_PRODUCT_BELKIN_RTL8188CU	0x1102	/* RTL8188CU Wireless Adapter */
#define	USB_PRODUCT_BELKIN_F9L1103		0x1103	/* F9L1103 Wireless Adapter */
#define	USB_PRODUCT_BELKIN_RTL8192CU	0x2102	/* RTL8192CU Wireless Adapter */
#define	USB_PRODUCT_BELKIN_F7D2102		0x2103	/* F7D2102 Wireless Adapter */
#define	USB_PRODUCT_BELKIN_ZD1211B		0x4050	/* ZD1211B */
#define	USB_PRODUCT_BELKIN_F5D5055		0x5055	/* F5D5055 */
#define	USB_PRODUCT_BELKIN_F5D7050		0x7050	/* F5D7050 Wireless Adapter */
#define	USB_PRODUCT_BELKIN_F5D7051		0x7051	/* F5D7051 54g #define	USB_Network Adapter */
#define	USB_PRODUCT_BELKIN_F5D7050A		0x705a	/* F5D7050A Wireless Adapter */
/* Also sold as 'Ativa 802.11g wireless card' */
#define	USB_PRODUCT_BELKIN_F5D7050_V4000	0x705c	/* F5D7050 v4000 Wireless Adapter */
#define	USB_PRODUCT_BELKIN_F5D7050E		0x705e	/* F5D7050E Wireless Adapter */
#define	USB_PRODUCT_BELKIN_RT2870_1		0x8053	/* RT2870 */
#define	USB_PRODUCT_BELKIN_RT2870_2		0x805c	/* RT2870 */
#define	USB_PRODUCT_BELKIN_F5D8053V3	0x815c	/* F5D8053 v3 */
#define	USB_PRODUCT_BELKIN_RTL8192SU_1	0x815f	/* RTL8192SU */
#define	USB_PRODUCT_BELKIN_RTL8192SU_2	0x845a	/* RTL8192SU */
#define	USB_PRODUCT_BELKIN_RTL8192SU_3	0x945a	/* RTL8192SU */
#define	USB_PRODUCT_BELKIN_F5D8055		0x825a	/* F5D8055 */
#define	USB_PRODUCT_BELKIN_F5D8055V2	0x825b	/* F5D8055 v2 */
#define	USB_PRODUCT_BELKIN_F5D9050V3	0x905b	/* F5D9050 ver 3 Wireless Adapter */
#define	USB_PRODUCT_BELKIN2_F5U002		0x0002	/* F5U002 Parallel printer */
#define	USB_PRODUCT_BELKIN_F6D4050V1	0x935a	/* F6D4050 v1 */
#define	USB_PRODUCT_BELKIN_F6D4050V2	0x935b	/* F6D4050 v2 */

/* Billionton products */
#define	USB_PRODUCT_BILLIONTON_USB100	0x0986	/* USB100N 10/100 FastEthernet */
#define	USB_PRODUCT_BILLIONTON_USBLP100	0x0987	/* USB100LP */
#define	USB_PRODUCT_BILLIONTON_USBEL100	0x0988	/* USB100EL */
#define	USB_PRODUCT_BILLIONTON_USBE100	0x8511	/* USBE100 */
#define	USB_PRODUCT_BILLIONTON_USB2AR	0x90ff	/* USB2AR Ethernet */

/* Broadcom products */
#define	USB_PRODUCT_BROADCOM_BCM2033		0x2033	/* BCM2033 Bluetooth #define	USB_dongle */

/* Brother Industries products */
#define	USB_PRODUCT_BROTHER_HL1050			0x0002	/* HL-1050 laser printer */
#define	USB_PRODUCT_BROTHER_MFC8600 9650	0x0100	/* MFC8600/9650 multifunction device */

/* Behavior Technology Computer products */
#define	USB_PRODUCT_BTC_BTC6100				0x5550	/* 6100C Keyboard */
#define	USB_PRODUCT_BTC_BTC7932				0x6782	/* Keyboard with mouse port */

/* CACE Technologies products */
#define	USB_PRODUCT_CACE_AIRPCAPNX			0x0300	/* AirPcap NX */

/* Canon, Inc. products */
#define	USB_PRODUCT_CANON_N656U		0x2206	/* CanoScan N656U */
#define	USB_PRODUCT_CANON_N1220U	0x2207	/* CanoScan N1220U */
#define	USB_PRODUCT_CANON_D660U		0x2208	/* CanoScan D660U */
#define	USB_PRODUCT_CANON_N676U		0x220d	/* CanoScan N676U */
#define	USB_PRODUCT_CANON_N1240U	0x220e	/* CanoScan N1240U */
#define	USB_PRODUCT_CANON_LIDE25	0x2220	/* CanoScan LIDE 25 */
#define	USB_PRODUCT_CANON_S10		0x3041	/* PowerShot S10 */
#define	USB_PRODUCT_CANON_S100		0x3045	/* PowerShot S100 */
#define	USB_PRODUCT_CANON_S200		0x3065	/* PowerShot S200 */
#define	USB_PRODUCT_CANON_REBELXT	0x30ef	/* Digital Rebel XT */

/* CATC products */
#define	USB_PRODUCT_CATC_NETMATE		0x000a	/* Netmate Ethernet */
#define	USB_PRODUCT_CATC_NETMATE2		0x000c	/* Netmate2 Ethernet */
#define	USB_PRODUCT_CATC_CHIEF			0x000d	/* USB Chief Bus & Protocol Analyzer */
#define	USB_PRODUCT_CATC_ANDROMEDA		0x1237	/* Andromeda hub */

/* CASIO products */
#define	USB_PRODUCT_CASIO_QV_DIGICAM	0x1001	/* QV DigiCam */
#define	USB_PRODUCT_CASIO_EXS880		0x1105	/* Exilim EX-S880 */
#define	USB_PRODUCT_CASIO_BE300			0x2002	/* BE-300 PDA */
#define	USB_PRODUCT_CASIO_NAMELAND		0x4001	/* CASIO Nameland EZ-USB */

/* CCYU products */
#define	USB_PRODUCT_CCYU_ED1064			0x2136	/* EasyDisk ED1064 */

/* Century products */
#define	USB_PRODUCT_CENTURY_EX35QUAT	0x011e	/* Century USB Disk Enclosure */
#define	USB_PRODUCT_CENTURY_EX35SW4_SB4	0x011f	/* Century USB Disk Enclosure */

/* Cherry products */
#define	USB_PRODUCT_CHERRY_MY3000KBD	0x0001	/* My3000 keyboard */
#define	USB_PRODUCT_CHERRY_MY3000HUB	0x0003	/* My3000 hub */
#define	USB_PRODUCT_CHERRY_CYBOARD		0x0004	/* CyBoard Keyboard */

/* Chic Technology products */
#define	USB_PRODUCT_CHIC_MOUSE1			0x0001	/* mouse */
#define	USB_PRODUCT_CHIC_CYPRESS_		0x0003	/* Cypress USB Mouse */

/* Chicony products */
#define	USB_PRODUCT_CHICONY_KB8933			0x0001	/* KB-8933 keyboard */
#define	USB_PRODUCT_CHICONY_KU0325			0x0116	/* KU-0325 keyboard */
#define	USB_PRODUCT_CHICONY_CNF7129			0xb071	/* Notebook Web Camera */
#define	USB_PRODUCT_CHICONY_HDUVCCAM		0xb40a	/* HD UVC WebCam */
#define	USB_PRODUCT_CHICONY_RTL8188CUS_1	0xaff7	/* RTL8188CUS */
#define	USB_PRODUCT_CHICONY_RTL8188CUS_2	0xaff8	/* RTL8188CUS */
#define	USB_PRODUCT_CHICONY_RTL8188CUS_3	0xaff9	/* RTL8188CUS */
#define	USB_PRODUCT_CHICONY_RTL8188CUS_4	0xaffa	/* RTL8188CUS */
#define	USB_PRODUCT_CHICONY_RTL8188CUS_5	0xaffa	/* RTL8188CUS */
#define	USB_PRODUCT_CHICONY2_TWINKLECAM		0x600d	/* TwinkleCam USB camera */

/* CH Products */
#define	USB_PRODUCT_CHPRODUCTS_PROTHROTTLE	0x00f1	/* Pro Throttle */
#define	USB_PRODUCT_CHPRODUCTS_PROPEDALS	0x00f2	/* Pro Pedals */
#define	USB_PRODUCT_CHPRODUCTS_FIGHTERSTICK 0x00f3	/* Fighterstick */
#define	USB_PRODUCT_CHPRODUCTS_FLIGHTYOKE	0x00ff	/* Flight Sim Yoke */

/* Cisco-Linksys products */
#define	USB_PRODUCT_CISCOLINKSYS_WUSB54AG	0x000c	/* WUSB54AG Wireless Adapter */
#define	USB_PRODUCT_CISCOLINKSYS_WUSB54G	0x000d	/* WUSB54G Wireless Adapter */
#define	USB_PRODUCT_CISCOLINKSYS_WUSB54GP	0x0011	/* WUSB54GP Wireless Adapter */
#define	USB_PRODUCT_CISCOLINKSYS_USB200MV2	0x0018	/* USB200M v2 */
#define	USB_PRODUCT_CISCOLINKSYS_HU200TS	0x001a	/* HU200TS Wireless Adapter */
#define	USB_PRODUCT_CISCOLINKSYS_WUSB54GC	0x0020	/* WUSB54GC */
#define	USB_PRODUCT_CISCOLINKSYS_WUSB54GR	0x0023	/* WUSB54GR */
#define	USB_PRODUCT_CISCOLINKSYS_WUSBF54G	0x0024	/* WUSBF54G */
#define	USB_PRODUCT_CISCOLINKSYS_AE1000		0x002f	/* AE1000 */
#define	USB_PRODUCT_CISCOLINKSYS_USB3GIGV1	0x0041	/* USB3GIGV1 USB Ethernet Adapter */
#define	USB_PRODUCT_CISCOLINKSYS2_RT3070_	0x4001	/* RT3070 */
#define	USB_PRODUCT_CISCOLINKSYS3_RT3070_	0x0101	/* RT3070 */

/* Clipsal products */
#define	USB_PRODUCT_CLIPSAL_560884		0x0101	/* 560884 C-Bus Audio Matrix Switch */
#define	USB_PRODUCT_CLIPSAL_5500PACA	0x0201	/* 5500PACA C-Bus Pascal Automation Controller */
#define	USB_PRODUCT_CLIPSAL_5800PC		0x0301	/* 5800PC C-Bus Wireless Interface */
#define	USB_PRODUCT_CLIPSAL_5500PCU		0x0303	/* 5500PCU C-Bus Interface */
#define	USB_PRODUCT_CLIPSAL_5000CT2		0x0304	/* 5000CT2 C-Bus Touch Screen */
#define	USB_PRODUCT_CLIPSAL_C5000CT2	0x0305	/* C5000CT2 C-Bus Touch Screen */
#define	USB_PRODUCT_CLIPSAL_L51xx		0x0401	/* L51xx C-Bus Dimmer */

/* C-Media products */
#define	USB_PRODUCT_CMEDIA_CM6206		0x0102	/* CM106 compatible sound device */

/* CMOTECH products */
#define	USB_PRODUCT_CMOTECH_CNU510		0x5141	/* CDMA Technologies USB modem */
#define	USB_PRODUCT_CMOTECH_CNU550		0x5543	/* CDMA 2000 1xRTT/1xEVDO USB modem */
#define	USB_PRODUCT_CMOTECH_CGU628		0x6006	/* CGU-628 */
#define	USB_PRODUCT_CMOTECH_CDMA_MODEM1	0x6280	/* CDMA Technologies USB modem */
#define	USB_PRODUCT_CMOTECH_DISK		0xf000	/* disk mode */

/* Compaq products */
#define	USB_PRODUCT_COMPAQ_IPAQPOCKETPC	0x0003	/* iPAQ PocketPC */
#define	USB_PRODUCT_COMPAQ_PJB100		0x504a	/* Personal Jukebox PJB100 */
#define	USB_PRODUCT_COMPAQ_IPAQLINUX	0x505a	/* iPAQ Linux */

/* Composite Corp products looks the same as "TANGTOP" */
#define	USB_PRODUCT_COMPOSITE_USBPS2	0x0001	/* #define	USB_to PS2 Adaptor */

/* Conceptronic products */
#define	USB_PRODUCT_CONCEPTRONIC_PRISM_GT		0x3762	/* PrismGT USB 2.0 WLAN */
#define	USB_PRODUCT_CONCEPTRONIC_C11U			0x7100	/* C11U */
#define	USB_PRODUCT_CONCEPTRONIC_WL210			0x7110	/* WL-210 */
#define	USB_PRODUCT_CONCEPTRONIC_AR5523_1		0x7801	/* AR5523 */
#define	USB_PRODUCT_CONCEPTRONIC_AR5523_1_NF	0x7802	/* AR5523 (no firmware) */
#define	USB_PRODUCT_CONCEPTRONIC_AR5523_2		0x7811	/* AR5523 */
#define	USB_PRODUCT_CONCEPTRONIC_AR5523_2_NF	0x7812	/* AR5523 (no firmware) */
#define	USB_PRODUCT_CONCEPTRONIC2_RTL8192SU_1	0x3300	/* RTL8192SU */
#define	USB_PRODUCT_CONCEPTRONIC2_RTL8192SU_2	0x3301	/* RTL8192SU */
#define	USB_PRODUCT_CONCEPTRONIC2_RTL8192SU_3	0x3302	/* RTL8192SU */
#define	USB_PRODUCT_CONCEPTRONIC2_C54RU			0x3c02	/* C54RU WLAN */
#define	USB_PRODUCT_CONCEPTRONIC2_C54RU2		0x3c22	/* C54RU */
#define	USB_PRODUCT_CONCEPTRONIC2_RT3070_1		0x3c08	/* RT3070 */
#define	USB_PRODUCT_CONCEPTRONIC2_RT3070_2		0x3c11	/* RT3070 */
#define	USB_PRODUCT_CONCEPTRONIC2_VIGORN61		0x3c25	/* VIGORN61 */
#define	USB_PRODUCT_CONCEPTRONIC2_RT2870_1		0x3c06	/* RT2870 */
#define	USB_PRODUCT_CONCEPTRONIC2_RT2870_2		0x3c07	/* RT2870 */
#define	USB_PRODUCT_CONCEPTRONIC2_RT2870_7		0x3c09	/* RT2870 */
#define	USB_PRODUCT_CONCEPTRONIC2_RT2870_8		0x3c12	/* RT2870 */
#define	USB_PRODUCT_CONCEPTRONIC2_RT2870_3		0x3c23	/* RT2870 */
#define	USB_PRODUCT_CONCEPTRONIC2_RT2870_4		0x3c25	/* RT2870 */
#define	USB_PRODUCT_CONCEPTRONIC2_RT2870_5		0x3c27	/* RT2870 */
#define	USB_PRODUCT_CONCEPTRONIC2_RT2870_6		0x3c28	/* RT2870 */

/* Connectix products */
#define	USB_PRODUCT_CONNECTIX_QUICKCAM		0x0001	/* QuickCam */

/* Conect products */
#define	USB_PRODUCT_CONTEC_COM1USBH			0x8311	/* FTDI compatible adapter */

/* Corega products */
#define	USB_PRODUCT_COREGA_ETHER_USB_T		0x0001	/* Ether USB-T */
#define	USB_PRODUCT_COREGA_FETHER_USB_TX	0x0004	/* FEther USB-TX */
#define	USB_PRODUCT_COREGA_WLAN_USB_USB_11	0x000c	/* WirelessLAN USB-11 */
#define	USB_PRODUCT_COREGA_FETHER_USB_TXS	0x000d	/* FEther USB-TXS */
#define	USB_PRODUCT_COREGA_WLANUSB			0x0012	/* Wireless LAN Stick-11 */
#define	USB_PRODUCT_COREGA_FETHER_USB2_TX	0x0017	/* FEther USB2-TX */
#define	USB_PRODUCT_COREGA_WLUSB_11_KEY		0x001a	/* ULUSB-11 Key */
#define	USB_PRODUCT_COREGA_CGUSBRS232R		0x002a	/* CG-USBRS232R */
#define	USB_PRODUCT_COREGA_CGWLUSB2GL		0x002d	/* CG-WLUSB2GL */
#define	USB_PRODUCT_COREGA_CGWLUSB2GPX		0x002e	/* CG-WLUSB2GPX */
#define	USB_PRODUCT_COREGA_RT2870_1			0x002f	/* RT2870 */
#define	USB_PRODUCT_COREGA_RT2870_2			0x003c	/* RT2870 */
#define	USB_PRODUCT_COREGA_RT2870_3			0x003f	/* RT2870 */
#define	USB_PRODUCT_COREGA_RT3070			0x0041	/* RT3070 */
#define	USB_PRODUCT_COREGA_CGWLUSB300GNM	0x0042	/* CG-WLUSB300GNM */
#define	USB_PRODUCT_COREGA_RTL8192SU		0x0047	/* RTL8192SU */
#define	USB_PRODUCT_COREGA_RTL8192CU		0x0056	/* RTL8192CU */

#define	USB_PRODUCT_COREGA_WLUSB_11_STICK	0x7613	/* WLAN USB Stick 11 */
#define	USB_PRODUCT_COREGA_FETHER_USB_TXC	0x9601	/* FEther USB-TXC */

/* Corsair products */
#define	USB_PRODUCT_CORSAIR_K60				0x0a60	/* Corsair Vengeance K60 keyboard */
#define	USB_PRODUCT_CORSAIR_K68				0x1b3f	/* Corsair Gaming K68 keyboard */
#define	USB_PRODUCT_CORSAIR_K70				0x1b09	/* Corsair Vengeance K70 keyboard */
#define	USB_PRODUCT_CORSAIR_K70_RGB			0x1b13	/* Corsair K70 RGB Keyboard */
#define	USB_PRODUCT_CORSAIR_STRAFE			0x1b15	/* Corsair STRAFE Gaming keyboard */
#define	USB_PRODUCT_CORSAIR_STRAFE2			0x1b44	/* Corsair STRAFE Gaming keyboard */

/* Creative products */
#define	USB_PRODUCT_CREATIVE_NOMAD_II		0x1002	/* Nomad II MP3 player */
#define	USB_PRODUCT_CREATIVE_NOMAD_IIMG		0x4004	/* Nomad II MG */
#define	USB_PRODUCT_CREATIVE_NOMAD			0x4106	/* Nomad */
#define	USB_PRODUCT_CREATIVE2_VOIP_BLASTER	0x0258	/* Voip Blaster */
#define	USB_PRODUCT_CREATIVE3_OPTICAL_MOUSE	0x0001	/* Notebook Optical Mouse */

/* Cambridge Silicon Radio Ltd. products */
#define	USB_PRODUCT_CSR_BT_DONGLE			0x0001	/* Bluetooth USB dongle */
#define	USB_PRODUCT_CSR_CSRDFU				0xffff	/* #define	USB_Bluetooth Device in DFU State */

/* Chipsbank Microelectronics Co., Ltd */
#define	USB_PRODUCT_CHIPSBANK_USBMEMSTICK	0x6025	/* CBM2080 Flash drive controller */
#define	USB_PRODUCT_CHIPSBANK_USBMEMSTICK1	0x6026	/* CBM1180 Flash drive controller */

/* CTX products */
#define	USB_PRODUCT_CTX_EX1300				0x9999	/* Ex1300 hub */

/* Curitel products */
#define	USB_PRODUCT_CURITEL_HX550C			0x1101	/* CDMA 2000 1xRTT USB modem (HX-550C) */
#define	USB_PRODUCT_CURITEL_HX57XB			0x2101	/* CDMA 2000 1xRTT USB modem (HX-570/575B/PR-600) */
#define	USB_PRODUCT_CURITEL_PC5740			0x3701	/* Broadband Wireless modem */
#define	USB_PRODUCT_CURITEL_UM150			0x3711	/* EVDO modem */
#define	USB_PRODUCT_CURITEL_UM175			0x3714	/* EVDO modem */

/* CyberPower products */
#define	USB_PRODUCT_CYBERPOWER_1500CAVRLCD	0x0501	/* 1500CAVRLCD */

/* CyberTAN Technology products */
#define	USB_PRODUCT_CYBERTAN_TG54USB_		0x1666	/* TG54USB */
#define	USB_PRODUCT_CYBERTAN_RT2870			0x1828	/* RT2870 */

/* Cypress Semiconductor products */
#define	USB_PRODUCT_CYPRESS_MOUSE			0x0001	/* mouse */
#define	USB_PRODUCT_CYPRESS_THERMO			0x0002	/* thermometer */
#define	USB_PRODUCT_CYPRESS_WISPY1A			0x0bad	/* MetaGeek Wi-Spy */
#define	USB_PRODUCT_CYPRESS_KBDHUB			0x0101	/* Keyboard/Hub */
#define	USB_PRODUCT_CYPRESS_FMRADIO			0x1002	/* FM Radio */
#define	USB_PRODUCT_CYPRESS_IKARILASER		0x121f	/* Ikari Laser SteelSeries ApS */

#define	USB_PRODUCT_CYPRESS_USBRS232		0x5500	/* USB-RS232 Interface */
#define	USB_PRODUCT_CYPRESS_SLIM_HUB		0x6560	/* Slim Hub */
#define	USB_PRODUCT_CYPRESS_XX6830XX		0x6830	/* PATA Storage Device */
#define	USB_PRODUCT_CYPRESS_SILVERSHIELD	0xfd13	/* Gembird Silver Shield PM */

/* Daisy Technology products */
#define	USB_PRODUCT_DAISY_DMC			0x6901	/* #define	USB_MultiMedia Reader */

/* Dallas Semiconductor products */
#define	USB_PRODUCT_DALLAS_J6502		0x4201	/* J-6502 speakers */

/* DataApex products */
#define	USB_PRODUCT_DATAAPEX_MULTICOM	0xead6	/* MultiCom */

/* Dell products */
#define	USB_PRODUCT_DELL_PORT			0x0058	/* Port Replicator */
#define	USB_PRODUCT_DELL_AIO926			0x5115	/* Photo AIO Printer 926 */
#define	USB_PRODUCT_DELL_BC02			0x8000	/* BC02 Bluetooth #define	USB_Adapter */
#define	USB_PRODUCT_DELL_PRISM_GT_1		0x8102	/* PrismGT #define	USB_2.0 WLAN */
#define	USB_PRODUCT_DELL_TM350			0x8103	/* TrueMobile 350 Bluetooth #define	USB_Adapter */
#define	USB_PRODUCT_DELL_PRISM_GT_2		0x8104	/* PrismGT #define	USB_2.0 WLAN */
#define	USB_PRODUCT_DELL_U5700			0x8114	/* Dell 5700 3G */
#define	USB_PRODUCT_DELL_U5500			0x8115	/* Dell 5500 3G */
#define	USB_PRODUCT_DELL_U5505			0x8116	/* Dell 5505 3G */
#define	USB_PRODUCT_DELL_U5700_2		0x8117	/* Dell 5700 3G */
#define	USB_PRODUCT_DELL_U5510			0x8118	/* Dell 5510 3G */
#define	USB_PRODUCT_DELL_U5700_3		0x8128	/* Dell 5700 3G */
#define	USB_PRODUCT_DELL_U5700_4		0x8129	/* Dell 5700 3G */
#define	USB_PRODUCT_DELL_U5720			0x8133	/* Dell 5720 3G */
#define	USB_PRODUCT_DELL_U5720_2		0x8134	/* Dell 5720 3G */
#define	USB_PRODUCT_DELL_U740			0x8135	/* Dell U740 CDMA */
#define	USB_PRODUCT_DELL_U5520			0x8136	/* Dell 5520 3G */
#define	USB_PRODUCT_DELL_U5520_2		0x8137	/* Dell 5520 3G */
#define	USB_PRODUCT_DELL_U5520_3		0x8138	/* Dell 5520 3G */
#define	USB_PRODUCT_DELL_U5730			0x8180	/* Dell 5730 3G */
#define	USB_PRODUCT_DELL_U5730_2		0x8181	/* Dell 5730 3G */
#define	USB_PRODUCT_DELL_U5730_3		0x8182	/* Dell 5730 3G */
#define	USB_PRODUCT_DELL_DW700			0x9500	/* Dell DW700 GPS */

/* Delorme Paublishing products */
#define	USB_PRODUCT_DELORME_EARTHMATE	0x0100	/* Earthmate GPS */

/* Desknote products */
#define	USB_PRODUCT_DESKNOTE_UCR_61S2B	0x0c55	/* UCR-61S2B */

/* Diamond products */
#define	USB_PRODUCT_DIAMOND_RIO500USB	0x0001	/* Rio 500 USB */

/* Dick Smith Electronics (really C-Net) products */
#define	USB_PRODUCT_DICKSMITH_RT2573	0x9022	/* RT2573 */
#define	USB_PRODUCT_DICKSMITH_CWD854F	0x9032	/* C-Net CWD-854 rev F */

/* Digi International products */
#define	USB_PRODUCT_DIGI_ACCELEPORT2	0x0002	/* AccelePort #define	USB_2 */
#define	USB_PRODUCT_DIGI_ACCELEPORT4	0x0004	/* AccelePort #define	USB_4 */
#define	USB_PRODUCT_DIGI_ACCELEPORT8	0x0008	/* AccelePort #define	USB_8 */

/* Digianswer A/S products */
#define	USB_PRODUCT_DIGIANSWER_ZIGBEE802154	0x000a	/* ZigBee/802.15.4 MAC */

/* D-Link products */
#define	USB_PRODUCT_DLINK_DUBE100		0x1a00	/* 10/100 Ethernet */
#define	USB_PRODUCT_DLINK_DUBE100C1		0x1a02	/* DUB-E100 rev C1 */
#define	USB_PRODUCT_DLINK_DSB650TX4		0x200c	/* 10/100 Ethernet */
#define	USB_PRODUCT_DLINK_DWL120E		0x3200	/* DWL-120 rev E */
#define	USB_PRODUCT_DLINK_DWA125D1		0x330f	/* DWA-125 rev D1 */
#define	USB_PRODUCT_DLINK_DWA123D1		0x3310	/* DWA-123 rev D1 */
#define	USB_PRODUCT_DLINK_DWL122		0x3700	/* DWL-122 */
#define	USB_PRODUCT_DLINK_DWLG120		0x3701	/* DWL-G120 */
#define	USB_PRODUCT_DLINK_DWL120F		0x3702	/* DWL-120 rev F */
#define	USB_PRODUCT_DLINK_DWLAG132		0x3a00	/* DWL-AG132 */
#define	USB_PRODUCT_DLINK_DWLAG132_NF	0x3a01	/* DWL-AG132 (no firmware) */
#define	USB_PRODUCT_DLINK_DWLG132		0x3a02	/* DWL-G132 */
#define	USB_PRODUCT_DLINK_DWLG132_NF	0x3a03	/* DWL-G132 (no firmware) */
#define	USB_PRODUCT_DLINK_DWLAG122		0x3a04	/* DWL-AG122 */
#define	USB_PRODUCT_DLINK_DWLAG122_NF	0x3a05	/* DWL-AG122 (no firmware) */
#define	USB_PRODUCT_DLINK_DWLG122		0x3c00	/* DWL-G122 b1 Wireless Adapter */
#define	USB_PRODUCT_DLINK_DUBE100B1		0x3c05	/* DUB-E100 rev B1 */
#define	USB_PRODUCT_DLINK_RT2870		0x3c09	/* RT2870 */
#define	USB_PRODUCT_DLINK_RT3072_		0x3c0a	/* RT3072 */
#define	USB_PRODUCT_DLINK_DWA140B3		0x3c15	/* DWA-140 rev B3 */
#define	USB_PRODUCT_DLINK_DWA160B2		0x3c1a	/* DWA-160 rev B2 */
#define	USB_PRODUCT_DLINK_DWA127		0x3c1b	/* DWA-127 Wireless Adapter */
#define	USB_PRODUCT_DLINK_DWA162		0x3c1f	/* DWA-162 Wireless Adapter */
#define	USB_PRODUCT_DLINK_DWA140D1		0x3c20	/* DWA-140 rev D1 */
#define	USB_PRODUCT_DLINK_DSB650C		0x4000	/* 10Mbps Ethernet */
#define	USB_PRODUCT_DLINK_DSB650TX1		0x4001	/* 10/100 Ethernet */
#define	USB_PRODUCT_DLINK_DSB650TX		0x4002	/* 10/100 Ethernet */
#define	USB_PRODUCT_DLINK_DSB650TX_PNA	0x4003	/* 1/10/100 Ethernet */
#define	USB_PRODUCT_DLINK_DSB650TX3		0x400b	/* 10/100 Ethernet */
#define	USB_PRODUCT_DLINK_DSB650TX2		0x4102	/* 10/100 Ethernet */
#define	USB_PRODUCT_DLINK_DUB1312		0x4a00	/* 10/100/1000 Ethernet */
#define	USB_PRODUCT_DLINK_DSB650		0xabc1	/* 10/100 Ethernet */
#define	USB_PRODUCT_DLINK_DUBH7			0xf103	/* DUB-H7 USB 2.0 7-Port Hub */
#define	USB_PRODUCT_DLINK_DWR510_CD		0xa805	/* DWR-510 CD-ROM Mode */
#define	USB_PRODUCT_DLINK_DWR510		0x7e12	/* DWR-510 */
#define	USB_PRODUCT_DLINK_DWM157		0x7d02	/* DWM-157 */
#define	USB_PRODUCT_DLINK_DWM157_CD		0xa707	/* DWM-157 CD-ROM Mode */
#define	USB_PRODUCT_DLINK_RTL8188CU		0x3308	/* RTL8188CU */
#define	USB_PRODUCT_DLINK_RTL8192CU_1	0x3307	/* RTL8192CU */
#define	USB_PRODUCT_DLINK_RTL8192CU_2	0x3309	/* RTL8192CU */
#define	USB_PRODUCT_DLINK_RTL8192CU_3	0x330a	/* RTL8192CU */
#define	USB_PRODUCT_DLINK_DWA131B		0x330d	/* DWA-131 rev B */
#define	USB_PRODUCT_DLINK2_RTL8192SU_1	0x3300	/* RTL8192SU */
#define	USB_PRODUCT_DLINK2_RTL8192SU_2	0x3302	/* RTL8192SU */
#define	USB_PRODUCT_DLINK2_DWA131A1		0x3303	/* DWA-131 A1 */
#define	USB_PRODUCT_DLINK2_DWA160A2		0x3a09	/* DWA-160 A2 */
#define	USB_PRODUCT_DLINK2_DWA120		0x3a0c	/* DWA-120 */
#define	USB_PRODUCT_DLINK2_DWA120_NF	0x3a0d	/* DWA-120 (no firmware) */
#define	USB_PRODUCT_DLINK2_DWA130D1		0x3a0f	/* DWA-130 D1 */
#define	USB_PRODUCT_DLINK2_DWLG122C1	0x3c03	/* DWL-G122 c1 */
#define	USB_PRODUCT_DLINK2_WUA1340 		0x3c04	/* WUA-1340 */
#define	USB_PRODUCT_DLINK2_DWA111		0x3c06	/* DWA-111 */
#define	USB_PRODUCT_DLINK2_RT2870_1		0x3c09	/* RT2870 */
#define	USB_PRODUCT_DLINK2_DWA110		0x3c07	/* DWA-110 */
#define	USB_PRODUCT_DLINK2_RT3072_		0x3c0a	/* RT3072 */
#define	USB_PRODUCT_DLINK2_RT3072_1		0x3c0b	/* RT3072 */
#define	USB_PRODUCT_DLINK2_RT3070_1		0x3c0d	/* RT3070 */
#define	USB_PRODUCT_DLINK2_RT3070_2		0x3c0e	/* RT3070 */
#define	USB_PRODUCT_DLINK2_RT3070_3		0x3c0f	/* RT3070 */
#define	USB_PRODUCT_DLINK2_DWA160A1		0x3c10	/* DWA-160 A1 */
#define	USB_PRODUCT_DLINK2_RT2870_2		0x3c11	/* RT2870 */
#define	USB_PRODUCT_DLINK2_DWA130		0x3c13	/* DWA-130 */
#define	USB_PRODUCT_DLINK2_RT3070_4		0x3c15	/* RT3070 */
#define	USB_PRODUCT_DLINK2_RT3070_5		0x3c16	/* RT3070 */
#define	USB_PRODUCT_DLINK3_DWM652		0x3e04	/* DWM-652 */

/* DisplayLink products */
#define	USB_PRODUCT_DISPLAYLINK_LCD4300U	0x01ba	/* LCD-4300U */
#define	USB_PRODUCT_DISPLAYLINK_LCD8000U	0x01bb	/* LCD-8000U */
#define	USB_PRODUCT_DISPLAYLINK_LD220		0x0100	/* Samsung LD220 */
#define	USB_PRODUCT_DISPLAYLINK_GUC2020		0x0059	/* IOGEAR DVI GUC2020 */
#define	USB_PRODUCT_DISPLAYLINK_VCUD60		0x0136	/* Rextron DVI */
#define	USB_PRODUCT_DISPLAYLINK_CONV		0x0138	/* StarTech CONV-USB2DVI */
#define	USB_PRODUCT_DISPLAYLINK_DLDVI		0x0141	/* DisplayLink DVI */
#define	USB_PRODUCT_DISPLAYLINK_VGA10		0x015a	/* CMP-USBVGA10 */
#define	USB_PRODUCT_DISPLAYLINK_WSDVI		0x0198	/* WS Tech DVI */
#define	USB_PRODUCT_DISPLAYLINK_EC008		0x019b	/* EasyCAP008 DVI */
#define	USB_PRODUCT_DISPLAYLINK_HPDOCK		0x01d4	/* HP USB Docking */
#define	USB_PRODUCT_DISPLAYLINK_NL571		0x01d7	/* HP USB DVI */
#define	USB_PRODUCT_DISPLAYLINK_M01061		0x01e2	/* Lenovo DVI */
#define	USB_PRODUCT_DISPLAYLINK_SWDVI		0x024c	/* SUNWEIT DVI */
#define	USB_PRODUCT_DISPLAYLINK_NBDOCK		0x0215	/* VideoHome NBdock1920 */
#define	USB_PRODUCT_DISPLAYLINK_LUM70		0x02a9	/* Lilliput UM-70 */
#define	USB_PRODUCT_DISPLAYLINK_UM7X0		0x401a	/* nanovision MiMo */
#define	USB_PRODUCT_DISPLAYLINK_LT1421		0x03e0	/* Lenovo ThinkVision LT1421 */
#define	USB_PRODUCT_DISPLAYLINK_POLARIS2	0x0117	/* Polaris2 #define	USB_dock */
#define	USB_PRODUCT_DISPLAYLINK_PLUGABLE	0x0377	/* Plugable docking station */
#define	USB_PRODUCT_DISPLAYLINK_ITEC		0x02e9	/* i-tec USB 2.0 Docking Station */

/* DMI products */
#define	USB_PRODUCT_DMI_CFSM_RW			0xa109	/* CF/SM Reader/Writer */
#define	USB_PRODUCT_DMI_DISK			0x2bcf	/* Generic Disk */

/* DrayTek products */
#define	USB_PRODUCT_DRAYTEK_VIGOR550	0x0550	/* Vigor550 */

/* Dream Link products */
#define	USB_PRODUCT_DREAMLINK_DL100B	0x0004	/* USB Webmail Notifier */

/* dresden elektronik products */
#define	USB_PRODUCT_DRESDENELEKTRONIK_SENSORTERMINALBOARD		0x0001 /* SensorTerminalBoard */
#define	USB_PRODUCT_DRESDENELEKTRONIK_WIRELESSHANDHELDTERMINAL	0x0004 /* Wireless Handheld Terminal */
#define	USB_PRODUCT_DRESDENELEKTRONIK_DE_RFNODE					0x001c /* deRFnode */
#define	USB_PRODUCT_DRESDENELEKTRONIK_LEVELSHIFTERSTICKLOWCOST	0x0022 /* Levelshifter Stick Low Cost */

/* DYMO */
#define	USB_PRODUCT_DYMO_LABELMANAGERPNP	0x1001	/* DYMO LabelManager PnP */

/* Dynastream Innovations */
#define	USB_PRODUCT_DYNASTREAM_ANTDEVBOARD	0x1003	/* ANT dev board */
#define	USB_PRODUCT_DYNASTREAM_ANT2USB		0x1004	/* ANT2USB */
#define	USB_PRODUCT_DYNASTREAM_ANTDEVBOARD2	0x1006	/* ANT dev board */

/* Edimax products */
#define	USB_PRODUCT_EDIMAX_EW7318USG	0x7318	/* USB Wireless dongle */
#define	USB_PRODUCT_EDIMAX_RTL8192SU_1	0x7611	/* RTL8192SU */
#define	USB_PRODUCT_EDIMAX_RTL8192SU_2	0x7612	/* RTL8192SU */
#define	USB_PRODUCT_EDIMAX_EW7622UMN	0x7622	/* EW-7622UMn */
#define	USB_PRODUCT_EDIMAX_RT2870_1		0x7711	/* RT2870 */
#define	USB_PRODUCT_EDIMAX_EW7717		0x7717	/* EW-7717 */
#define	USB_PRODUCT_EDIMAX_EW7718		0x7718	/* EW-7718 */
#define	USB_PRODUCT_EDIMAX_EW7733UND	0x7733	/* EW-7733UnD */
#define	USB_PRODUCT_EDIMAX_EW7811UN		0x7811	/* EW-7811Un */
#define	USB_PRODUCT_EDIMAX_RTL8192CU	0x7822	/* RTL8192CU */

/* eGalax Products */
#define	USB_PRODUCT_EGALAX_TPANEL		0x0001	/* Touch Panel */
#define	USB_PRODUCT_EGALAX_TPANEL2		0x0002	/* Touch Panel */
#define	USB_PRODUCT_EGALAX2_TPANEL		0x0001	/* Touch Panel */

/* EGO Products */
#define	USB_PRODUCT_EGO_DUMMY			0x0000	/* Dummy Product */
#define	USB_PRODUCT_EGO_M4U				0x1020	/* ESI M4U */

/* Eicon Networks */
#define	USB_PRODUCT_EICON_DIVA852		0x4905	/* Diva 852 ISDN TA */

/* EIZO products */
#define	USB_PRODUCT_EIZO_HUB			0x0000	/* hub */
#define	USB_PRODUCT_EIZO_MONITOR		0x0001	/* monitor */

/* ELCON Systemtechnik products */
#define	USB_PRODUCT_ELCON_PLAN			0x0002	/* Goldpfeil P-LAN */

/* Elecom products */
#define	USB_PRODUCT_ELECOM_MOUSE29UO	0x0002	/* mouse 29UO */
#define	USB_PRODUCT_ELECOM_LDUSBTX0		0x200c	/* LD-USB/TX */
#define	USB_PRODUCT_ELECOM_LDUSBTX1		0x4002	/* LD-USB/TX */
#define	USB_PRODUCT_ELECOM_LDUSBLTX		0x4005	/* LD-USBL/TX */
#define	USB_PRODUCT_ELECOM_WDC150SU2M	0x4008	/* WDC-150SU2M */
#define	USB_PRODUCT_ELECOM_LDUSBTX2		0x400b	/* LD-USB/TX */
#define	USB_PRODUCT_ELECOM_LDUSB20		0x4010	/* LD-USB20 */
#define	USB_PRODUCT_ELECOM_UCSGT		0x5003	/* UC-SGT */
#define	USB_PRODUCT_ELECOM_UCSGT0		0x5004	/* UC-SGT */
#define	USB_PRODUCT_ELECOM_LDUSBTX3		0xabc1	/* LD-USB/TX */

/* Elektor products */
#define	USB_PRODUCT_ELEKTOR_FT323R		0x0005	/* FTDI compatible adapter */

/* Elsa products */
#define	USB_PRODUCT_ELSA_MODEM1			0x2265	/* ELSA Modem Board */
#define	USB_PRODUCT_ELSA_USB2ETHERNET	0x3000	/* Microlink USB2Ethernet */

/* ELV products */
#define	USB_PRODUCT_ELV_USBI2C			0xe00f	/* USB-I2C interface */

/* EMS products */
#define	USB_PRODUCT_EMS_DUAL_SHOOTER	0x0003	/* PSX gun controller converter */

/* Emtec products */
#define	USB_PRODUCT_EMTEC_RUF2PS		0x2240	/* Flash Drive */

/* Encore products */
#define	USB_PRODUCT_ENCORE_RT3070_1		0x1480	/* RT3070 */
#define	USB_PRODUCT_ENCORE_RT3070_2		0x14a1	/* RT3070 */
#define	USB_PRODUCT_ENCORE_RT3070_3		0x14a9	/* RT3070 */

/* Entrega products */
#define	USB_PRODUCT_ENTREGA_1S			0x0001	/* 1S serial */
#define	USB_PRODUCT_ENTREGA_2S			0x0002	/* 2S serial */
#define	USB_PRODUCT_ENTREGA_1S25		0x0003	/* 1S25 serial */
#define	USB_PRODUCT_ENTREGA_4S			0x0004	/* 4S serial */
#define	USB_PRODUCT_ENTREGA_E45			0x0005	/* E45 Ethernet */
#define	USB_PRODUCT_ENTREGA_CENTRONICS	0x0006	/* Parallel Port */
#define	USB_PRODUCT_ENTREGA_XX1			0x0008	/* Ethernet */
#define	USB_PRODUCT_ENTREGA_1S9			0x0093	/* 1S9 serial */
#define	USB_PRODUCT_ENTREGA_EZUSB		0x8000	/* EZ-USB */
#define	USB_PRODUCT_ENTREGA_2U4S		0x8004	/* 2U4S serial/usb hub */
#define	USB_PRODUCT_ENTREGA_XX2			0x8005	/* Ethernet */

/* Epson products */
#define	USB_PRODUCT_EPSON_PRINTER1		0x0001	/* #define	USB_Printer */
#define	USB_PRODUCT_EPSON_PRINTER2		0x0002	/* ISD #define	USB_Smart Cable for Mac */
#define	USB_PRODUCT_EPSON_PRINTER3		0x0003	/* ISD #define	USB_Smart Cable */
#define	USB_PRODUCT_EPSON_PRINTER5		0x0005	/* #define	USB_Printer */
#define	USB_PRODUCT_EPSON_636			0x0101	/* Perfection 636U / 636Photo scanner */
#define	USB_PRODUCT_EPSON_610			0x0103	/* Perfection 610 scanner */
#define	USB_PRODUCT_EPSON_1200			0x0104	/* Perfection 1200U / 1200Photo scanner */
#define	USB_PRODUCT_EPSON_1600			0x0107	/* Expression 1600 scanner */
#define	USB_PRODUCT_EPSON_1640			0x010a	/* Perfection 1640SU scanner */
#define	USB_PRODUCT_EPSON_1240			0x010b	/* Perfection 1240U / 1240Photo scanner */
#define	USB_PRODUCT_EPSON_640U			0x010c	/* Perfection 640U scanner */
#define	USB_PRODUCT_EPSON_1250			0x010f	/* Perfection 1250U / 1250Photo scanner */
#define	USB_PRODUCT_EPSON_1650			0x0110	/* Perfection 1650 scanner */
#define	USB_PRODUCT_EPSON_GT9700F		0x0112	/* GT-9700F scanner */
#define	USB_PRODUCT_EPSON_GT9300UF		0x011b	/* GT-9300UF scanner */
#define	USB_PRODUCT_EPSON_3200			0x011c	/* Perfection 3200 scanner */
#define	USB_PRODUCT_EPSON_1260			0x011d	/* Perfection 1260 scanner */
#define	USB_PRODUCT_EPSON_1660			0x011e	/* Perfection 1660 scanner */
#define	USB_PRODUCT_EPSON_1670			0x011f	/* Perfection 1670 scanner */
#define	USB_PRODUCT_EPSON_1270			0x0120	/* Perfection 1270 scanner */
#define	USB_PRODUCT_EPSON_2480			0x0121	/* Perfection 2480 scanner */
#define	USB_PRODUCT_EPSON_3590			0x0122	/* Perfection 3590 scanner */
#define	USB_PRODUCT_EPSON_4990			0x012a	/* Perfection 4990 Photo scanner */
#define	USB_PRODUCT_EPSON_CRESSI_EDY	0x0521	/* Cressi Edy diving computer */
#define	USB_PRODUCT_EPSON_N2ITION3		0x0522	/* Zeagle N2iTion3 diving computer */
#define	USB_PRODUCT_EPSON_STYLUS_875DC	0x0601	/* Stylus Photo 875DC Card Reader */
#define	USB_PRODUCT_EPSON_STYLUS_895	0x0602	/* Stylus Photo 895 Card Reader */
#define	USB_PRODUCT_EPSON_CX5400		0x0808	/* CX5400 scanner */
#define	USB_PRODUCT_EPSON_3500			0x080e	/* CX-3500/3600/3650 MFP */
#define	USB_PRODUCT_EPSON_RX425			0x080f	/* Stylus Photo RX425 scanner */
#define	USB_PRODUCT_EPSON_DX3800		0x0818	/* CX3700/CX3800/DX38x0 MFP scanner */
#define	USB_PRODUCT_EPSON_4800			0x0819	/* CX4700/CX4800/DX48x0 MFP scanner */
#define	USB_PRODUCT_EPSON_4200			0x0820	/* CX4100/CX4200/DX4200 MFP scanner */
#define	USB_PRODUCT_EPSON_5000			0x082b	/* CX4900/CX5000/DX50x0 MFP scanner */
#define	USB_PRODUCT_EPSON_6000			0x082e	/* CX5900/CX6000/DX60x0 MFP scanner */
#define	USB_PRODUCT_EPSON_DX4000		0x082f	/* DX4000 MFP scanner */
#define	USB_PRODUCT_EPSON_DX7400		0x0838	/* CX7300/CX7400/DX7400 MFP scanner */
#define	USB_PRODUCT_EPSON_DX8400		0x0839	/* CX8300/CX8400/DX8400 MFP scanner */
#define	USB_PRODUCT_EPSON_SX100			0x0841	/* SX100/NX100 MFP scanner */
#define	USB_PRODUCT_EPSON_NX300			0x0848	/* NX300 MFP scanner */
#define	USB_PRODUCT_EPSON_SX200			0x0849	/* SX200/SX205 MFP scanner */
#define	USB_PRODUCT_EPSON_SX400			0x084a	/* SX400/NX400/TX400 MFP scanner */

/* e-TEK Labs products */
#define	USB_PRODUCT_ETEK_1COM			0x8007	/* Serial */

/* Evolution products */
#define	USB_PRODUCT_EVOLUTION_ER1		0x0300	/* FTDI compatible adapter */
#define	USB_PRODUCT_EVOLUTION_HYBRID	0x0302	/* FTDI compatible adapter */
#define	USB_PRODUCT_EVOLUTION_RCM4		0x0303	/* FTDI compatible adapter */

/* Extended Systems products */
#define	USB_PRODUCT_EXTENDED_XTNDACCESS	0x0100	/* XTNDAccess IrDA */

/* Falcom products */
#define	USB_PRODUCT_FALCOM_TWIST		0x0001	/* USB GSM/GPRS Modem */
#define	USB_PRODUCT_FALCOM_SAMBA		0x0005	/* FTDI compatible adapter */

/* FEIYA products */
#define	USB_PRODUCT_FEIYA_DUMMY			0x0000	/* Dummy product */
#define	USB_PRODUCT_FEIYA_5IN1			0x1132	/* 5-in-1 Card Reader */
#define	USB_PRODUCT_FEIYA_ELANGO		0x6200	/* MicroSDHC Card Reader */
#define	USB_PRODUCT_FEIYA_AC110			0x6300	/* AC-110 Card Reader */

/* FeiXun Communication products */
#define	USB_PRODUCT_FEIXUN_RTL8188CU	0x0090	/* RTL8188CU */
#define	USB_PRODUCT_FEIXUN_RTL8192CU	0x0091	/* RTL8192CU */

/* Festo */
#define	USB_PRODUCT_FESTO_CPX_USB		0x0102	/* CPX-USB */
#define	USB_PRODUCT_FESTO_CMSP			0x0501	/* CMSP */

/* Fiberline */
#define	USB_PRODUCT_FIBERLINE_WL430U	0x6003	/* WL-430U */

/* FIC / OpenMoko */
#define	USB_PRODUCT_FIC_NEO1973_DEBUG	0x5118	/* FTDI compatible adapter */

/* Fossil, Inc products */
#define	USB_PRODUCT_FOSSIL_WRISTPDA		0x0002	/* Wrist PDA */

/* Foxconn products */
#define	USB_PRODUCT_FOXCONN_TCOM_TC_300		0xe000	/* T-Com TC 300 */
#define	USB_PRODUCT_FOXCONN_PIRELLI_DP_L10	0xe003	/* Pirelli DP-L10 */

/* Freecom products */
#define	USB_PRODUCT_FREECOM_DVD				0xfc01	/* DVD drive */
#define	USB_PRODUCT_FREECOM_HDD				0xfc05	/* Classic SL Hard Drive */

/* Fujitsu Siemens Computers products */
#define	USB_PRODUCT_FSC_E5400				0x1009	/* PrismGT USB 2.0 WLAN */

/* Future Technology Devices products */
#define	USB_PRODUCT_FTDI_SCX8_USB_PHOENIX	0x5259	SCx8 USB Phoenix interface
#define	USB_PRODUCT_FTDI_SERIAL_8U100AX		0x8372	/* 8U100AX Serial */
#define	USB_PRODUCT_FTDI_SERIAL_8U232AM		0x6001	/* 8U232AM Serial */
#define	USB_PRODUCT_FTDI_SERIAL_8U232AM4	0x6004	/* 8U232AM Serial */
#define	USB_PRODUCT_FTDI_SERIAL_232RL		0x6006	/* FT232RL Serial */
#define	USB_PRODUCT_FTDI_SERIAL_2232C		0x6010	/* FT2232C Dual port Serial */
#define	USB_PRODUCT_FTDI_232H				0x6014	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_232EX				0x6015	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SERIAL_2232D		0x9e90	/* FT2232D Dual port Serial */
#define	USB_PRODUCT_FTDI_SERIAL_4232H		0x6011	/* FT4232H Quad port Serial */
#define	USB_PRODUCT_FTDI_XDS100V2			0xa6d0	/* TI XDS100V1/V2 and early Beaglebones */
#define	USB_PRODUCT_FTDI_XDS100V3			0xa6d1	/* TI XDS100V3 */
#define	USB_PRODUCT_FTDI_KTLINK				0xbbe2	/* KT-LINK Embedded Hackers Multitool */
#define	USB_PRODUCT_FTDI_TURTELIZER2		0xbdc8	/* egnite Turtelizer 2 JTAG/RS232 Adapter */
/* Gude Analog- und Digitalsysteme products also uses FTDI's id: */
#define	USB_PRODUCT_FTDI_TACTRIX_OPENPORT_13M	0xcc48	/* OpenPort 1.3 Mitsubishi */
#define	USB_PRODUCT_FTDI_TACTRIX_OPENPORT_13S	0xcc49	/* OpenPort 1.3 Subaru */
#define	USB_PRODUCT_FTDI_TACTRIX_OPENPORT_13U	0xcc4a	/* OpenPort 1.3 Universal */
#define	USB_PRODUCT_FTDI_GAMMASCOUT				0xd678	/* Gamma-Scout */
#define	USB_PRODUCT_FTDI_KBS			0xe6c8	/* Pyramid KBS USB LCD */
#define	USB_PRODUCT_FTDI_EISCOU			0xe888	/* Expert ISDN Control USB */
#define	USB_PRODUCT_FTDI_UOPTBR			0xe889	/* USB-RS232 OptoBridge */
#define	USB_PRODUCT_FTDI_EMCU2D			0xe88a	/* Expert mouseCLOCK #define	USB_II */
#define	USB_PRODUCT_FTDI_PCMSFU			0xe88b	/* Precision Clock MSF USB */
#define	USB_PRODUCT_FTDI_EMCU2H			0xe88c	/* Expert mouseCLOCK #define	USB_II HBG */
#define	USB_PRODUCT_FTDI_MAXSTREAM		0xee18	/* Maxstream PKG-U */
#define	USB_PRODUCT_FTDI_USB_UIRT		0xf850	/* USB-UIRT */
#define	USB_PRODUCT_FTDI_USBSERIAL		0xfa00	/* Matrix Orbital #define	USB_Serial */
#define	USB_PRODUCT_FTDI_MX2_3			0xfa01	/* Matrix Orbital MX2 or MX3 */
#define	USB_PRODUCT_FTDI_MX4_5			0xfa02	/* Matrix Orbital MX4 or MX5 */
#define	USB_PRODUCT_FTDI_LK202			0xfa03	/* Matrix Orbital VK/LK202 Family */
#define	USB_PRODUCT_FTDI_LK204			0xfa04	/* Matrix Orbital VK/LK204 Family */
#define	USB_PRODUCT_FTDI_CFA_632		0xfc08	/* Crystalfontz CFA-632 #define	USB_LCD */
#define	USB_PRODUCT_FTDI_CFA_634		0xfc09	/* Crystalfontz CFA-634 #define	USB_LCD */
#define	USB_PRODUCT_FTDI_CFA_633		0xfc0b	/* Crystalfontz CFA-633 #define	USB_LCD */
#define	USB_PRODUCT_FTDI_CFA_631		0xfc0c	/* Crystalfontz CFA-631 #define	USB_LCD */
#define	USB_PRODUCT_FTDI_CFA_635		0xfc0d	/* Crystalfontz CFA-635 #define	USB_LCD */
#define	USB_PRODUCT_FTDI_SEMC_DSS20		0xfc82	/* SEMC DSS-20 SyncStation */
/* Commerzielle und Technische Informationssysteme GmbH products */
#define	USB_PRODUCT_FTDI_CTI_USB_NANO_485		0xf60b	/* CTI USB-Nano 485 */
#define	USB_PRODUCT_FTDI_CTI_USB_MINI_485		0xf608	/* CTI USB-Mini 485 */
/* Other products */
#define	USB_PRODUCT_FTDI_232RL			0xfbfa	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_4N_GALAXY_DE_1	0xf3c0	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_4N_GALAXY_DE_2	0xf3c1	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_4N_GALAXY_DE_3	0xf3c2	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_8U232AM_ALT	0x6006	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ACCESSO		0xfad0	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ACG_HFDUAL		0xdd20	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ACTIVE_ROBOTS	0xe548	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ACTZWAVE		0xf2d0	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_AMC232			0xff00	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ARTEMIS		0xdf28	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ASK_RDR400		0xc991	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ATIK_ATK16		0xdf30	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ATIK_ATK16C	0xdf32	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ATIK_ATK16HR	0xdf31	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ATIK_ATK16HRC	0xdf33	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ATIK_ATK16IC	0xdf35	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_BCS_SE923		0xfb99	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CANDAPTER		0x9f80	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CANUSB			0xffa8	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CCSICDU20_0	0xf9d0	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CCSICDU40_1	0xf9d1	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CCSICDU64_4	0xf9d4	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CCSLOAD_N_GO_3	0xf9d3	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CCSMACHX_2		0xf9d2	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CCSPRIME8_5	0xf9d5	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CHAMSYS_24_MASTER_WING	0xdaf8	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CHAMSYS_MAXI_WING		0xdafd	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CHAMSYS_MEDIA_WING		0xdafe	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CHAMSYS_MIDI_TIMECODE	0xdafb	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CHAMSYS_MINI_WING		0xdafc	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CHAMSYS_PC_WING		0xdaf9	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CHAMSYS_USB_DMX		0xdafa	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CHAMSYS_WING			0xdaff	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_COM4SM			0xd578	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CONVERTER_0	0xd388	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CONVERTER_1	0xd389	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CONVERTER_2	0xd38a	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CONVERTER_3	0xd38b	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CONVERTER_4	0xd38c	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CONVERTER_5	0xd38d	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CONVERTER_6	0xd38e	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_CONVERTER_7	0xd38f	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_DMX4ALL		0xc850	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_DOMINTELL_DGQG	0xef50	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_DOMINTELL_DUSB_	0xef51	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_DOTEC			0x9868	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ECLO_COM_1WIRE	0xea90	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ECO_PRO_CDS	0xe520	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELSTER_UNICOM	0xe700	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_ALC8500	0xf06e	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_CLI7000	0xfb59	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_CSI8		0xe0f0	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_EC3000		0xe006	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_EM1000DL	0xe0f1	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_EM1010PC	0xe0ef	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_FEM		0xe00a	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_FHZ1000PC	0xf06f	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_FHZ1300PC	0xe0e8	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_FM3RX		0xe0ed	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_FS20SIG	0xe0f4	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_HS485		0xe0ea	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_KL100		0xe002	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_MSM1		0xe001	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_PCD200		0xf06c	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_PCK100		0xe0f2	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_PPS7330	0xfb5c	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_RFP500		0xe0f3	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_T1100		0xf06b	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_TFD128		0xe0ec	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_TFM100		0xfb5d	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_TWS550		0xe009	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_UAD8		0xf068	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_UDA7		0xf069	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_UDF77		0xfb5e	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_UIO88		0xfb5f	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_ULA200		0xf06d	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_UM100		0xfb5a	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_UMS100		0xe0eb	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_UO100		0xfb5b	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_UR100		0xfb58	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_USI2		0xf06a	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_USR		0xe000	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_UTP8		0xe0f5	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_WS300PC	0xe0f6	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_WS444PC	0xe0f7	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_WS500		0xe0e9	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_WS550		0xe004	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_WS777		0xe0ee	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_ELV_WS888		0xe008	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_FUTURE_0		0xf44a	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_FUTURE_1		0xf44b	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_FUTURE_2		0xf44c	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_GENERIC		0x9378	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_GUDEADS_E808	0xe808	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_GUDEADS_E809	0xe809	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_GUDEADS_E80A	0xe80a	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_GUDEADS_E80B	0xe80b	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_GUDEADS_E80C	0xe80c	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_GUDEADS_E80D	0xe80d	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_GUDEADS_E80E	0xe80e	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_GUDEADS_E80F	0xe80f	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_GUDEADS_E88D	0xe88d	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_GUDEADS_E88E	0xe88e	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_GUDEADS_E88F	0xe88f	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_HD_RADIO		0x937c	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_HO720			0xed72	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_HO730			0xed73	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_HO820			0xed74	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_HO870			0xed71	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_IBS_APP70		0xff3d	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_IBS_PCMCIA		0xff3a	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_IBS_PEDO		0xff3e	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_IBS_PICPRO		0xff39	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_IBS_PK1		0xff3b	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_IBS_PROD		0xff3f	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_IBS_RS232MON	0xff3c	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_IBS_US485		0xff38	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_IPLUS			0xd070	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_IPLUS2			0xd071	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_IRTRANS		0xfc60	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_LENZ_LIUSB		0xd780	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_LM3S_DEVEL_BOARD	0xbcd8	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_LM3S_EVAL_BOARD	0xbcd9	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_LM3S_ICDI_B_BOARD	0xbcda	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_MASTERDEVEL2		0xf449	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_MHAM_DB9			0xeeed	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_MHAM_IC			0xeeec	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_MHAM_KW			0xeee8	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_MHAM_RS232			0xeeee	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_MHAM_Y6			0xeeea	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_MHAM_Y8			0xeeeb	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_MHAM_Y9			0xeeef	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_MHAM_YS			0xeee9	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_MICRO_CHAMELEON	0xcaa0	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_MTXORB_5			0xfa05	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_MTXORB_6			0xfa06	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_NXTCAM				0xabb8	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_OCEANIC			0xf460	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_OOCDLINK			0xbaf8	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_OPENDCC			0xbfd8	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_OPENDCC_GATEWAY	0xbfdb	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_OPENDCC_GBM		0xbfdc	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_OPENDCC_SNIFFER	0xbfd9	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_OPENDCC_THROTTLE	0xbfda	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_PCDJ_DAC2			0xfa88	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_PERLE_ULTRAPORT	0xf0c0	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_PHI_FISCO			0xe40b	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_PIEGROUP			0xf208	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_PROPOX_JTAGCABLEII	0xd738	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_R2000KU_TRUE_RNG	0xfb80	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_R2X0				0xfc71	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_RELAIS				0xfa10	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_REU_TINY			0xed22	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_RMP200				0xe729	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_RM_CANVIEW			0xfd60	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_RRCIRKITS_LOCOBUFFER		0xc7d0	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SCIENCESCOPE_HS_LOGBOOK	0xff1d	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SCIENCESCOPE_LOGBOOKML		0xff18	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SCIENCESCOPE_LS_LOGBOOK	0xff1c	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SCS_DEVICE_0		0xd010	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SCS_DEVICE_1		0xd011	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SCS_DEVICE_2		0xd012	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SCS_DEVICE_3		0xd013	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SCS_DEVICE_4		0xd014	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SCS_DEVICE_5		0xd015	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SCS_DEVICE_6		0xd016	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SCS_DEVICE_7		0xd017	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SDMUSBQSS			0xf448	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SIGNALYZER_SH2		0xbca2	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SIGNALYZER_SH4		0xbca4	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SIGNALYZER_SLITE	0xbca1	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SIGNALYZER_ST		0xbca0	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SPECIAL_1			0xfc70	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SPECIAL_3			0xfc72	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SPECIAL_4			0xfc73	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SPROG_II			0xf0c8	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SR_RADIO			0x9379	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_SUUNTO_SPORTS		0xf680	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_TAVIR_STK500		0xfa33	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_TERATRONIK_D2XX	0xec89	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_TERATRONIK_VCP		0xec88	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_THORLABS			0xfaf0	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_TIAO				0x8a98	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_TNC_X				0xebe0	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_TTUSB_				0xff20	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_USBX_707			0xf857	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_USINT_CAT			0xb810	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_USINT_RS232		0xb812	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_USINT_WKEY			0xb811	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_VARDAAN			0xf070	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_VNHCPCUSB_D		0xfe38	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_WESTREX_MODEL_777		0xdc00	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_WESTREX_MODEL_8900F	0xdc01	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_XF_547					0xfc0a	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_XF_640					0xfc0e	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_XF_642					0xfc0f	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_XM_RADIO				0x937a	/* FTDI compatible adapter */
#define	USB_PRODUCT_FTDI_YEI_SERVOCENTER31		0xe050	/* FTDI compatible adapter */

/* Fuji photo products */
#define	USB_PRODUCT_FUJIPHOTO_MASS0100		0x0100	/* Mass Storage */

/* Fujitsu protducts */
#define	USB_PRODUCT_FUJITSU_AH_F401U		0x105b	/* AH-F401U Air H device */

/* Fujitsu-Siemens protducts */
#define	USB_PRODUCT_FUJITSUSIEMENS_SCR		0x0009	/* Fujitsu-Siemens SCR #define	USB_Reader */

/* Garmin products */
#define	USB_PRODUCT_GARMIN_FORERUNNER230	0x086d	/* ForeRunner 230 */
#define	USB_PRODUCT_GARMIN_IQUE_3600		0x0004	/* iQue 3600 */

/* Gemalto products */
#define	USB_PRODUCT_GEMALTO_PROXPU			0x5501	/* Prox-PU/CU RFID Card Reader */

/* General Instruments (Motorola) products */
#define	USB_PRODUCT_GENERALINSTMNTS_SB5100	0x5100	/* SURFboard SB5100 Cable modem */

/* Genesys Logic products */
#define	USB_PRODUCT_GENESYS_GL620USB		0x0501	/* GL620 USB_Host-Host interface */
#define	USB_PRODUCT_GENESYS_GL650			0x0604	/* GL650 HUB */
#define	USB_PRODUCT_GENESYS_GL606			0x0606	/* USB 2.0 HUB */
#define	USB_PRODUCT_GENESYS_GL641USB		0x0700	/* GL641 USB_CompactFlash Card Reader */
#define	USB_PRODUCT_GENESYS_GL641USB2IDE_2	0x0701	/* GL641 USB_USB-IDE Bridge No 2 */
#define	USB_PRODUCT_GENESYS_GL641USB2IDE	0x0702	/* GL641 USB_USB-IDE Bridge */
#define	USB_PRODUCT_GENESYS_GL641USB_2		0x0760	/* GL641 USB_6-in-1 Card Reader */

/* GIGABYTE products */
#define	USB_PRODUCT_GIGABYTE_GN54G		0x8001	/* GN-54G */
#define	USB_PRODUCT_GIGABYTE_GNBR402W	0x8002	/* GN-BR402W */
#define	USB_PRODUCT_GIGABYTE_GNWLBM101	0x8003	/* GN-WLBM101 */
#define	USB_PRODUCT_GIGABYTE_GNWBKG		0x8007	/* GN-WBKG */
#define	USB_PRODUCT_GIGABYTE_GNWB01GS	0x8008	/* GN-WB01GS */
#define	USB_PRODUCT_GIGABYTE_GNWI05GS	0x800a	/* GN-WI05GS */

/* Gigaset products */
#define	USB_PRODUCT_GIGASET_WLAN			0x0701	/* WLAN */
#define	USB_PRODUCT_GIGASET_SMCWUSBTG		0x0710	/* SMCWUSBT-G */
#define	USB_PRODUCT_GIGASET_SMCWUSBTG_NF	0x0711	/* SMCWUSBT-G (no firmware) */
#define	USB_PRODUCT_GIGASET_AR5523			0x0712	/* AR5523 */
#define	USB_PRODUCT_GIGASET_AR5523_NF		0x0713	/* AR5523 (no firmware) */
#define	USB_PRODUCT_GIGASET_RT2573			0x0722	/* RT2573 */
#define	USB_PRODUCT_GIGASET_RT3070_1		0x0740	/* RT3070 */
#define	USB_PRODUCT_GIGASET_RT3070_2		0x0744	/* RT3070 */
#define	USB_PRODUCT_GIGABYTE_RT2870_1		0x800b	/* RT2870 */
#define	USB_PRODUCT_GIGABYTE_GNWB31N		0x800c	/* GN-WB31N */
#define	USB_PRODUCT_GIGABYTE_GNWB32L		0x800d	/* GN-WB32L */

/* Global Sun Technology #define	USB_PRODUCT_*/
#define	USB_PRODUCT_GLOBALSUN_AR5523_1		0x7801	/* AR5523 */
#define	USB_PRODUCT_GLOBALSUN_AR5523_1_NF	0x7802	/* AR5523 (no firmware) */
#define	USB_PRODUCT_GLOBALSUN_AR5523_2		0x7811	/* AR5523 */
#define	USB_PRODUCT_GLOBALSUN_AR5523_2_NF	0x7812	/* AR5523 (no firmware) */

/* Globespan products */
#define	USB_PRODUCT_GLOBESPAN_PRISM_GT_1	0x2000	/* PrismGT USB 2.0 WLAN */
#define	USB_PRODUCT_GLOBESPAN_PRISM_GT_2	0x2002	/* PrismGT USB 2.0 WLAN */

/* G.Mate, Inc products */
#define	USB_PRODUCT_GMATE_YP3X00		0x1001	/* YP3X00 PDA */

/* GN Otometrics */
#define	USB_PRODUCT_GNOTOMETRICS_USB	0x0010	/* FTDI compatible adapter */

/* GoHubs products */
#define	USB_PRODUCT_GOHUBS_GOCOM232		0x1001	/* GoCOM232 Serial */

/* Good Way Technology products */
#define	USB_PRODUCT_GOODWAY_GWUSB2E		0x6200	/* GWUSB2E */
#define	USB_PRODUCT_GOODWAY_RT2573		0xc019	/* RT2573 */

/* Google products */
#define	USB_PRODUCT_GOOGLE_NEXUSONE		0x4e11	/* Nexus One */

/* Gravis products */
#define	USB_PRODUCT_GRAVIS_GAMEPADPRO	0x4001	/* GamePad Pro */

/* GREENHOUSE products */
#define	USB_PRODUCT_GREENHOUSE_KANA21	0x0001	/* CF-writer with MP3 */

/* Griffin Technology */
#define	USB_PRODUCT_GRIFFIN_IMATE		0x0405	/* iMate, ADB Adapter */

/* Guillemot Corporation */
#define	USB_PRODUCT_GUILLEMOT_DALEADER		0xa300	/* DA Leader */
#define	USB_PRODUCT_GUILLEMOT_HWGUSB254		0xe000	/* HWGUSB2-54 WLAN */
#define	USB_PRODUCT_GUILLEMOT_HWGUSB254LB	0xe010	/* HWGUSB2-54-LB */
#define	USB_PRODUCT_GUILLEMOT_HWGUSB254V2AP	0xe020	/* HWGUSB2-54V2-AP */
#define	USB_PRODUCT_GUILLEMOT_HWNU300		0xe030	/* HWNU-300 */
#define	USB_PRODUCT_GUILLEMOT_HWNUM300		0xe031	/* HWNUm-300 */
#define	USB_PRODUCT_GUILLEMOT_HWGUN54		0xe032	/* HWGUn-54 */
#define	USB_PRODUCT_GUILLEMOT_HWNUP150		0xe033	/* HWNUP-150 */

/* Hagiwara products */
#define	USB_PRODUCT_HAGIWARA_FGSM		0x0002	/* FlashGate SmartMedia Card Reader */
#define	USB_PRODUCT_HAGIWARA_FGCF		0x0003	/* FlashGate CompactFlash Card Reader */
#define	USB_PRODUCT_HAGIWARA_FG			0x0005	/* FlashGate */

/* HAL Corporation products */
#define	USB_PRODUCT_HAL_IMR001			0x0011	/* Crossam2+ USB IR commander */

/* Handspring, Inc. */
#define	USB_PRODUCT_HANDSPRING_VISOR	0x0100	/* Handspring Visor */
#define	USB_PRODUCT_HANDSPRING_TREO		0x0200	/* Handspring Treo */
#define	USB_PRODUCT_HANDSPRING_TREO600	0x0300	/* Handspring Treo 600 */

/* Hauppauge Computer Works */
#define	USB_PRODUCT_HAUPPAUGE_WINTV_USB_FM	0x4d12	/* WinTV USB FM */
#define	USB_PRODUCT_HAUPPAUGE2_NOVAT500		0x9580	/* NovaT 500Stick */

/* Hawking Technologies products */
#define	USB_PRODUCT_HAWKING_RT2870_1	0x0001	/* RT2870 */
#define	USB_PRODUCT_HAWKING_RT2870_2	0x0003	/* RT2870 */
#define	USB_PRODUCT_HAWKING_HWUN2		0x0009	/* HWUN2 */
#define	USB_PRODUCT_HAWKING_RT3070		0x000b	/* RT3070 */
#define	USB_PRODUCT_HAWKING_RTL8192CU	0x0019	/* RTL8192CU */
#define	USB_PRODUCT_HAWKING_UF100		0x400c	/* 10/100 USB Ethernet */
#define	USB_PRODUCT_HAWKING_RTL8192SU_1	0x0015	/* RTL8192SU */
#define	USB_PRODUCT_HAWKING_RTL8192SU_2	0x0016	/* RTL8192SU */

/* HID Global GmbH products */
#define	USB_PRODUCT_HIDGLOBAL_CM2020	0x0596	/* Omnikey Cardman 2020 */
#define	USB_PRODUCT_HIDGLOBAL_CM6020	0x1784	/* Omnikey Cardman 6020 */

/* Hitachi, Ltd. products */
#define	USB_PRODUCT_HITACHI_DVDCAM_DZ_MV100A	0x0004	/* DVD-CAM DZ-MV100A Camcorder */
#define	USB_PRODUCT_HITACHI_DVDCAM_USB			0x001e	/* DVDCAM #define	USB_HS Interface */

/* Holtek products */
#define	USB_PRODUCT_HOLTEK_F85		0xa030	/* Holtek #define	USB_gaming keyboard */

/* HP products */
#define	USB_PRODUCT_HP_895C			0x0004	/* DeskJet 895C */
#define	USB_PRODUCT_HP_4100C		0x0101	/* Scanjet 4100C */
#define	USB_PRODUCT_HP_S20			0x0102	/* Photosmart S20 */
#define	USB_PRODUCT_HP_880C			0x0104	/* DeskJet 880C */
#define	USB_PRODUCT_HP_4200C		0x0105	/* ScanJet 4200C */
#define	USB_PRODUCT_HP_CDWRITERPLUS	0x0107	/* CD-Writer Plus */
#define	USB_PRODUCT_HP_KBDHUB		0x010c	/* Multimedia Keyboard Hub */
#define	USB_PRODUCT_HP_G55XI		0x0111	/* OfficeJet G55xi */
#define	USB_PRODUCT_HP_HN210W		0x011c	/* HN210W 802.11b WLAN */
#define	USB_PRODUCT_HP_49GPLUS		0x0121	/* 49g+ graphing calculator */
#define	USB_PRODUCT_HP_6200C		0x0201	/* ScanJet 6200C */
#define	USB_PRODUCT_HP_S20b			0x0202	/* PhotoSmart S20 */
#define	USB_PRODUCT_HP_815C			0x0204	/* DeskJet 815C */
#define	USB_PRODUCT_HP_3300C		0x0205	/* ScanJet 3300C */
#define	USB_PRODUCT_HP_CDW8200		0x0207	/* CD-Writer Plus 8200e */
#define	USB_PRODUCT_HP_MMKEYB		0x020c	/* Multimedia keyboard */
#define	USB_PRODUCT_HP_1220C		0x0212	/* DeskJet 1220C */
#define	USB_PRODUCT_HP_UN2420_QDL	0x241d	/* UN2420 QDL Firmware Loader */
#define	USB_PRODUCT_HP_UN2420		0x251d	/* UN2420 WWAN/GPS Module */
#define	USB_PRODUCT_HP_810C			0x0304	/* DeskJet 810C/812C */
#define	USB_PRODUCT_HP_4300C		0x0305	/* Scanjet 4300C */
#define	USB_PRODUCT_HP_CDW4E		0x0307	/* CD-Writer+ CD-4e */
#define	USB_PRODUCT_HP_G85XI		0x0311	/* OfficeJet G85xi */
#define	USB_PRODUCT_HP_1200			0x0317	/* LaserJet 1200 */
#define	USB_PRODUCT_HP_5200C		0x0401	/* Scanjet 5200C */
#define	USB_PRODUCT_HP_830C			0x0404	/* DeskJet 830C */
#define	USB_PRODUCT_HP_3400CSE		0x0405	/* ScanJet 3400cse */
#define	USB_PRODUCT_HP_6300C		0x0601	/* Scanjet 6300C */
#define	USB_PRODUCT_HP_840C			0x0604	/* DeskJet 840c */
#define	USB_PRODUCT_HP_2200C		0x0605	/* ScanJet 2200C */
#define	USB_PRODUCT_HP_5300C		0x0701	/* Scanjet 5300C */
#define	USB_PRODUCT_HP_4400C		0x0705	/* Scanjet 4400C */
#define	USB_PRODUCT_HP_4470C		0x0805	/* Scanjet 4470C */
#define	USB_PRODUCT_HP_82x0C		0x0b01	/* Scanjet 82x0C */
#define	USB_PRODUCT_HP_2300D		0x0b17	/* Laserjet 2300d */
#define	USB_PRODUCT_HP_970CSE		0x1004	/* Deskjet 970Cse */
#define	USB_PRODUCT_HP_5400C		0x1005	/* Scanjet 5400C */
#define	USB_PRODUCT_HP_2215			0x1016	/* iPAQ 22xx/Jornada 548 */
#define	USB_PRODUCT_HP_568J			0x1116	/* Jornada 568 */
#define	USB_PRODUCT_HP_930C			0x1204	/* DeskJet 930c */
#define	USB_PRODUCT_HP3_RTL8188CU	0x1629	/* RTL8188CU */
#define	USB_PRODUCT_HP_P2000U		0x1801	/* Inkjet P-2000U */
#define	USB_PRODUCT_HP_HS2300		0x1e1d	/* HS2300 HSDPA (aka MC8775) */
#define	USB_PRODUCT_HP_640C			0x2004	/* DeskJet 640c */
#define	USB_PRODUCT_HP_4670V		0x3005	/* ScanJet 4670v */
#define	USB_PRODUCT_HP_P1100		0x3102	/* Photosmart P1100 */
#define	USB_PRODUCT_HP_LD220		0x3524	/* LD220 POS Display */
#define	USB_PRODUCT_HP_OJ4215		0x3d11	/* OfficeJet 4215 */
#define	USB_PRODUCT_HP_HN210E		0x811c	/* Ethernet HN210E */
#define	USB_PRODUCT_HP2_C500		0x6002	/* PhotoSmart C500 */
#define	USB_PRODUCT_HP_EV2200		0x1b1d	/* ev2200 HSDPA (aka MC5720) */
#define	USB_PRODUCT_HP_HS2300		0x1e1d	/* hs2300 HSDPA (aka MC8775) */

/* HTC products */
#define	USB_PRODUCT_HTC_WINMOBILE		0x00ce	/* HTC USB Sync */
#define	USB_PRODUCT_HTC_PPC6700MODEM	0x00cf	/* PPC6700 Modem */
#define	USB_PRODUCT_HTC_SMARTPHONE		0x0a51	/* SmartPhone USB Sync */
#define	USB_PRODUCT_HTC_WIZARD			0x0bce	/* HTC Wizard USB Sync */
#define	USB_PRODUCT_HTC_LEGENDSYNC		0x0c97	/* HTC Legend USB Sync */
#define	USB_PRODUCT_HTC_LEGEND			0x0ff9	/* HTC Legend */
#define	USB_PRODUCT_HTC_LEGENDINTERNET	0x0ffe	/* HTC Legend Internet Sharing */

/* HUAWEI products */
#define	USB_PRODUCT_HUAWEI_MOBILE		0x1001	/* Huawei Mobile */
#define	USB_PRODUCT_HUAWEI_E220			0x1003	/* HSDPA modem */
#define	USB_PRODUCT_HUAWEI_E220BIS		0x1004	/* HSDPA modem */
#define	USB_PRODUCT_HUAWEI_E1401		0x1401	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1402		0x1402	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1403		0x1403	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1404		0x1404	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1405		0x1405	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1406		0x1406	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1407		0x1407	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1408		0x1408	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1409		0x1409	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E140A		0x140a	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E140B		0x140b	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E180V		0x140c	/* E180V */
#define	USB_PRODUCT_HUAWEI_E140D		0x140d	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E140E		0x140e	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E140F		0x140f	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1410		0x1410	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1411		0x1411	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1412		0x1412	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1413		0x1413	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1414		0x1414	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1415		0x1415	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1416		0x1416	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1417		0x1417	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1418		0x1418	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1419		0x1419	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E141A		0x141a	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E141B		0x141b	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E141C		0x141c	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E141D		0x141d	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E141E		0x141e	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E141F		0x141f	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1420		0x1420	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1421		0x1421	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1422		0x1422	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1423		0x1423	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1424		0x1424	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1425		0x1425	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1426		0x1426	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1427		0x1427	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1428		0x1428	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1429		0x1429	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E142A		0x142a	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E142B		0x142b	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E142C		0x142c	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E142D		0x142d	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E142E		0x142e	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E142F		0x142f	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1430		0x1430	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1431		0x1431	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1432		0x1432	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1433		0x1433	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1434		0x1434	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1435		0x1435	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1436		0x1436	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1437		0x1437	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1438		0x1438	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1439		0x1439	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E143A		0x143a	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E143B		0x143b	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E143C		0x143c	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E143D		0x143d	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E143E		0x143e	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E143F		0x143f	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1752		0x1446	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_K4505		0x1464	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_K3765		0x1465	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E1820		0x14ac	/* E1820 HSPA+ #define	USB_Slider */
#define	USB_PRODUCT_HUAWEI_K3770		0x14c9	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_K3772		0x14cf	/* K3772 */
#define	USB_PRODUCT_HUAWEI_K3770_INIT	0x14d1	/* K3770 Initial */
#define	USB_PRODUCT_HUAWEI_E3131_INIT	0x14fe	/* 3G modem initial */
#define	USB_PRODUCT_HUAWEI_E392			0x1505	/* LTE modem */
#define	USB_PRODUCT_HUAWEI_E3131		0x1506	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_K3765_INIT	0x1520	/* K3765 Initial */
#define	USB_PRODUCT_HUAWEI_K4505_INIT	0x1521	/* K4505 Initial */
#define	USB_PRODUCT_HUAWEI_K3772_INIT	0x1526	/* K3772 Initial */
#define	USB_PRODUCT_HUAWEI_E3272_INIT	0x155b	/* LTE modem initial */
#define	USB_PRODUCT_HUAWEI_ME909U		0x1573	/* LTE modem */
#define	USB_PRODUCT_HUAWEI_R215_INIT	0x1582	/* LTE modem initial */
#define	USB_PRODUCT_HUAWEI_R215			0x1588	/* LTE modem */
#define	USB_PRODUCT_HUAWEI_ME909S		0x15c1	/* LTE modem */
#define	USB_PRODUCT_HUAWEI_ETS2055		0x1803	/* CDMA modem */
#define	USB_PRODUCT_HUAWEI_E173			0x1c05	/* 3G modem */
#define	USB_PRODUCT_HUAWEI_E173_INIT	0x1c0b	/* 3G modem initial */
#define	USB_PRODUCT_HUAWEI_E3272		0x1c1e	/* LTE modem */

/* HUAWEI 3com products */
#define	USB_PRODUCT_HUAWEI3COM_WUB320G	0x0009	/* Aolynk WUB320g */

/* IBM Corporation */
#define	USB_PRODUCT_IBM_USBCDROMDRIVE	0x4427	/* USB CD-ROM Drive */

/* Icom products */
#define	USB_PRODUCT_ICOM_SP1		0x0004	/* FTDI compatible adapter */
#define	USB_PRODUCT_ICOM_OPC_U_UC	0x0018	/* FTDI compatible adapter */
#define	USB_PRODUCT_ICOM_RP2C1		0x0009	/* FTDI compatible adapter */
#define	USB_PRODUCT_ICOM_RP2C2		0x000a	/* FTDI compatible adapter */
#define	USB_PRODUCT_ICOM_RP2D		0x000b	/* FTDI compatible adapter */
#define	USB_PRODUCT_ICOM_RP2KVR		0x0013	/* FTDI compatible adapter */
#define	USB_PRODUCT_ICOM_RP2KVT		0x0012	/* FTDI compatible adapter */
#define	USB_PRODUCT_ICOM_RP2VR		0x000d	/* FTDI compatible adapter */
#define	USB_PRODUCT_ICOM_RP2VT		0x000c	/* FTDI compatible adapter */
#define	USB_PRODUCT_ICOM_RP4KVR		0x0011	/* FTDI compatible adapter */
#define	USB_PRODUCT_ICOM_RP4KVT		0x0010	/* FTDI compatible adapter */

/* ID-tech products */
#define	USB_PRODUCT_IDTECH_IDT1221U		0x0300	/* FTDI compatible adapter */

/* Imagination Technologies products */
#define	USB_PRODUCT_IMAGINATION_DBX1	0x2107	/* DBX1 DSP core */

/* Initio Corporation products */
#define	USB_PRODUCT_INITIO_DUMMY		0x0000	/* Dummy product */
#define	USB_PRODUCT_INITIO_INIC_1610P	0x1e40	/* #define	USB_to SATA Bridge */

/* Inside Out Networks products */
#define	USB_PRODUCT_INSIDEOUT_EDGEPORT4	0x0001	/* EdgePort/4 serial ports */

/* In-System products */
#define	USB_PRODUCT_INSYSTEM_F5U002		0x0002	/* Parallel printer */
#define	USB_PRODUCT_INSYSTEM_ATAPI		0x0031	/* ATAPI Adapter */
#define	USB_PRODUCT_INSYSTEM_ISD110		0x0200	/* IDE Adapter ISD110 */
#define	USB_PRODUCT_INSYSTEM_ISD105		0x0202	/* IDE Adapter ISD105 */
#define	USB_PRODUCT_INSYSTEM_USBCABLE	0x081a	/* #define	USB_cable */
#define	USB_PRODUCT_INSYSTEM_STORAGE_V2	0x5701	/* #define	USB_Storage Adapter V2 */

/* Intenso products */
#define	USB_PRODUCT_INTENSO_MEMORY_BOX	0x0701	/* External disk */

/* Intel products */
#define	USB_PRODUCT_INTEL_EASYPC_CAMERA	0x0110	/* Easy PC Camera */
#define	USB_PRODUCT_INTEL_TESTBOARD		0x9890	/* 82930 test board */
#define	USB_PRODUCT_INTEL2_IRMH			0x0020	/* Integrated Rate Matching Hub */
#define	USB_PRODUCT_INTEL2_IRMH2		0x0024	/* Integrated Rate Matching Hub */
#define	USB_PRODUCT_INTEL2_IRMH3		0x8000	/* Integrated Rate Matching Hub */
#define	USB_PRODUCT_INTEL2_IRMH4		0x8008	/* Integrated Rate Matching Hub */

/* Interbiometric products */
#define	USB_PRODUCT_INTERBIOMETRICS_IOBOARD			0x1002	/* FTDI compatible adapter */
#define	USB_PRODUCT_INTERBIOMETRICS_MINI_IOBOARD	0x1006	/* FTDI compatible adapter */

/* Intersil products */
#define	USB_PRODUCT_INTERSIL_PRISM_GT	0x1000	/* PrismGT USB 2.0 WLAN */
#define	USB_PRODUCT_INTERSIL_PRISM_2X	0x3642	/* Prism2.x or Atmel WLAN */

/* Interpid Control Systems products */
#define	USB_PRODUCT_INTREPIDCS_VALUECAN	0x0601	/* ValueCAN CAN bus interface */
#define	USB_PRODUCT_INTREPIDCS_NEOVI	0x0701	/* NeoVI Blue vehicle bus interface */

/* I/O DATA products */
#define	USB_PRODUCT_IODATA_IU_CD2		0x0204	/* DVD Multi-plus unit iU-CD2 */
#define	USB_PRODUCT_IODATA_DVR_UEH8		0x0206	/* DVD Multi-plus unit DVR-UEH8 */
#define	USB_PRODUCT_IODATA_USBSSMRW		0x0314	/* USB-SSMRW SD-card */
#define	USB_PRODUCT_IODATA_USBSDRW		0x031e	/* USB-SDRW SD-card */
#define	USB_PRODUCT_IODATA_USBETT		0x0901	/* USB ETT */
#define	USB_PRODUCT_IODATA_USBETTX		0x0904	/* USB ETTX */
#define	USB_PRODUCT_IODATA_USBETTXS		0x0913	/* USB ETTX */
#define	USB_PRODUCT_IODATA_USBWNB11A	0x0919	/* USB WN-B11 */
#define	USB_PRODUCT_IODATA_USBWNB11		0x0922	/* USB Airport WN-B11 */
#define	USB_PRODUCT_IODATA_ETGUS2		0x0930	/* ETG-US2 */
#define	USB_PRODUCT_IODATA_WNGDNUS2		0x093f	/* WN-GDN/US2 */
#define	USB_PRODUCT_IODATA_RT3072_1		0x0944	/* RT3072 */
#define	USB_PRODUCT_IODATA_RT3072_2		0x0945	/* RT3072 */
#define	USB_PRODUCT_IODATA_RT3072_3		0x0947	/* RT3072 */
#define	USB_PRODUCT_IODATA_RT3072_4		0x0948	/* RT3072 */
#define	USB_PRODUCT_IODATA_USBRSAQ		0x0a03	/* Serial USB-RSAQ1 */
#define	USB_PRODUCT_IODATA_USBRSAQ5		0x0a0e	/* Serial USB-RSAQ5 */
#define	USB_PRODUCT_IODATA2_USB2SC		0x0a09	/* USB2.0-SCSI Bridge USB2-SC */

/* Iomega products */
#define	USB_PRODUCT_IOMEGA_ZIP100		0x0001	/* Zip 100 */
#define	USB_PRODUCT_IOMEGA_ZIP250		0x0030	/* Zip 250 */

/* Ionic products */
#define	USB_PRODUCT_IONICS_PLUGCOMPUTER	0x0102	/* FTDI compatible adapter */

/* Integrated System Solution Corp. products */
#define	USB_PRODUCT_ISSC_ISSCBTA		0x1001	/* Bluetooth USB Adapter */

/* iTegno products */
#define	USB_PRODUCT_ITEGNO_WM1080A		0x1080	/* WM1080A GSM/GPRS modem */
#define	USB_PRODUCT_ITEGNO_WM2080A		0x2080	/* WM2080A CDMA modem */

/* Ituner networks products */
#define	USB_PRODUCT_ITUNERNET_USBLCD2X20	0x0002	/* USB-LCD 2x20 */
#define	USB_PRODUCT_ITUNERNET_USBLCD4X20	0xc001	/* USB-LCD 4x20 */

/* Jablotron products */
#define	USB_PRODUCT_JABLOTRON_PC60B		0x0001	/* PC-60B */

/* Jaton products */
#define	USB_PRODUCT_JATON_EDA			0x5704	/* Ethernet */

/* Jeti products */
#define	USB_PRODUCT_JETI_SPC1201		0x04b2	/* FTDI compatible adapter */

/* JMicron products */
#define USB_PRODUCT_JMICRON_JMS566		0x3569	/* USB to SATA 3.0Gb/s bridge */
#define	USB_PRODUCT_JMICRON_JMS567		0x0567	/* USB to SATA 6.0Gb/s bridge */
#define	USB_PRODUCT_JMICRON_JM20336		0x2336	/* USB to SATA Bridge */
#define	USB_PRODUCT_JMICRON_JM20337		0x2338	/* USB to ATA/ATAPI Bridge */

/* JVC products */
#define	USB_PRODUCT_JVC_GR_DX95			0x000a	/* GR-DX95 */
#define	USB_PRODUCT_JVC_MP_PRX1			0x3008	/* MP-PRX1 Ethernet */

/* JRC products */
#define	USB_PRODUCT_JRC_AH_J3001V_J3002V	0x0001	/* AirH PHONE AH-J3001V/J3002V */

/* Kamstrrup products */
#define	USB_PRODUCT_KAMSTRUP_OPTICALEYE		0x0001	/* Optical Eye/3-wire */
#define	USB_PRODUCT_KAMSTRUP_MBUS_250D		0x0005	/* M-Bus Master MultiPort 250D */

/* Kawatsu products */
#define	USB_PRODUCT_KAWATSU_MH4000P			0x0003	/* MiniHub 4000P */

/* Keisokugiken Corp. products */
#define	USB_PRODUCT_KEISOKUGIKEN_USBDAQ		0x0068	/* HKS-0200 USBDAQ */

/* Kensington products */
#define	USB_PRODUCT_KENSINGTON_ORBIT		0x1003	/* Orbit USB/PS2 trackball */
#define	USB_PRODUCT_KENSINGTON_TURBOBALL	0x1005	/* TurboBall */

/* Keyspan products */
#define	USB_PRODUCT_KEYSPAN_USA28_NF	0x0101	/* USA-28 serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA28X_NF	0x0102	/* USA-28X serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA19_NF	0x0103	/* USA-19 serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA18_NF	0x0104	/* USA-18 serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA18X_NF	0x0105	/* USA-18X serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA19W_NF	0x0106	/* USA-19W serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA19		0x0107	/* USA-19 serial Adapter */
#define	USB_PRODUCT_KEYSPAN_USA19W		0x0108	/* USA-19W serial Adapter */
#define	USB_PRODUCT_KEYSPAN_USA49W_NF	0x0109	/* USA-49W serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA49W		0x010a	/* USA-49W serial Adapter */
#define	USB_PRODUCT_KEYSPAN_USA19QI_NF	0x010b	/* USA-19QI serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA19QI		0x010c	/* USA-19QI serial Adapter */
#define	USB_PRODUCT_KEYSPAN_USA19Q_NF	0x010d	/* USA-19Q serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA19Q		0x010e	/* USA-19Q serial Adapter */
#define	USB_PRODUCT_KEYSPAN_USA28		0x010f	/* USA-28 serial Adapter */
#define	USB_PRODUCT_KEYSPAN_USA28XXB	0x0110	/* USA-28X/XB serial Adapter */
#define	USB_PRODUCT_KEYSPAN_USA18		0x0111	/* USA-18 serial Adapter */
#define	USB_PRODUCT_KEYSPAN_USA18X		0x0112	/* USA-18X serial Adapter */
#define	USB_PRODUCT_KEYSPAN_USA28XB_NF	0x0113	/* USA-28XB serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA28XA_NF	0x0114	/* USA-28XB serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA28XA		0x0115	/* USA-28XA serial Adapter */
#define	USB_PRODUCT_KEYSPAN_USA18XA_NF	0x0116	/* USA-18XA serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA18XA		0x0117	/* USA-18XA serial Adapter */
#define	USB_PRODUCT_KEYSPAN_USA19QW_NF	0x0118	/* USA-19WQ serial Adapter (no firmware) */
#define	USB_PRODUCT_KEYSPAN_USA19QW		0x0119	/* USA-19WQ serial Adapter */
#define	USB_PRODUCT_KEYSPAN_USA19HA		0x0121	/* USA-19HS serial Adapter */
#define	USB_PRODUCT_KEYSPAN_UIA10		0x0201	/* UIA-10 remote control */
#define	USB_PRODUCT_KEYSPAN_UIA11		0x0202	/* UIA-11 remote control */

/* Kingston products */
#define	USB_PRODUCT_KINGSTON_XX1		0x0008	/* Ethernet */
#define	USB_PRODUCT_KINGSTON_KNU101TX	0x000a	/* KNU101TX #define	USB_Ethernet */
#define	USB_PRODUCT_KINGSTON_HYPERX3_0	0x162b	/* DT HyperX 3.0 */

/* Kawasaki products */
#define	USB_PRODUCT_KLSI_DUH3E10BT		0x0008	/* #define	USB_Ethernet */
#define	USB_PRODUCT_KLSI_DUH3E10BTN		0x0009	/* #define	USB_Ethernet */

/* Kobil products */
#define	USB_PRODUCT_KOBIL_CONV_B1		0x2020	/* FTDI compatible adapter */
#define	USB_PRODUCT_KOBIL_CONV_KAAN		0x2021	/* FTDI compatible adapter */

/* Kodak products */
#define	USB_PRODUCT_KODAK_DC220		0x0100	/* Digital Science DC220 */
#define	USB_PRODUCT_KODAK_DC260		0x0110	/* Digital Science DC260 */
#define	USB_PRODUCT_KODAK_DC265		0x0111	/* Digital Science DC265 */
#define	USB_PRODUCT_KODAK_DC290		0x0112	/* Digital Science DC290 */
#define	USB_PRODUCT_KODAK_DC240		0x0120	/* Digital Science DC240 */
#define	USB_PRODUCT_KODAK_DC280		0x0130	/* Digital Science DC280 */

/* Kontron AG products */
#define	USB_PRODUCT_KONTRON_DM9601		0x8101	/* #define	USB_Ethernet */
#define	USB_PRODUCT_KONTRON_JP1082		0x9700	/* #define	USB_Ethernet */

/* Konica Corp. Products */
#define	USB_PRODUCT_KONICA_CAMERA		0x0720	/* Digital Color Camera */

/* KYE products */
#define	USB_PRODUCT_KYE_NICHE			0x0001	/* Niche mouse */
#define	USB_PRODUCT_KYE_NETSCROLL		0x0003	/* Genius NetScroll mouse */
#define	USB_PRODUCT_KYE_FLIGHT2000		0x1004	/* Flight 2000 joystick */
#define	USB_PRODUCT_KYE_VIVIDPRO		0x2001	/* ColorPage Vivid-Pro scanner */

/* Kyocera products */
#define	USB_PRODUCT_KYOCERA_FINECAM_S3X	0x0100	/* Finecam S3x */
#define	USB_PRODUCT_KYOCERA_FINECAM_S4	0x0101	/* Finecam S4 */
#define	USB_PRODUCT_KYOCERA_FINECAM_S5	0x0103	/* Finecam S5 */
#define	USB_PRODUCT_KYOCERA_FINECAM_L3	0x0105	/* Finecam L3 */
#define	USB_PRODUCT_KYOCERA_AHK3001V	0x0203	/* AH-K3001V */
#define	USB_PRODUCT_KYOCERA2_CDMA_MSM_K	0x17da	/* Qualcomm Kyocera CDMA Technologies MSM */
#define	USB_PRODUCT_KYOCERA2_KPC680		0x180a	/* Qualcomm Kyocera CDMA Technologies MSM */

/* LaCie products */
#define	USB_PRODUCT_LACIE_HD			0xa601	/* Hard Disk */
#define	USB_PRODUCT_LACIE_CDRW			0xa602	/* CD R/W */

/* Lake Shore Cryotronics products */
#define	USB_PRODUCT_LAKESHORE_121		0x0100	/* 121 Current Source */
#define	USB_PRODUCT_LAKESHORE_218A		0x0200	/* 218A Temperature Monitor */
#define	USB_PRODUCT_LAKESHORE_219		0x0201	/* 219 Temperature Monitor */
#define	USB_PRODUCT_LAKESHORE_233		0x0202	/* 233 Temperature Transmitter */
#define	USB_PRODUCT_LAKESHORE_235		0x0203	/* 235 Temperature Transmitter */
#define	USB_PRODUCT_LAKESHORE_335		0x0300	/* 335 Temperature Controller */
#define	USB_PRODUCT_LAKESHORE_336		0x0301	/* 336 Temperature Controller */
#define	USB_PRODUCT_LAKESHORE_350		0x0302	/* 350 Temperature Controller */
#define	USB_PRODUCT_LAKESHORE_371		0x0303	/* 371 AC Bridge */
#define	USB_PRODUCT_LAKESHORE_411		0x0400	/* 411 Handheld Gaussmeter */
#define	USB_PRODUCT_LAKESHORE_425		0x0401	/* 425 Gaussmeter */
#define	USB_PRODUCT_LAKESHORE_455A		0x0402	/* 455A DSP Gaussmeter */
#define	USB_PRODUCT_LAKESHORE_475A		0x0403	/* 475A DSP Gaussmeter */
#define	USB_PRODUCT_LAKESHORE_465		0x0404	/* 465 Gaussmeter */
#define	USB_PRODUCT_LAKESHORE_625A		0x0600	/* 625A Magnet PSU */
#define	USB_PRODUCT_LAKESHORE_642A		0x0601	/* 642A Magnet PSU */
#define	USB_PRODUCT_LAKESHORE_648		0x0602	/* 648 Magnet PSU */
#define	USB_PRODUCT_LAKESHORE_737		0x0700	/* 737 VSM Controller */
#define	USB_PRODUCT_LAKESHORE_776		0x0701	/* 776 Matrix Switch */

/* Larsen and Brusgaard products */
#define	USB_PRODUCT_LARSENBRUSGAARD_ALTITRACK	0x0001	/* FTDI compatible adapter */

/* Leadtek products */
#define	USB_PRODUCT_LEADTEK_9531		0x2101	/* 9531 GPS */

/* Lenovo products */
#define	USB_PRODUCT_LENOVO_GIGALAN		0x304b	/* USB 3.0 Ethernet */
#define	USB_PRODUCT_LENOVO_ETHERNET		0x7203	/* USB 2.0 Ethernet */

/* Lexar products */
#define	USB_PRODUCT_LEXAR_JUMPSHOT		0x0001	/* jumpSHOT CompactFlash Reader */
#define	USB_PRODUCT_LEXAR_CF_READER		0xb002	/* USB CF Reader */
#define	USB_PRODUCT_LEXAR_JUMPDRIVE		0xa833	/* USB Jumpdrive Flash Drive */

/* Lexmark products */
#define	USB_PRODUCT_LEXMARK_S2450		0x0009	/* Optra S 2450 */

/* Liebert products */
#define	USB_PRODUCT_LIEBERT_POWERSURE_PXT	0xffff	/* PowerSure Personal XT */
#define	USB_PRODUCT_LIEBERT2_PSI1000		0x0004	/* UPS PSI 1000 FW:08 */

/* Link Instruments Inc. products */
#define	USB_PRODUCT_LINKINSTRUMENTS_MSO19	0xf190	/* Link Instruments MSO-19 */
#define	USB_PRODUCT_LINKINSTRUMENTS_MSO28	0xf280	/* Link Instruments MSO-28 */
#define	USB_PRODUCT_LINKINSTRUMENTS_MSO28_2	0xf281	/* Link Instruments MSO-28 */

/* Linksys products */
#define	USB_PRODUCT_LINKSYS_MAUSB2		0x0105	/* Camedia MAUSB-2 */
#define	USB_PRODUCT_LINKSYS_USB10TX1	0x200c	/* USB10TX */
#define	USB_PRODUCT_LINKSYS_USB10T		0x2202	/* USB10T Ethernet */
#define	USB_PRODUCT_LINKSYS_USB100TX	0x2203	/* USB100TX Ethernet */
#define	USB_PRODUCT_LINKSYS_USB100H1	0x2204	/* USB100H1 Ethernet/HPNA */
#define	USB_PRODUCT_LINKSYS_USB10TA		0x2206	/* USB10TA Ethernet */
#define	USB_PRODUCT_LINKSYS_USB10TX2	0x400b	/* USB10TX */
#define	USB_PRODUCT_LINKSYS2_WUSB11		0x2219	/* WUSB11 Wireless Adapter */
#define	USB_PRODUCT_LINKSYS2_USB200M	0x2226	/* USB 2.0 10/100 Ethernet */
#define	USB_PRODUCT_LINKSYS3_WUSB11v28	0x2233	/* WUSB11 v2.8 Wireless Adapter */
#define	USB_PRODUCT_LINKSYS4_USB1000	0x0039	/* USB1000 */
#define	USB_PRODUCT_LINKSYS4_WUSB100	0x0070	/* WUSB100 */
#define	USB_PRODUCT_LINKSYS4_WUSB600N	0x0071	/* WUSB600N */
#define	USB_PRODUCT_LINKSYS4_WUSB54GCV2	0x0073	/* WUSB54GC v2 */
#define	USB_PRODUCT_LINKSYS4_WUSB54GCV3	0x0077	/* WUSB54GC v3 */
#define	USB_PRODUCT_LINKSYS4_RT3070		0x0078	/* RT3070 */
#define	USB_PRODUCT_LINKSYS4_WUSB600NV2	0x0079	/* WUSB600N v2 */

/* Logilink products */
#define	USB_PRODUCT_LOGILINK_DUMMY		0x0000	/* Dummy product */
#define	USB_PRODUCT_LOGILINK_U2M		0x0101	/* LogiLink USB MIDI Cable */

/* Logitech products */
#define	USB_PRODUCT_LOGITECH_M2452			0x0203	/* M2452 keyboard */
#define	USB_PRODUCT_LOGITECH_M4848			0x0301	/* M4848 mouse */
#define	USB_PRODUCT_LOGITECH_PAGESCAN		0x040f	/* PageScan */
#define	USB_PRODUCT_LOGITECH_QUICKCAMWEB	0x0801	/* QuickCam Web */
#define	USB_PRODUCT_LOGITECH_QUICKCAMPRO	0x0810	/* QuickCam Pro */
#define	USB_PRODUCT_LOGITECH_WEBCAMC100		0X0817	/* Webcam C100 */
#define	USB_PRODUCT_LOGITECH_QUICKCAMEXP	0x0840	/* QuickCam Express */
#define	USB_PRODUCT_LOGITECH_QUICKCAM		0x0850	/* QuickCam */
#define	USB_PRODUCT_LOGITECH_QUICKCAMOEM_1	0x08c6	/* QuickCam OEM */
#define	USB_PRODUCT_LOGITECH_QUICKCAMPRO3	0x0990	/* QuickCam Pro 9000 */
#define	USB_PRODUCT_LOGITECH_N43			0xc000	/* N43 */
#define	USB_PRODUCT_LOGITECH_N48			0xc001	/* N48 mouse */
#define	USB_PRODUCT_LOGITECH_MBA47			0xc002	/* M-BA47 mouse */
#define	USB_PRODUCT_LOGITECH_WMMOUSE		0xc004	/* WingMan Gaming Mouse */
#define	USB_PRODUCT_LOGITECH_BD58			0xc00c	/* BD58 mouse */
#define	USB_PRODUCT_LOGITECH_UN58A			0xc030	/* iFeel Mouse */
#define	USB_PRODUCT_LOGITECH_UN53B			0xc032	/* iFeel MouseMan */
#define	USB_PRODUCT_LOGITECH_WMPAD			0xc208	/* WingMan GamePad Extreme */
#define	USB_PRODUCT_LOGITECH_WMRPAD			0xc20a	/* WingMan RumblePad */
#define	USB_PRODUCT_LOGITECH_G510S			0xc22d	/* G510s Keyboard */
#define	USB_PRODUCT_LOGITECH_WMJOY			0xc281	/* WingMan Force joystick */
#define	USB_PRODUCT_LOGITECH_BB13			0xc401	/* USB-PS/2 Trackball */
#define	USB_PRODUCT_LOGITECH_RK53			0xc501	/* Cordless mouse */
#define	USB_PRODUCT_LOGITECH_RB6			0xc503	/* Cordless keyboard */
#define	USB_PRODUCT_LOGITECH_MX700			0xc506	/* Cordless optical mouse */
#define	USB_PRODUCT_LOGITECH_UNIFYING		0xc52b	/* Logitech Unifying Receiver */
#define	USB_PRODUCT_LOGITECH_QUICKCAMPRO2	0xd001	/* QuickCam Pro */

/* Logitec Corp. products */
#define	USB_PRODUCT_LOGITEC_LDR_H443SU2	0x0033	/* DVD Multi-plus unit LDR-H443SU2 */
#define	USB_PRODUCT_LOGITEC_LDR_H443U2	0x00b3	/* DVD Multi-plus unit LDR-H443U2 */
#define	USB_PRODUCT_LOGITEC_LAN_GTJU2A	0x0160	/* LAN-GTJ/U2A Ethernet */
#define	USB_PRODUCT_LOGITEC_RT2870_1	0x0162	/* RT2870 */
#define	USB_PRODUCT_LOGITEC_RT2870_2	0x0163	/* RT2870 */
#define	USB_PRODUCT_LOGITEC_RT2870_3	0x0164	/* RT2870 */
#define	USB_PRODUCT_LOGITEC_LANW300NU2	0x0166	/* LAN-W300N/U2 */
#define	USB_PRODUCT_LOGITEC_LANW150NU2	0x0168	/* LAN-W150N/U2 */
#define	USB_PRODUCT_LOGITEC_LANW300NU2S	0x0169	/* LAN-W300N/U2S */

/* Longcheer Holdings, Ltd. products */
#define	USB_PRODUCT_LONGCHEER_WM66		0x6061	/* Longcheer WM66 HSDPA */
#define	USB_PRODUCT_LONGCHEER_W14		0x9603	/* Mobilcom W14 */
#define	USB_PRODUCT_LONGCHEER_DISK		0xf000	/* Driver disk */
#define	USB_PRODUCT_LONGCHEER_XSSTICK	0x9605	/* 4G Systems XSStick P14 */


/* Lucent products */
#define	USB_PRODUCT_LUCENT_EVALKIT		0x1001	/* USS-720 evaluation kit */

/* Luwen products */
#define	USB_PRODUCT_LUWEN_EASYDISK		0x0005	/* EasyDisc */

/* Macally products */
#define	USB_PRODUCT_MACALLY_MOUSE1		0x0101	/* mouse */

/* Mag-Tek products */
#define	USB_PRODUCT_MAGTEK_USBSWIPE		0x0002	/* USB Mag Stripe Swipe Reader */

/* Marvell Technology Group, Ltd. products */
#define	USB_PRODUCT_MARVELL_SHEEVAPLUG	0x9e8f	/* SheevaPlug serial interface */

/* Matrix Orbital products */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0100		0x0100	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0101		0x0101	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0102		0x0102	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0103		0x0103	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0104		0x0104	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0105		0x0105	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0106		0x0106	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0107		0x0107	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0108		0x0108	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0109		0x0109	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_010A		0x010a	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_010B		0x010b	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_010C		0x010c	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_010D		0x010d	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_010E		0x010e	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_010F		0x010f	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0110		0x0110	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0111		0x0111	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0112		0x0112	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0113		0x0113	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0114		0x0114	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0115		0x0115	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0116		0x0116	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0117		0x0117	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0118		0x0118	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0119		0x0119	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_011A		0x011a	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_011B		0x011b	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_011C		0x011c	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_011D		0x011d	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_011E		0x011e	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_011F		0x011f	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0120		0x0120	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0121		0x0121	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0122		0x0122	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0123		0x0123	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0124		0x0124	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0125		0x0125	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0126		0x0126	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0128		0x0128	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0129		0x0129	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_012A		0x012a	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_012B		0x012b	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_012D		0x012d	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_012E		0x012e	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_012F		0x012f	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0130		0x0130	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0131		0x0131	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0132		0x0132	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0133		0x0133	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0134		0x0134	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0135		0x0135	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0136		0x0136	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0137		0x0137	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0138		0x0138	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0139		0x0139	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_013A		0x013a	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_013B		0x013b	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_013C		0x013c	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_013D		0x013d	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_013E		0x013e	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_013F		0x013f	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0140		0x0140	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0141		0x0141	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0142		0x0142	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0143		0x0143	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0144		0x0144	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0145		0x0145	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0146		0x0146	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0147		0x0147	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0148		0x0148	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0149		0x0149	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_014A		0x014a	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_014B		0x014b	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_014C		0x014c	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_014D		0x014d	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_014E		0x014e	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_014F		0x014f	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0150		0x0150	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0151		0x0151	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0152		0x0152	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_MOUA					0x0153	/* Martrix Orbital MOU-Axxxx LCD displays */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0159		0x0159	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_015A		0x015a	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_015B		0x015b	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_015C		0x015c	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_015D		0x015d	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_015E		0x015e	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_015F		0x015f	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0160		0x0160	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0161		0x0161	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0162		0x0162	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0163		0x0163	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0164		0x0164	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0165		0x0165	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0166		0x0166	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0167		0x0167	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0168		0x0168	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0169		0x0169	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_016A		0x016a	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_016B		0x016b	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_016C		0x016c	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_016D		0x016d	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_016E		0x016e	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_016F		0x016f	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0170		0x0170	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0171		0x0171	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0172		0x0172	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0173		0x0173	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0174		0x0174	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0175		0x0175	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0176		0x0176	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0177		0x0177	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0178		0x0178	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0179		0x0179	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_017A		0x017a	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_017B		0x017b	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_017C		0x017c	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_017D		0x017d	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_017E		0x017e	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_017F		0x017f	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0180		0x0180	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0181		0x0181	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0182		0x0182	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0183		0x0183	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0184		0x0184	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0185		0x0185	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0186		0x0186	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0187		0x0187	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0188		0x0188	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0189		0x0189	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_018A		0x018a	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_018B		0x018b	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_018C		0x018c	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_018D		0x018d	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_018E		0x018e	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_018F		0x018f	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0190		0x0190	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0191		0x0191	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0192		0x0192	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0193		0x0193	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0194		0x0194	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0195		0x0195	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0196		0x0196	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0197		0x0197	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0198		0x0198	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_0199		0x0199	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_019A		0x019a	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_019B		0x019b	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_019C		0x019c	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_019D		0x019d	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_019E		0x019e	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_019F		0x019f	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01A0		0x01a0	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01A1		0x01a1	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01A2		0x01a2	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01A3		0x01a3	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01A4		0x01a4	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01A5		0x01a5	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01A6		0x01a6	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01A7		0x01a7	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01A8		0x01a8	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01A9		0x01a9	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01AA		0x01aa	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01AB		0x01ab	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01AC		0x01ac	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01AD		0x01ad	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01AE		0x01ae	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01AF		0x01af	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01B0		0x01b0	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01B1		0x01b1	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01B2		0x01b2	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01B3		0x01b3	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01B4		0x01b4	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01B5		0x01b5	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01B6		0x01b6	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01B7		0x01b7	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01B8		0x01b8	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01B9		0x01b9	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01BA		0x01ba	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01BB		0x01bb	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01BC		0x01bc	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01BD		0x01bd	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01BE		0x01be	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01BF		0x01bf	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01C0		0x01c0	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01C1		0x01c1	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01C2		0x01c2	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01C3		0x01c3	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01C4		0x01c4	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01C5		0x01c5	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01C6		0x01c6	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01C7		0x01c7	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01C8		0x01c8	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01C9		0x01c9	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01CA		0x01ca	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01CB		0x01cb	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01CC		0x01cc	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01CD		0x01cd	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01CE		0x01ce	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01CF		0x01cf	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01D0		0x01d0	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01D1		0x01d1	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01D2		0x01d2	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01D3		0x01d3	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01D4		0x01d4	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01D5		0x01d5	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01D6		0x01d6	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01D7		0x01d7	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01D8		0x01d8	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01D9		0x01d9	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01DA		0x01da	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01DB		0x01db	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01DC		0x01dc	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01DD		0x01dd	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01DE		0x01de	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01DF		0x01df	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01E0		0x01e0	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01E1		0x01e1	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01E2		0x01e2	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01E3		0x01e3	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01E4		0x01e4	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01E5		0x01e5	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01E6		0x01e6	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01E7		0x01e7	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01E8		0x01e8	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01E9		0x01e9	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01EA		0x01ea	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01EB		0x01eb	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01EC		0x01ec	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01ED		0x01ed	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01EE		0x01ee	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01EF		0x01ef	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01F0		0x01f0	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01F1		0x01f1	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01F2		0x01f2	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01F3		0x01f3	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01F4		0x01f4	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01F5		0x01f5	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01F6		0x01f6	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01F7		0x01f7	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01F8		0x01f8	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01F9		0x01f9	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01FA		0x01fa	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01FB		0x01fb	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01FC		0x01fc	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01FD		0x01fd	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01FE		0x01fe	/* FTDI compatible adapter */
#define	USB_PRODUCT_MATRIXORBITAL_FTDI_RANGE_01FF		0x01ff	/* FTDI compatible adapter */

/* MCT Corp. */
#define	USB_PRODUCT_MCT_HUB0100			0x0100	/* Hub */
#define	USB_PRODUCT_MCT_DU_H3SP_USB232	0x0200	/* D-Link DU-H3SP #define	USB_BAY Hub */
#define	USB_PRODUCT_MCT_USB232			0x0210	/* USB-232 Interface */
#define	USB_PRODUCT_MCT_SITECOM_USB232	0x0230	/* Sitecom USB-232 Products */

/* Medeli */
#define	USB_PRODUCT_MEDELI_DD305		0x5011	/* DD305 Digital Drum Set */

/* MediaTek, Inc. */
#define	USB_PRODUCT_MEDIATEK_MTK3329	0x3329	/* MTK II GPS Receiver */

/* Meizu Electronics */
#define	USB_PRODUCT_MEIZU_M6_SL			0x0140	/* MiniPlayer M6 (SL) */

/* Melco, Inc products */
#define	USB_PRODUCT_MELCO_LUATX1		0x0001	/* LUA-TX Ethernet */
#define	USB_PRODUCT_MELCO_LUATX5		0x0005	/* LUA-TX Ethernet */
#define	USB_PRODUCT_MELCO_LUA2TX5		0x0009	/* LUA2-TX Ethernet */
#define	USB_PRODUCT_MELCO_LUAKTX		0x0012	/* LUA-KTX Ethernet */
#define	USB_PRODUCT_MELCO_DUBPXXG		0x001c	/* DUB-PxxG */
#define	USB_PRODUCT_MELCO_LUAU2KTX		0x003d	/* LUA-U2-KTX Ethernet */
#define	USB_PRODUCT_MELCO_KG54YB		0x005e	/* WLI-U2-KG54-YB WLAN */
#define	USB_PRODUCT_MELCO_KG54			0x0066	/* WLI-U2-KG54 WLAN */
#define	USB_PRODUCT_MELCO_KG54AI		0x0067	/* WLI-U2-KG54-AI WLAN */
#define	USB_PRODUCT_MELCO_LUA3U2AGT		0x006e	/* LUA3-U2-AGT */
#define	USB_PRODUCT_MELCO_NINWIFI		0x008b	/* Nintendo Wi-Fi */
#define	USB_PRODUCT_MELCO_PCOPRS1		0x00b3	/* PC-OP-RS1 RemoteStation */
#define	USB_PRODUCT_MELCO_SG54HP		0x00d8	/* WLI-U2-SG54HP */
#define	USB_PRODUCT_MELCO_G54HP			0x00d9	/* WLI-U2-G54HP */
#define	USB_PRODUCT_MELCO_KG54L			0x00da	/* WLI-U2-KG54L */
#define	USB_PRODUCT_MELCO_WLIUCG300N	0x00e8	/* WLI-UC-G300N */
#define	USB_PRODUCT_MELCO_SG54HG		0x00f4	/* WLI-U2-SG54HG */
#define	USB_PRODUCT_MELCO_WLRUCG		0x0116	/* WLR-UC-G */
#define	USB_PRODUCT_MELCO_WLRUCGAOSS	0x0119	/* WLR-UC-G-AOSS */
#define	USB_PRODUCT_MELCO_WLIUCAG300N	0x012e	/* WLI-UC-AG300N */
#define	USB_PRODUCT_MELCO_WLIUCG		0x0137	/* WLI-UC-G */
#define	USB_PRODUCT_MELCO_WLIUCG300HP	0x0148	/* WLI-UC-G300HP */
#define	USB_PRODUCT_MELCO_RT2870_2		0x0150	/* RT2870 */
#define	USB_PRODUCT_MELCO_WLIUCGN		0x015d	/* WLI-UC-GN */
#define	USB_PRODUCT_MELCO_WLIUCG301N	0x016f	/* WLI-UC-G301N */
#define	USB_PRODUCT_MELCO_WLIUCGNM		0x01a2	/* WLI-UC-GNM */
#define	USB_PRODUCT_MELCO_WLIUCG300HPV1	0x01a8	/* WLI-UC-G300HP-V1 */
#define	USB_PRODUCT_MELCO_WLIUCGNM2		0x01ee	/* WLI-UC-GNM2 */

/* Merlin products */
#define	USB_PRODUCT_MERLIN_V620			0x1110	/* Merlin V620 */

/* MetaGeek products */
#define	USB_PRODUCT_METAGEEK_TELLSTICK	0x0c30	/* FTDI compatible adapter */
#define	USB_PRODUCT_METAGEEK_WISPY1B	0x083e	/* MetaGeek Wi-Spy */
#define	USB_PRODUCT_METAGEEK_WISPY24X	0x083f	/* MetaGeek Wi-Spy 2.4x */
#define	USB_PRODUCT_METAGEEK2_WISPYDBX	0x5000	/* MetaGeek Wi-Spy DBx */

/* Metricom products */
#define	USB_PRODUCT_METRICOM_RICOCHET_GS	0x0001	/* Ricochet GS */

/* MGE UPS Systems */
#define	USB_PRODUCT_MGE_UPS1		0x0001	/* MGE UPS SYSTEMS PROTECTIONCENTER 1 */
#define	USB_PRODUCT_MGE_UPS2		0xffff	/* MGE UPS SYSTEMS PROTECTIONCENTER 2 */

/* MEI products */
#define	USB_PRODUCT_MEI_CASHFLOW_SC	0x1100	/* Cashflow-SC Cash Acceptor */
#define	USB_PRODUCT_MEI_S2000		0x1101	/* Series 2000 Combo Acceptor */

/* Microdia / Sonix Techonology Co., Ltd. products */
#define	USB_PRODUCT_CHICONY2_YUREX		0x1010	/* YUREX */
#define	USB_PRODUCT_CHICONY2_CAM_1		0x62c0	/* CAM 1 */
#define	USB_PRODUCT_CHICONY2_TEMPER		0x7401	/* TEMPer sensor */

/* Micro Star International products */
#define	USB_PRODUCT_MSI_BT_DONGLE		0x1967	/* Bluetooth USB dongle */
#define	USB_PRODUCT_MSI_RT3070_1		0x3820	/* RT3070 */
#define	USB_PRODUCT_MSI_RT3070_2		0x3821	/* RT3070 */
#define	USB_PRODUCT_MSI_RT3070_8		0x3822	/* RT3070 */
#define	USB_PRODUCT_MSI_RT3070_3		0x3870	/* RT3070 */
#define	USB_PRODUCT_MSI_RT3070_9		0x3871	/* RT3070 */
#define	USB_PRODUCT_MSI_UB11B			0x6823	/* UB11B */
#define	USB_PRODUCT_MSI_RT2570			0x6861	/* RT2570 */
#define	USB_PRODUCT_MSI_RT2570_2		0x6865	/* RT2570 */
#define	USB_PRODUCT_MSI_RT2570_3		0x6869	/* RT2570 */
#define	USB_PRODUCT_MSI_RT2573_1		0x6874	/* RT2573 */
#define	USB_PRODUCT_MSI_RT2573_2		0x6877	/* RT2573 */
#define	USB_PRODUCT_MSI_RT3070_4		0x6899	/* RT3070 */
#define	USB_PRODUCT_MSI_RT3070_5		0x821a	/* RT3070 */
#define	USB_PRODUCT_MSI_RT3070_10		0x822a	/* RT3070 */
#define	USB_PRODUCT_MSI_RT3070_6		0x870a	/* RT3070 */
#define	USB_PRODUCT_MSI_RT3070_11		0x871a	/* RT3070 */
#define	USB_PRODUCT_MSI_RT3070_7		0x899a	/* RT3070 */
#define	USB_PRODUCT_MSI_RT2573_3		0xa861	/* RT2573 */
#define	USB_PRODUCT_MSI_RT2573_4		0xa874	/* RT2573 */

/* Micron products */
#define	USB_PRODUCT_MICRON_REALSSD		0x0655	/* Real SSD eUSB */

/* Microsoft products */
#define	USB_PRODUCT_MICROSOFT_SIDEPREC		0x0008	/* SideWinder Precision Pro */
#define	USB_PRODUCT_MICROSOFT_INTELLIMOUSE	0x0009	/* IntelliMouse */
#define	USB_PRODUCT_MICROSOFT_NATURALKBD	0x000b	/* Natural Keyboard Elite */
#define	USB_PRODUCT_MICROSOFT_DDS80			0x0014	/* Digital Sound System 80 */
#define	USB_PRODUCT_MICROSOFT_SIDEWINDER	0x001a	/* Sidewinder Precision Racing Wheel */
#define	USB_PRODUCT_MICROSOFT_INETPRO		0x001c	/* Internet Keyboard Pro */
#define	USB_PRODUCT_MICROSOFT_TBEXPLORER	0x0024	/* Trackball Explorer */
#define	USB_PRODUCT_MICROSOFT_INTELLIEYE	0x0025	/* IntelliEye mouse */
#define	USB_PRODUCT_MICROSOFT_INETPRO2		0x002b	/* Internet Keyboard Pro */
#define	USB_PRODUCT_MICROSOFT_INTELLIMOUSE5	0x0039	/* IntelliMouse 1.1 5-Button Mouse */
#define	USB_PRODUCT_MICROSOFT_WHEELMOUSE	0x0040	/* Wheel Mouse Optical */
#define	USB_PRODUCT_MICROSOFT_MN510			0x006e	/* MN510 Wireless */
#define	USB_PRODUCT_MICROSOFT_700WX			0x0079	/* Palm 700WX */
#define	USB_PRODUCT_MICROSOFT_MN110			0x007a	/* 10/100 USB NIC */
#define	USB_PRODUCT_MICROSOFT_WLINTELLIMOUSE	0x008c	/* Wireless Optical IntelliMouse */
#define	USB_PRODUCT_MICROSOFT_WLNOTEBOOK	0x00b9	/* Wireless Optical Mouse (Model 1023) */
#define	USB_PRODUCT_MICROSOFT_COMFORT3000	0x00d1	/* Comfort Optical Mouse 3000 (Model 1043) */
#define	USB_PRODUCT_MICROSOFT_WLNOTEBOOK3	0x00d2	/* Wireless Optical Mouse 3000 (Model 1049) */
#define	USB_PRODUCT_MICROSOFT_NATURAL4000	0x00db	/* Natural Ergonomic Keyboard 4000 */
#define	USB_PRODUCT_MICROSOFT_WLNOTEBOOK2	0x00e1	/* Wireless Optical Mouse 3000 (Model 1056) */
#define	USB_PRODUCT_MICROSOFT_XBOX360		0x0292	/* XBOX 360 WLAN */

/* Microtech products */
#define	USB_PRODUCT_MICROTECH_SCSIDB25	0x0004	/* USB-SCSI-DB25 */
#define	USB_PRODUCT_MICROTECH_SCSIHD50	0x0005	/* USB-SCSI-HD50 */
#define	USB_PRODUCT_MICROTECH_DPCM		0x0006	/* USB CameraMate */
#define	USB_PRODUCT_MICROTECH_FREECOM	0xfc01	/* Freecom USB-IDE */

/* Microtek products */
#define	USB_PRODUCT_MICROTEK_336CX		0x0094	/* Phantom 336CX - C3 scanner */
#define	USB_PRODUCT_MICROTEK_X6U		0x0099	/* ScanMaker X6 - X6U */
#define	USB_PRODUCT_MICROTEK_C6			0x009a	/* Phantom C6 scanner */
#define	USB_PRODUCT_MICROTEK_336CX2		0x00a0	/* Phantom 336CX - C3 scanner */
#define	USB_PRODUCT_MICROTEK_V6USL		0x00a3	/* ScanMaker V6USL */
#define	USB_PRODUCT_MICROTEK_V6USL2		0x80a3	/* ScanMaker V6USL */
#define	USB_PRODUCT_MICROTEK_V6UL		0x80ac	/* ScanMaker V6UL */

/* Microtune, Inc. products */
#define	USB_PRODUCT_MICROTUNE_BT_DONGLE		0x1000	/* Bluetooth #define	USB_dongle */

/* Midiman products */
#define	USB_PRODUCT_MAUDIO_MIDISPORT2X2		0x1001	/* Midisport 2x2 */
#define	USB_PRODUCT_MAUDIO_FASTTRACKULTRA	0x2080	/* Fast Track Ultra */
#define	USB_PRODUCT_MAUDIO_FASTTRACKULTRA8R	0x2081	/* Fast Track Ultra 8R */

/* MindsAtWork products */
#define	USB_PRODUCT_MINDSATWORK_WALLET		0x0001	/* Digital Wallet */

/* Minolta Co., Ltd. */
#define	USB_PRODUCT_MINOLTA_2300		0x4001	/* Dimage 2300 */
#define	USB_PRODUCT_MINOLTA_S304		0x4007	/* Dimage S304 */
#define	USB_PRODUCT_MINOLTA_X			0x4009	/* Dimage X */
#define	USB_PRODUCT_MINOLTA_5400		0x400e	/* Dimage 5400 */
#define	USB_PRODUCT_MINOLTA_F300		0x4011	/* Dimage F300 */
#define	USB_PRODUCT_MINOLTA_E223		0x4017	/* Dimage E223 */

/* Mitsumi products */
#define	USB_PRODUCT_MITSUMI_CDRRW		0x0000	/* CD-R/RW Drive */
#define	USB_PRODUCT_MITSUMI_BT_DONGLE	0x641f	/* Bluetooth USB dongle */
#define	USB_PRODUCT_MITSUMI_FDD			0x6901	/* USB FDD */

/* Mobile Action products */
#define	USB_PRODUCT_MOBILEACTION_MA620	0x0620	/* MA-620 Infrared Adapter */

/* Mobility products */
#define	USB_PRODUCT_MOBILITY_USB_SERIAL	0x0202	/* FTDI compatible adapter */
#define	USB_PRODUCT_MOBILITY_EA			0x0204	/* Ethernet */
#define	USB_PRODUCT_MOBILITY_EASIDOCK	0x0304	/* EasiDock Ethernet */

/* MosChip products */
#define	USB_PRODUCT_MOSCHIP_MCS7703		0x7703	/* MCS7703 Serial Port Adapter */
#define	USB_PRODUCT_MOSCHIP_MCS7730		0x7730	/* MCS7730 Ethernet */
#define	USB_PRODUCT_MOSCHIP_MCS7820		0x7820	/* MCS7820 Serial Port Adapter */
#define	USB_PRODUCT_MOSCHIP_MCS7830		0x7830	/* MCS7830 Ethernet */
#define	USB_PRODUCT_MOSCHIP_MCS7832		0x7832	/* MCS7832 Ethernet */
#define	USB_PRODUCT_MOSCHIP_MCS7840		0x7840	/* MCS7840 Serial Port Adapter */

/* Motorola products */
#define	USB_PRODUCT_MOTOROLA_MC141555	0x1555	/* MC141555 hub controller */
#define	USB_PRODUCT_MOTOROLA_SB4100		0x4100	/* SB4100 USB Cable Modem */
#define	USB_PRODUCT_MOTOROLA2_T720C		0x2822	/* T720c */
#define	USB_PRODUCT_MOTOROLA2_A41XV32X	0x2a22	/* A41x/V32x Mobile Phones */
#define	USB_PRODUCT_MOTOROLA2_E398		0x4810	/* E398 Mobile Phone */
#define	USB_PRODUCT_MOTOROLA2_USBLAN	0x600c	/* USBLAN */
#define	USB_PRODUCT_MOTOROLA2_USBLAN2	0x6027	/* USBLAN */
#define	USB_PRODUCT_MOTOROLA2_MB886		0x710f	/* MB886 Mobile Phone (Atria HD) */
#define	USB_PRODUCT_MOTOROLA4_RT2770	0x9031	/* RT2770 */
#define	USB_PRODUCT_MOTOROLA4_RT3070	0x9032	/* RT3070 */

/* MpMan products */
#define	USB_PRODUCT_MPMAN_MPF400_2		0x25a8	/* MPF400 Music Player 2Go */
#define	USB_PRODUCT_MPMAN_MPF400_1		0x36d0	/* MPF400 Music Player 1Go */

/* MultiTech products */
#define	USB_PRODUCT_MULTITECH_ATLAS		0xf101	/* MT5634ZBA-USB modem */

/* Mustek products */
#define	USB_PRODUCT_MUSTEK_1200CU		0x0001	/* 1200 CU scanner */
#define	USB_PRODUCT_MUSTEK_600CU		0x0002	/* 600 CU scanner */
#define	USB_PRODUCT_MUSTEK_1200USB		0x0003	/* 1200 USB scanner */
#define	USB_PRODUCT_MUSTEK_1200UB		0x0006	/* 1200 UB scanner */
#define	USB_PRODUCT_MUSTEK_1200USBPLUS	0x0007	/* 1200 USB Plus scanner */
#define	USB_PRODUCT_MUSTEK_1200CUPLUS	0x0008	/* 1200 CU Plus scanner */
#define	USB_PRODUCT_MUSTEK_BEARPAW1200F	0x0010	/* BearPaw 1200F scanner */
#define	USB_PRODUCT_MUSTEK_BEARPAW2400TA	0x0218	/* BearPaw 2400TA scanner */
#define	USB_PRODUCT_MUSTEK_BEARPAW1200TA	0x021e	/* BearPaw 1200TA scanner */
#define	USB_PRODUCT_MUSTEK_600USB			0x0873	/* 600 USB scanner */
#define	USB_PRODUCT_MUSTEK_MDC800			0xa800	/* MDC-800 digital camera */

/* M-Systems products */
#define	USB_PRODUCT_MSYSTEMS_DISKONKEY	0x0010	/* DiskOnKey */
#define	USB_PRODUCT_MSYSTEMS_DISKONKEY2	0x0011	/* DiskOnKey */

/* Myson products */
#define	USB_PRODUCT_MYSON_HEDEN_8813	0x8813	/* USB-IDE */
#define	USB_PRODUCT_MYSON_HEDEN			0x8818	/* USB-IDE */
#define	USB_PRODUCT_MYSON_HUBREADER		0x8819	/* COMBO Card reader with USB HUB */
#define	USB_PRODUCT_MYSON_STARREADER	0x9920	/* USB flash card adapter */

/* National Semiconductor */
#define	USB_PRODUCT_NATIONAL_BEARPAW1200	0x1000	/* BearPaw 1200 */
#define	USB_PRODUCT_NATIONAL_BEARPAW2400	0x1001	/* BearPaw 2400 */

/* NEC products */
#define	USB_PRODUCT_NEC_HUB_0050	0x0050	/* USB 2.0 7-Port Hub */
#define	USB_PRODUCT_NEC_HUB_005A	0x005a	/* USB 2.0 4-Port Hub */
#define	USB_PRODUCT_NEC_WL300NUG	0x0249	/* WL300NU-G */
#define	USB_PRODUCT_NEC_HUB			0x55aa	/* hub */
#define	USB_PRODUCT_NEC_HUB_B		0x55ab	/* hub */

/* NEODIO products */
#define	USB_PRODUCT_NEODIO_ND3260		0x3260	/* 8-in-1 Multi-format Flash Controller */
#define	USB_PRODUCT_NEODIO_ND5010		0x5010	/* Multi-format Flash Controller */

/* Neotel products */
#define	USB_PRODUCT_NEOTEL_PRIME		0x4000	/* Prime USB modem */

/* Netac products */
#define	USB_PRODUCT_NETAC_CF_CARD		0x1060	/* USB-CF-Card */
#define	USB_PRODUCT_NETAC_ONLYDISK		0x0003	/* OnlyDisk */

/* NetChip Technology Products */
#define	USB_PRODUCT_NETCHIP_TURBOCONNECT	0x1080	/* Turbo-Connect */
#define	USB_PRODUCT_NETCHIP_CLIK_40			0xa140	/* USB Clik! 40 */
#define	USB_PRODUCT_NETCHIP_GADGETZERO		0xa4a0	/* Linux Gadget Zero */
#define	USB_PRODUCT_NETCHIP_ETHERNETGADGET	0xa4a2	/* Linux Ethernet/RNDIS gadget on pxa210/25x/26x */
#define	USB_PRODUCT_NETCHIP_POCKETBOOK		0xa4a5	/* PocketBook */

/* Netgear products */
#define	USB_PRODUCT_NETGEAR_EA101		0x1001	/* Ethernet */
#define	USB_PRODUCT_NETGEAR_EA101X		0x1002	/* Ethernet */
#define	USB_PRODUCT_NETGEAR_FA101		0x1020	/* Ethernet 10/100, USB1.1 */
#define	USB_PRODUCT_NETGEAR_FA120		0x1040	/* USB 2.0 Ethernet */
#define	USB_PRODUCT_NETGEAR_M4100		0x1100	/* M4100/M5300/M7100 series switch */
#define	USB_PRODUCT_NETGEAR_WG111V1_2	0x4240	/* PrismGT USB 2.0 WLAN */
#define	USB_PRODUCT_NETGEAR_WG111V3		0x4260	/* WG111v3 */
#define	USB_PRODUCT_NETGEAR_WG111U		0x4300	/* WG111U */
#define	USB_PRODUCT_NETGEAR_WG111U_NF	0x4301	/* WG111U (no firmware) */
#define	USB_PRODUCT_NETGEAR_WG111V2		0x6a00	/* WG111V2 */
#define	USB_PRODUCT_NETGEAR_WN111V2		0x9001	/* WN111V2 */
#define	USB_PRODUCT_NETGEAR_WNDA3100	0x9010	/* WNDA3100 */
#define	USB_PRODUCT_NETGEAR_WNDA4100	0x9012	/* WNDA4100 */
#define	USB_PRODUCT_NETGEAR_WNDA3200	0x9018	/* WNDA3200 */
#define	USB_PRODUCT_NETGEAR_RTL8192CU	0x9021	/* RTL8192CU */
#define	USB_PRODUCT_NETGEAR_WNA1000		0x9040	/* WNA1000 */
#define	USB_PRODUCT_NETGEAR_WNA1000M	0x9041	/* WNA1000M */
#define	USB_PRODUCT_NETGEAR2_MA101		0x4100	/* MA101 */
#define	USB_PRODUCT_NETGEAR2_MA101B		0x4102	/* MA101 Rev B */
#define	USB_PRODUCT_NETGEAR3_WG111T		0x4250	/* WG111T */
#define	USB_PRODUCT_NETGEAR3_WG111T_NF	0x4251	/* WG111T (no firmware) */
#define	USB_PRODUCT_NETGEAR3_WPN111		0x5f00	/* WPN111 */
#define	USB_PRODUCT_NETGEAR3_WPN111_NF	0x5f01	/* WPN111 (no firmware) */
#define	USB_PRODUCT_NETGEAR3_WPN111_2	0x5f02	/* WPN111 */
#define	USB_PRODUCT_NETGEAR4_RTL8188CU	0x9041	/* RTL8188CU */

/* NetIndex products */
#define	USB_PRODUCT_NETINDEX_WS002IN		0x2001	/* Willcom WS002IN */

/* NEWlink */
#define	USB_PRODUCT_NEWLINK_USB2IDEBRIDGE	0x00ff	/* USB 2.0 Hard Drive Enclosure */

/* Nikon products */
#define	USB_PRODUCT_NIKON_E990		0x0102	/* Digital Camera E990 */
#define	USB_PRODUCT_NIKON_LS40		0x4000	/* CoolScan LS40 ED */
#define	USB_PRODUCT_NIKON_D300		0x041a	/* Digital Camera D300 */

/* NovaTech Products */
#define	USB_PRODUCT_NOVATECH_NV902		0x9020	/* NovaTech NV-902W */
#define	USB_PRODUCT_NOVATECH_RT2573		0x9021	/* RT2573 */
#define	USB_PRODUCT_NOVATECH_RTL8188CU	0x9071	/* RTL8188CU */

/* Nokia products */
#define	USB_PRODUCT_NOKIA_N958GB		0x0070	/* Nokia N95 8GBc */
#define	USB_PRODUCT_NOKIA2_CA42			0x1234	/* CA-42 cable */

/* Novatel Wireless products */
#define	USB_PRODUCT_NOVATEL_V640		0x1100	/* Merlin V620 */
#define	USB_PRODUCT_NOVATEL_CDMA_MODEM	0x1110	/* Novatel Wireless Merlin CDMA */
#define	USB_PRODUCT_NOVATEL_V620		0x1110	/* Merlin V620 */
#define	USB_PRODUCT_NOVATEL_V740		0x1120	/* Merlin V740 */
#define	USB_PRODUCT_NOVATEL_V720		0x1130	/* Merlin V720 */
#define	USB_PRODUCT_NOVATEL_U740		0x1400	/* Merlin U740 */
#define	USB_PRODUCT_NOVATEL_U740_2		0x1410	/* Merlin U740 */
#define	USB_PRODUCT_NOVATEL_U870		0x1420	/* Merlin U870 */
#define	USB_PRODUCT_NOVATEL_XU870		0x1430	/* Merlin XU870 */
#define	USB_PRODUCT_NOVATEL_X950D		0x1450	/* Merlin X950D */
#define	USB_PRODUCT_NOVATEL_ES620		0x2100	/* Expedite ES620 */
#define	USB_PRODUCT_NOVATEL_E725		0x2120	/* Expedite E725 */
#define	USB_PRODUCT_NOVATEL_ES620_2		0x2130	/* Expedite ES620 */
#define	USB_PRODUCT_NOVATEL_ES620		0x2100	/* ES620 CDMA */
#define	USB_PRODUCT_NOVATEL_U720		0x2110	/* Merlin U720 */
#define	USB_PRODUCT_NOVATEL_EU730		0x2400	/* Expedite EU730 */
#define	USB_PRODUCT_NOVATEL_EU740		0x2410	/* Expedite EU740 */
#define	USB_PRODUCT_NOVATEL_EU870D		0x2420	/* Expedite EU870D */
#define	USB_PRODUCT_NOVATEL_U727		0x4100	/* Merlin U727 CDMA */
#define	USB_PRODUCT_NOVATEL_MC950D		0x4400	/* Novatel MC950D HSUPA */
#define	USB_PRODUCT_NOVATEL_MC990D		0x7001	/* Novatel MC990D */
#define	USB_PRODUCT_NOVATEL_ZEROCD		0x5010	/* Novatel ZeroCD */
#define	USB_PRODUCT_NOVATEL_MIFI2200V	0x5020	/* Novatel MiFi 2200 CDMA Virgin Mobile */
#define	USB_PRODUCT_NOVATEL_ZEROCD2		0x5030	/* Novatel ZeroCD */
#define	USB_PRODUCT_NOVATEL_MIFI2200	0x5041	/* Novatel MiFi 2200 CDMA */
#define	USB_PRODUCT_NOVATEL_U727_2		0x5100	/* Merlin U727 CDMA */
#define	USB_PRODUCT_NOVATEL_U760		0x6000	/* Novatel U760 */
#define	USB_PRODUCT_NOVATEL_MC760		0x6002	/* Novatel MC760 */
#define	USB_PRODUCT_NOVATEL_MC547		0x7042	/* Novatel MC547 */
#define	USB_PRODUCT_NOVATEL_MC679		0x7031	/* Novatel MC679 */
#define	USB_PRODUCT_NOVATEL2_FLEXPACKGPS	0x0100	/* NovAtel FlexPack GPS receiver */

/* Merlin products */
#define	USB_PRODUCT_MERLIN_V620				0x1110	/* Merlin V620 */

/* O2Micro products */
#define	USB_PRODUCT_O2MICRO_OZ776_HUB		0x7761	/* OZ776 hub */
#define	USB_PRODUCT_O2MICRO_OZ776_CCID_SC	0x7772	/* OZ776 CCID SC Reader */

/* Olimex products */
#define	USB_PRODUCT_OLIMEX_ARM_USB_OCD		0x0003	/* FTDI compatible adapter */
#define	USB_PRODUCT_OLIMEX_ARM_USB_OCD_H	0x002b	/* FTDI compatible adapter */

/* Olympus products */
#define	USB_PRODUCT_OLYMPUS_C1				0x0102	/* C-1 Digital Camera */
#define	USB_PRODUCT_OLYMPUS_C700			0x0105	/* C-700 Ultra Zoom */

/* OmniVision Technologies, Inc. products */
#define	USB_PRODUCT_OMNIVISION_OV511		0x0511	/* OV511 Camera */
#define	USB_PRODUCT_OMNIVISION_OV511PLUS	0xa511	/* OV511+ Camera */

/* OnSpec Electronic, Inc. */
#define	USB_PRODUCT_ONSPEC_SDS_HOTFIND_D		0x0400	/* SDS-infrared.com Hotfind-D Infrared Camera */
#define	USB_PRODUCT_ONSPEC_MDCFE_B_CF_READER	0xa000	/* MDCFE-B USB CF Reader */
#define	USB_PRODUCT_ONSPEC_CFMS_RW				0xa001	/* SIIG/Datafab Memory Stick+CF Reader/Writer */
#define	USB_PRODUCT_ONSPEC_READER				0xa003	/* Datafab-based Reader */
#define	USB_PRODUCT_ONSPEC_CFSM_READER			0xa005	/* PNY/Datafab CF+SM Reader */
#define	USB_PRODUCT_ONSPEC_CFSM_READER2			0xa006	/* Simple Tech/Datafab CF+SM Reader */
#define	USB_PRODUCT_ONSPEC_MDSM_B_READER		0xa103	/* MDSM-B reader */
#define	USB_PRODUCT_ONSPEC_CFSM_COMBO			0xa109	/* USB to CF + SM Combo (LC1) */
#define	USB_PRODUCT_ONSPEC_UCF100				0xa400	/* FlashLink UCF-100 CompactFlash Reader */
#define	USB_PRODUCT_ONSPEC2_IMAGEMATE_SDDR55	0xa103	/* ImageMate SDDR55 */

/* Option products */
#define	USB_PRODUCT_OPTION_VODAFONEMC3G	0x5000	/* Vodafone Mobile Connect 3G datacard */
#define	USB_PRODUCT_OPTION_GT3G			0x6000	/* GlobeTrotter 3G datacard */
#define	USB_PRODUCT_OPTION_GT3GQUAD		0x6300	/* GlobeTrotter 3G QUAD datacard */
#define	USB_PRODUCT_OPTION_GT3GPLUS		0x6600	/* GlobeTrotter 3G+ datacard */
#define	USB_PRODUCT_OPTION_GTICON322	0xd033	/* GlobeTrotter Icon322 storage */
#define	USB_PRODUCT_OPTION_GTMAX36		0x6701	/* GlobeTrotter Max 3.6 Modem */
#define	USB_PRODUCT_OPTION_GTMAX72		0x6711	/* GlobeTrotter Max 7.2 HSDPA */
#define	USB_PRODUCT_OPTION_GTHSDPA		0x6971	/* GlobeTrotter HSDPA */
#define	USB_PRODUCT_OPTION_GTMAXHSUPA	0x7001	/* GlobeTrotter HSUPA */
#define	USB_PRODUCT_OPTION_GTMAXHSUPAE	0x6901	/* GlobeTrotter HSUPA PCIe */
#define	USB_PRODUCT_OPTION_GTMAX380HSUPAE	0x7211	/* GlobeTrotter 380HSUPA PCIe */
#define	USB_PRODUCT_OPTION_GT3G_1		0x6050	/* 3G modem */
#define	USB_PRODUCT_OPTION_GT3G_2		0x6100	/* 3G modem */
#define	USB_PRODUCT_OPTION_GT3G_3		0x6150	/* 3G modem */
#define	USB_PRODUCT_OPTION_GT3G_4		0x6200	/* 3G modem */
#define	USB_PRODUCT_OPTION_GT3G_5		0x6250	/* 3G modem */
#define	USB_PRODUCT_OPTION_GT3G_6		0x6350	/* 3G modem */
#define	USB_PRODUCT_OPTION_E6500		0x6500	/* 3G modem */
#define	USB_PRODUCT_OPTION_E6501		0x6501	/* 3G modem */
#define	USB_PRODUCT_OPTION_E6601		0x6601	/* 3G modem */
#define	USB_PRODUCT_OPTION_E6721		0x6721	/* 3G modem */
#define	USB_PRODUCT_OPTION_E6741		0x6741	/* 3G modem */
#define	USB_PRODUCT_OPTION_E6761		0x6761	/* 3G modem */
#define	USB_PRODUCT_OPTION_E6800		0x6800	/* 3G modem */
#define	USB_PRODUCT_OPTION_E7021		0x7021	/* 3G modem */
#define	USB_PRODUCT_OPTION_E7041		0x7041	/* 3G modem */
#define	USB_PRODUCT_OPTION_E7061		0x7061	/* 3G modem */
#define	USB_PRODUCT_OPTION_E7100		0x7100	/* 3G modem */
#define	USB_PRODUCT_OPTION_GTM380		0x7201	/* 3G modem */
#define	USB_PRODUCT_OPTION_GE40X		0x7601	/* Globetrotter HSUPA */
#define	USB_PRODUCT_OPTION_GSICON72		0x6911	/* GlobeSurfer iCON */
#define	USB_PRODUCT_OPTION_GSICONHSUPA	0x7251	/* Globetrotter HSUPA */
#define	USB_PRODUCT_OPTION_ICON401		0x7401	/* GlobeSurfer iCON 401 */
#define	USB_PRODUCT_OPTION_GTHSUPA		0x7011	/* Globetrotter HSUPA */
#define	USB_PRODUCT_OPTION_GMT382		0x7501	/* Globetrotter HSUPA */
#define	USB_PRODUCT_OPTION_GE40X_1		0x7301	/* Globetrotter HSUPA */
#define	USB_PRODUCT_OPTION_GE40X_2		0x7361	/* Globetrotter HSUPA */
#define	USB_PRODUCT_OPTION_GE40X_3		0x7381	/* Globetrotter HSUPA */
#define	USB_PRODUCT_OPTION_GTM661W		0x9000	/* GTM661W */
#define	USB_PRODUCT_OPTION_ICONEDGE		0xc031	/* GlobeSurfer iCON EDGE */
#define	USB_PRODUCT_OPTION_MODHSXPA		0xd013	/* Globetrotter HSUPA */
#define	USB_PRODUCT_OPTION_ICON321		0xd031	/* Globetrotter HSUPA */
#define	USB_PRODUCT_OPTION_ICON505		0xd055	/* Globetrotter iCON 505 */
#define	USB_PRODUCT_OPTION_ICON452		0x7901	/* Globetrotter iCON 452 */

/* Optoelectronics Co., Ltd */
#define	USB_PRODUCT_OPTO_BARCODE		0x0001	/* Barcode Reader */
#define	USB_PRODUCT_OPTO_OPTICONCODE	0x0009	/* Opticon Code Reader */
#define	USB_PRODUCT_OPTO_BARCODE_1		0xa002	/* Barcode Reader */
#define	USB_PRODUCT_OPTO_CRD7734		0xc000	/* USB Cradle CRD-7734-RU */
#define	USB_PRODUCT_OPTO_CRD7734_1		0xc001	/* USB Cradle CRD-7734-RU */

/* OvisLink #define	USB_PRODUCT_*/
#define	USB_PRODUCT_OVISLINK_RT3072		0x3072	/* RT3072 */

/* OQO */
#define	USB_PRODUCT_OQO_WIFI01		0x0002	/* model 01 WiFi interface */
#define	USB_PRODUCT_OQO_BT01		0x0003	/* model 01 Bluetooth interface */
#define	USB_PRODUCT_OQO_ETHER01PLUS	0x7720	/* model 01+ Ethernet */
#define	USB_PRODUCT_OQO_ETHER01		0x8150	/* model 01 Ethernet interface */

/* Ours Technology Inc. */
#define	USB_PRODUCT_OTI_DKU5		0x6858	/* DKU-5 Serial */

/* Owen.ru products */
#define	USB_PRODUCT_OWEN_AC4		0x0004	/* AC4 USB-RS485 converter */

/* OWL producs */
#define	USB_PRODUCT_OWL_CM_160		0xca05	/* OWL CM-160 power monitor */

/* Palm Computing, Inc. #define	USB_PRODUCT_*/
#define	USB_PRODUCT_PALM_SERIAL		0x0080	/* USB Serial */
#define	USB_PRODUCT_PALM_M500		0x0001	/* Palm m500 */
#define	USB_PRODUCT_PALM_M505		0x0002	/* Palm m505 */
#define	USB_PRODUCT_PALM_M515		0x0003	/* Palm m515 */
#define	USB_PRODUCT_PALM_I705		0x0020	/* Palm i705 */
#define	USB_PRODUCT_PALM_TUNGSTEN_Z	0x0031	/* Palm Tungsten Z */
#define	USB_PRODUCT_PALM_M125		0x0040	/* Palm m125 */
#define	USB_PRODUCT_PALM_M130		0x0050	/* Palm m130 */
#define	USB_PRODUCT_PALM_TUNGSTEN_T	0x0060	/* Palm Tungsten T */
#define	USB_PRODUCT_PALM_ZIRE31		0x0061	/* Palm Zire 31 */
#define	USB_PRODUCT_PALM_ZIRE		0x0070	/* Palm Zire */

/* Panasonic products */
#define	USB_PRODUCT_PANASONIC_LS120CAM	0x0901	/* LS-120 Camera */
#define	USB_PRODUCT_PANASONIC_KXL840AN	0x0d01	/* CD-R Drive KXL-840AN */
#define	USB_PRODUCT_PANASONIC_KXLRW32AN	0x0d09	/* CD-R Drive KXL-RW32AN */
#define	USB_PRODUCT_PANASONIC_KXLCB20AN	0x0d0a	/* CD-R Drive KXL-CB20AN */
#define	USB_PRODUCT_PANASONIC_KXLCB35AN	0x0d0e	/* DVD-ROM & CD-R/RW */
#define	USB_PRODUCT_PANASONIC_SDCAAE	0x1b00	/* MultiMediaCard */
#define	USB_PRODUCT_PANASONIC_TYTP50P6S	0x3900	/* TY-TP50P6-S 50in Touch Panel */

/* Papouch products */
#define	USB_PRODUCT_PAPOUCH_AD4USB		0x8003	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_AP485		0x0101	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_AP485_2		0x0104	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_DRAK5		0x0700	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_DRAK6		0x1000	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_GMSR		0x8005	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_GMUX		0x8004	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_IRAMP		0x0500	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_LEC			0x0300	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_MU			0x8001	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_QUIDO10X1		0x0b00	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_QUIDO2X16		0x0e00	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_QUIDO2X2		0x0a00	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_QUIDO30X3		0x0c00	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_QUIDO3X32		0x0f00	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_QUIDO4X4		0x0900	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_QUIDO60X3		0x0d00	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_QUIDO8X8		0x0800	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_SB232		0x0301	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_SB422		0x0102	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_SB422_2		0x0105	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_SB485		0x0100	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_SB485C		0x0107	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_SB485S		0x0106	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_SB485_2		0x0103	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_SIMUKEY		0x8002	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_TMU			0x0400	/* FTDI compatible adapter */
#define	USB_PRODUCT_PAPOUCH_UPSUSB		0x8000	/* FTDI compatible adapter */

/* PARA Industrial products */
#define	USB_PRODUCT_PARA_RT3070			0x8888	/* RT3070 */

/* Simtec Electronics products */
#define	USB_PRODUCT_SIMTEC_ENTROPYKEY	0x0001	/* Entropy Key */

/* Pegatron products */
#define	USB_PRODUCT_PEGATRON_RT2870		0x0002	/* RT2870 */
#define	USB_PRODUCT_PEGATRON_RT3070		0x000c	/* RT3070 */
#define	USB_PRODUCT_PEGATRON_RT3070_2	0x000e	/* RT3070 */
#define	USB_PRODUCT_PEGATRON_RT3070_3	0x0010	/* RT3070 */

/* Peracom products */
#define	USB_PRODUCT_PERACOM_SERIAL1		0x0001	/* Serial */
#define	USB_PRODUCT_PERACOM_ENET		0x0002	/* Ethernet */
#define	USB_PRODUCT_PERACOM_ENET3		0x0003	/* At Home Ethernet */
#define	USB_PRODUCT_PERACOM_ENET2		0x0005	/* Ethernet */

/* Philips products */
#define	USB_PRODUCT_PHILIPS_DSS350		0x0101	/* DSS 350 Digital Speaker System */
#define	USB_PRODUCT_PHILIPS_DSS			0x0104	/* DSS XXX Digital Speaker System */
#define	USB_PRODUCT_PHILIPS_HUB			0x0201	/* hub */
#define	USB_PRODUCT_PHILIPS_PCA646VC	0x0303	/* PCA646VC PC Camera */
#define	USB_PRODUCT_PHILIPS_PCVC680K	0x0308	/* PCVC680K Vesta Pro PC Camera */
#define	USB_PRODUCT_PHILIPS_DSS150		0x0471	/* DSS 150 Digital Speaker System */
#define	USB_PRODUCT_PHILIPS_ACE1001		0x066a	/* AKTAKOM ACE-1001 cable */
#define	USB_PRODUCT_PHILIPS_SPE3030CC	0x083a	/* USB 2.0 External Disk */
#define	USB_PRODUCT_PHILIPS_SNU5600		0x1236	/* SNU5600 */
#define	USB_PRODUCT_PHILIPS_UM10016		0x1552	/* ISP 1581 Hi-Speed #define	USB_MPEG2 Encoder Reference Kit */
#define	USB_PRODUCT_PHILIPS_DIVAUSB		0x1801	/* DIVA USB mp3 player */
#define	USB_PRODUCT_PHILIPS_RT2870		0x200f	/* RT2870 */

/* Philips Semiconductor products */
#define	USB_PRODUCT_PHILIPSSEMI_HUB1122	0x1122	/* HUB */

/* Megatec */
#define	USB_PRODUCT_MEGATEC_UPS			0x5161	/* Phoenixtec protocol based UPS */

/* P.I. Engineering products */
#define	USB_PRODUCT_PIENGINEERING_PS2USB	0x020b	/* PS2 to Mac USB Adapter */

/* Planex Communications products */
#define	USB_PRODUCT_PLANEX_GW_US11H		0x14ea	/* GW-US11H WLAN */
#define	USB_PRODUCT_PLANEX2_RTL8188CUS	0x1201	/* RTL8188CUS */
#define	USB_PRODUCT_PLANEX2_GW_US11S	0x3220	/* GW-US11S WLAN */
#define	USB_PRODUCT_PLANEX2_GW_US54GXS	0x5303	/* GW-US54GXS WLAN */
#define	USB_PRODUCT_PLANEX2_GW_US300	0x5304	/* GW-US300 */
#define	USB_PRODUCT_PLANEX2_RTL8188CU_1	0xab2a	/* RTL8188CU */
#define	USB_PRODUCT_PLANEX2_RTL8188CU_2	0xed17	/* RTL8188CU */
#define	USB_PRODUCT_PLANEX2_RTL8188CU_3	0x4902	/* RTL8188CU */
#define	USB_PRODUCT_PLANEX2_RTL8188CU_4	0xab2e	/* RTL8188CU */
#define	USB_PRODUCT_PLANEX2_RTL8192CU	0xab2b	/* RTL8192CU */
#define	USB_PRODUCT_PLANEX2_GWUS54HP	0xab01	/* GW-US54HP */
#define	USB_PRODUCT_PLANEX2_GWUS300MINIS	0xab24	/* GW-US300MiniS */
#define	USB_PRODUCT_PLANEX2_RT3070		0xab25	/* RT3070 */
#define	USB_PRODUCT_PLANEX2_MZKUE150N	0xab2f	/* MZK-UE150N */
#define	USB_PRODUCT_PLANEX2_GWUS54MINI2	0xab50	/* GW-US54Mini2 */
#define	USB_PRODUCT_PLANEX2_GWUS54SG	0xc002	/* GW-US54SG */
#define	USB_PRODUCT_PLANEX2_GWUS54GZL	0xc007	/* GW-US54GZL */
#define	USB_PRODUCT_PLANEX2_GWUS54GD	0xed01	/* GW-US54GD */
#define	USB_PRODUCT_PLANEX2_GWUSMM		0xed02	/* GW-USMM */
#define	USB_PRODUCT_PLANEX2_RT2870		0xed06	/* RT2870 */
#define	USB_PRODUCT_PLANEX2_GWUSMICRON	0xed14	/* GW-USMicroN */
#define	USB_PRODUCT_PLANEX2_GWUSVALUEEZ	0xed17	/* GW-USValue-EZ */
#define	USB_PRODUCT_PLANEX3_GWUS54GZ	0xab10	/* GW-US54GZ */
#define	USB_PRODUCT_PLANEX3_GU1000T		0xab11	/* GU-1000T */
#define	USB_PRODUCT_PLANEX3_GWUS54MINI	0xab13	/* GW-US54Mini */
#define	USB_PRODUCT_PLANEX2_GWUSNANO	0xab28	/* GW-USNano */

/* Plextor Corp. */
#define	USB_PRODUCT_PLEXTOR_40_12_40U	0x0011	/* PlexWriter 40/12/40U */

/* Ploytec GmbH */
#define	USB_PRODUCT_PLOYTEC_SPL_CRIMSON_1			0xc150	/* SPL Crimson Revision 1 */
/* PLX products */
#define	USB_PRODUCT_PLX_TESTBOARD		0x9060	/* test board */
#define	USB_PRODUCT_PLX_CA42			0xac70	/* CA-42 */

/* PNY products */
#define	USB_PRODUCT_PNY_ATTACHE2		0x0010	/* #define	USB_2.0 Flash Drive */

/* PortGear products */
#define	USB_PRODUCT_PORTGEAR_EA8		0x0008	/* Ethernet */
#define	USB_PRODUCT_PORTGEAR_EA9		0x0009	/* Ethernet */

/* Portsmith products */
#define	USB_PRODUCT_PORTSMITH_EEA		0x3003	/* Express Ethernet */

/* Posiflex products */
#define	USB_PRODUCT_POSIFLEX_PP7000		0x0300	/* FTDI compatible adapter */

/* Primax products */
#define	USB_PRODUCT_PRIMAX_G2X300		0x0300	/* G2-200 scanner */
#define	USB_PRODUCT_PRIMAX_G2E300		0x0301	/* G2E-300 scanner */
#define	USB_PRODUCT_PRIMAX_G2300		0x0302	/* G2-300 scanner */
#define	USB_PRODUCT_PRIMAX_G2E3002		0x0303	/* G2E-300 scanner */
#define	USB_PRODUCT_PRIMAX_9600			0x0340	/* Colorado #define	USB_9600 scanner */
#define	USB_PRODUCT_PRIMAX_600U			0x0341	/* Colorado 600u scanner */
#define	USB_PRODUCT_PRIMAX_6200			0x0345	/* Visioneer 6200 scanner */
#define	USB_PRODUCT_PRIMAX_19200		0x0360	/* Colorado #define	USB_19200 scanner */
#define	USB_PRODUCT_PRIMAX_1200U		0x0361	/* Colorado 1200u scanner */
#define	USB_PRODUCT_PRIMAX_G600			0x0380	/* G2-600 scanner */
#define	USB_PRODUCT_PRIMAX_636I			0x0381	/* ReadyScan 636i */
#define	USB_PRODUCT_PRIMAX_G2600		0x0382	/* G2-600 scanner */
#define	USB_PRODUCT_PRIMAX_G2E600		0x0383	/* G2E-600 scanner */
#define	USB_PRODUCT_PRIMAX_COMFORT		0x4d01	/* Comfort */
#define	USB_PRODUCT_PRIMAX_MOUSEINABOX	0x4d02	/* Mouse-in-a-Box */
#define	USB_PRODUCT_PRIMAX_PCGAUMS1		0x4d04	/* Sony PCGA-UMS1 */
#define	USB_PRODUCT_PRIMAX_HP_RH304AA	0x4d17	/* HP RH304AA mouse */

/* Prolific products */
#define	USB_PRODUCT_PROLIFIC_PL2301		0x0000	/* PL2301 Host-Host interface */
#define	USB_PRODUCT_PROLIFIC_PL2302		0x0001	/* PL2302 Host-Host interface */
#define	USB_PRODUCT_PROLIFIC_MOTOROLA	0x0307	/* Motorola Cable */
#define	USB_PRODUCT_PROLIFIC_RSAQ2		0x04bb	/* PL2303 Serial (IODATA USB-RSAQ2) */
#define	USB_PRODUCT_PROLIFIC_ALLTRONIX_GPRS	0x0609	/* Alltronix ACM003U00 modem */
#define	USB_PRODUCT_PROLIFIC_ALDIGA_AL11U	0x0611	/* AlDiga AL-11U modem */
#define	USB_PRODUCT_PROLIFIC_MICROMAX_610U	0x0612	/* Micromax 610U */
#define	USB_PRODUCT_PROLIFIC_DCU11		0x1234	/* DCU-11 Phone Cable */
#define	USB_PRODUCT_PROLIFIC_UIC_MSR206	0x206a	/* UIC MSR206 Card Reader */
#define	USB_PRODUCT_PROLIFIC_PL2303		0x2303	/* PL2303 Serial (ATEN/IOGEAR UC232A) */
#define	USB_PRODUCT_PROLIFIC_PL2305		0x2305	/* Parallel printer */
#define	USB_PRODUCT_PROLIFIC_ATAPI4		0x2307	/* ATAPI-4 Controller */
#define	USB_PRODUCT_PROLIFIC_PL2501		0x2501	/* PL2501 Host-Host interface */
#define	USB_PRODUCT_PROLIFIC_PL2506		0x2506	/* PL2506 USB to IDE Bridge */
#define	USB_PRODUCT_PROLIFIC_PL27A1		0x27A1	/* PL27A1 USB 3.0 Host-Host interface */
#define	USB_PRODUCT_PROLIFIC_HCR331		0x331a	/* HCR331 Hybrid Card Reader */
#define	USB_PRODUCT_PROLIFIC_PHAROS		0xaaa0	/* Prolific Pharos */
#define	USB_PRODUCT_PROLIFIC_RSAQ3		0xaaa2	/* PL2303 Serial Adapter (IODATA USB-RSAQ3) */
#define	USB_PRODUCT_PROLIFIC2_PL2303	0x2303	/* PL2303 Serial Adapter */

/* Putercom products */
#define	USB_PRODUCT_PUTERCOM_UPA100		0x047e	/* USB-1284 BRIDGE */

/* Qcom products */
#define	USB_PRODUCT_QCOM_RT2573		0x6196	/* RT2573 */
#define	USB_PRODUCT_QCOM_RT2573_2	0x6229	/* RT2573 */
#define	USB_PRODUCT_QCOM_RT2573_3	0x6238	/* RT2573 */
#define	USB_PRODUCT_QCOM_RT2870		0x6259	/* RT2870 */

/* QI-hardware */
#define	USB_PRODUCT_QIHARDWARE_JTAGSERIAL		0x0713	/* FTDI compatible adapter */

/* Qisda products */
#define	USB_PRODUCT_QISDA_H21_1		0x4512	/* 3G modem */
#define	USB_PRODUCT_QISDA_H21_2		0x4523	/* 3G modem */
#define	USB_PRODUCT_QISDA_H20_1		0x4515	/* 3G modem */
#define	USB_PRODUCT_QISDA_H20_2		0x4519	/* 3G modem */

/* Qualcomm products */
#define	USB_PRODUCT_QUALCOMM_CDMA_MSM			0x6000	/* CDMA Technologies MSM phone */
#define	USB_PRODUCT_QUALCOMM_NTT_L02C_MODEM		0x618f	/* NTT DOCOMO L-02C */
#define	USB_PRODUCT_QUALCOMM_NTT_L02C_STORAGE	0x61dd	/* NTT DOCOMO L-02C */
#define	USB_PRODUCT_QUALCOMM2_MF330			0x6613	/* MF330 */
#define	USB_PRODUCT_QUALCOMM2_RWT_FCT		0x3100	/* RWT FCT-CDMA 2000 1xRTT modem */
#define	USB_PRODUCT_QUALCOMM2_CDMA_MSM		0x3196	/* CDMA Technologies MSM modem */
#define	USB_PRODUCT_QUALCOMM2_AC8700		0x6000	/* AC8700 */
#define	USB_PRODUCT_QUALCOMM2_VW110L		0x1000	/* Vertex Wireless 110L modem */
#define	USB_PRODUCT_QUALCOMM2_SIM5218		0x9000	/* SIM5218 */
#define	USB_PRODUCT_QUALCOMM2_WM620			0x9002	/* Neoway WM620 */
#define	USB_PRODUCT_QUALCOMM2_GOBI2000_QDL	0x9204	/* Qualcomm Gobi 2000 QDL */
#define	USB_PRODUCT_QUALCOMM2_GOBI2000		0x9205	/* Qualcomm Gobi 2000 modem */
#define	USB_PRODUCT_QUALCOMM2_VT80N			0x6500	/* Venus VT80N */
#define	USB_PRODUCT_QUALCOMM3_VFAST2		0x9909	/* Venus Fast2 modem */
#define	USB_PRODUCT_QUALCOMMINC_CDMA_MSM	0x0001	/* CDMA Technologies MSM modem */
#define	USB_PRODUCT_QUALCOMMINC_E0002	0x0002	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0003	0x0003	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0004	0x0004	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0005	0x0005	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0006	0x0006	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0007	0x0007	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0008	0x0008	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0009	0x0009	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E000A	0x000a	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E000B	0x000b	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E000C	0x000c	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E000D	0x000d	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E000E	0x000e	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E000F	0x000f	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0010	0x0010	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0011	0x0011	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0012	0x0012	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0013	0x0013	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0014	0x0014	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_MF628	0x0015	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_MF633R	0x0016	/* ZTE WCDMA modem */
#define	USB_PRODUCT_QUALCOMMINC_E0017	0x0017	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0018	0x0018	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0019	0x0019	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0020	0x0020	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0021	0x0021	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0022	0x0022	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0023	0x0023	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0024	0x0024	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0025	0x0025	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0026	0x0026	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0027	0x0027	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0028	0x0028	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0029	0x0029	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0030	0x0030	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_MF626	0x0031	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0032	0x0032	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0033	0x0033	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0037	0x0037	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0039	0x0039	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0042	0x0042	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0043	0x0043	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0048	0x0048	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0049	0x0049	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0051	0x0051	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0052	0x0052	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_ZTE_STOR2	0x0053	/* USB ZTE Storage */
#define	USB_PRODUCT_QUALCOMMINC_E0054	0x0054	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0055	0x0055	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0057	0x0057	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0058	0x0058	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0059	0x0059	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0060	0x0060	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0061	0x0061	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0062	0x0062	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0063	0x0063	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0064	0x0064	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0066	0x0066	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0069	0x0069	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0070	0x0070	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0073	0x0073	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0076	0x0076	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0078	0x0078	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0082	0x0082	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E0086	0x0086	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_MF112	0x0103	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_SURFSTICK		0x0117	/* 1&1 Surf Stick */
#define	USB_PRODUCT_QUALCOMMINC_K3772_Z_INIT	0x1179	/* K3772-Z Initial */
#define	USB_PRODUCT_QUALCOMMINC_K3772_Z			0x1181	/* K3772-Z */
#define	USB_PRODUCT_QUALCOMMINC_ZTE_MF730M		0x1420	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_MF195E_INIT		0x1514	/* MF195E initial */
#define	USB_PRODUCT_QUALCOMMINC_MF195E			0x1516	/* MF195E */
#define	USB_PRODUCT_QUALCOMMINC_ZTE_STOR		0x2000	/* USB ZTE Storage */
#define	USB_PRODUCT_QUALCOMMINC_E2002			0x2002	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_E2003			0x2003	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_AC682			0xffdd	/* CDMA 1xEVDO USB modem */
#define	USB_PRODUCT_QUALCOMMINC_AC682_INIT		0xffde	/* CDMA 1xEVDO USB modem (initial) */
#define	USB_PRODUCT_QUALCOMMINC_AC8710			0xfff1	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_AC2726			0xfff5	/* 3G modem */
#define	USB_PRODUCT_QUALCOMMINC_AC8700			0xfffe	/* CDMA 1xEVDO USB modem */

/* Quanta products */
#define	USB_PRODUCT_QUANTA_RW6815_1		0x00ce	/* HP iPAQ rw6815 */
#define	USB_PRODUCT_QUANTA_RT3070		0x0304	/* RT3070 */
#define	USB_PRODUCT_QUANTA_Q101_STOR	0x1000	/* USB Q101 Storage */
#define	USB_PRODUCT_QUANTA_Q101			0xea02	/* HSDPA modem */
#define	USB_PRODUCT_QUANTA_Q111			0xea03	/* HSDPA modem */
#define	USB_PRODUCT_QUANTA_GLX			0xea04	/* HSDPA modem */
#define	USB_PRODUCT_QUANTA_GKE			0xea05	/* HSDPA modem */
#define	USB_PRODUCT_QUANTA_GLE			0xea06	/* HSDPA modem */
#define	USB_PRODUCT_QUANTA_RW6815R		0xf003	/* HP iPAQ rw6815 RNDIS */

/* Quectel products */
#define	USB_PRODUCT_QUECTEL_EC25		0x0125	/* LTE modem */
#define	USB_PRODUCT_QUECTEL_EC200T		0x6026	/* LTE_modem */

/* Quickshot products */
#define	USB_PRODUCT_QUICKSHOT_STRIKEPAD	0x6238	/* USB StrikePad */

/* Qtronix products */
#define	USB_PRODUCT_QTRONIX_980N		0x2011	/* Scorpion-980N keyboard */

/* Radio Shack */
#define	USB_PRODUCT_RADIOSHACK_USBCABLE	0x4026	/* USB to Serial Cable */

/* Rainbow Technologies products */
#define	USB_PRODUCT_RAINBOW_IKEY2000	0x1200	/* i-Key 2000 */

/* Ralink Technology products */
#define	USB_PRODUCT_RALINK_RT2570		0x1706	/* RT2500 USB Wireless Adapter */
#define	USB_PRODUCT_RALINK_RT2070		0x2070	/* RT2070 */
#define	USB_PRODUCT_RALINK_RT2570_2		0x2570	/* RT2500 USB Wireless Adapter */
#define	USB_PRODUCT_RALINK_RT2573		0x2573	/* RT2501 USB Wireless Adapter */
#define	USB_PRODUCT_RALINK_RT2671		0x2671	/* RT2601 USB Wireless Adapter */
#define	USB_PRODUCT_RALINK_RT2770		0x2770	/* RT2770 */
#define	USB_PRODUCT_RALINK_RT2870		0x2870	/* RT2870 */
#define	USB_PRODUCT_RALINK_RT_STOR		0x2878	/* USB Storage */
#define	USB_PRODUCT_RALINK_RT3070		0x3070	/* RT3070 */
#define	USB_PRODUCT_RALINK_RT3071		0x3071	/* RT3071 */
#define	USB_PRODUCT_RALINK_RT3072		0x3072	/* RT3072 */
#define	USB_PRODUCT_RALINK_RT3370		0x3370	/* RT3370 */
#define	USB_PRODUCT_RALINK_RT3572		0x3572	/* RT3572 */
#define	USB_PRODUCT_RALINK_RT3573		0x3573	/* RT3573 */
#define	USB_PRODUCT_RALINK_RT5370		0x5370	/* RT5370 */
#define	USB_PRODUCT_RALINK_RT5572		0x5572	/* RT5572 */
#define	USB_PRODUCT_RALINK_RT8070		0x8070	/* RT8070 */
#define	USB_PRODUCT_RALINK_RT2570_3		0x9020	/* RT2500 USB Wireless Adapter */
#define	USB_PRODUCT_RALINK_RT2573_2		0x9021	/* RT2501 USB Wireless Adapter */

/* RATOC Systems products */
#define	USB_PRODUCT_RATOC_REXUSB60		0xb000	/* USB serial adapter REX-USB60 */
#define	USB_PRODUCT_RATOC_REXUSB60F		0xb020	/* USB serial adapter REX-USB60F */

/* Realtek products */
/* Green House and CompUSA OEM this part */
#define	USB_PRODUCT_REALTEK_DUMMY		0x0000	/* Dummy product */
#define	USB_PRODUCT_REALTEK_USB20CRW	0x0158	/* USB20CRW Card Reader */
#define	USB_PRODUCT_REALTEK_RTL8188ETV	0x0179	/* RTL8188ETV */
#define	USB_PRODUCT_REALTEK_RTL8188CTV	0x018a	/* RTL8188CTV */
#define	USB_PRODUCT_REALTEK_USBKR100	0x8150	/* USBKR100 USB Ethernet */
#define	USB_PRODUCT_REALTEK_RTL8152		0x8152	/* RTL8152 USB Ethernet */
#define	USB_PRODUCT_REALTEK_RTL8153		0x8153	/* RTL8153 USB Ethernet */
#define	USB_PRODUCT_REALTEK_RTL8188CE_0	0x8170	/* RTL8188CE */
#define	USB_PRODUCT_REALTEK_RTL8171		0x8171	/* RTL8171 */
#define	USB_PRODUCT_REALTEK_RTL8172		0x8172	/* RTL8172 */
#define	USB_PRODUCT_REALTEK_RTL8173		0x8173	/* RTL8173 */
#define	USB_PRODUCT_REALTEK_RTL8174		0x8174	/* RTL8174 */
#define	USB_PRODUCT_REALTEK_RTL8188CU_0	0x8176	/* RTL8188CU */
#define	USB_PRODUCT_REALTEK_RTL8188EU	0x8179	/* RTL8188EU */
#define	USB_PRODUCT_REALTEK_RTL8188CE_1	0x817e	/* RTL8188CE */
#define	USB_PRODUCT_REALTEK_RTL8188CU_1	0x817a	/* RTL8188CU */
#define	USB_PRODUCT_REALTEK_RTL8188CU_2	0x817b	/* RTL8188CU */
#define	USB_PRODUCT_REALTEK_RTL8187		0x8187	/* RTL8187 Wireless Adapter */
#define	USB_PRODUCT_REALTEK_RTL8187B_0	0x8189	/* RTL8187B Wireless Adapter */
#define	USB_PRODUCT_REALTEK_RTL8188CU_3	0x8191	/* RTL8188CU */
#define	USB_PRODUCT_REALTEK_RTL8196EU	0x8196	/* RTL8196EU */
#define	USB_PRODUCT_REALTEK_RTL8187B_1	0x8197	/* RTL8187B Wireless Adapter */
#define	USB_PRODUCT_REALTEK_RTL8187B_2	0x8198	/* RTL8187B Wireless Adapter */
#define	USB_PRODUCT_REALTEK_RTL8188CUS	0x818a	/* RTL8188CUS */
#define	USB_PRODUCT_REALTEK_RTL8188CU_COMBO	0x8754	/* RTL8188CU */
#define	USB_PRODUCT_REALTEK_RTL8191CU	0x8177	/* RTL8191CU */
#define	USB_PRODUCT_REALTEK_RTL8192CU	0x8178	/* RTL8192CU */
#define	USB_PRODUCT_REALTEK_RTL8192CE	0x817c	/* RTL8192CE */
#define	USB_PRODUCT_REALTEK_RTL8188RU_1	0x817d	/* RTL8188RU */
#define	USB_PRODUCT_REALTEK_RTL8188RU_3	0x817f	/* RTL8188RU */
#define	USB_PRODUCT_REALTEK_RTL8712		0x8712	/* RTL8712 */
#define	USB_PRODUCT_REALTEK_RTL8713		0x8712	/* RTL8713 */
#define	USB_PRODUCT_REALTEK_RTL8188RU_2	0x317f	/* RTL8188RU */
#define	USB_PRODUCT_REALTEK_RTL8192SU	0xc512	/* RTL8192SU */

/* RedOctane products */
#define	USB_PRODUCT_REDOCTANE_DUMMY		0x0000	/* Dummy product */
#define	USB_PRODUCT_REDOCTANE_GHMIDI	0x474b	/* GH MIDI INTERFACE */

/* Renesas products */
#define	USB_PRODUCT_RENESAS_RX610		0x0053	/* RX610 RX-Stick */

/* Ricoh products */
#define	USB_PRODUCT_RICOH_VGPVCC2		0x1830	/* VGP-VCC2 Camera */
#define	USB_PRODUCT_RICOH_VGPVCC3		0x1832	/* VGP-VCC3 Camera */
#define	USB_PRODUCT_RICOH_VGPVCC2_2		0x1833	/* VGP-VCC2 Camera */
#define	USB_PRODUCT_RICOH_VGPVCC2_3		0x1834	/* VGP-VCC2 Camera */
#define	USB_PRODUCT_RICOH_VGPVCC5		0x1835	/* VGP-VCC5 Camera */
#define	USB_PRODUCT_RICOH_VGPVCC4		0x1836	/* VGP-VCC4 Camera */
#define	USB_PRODUCT_RICOH_VGPVCC4_2		0x1837	/* VGP-VCC4 Camera */
#define	USB_PRODUCT_RICOH_VGPVCC6		0x1839	/* VGP-VCC6 Camera */
#define	USB_PRODUCT_RICOH_VGPVCC7		0x183a	/* VGP-VCC7 Camera */
#define	USB_PRODUCT_RICOH_VGPVCC8		0x183b	/* VGP-VCC8 Camera */
#define	USB_PRODUCT_RICOH_VGPVCC9		0x183e	 /* VGP-VCC9 Camera */

/* Reiner-SCT products */
#define	USB_PRODUCT_REINERSCT_CYBERJACK_ECOM	0x0100	/* e-com cyberJack */

/* Roland products */
#define	USB_PRODUCT_ROLAND_UA100		0x0000	/* UA-100 Audio I/F */
#define	USB_PRODUCT_ROLAND_UM4			0x0002	/* UM-4 MIDI I/F */
#define	USB_PRODUCT_ROLAND_SC8850		0x0003	/* SC-8850 MIDI Synth */
#define	USB_PRODUCT_ROLAND_U8			0x0004	/* U-8 Audio I/F */
#define	USB_PRODUCT_ROLAND_UM2			0x0005	/* UM-2 MIDI I/F */
#define	USB_PRODUCT_ROLAND_SC8820		0x0007	/* SC-8820 MIDI Synth */
#define	USB_PRODUCT_ROLAND_PC300		0x0008	/* PC-300 MIDI Keyboard */
#define	USB_PRODUCT_ROLAND_UM1			0x0009	/* UM-1 MIDI I/F */
#define	USB_PRODUCT_ROLAND_SK500		0x000b	/* SK-500 MIDI Keyboard */
#define	USB_PRODUCT_ROLAND_SCD70		0x000c	/* SC-D70 MIDI Synth */
#define	USB_PRODUCT_ROLAND_UM880N		0x0014	/* EDIROL UM-880 MIDI I/F (native) */
#define	USB_PRODUCT_ROLAND_UM880G		0x0015	/* EDIROL UM-880 MIDI I/F (generic) */
#define	USB_PRODUCT_ROLAND_SD90			0x0016	/* SD-90 MIDI Synth */
#define	USB_PRODUCT_ROLAND_UM550		0x0023	/* UM-550 MIDI I/F */
#define	USB_PRODUCT_ROLAND_SD20			0x0027	/* SD-20 MIDI Synth */
#define	USB_PRODUCT_ROLAND_SD80			0x0029	/* SD-80 MIDI Synth */
#define	USB_PRODUCT_ROLAND_UA700		0x002b	/* UA-700 Audio I/F */
#define	USB_PRODUCT_ROLAND_PCR300		0x0033	/* EDIROL PCR-300 MIDI I/F */
#define	USB_PRODUCT_ROLAND_UA25EX_AD	0x00e6	/* EDIROL UA-25EX (Advanced Driver) */
#define	USB_PRODUCT_ROLAND_UA25EX_CC	0x00e7	/* EDIROL UA-25EX (Class Compliant) */

/* Rockfire products */
#define	USB_PRODUCT_ROCKFIRE_GAMEPAD	0x2033	/* gamepad 203USB */

/* RATOC Systems products */
#define	USB_PRODUCT_RATOC_REXUSB60		0xb000	/* REX-USB60 */
#define	USB_PRODUCT_RATOC_REXUSB60F		0xb020	/* REX-USB60F */

/* RT system products */
#define	USB_PRODUCT_RTSYSTEMS_CT29B			0x9e54	/* FTDI compatible adapter */
#define	USB_PRODUCT_RTSYSTEMS_SERIAL_VX7	0x9e52	/* FTDI compatible adapter */

/* Sagem products */
#define	USB_PRODUCT_SAGEM_USBSERIAL		0x0027	/* USB-Serial Controller */
#define	USB_PRODUCT_SAGEM_XG760A		0x004a	/* XG-760A */
#define	USB_PRODUCT_SAGEM_XG76NA		0x0062	/* XG-76NA */

/* Samsung products */
#define	USB_PRODUCT_SAMSUNG_WIS09ABGN	0x2018	/* WIS09ABGN Wireless LAN adapter */
#define	USB_PRODUCT_SAMSUNG_ML6060		0x3008	/* ML-6060 laser printer */
#define	USB_PRODUCT_SAMSUNG_YP_U2		0x5050	/* YP-U2 MP3 Player */
#define	USB_PRODUCT_SAMSUNG_YP_U4		0x5092	/* YP-U4 MP3 Player */
#define	USB_PRODUCT_SAMSUNG_I500		0x6601	/* I500 Palm USB Phone */
#define	USB_PRODUCT_SAMSUNG_I330		0x8001	/* I330 phone cradle */
#define	USB_PRODUCT_SAMSUNG2_RT2870_1	0x2018	/* RT2870 */

/* Samsung Techwin products */
#define	USB_PRODUCT_SAMSUNG_TECHWIN_DIGIMAX_410	0x000a	/* Digimax 410 */

/* SanDisk products */
#define	USB_PRODUCT_SANDISK_SDDR05A		0x0001	/* ImageMate SDDR-05a */
#define	USB_PRODUCT_SANDISK_SDDR31		0x0002	/* ImageMate SDDR-31 */
#define	USB_PRODUCT_SANDISK_SDDR05		0x0005	/* ImageMate SDDR-05 */
#define	USB_PRODUCT_SANDISK_SDDR12		0x0100	/* ImageMate SDDR-12 */
#define	USB_PRODUCT_SANDISK_SDDR09		0x0200	/* ImageMate SDDR-09 */
#define	USB_PRODUCT_SANDISK_SDDR75		0x0810	/* ImageMate SDDR-75 */
#define	USB_PRODUCT_SANDISK_SDCZ2_128	0x7100	/* Cruzer Mini 128MB */
#define	USB_PRODUCT_SANDISK_SDCZ2_256	0x7104	/* Cruzer Mini 256MB */
#define	USB_PRODUCT_SANDISK_SDCZ4_128	0x7112	/* Cruzer Micro 128MB */
#define	USB_PRODUCT_SANDISK_SDCZ4_256	0x7113	/* Cruzer Micro 256MB */
#define	USB_PRODUCT_SANDISK_SDCZ48_32	0x5581	/* Ultra 32GB */
#define	USB_PRODUCT_SANDISK_IMAGEMATE_SDDR289	0xb6ba	/* ImageMate SDDR-289 */

/* Sanwa Electric Instrument Co., Ltd. products */
#define	USB_PRODUCT_SANWA_KB_USB2		0x0701	/* KB-USB2 multimeter cable */

/* Sanyo Electric products */
#define	USB_PRODUCT_SANYO_SCP4900		0x0701	/* Sanyo SCP-4900 USB Phone */

/* ScanLogic products */
#define	USB_PRODUCT_SCANLOGIC_SL11R		0x0002	/* SL11R IDE Adapter */
#define	USB_PRODUCT_SCANLOGIC_336CX		0x0300	/* Phantom 336CX - C3 scanner */

/* Schweitzer Engineering Laboratories products */
#define	USB_PRODUCT_SEL_C662			0x0001	/* C662 Cable */

/* Sealevel products */
#define	USB_PRODUCT_SEALEVEL_2101		0x2101	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2102		0x2102	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2103		0x2103	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2104		0x2104	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2106		0x9020	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2201_1		0x2211	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2201_2		0x2221	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2202_1		0x2212	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2202_2		0x2222	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2203_1		0x2213	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2203_2		0x2223	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2401_1		0x2411	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2401_2		0x2421	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2401_3		0x2431	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2401_4		0x2441	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2402_1		0x2412	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2402_2		0x2422	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2402_3		0x2432	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2402_4		0x2442	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2403_1		0x2413	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2403_2		0x2423	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2403_3		0x2433	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2403_4		0x2443	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2801_1		0x2811	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2801_2		0x2821	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2801_3		0x2831	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2801_4		0x2841	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2801_5		0x2851	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2801_6		0x2861	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2801_7		0x2871	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2801_8		0x2881	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2802_1		0x2812	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2802_2		0x2822	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2802_3		0x2832	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2802_4		0x2842	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2802_5		0x2852	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2802_6		0x2862	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2802_7		0x2872	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2802_8		0x2882	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2803_1		0x2813	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2803_2		0x2823	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2803_3		0x2833	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2803_4		0x2843	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2803_5		0x2853	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2803_6		0x2863	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2803_7		0x2873	/* FTDI compatible adapter */
#define	USB_PRODUCT_SEALEVEL_2803_8		0x2883	/* FTDI compatible adapter */

/* Senao products */
#define	USB_PRODUCT_SENAO_RT2870_3		0x0605	/* RT2870 */
#define	USB_PRODUCT_SENAO_RT2870_4		0x0615	/* RT2870 */
#define	USB_PRODUCT_SENAO_NUB8301		0x2000	/* NUB-8301 */
#define	USB_PRODUCT_SENAO_RT2870_1		0x9701	/* RT2870 */
#define	USB_PRODUCT_SENAO_RT2870_2		0x9702	/* RT2870 */
#define	USB_PRODUCT_SENAO_RT3070		0x9703	/* RT3070 */
#define	USB_PRODUCT_SENAO_RT3071		0x9705	/* RT3071 */
#define	USB_PRODUCT_SENAO_RT3072_1		0x9706	/* RT3072 */
#define	USB_PRODUCT_SENAO_RT3072_2		0x9707	/* RT3072 */
#define	USB_PRODUCT_SENAO_RT3072_3		0x9708	/* RT3072 */
#define	USB_PRODUCT_SENAO_RT3072_4		0x9709	/* RT3072 */
#define	USB_PRODUCT_SENAO_RT3072_5		0x9801	/* RT3072 */
#define	USB_PRODUCT_SENAO_RTL8192SU_1	0x9603	/* RTL8192SU */
#define	USB_PRODUCT_SENAO_RTL8192SU_2	0x9605	/* RTL8192SU */

/* ShanTou products */
#define	USB_PRODUCT_SHANTOU_ST268		0x0268	/* ST268 */
#define	USB_PRODUCT_SHANTOU_DM9601		0x9601	/* DM 9601 */
#define	USB_PRODUCT_SHANTOU_ADM8515		0x8515	/* ADM8515 */

/* Shark products */
#define	USB_PRODUCT_SHARK_PA			0x0400	/* Pocket Adapter */

/* Sharp products */
#define	USB_PRODUCT_SHARP_SL5500		0x8004	/* Zaurus SL-5500 PDA */
#define	USB_PRODUCT_SHARP_SLA300		0x8005	/* Zaurus SL-A300 PDA */
#define	USB_PRODUCT_SHARP_SL5600		0x8006	/* Zaurus SL-5600 PDA */
#define	USB_PRODUCT_SHARP_SLC700		0x8007	/* Zaurus SL-C700 PDA */
#define	USB_PRODUCT_SHARP_SLC750		0x9031	/* Zaurus SL-C750 PDA */
#define	USB_PRODUCT_SHARP_WZERO3ES		0x9123	/* W-ZERO3 ES Smartphone */
#define	USB_PRODUCT_SHARP_WZERO3ADES	0x91ac	/* Advanced W-ZERO3 ES Smartphone */
#define	USB_PRODUCT_SHARP_WILLCOM03		0x9242	/* WILLCOM03 */

/* Shuttle Technology products */
#define	USB_PRODUCT_SHUTTLE_EUSB		0x0001	/* E-USB Bridge */
#define	USB_PRODUCT_SHUTTLE_EUSCSI		0x0002	/* eUSCSI Bridge */
#define	USB_PRODUCT_SHUTTLE_SDDR09		0x0003	/* ImageMate SDDR09 */
#define	USB_PRODUCT_SHUTTLE_EUSBCFSM	0x0005	/* eUSB SmartMedia / CompactFlash Adapter */
#define	USB_PRODUCT_SHUTTLE_ZIOMMC		0x0006	/* eUSB MultiMediaCard Adapter */
#define	USB_PRODUCT_SHUTTLE_HIFD		0x0007	/* Sony Hifd */
#define	USB_PRODUCT_SHUTTLE_EUSBATAPI	0x0009	/* eUSB ATA/ATAPI Adapter */
#define	USB_PRODUCT_SHUTTLE_CF			0x000a	/* eUSB CompactFlash Adapter */
#define	USB_PRODUCT_SHUTTLE_EUSCSI_B	0x000b	/* eUSCSI Bridge */
#define	USB_PRODUCT_SHUTTLE_EUSCSI_C	0x000c	/* eUSCSI Bridge */
#define	USB_PRODUCT_SHUTTLE_CDRW		0x0101	/* CD-RW Device */
#define	USB_PRODUCT_SHUTTLE_EUSBORCA	0x0325	/* eUSB ORCA Quad Reader */

/* Siemens products */
#define	USB_PRODUCT_SIEMENS_SPEEDSTREAM		0x1001	/* SpeedStream */
#define	USB_PRODUCT_SIEMENS_SPEEDSTREAM22	0x1022	/* SpeedStream 1022 */
#define	USB_PRODUCT_SIEMENS2_WLL013		0x001b	/* WLL013 */
#define	USB_PRODUCT_SIEMENS2_ES75		0x0034	/* GSM module MC35 */
#define	USB_PRODUCT_SIEMENS2_WL54G		0x3c06	/* 54g USB Network Adapter */
#define	USB_PRODUCT_SIEMENS3_SX1		0x0001	/* SX1 */
#define	USB_PRODUCT_SIEMENS3_X65		0x0003	/* X65 */
#define	USB_PRODUCT_SIEMENS3_X75		0x0004	/* X75 */
#define	USB_PRODUCT_SIEMENS3_EF81		0x0005	/* EF81 */

/* Sierra Wireless products */
#define	USB_PRODUCT_SIERRA_EM5625		0x0017	/* EM5625 */
#define	USB_PRODUCT_SIERRA_MC5720_2		0x0018	/* MC5720 */
#define	USB_PRODUCT_SIERRA_MC5725		0x0020	/* MC5725 */
#define	USB_PRODUCT_SIERRA_AIRCARD580	0x0112	/* Sierra Wireless AirCard 580 */
#define	USB_PRODUCT_SIERRA_AIRCARD595	0x0019	/* Sierra Wireless AirCard 595 */
#define	USB_PRODUCT_SIERRA_AC595U		0x0120	/* Sierra Wireless AirCard 595U */
#define	USB_PRODUCT_SIERRA_AC597E		0x0021	/* Sierra Wireless AirCard 597E */
#define	USB_PRODUCT_SIERRA_EM5725		0x0022	/* EM5725 */
#define	USB_PRODUCT_SIERRA_C597			0x0023	/* Sierra Wireless Compass 597 */
#define	USB_PRODUCT_SIERRA_MC5727		0x0024	/* MC5727 */
#define	USB_PRODUCT_SIERRA_T598			0x0025	/* T598 */
#define	USB_PRODUCT_SIERRA_T11			0x0026	/* T11 */
#define	USB_PRODUCT_SIERRA_AC402		0x0027	/* AC402 */
#define	USB_PRODUCT_SIERRA_MC5728		0x0028	/* MC5728 */
#define	USB_PRODUCT_SIERRA_E0029		0x0029	/* E0029 */
#define	USB_PRODUCT_SIERRA_AIRCARD580	0x0112	/* Sierra Wireless AirCard 580 */
#define	USB_PRODUCT_SIERRA_AC595U		0x0120	/* Sierra Wireless AirCard 595U */
#define	USB_PRODUCT_SIERRA_MC5720		0x0218	/* MC5720 Wireless Modem */
#define	USB_PRODUCT_SIERRA_MINI5725		0x0220	/* Sierra Wireless miniPCI 5275 */
#define	USB_PRODUCT_SIERRA_MC5727_2		0x0224	/* MC5727 */
#define	USB_PRODUCT_SIERRA_MC8755_2		0x6802	/* MC8755 */
#define	USB_PRODUCT_SIERRA_MC8765		0x6803	/* MC8765 */
#define	USB_PRODUCT_SIERRA_MC8755		0x6804	/* MC8755 */
#define	USB_PRODUCT_SIERRA_MC8765_2		0x6805	/* MC8765 */
#define	USB_PRODUCT_SIERRA_MC8755_4		0x6808	/* MC8755 */
#define	USB_PRODUCT_SIERRA_MC8765_3		0x6809	/* MC8765 */
#define	USB_PRODUCT_SIERRA_AC875U		0x6812	/* AC875U HSDPA #define	USB_Modem */
#define	USB_PRODUCT_SIERRA_MC8755_3		0x6813	/* MC8755 HSDPA */
#define	USB_PRODUCT_SIERRA_MC8775_2		0x6815	/* MC8775 */
#define	USB_PRODUCT_SIERRA_MC8775		0x6816	/* MC8775 */
#define	USB_PRODUCT_SIERRA_AC875		0x6820	/* Sierra Wireless AirCard 875 */
#define	USB_PRODUCT_SIERRA_AC875U_2		0x6821	/* AC875U */
#define	USB_PRODUCT_SIERRA_AC875E		0x6822	/* AC875E */
#define	USB_PRODUCT_SIERRA_MC8780		0x6832	/* MC8780 */
#define	USB_PRODUCT_SIERRA_MC8781		0x6833	/* MC8781 */
#define	USB_PRODUCT_SIERRA_MC8780_2		0x6834	/* MC8780 */
#define	USB_PRODUCT_SIERRA_MC8781_2		0x6835	/* MC8781 */
#define	USB_PRODUCT_SIERRA_MC8780_3		0x6838	/* MC8780 */
#define	USB_PRODUCT_SIERRA_MC8781_3		0x6839	/* MC8781 */
#define	USB_PRODUCT_SIERRA_MC8785		0x683A	/* MC8785 */
#define	USB_PRODUCT_SIERRA_MC8785_2		0x683B	/* MC8785 */
#define	USB_PRODUCT_SIERRA_MC8790		0x683C	/* MC8790 */
#define	USB_PRODUCT_SIERRA_MC8791		0x683D	/* MC8791 */
#define	USB_PRODUCT_SIERRA_MC8792		0x683E	/* MC8792 */
#define	USB_PRODUCT_SIERRA_AC880		0x6850	/* Sierra Wireless AirCard 880 */
#define	USB_PRODUCT_SIERRA_AC881		0x6851	/* Sierra Wireless AirCard 881 */
#define	USB_PRODUCT_SIERRA_AC880E		0x6852	/* Sierra Wireless AirCard 880E */
#define	USB_PRODUCT_SIERRA_AC881E		0x6853	/* Sierra Wireless AirCard 881E */
#define	USB_PRODUCT_SIERRA_AC880U		0x6855	/* Sierra Wireless AirCard 880U */
#define	USB_PRODUCT_SIERRA_AC881U		0x6856	/* Sierra Wireless AirCard 881U */
#define	USB_PRODUCT_SIERRA_AC885E		0x6859	/* AC885E */
#define	USB_PRODUCT_SIERRA_AC885E_2		0x685A	/* AC885E */
#define	USB_PRODUCT_SIERRA_AC885U		0x6880	/* Sierra Wireless AirCard 885U */
#define	USB_PRODUCT_SIERRA_C888			0x6890	/* C888 */
#define	USB_PRODUCT_SIERRA_C22			0x6891	/* C22 */
#define	USB_PRODUCT_SIERRA_E6892		0x6892	/* E6892 */
#define	USB_PRODUCT_SIERRA_E6893		0x6893	/* E6893 */
#define	USB_PRODUCT_SIERRA_MC8700		0x68A3	/* MC8700 */
#define	USB_PRODUCT_SIERRA_MC7354		0x68C0	/* MC7354 */
#define	USB_PRODUCT_SIERRA_MC7355		0x9041	/* MC7355 */
#define	USB_PRODUCT_SIERRA_MC7430		0x9071	/* Sierra Wireless MC7430 Qualcomm Snapdragon X7 LTE-A */
#define	USB_PRODUCT_SIERRA_AC313U		0x68aa	/* Sierra Wireless AirCard 313U */
#define	USB_PRODUCT_SIERRA_TRUINSTALL	0x0fff	/* Aircard Tru Installer */

/* Sigmatel products */
#define	USB_PRODUCT_SIGMATEL_WBT_3052	0x4200	/* WBT-3052 IrDA/#define	USB_Bridge */
#define	USB_PRODUCT_SIGMATEL_I_BEAD100	0x8008	/* i-Bead 100 MP3 Player */

/* SIIG products */
/* Also: Omnidirectional Control Technology products */
#define	USB_PRODUCT_SIIG_DIGIFILMREADER	0x0004	/* DigiFilm-Combo Reader */
#define	USB_PRODUCT_SIIG_WINTERREADER	0x0330	/* WINTERREADER Reader */
#define	USB_PRODUCT_SIIG2_DK201			0x0103	/* FTDI compatible adapter */
#define	USB_PRODUCT_SIIG2_USBTOETHER	0x0109	/* USB TO Ethernet */
#define	USB_PRODUCT_SIIG2_US2308		0x0421	/* Serial */

/* Silicom products */
#define	USB_PRODUCT_SILICOM_U2E		0x0001	/* U2E */
#define	USB_PRODUCT_SILICOM_GPE		0x0002	/* Psion Gold Port Ethernet */

/* SI Labs */
#define	USB_PRODUCT_SILABS_VSTABI			0x0f91	/* VStabi Controller */
#define	USB_PRODUCT_SILABS_ARKHAM_DS101_M	0x1101	/* Arkham DS101 Monitor */
#define	USB_PRODUCT_SILABS_ARKHAM_DS101_A	0x1601	/* Arkham DS101 Adapter */
#define	USB_PRODUCT_SILABS_BSM7DUSB			0x800a	/* SPORTident BSM7-D USB */
#define	USB_PRODUCT_SILABS_POLOLU			0x803b	/* Pololu Serial */
#define	USB_PRODUCT_SILABS_CYGNAL_DEBUG		0x8044	/* Cygnal Debug Adapter */
#define	USB_PRODUCT_SILABS_SB_PARAMOUNT_ME	0x8043	/* Software Bisque Paramount ME */
#define	USB_PRODUCT_SILABS_SAEL				0x8053	/* SA-EL USB */
#define	USB_PRODUCT_SILABS_GSM2228			0x8054	/* Enfora GSM2228 USB */
#define	USB_PRODUCT_SILABS_ARGUSISP			0x8066	/* Argussoft ISP */
#define	USB_PRODUCT_SILABS_IMS_USB_RS422	0x806f	/* IMS USB-RS422 */
#define	USB_PRODUCT_SILABS_CRUMB128			0x807a	/* Crumb128 board */
#define	USB_PRODUCT_SILABS_OPTRIS_MSPRO		0x80c4	/* Optris MSpro LT Thermometer */
#define	USB_PRODUCT_SILABS_DEGREE			0x80ca	/* Degree Controls Inc */
#define	USB_PRODUCT_SILABS_TRACIENT			0x80dd	/* Tracient RFID */
#define	USB_PRODUCT_SILABS_TRAQMATE			0x80ed	/* Track Systems Traqmate */
#define	USB_PRODUCT_SILABS_SUUNTO			0x80f6	/* Suunto Sports Instrument */
#define	USB_PRODUCT_SILABS_ARYGON_MIFARE	0x8115	/* Arygon Mifare RFID reader */
#define	USB_PRODUCT_SILABS_BURNSIDE			0x813d	/* Burnside Telecon Deskmobile */
#define	USB_PRODUCT_SILABS_TAMSMASTER		0x813f	/* Tams Master Easy Control */
#define	USB_PRODUCT_SILABS_WMRBATT			0x814a	/* WMR RIGblaster Plug&Play */
#define	USB_PRODUCT_SILABS_WMRRIGBLASTER	0x814a	/* WMR RIGblaster Plug&Play */
#define	USB_PRODUCT_SILABS_WMRRIGTALK		0x814b	/* WMR RIGtalk RT1 */
#define	USB_PRODUCT_SILABS_B_G_H3000		0x8156	/* B&G H3000 Data Cable */
#define	USB_PRODUCT_SILABS_HELICOM			0x815e	/* Helicomm IP-Link 1220-DVM */
#define	USB_PRODUCT_SILABS_HAMLINKUSB_		0x815f	/* Timewave HamLinkUSB */
#define	USB_PRODUCT_SILABS_AVIT_USB_TTL		0x818b	/* AVIT Research USB-TTL */
#define	USB_PRODUCT_SILABS_MJS_TOSLINK		0x819f	/* MJS USB-TOSLINK */
#define	USB_PRODUCT_SILABS_WAVIT			0x81a6	/* ThinkOptics WavIt */
#define	USB_PRODUCT_SILABS_MULTIPLEX_RC		0x81a9	/* Multiplex RC adapter */
#define	USB_PRODUCT_SILABS_MSD_DASHHAWK		0x81ac	/* MSD DashHawk */
#define	USB_PRODUCT_SILABS_INSYS_MODEM		0x81ad	/* INSYS Modem */
#define	USB_PRODUCT_SILABS_LIPOWSKY_JTAG	0x81c8	/* Lipowsky Baby-JTAG */
#define	USB_PRODUCT_SILABS_LIPOWSKY_LIN		0x81e2	/* Lipowsky Baby-LIN */
#define	USB_PRODUCT_SILABS_AEROCOMM			0x81e7	/* Aerocomm Radio */
#define	USB_PRODUCT_SILABS_ZEPHYR_BIO		0x81e8	/* Zephyr Bioharness */
#define	USB_PRODUCT_SILABS_EMS_C1007		0x81f2	/* EMS C1007 HF RFID controller */
#define	USB_PRODUCT_SILABS_LIPOWSKY_HARP	0x8218	/* Lipowsky HARP-1 */
#define	USB_PRODUCT_SILABS_C2_EDGE_MODEM	0x822b	/* Commander 2 EDGE(GSM) Modem */
#define	USB_PRODUCT_SILABS_CYGNAL_GPS		0x826b	/* Cygnal Fasttrax GPS */
#define	USB_PRODUCT_SILABS_TELEGESIS_ETRX2	0x8293	/* Telegesis ETRX2USB */
#define	USB_PRODUCT_SILABS_PROCYON_AVS		0x82f9	/* Procyon AVS */
#define	USB_PRODUCT_SILABS_MC35PU			0x8341	/* MC35pu */
#define	USB_PRODUCT_SILABS_CYGNAL			0x8382	/* Cygnal */
#define	USB_PRODUCT_SILABS_AMBER_AMB2560	0x83a8	/* Amber Wireless AMB2560 */
#define	USB_PRODUCT_SILABS_DEKTEK_DTAPLUS	0x83d8	/* DekTec DTA Plus VHF/UHF Booster */
#define	USB_PRODUCT_SILABS_KYOCERA_GPS		0x8411	/* Kyocera GPS */
#define	USB_PRODUCT_SILABS_IRZ_SG10			0x8418	/* IRZ SG-10 GSM/GPRS Modem */
#define	USB_PRODUCT_SILABS_BEI_VCP			0x846e	/* BEI USB Sensor (VCP) */
#define	USB_PRODUCT_SILABS_BALLUFF_RFID		0x8477	/* Balluff RFID reader */
#define	USB_PRODUCT_SILABS_AC_SERV_IBUS		0x85ea	/* AC-Services IBUS Interface */
#define	USB_PRODUCT_SILABS_AC_SERV_CIS		0x85eb	/* AC-Services CIS-IBUS */
#define	USB_PRODUCT_SILABS_V_PREON32		0x85f8	/* Virtenio Preon32 */
#define	USB_PRODUCT_SILABS_AC_SERV_CAN		0x8664	/* AC-Services CAN Interface */
#define	USB_PRODUCT_SILABS_AC_SERV_OBD		0x8665	/* AC-Services OBD Interface */
#define	USB_PRODUCT_SILABS_MMB_ZIGBEE		0x88a4	/* MMB Networks ZigBee */
#define	USB_PRODUCT_SILABS_INGENI_ZIGBEE	0x88a5	/* Planet Innovation Ingeni ZigBee */
#define	USB_PRODUCT_SILABS_HUBZ				0x8a2a	/* HubZ dual ZigBee and Z-Wave */
#define	USB_PRODUCT_SILABS_CP2102			0xea60	/* SILABS USB UART */
#define	USB_PRODUCT_SILABS_CP210X_2			0xea61	/* CP210x Serial */
#define	USB_PRODUCT_SILABS_CP210X_3			0xea70	/* CP210x Serial */
#define	USB_PRODUCT_SILABS_CP210X_4			0xea80	/* CP210x Serial */
#define	USB_PRODUCT_SILABS_INFINITY_MIC	0xea71	/* Infinity GPS-MIC-1 Radio Monophone */
#define	USB_PRODUCT_SILABS_USBSCOPE50	0xf001	/* USBscope50 */
#define	USB_PRODUCT_SILABS_USBWAVE12	0xf002	/* USBwave12 */
#define	USB_PRODUCT_SILABS_USBPULSE100	0xf003	/* USBpulse100 */
#define	USB_PRODUCT_SILABS_USBCOUNT50	0xf004	/* USBcount50 */
#define	USB_PRODUCT_SILABS2_DCU11CLONE	0xaa26	/* DCU-11 clone */
#define	USB_PRODUCT_SILABS3_GPRS_MODEM	0xea61	/* GPRS Modem */
#define	USB_PRODUCT_SILABS4_100EU_MODEM	0xea61	/* GPRS Modem 100EU */

/* Silicon Portals Inc. */
#define	USB_PRODUCT_SILICONPORTALS_YAPPH_NF	0x0200	/* YAP Phone (no firmware) */
#define	USB_PRODUCT_SILICONPORTALS_YAPPHONE	0x0201	/* YAP Phone */

/* Sirius Technologies products */
#define	USB_PRODUCT_SIRIUS_ROADSTER		0x0001	/* NetComm Roadster II 56 USB */

/* Sitecom products */
#define	USB_PRODUCT_SITECOM_LN029		0x182d	/* #define	USB_2.0 Ethernet */
#define	USB_PRODUCT_SITECOM_SERIAL		0x2068	/* #define	USB_to serial cable (v2) */
#define	USB_PRODUCT_SITECOM2_WL022		0x182d	/* WL-022 */

/* Sitecom Europe products */
#define	USB_PRODUCT_SITECOMEU_RT2870_1	0x0017	/* RT2870 */
#define	USB_PRODUCT_SITECOMEU_WL168V1	0x000d	/* WL-168 v1 */
#define	USB_PRODUCT_SITECOMEU_LN030		0x0021	/* MCS7830 */
#define	USB_PRODUCT_SITECOMEU_WL168V4	0x0028	/* WL-168 v4 */
#define	USB_PRODUCT_SITECOMEU_RT2870_2	0x002b	/* RT2870 */
#define	USB_PRODUCT_SITECOMEU_RT2870_3	0x002c	/* RT2870 */
#define	USB_PRODUCT_SITECOMEU_RT2870_4	0x002d	/* RT2870 */
#define	USB_PRODUCT_SITECOMEU_RT2770	0x0039	/* RT2770 */
#define	USB_PRODUCT_SITECOMEU_RT3070_2	0x003b	/* RT3070 */
#define	USB_PRODUCT_SITECOMEU_RT3070_3	0x003c	/* RT3070 */
#define	USB_PRODUCT_SITECOMEU_RT3070_4	0x003d	/* RT3070 */
#define	USB_PRODUCT_SITECOMEU_RT3070	0x003e	/* RT3070 */
#define	USB_PRODUCT_SITECOMEU_WL608		0x003f	/* WL-608 */
#define	USB_PRODUCT_SITECOMEU_RT3071	0x0040	/* RT3071 */
#define	USB_PRODUCT_SITECOMEU_RT3072_1	0x0041	/* RT3072 */
#define	USB_PRODUCT_SITECOMEU_RT3072_2	0x0042	/* RT3072 */
#define	USB_PRODUCT_SITECOMEU_WL353		0x0045	/* WL-353 */
#define	USB_PRODUCT_SITECOMEU_RT3072_3	0x0047	/* RT3072 */
#define	USB_PRODUCT_SITECOMEU_RT3072_4	0x0048	/* RT3072 */
#define	USB_PRODUCT_SITECOMEU_RT3072_5	0x004a	/* RT3072 */
#define	USB_PRODUCT_SITECOMEU_WL349V1	0x004b	/* WL-349 v1 */
#define	USB_PRODUCT_SITECOMEU_RT3072_6	0x004d	/* RT3072 */
#define	USB_PRODUCT_SITECOMEU_WLA1000	0x005b	/* WLA-1000 */
#define	USB_PRODUCT_SITECOMEU_RTL8188CU_1	0x0052	/* RTL8188CU */
#define	USB_PRODUCT_SITECOMEU_RTL8188CU_2	0x005c	/* RTL8188CU */
#define	USB_PRODUCT_SITECOMEU_RTL8192CU	0x0061	/* RTL8192CU */
#define	USB_PRODUCT_SITECOMEU_LN032		0x0072	/* LN-032 */
#define	USB_PRODUCT_SITECOMEU_LN031		0x0056	/* LN-031 */
#define	USB_PRODUCT_SITECOMEU_LN028		0x061c	/* LN-028 */
#define	USB_PRODUCT_SITECOMEU_WL113		0x9071	/* WL-113 */
#define	USB_PRODUCT_SITECOMEU_ZD1211B	0x9075	/* ZD1211B */
#define	USB_PRODUCT_SITECOMEU_WL172		0x90ac	/* WL-172 */
#define	USB_PRODUCT_SITECOMEU_WL113R2	0x9712	/* WL-113 rev 2 */

/* Skanhex Technology products */
#define	USB_PRODUCT_SKANHEX_MD_7425		0x410a	/* MD 7425 Camera */
#define	USB_PRODUCT_SKANHEX_SX_520Z		0x5200	/* SX 520z Camera */

/* Smart Technologies products */
#define	USB_PRODUCT_SMART_PL2303		0x2303	/* Serial adapter */

/* SmartBridges products */
#define	USB_PRODUCT_SMARTBRIDGES_SMARTLINK	0x0001	/* SmartLink USB Ethernet */
#define	USB_PRODUCT_SMARTBRIDGES_SMARTNIC	0x0003	/* smartNIC 2 PnP Ethernet */

/* SMC products */
#define	USB_PRODUCT_SMC_2102USB			0x0100	/* 10Mbps Ethernet */
#define	USB_PRODUCT_SMC_2202USB			0x0200	/* 10/100 Ethernet */
#define	USB_PRODUCT_SMC_2206USB			0x0201	/* EZ Connect USB Ethernet */
#define	USB_PRODUCT_SMC_2862WG			0xee13	/* EZ Connect Wireless Adapter */
#define	USB_PRODUCT_SMC2_2020HUB		0x2020	/* USB Hub */
#define	USB_PRODUCT_SMC2_2514HUB		0x2514	/* USB Hub */
#define	USB_PRODUCT_SMC3_2662WUSB		0xa002	/* 2662W-AR Wireless */
#define	USB_PRODUCT_SMC2_LAN9500_ETH	0x9500	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9505_ETH	0x9505	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9530_ETH	0x9530	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9730_ETH	0x9730	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9500_SAL10	0x9900	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9505_SAL10	0x9901	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9500A_SAL10	0x9902	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9505A_SAL10	0x9903	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9514_SAL10	0x9904	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9500A_HAL	0x9905	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9505A_HAL	0x9906	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9500_ETH_2	0x9907	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9500A_ETH_2	0x9908	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9514_ETH_2	0x9909	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9500A_ETH	0x9e00	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9505A_ETH	0x9e01	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN89530_ETH	0x9e08	/* USB/Ethernet */
#define	USB_PRODUCT_SMC2_LAN9514_ETH	0xec00	/* USB/Ethernet */

/* SOHOware products */
#define	USB_PRODUCT_SOHOWARE_NUB100		0x9100	/* 10/100 USB Ethernet */
#define	USB_PRODUCT_SOHOWARE_NUB110		0x9110	/* 10/100 USB Ethernet */

/* SOLID YEAR products */
#define	USB_PRODUCT_SOLIDYEAR_KEYBOARD	0x2101	/* Solid Year USB keyboard */

/* SONY products */
#define	USB_PRODUCT_SONY_DSC			0x0010	/* DSC cameras */
#define	USB_PRODUCT_SONY_MS_NW_MS7		0x0025	/* Memorystick NW-MS7 */
#define	USB_PRODUCT_SONY_PORTABLE_HDD_V2	0x002b	/* Portable USB Harddrive V2 */
#define	USB_PRODUCT_SONY_MSACUS1		0x002d	/* Memorystick MSAC-US1 */
#define	USB_PRODUCT_SONY_HANDYCAM		0x002e	/* Handycam */
#define	USB_PRODUCT_SONY_MSC			0x0032	/* MSC memory stick slot */
#define	USB_PRODUCT_SONY_CLIE_35		0x0038	/* Sony Clie v3.5 */
#define	USB_PRODUCT_SONY_MS_PEG_N760C	0x0058	/* PEG N760c Memorystick */
#define	USB_PRODUCT_SONY_CLIE_40		0x0066	/* Sony Clie v4.0 */
#define	USB_PRODUCT_SONY_MS_MSC_U03		0x0069	/* Memorystick MSC-U03 */
#define	USB_PRODUCT_SONY_CLIE_40_MS		0x006d	/* Sony Clie v4.0 Memory Stick slot */
#define	USB_PRODUCT_SONY_CLIE_S360		0x0095	/* Sony Clie s360 */
#define	USB_PRODUCT_SONY_CLIE_41_MS		0x0099	/* Sony Clie v4.1 Memory Stick slot */
#define	USB_PRODUCT_SONY_CLIE_41		0x009a	/* Sony Clie v4.1 */
#define	USB_PRODUCT_SONY_CLIE_NX60		0x00da	/* Sony Clie nx60 */
#define	USB_PRODUCT_SONY_CLIE_TH55		0x0144	/* Sony Clie th55 */
#define	USB_PRODUCT_SONY_CLIE_TJ37		0x0169	/* Sony Clie tj37 */
#define	USB_PRODUCT_SONY_RF_RECEIVER	0x01db	/* Sony RF mouse/kbd Receiver VGP-WRC1 */
#define	USB_PRODUCT_SONY_QN3			0x0437	/* Sony QN3 CMD-Jxx phone cable */

/* Sony Ericsson products */
#define	USB_PRODUCT_SONYERICSSON_DCU10		0x0528	/* DCU-10 Phone Data Cable */
#define	USB_PRODUCT_SONYERICSSON_DATAPILOT	0x2003	/* Datapilot Phone Cable */

/* SOURCENEXT products */
#define	USB_PRODUCT_SOURCENEXT_KEIKAI8		0x039f	/* KeikaiDenwa 8 */
#define	USB_PRODUCT_SOURCENEXT_KEIKAI8_CHG	0x012e	/* KeikaiDenwa 8 with charger */

/* SparkLAN products */
#define	USB_PRODUCT_SPARKLAN_RT2573		0x0004	/* RT2573 */
#define	USB_PRODUCT_SPARKLAN_RT2870_1	0x0006	/* RT2870 */
#define	USB_PRODUCT_SPARKLAN_RT3070		0x0010	/* RT3070 */

/* Soundgraph products */
#define	USB_PRODUCT_SOUNDGRAPH_IMON_VFD		0x0044	/* Antec Veris Elite VFD Panel, Knob, and Remote */
#define	USB_PRODUCT_SOUNDGRAPH_SSTONE_LC16	0xffdc	/* Silverstone LC16 VFD Panel, Knob, and Remote */

/* Speed Dragon Multimedia products */
#define	USB_PRODUCT_SPEEDDRAGON_MS3303H		0x110b	/* MS3303H Serial */

/* Sphairon Access Systems GmbH products */
#define	USB_PRODUCT_SPHAIRON_UB801R			0x0110	/* UB801R */

/* Stelera Wireless products */
#define	USB_PRODUCT_STELERA_ZEROCD		0x1000	/* Zerocd Installer */
#define	USB_PRODUCT_STELERA_C105		0x1002	/* Stelera/Bandrish C105 USB */
#define	USB_PRODUCT_STELERA_E1003		0x1003	/* 3G modem */
#define	USB_PRODUCT_STELERA_E1004		0x1004	/* 3G modem */
#define	USB_PRODUCT_STELERA_E1005		0x1005	/* 3G modem */
#define	USB_PRODUCT_STELERA_E1006		0x1006	/* 3G modem */
#define	USB_PRODUCT_STELERA_E1007		0x1007	/* 3G modem */
#define	USB_PRODUCT_STELERA_E1008		0x1008	/* 3G modem */
#define	USB_PRODUCT_STELERA_E1009		0x1009	/* 3G modem */
#define	USB_PRODUCT_STELERA_E100A		0x100a	/* 3G modem */
#define	USB_PRODUCT_STELERA_E100B		0x100b	/* 3G modem */
#define	USB_PRODUCT_STELERA_E100C		0x100c	/* 3G modem */
#define	USB_PRODUCT_STELERA_E100D		0x100d	/* 3G modem */
#define	USB_PRODUCT_STELERA_E100E		0x100e	/* 3G modem */
#define	USB_PRODUCT_STELERA_E100F		0x100f	/* 3G modem */
#define	USB_PRODUCT_STELERA_E1010		0x1010	/* 3G modem */
#define	USB_PRODUCT_STELERA_E1011		0x1011	/* 3G modem */
#define	USB_PRODUCT_STELERA_E1012		0x1012	/* 3G modem */

/* STMicroelectronics products */
#define	USB_PRODUCT_STMICRO_BIOCPU			0x2016	/* Biometric Coprocessor */
#define	USB_PRODUCT_STMICRO_COMMUNICATOR	0x7554	/* USB Communicator */
#define	USB_PRODUCT_STMICRO_ST72682			0xfada	/* 2.0 Flash drive controller */

/* STSN products */
#define	USB_PRODUCT_STSN_STSN0001		0x0001	/* Internet Access Device */

/* SUN Corporation products */
#define	USB_PRODUCT_SUNTAC_DS96L		0x0003	/* SUNTAC U-Cable type D2 */
#define	USB_PRODUCT_SUNTAC_PS64P1		0x0005	/* SUNTAC U-Cable type P1 */
#define	USB_PRODUCT_SUNTAC_VS10U		0x0009	/* SUNTAC Slipper U */
#define	USB_PRODUCT_SUNTAC_IS96U		0x000a	/* SUNTAC Ir-Trinity */
#define	USB_PRODUCT_SUNTAC_AS64LX		0x000b	/* SUNTAC U-Cable type A3 */
#define	USB_PRODUCT_SUNTAC_AS144L4		0x0011	/* SUNTAC U-Cable type A4 */

/* Sun Microsystems products */
#define	USB_PRODUCT_SUN_KEYBOARD_TYPE_6	0x0005	/* Type 6 USB keyboard */
#define	USB_PRODUCT_SUN_KEYBOARD_TYPE_7	0x00a2	/* Type 7 USB keyboard */
/* XXX The above is a North American PC style keyboard possibly */
#define	USB_PRODUCT_SUN_MOUSE			0x0100	/* Type 6 USB mouse */
#define	USB_PRODUCT_SUN_KBD_HUB			0x100e	/* Kbd Hub */

/* Sunplus Innovation Technology Inc. products */
#define	USB_PRODUCT_SUNPLUS_USBMOUSE	0x0007	/* USB Optical Mouse */

/* Super Top products */
#define	USB_PRODUCT_SUPERTOP_IDE		0x6600	/* USB-IDE */
#define	USB_PRODUCT_SUPERTOP_FLASHDRIVE	0x121c	/* extrememory Snippy */

/* Syntech products */
#define	USB_PRODUCT_SYNTECH_CPT8001C		0x0001	/* CPT-8001C Barcode scanner */
#define	USB_PRODUCT_SYNTECH_CYPHERLAB100	0x1000	/* CipherLab USB Barcode Scanner */

/* Teclast products */
#define	USB_PRODUCT_TECLAST_TLC300			0x3203	/* USB Media Player */

/* Testo products */
#define	USB_PRODUCT_TESTO_USB_INTERFACE		0x0001	/* FTDI compatible adapter */

/* TexTech products */
#define	USB_PRODUCT_TEXTECH_DUMMY		0x0000	/* Dummy product */
#define	USB_PRODUCT_TEXTECH_U2M_1		0x0101	/* Textech USB MIDI cable */
#define	USB_PRODUCT_TEXTECH_U2M_2		0x1806	/* Textech USB MIDI cable */

/* The Mobility Lab products */
#define	USB_PRODUCT_TML_USB_SERIAL		0x0064	/* FTDI compatible adapter */

/* Thurlby Thandar Instrument products */
#define	USB_PRODUCT_TTI_QL355P			0x03e8	/* FTDI compatible adapter */

/* Supra products */
#define	USB_PRODUCT_DIAMOND2_SUPRAEXPRESS56K	0x07da	/* Supra Express 56K modem */
#define	USB_PRODUCT_DIAMOND2_SUPRA2890			0x0b4a	/* SupraMax 2890 56K Modem */
#define	USB_PRODUCT_DIAMOND2_RIO600USB			0x5001	/* Rio 600 USB */
#define	USB_PRODUCT_DIAMOND2_RIO800USB			0x5002	/* Rio 800 USB */

/* Surecom Technology products */
#define	USB_PRODUCT_SURECOM_EP9001G2A	0x11f2	/* EP-9001-G rev 2A */
#define	USB_PRODUCT_SURECOM_RT2570		0x11f3	/* RT2570 */
#define	USB_PRODUCT_SURECOM_RT2573		0x31f3	/* RT2573 */

/* Sweex products */
#define	USB_PRODUCT_SWEEX_ZD1211		0x1809	/* ZD1211 */
#define	USB_PRODUCT_SWEEX2_LW153		0x0153	/* LW153 */
#define	USB_PRODUCT_SWEEX2_LW154		0x0154	/* LW154 */
#define	USB_PRODUCT_SWEEX2_LW303		0x0302	/* LW303 */
#define	USB_PRODUCT_SWEEX2_LW313		0x0313	/* LW313 */

/* System TALKS, Inc. */
#define	USB_PRODUCT_SYSTEMTALKS_SGCX2UL	0x1920	/* SGC-X2UL */

/* Tapwave products */
#define	USB_PRODUCT_TAPWAVE_ZODIAC		0x0100	/* Zodiac */

/* Taugagreining products */
#define	USB_PRODUCT_TAUGA_CAMERAMATE	0x0005	/* CameraMate (DPCM USB) */

/* TCTMobile products */
#define	USB_PRODUCT_TCTMOBILE_X060S		0x0000	/* X060S 3G modem */
#define	USB_PRODUCT_TCTMOBILE_X080S		0xf000	/* X080S 3G modem */

/* TDK products */
#define	USB_PRODUCT_TDK_UPA9664			0x0115	/* USB-PDC Adapter UPA9664 */
#define	USB_PRODUCT_TDK_UCA1464			0x0116	/* USB-cdmaOne Adapter UCA1464 */
#define	USB_PRODUCT_TDK_UHA6400			0x0117	/* USB-PHS Adapter UHA6400 */
#define	USB_PRODUCT_TDK_UPA6400			0x0118	/* USB-PHS Adapter UPA6400 */
#define	USB_PRODUCT_TDK_BT_DONGLE		0x0309	/* Bluetooth USB dongle */

/* TEAC products */
#define	USB_PRODUCT_TEAC_FD05PUB		0x0000	/* FD-05PUB floppy */

/* Tekram Technology products */
#define	USB_PRODUCT_TEKRAM_QUICKWLAN	0x1630	/* QuickWLAN */
#define	USB_PRODUCT_TEKRAM_ZD1211_1		0x5630	/* ZD1211 */
#define	USB_PRODUCT_TEKRAM_ZD1211_2		0x6630	/* ZD1211 */

/* Telex Communications products */
#define	USB_PRODUCT_TELEX_MIC1			0x0001	/* Enhanced USB Microphone */

/* Telit products */
#define	USB_PRODUCT_TELIT_UC864E		0x1003	/* UC864E 3G modem */
#define	USB_PRODUCT_TELIT_UC864G		0x1004	/* UC864G 3G modem */

/* Ten X Technology, Inc. */
#define	USB_PRODUCT_TENX_UAUDIO0		0xf211	/* USB audio headset */

/* Texas Intel products */
#define	USB_PRODUCT_TI_UTUSB41			0x1446	/* UT-USB41 hub */
#define	USB_PRODUCT_TI_TUSB2046			0x2046	/* TUSB2046 hub */

/* Thrustmaster products */
#define	USB_PRODUCT_THRUST_FUSION_PAD	0xa0a3	/* Fusion Digital Gamepad */

/* TLayTech products */
#define	USB_PRODUCT_TLAYTECH_TEU800		0x1682	/* TEU800 3G modem */

/* Topre Corporation products */
#define	USB_PRODUCT_TOPRE_HHKB			0x0100	/* HHKB Professional */

/* Toshiba Corporation products */
#define	USB_PRODUCT_TOSHIBA_POCKETPC_E740	0x0706	/* PocketPC e740 */
#define	USB_PRODUCT_TOSHIBA_RT3070			0x0a07	/* RT3070 */
#define	USB_PRODUCT_TOSHIBA_G450			0x0d45	/* G450 modem */
#define	USB_PRODUCT_TOSHIBA_HSDPA			0x1302	/* G450 modem */
#define	USB_PRODUCT_TOSHIBA_TRANSMEMORY		0x6545	/* USB ThumbDrive */

/* TP-Link products */
#define	USB_PRODUCT_TPLINK_T4U			0x0101	/* Archer T4U */
#define	USB_PRODUCT_TPLINK_WN722NV2		0x010c	/* TL-WN722N v2 */

/* Trek Technology products */
#define	USB_PRODUCT_TREK_THUMBDRIVE		0x1111	/* ThumbDrive */
#define	USB_PRODUCT_TREK_MEMKEY			0x8888	/* IBM USB Memory Key */
#define	USB_PRODUCT_TREK_THUMBDRIVE_8MB	0x9988	/* ThumbDrive 8MB */

/* TRENDnet products */
#define	USB_PRODUCT_TRENDNET_RTL8192CU	0x624d	/* RTL8192CU */
#define	USB_PRODUCT_TRENDNET_TEW646UBH	0x646b	/* TEW-646UBH */
#define	USB_PRODUCT_TRENDNET_RTL8188CU	0x648b	/* RTL8188CU */

/* Tripp-Lite products */
#define	USB_PRODUCT_TRIPPLITE_U209		0x2008	/* Serial */

/* Trumpion products */
#define	USB_PRODUCT_TRUMPION_T33520		0x1001	/* T33520 USB_Flash Card Controller */
#define	USB_PRODUCT_TRUMPION_C3310		0x1100	/* Comotron C3310 MP3 player */
#define	USB_PRODUCT_TRUMPION_MP3		0x1200	/* MP3 player */

/* TwinMOS */
#define	USB_PRODUCT_TWINMOS_G240		0xa006	/* G240 */
#define	USB_PRODUCT_TWINMOS_MDIV		0x1325	/* Memory Disk IV */

/* Ubiquam products */
#define	USB_PRODUCT_UBIQUAM_UALL		0x3100	/* CDMA 1xRTT USB Modem (U-100/105/200/300/520) */

/* Ultima products */
#define	USB_PRODUCT_ULTIMA_1200UBPLUS	0x4002	/* 1200 UB Plus scanner */

/* UMAX products */
#define	USB_PRODUCT_UMAX_ASTRA1236U		0x0002	/* Astra 1236U Scanner */
#define	USB_PRODUCT_UMAX_ASTRA1220U		0x0010	/* Astra 1220U Scanner */
#define	USB_PRODUCT_UMAX_ASTRA2000U		0x0030	/* Astra 2000U Scanner */
#define	USB_PRODUCT_UMAX_ASTRA2100U		0x0130	/* Astra 2100U Scanner */
#define	USB_PRODUCT_UMAX_ASTRA2200U		0x0230	/* Astra 2200U Scanner */
#define	USB_PRODUCT_UMAX_ASTRA3400		0x0060	/* Astra 3400 Scanner */

/* U-MEDIA Communications products */
#define	USB_PRODUCT_UMEDIA_TEW444UBEU		0x3006	/* TEW-444UB EU */
#define	USB_PRODUCT_UMEDIA_TEW444UBEU_NF	0x3007	/* TEW-444UB EU (no firmware) */
#define	USB_PRODUCT_UMEDIA_TEW429UB_A		0x300a	/* TEW-429UB A */
#define	USB_PRODUCT_UMEDIA_TEW429UB			0x300b	/* TEW-429UB */
#define	USB_PRODUCT_UMEDIA_TEW429UBC1		0x300d	/* TEW-429UB C1 */
#define	USB_PRODUCT_UMEDIA_RT2870_1			0x300e	/* RT2870 */
#define	USB_PRODUCT_UMEDIA_ALL0298V2		0x3204	/* ALL0298 v2 */
#define	USB_PRODUCT_UMEDIA_AR5523_2			0x3205	/* AR5523 */
#define	USB_PRODUCT_UMEDIA_AR5523_2_NF		0x3206	/* AR5523 (no firmware) */

/* Universal Access products */
#define	USB_PRODUCT_UNIACCESS_PANACHE	0x0101	/* Panache Surf USB ISDN Adapter */

/* Unknown products */
#define	USB_PRODUCT_UNKNOWN4_NF_RIC		0x0001	/* FTDI compatible adapter */

/* USI products */
#define	USB_PRODUCT_USI_MC60			0x10c5	/* MC60 Serial */

/* U.S. Robotics products */
#define	USB_PRODUCT_USR_USR5422			0x0118	/* USR5422 WLAN */
#define	USB_PRODUCT_USR_USR5423			0x0121	/* USR5423 WLAN */

/* VIA Technologies products */
#define	USB_PRODUCT_VIA_USB2IDEBRIDGE	0x6204	/* USB 2.0 IDE Bridge */

/* VIA Labs */
#define	USB_PRODUCT_VIALABS_USB30SATABRIDGE	0x0700	/* USB 3.0 SATA Bridge */

/* Vaisala products */
#define	USB_PRODUCT_VAISALA_CABLE		0x0200	/* #define	USB_Interface cable */

/* Vertex products */
#define	USB_PRODUCT_VERTEX_VW110L		0x0100	/* Vertex VW110L modem */

/* VidzMedia products */
#define	USB_PRODUCT_VIDZMEDIA_MONSTERTV	0x4fb1	/* MonsterTV P2H */

/* Vision products */
#define	USB_PRODUCT_VISION_VC6452V002	0x0002	/* CPiA Camera */

/* Visioneer products */
#define	USB_PRODUCT_VISIONEER_7600		0x0211	/* OneTouch 7600 */
#define	USB_PRODUCT_VISIONEER_5300		0x0221	/* OneTouch 5300 */
#define	USB_PRODUCT_VISIONEER_3000		0x0224	/* Scanport 3000 */
#define	USB_PRODUCT_VISIONEER_6100		0x0231	/* OneTouch 6100 */
#define	USB_PRODUCT_VISIONEER_6200		0x0311	/* OneTouch 6200 */
#define	USB_PRODUCT_VISIONEER_8100		0x0321	/* OneTouch 8100 */
#define	USB_PRODUCT_VISIONEER_8600		0x0331	/* OneTouch 8600 */

/* Vivitar products */
#define	USB_PRODUCT_VIVITAR_35XX		0x0003	/* Vivicam 35Xx */

/* VTech products */
#define	USB_PRODUCT_VTECH_RT2570		0x3012	/* RT2570 */
#define	USB_PRODUCT_VTECH_ZD1211B		0x3014	/* ZD1211B */

/* Wacom products */
#define	USB_PRODUCT_WACOM_CT0405U		0x0000	/* CT-0405-U Tablet */
#define	USB_PRODUCT_WACOM_GRAPHIRE		0x0010	/* Graphire */
#define	USB_PRODUCT_WACOM_GRAPHIRE3_4X5	0x0013	/* Graphire 3 4x5 */
#define	USB_PRODUCT_WACOM_INTUOSA5		0x0021	/* Intuos A5 */
#define	USB_PRODUCT_WACOM_GD0912U		0x0022	/* Intuos 9x12 Graphics Tablet */

/* WAGO Kontakttechnik GmbH products */
#define	USB_PRODUCT_WAGO_SERVICECABLE	0x07a6	/* USB Service Cable 750-923 */

/* WaveSense products */
#define	USB_PRODUCT_WAVESENSE_JAZZ		0xaaaa	/* Jazz blood glucose meter */

/* WCH products */
#define	USB_PRODUCT_WCH_CH341SER		0x5523	/* CH341/CH340 USB-Serial Bridge */
#define	USB_PRODUCT_WCH2_DUMMY			0x0000	/* Dummy product */
#define	USB_PRODUCT_WCH2_CH341SER_2		0x5523	/* CH341/CH340 USB-Serial Bridge */
#define	USB_PRODUCT_WCH2_CH341SER		0x7523	/* CH341/CH340 USB-Serial Bridge */
#define	USB_PRODUCT_WCH2_U2M			0X752d	/* CH345 USB2.0-MIDI */

/* West Mountain Radio products */
#define	USB_PRODUCT_WESTMOUNTAIN_RIGBLASTER_ADVANTAGE	0x0003	/* RIGblaster Advantage */

/* Western Digital products */
#define	USB_PRODUCT_WESTERN_COMBO			0x0200	/* Firewire USB Combo */
#define	USB_PRODUCT_WESTERN_EXTHDD			0x0400	/* External HDD */
#define	USB_PRODUCT_WESTERN_HUB				0x0500	/* USB HUB */
#define	USB_PRODUCT_WESTERN_MYBOOK			0x0901	/* MyBook External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORT_00	0x0704	/* MyPassport External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORT_11	0x0741	/* MyPassport External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORT_01	0x0746	/* MyPassport External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORT_02	0x0748	/* MyPassport External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORT_03	0x074A	/* MyPassport External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORT_04	0x074C	/* MyPassport External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORT_05	0x074E	/* MyPassport External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORT_06	0x07A6	/* MyPassport External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORT_07	0x07A8	/* MyPassport External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORT_08	0x07AA	/* MyPassport External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORT_09	0x07AC	/* MyPassport External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORT_10	0x07AE	/* MyPassport External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORTES_00	0x070A	/* MyPassport Essential External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORTES_01	0x071A	/* MyPassport Essential External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORTES_02	0x0730	/* MyPassport Essential External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORTES_03	0x0732	/* MyPassport Essential External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORTES_04	0x0740	/* MyPassport Essential External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORTES_05	0x0742	/* MyPassport Essential External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORTES_06	0x0750	/* MyPassport Essential External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORTES_07	0x0752	/* MyPassport Essential External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORTES_08	0x07A0	/* MyPassport Essential External HDD */
#define	USB_PRODUCT_WESTERN_MYPASSPORTES_09	0x07A2	/* MyPassport Essential External HDD */

/* WeTelecom products */
#define	USB_PRODUCT_WETELECOM_WM_D200		0x6801	/* WM-D200 */

/* WIENER Plein & Baus GmbH products */
#define	USB_PRODUCT_WIENERPLEINBAUS_PL512	0x0010	/* PL512 PSU */
#define	USB_PRODUCT_WIENERPLEINBAUS_RCM		0x0011	/* RCM Remote Control */
#define	USB_PRODUCT_WIENERPLEINBAUS_MPOD	0x0012	/* MPOD PSU */
#define	USB_PRODUCT_WIENERPLEINBAUS_CML		0x0015	/* CML Data Logger */

/* Windbond Electronics */
#define	USB_PRODUCT_WINBOND_UH104			0x5518	/* 4-port USB Hub */

/* WinMaxGroup products */
#define	USB_PRODUCT_WINMAXGROUP_FLASH64MC	0x6660	/* USB Flash Disk 64M-C */

/* Wistron NeWeb products */
#define	USB_PRODUCT_WISTRONNEWEB_WNC0600	0x0326	/* WNC-0600USB */
#define	USB_PRODUCT_WISTRONNEWEB_UR045G		0x0427	/* PrismGT USB 2.0 WLAN */
#define	USB_PRODUCT_WISTRONNEWEB_UR055G		0x0711	/* UR055G */
#define	USB_PRODUCT_WISTRONNEWEB_O8494		0x0804	/* ORiNOCO 802.11n */
#define	USB_PRODUCT_WISTRONNEWEB_AR5523_1	0x0826	/* AR5523 */
#define	USB_PRODUCT_WISTRONNEWEB_AR5523_1_NF	0x0827	/* AR5523 (no firmware) */
#define	USB_PRODUCT_WISTRONNEWEB_AR5523_2		0x082a	/* AR5523 */
#define	USB_PRODUCT_WISTRONNEWEB_AR5523_2_NF	0x0829	/* AR5523 (no firmware) */

/* Xerox products */
#define	USB_PRODUCT_XEROX_WCM15			0xffef	/* WorkCenter M15 */

/* Xirlink products */
#define	USB_PRODUCT_XIRLINK_PCCAM		0x8080	/* IBM PC Camera */

/* Xyratex products */
#define	USB_PRODUCT_XYRATEX_PRISM_GT_1	0x2000	/* PrismGT USB 2.0 WLAN */
#define	USB_PRODUCT_XYRATEX_PRISM_GT_2	0x2002	/* PrismGT USB 2.0 WLAN */

/* Yamaha products */
#define	USB_PRODUCT_YAMAHA_UX256		0x1000	/* UX256 MIDI I/F */
#define	USB_PRODUCT_YAMAHA_UX96			0x1008	/* UX96 MIDI I/F */
#define	USB_PRODUCT_YAMAHA_RPU200		0x3104	/* RP-U200 */
#define	USB_PRODUCT_YAMAHA_RTA54I		0x4000	/* NetVolante RTA54i Broadband&ISDN Router */
#define	USB_PRODUCT_YAMAHA_RTW65B		0x4001	/* NetVolante RTW65b Broadband Wireless Router */
#define	USB_PRODUCT_YAMAHA_RTW65I		0x4002	/* NetVolante RTW65i Broadband&ISDN Wireless Router */
#define	USB_PRODUCT_YAMAHA_RTA55I		0x4004	/* NetVolante RTA55i Broadband VoIP Router */

/* Yano products */
#define	USB_PRODUCT_YANO_U640MO			0x0101	/* U640MO-03 */
#define	USB_PRODUCT_YANO_FW800HD		0x05fc	/* METALWEAR-HDD */

/* Y.C. Cable products */
#define	USB_PRODUCT_YCCABLE_PL2303		0x0fba	/* PL2303 Serial */

/* Y-E Data products */
#define	USB_PRODUCT_YEDATA_FLASHBUSTERU	0x0000	/* Flashbuster-U */

/* Yiso Wireless Co. products */
#define	USB_PRODUCT_YISO_C893		0xc893	/* CDMA 2000 1xEVDO PC Card */

/* Z-Com products */
#define	USB_PRODUCT_ZCOM_M4Y750		0x0001	/* M4Y-750 */
#define	USB_PRODUCT_ZCOM_XI725		0x0002	/* XI-725/726 */
#define	USB_PRODUCT_ZCOM_XI735		0x0005	/* XI-735 */
#define	USB_PRODUCT_ZCOM_XG703A		0x0008	/* PrismGT USB 2.0 WLAN */
#define	USB_PRODUCT_ZCOM_ZD1211		0x0011	/* ZD1211 */
#define	USB_PRODUCT_ZCOM_AR5523		0x0012	/* AR5523 */
#define	USB_PRODUCT_ZCOM_AR5523_NF	0x0013	/* AR5523 driver (no firmware) */
#define	USB_PRODUCT_ZCOM_XM142		0x0015	/* XM-142 */
#define	USB_PRODUCT_ZCOM_ZD1211B	0x001a	/* ZD1211B */
#define	USB_PRODUCT_ZCOM_RT2870_1	0x0022	/* RT2870 */
#define	USB_PRODUCT_ZCOM_UB81		0x0023	/* UB81 */
#define	USB_PRODUCT_ZCOM_RT2870_2	0x0025	/* RT2870 */
#define	USB_PRODUCT_ZCOM_UB82		0x0026	/* UB82 */

/* Zinwell products */
#define	USB_PRODUCT_ZINWELL_RT2570		0x0260	/* RT2570 */
#define	USB_PRODUCT_ZINWELL_RT2870_1	0x0280	/* RT2870 */
#define	USB_PRODUCT_ZINWELL_RT2870_2	0x0282	/* RT2870 */
#define	USB_PRODUCT_ZINWELL_RT3072_1	0x0283	/* RT3072 */
#define	USB_PRODUCT_ZINWELL_RT3072_2	0x0284	/* RT3072 */
#define	USB_PRODUCT_ZINWELL_RT3070		0x5257	/* RT3070 */

/* Zoom Telephonics, Inc. products */
#define	USB_PRODUCT_ZOOM_2986L			0x9700	/* 2986L Fax modem */

/* Zoran Microelectronics products */
#define	USB_PRODUCT_ZORAN_EX20DSC		0x4343	/* Digital Camera EX-20 DSC */

/* Zydas Technology Corporation products */
#define	USB_PRODUCT_ZYDAS_ZD1211		0x1211	/* ZD1211 WLAN abg */
#define	USB_PRODUCT_ZYDAS_ZD1211B		0x1215	/* ZD1211B */
#define	USB_PRODUCT_ZYDAS_ZD1221		0x1221	/* ZD1221 */

/* ZyXEL Communication Co. products */
#define	USB_PRODUCT_ZYXEL_OMNI56K		0x1500	/* Omni 56K Plus */
#define	USB_PRODUCT_ZYXEL_980N			0x2011	/* Scorpion-980N keyboard */
#define	USB_PRODUCT_ZYXEL_ZYAIRG220		0x3401	/* ZyAIR G-220 */
#define	USB_PRODUCT_ZYXEL_G200V2		0x3407	/* G-200 v2 */
#define	USB_PRODUCT_ZYXEL_AG225H		0x3409	/* AG-225H */
#define	USB_PRODUCT_ZYXEL_M202			0x340a	/* M-202 */
#define	USB_PRODUCT_ZYXEL_G220V2		0x340f	/* G-220 v2 */
#define	USB_PRODUCT_ZYXEL_G202			0x3410	/* G-202 */
#define	USB_PRODUCT_ZYXEL_RT2870_1		0x3416	/* RT2870 */
#define	USB_PRODUCT_ZYXEL_NWD271N		0x3417	/* NWD-271N */
#define	USB_PRODUCT_ZYXEL_NWD211AN		0x3418	/* NWD-211AN */
#define	USB_PRODUCT_ZYXEL_RT2870_2		0x341a	/* RT2870 */
#define	USB_PRODUCT_ZYXEL_RT3070		0x341e	/* NWD2105 */
#define	USB_PRODUCT_ZYXEL_RTL8192CU		0x341f	/* RTL8192CU */
#define	USB_PRODUCT_ZYXEL_NWD2705		0x3421	/* NWD2705 */
