/* 0 source fass.de uni fass.de ace fass.de nv8  line B;	fass.de;	;	;	
 */
{ "fass.de", "fass.de", IDN2_OK },
/* 1 source faß.de uni faß.de ace xn--fa-hia.de nv8  line N;	faß.de;	;	xn--fa-hia.de;	
 */
{ "faß.de", "xn--fa-hia.de", IDN2_OK },
/* 2 source a\u200Cb uni [C1] ace [C1] nv8  line N;	a\u200Cb;	[C1];	[C1];		#	a‌b
 */
/* punt1 */
/* 2 source ab uni ab ace ab nv8  line B;	ab;	;	;	
 */
{ "ab", "ab", IDN2_OK },
/* 3 source \u0308\u200C\u0308\u0628b uni [V5 B1 C1] ace [V5 B1 C1] nv8  line N;	\u0308\u200C\u0308\u0628b;	[V5 B1 C1];	[V5 B1 C1];		#	̈‌̈بb
 */
/* punt1 */
/* 3 source a\u0628\u0308\u200C\u0308 uni [B5 B6 C1] ace [B5 B6 C1] nv8  line N;	a\u0628\u0308\u200C\u0308;	[B5 B6 C1];	[B5 B6 C1];		#	aب̈‌̈
 */
/* punt1 */
/* 3 source a\u0628\u0308\u200C\u0308\u0628b uni [B5] ace [B5] nv8  line B;	a\u0628\u0308\u200C\u0308\u0628b;	[B5];	[B5];		#	aب̈‌̈بb
 */
/* punt1 */
/* 3 source ¡ uni ¡ ace xn--7a nv8 NV8 line B;	¡;	;	xn--7a;	NV8
 */
{ "¡", "xn--7a", IDN2_DISALLOWED },
/* 4 source www.eXample.cOm uni www.example.com ace www.example.com nv8  line B;	www.eXample.cOm;	www.example.com;	;	
 */
{ "www.example.com", "www.example.com", IDN2_OK },
/* 5 source Bücher.de uni bücher.de ace xn--bcher-kva.de nv8  line B;	Bücher.de;	bücher.de;	xn--bcher-kva.de;	
 */
{ "bücher.de", "xn--bcher-kva.de", IDN2_OK },
/* 6 source ÖBB uni öbb ace xn--bb-eka nv8  line B;	ÖBB;	öbb;	xn--bb-eka;	
 */
{ "öbb", "xn--bb-eka", IDN2_OK },
/* 7 source XN--fA-hia.dE uni faß.de ace xn--fa-hia.de nv8  line B;	XN--fA-hia.dE;	faß.de;	xn--fa-hia.de;	
 */
{ "faß.de", "xn--fa-hia.de", IDN2_OK },
/* 8 source βόλος.com uni βόλος.com ace xn--nxasmm1c.com nv8  line N;	βόλος.com;	;	xn--nxasmm1c.com;	
 */
{ "βόλος.com", "xn--nxasmm1c.com", IDN2_OK },
/* 9 source ΒΌΛΟΣ.COM uni βόλοσ.com ace xn--nxasmq6b.com nv8  line B;	ΒΌΛΟΣ.COM;	βόλοσ.com;	xn--nxasmq6b.com;	
 */
{ "βόλοσ.com", "xn--nxasmq6b.com", IDN2_OK },
/* 10 source Βόλος.com uni βόλος.com ace xn--nxasmm1c.com nv8  line N;	Βόλος.com;	βόλος.com;	xn--nxasmm1c.com;	
 */
{ "βόλος.com", "xn--nxasmm1c.com", IDN2_OK },
/* 11 source xn--nxasmm1c uni βόλος ace xn--nxasmm1c nv8  line B;	xn--nxasmm1c;	βόλος;	xn--nxasmm1c;	
 */
{ "βόλος", "xn--nxasmm1c", IDN2_OK },
/* 12 source ΒΌΛΟΣ uni βόλοσ ace xn--nxasmq6b nv8  line B;	ΒΌΛΟΣ;	βόλοσ;	xn--nxasmq6b;	
 */
{ "βόλοσ", "xn--nxasmq6b", IDN2_OK },
/* 13 source Βόλος uni βόλος ace xn--nxasmm1c nv8  line N;	Βόλος;	βόλος;	xn--nxasmm1c;	
 */
{ "βόλος", "xn--nxasmm1c", IDN2_OK },
/* 14 source \u0646\u0627\u0645\u0647\u200C\u0627\u06CC uni \u0646\u0627\u0645\u0647\u200C\u0627\u06CC ace xn--mgba3gch31f060k nv8  line N;	\u0646\u0627\u0645\u0647\u200C\u0627\u06CC;	;	xn--mgba3gch31f060k;		#	نامه‌ای
 */
{ "\u0646\u0627\u0645\u0647\u200C\u0627\u06CC", "xn--mgba3gch31f060k", IDN2_OK },
/* 15 source xn--mgba3gch31f uni \u0646\u0627\u0645\u0647\u0627\u06CC ace xn--mgba3gch31f nv8  line B;	xn--mgba3gch31f;	\u0646\u0627\u0645\u0647\u0627\u06CC;	xn--mgba3gch31f;		#	نامهای
 */
{ "\u0646\u0627\u0645\u0647\u0627\u06CC", "xn--mgba3gch31f", IDN2_OK },
/* 16 source xn--mgba3gch31f060k uni \u0646\u0627\u0645\u0647\u200C\u0627\u06CC ace xn--mgba3gch31f060k nv8  line B;	xn--mgba3gch31f060k;	\u0646\u0627\u0645\u0647\u200C\u0627\u06CC;	xn--mgba3gch31f060k;		#	نامه‌ای
 */
{ "\u0646\u0627\u0645\u0647\u200C\u0627\u06CC", "xn--mgba3gch31f060k", IDN2_OK },
/* 17 source xn--mgba3gch31f060k.com uni \u0646\u0627\u0645\u0647\u200C\u0627\u06CC.com ace xn--mgba3gch31f060k.com nv8  line B;	xn--mgba3gch31f060k.com;	\u0646\u0627\u0645\u0647\u200C\u0627\u06CC.com;	xn--mgba3gch31f060k.com;		#	نامه‌ای.com
 */
{ "\u0646\u0627\u0645\u0647\u200C\u0627\u06CC.com", "xn--mgba3gch31f060k.com", IDN2_OK },
/* 18 source xn--mgba3gch31f.com uni \u0646\u0627\u0645\u0647\u0627\u06CC.com ace xn--mgba3gch31f.com nv8  line B;	xn--mgba3gch31f.com;	\u0646\u0627\u0645\u0647\u0627\u06CC.com;	xn--mgba3gch31f.com;		#	نامهای.com
 */
{ "\u0646\u0627\u0645\u0647\u0627\u06CC.com", "xn--mgba3gch31f.com", IDN2_OK },
/* 19 source a.b．c。d｡ uni a.b.c.d. ace a.b.c.d. nv8  line B;	a.b．c。d｡;	a.b.c.d.;	;	
 */
{ "a.b.c.d.", "a.b.c.d.", IDN2_OK },
/* 20 source U\u0308.xn--tda uni ü.ü ace xn--tda.xn--tda nv8  line B;	U\u0308.xn--tda;	ü.ü;	xn--tda.xn--tda;	
 */
{ "ü.ü", "xn--tda.xn--tda", IDN2_OK },
/* 21 source xn--u-ccb uni [V1] ace [V1] nv8  line B;	xn--u-ccb;	[V1];	[V1];		#	ü
 */
/* punt1 */
/* 21 source a⒈com uni [P1 V6] ace [P1 V6] nv8  line B;	a⒈com;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 21 source xn--a-ecp.ru uni [V6] ace [V6] nv8  line B;	xn--a-ecp.ru;	[V6];	[V6];	
 */
/* punt1 */
/* 21 source xn--0.pt uni [A3] ace [A3] nv8  line B;	xn--0.pt;	[A3];	[A3];	
 */
/* punt1 */
/* 21 source xn--a.pt uni [V6] ace [V6] nv8  line B;	xn--a.pt;	[V6];	[V6];		#	.pt
 */
/* punt1 */
/* 21 source xn--a-Ä.pt uni [A3] ace [A3] nv8  line B;	xn--a-Ä.pt;	[A3];	[A3];	
 */
/* punt1 */
/* 21 source 日本語。ＪＰ uni 日本語.jp ace xn--wgv71a119e.jp nv8  line B;	日本語。ＪＰ;	日本語.jp;	xn--wgv71a119e.jp;	
 */
{ "日本語.jp", "xn--wgv71a119e.jp", IDN2_OK },
/* 22 source ☕ uni ☕ ace xn--53h nv8 NV8 line B;	☕;	;	xn--53h;	NV8
 */
{ "☕", "xn--53h", IDN2_DISALLOWED },
/* 23 source xn--bss uni 夙 ace xn--bss nv8  line B;	xn--bss;	夙;	xn--bss;	
 */
{ "夙", "xn--bss", IDN2_OK },
/* 24 source xn--bssffl uni 夡夞夜夙 ace xn--bssffl nv8  line B;	xn--bssffl;	夡夞夜夙;	xn--bssffl;	
 */
{ "夡夞夜夙", "xn--bssffl", IDN2_OK },
/* 25 source a.b..-q--a-.e uni [V2 V3] ace [V2 V3 A4_2] nv8  line B;	a.b..-q--a-.e;	[V2 V3];	[V2 V3 A4_2];	
 */
/* punt1 */
/* 25 source a..c uni a..c ace [A4_2] nv8  line B;	a..c;	;	[A4_2];	
 */
/* punt1 */
/* 25 source a.-b. uni [V3] ace [V3] nv8  line B;	a.-b.;	[V3];	[V3];	
 */
/* punt1 */
/* 25 source a.bc--de.f uni [V2] ace [V2] nv8  line B;	a.bc--de.f;	[V2];	[V2];	
 */
/* punt1 */
/* 25 source ä..c uni ä..c ace [A4_2] nv8  line B;	ä..c;	;	[A4_2];	
 */
/* punt1 */
/* 25 source ä.-b. uni [V3] ace [V3] nv8  line B;	ä.-b.;	[V3];	[V3];	
 */
/* punt1 */
/* 25 source ä.bc--de.f uni [V2] ace [V2] nv8  line B;	ä.bc--de.f;	[V2];	[V2];	
 */
/* punt1 */
/* 25 source a.b.\u0308c.d uni [V5] ace [V5] nv8  line B;	a.b.\u0308c.d;	[V5];	[V5];		#	a.b.̈c.d
 */
/* punt1 */
/* 25 source A0 uni a0 ace a0 nv8  line B;	A0;	a0;	;	
 */
{ "a0", "a0", IDN2_OK },
/* 26 source 0A uni 0a ace 0a nv8  line B;	0A;	0a;	;	
 */
{ "0a", "0a", IDN2_OK },
/* 27 source c.xn--0-eha.xn--4db uni [B1] ace [B1] nv8  line B;	c.xn--0-eha.xn--4db;	[B1];	[B1];		#	c.0ü.א
 */
/* punt1 */
/* 27 source d.xn----dha.xn--4db uni [V3 B6] ace [V3 B6] nv8  line B;	d.xn----dha.xn--4db;	[V3 B6];	[V3 B6];		#	d.ü-.א
 */
/* punt1 */
/* 27 source a7\u0667z uni [B5] ace [B5] nv8  line B;	a7\u0667z;	[B5];	[B5];		#	a7٧z
 */
/* punt1 */
/* 27 source xn--dmc uni ஹ ace xn--dmc nv8  line B;	xn--dmc;	ஹ;	xn--dmc;	
 */
{ "ஹ", "xn--dmc", IDN2_OK },
/* 28 source  uni  ace  nv8  line B;	;	;	;	
 */
{ "", "", IDN2_OK },
/* 29 source ஹ\u200C uni [C1] ace [C1] nv8  line N;	ஹ\u200C;	[C1];	[C1];		#	ஹ‌
 */
/* punt1 */
/* 29 source \u0644\u0670\u200C\u06EF uni \u0644\u0670\u200C\u06EF ace xn--ghb2g3qq34f nv8  line N;	\u0644\u0670\u200C\u06EF;	;	xn--ghb2g3qq34f;		#	لٰ‌ۯ
 */
{ "\u0644\u0670\u200C\u06EF", "xn--ghb2g3qq34f", IDN2_OK },
/* 30 source xn--ghb2g3q uni \u0644\u0670\u06EF ace xn--ghb2g3q nv8  line B;	xn--ghb2g3q;	\u0644\u0670\u06EF;	xn--ghb2g3q;		#	لٰۯ
 */
{ "\u0644\u0670\u06EF", "xn--ghb2g3q", IDN2_OK },
/* 31 source xn--ghb2g3qq34f uni \u0644\u0670\u200C\u06EF ace xn--ghb2g3qq34f nv8  line B;	xn--ghb2g3qq34f;	\u0644\u0670\u200C\u06EF;	xn--ghb2g3qq34f;		#	لٰ‌ۯ
 */
{ "\u0644\u0670\u200C\u06EF", "xn--ghb2g3qq34f", IDN2_OK },
/* 32 source \u0644\u200C\u06EF uni \u0644\u200C\u06EF ace xn--ghb65a953d nv8  line N;	\u0644\u200C\u06EF;	;	xn--ghb65a953d;		#	ل‌ۯ
 */
{ "\u0644\u200C\u06EF", "xn--ghb65a953d", IDN2_OK },
/* 33 source xn--ghb65a uni \u0644\u06EF ace xn--ghb65a nv8  line B;	xn--ghb65a;	\u0644\u06EF;	xn--ghb65a;		#	لۯ
 */
{ "\u0644\u06EF", "xn--ghb65a", IDN2_OK },
/* 34 source xn--ghb65a953d uni \u0644\u200C\u06EF ace xn--ghb65a953d nv8  line B;	xn--ghb65a953d;	\u0644\u200C\u06EF;	xn--ghb65a953d;		#	ل‌ۯ
 */
{ "\u0644\u200C\u06EF", "xn--ghb65a953d", IDN2_OK },
/* 35 source \u06EF\u200C\u06EF uni [C1] ace [C1] nv8  line N;	\u06EF\u200C\u06EF;	[C1];	[C1];		#	ۯ‌ۯ
 */
/* punt1 */
/* 35 source xn--cmba uni \u06EF\u06EF ace xn--cmba nv8  line B;	xn--cmba;	\u06EF\u06EF;	xn--cmba;		#	ۯۯ
 */
{ "\u06EF\u06EF", "xn--cmba", IDN2_OK },
/* 36 source \u0644\u200C uni [B3 C1] ace [B3 C1] nv8  line N;	\u0644\u200C;	[B3 C1];	[B3 C1];		#	ل‌
 */
/* punt1 */
/* 36 source xn--ghb uni \u0644 ace xn--ghb nv8  line B;	xn--ghb;	\u0644;	xn--ghb;		#	ل
 */
{ "\u0644", "xn--ghb", IDN2_OK },
/* 37 source \u200C趜 uni [C1] ace [C1] nv8  line N;	\u200C趜;	[C1];	[C1];		#	‌趜
 */
/* punt1 */
/* 37 source xn--er3a uni 趜 ace xn--er3a nv8  line B;	xn--er3a;	趜;	xn--er3a;	
 */
{ "趜", "xn--er3a", IDN2_OK },
/* 38 source ≮㊻｡- uni [P1 V6 V3] ace [P1 V6 V3] nv8  line B;	≮㊻｡-;	[P1 V6 V3];	[P1 V6 V3];	
 */
/* punt1 */
/* 38 source 🄅\u0660．≠ uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	🄅\u0660．≠;	[P1 V6 B1];	[P1 V6 B1];		#	🄅٠.≠
 */
/* punt1 */
/* 38 source 𝟠 uni 8 ace 8 nv8  line B;	𝟠;	8;	;	
 */
{ "8", "8", IDN2_OK },
/* 39 source ≠ uni [P1 V6] ace [P1 V6] nv8  line B;	≠;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 39 source \uABE5뙃.\uA953- uni [V5 V3] ace [V5 V3] nv8  line B;	\uABE5뙃.\uA953-;	[V5 V3];	[V5 V3];		#	ꯥ뙃.꥓-
 */
/* punt1 */
/* 39 source \u06AA窮⒈ uni [P1 V6 B2] ace [P1 V6 B2] nv8  line B;	\u06AA窮⒈;	[P1 V6 B2];	[P1 V6 B2];		#	ڪ窮⒈
 */
/* punt1 */
/* 39 source \u0768\u079B\u0644\u06CE．𝟕 uni [B1] ace [B1] nv8  line B;	\u0768\u079B\u0644\u06CE．𝟕;	[B1];	[B1];		#	ݨޛلێ.7
 */
/* punt1 */
/* 39 source -．\u200C uni [V3 C1] ace [V3 C1] nv8  line N;	-．\u200C;	[V3 C1];	[V3 C1];		#	-.‌
 */
/* punt1 */
/* 39 source 𥛋\u200C\u08A0\uA9C0｡ß\u200C uni [P1 V6 B5 B6 C1] ace [P1 V6 B5 B6 C1] nv8  line N;	𥛋\u200C\u08A0\uA9C0｡ß\u200C;	[P1 V6 B5 B6 C1];	[P1 V6 B5 B6 C1];		#	𥛋‌ࢠ꧀.ß‌
 */
/* punt1 */
/* 39 source 𝟲．Ⴓ uni [P1 V6] ace [P1 V6] nv8  line B;	𝟲．Ⴓ;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 39 source 𝟲．ⴓ uni 6.ⴓ ace 6.xn--blj nv8  line B;	𝟲．ⴓ;	6.ⴓ;	6.xn--blj;	
 */
{ "6.ⴓ", "6.xn--blj", IDN2_OK },
/* 40 source 6.Ⴓ uni [P1 V6] ace [P1 V6] nv8  line B;	6.Ⴓ;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 40 source \u0E4E uni [V5] ace [V5] nv8  line B;	\u0E4E;	[V5];	[V5];		#	๎
 */
/* punt1 */
/* 40 source 婬\u1A65 uni 婬\u1A65 ace xn--oof8190a nv8  line B;	婬\u1A65;	;	xn--oof8190a;		#	婬ᩥ
 */
{ "婬\u1A65", "xn--oof8190a", IDN2_OK },
/* 41 source \u0659-- uni [V3 V5] ace [V3 V5] nv8  line B;	\u0659--;	[V3 V5];	[V3 V5];		#	ٙ--
 */
/* punt1 */
/* 41 source xn--ss8-rk1b.xn--dnb8p986g uni ⴟss8.\u0713⩃\u076F ace xn--ss8-rk1b.xn--dnb8p986g nv8 NV8 line B;	xn--ss8-rk1b.xn--dnb8p986g;	ⴟss8.\u0713⩃\u076F;	xn--ss8-rk1b.xn--dnb8p986g;	NV8	#	ⴟss8.ܓ⩃ݯ
 */
{ "ⴟss8.\u0713⩃\u076F", "xn--ss8-rk1b.xn--dnb8p986g", IDN2_DISALLOWED },
/* 42 source ႿSS8.\u0713⩃\u076F uni [P1 V6] ace [P1 V6] nv8  line B;	ႿSS8.\u0713⩃\u076F;	[P1 V6];	[P1 V6];		#	Ⴟss8.ܓ⩃ݯ
 */
/* punt1 */
/* 42 source xn--8-pfa7905a.xn--dnb8p986g uni ⴟß8.\u0713⩃\u076F ace xn--8-pfa7905a.xn--dnb8p986g nv8 NV8 line B;	xn--8-pfa7905a.xn--dnb8p986g;	ⴟß8.\u0713⩃\u076F;	xn--8-pfa7905a.xn--dnb8p986g;	NV8	#	ⴟß8.ܓ⩃ݯ
 */
{ "ⴟß8.\u0713⩃\u076F", "xn--8-pfa7905a.xn--dnb8p986g", IDN2_DISALLOWED },
/* 43 source Ⴟß8.\u0713⩃\u076F uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴟß8.\u0713⩃\u076F;	[P1 V6];	[P1 V6];		#	Ⴟß8.ܓ⩃ݯ
 */
/* punt1 */
/* 43 source ӏ｡㽟 uni ӏ.㽟 ace xn--s5a.xn--4en nv8  line B;	ӏ｡㽟;	ӏ.㽟;	xn--s5a.xn--4en;	
 */
{ "ӏ.㽟", "xn--s5a.xn--4en", IDN2_OK },
/* 44 source Ӏ.㽟 uni [P1 V6] ace [P1 V6] nv8  line B;	Ӏ.㽟;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 44 source \u0320\u200C≠\u200C uni [P1 V5 V6 C1] ace [P1 V5 V6 C1] nv8  line N;	\u0320\u200C≠\u200C;	[P1 V5 V6 C1];	[P1 V5 V6 C1];		#	̠‌≠‌
 */
/* punt1 */
/* 44 source \u0697\u0638\u200C uni [B3 C1] ace [B3 C1] nv8  line N;	\u0697\u0638\u200C;	[B3 C1];	[B3 C1];		#	ڗظ‌
 */
/* punt1 */
/* 44 source xn--3gb3q uni \u0697\u0638 ace xn--3gb3q nv8  line B;	xn--3gb3q;	\u0697\u0638;	xn--3gb3q;		#	ڗظ
 */
{ "\u0697\u0638", "xn--3gb3q", IDN2_OK },
/* 45 source 籡。\u103AႠ\u0620 uni [P1 V5 V6 B1] ace [P1 V5 V6 B1] nv8  line B;	籡。\u103AႠ\u0620;	[P1 V5 V6 B1];	[P1 V5 V6 B1];		#	籡.်Ⴀؠ
 */
/* punt1 */
/* 45 source 籡。\u103Aⴀ\u0620 uni [V5 B1] ace [V5 B1] nv8  line B;	籡。\u103Aⴀ\u0620;	[V5 B1];	[V5 B1];		#	籡.်ⴀؠ
 */
/* punt1 */
/* 45 source ς\u1714 uni ς\u1714 ace xn--3xa600h nv8  line N;	ς\u1714;	;	xn--3xa600h;		#	ς᜔
 */
{ "ς\u1714", "xn--3xa600h", IDN2_OK },
/* 46 source Σ\u1714 uni σ\u1714 ace xn--4xa400h nv8  line B;	Σ\u1714;	σ\u1714;	xn--4xa400h;		#	σ᜔
 */
{ "σ\u1714", "xn--4xa400h", IDN2_OK },
/* 47 source xn--3xa600h uni ς\u1714 ace xn--3xa600h nv8  line B;	xn--3xa600h;	ς\u1714;	xn--3xa600h;		#	ς᜔
 */
{ "ς\u1714", "xn--3xa600h", IDN2_OK },
/* 48 source \uA8E2 uni [V5] ace [V5] nv8  line B;	\uA8E2;	[V5];	[V5];		#	꣢
 */
/* punt1 */
/* 48 source Ⴐ≮ uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴐ≮;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 48 source \u1036\u06A9-\u1060 uni [V5 B1] ace [V5 B1] nv8  line B;	\u1036\u06A9-\u1060;	[V5 B1];	[V5 B1];		#	ံک-ၠ
 */
/* punt1 */
/* 48 source \u0753🄅 uni [P1 V6] ace [P1 V6] nv8  line B;	\u0753🄅;	[P1 V6];	[P1 V6];		#	ݓ🄅
 */
/* punt1 */
/* 48 source \u1920\uFB94 uni [V5 B1] ace [V5 B1] nv8  line B;	\u1920\uFB94;	[V5 B1];	[V5 B1];		#	ᤠگ
 */
/* punt1 */
/* 48 source \u066B uni [B1] ace [B1] nv8  line B;	\u066B;	[B1];	[B1];		#	٫
 */
/* punt1 */
/* 48 source Ⴡ- uni [P1 V3 V6] ace [P1 V3 V6] nv8  line B;	Ⴡ-;	[P1 V3 V6];	[P1 V3 V6];	
 */
/* punt1 */
/* 48 source ⴡ- uni [V3] ace [V3] nv8  line B;	ⴡ-;	[V3];	[V3];	
 */
/* punt1 */
/* 48 source \u07AF⁸\uAB1A\u076B uni [P1 V5 V6 B1] ace [P1 V5 V6 B1] nv8  line B;	\u07AF⁸\uAB1A\u076B;	[P1 V5 V6 B1];	[P1 V5 V6 B1];		#	ޯ8꬚ݫ
 */
/* punt1 */
/* 48 source ⒈\u033C⒐Ⴍ｡ヸ uni [P1 V6] ace [P1 V6] nv8  line B;	⒈\u033C⒐Ⴍ｡ヸ;	[P1 V6];	[P1 V6];		#	⒈̼⒐Ⴍ.ヸ
 */
/* punt1 */
/* 48 source \u200C\uA94AႰ\u0645 uni [P1 V6 B1 C1] ace [P1 V6 B1 C1] nv8  line N;	\u200C\uA94AႰ\u0645;	[P1 V6 B1 C1];	[P1 V6 B1 C1];		#	‌ꥊႰم
 */
/* punt1 */
/* 48 source \u200C\uA94Aⴐ\u0645 uni [B1 C1] ace [B1 C1] nv8  line N;	\u200C\uA94Aⴐ\u0645;	[B1 C1];	[B1 C1];		#	‌ꥊⴐم
 */
/* punt1 */
/* 48 source xn--1kjp uni ⴒⴊ ace xn--1kjp nv8  line B;	xn--1kjp;	ⴒⴊ;	xn--1kjp;	
 */
{ "ⴒⴊ", "xn--1kjp", IDN2_OK },
/* 49 source ႲႪ uni [P1 V6] ace [P1 V6] nv8  line B;	ႲႪ;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 49 source ≮\u075E uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	≮\u075E;	[P1 V6 B1];	[P1 V6 B1];		#	≮ݞ
 */
/* punt1 */
/* 49 source \u0632\u073C uni \u0632\u073C ace xn--xgb64c nv8  line B;	\u0632\u073C;	;	xn--xgb64c;		#	زܼ
 */
{ "\u0632\u073C", "xn--xgb64c", IDN2_OK },
/* 50 source xn--mkb uni \u06B3 ace xn--mkb nv8  line B;	xn--mkb;	\u06B3;	xn--mkb;		#	ڳ
 */
{ "\u06B3", "xn--mkb", IDN2_OK },
/* 51 source \u200C🄅 uni [P1 V6 C1] ace [P1 V6 C1] nv8  line N;	\u200C🄅;	[P1 V6 C1];	[P1 V6 C1];		#	‌🄅
 */
/* punt1 */
/* 51 source - uni [V3] ace [V3] nv8  line B;	-;	[V3];	[V3];	
 */
/* punt1 */
/* 51 source \u0768ᳰ uni [B2 B3] ace [B2 B3] nv8  line B;	\u0768ᳰ;	[B2 B3];	[B2 B3];		#	ݨᳰ
 */
/* punt1 */
/* 51 source Ⴌ⒈.\u0347\u0FA5 uni [P1 V6 V5] ace [P1 V6 V5] nv8  line B;	Ⴌ⒈.\u0347\u0FA5;	[P1 V6 V5];	[P1 V6 V5];		#	Ⴌ⒈.͇ྥ
 */
/* punt1 */
/* 51 source 鮌 uni 鮌 ace xn--co6a nv8  line B;	鮌;	;	xn--co6a;	
 */
{ "鮌", "xn--co6a", IDN2_OK },
/* 52 source ≮．⒗Ӏ uni [P1 V6] ace [P1 V6] nv8  line B;	≮．⒗Ӏ;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 52 source \u1B3A．뜚 uni [V5] ace [V5] nv8  line B;	\u1B3A．뜚;	[V5];	[V5];		#	ᬺ.뜚
 */
/* punt1 */
/* 52 source \uFC79⋓ uni [B3] ace [B3] nv8  line B;	\uFC79⋓;	[B3];	[B3];		#	ثن⋓
 */
/* punt1 */
/* 52 source ß uni ß ace xn--zca nv8  line N;	ß;	;	xn--zca;	
 */
{ "ß", "xn--zca", IDN2_OK },
/* 53 source SS uni ss ace ss nv8  line B;	SS;	ss;	;	
 */
{ "ss", "ss", IDN2_OK },
/* 54 source xn--zca uni ß ace xn--zca nv8  line B;	xn--zca;	ß;	xn--zca;	
 */
{ "ß", "xn--zca", IDN2_OK },
/* 55 source \u05A8\u0756\u200C uni [V5 B1 C1] ace [V5 B1 C1] nv8  line N;	\u05A8\u0756\u200C;	[V5 B1 C1];	[V5 B1 C1];		#	֨ݖ‌
 */
/* punt1 */
/* 55 source Ⴋ uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴋ;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 55 source ⴋ uni ⴋ ace xn--2kj nv8  line B;	ⴋ;	;	xn--2kj;	
 */
{ "ⴋ", "xn--2kj", IDN2_OK },
/* 56 source \u1772\uFCBB｡\u0360\u0726䜀\u200C uni [V5 B1 C1] ace [V5 B1 C1] nv8  line N;	\u1772\uFCBB｡\u0360\u0726䜀\u200C;	[V5 B1 C1];	[V5 B1 C1];		#	ᝲعم.͠ܦ䜀‌
 */
/* punt1 */
/* 56 source \u0776 uni \u0776 ace xn--6pb nv8  line B;	\u0776;	;	xn--6pb;		#	ݶ
 */
{ "\u0776", "xn--6pb", IDN2_OK },
/* 57 source 옔︒ uni [P1 V6] ace [P1 V6] nv8  line B;	옔︒;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 57 source \u0664≠ uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	\u0664≠;	[P1 V6 B1];	[P1 V6 B1];		#	٤≠
 */
/* punt1 */
/* 57 source ₅。𝟝 uni 5.5 ace 5.5 nv8  line B;	₅。𝟝;	5.5;	;	
 */
{ "5.5", "5.5", IDN2_OK },
/* 58 source \u076B．\uFE26\u05AF uni [V5 B1 B3 B6] ace [V5 B1 B3 B6] nv8  line B;	\u076B．\uFE26\u05AF;	[V5 B1 B3 B6];	[V5 B1 B3 B6];		#	ݫ.︦֯
 */
/* punt1 */
/* 58 source \u0C47 uni [V5] ace [V5] nv8  line B;	\u0C47;	[V5];	[V5];		#	ే
 */
/* punt1 */
/* 58 source -．ς uni [V3] ace [V3] nv8  line B;	-．ς;	[V3];	[V3];	
 */
/* punt1 */
/* 58 source \uA9BC uni [V5] ace [V5] nv8  line B;	\uA9BC;	[V5];	[V5];		#	ꦼ
 */
/* punt1 */
/* 58 source 𝌹\u0625璲쀲。︒≯𪤘 uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	𝌹\u0625璲쀲。︒≯𪤘;	[P1 V6 B1];	[P1 V6 B1];		#	𝌹إ璲쀲.︒≯𪤘
 */
/* punt1 */
/* 58 source \u0664 uni [B1] ace [B1] nv8  line B;	\u0664;	[B1];	[B1];		#	٤
 */
/* punt1 */
/* 58 source \u08EC≠ uni [P1 V6 B3] ace [P1 V6 B3] nv8  line B;	\u08EC≠;	[P1 V6 B3];	[P1 V6 B3];		#	࣬≠
 */
/* punt1 */
/* 58 source \uA981 uni [V5] ace [V5] nv8  line B;	\uA981;	[V5];	[V5];		#	ꦁ
 */
/* punt1 */
/* 58 source xn--hlj.xn--bhb uni ⴙ.\u063F ace xn--hlj.xn--bhb nv8  line B;	xn--hlj.xn--bhb;	ⴙ.\u063F;	xn--hlj.xn--bhb;		#	ⴙ.ؿ
 */
{ "ⴙ.\u063F", "xn--hlj.xn--bhb", IDN2_OK },
/* 59 source Ⴙ.\u063F uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴙ.\u063F;	[P1 V6];	[P1 V6];		#	Ⴙ.ؿ
 */
/* punt1 */
/* 59 source ⴓ uni ⴓ ace xn--blj nv8  line B;	ⴓ;	;	xn--blj;	
 */
{ "ⴓ", "xn--blj", IDN2_OK },
/* 60 source ≠ß≯。𝟪𤓑\u07EA쨯 uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	≠ß≯。𝟪𤓑\u07EA쨯;	[P1 V6 B1];	[P1 V6 B1];		#	≠ß≯.8𤓑ߪ쨯
 */
/* punt1 */
/* 60 source ۳ uni ۳ ace xn--gmb nv8  line B;	۳;	;	xn--gmb;	
 */
{ "۳", "xn--gmb", IDN2_OK },
/* 61 source \u068F uni \u068F ace xn--ljb nv8  line B;	\u068F;	;	xn--ljb;		#	ڏ
 */
{ "\u068F", "xn--ljb", IDN2_OK },
/* 62 source 𝟯 uni 3 ace 3 nv8  line B;	𝟯;	3;	;	
 */
{ "3", "3", IDN2_OK },
/* 63 source ≮ uni [P1 V6] ace [P1 V6] nv8  line B;	≮;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 63 source ς₇｡숝 uni ς7.숝 ace xn--7-xmb.xn--fq4b nv8  line N;	ς₇｡숝;	ς7.숝;	xn--7-xmb.xn--fq4b;	
 */
{ "ς7.숝", "xn--7-xmb.xn--fq4b", IDN2_OK },
/* 64 source Σ₇｡숝 uni σ7.숝 ace xn--7-zmb.xn--fq4b nv8  line B;	Σ₇｡숝;	σ7.숝;	xn--7-zmb.xn--fq4b;	
 */
{ "σ7.숝", "xn--7-zmb.xn--fq4b", IDN2_OK },
/* 65 source xn--7-xmb.xn--fq4b uni ς7.숝 ace xn--7-xmb.xn--fq4b nv8  line B;	xn--7-xmb.xn--fq4b;	ς7.숝;	xn--7-xmb.xn--fq4b;	
 */
{ "ς7.숝", "xn--7-xmb.xn--fq4b", IDN2_OK },
/* 66 source -⒈ uni [P1 V3 V6] ace [P1 V3 V6] nv8  line B;	-⒈;	[P1 V3 V6];	[P1 V3 V6];	
 */
/* punt1 */
/* 66 source ႩႤ．⒐\u068A\u0722 uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	ႩႤ．⒐\u068A\u0722;	[P1 V6 B1];	[P1 V6 B1];		#	ႩႤ.⒐ڊܢ
 */
/* punt1 */
/* 66 source ⒈。\u200C\u0FB0 uni [P1 V6 C1] ace [P1 V6 C1] nv8  line N;	⒈。\u200C\u0FB0;	[P1 V6 C1];	[P1 V6 C1];		#	⒈.‌ྰ
 */
/* punt1 */
/* 66 source ❘\u0728۵ uni [B1] ace [B1] nv8  line B;	❘\u0728۵;	[B1];	[B1];		#	❘ܨ۵
 */
/* punt1 */
/* 66 source \u0761\u07CF uni \u0761\u07CF ace xn--lpb4t nv8  line B;	\u0761\u07CF;	;	xn--lpb4t;		#	ݡߏ
 */
{ "\u0761\u07CF", "xn--lpb4t", IDN2_OK },
/* 67 source ⒍\u077F\u06C3 uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	⒍\u077F\u06C3;	[P1 V6 B1];	[P1 V6 B1];		#	⒍ݿۃ
 */
/* punt1 */
/* 67 source -乘 uni [V3] ace [V3] nv8  line B;	-乘;	[V3];	[V3];	
 */
/* punt1 */
/* 67 source ⾕ uni 谷 ace xn--6g3a nv8  line B;	⾕;	谷;	xn--6g3a;	
 */
{ "谷", "xn--6g3a", IDN2_OK },
/* 68 source ᵀ\u1BAA uni t\u1BAA ace xn--t-oml nv8  line B;	ᵀ\u1BAA;	t\u1BAA;	xn--t-oml;		#	t᮪
 */
{ "t\u1BAA", "xn--t-oml", IDN2_OK },
/* 69 source \u08AB uni [P1 V6] ace [P1 V6] nv8  line B;	\u08AB;	[P1 V6];	[P1 V6];		#	ࢫ
 */
/* punt1 */
/* 69 source 폁 uni 폁 ace xn--gf8b nv8  line B;	폁;	;	xn--gf8b;	
 */
{ "폁", "xn--gf8b", IDN2_OK },
/* 70 source ς⋄｡\u200C uni [C1] ace [C1] nv8  line N;	ς⋄｡\u200C;	[C1];	[C1];		#	ς⋄.‌
 */
/* punt1 */
/* 70 source xn--4xa889m. uni σ⋄. ace xn--4xa889m. nv8 NV8 line B;	xn--4xa889m.;	σ⋄.;	xn--4xa889m.;	NV8
 */
{ "σ⋄.", "xn--4xa889m.", IDN2_DISALLOWED },
/* 71 source xn--rlj. uni ⴣ. ace xn--rlj. nv8  line B;	xn--rlj.;	ⴣ.;	xn--rlj.;	
 */
{ "ⴣ.", "xn--rlj.", IDN2_OK },
/* 72 source Ⴣ. uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴣ.;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 72 source \u069B uni \u069B ace xn--xjb nv8  line B;	\u069B;	;	xn--xjb;		#	ڛ
 */
{ "\u069B", "xn--xjb", IDN2_OK },
/* 73 source Ⴒ uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴒ;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 73 source ⴒ uni ⴒ ace xn--9kj nv8  line B;	ⴒ;	;	xn--9kj;	
 */
{ "ⴒ", "xn--9kj", IDN2_OK },
/* 74 source \u17B5ς uni [P1 V6] ace [P1 V6] nv8  line B;	\u17B5ς;	[P1 V6];	[P1 V6];		#	឵ς
 */
/* punt1 */
/* 74 source \u06A7｡\u06BA uni \u06A7.\u06BA ace xn--9jb.xn--tkb nv8  line B;	\u06A7｡\u06BA;	\u06A7.\u06BA;	xn--9jb.xn--tkb;		#	ڧ.ں
 */
{ "\u06A7.\u06BA", "xn--9jb.xn--tkb", IDN2_OK },
/* 75 source ⾆ uni 舌 ace xn--tc1a nv8  line B;	⾆;	舌;	xn--tc1a;	
 */
{ "舌", "xn--tc1a", IDN2_OK },
/* 76 source 턴≠ uni [P1 V6] ace [P1 V6] nv8  line B;	턴≠;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 76 source \u1CE4.\u1058\u066E\u0C04 uni [P1 V5 V6 B1 B3 B6] ace [P1 V5 V6 B1 B3 B6] nv8  line B;	\u1CE4.\u1058\u066E\u0C04;	[P1 V5 V6 B1 B3 B6];	[P1 V5 V6 B1 B3 B6];		#	᳤.ၘٮఄ
 */
/* punt1 */
/* 76 source \u06B3Ⴙ.ς\u200C uni [P1 V6 B2 B3 B6 C1] ace [P1 V6 B2 B3 B6 C1] nv8  line N;	\u06B3Ⴙ.ς\u200C;	[P1 V6 B2 B3 B6 C1];	[P1 V6 B2 B3 B6 C1];		#	ڳႹ.ς‌
 */
/* punt1 */
/* 76 source \u06B3ⴙ.ς\u200C uni [B2 B3 B6 C1] ace [B2 B3 B6 C1] nv8  line N;	\u06B3ⴙ.ς\u200C;	[B2 B3 B6 C1];	[B2 B3 B6 C1];		#	ڳⴙ.ς‌
 */
/* punt1 */
/* 76 source \u06B3Ⴙ.Σ\u200C uni [P1 V6 B2 B3 B6 C1] ace [P1 V6 B2 B3 B6 C1] nv8  line N;	\u06B3Ⴙ.Σ\u200C;	[P1 V6 B2 B3 B6 C1];	[P1 V6 B2 B3 B6 C1];		#	ڳႹ.σ‌
 */
/* punt1 */
/* 76 source \u06B3ⴙ.σ\u200C uni [B2 B3 B6 C1] ace [B2 B3 B6 C1] nv8  line N;	\u06B3ⴙ.σ\u200C;	[B2 B3 B6 C1];	[B2 B3 B6 C1];		#	ڳⴙ.σ‌
 */
/* punt1 */
/* 76 source \u06B3Ⴙ.σ\u200C uni [P1 V6 B2 B3 B6 C1] ace [P1 V6 B2 B3 B6 C1] nv8  line N;	\u06B3Ⴙ.σ\u200C;	[P1 V6 B2 B3 B6 C1];	[P1 V6 B2 B3 B6 C1];		#	ڳႹ.σ‌
 */
/* punt1 */
/* 76 source \u0665\u0660₀．\u069C- uni [V3 B1 B3] ace [V3 B1 B3] nv8  line B;	\u0665\u0660₀．\u069C-;	[V3 B1 B3];	[V3 B1 B3];		#	٥٠0.ڜ-
 */
/* punt1 */
/* 76 source xn--i7l uni 㦮 ace xn--i7l nv8  line B;	xn--i7l;	㦮;	xn--i7l;	
 */
{ "㦮", "xn--i7l", IDN2_OK },
/* 77 source ꒾🄂ꦖ\u07CA uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	꒾🄂ꦖ\u07CA;	[P1 V6 B1];	[P1 V6 B1];		#	꒾🄂ꦖߊ
 */
/* punt1 */
/* 77 source \u200C\uA9B8 uni [C1] ace [C1] nv8  line N;	\u200C\uA9B8;	[C1];	[C1];		#	‌ꦸ
 */
/* punt1 */
/* 77 source 폸。\u0761\u0EB6⪎ uni [B3] ace [B3] nv8  line B;	폸。\u0761\u0EB6⪎;	[B3];	[B3];		#	폸.ݡຶ⪎
 */
/* punt1 */
/* 77 source 㻶 uni 㻶 ace xn--4bn nv8  line B;	㻶;	;	xn--4bn;	
 */
{ "㻶", "xn--4bn", IDN2_OK },
/* 78 source ≯끄 uni [P1 V6] ace [P1 V6] nv8  line B;	≯끄;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 78 source ς．\u063A uni ς.\u063A ace xn--3xa.xn--5gb nv8  line N;	ς．\u063A;	ς.\u063A;	xn--3xa.xn--5gb;		#	ς.غ
 */
{ "ς.\u063A", "xn--3xa.xn--5gb", IDN2_OK },
/* 79 source Σ．\u063A uni σ.\u063A ace xn--4xa.xn--5gb nv8  line B;	Σ．\u063A;	σ.\u063A;	xn--4xa.xn--5gb;		#	σ.غ
 */
{ "σ.\u063A", "xn--4xa.xn--5gb", IDN2_OK },
/* 80 source xn--3xa.xn--5gb uni ς.\u063A ace xn--3xa.xn--5gb nv8  line B;	xn--3xa.xn--5gb;	ς.\u063A;	xn--3xa.xn--5gb;		#	ς.غ
 */
{ "ς.\u063A", "xn--3xa.xn--5gb", IDN2_OK },
/* 81 source \u0326。\u0713 uni [V5 B1 B3 B6] ace [V5 B1 B3 B6] nv8  line B;	\u0326。\u0713;	[V5 B1 B3 B6];	[V5 B1 B3 B6];		#	̦.ܓ
 */
/* punt1 */
/* 81 source જ\u200C uni [C1] ace [C1] nv8  line N;	જ\u200C;	[C1];	[C1];		#	જ‌
 */
/* punt1 */
/* 81 source xn--7dc uni જ ace xn--7dc nv8  line B;	xn--7dc;	જ;	xn--7dc;	
 */
{ "જ", "xn--7dc", IDN2_OK },
/* 82 source ۹쁔 uni ۹쁔 ace xn--mmb6106g nv8  line B;	۹쁔;	;	xn--mmb6106g;	
 */
{ "۹쁔", "xn--mmb6106g", IDN2_OK },
/* 83 source ጕ uni ጕ ace xn--64d nv8  line B;	ጕ;	;	xn--64d;	
 */
{ "ጕ", "xn--64d", IDN2_OK },
/* 84 source 苫≮｡-◖ß uni [P1 V6 V3] ace [P1 V6 V3] nv8  line B;	苫≮｡-◖ß;	[P1 V6 V3];	[P1 V6 V3];	
 */
/* punt1 */
/* 84 source ≠｡\u0ECA uni [P1 V6 V5] ace [P1 V6 V5] nv8  line B;	≠｡\u0ECA;	[P1 V6 V5];	[P1 V6 V5];		#	≠.໊
 */
/* punt1 */
/* 84 source -\u0602 uni [P1 V3 V6 B1] ace [P1 V3 V6 B1] nv8  line B;	-\u0602;	[P1 V3 V6 B1];	[P1 V3 V6 B1];		#	-؂
 */
/* punt1 */
/* 84 source \u0624\u032A.\u069C\u1A66 uni \u0624\u032A.\u069C\u1A66 ace xn--rta73m.xn--yjb642h nv8  line B;	\u0624\u032A.\u069C\u1A66;	;	xn--rta73m.xn--yjb642h;		#	ؤ̪.ڜᩦ
 */
{ "\u0624\u032A.\u069C\u1A66", "xn--rta73m.xn--yjb642h", IDN2_OK },
/* 85 source \u0758 uni \u0758 ace xn--cpb nv8  line B;	\u0758;	;	xn--cpb;		#	ݘ
 */
{ "\u0758", "xn--cpb", IDN2_OK },
/* 86 source ³\u0725\u200C\u1AFA.᧪\u200C\u0703 uni [P1 V6 B1 C1] ace [P1 V6 B1 C1] nv8  line N;	³\u0725\u200C\u1AFA.᧪\u200C\u0703;	[P1 V6 B1 C1];	[P1 V6 B1 C1];		#	3ܥ‌᫺.᧪‌܃
 */
/* punt1 */
/* 86 source \u0666\u115F\u0601 uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	\u0666\u115F\u0601;	[P1 V6 B1];	[P1 V6 B1];		#	٦ᅟ؁
 */
/* punt1 */
/* 86 source \u0FBC uni [V5] ace [V5] nv8  line B;	\u0FBC;	[V5];	[V5];		#	ྼ
 */
/* punt1 */
/* 86 source Ⴠ\uFB50。\uFFA0🄇 uni [P1 V6 B5 B6] ace [P1 V6 B5 B6] nv8  line B;	Ⴠ\uFB50。\uFFA0🄇;	[P1 V6 B5 B6];	[P1 V6 B5 B6];		#	Ⴠٱ.ﾠ🄇
 */
/* punt1 */
/* 86 source ７ uni 7 ace 7 nv8  line B;	７;	7;	;	
 */
{ "7", "7", IDN2_OK },
/* 87 source ≠\u1074 uni [P1 V6] ace [P1 V6] nv8  line B;	≠\u1074;	[P1 V6];	[P1 V6];		#	≠ၴ
 */
/* punt1 */
/* 87 source \u0600ς\u200C uni [P1 V6 B1 C1] ace [P1 V6 B1 C1] nv8  line N;	\u0600ς\u200C;	[P1 V6 B1 C1];	[P1 V6 B1 C1];		#	؀ς‌
 */
/* punt1 */
/* 87 source \u1BAA。Ↄ uni [P1 V5 V6] ace [P1 V5 V6] nv8  line B;	\u1BAA。Ↄ;	[P1 V5 V6];	[P1 V5 V6];		#	᮪.Ↄ
 */
/* punt1 */
/* 87 source \u1BAA。ↄ uni [V5] ace [V5] nv8  line B;	\u1BAA。ↄ;	[V5];	[V5];		#	᮪.ↄ
 */
/* punt1 */
/* 87 source \u0811 uni \u0811 ace xn--mub nv8  line B;	\u0811;	;	xn--mub;		#	ࠑ
 */
{ "\u0811", "xn--mub", IDN2_OK },
/* 88 source ︒\u0619 uni [P1 V6] ace [P1 V6] nv8  line B;	︒\u0619;	[P1 V6];	[P1 V6];		#	︒ؙ
 */
/* punt1 */
/* 88 source \u036F圧．︒-⒔ uni [P1 V5 V6] ace [P1 V5 V6] nv8  line B;	\u036F圧．︒-⒔;	[P1 V5 V6];	[P1 V5 V6];		#	ͯ圧.︒-⒔
 */
/* punt1 */
/* 88 source -\u0773Ⴐ。\u1714🄇\u05C7\u06C1 uni [P1 V3 V6 V5 B1] ace [P1 V3 V6 V5 B1] nv8  line B;	-\u0773Ⴐ。\u1714🄇\u05C7\u06C1;	[P1 V3 V6 V5 B1];	[P1 V3 V6 V5 B1];		#	-ݳႰ.᜔🄇ׇہ
 */
/* punt1 */
/* 88 source -\u0773ⴐ。\u1714🄇\u05C7\u06C1 uni [P1 V3 V5 V6 B1] ace [P1 V3 V5 V6 B1] nv8  line B;	-\u0773ⴐ。\u1714🄇\u05C7\u06C1;	[P1 V3 V5 V6 B1];	[P1 V3 V5 V6 B1];		#	-ݳⴐ.᜔🄇ׇہ
 */
/* punt1 */
/* 88 source \u0725 uni \u0725 ace xn--vnb nv8  line B;	\u0725;	;	xn--vnb;		#	ܥ
 */
{ "\u0725", "xn--vnb", IDN2_OK },
/* 89 source \u0685 uni \u0685 ace xn--bjb nv8  line B;	\u0685;	;	xn--bjb;		#	څ
 */
{ "\u0685", "xn--bjb", IDN2_OK },
/* 90 source \u05A3ꉣ❳ uni [V5] ace [V5] nv8  line B;	\u05A3ꉣ❳;	[V5];	[V5];		#	֣ꉣ❳
 */
/* punt1 */
/* 90 source -- uni [V3] ace [V3] nv8  line B;	--;	[V3];	[V3];	
 */
/* punt1 */
/* 90 source ß．\u0E3A uni [V5] ace [V5] nv8  line B;	ß．\u0E3A;	[V5];	[V5];		#	ß.ฺ
 */
/* punt1 */
/* 90 source 𝟓 uni 5 ace 5 nv8  line B;	𝟓;	5;	;	
 */
{ "5", "5", IDN2_OK },
/* 91 source \u06E4\u06FB.۰ uni [V5 B1] ace [V5 B1] nv8  line B;	\u06E4\u06FB.۰;	[V5 B1];	[V5 B1];		#	ۤۻ.۰
 */
/* punt1 */
/* 91 source \u0724\u06FC uni \u0724\u06FC ace xn--pmb3f nv8  line B;	\u0724\u06FC;	;	xn--pmb3f;		#	ܤۼ
 */
{ "\u0724\u06FC", "xn--pmb3f", IDN2_OK },
/* 92 source \u07E7\uFE22- uni [V3 B3] ace [V3 B3] nv8  line B;	\u07E7\uFE22-;	[V3 B3];	[V3 B3];		#	ߧ︢-
 */
/* punt1 */
/* 92 source \u0710 uni \u0710 ace xn--9mb nv8  line B;	\u0710;	;	xn--9mb;		#	ܐ
 */
{ "\u0710", "xn--9mb", IDN2_OK },
/* 93 source xn--ch8h uni 🌟 ace xn--ch8h nv8 NV8 line B;	xn--ch8h;	🌟;	xn--ch8h;	NV8
 */
{ "🌟", "xn--ch8h", IDN2_UNASSIGNED },
/* 94 source ⁅ uni ⁅ ace xn--nwg nv8 NV8 line B;	⁅;	;	xn--nwg;	NV8
 */
{ "⁅", "xn--nwg", IDN2_DISALLOWED },
/* 95 source \u071C\u200C.\uFC0B uni [B3 C1] ace [B3 C1] nv8  line N;	\u071C\u200C.\uFC0B;	[B3 C1];	[B3 C1];		#	ܜ‌.تج
 */
/* punt1 */
/* 95 source xn--mnb.xn--pgbe uni \u071C.\u062A\u062C ace xn--mnb.xn--pgbe nv8  line B;	xn--mnb.xn--pgbe;	\u071C.\u062A\u062C;	xn--mnb.xn--pgbe;		#	ܜ.تج
 */
{ "\u071C.\u062A\u062C", "xn--mnb.xn--pgbe", IDN2_OK },
/* 96 source 7\u077C၆誱 uni [B1] ace [B1] nv8  line B;	7\u077C၆誱;	[B1];	[B1];		#	7ݼ၆誱
 */
/* punt1 */
/* 96 source ς uni ς ace xn--3xa nv8  line N;	ς;	;	xn--3xa;	
 */
{ "ς", "xn--3xa", IDN2_OK },
/* 97 source Σ uni σ ace xn--4xa nv8  line B;	Σ;	σ;	xn--4xa;	
 */
{ "σ", "xn--4xa", IDN2_OK },
/* 98 source xn--3xa uni ς ace xn--3xa nv8  line B;	xn--3xa;	ς;	xn--3xa;	
 */
{ "ς", "xn--3xa", IDN2_OK },
/* 99 source \u0697👮\u0666。\u0722 uni \u0697👮\u0666.\u0722 ace xn--fib1hw306n.xn--snb nv8 NV8 line B;	\u0697👮\u0666。\u0722;	\u0697👮\u0666.\u0722;	xn--fib1hw306n.xn--snb;	NV8	#	ڗ👮٦.ܢ
 */
{ "\u0697👮\u0666.\u0722", "xn--fib1hw306n.xn--snb", IDN2_UNASSIGNED },
/* 100 source -。鏺\u077B- uni [V3 B1 B5 B6] ace [V3 B1 B5 B6] nv8  line B;	-。鏺\u077B-;	[V3 B1 B5 B6];	[V3 B1 B5 B6];		#	-.鏺ݻ-
 */
/* punt1 */
/* 100 source Ⴤ1\u200C uni [P1 V6 C1] ace [P1 V6 C1] nv8  line N;	Ⴤ1\u200C;	[P1 V6 C1];	[P1 V6 C1];		#	Ⴤ1‌
 */
/* punt1 */
/* 100 source ⴤ1\u200C uni [C1] ace [C1] nv8  line N;	ⴤ1\u200C;	[C1];	[C1];		#	ⴤ1‌
 */
/* punt1 */
/* 100 source xn--1-bxs uni ⴤ1 ace xn--1-bxs nv8  line B;	xn--1-bxs;	ⴤ1;	xn--1-bxs;	
 */
{ "ⴤ1", "xn--1-bxs", IDN2_OK },
/* 101 source Ⴤ1 uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴤ1;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 101 source xn--elj uni ⴖ ace xn--elj nv8  line B;	xn--elj;	ⴖ;	xn--elj;	
 */
{ "ⴖ", "xn--elj", IDN2_OK },
/* 102 source Ⴖ uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴖ;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 102 source \u06A4≠₉。\u061A uni [P1 V6 V5 B1 B3 B6] ace [P1 V6 V5 B1 B3 B6] nv8  line B;	\u06A4≠₉。\u061A;	[P1 V6 V5 B1 B3 B6];	[P1 V6 V5 B1 B3 B6];		#	ڤ≠9.ؚ
 */
/* punt1 */
/* 102 source \u0761۰ℲႥ.\u074F uni [P1 V6 B2 B3] ace [P1 V6 B2 B3] nv8  line B;	\u0761۰ℲႥ.\u074F;	[P1 V6 B2 B3];	[P1 V6 B2 B3];		#	ݡ۰ℲႥ.ݏ
 */
/* punt1 */
/* 102 source \u0761۰ⅎⴅ.\u074F uni [B2 B3] ace [B2 B3] nv8  line B;	\u0761۰ⅎⴅ.\u074F;	[B2 B3];	[B2 B3];		#	ݡ۰ⅎⴅ.ݏ
 */
/* punt1 */
/* 102 source \u0761۰Ⅎⴅ.\u074F uni [P1 V6 B2 B3] ace [P1 V6 B2 B3] nv8  line B;	\u0761۰Ⅎⴅ.\u074F;	[P1 V6 B2 B3];	[P1 V6 B2 B3];		#	ݡ۰Ⅎⴅ.ݏ
 */
/* punt1 */
/* 102 source \u074E uni \u074E ace xn--1ob nv8  line B;	\u074E;	;	xn--1ob;		#	ݎ
 */
{ "\u074E", "xn--1ob", IDN2_OK },
/* 103 source \u200C慺 uni [C1] ace [C1] nv8  line N;	\u200C慺;	[C1];	[C1];		#	‌慺
 */
/* punt1 */
/* 103 source xn--lju uni 慺 ace xn--lju nv8  line B;	xn--lju;	慺;	xn--lju;	
 */
{ "慺", "xn--lju", IDN2_OK },
/* 104 source ︒ႢႴ.ß uni [P1 V6] ace [P1 V6] nv8  line B;	︒ႢႴ.ß;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 104 source \u200C\u0724 uni [B1 C1] ace [B1 C1] nv8  line N;	\u200C\u0724;	[B1 C1];	[B1 C1];		#	‌ܤ
 */
/* punt1 */
/* 104 source xn--unb uni \u0724 ace xn--unb nv8  line B;	xn--unb;	\u0724;	xn--unb;		#	ܤ
 */
{ "\u0724", "xn--unb", IDN2_OK },
/* 105 source ۴\u200Cß\u075C uni [B1 C1] ace [B1 C1] nv8  line N;	۴\u200Cß\u075C;	[B1 C1];	[B1 C1];		#	۴‌ßݜ
 */
/* punt1 */
/* 105 source ᇣ≯ uni [P1 V6] ace [P1 V6] nv8  line B;	ᇣ≯;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 105 source \u06B2 uni \u06B2 ace xn--lkb nv8  line B;	\u06B2;	;	xn--lkb;		#	ڲ
 */
{ "\u06B2", "xn--lkb", IDN2_OK },
/* 106 source 댨\u0666 uni [B5 B6] ace [B5 B6] nv8  line B;	댨\u0666;	[B5 B6];	[B5 B6];		#	댨٦
 */
/* punt1 */
/* 106 source Ⴈ uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴈ;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 106 source ⴈ uni ⴈ ace xn--zkj nv8  line B;	ⴈ;	;	xn--zkj;	
 */
{ "ⴈ", "xn--zkj", IDN2_OK },
/* 107 source ⿶奵-藛 uni [P1 V6] ace [P1 V6] nv8  line B;	⿶奵-藛;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 107 source \uAA31\u0644\u05BE uni [V5 B1] ace [V5 B1] nv8  line B;	\uAA31\u0644\u05BE;	[V5 B1];	[V5 B1];		#	ꨱل־
 */
/* punt1 */
/* 107 source \u0327。咏\u0871 uni [P1 V5 V6 B1 B3 B6] ace [P1 V5 V6 B1 B3 B6] nv8  line B;	\u0327。咏\u0871;	[P1 V5 V6 B1 B3 B6];	[P1 V5 V6 B1 B3 B6];		#	̧.咏ࡱ
 */
/* punt1 */
/* 107 source ≯\u06A2≯ uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	≯\u06A2≯;	[P1 V6 B1];	[P1 V6 B1];		#	≯ڢ≯
 */
/* punt1 */
/* 107 source \u105F≯홨嘆 uni [P1 V5 V6] ace [P1 V5 V6] nv8  line B;	\u105F≯홨嘆;	[P1 V5 V6];	[P1 V5 V6];		#	ၟ≯홨嘆
 */
/* punt1 */
/* 107 source -\u0721 uni [V3 B1] ace [V3 B1] nv8  line B;	-\u0721;	[V3 B1];	[V3 B1];		#	-ܡ
 */
/* punt1 */
/* 107 source ⩅\u071E\u05BC uni [B1] ace [B1] nv8  line B;	⩅\u071E\u05BC;	[B1];	[B1];		#	⩅ܞּ
 */
/* punt1 */
/* 107 source Ⴛ.≯\u0776\u0FA7 uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	Ⴛ.≯\u0776\u0FA7;	[P1 V6 B1];	[P1 V6 B1];		#	Ⴛ.≯ݶྦྷ
 */
/* punt1 */
/* 107 source \u9FE4𝟶-Ⴓ uni [P1 V6] ace [P1 V6] nv8  line B;	\u9FE4𝟶-Ⴓ;	[P1 V6];	[P1 V6];		#	鿤0-Ⴓ
 */
/* punt1 */
/* 107 source \u0601 uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	\u0601;	[P1 V6 B1];	[P1 V6 B1];		#	؁
 */
/* punt1 */
/* 107 source \u06BC≠ uni [P1 V6 B3] ace [P1 V6 B3] nv8  line B;	\u06BC≠;	[P1 V6 B3];	[P1 V6 B3];		#	ڼ≠
 */
/* punt1 */
/* 107 source տ uni տ ace xn--tbb nv8  line B;	տ;	;	xn--tbb;	
 */
{ "տ", "xn--tbb", IDN2_OK },
/* 108 source -\u071B uni [V3 B1] ace [V3 B1] nv8  line B;	-\u071B;	[V3 B1];	[V3 B1];		#	-ܛ
 */
/* punt1 */
/* 108 source \u076FႾ。\u200C uni [P1 V6 B2 B3 B1 C1] ace [P1 V6 B2 B3 B1 C1] nv8  line N;	\u076FႾ。\u200C;	[P1 V6 B2 B3 B1 C1];	[P1 V6 B2 B3 B1 C1];		#	ݯႾ.‌
 */
/* punt1 */
/* 108 source \u076Fⴞ。\u200C uni [B2 B3 B1 C1] ace [B2 B3 B1 C1] nv8  line N;	\u076Fⴞ。\u200C;	[B2 B3 B1 C1];	[B2 B3 B1 C1];		#	ݯⴞ.‌
 */
/* punt1 */
/* 108 source ⾆.\u200C uni [C1] ace [C1] nv8  line N;	⾆.\u200C;	[C1];	[C1];		#	舌.‌
 */
/* punt1 */
/* 108 source xn--tc1a. uni 舌. ace xn--tc1a. nv8  line B;	xn--tc1a.;	舌.;	xn--tc1a.;	
 */
{ "舌.", "xn--tc1a.", IDN2_OK },
/* 109 source ⒔Ⴈ uni [P1 V6] ace [P1 V6] nv8  line B;	⒔Ⴈ;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 109 source \u06AF⋍♅︒｡Ⴚ\u072E\u1BEF uni [P1 V6 B3 B5 B6] ace [P1 V6 B3 B5 B6] nv8  line B;	\u06AF⋍♅︒｡Ⴚ\u072E\u1BEF;	[P1 V6 B3 B5 B6];	[P1 V6 B3 B5 B6];		#	گ⋍♅︒.Ⴚܮᯯ
 */
/* punt1 */
/* 109 source Ⴓ⒈ uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴓ⒈;	[P1 V6];	[P1 V6];	
 */
/* punt1 */
/* 109 source ⥴ uni ⥴ ace xn--tti nv8 NV8 line B;	⥴;	;	xn--tti;	NV8
 */
{ "⥴", "xn--tti", IDN2_DISALLOWED },
/* 110 source \u1BF3。≯⒈ uni [P1 V5 V6] ace [P1 V5 V6] nv8  line B;	\u1BF3。≯⒈;	[P1 V5 V6];	[P1 V5 V6];		#	᯳.≯⒈
 */
/* punt1 */
/* 110 source \u0752\u0776\u1A6C uni \u0752\u0776\u1A6C ace xn--5ob6e460e nv8  line B;	\u0752\u0776\u1A6C;	;	xn--5ob6e460e;		#	ݒݶᩬ
 */
{ "\u0752\u0776\u1A6C", "xn--5ob6e460e", IDN2_OK },
/* 111 source ︒- uni [P1 V3 V6] ace [P1 V3 V6] nv8  line B;	︒-;	[P1 V3 V6];	[P1 V3 V6];	
 */
/* punt1 */
/* 111 source ︒\u0714 uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	︒\u0714;	[P1 V6 B1];	[P1 V6 B1];		#	︒ܔ
 */
/* punt1 */
/* 111 source ₀ uni 0 ace 0 nv8  line B;	₀;	0;	;	
 */
{ "0", "0", IDN2_OK },
/* 112 source 𐆅\u06FB\u200C．\u06A5 uni [B1 C1] ace [B1 C1] nv8  line N;	𐆅\u06FB\u200C．\u06A5;	[B1 C1];	[B1 C1];		#	𐆅ۻ‌.ڥ
 */
/* punt1 */
/* 112 source 믄.-\u0311 uni [V3] ace [V3] nv8  line B;	믄.-\u0311;	[V3];	[V3];		#	믄.-̑
 */
/* punt1 */
/* 112 source ₉\u200C uni [C1] ace [C1] nv8  line N;	₉\u200C;	[C1];	[C1];		#	9‌
 */
/* punt1 */
/* 112 source 9 uni 9 ace 9 nv8  line B;	9;	;	;	
 */
{ "9", "9", IDN2_OK },
/* 113 source 𝟚\u200C\u07E8\u17B5。\u0665 uni [P1 V6 B1 C1] ace [P1 V6 B1 C1] nv8  line N;	𝟚\u200C\u07E8\u17B5。\u0665;	[P1 V6 B1 C1];	[P1 V6 B1 C1];		#	2‌ߨ឵.٥
 */
/* punt1 */
/* 113 source \u20EF uni [V5] ace [V5] nv8  line B;	\u20EF;	[V5];	[V5];		#	⃯
 */
/* punt1 */
/* 113 source \uA806Ⴅ uni [P1 V5 V6] ace [P1 V5 V6] nv8  line B;	\uA806Ⴅ;	[P1 V5 V6];	[P1 V5 V6];		#	꠆Ⴅ
 */
/* punt1 */
/* 113 source \uA806ⴅ uni [V5] ace [V5] nv8  line B;	\uA806ⴅ;	[V5];	[V5];		#	꠆ⴅ
 */
/* punt1 */
/* 113 source ︒\u200C\u1BF2 uni [P1 V6 C1] ace [P1 V6 C1] nv8  line N;	︒\u200C\u1BF2;	[P1 V6 C1];	[P1 V6 C1];		#	︒‌᯲
 */
/* punt1 */
/* 113 source Ⴛ\u0770。𝟐\u0641\u0664\u1BF1 uni [P1 V6 B5 B6 B1] ace [P1 V6 B5 B6 B1] nv8  line B;	Ⴛ\u0770。𝟐\u0641\u0664\u1BF1;	[P1 V6 B5 B6 B1];	[P1 V6 B5 B6 B1];		#	Ⴛݰ.2ف٤ᯱ
 */
/* punt1 */
/* 113 source ⴛ\u0770。𝟐\u0641\u0664\u1BF1 uni [B5 B6 B1] ace [B5 B6 B1] nv8  line B;	ⴛ\u0770。𝟐\u0641\u0664\u1BF1;	[B5 B6 B1];	[B5 B6 B1];		#	ⴛݰ.2ف٤ᯱ
 */
/* punt1 */
/* 113 source \u1BF3伻\u077C uni [V5 B5 B6] ace [V5 B5 B6] nv8  line B;	\u1BF3伻\u077C;	[V5 B5 B6];	[V5 B5 B6];		#	᯳伻ݼ
 */
/* punt1 */
/* 113 source Ⴍ\u0824８ uni [P1 V6 B5] ace [P1 V6 B5] nv8  line B;	Ⴍ\u0824８;	[P1 V6 B5];	[P1 V6 B5];		#	Ⴍࠤ8
 */
/* punt1 */
/* 113 source ⴍ\u0824８ uni [B5] ace [B5] nv8  line B;	ⴍ\u0824８;	[B5];	[B5];		#	ⴍࠤ8
 */
/* punt1 */
/* 113 source \u06AF uni \u06AF ace xn--ikb nv8  line B;	\u06AF;	;	xn--ikb;		#	گ
 */
{ "\u06AF", "xn--ikb", IDN2_OK },
/* 114 source xn--4jb uni \u06A2 ace xn--4jb nv8  line B;	xn--4jb;	\u06A2;	xn--4jb;		#	ڢ
 */
{ "\u06A2", "xn--4jb", IDN2_OK },
/* 115 source \u0630 uni \u0630 ace xn--vgb nv8  line B;	\u0630;	;	xn--vgb;		#	ذ
 */
{ "\u0630", "xn--vgb", IDN2_OK },
/* 116 source Ⴈ鱫\uFE0F\u072E．岴넎\u085A\u1BAA uni [P1 V6 B5 B6] ace [P1 V6 B5 B6] nv8  line B;	Ⴈ鱫\uFE0F\u072E．岴넎\u085A\u1BAA;	[P1 V6 B5 B6];	[P1 V6 B5 B6];		#	Ⴈ鱫ܮ.岴넎᮪࡚
 */
/* punt2 */
/* 116 source ⴈ鱫\uFE0F\u072E．岴넎\u1BAA\u085A uni [B5 B6] ace [B5 B6] nv8  line B;	ⴈ鱫\uFE0F\u072E．岴넎\u1BAA\u085A;	[B5 B6];	[B5 B6];		#	ⴈ鱫ܮ.岴넎᮪࡚
 */
/* punt2 */
/* 116 source Ⴖ\u0632轧 uni [P1 V6 B5] ace [P1 V6 B5] nv8  line B;	Ⴖ\u0632轧;	[P1 V6 B5];	[P1 V6 B5];		#	Ⴖز轧
 */
/* punt2 */
/* 116 source ⴖ\u0632轧 uni [B5] ace [B5] nv8  line B;	ⴖ\u0632轧;	[B5];	[B5];		#	ⴖز轧
 */
/* punt2 */
/* 116 source 。 uni 。 ace 。 nv8  line B;	。;	;	;	
 */
/* punt2 */
/* 116 source xn--llj uni ⴝ ace xn--llj nv8  line B;	xn--llj;	ⴝ;	xn--llj;	
 */
/* punt2 */
/* 116 source Ⴝ uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴝ;	[P1 V6];	[P1 V6];	
 */
/* punt2 */
/* 116 source Ⴃ\u200C㠎 uni [P1 V6 C1] ace [P1 V6 C1] nv8  line N;	Ⴃ\u200C㠎;	[P1 V6 C1];	[P1 V6 C1];		#	Ⴃ‌㠎
 */
/* punt2 */
/* 116 source ⴃ\u200C㠎 uni [C1] ace [C1] nv8  line N;	ⴃ\u200C㠎;	[C1];	[C1];		#	ⴃ‌㠎
 */
/* punt2 */
/* 116 source xn--ukjw66a uni ⴃ㠎 ace xn--ukjw66a nv8  line B;	xn--ukjw66a;	ⴃ㠎;	xn--ukjw66a;	
 */
/* punt2 */
/* 116 source Ⴃ㠎 uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴃ㠎;	[P1 V6];	[P1 V6];	
 */
/* punt2 */
/* 116 source ۷ uni ۷ ace xn--kmb nv8  line B;	۷;	;	xn--kmb;	
 */
/* punt2 */
/* 116 source \u066E\u077B uni \u066E\u077B ace xn--nib25c nv8  line B;	\u066E\u077B;	;	xn--nib25c;		#	ٮݻ
 */
/* punt2 */
/* 116 source \u0649\u0712Ⴎ uni [P1 V6 B2 B3] ace [P1 V6 B2 B3] nv8  line B;	\u0649\u0712Ⴎ;	[P1 V6 B2 B3];	[P1 V6 B2 B3];		#	ىܒႮ
 */
/* punt2 */
/* 116 source \u0649\u0712ⴎ uni [B2 B3] ace [B2 B3] nv8  line B;	\u0649\u0712ⴎ;	[B2 B3];	[B2 B3];		#	ىܒⴎ
 */
/* punt2 */
/* 116 source \u200C- uni [V3 C1] ace [V3 C1] nv8  line N;	\u200C-;	[V3 C1];	[V3 C1];		#	‌-
 */
/* punt2 */
/* 116 source Ⴡ．\u075E uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴡ．\u075E;	[P1 V6];	[P1 V6];		#	Ⴡ.ݞ
 */
/* punt2 */
/* 116 source ⴡ．\u075E uni ⴡ.\u075E ace xn--plj.xn--ipb nv8  line B;	ⴡ．\u075E;	ⴡ.\u075E;	xn--plj.xn--ipb;		#	ⴡ.ݞ
 */
/* punt2 */
/* 116 source Ⴡ.\u075E uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴡ.\u075E;	[P1 V6];	[P1 V6];		#	Ⴡ.ݞ
 */
/* punt2 */
/* 116 source ⌕.\u200C uni [C1] ace [C1] nv8  line N;	⌕.\u200C;	[C1];	[C1];		#	⌕.‌
 */
/* punt2 */
/* 116 source xn--7hh. uni ⌕. ace xn--7hh. nv8 NV8 line B;	xn--7hh.;	⌕.;	xn--7hh.;	NV8
 */
/* punt2 */
/* 116 source -ß。Ⅎ uni [P1 V3 V6] ace [P1 V3 V6] nv8  line B;	-ß。Ⅎ;	[P1 V3 V6];	[P1 V3 V6];	
 */
/* punt2 */
/* 116 source -ß。ⅎ uni [V3] ace [V3] nv8  line B;	-ß。ⅎ;	[V3];	[V3];	
 */
/* punt2 */
/* 116 source -SS。Ⅎ uni [P1 V3 V6] ace [P1 V3 V6] nv8  line B;	-SS。Ⅎ;	[P1 V3 V6];	[P1 V3 V6];	
 */
/* punt2 */
/* 116 source -ss。ⅎ uni [V3] ace [V3] nv8  line B;	-ss。ⅎ;	[V3];	[V3];	
 */
/* punt2 */
/* 116 source -Ss。Ⅎ uni [P1 V3 V6] ace [P1 V3 V6] nv8  line B;	-Ss。Ⅎ;	[P1 V3 V6];	[P1 V3 V6];	
 */
/* punt2 */
/* 116 source \u06CE uni \u06CE ace xn--elb nv8  line B;	\u06CE;	;	xn--elb;		#	ێ
 */
/* punt2 */
/* 116 source -᠆⒎迮.- uni [P1 V3 V6] ace [P1 V3 V6] nv8  line B;	-᠆⒎迮.-;	[P1 V3 V6];	[P1 V3 V6];	
 */
/* punt2 */
/* 116 source xn--zii uni ⟹ ace xn--zii nv8 NV8 line B;	xn--zii;	⟹;	xn--zii;	NV8
 */
/* punt2 */
/* 116 source Ⴆ\u06BA馏Ⴍ.솯-\u103AჃ uni [P1 V6 B5] ace [P1 V6 B5] nv8  line B;	Ⴆ\u06BA馏Ⴍ.솯-\u103AჃ;	[P1 V6 B5];	[P1 V6 B5];		#	Ⴆں馏Ⴍ.솯-်Ⴣ
 */
/* punt2 */
/* 116 source ⴆ\u06BA馏ⴍ.솯-\u103Aⴣ uni [B5] ace [B5] nv8  line B;	ⴆ\u06BA馏ⴍ.솯-\u103Aⴣ;	[B5];	[B5];		#	ⴆں馏ⴍ.솯-်ⴣ
 */
/* punt2 */
/* 116 source \u1CE0🄅\u0669- uni [P1 V3 V5 V6 B1] ace [P1 V3 V5 V6 B1] nv8  line B;	\u1CE0🄅\u0669-;	[P1 V3 V5 V6 B1];	[P1 V3 V5 V6 B1];		#	᳠🄅٩-
 */
/* punt2 */
/* 116 source xn--plj.3 uni ⴡ.3 ace xn--plj.3 nv8  line B;	xn--plj.3;	ⴡ.3;	xn--plj.3;	
 */
/* punt2 */
/* 116 source Ⴡ.3 uni [P1 V6] ace [P1 V6] nv8  line B;	Ⴡ.3;	[P1 V6];	[P1 V6];	
 */
/* punt2 */
/* 116 source \u065E uni [V5] ace [V5] nv8  line B;	\u065E;	[V5];	[V5];		#	ٞ
 */
/* punt2 */
/* 116 source \u0898 uni [P1 V6] ace [P1 V6] nv8  line B;	\u0898;	[P1 V6];	[P1 V6];		#	࢘
 */
/* punt2 */
/* 116 source \u200C.羮 uni [C1] ace [C1] nv8  line N;	\u200C.羮;	[C1];	[C1];		#	‌.羮
 */
/* punt2 */
/* 116 source xn--iu0a uni 羮 ace xn--iu0a nv8  line B;	xn--iu0a;	羮;	xn--iu0a;	
 */
/* punt2 */
/* 116 source \u0722Ⴑ uni [P1 V6 B2 B3] ace [P1 V6 B2 B3] nv8  line B;	\u0722Ⴑ;	[P1 V6 B2 B3];	[P1 V6 B2 B3];		#	ܢႱ
 */
/* punt2 */
/* 116 source \u0722ⴑ uni [B2 B3] ace [B2 B3] nv8  line B;	\u0722ⴑ;	[B2 B3];	[B2 B3];		#	ܢⴑ
 */
/* punt2 */
/* 116 source ﹜ uni [P1 V6] ace [P1 V6] nv8  line B;	﹜;	[P1 V6];	[P1 V6];	
 */
/* punt2 */
/* 116 source \u077E uni \u077E ace xn--fqb nv8  line B;	\u077E;	;	xn--fqb;		#	ݾ
 */
/* punt2 */
/* 116 source \u07E1 uni \u07E1 ace xn--8sb nv8  line B;	\u07E1;	;	xn--8sb;		#	ߡ
 */
/* punt2 */
/* 116 source --３ uni [V3] ace [V3] nv8  line B;	--３;	[V3];	[V3];	
 */
/* punt2 */
/* 116 source 6 uni 6 ace 6 nv8  line B;	6;	;	;	
 */
/* punt2 */
/* 116 source 📆-\u0730．\u071F uni [B1] ace [B1] nv8  line B;	📆-\u0730．\u071F;	[B1];	[B1];		#	📆-ܰ.ܟ
 */
/* punt2 */
/* 116 source \u1714 uni [V5] ace [V5] nv8  line B;	\u1714;	[V5];	[V5];		#	᜔
 */
/* punt2 */
/* 116 source 卦．\u069F uni 卦.\u069F ace xn--mlr.xn--1jb nv8  line B;	卦．\u069F;	卦.\u069F;	xn--mlr.xn--1jb;		#	卦.ڟ
 */
/* punt2 */
/* 116 source Ⴔ\u1160- uni [P1 V3 V6] ace [P1 V3 V6] nv8  line B;	Ⴔ\u1160-;	[P1 V3 V6];	[P1 V3 V6];		#	Ⴔᅠ-
 */
/* punt2 */
/* 116 source ≮\u200C uni [P1 V6 C1] ace [P1 V6 C1] nv8  line N;	≮\u200C;	[P1 V6 C1];	[P1 V6 C1];		#	≮‌
 */
/* punt2 */
/* 116 source ۱⒑\uA928 uni [P1 V6] ace [P1 V6] nv8  line B;	۱⒑\uA928;	[P1 V6];	[P1 V6];		#	۱⒑ꤨ
 */
/* punt2 */
/* 116 source \u077C첫\u0714.趭≯ uni [P1 V6 B2 B6] ace [P1 V6 B2 B6] nv8  line B;	\u077C첫\u0714.趭≯;	[P1 V6 B2 B6];	[P1 V6 B2 B6];		#	ݼ첫ܔ.趭≯
 */
/* punt2 */
/* 116 source ß\u063B-.𩆋Ⴈ\u3164\u200C uni [P1 V3 V6 B5 B6 C1] ace [P1 V3 V6 B5 B6 C1] nv8  line N;	ß\u063B-.𩆋Ⴈ\u3164\u200C;	[P1 V3 V6 B5 B6 C1];	[P1 V3 V6 B5 B6 C1];		#	ßػ-.𩆋Ⴈㅤ‌
 */
/* punt2 */
/* 116 source \u076F uni \u076F ace xn--zpb nv8  line B;	\u076F;	;	xn--zpb;		#	ݯ
 */
/* punt2 */
/* 116 source 蘐 uni 蘐 ace xn--651a nv8  line B;	蘐;	;	xn--651a;	
 */
/* punt2 */
/* 116 source 5.4 uni 5.4 ace 5.4 nv8  line B;	5.4;	;	;	
 */
/* punt2 */
/* 116 source ≠㇆⦩ uni [P1 V6] ace [P1 V6] nv8  line B;	≠㇆⦩;	[P1 V6];	[P1 V6];	
 */
/* punt2 */
/* 116 source \u0647 uni \u0647 ace xn--jhb nv8  line B;	\u0647;	;	xn--jhb;		#	ه
 */
/* punt2 */
/* 116 source \uAAC1 uni [V5] ace [V5] nv8  line B;	\uAAC1;	[V5];	[V5];		#	꫁
 */
/* punt2 */
/* 116 source \uFEFB\u1714Ⴓ뉠 uni [P1 V6 B2 B3] ace [P1 V6 B2 B3] nv8  line B;	\uFEFB\u1714Ⴓ뉠;	[P1 V6 B2 B3];	[P1 V6 B2 B3];		#	لا᜔Ⴓ뉠
 */
/* punt2 */
/* 116 source \uFEFB\u1714ⴓ뉠 uni [B2 B3] ace [B2 B3] nv8  line B;	\uFEFB\u1714ⴓ뉠;	[B2 B3];	[B2 B3];		#	لا᜔ⴓ뉠
 */
/* punt2 */
/* 116 source \u1BAA𝟖嚌\u1734。⭁Ⴂ uni [P1 V5 V6] ace [P1 V5 V6] nv8  line B;	\u1BAA𝟖嚌\u1734。⭁Ⴂ;	[P1 V5 V6];	[P1 V5 V6];		#	᮪8嚌᜴.⭁Ⴂ
 */
/* punt2 */
/* 116 source \u1BAA𝟖嚌\u1734。⭁ⴂ uni [V5] ace [V5] nv8  line B;	\u1BAA𝟖嚌\u1734。⭁ⴂ;	[V5];	[V5];		#	᮪8嚌᜴.⭁ⴂ
 */
/* punt2 */
/* 116 source \u1160Ⴃ uni [P1 V6] ace [P1 V6] nv8  line B;	\u1160Ⴃ;	[P1 V6];	[P1 V6];		#	ᅠႣ
 */
/* punt2 */
/* 116 source \u1035 uni [V5] ace [V5] nv8  line B;	\u1035;	[V5];	[V5];		#	ဵ
 */
/* punt2 */
/* 116 source \u0663-≮.\u064A uni [P1 V6 B1] ace [P1 V6 B1] nv8  line B;	\u0663-≮.\u064A;	[P1 V6 B1];	[P1 V6 B1];		#	٣-≮.ي
 */
/* punt2 */
/* 116 source \u0664\u1A6A.\u07EA\u0764 uni [B1] ace [B1] nv8  line B;	\u0664\u1A6A.\u07EA\u0764;	[B1];	[B1];		#	٤ᩪ.ߪݤ
 */
/* punt2 */
/* 116 source ς\u06B4\u066FჃ．％🃛-³ uni [P1 V6 B5 B1] ace [P1 V6 B5 B1] nv8  line B;	ς\u06B4\u066FჃ．％🃛-³;	[P1 V6 B5 B1];	[P1 V6 B5 B1];		#	ςڴٯჃ.％🃛-3
 */
/* punt2 */
