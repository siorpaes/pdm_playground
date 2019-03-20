// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.2 (win64) Build 2258646 Thu Jun 14 20:03:12 MDT 2018
// Date        : Wed Mar 13 12:57:13 2019
// Host        : AGRCWD8123 running 64-bit Service Pack 1  (build 7601)
// Command     : write_verilog -force -mode synth_stub {c:/Users/david
//               siorpaes/Desktop/clockgen/clockgen.srcs/sources_1/ip/c_counter_binary_0/c_counter_binary_0_stub.v}
// Design      : c_counter_binary_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a35tcpg236-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "c_counter_binary_v12_0_12,Vivado 2018.2" *)
module c_counter_binary_0(CLK, Q)
/* synthesis syn_black_box black_box_pad_pin="CLK,Q[15:0]" */;
  input CLK;
  output [15:0]Q;
endmodule
