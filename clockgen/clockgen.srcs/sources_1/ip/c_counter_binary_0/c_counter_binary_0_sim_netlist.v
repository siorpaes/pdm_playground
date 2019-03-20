// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.2 (win64) Build 2258646 Thu Jun 14 20:03:12 MDT 2018
// Date        : Wed Mar 13 12:57:13 2019
// Host        : AGRCWD8123 running 64-bit Service Pack 1  (build 7601)
// Command     : write_verilog -force -mode funcsim {c:/Users/david
//               siorpaes/Desktop/clockgen/clockgen.srcs/sources_1/ip/c_counter_binary_0/c_counter_binary_0_sim_netlist.v}
// Design      : c_counter_binary_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7a35tcpg236-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "c_counter_binary_0,c_counter_binary_v12_0_12,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "c_counter_binary_v12_0_12,Vivado 2018.2" *) 
(* NotValidForBitStream *)
module c_counter_binary_0
   (CLK,
    Q);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 clk_intf CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME clk_intf, ASSOCIATED_BUSIF q_intf:thresh0_intf:l_intf:load_intf:up_intf:sinit_intf:sset_intf, ASSOCIATED_RESET SCLR, ASSOCIATED_CLKEN CE, FREQ_HZ 10000000, PHASE 0.000" *) input CLK;
  (* x_interface_info = "xilinx.com:signal:data:1.0 q_intf DATA" *) (* x_interface_parameter = "XIL_INTERFACENAME q_intf, LAYERED_METADATA undef" *) output [15:0]Q;

  wire CLK;
  wire [15:0]Q;
  wire NLW_U0_THRESH0_UNCONNECTED;

  (* C_AINIT_VAL = "0" *) 
  (* C_CE_OVERRIDES_SYNC = "0" *) 
  (* C_FB_LATENCY = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_SINIT = "0" *) 
  (* C_HAS_SSET = "0" *) 
  (* C_IMPLEMENTATION = "0" *) 
  (* C_SCLR_OVERRIDES_SSET = "1" *) 
  (* C_SINIT_VAL = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_WIDTH = "16" *) 
  (* C_XDEVICEFAMILY = "artix7" *) 
  (* c_count_by = "1" *) 
  (* c_count_mode = "0" *) 
  (* c_count_to = "1" *) 
  (* c_has_load = "0" *) 
  (* c_has_thresh0 = "0" *) 
  (* c_latency = "1" *) 
  (* c_load_low = "0" *) 
  (* c_restrict_count = "0" *) 
  (* c_thresh0_value = "1" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  c_counter_binary_0_c_counter_binary_v12_0_12 U0
       (.CE(1'b1),
        .CLK(CLK),
        .L({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .LOAD(1'b0),
        .Q(Q),
        .SCLR(1'b0),
        .SINIT(1'b0),
        .SSET(1'b0),
        .THRESH0(NLW_U0_THRESH0_UNCONNECTED),
        .UP(1'b1));
endmodule

(* C_AINIT_VAL = "0" *) (* C_CE_OVERRIDES_SYNC = "0" *) (* C_COUNT_BY = "1" *) 
(* C_COUNT_MODE = "0" *) (* C_COUNT_TO = "1" *) (* C_FB_LATENCY = "0" *) 
(* C_HAS_CE = "0" *) (* C_HAS_LOAD = "0" *) (* C_HAS_SCLR = "0" *) 
(* C_HAS_SINIT = "0" *) (* C_HAS_SSET = "0" *) (* C_HAS_THRESH0 = "0" *) 
(* C_IMPLEMENTATION = "0" *) (* C_LATENCY = "1" *) (* C_LOAD_LOW = "0" *) 
(* C_RESTRICT_COUNT = "0" *) (* C_SCLR_OVERRIDES_SSET = "1" *) (* C_SINIT_VAL = "0" *) 
(* C_THRESH0_VALUE = "1" *) (* C_VERBOSITY = "0" *) (* C_WIDTH = "16" *) 
(* C_XDEVICEFAMILY = "artix7" *) (* ORIG_REF_NAME = "c_counter_binary_v12_0_12" *) (* downgradeipidentifiedwarnings = "yes" *) 
module c_counter_binary_0_c_counter_binary_v12_0_12
   (CLK,
    CE,
    SCLR,
    SSET,
    SINIT,
    UP,
    LOAD,
    L,
    THRESH0,
    Q);
  input CLK;
  input CE;
  input SCLR;
  input SSET;
  input SINIT;
  input UP;
  input LOAD;
  input [15:0]L;
  output THRESH0;
  output [15:0]Q;

  wire \<const1> ;
  wire CLK;
  wire [15:0]Q;
  wire NLW_i_synth_THRESH0_UNCONNECTED;

  assign THRESH0 = \<const1> ;
  VCC VCC
       (.P(\<const1> ));
  (* C_AINIT_VAL = "0" *) 
  (* C_CE_OVERRIDES_SYNC = "0" *) 
  (* C_FB_LATENCY = "0" *) 
  (* C_HAS_CE = "0" *) 
  (* C_HAS_SCLR = "0" *) 
  (* C_HAS_SINIT = "0" *) 
  (* C_HAS_SSET = "0" *) 
  (* C_IMPLEMENTATION = "0" *) 
  (* C_SCLR_OVERRIDES_SSET = "1" *) 
  (* C_SINIT_VAL = "0" *) 
  (* C_VERBOSITY = "0" *) 
  (* C_WIDTH = "16" *) 
  (* C_XDEVICEFAMILY = "artix7" *) 
  (* c_count_by = "1" *) 
  (* c_count_mode = "0" *) 
  (* c_count_to = "1" *) 
  (* c_has_load = "0" *) 
  (* c_has_thresh0 = "0" *) 
  (* c_latency = "1" *) 
  (* c_load_low = "0" *) 
  (* c_restrict_count = "0" *) 
  (* c_thresh0_value = "1" *) 
  (* downgradeipidentifiedwarnings = "yes" *) 
  c_counter_binary_0_c_counter_binary_v12_0_12_viv i_synth
       (.CE(1'b0),
        .CLK(CLK),
        .L({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .LOAD(1'b0),
        .Q(Q),
        .SCLR(1'b0),
        .SINIT(1'b0),
        .SSET(1'b0),
        .THRESH0(NLW_i_synth_THRESH0_UNCONNECTED),
        .UP(1'b0));
endmodule
`pragma protect begin_protected
`pragma protect version = 1
`pragma protect encrypt_agent = "XILINX"
`pragma protect encrypt_agent_info = "Xilinx Encryption Tool 2015"
`pragma protect key_keyowner="Cadence Design Systems.", key_keyname="cds_rsa_key", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=64)
`pragma protect key_block
RhedCTftnR/lFLJouqVu00X8CC4TkDlMiW/WeWJSYDyQHVO1xW1z9+hmgAziXI4s3uGElBs9cXRS
4yVMV7QH0w==

`pragma protect key_keyowner="Synopsys", key_keyname="SNPS-VCS-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
qX90FYlZfOA3sZpcv0rrvWRKCSlr3skWpeAe5OSxHcZPsVQFyY0hhWVDtP/vB+dV9hIUwAN29Fn9
+L9OEXYMlIw5gH6s9NmquAs3lmPRLTrrpKJWdvf6+b+LeG9CPwLz87bXAk4qQW80zUHBaDKDLV3q
pd/gEf8Y3st+mLOGjNU=

`pragma protect key_keyowner="Aldec", key_keyname="ALDEC15_001", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
chpH3Rj5RAirYZHkpJvTu4EJpydPPSy15v646y2lN/1w3bwHI+M8EpLMBjimx8uIWRJZ6dDWPR8E
zkwK1TMroEKFaL8IkFMSHPyzqbrH9l1jxYFs0ee8Itp8Rg8qenv5RXM+h4JRTtRmzHk1A8s8zeKY
MgXzIBCAzBa/vSgzDuDaUnO8r8f/5KtRjmE28JLNXXAxyijBrMTCiIHMRJZL5/+LgUyVq7/Zr5yx
7kuNGWv7Q0wESEqhsQbK6UNel5ak1cor7647dYJgIxnNZ6jGVJPkqi8ydAIZ0z0Dy4txBvVaMyP6
2kYYnbVN6S6q6yr/QcJHEOgefF59B/8JuWzdoQ==

`pragma protect key_keyowner="ATRENTA", key_keyname="ATR-SG-2015-RSA-3", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
Z2XauOF3/9FUIv1kEFfEtdy93+zHY5q9dH1pJCNLytoWWhhJBfCI5Uc2w/fQLrvVw2Ivy0/rs9qH
9fomTNECWeCphNDVpWGNcFDGE51jt6SDWt7FmgfZq4iXN7XWrfmkQa4DB7QbtSBHCMcBT53TKbDH
suKNhAWMV0htWeNEgN4Y0biiz8U4RLT1stdsMMtEzfYVhtrTmFWLihJ/9gJ01pm/kv4OB2cJEslg
sjbxCE2B4Y1uSj93tnBAw4/f2RYGfPcSrkaXkNgOYK2dc5NQgd82XvP8siAK/ETcZQ1lBK367Rxv
nlr6QUMwKALmjLVe/IThpCRGbOSy3QykkwnpHw==

`pragma protect key_keyowner="Xilinx", key_keyname="xilinxt_2017_05", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
F/mF2RV90mf5PFUZZUjMej6jQS+Qx16uCeiDQxUX+H+O2yjP6UECegDbtLmGk9algbDuGBCE0KgZ
HzSxX5pMwDq1J7nFyBsu1dGyu8NeJxfu0fFA/qS/SYJSTtwnZ/eIj09mNLJ3w8wGR87ke1ETTRpx
4Ni9DzGJ/aaWFaUenL/x4UWS9yqlaNi5Utcpa4kcUHC6fW0asZsThZJBqpArO54TF40nxZAD+V82
6mBGFOKUzgmHqXNsbVif4JqUd63LG8YWxjrOeesq61xzyjw9caQMuA9v/5sQslCFaeSt2atgqyaA
y4mcm0kU60s6mYqJr4KZt8DWG7LPGoIjhjpnMg==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VELOCE-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=128)
`pragma protect key_block
YNrNxIZl8p2OCPz+4Y4awQ09ZZ41X8EdKu2SX1gXfB3qoV3EOXf4eFHtYJ+bFIccfEIqPfZ+dnr7
udcSDAJMcxqZe+YNk5hTq+uX4PlnQH/IVlkgyYiDhQ7aRIS5pwtIRC3biXn80933ov4zlWLI+ZBq
bG8lodZjxKh6HZPWi7s=

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-VERIF-SIM-RSA-2", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
eWToRZf4bzAQhHTj44yEkOqolJ3BOvlBPKnKoDCpSvCHSrnRcJKgOd47PnboABTqLVstQenz8AFe
rWHBbaad7KOIh3LsEXBwDHKDdby7iDAB5nd3j2Wp7qiHOv7WpIJ5RG1GMQa8+QXHMVaV4jSvsdmt
d0D9H0WEVaqrSFW2ucpsMYNE0LnKcSJ1SejKOcgISzaGJgXcmEAOVAOnCDPc4slwc3dt7Jne1KvY
i66An36Mfhhd1b0RikMf4yqpM+uVrL5XWIP+TBtw3iQRE0ZkUSn3K0My73/2vKKBfwyV0c+M/Il+
aMxNaD44Gq+/f6zGjkelgMEI4BjB5rs1KRvSCg==

`pragma protect key_keyowner="Mentor Graphics Corporation", key_keyname="MGC-PREC-RSA", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
YCXccWttmE66hEtNOIl3YGBx0znAYdMQMWR23uBYXsTOtyrfpvGPngkMFlmRCF5mJG3TmGPtvgyi
vOqtHbjtw7638fDSzaJzZF0/TjcZSrEn3vccgQdjGj1+TFBpQ+stsLf7spKVQMbJI43tNfrdjblP
LaCT/UkCAe6F+vvSMTdxlgLWwjs1hzXOOaJKP32D7YmJ0ol/byLd9D+KjRFrNQYEEocZCOLIUGqq
4chQi16rbf/p8snxTWThs5VfBrPf6U+zjEt/l7hpfbMfEpzQmn/8bHP3yJUjq0XJR8oLw4UbO3gy
/4GydcFq9kbFLiOFLk+2S+bxwE8T0/S0GA6yFw==

`pragma protect key_keyowner="Synplicity", key_keyname="SYNP15_1", key_method="rsa"
`pragma protect encoding = (enctype="BASE64", line_length=76, bytes=256)
`pragma protect key_block
QFHe7ZLoFuaLgOYMP2q0DXn8ZUNEkevFuG66L8OeAHiVnR1s1jNs7ifO8adcPFd1hB+CeiBiQTiI
tsFglwaG9uz6VameJu4JCK1u+fS4+xN1oGAnM7IIVU1KMZfZ2x+eGqNuenBvquuNz47JACdP6GVR
N9OOLvCYWO4pZqJz/K/1SdtC9SgcTJNYcWYtVAkn6+NYWTXEle8NHd53XXLK4608rf6oyj2VoVaT
1W68vhO7UeTHAZg9dwM5Dbvui7W/AljzNXMm+Jhhorp+XXDNGwCWbq+Fbfna8kGRxfyncllZ+q14
BpE53AniM1fYsj1U9mamkntkTH3azg9uFNm7Uw==

`pragma protect data_method = "AES128-CBC"
`pragma protect encoding = (enctype = "BASE64", line_length = 76, bytes = 10096)
`pragma protect data_block
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
a6TDrZIbNA==
`pragma protect end_protected
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
