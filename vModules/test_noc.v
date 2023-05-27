`define N 5		/* для хранения количества роутеров и эмуряции пакета */
`define N2 9   /* это размер входящего и выходящего пакетов - 1 бит для эмуляции и K*2 бит для передачи двух чисел (шагов по первой и по второй образующим)*/
`define N_COUNT 8  /* это количество роутеров с отсчетом с нулевого, поэтому это значение всегда будет на один меньше от счетного количества*/
`define NODES 9

module toplevel_apo_9_nodes(
	clk,

	out_data,
	sw_on,
	sw_sel_data,
	sw_sel_router,
	key_inc,
	key_dec,

	hex_data,
	hex_router,
	ledr_out_data1,
	ledr_out_data2,
	ledr_out_data3,
	ledr_out_data4,
	ledr_out_data5,
	ledr_out_data6,
	ledr_out_data7,
	ledr_out_data8,
	ledr_out_data9,
	sw_in_data,
	out_router1_buffer,
	out_router2_buffer,
	out_router3_buffer,
	out_router4_buffer,
	out_router5_buffer,
	out_router6_buffer,
	out_router7_buffer,
	out_router8_buffer,
	out_router9_buffer
);
	input clk;
	input sw_on;
	input sw_sel_data;
	input sw_sel_router;
	input key_inc;
	input key_dec;
	input[7:0] sw_in_data;

	output wire[127:0] out_data;
	output wire[6:0] hex_data;
	output wire[6:0] hex_router;
	output wire[7:0] ledr_out_data1;
	output wire[7:0] ledr_out_data2;
	output wire[7:0] ledr_out_data3;
	output wire[7:0] ledr_out_data4;
	output wire[7:0] ledr_out_data5;
	output wire[7:0] ledr_out_data6;
	output wire[7:0] ledr_out_data7;
	output wire[7:0] ledr_out_data8;
	output wire[7:0] ledr_out_data9;


	wire[`N2-1:0] out_router1;
	wire[`N2-1:0] out_router2;
	wire[`N2-1:0] out_router3;
	wire[`N2-1:0] out_router4;
	wire[`N2-1:0] out_router5;
	wire[`N2-1:0] out_router6;
	wire[`N2-1:0] out_router7;
	wire[`N2-1:0] out_router8;
	wire[`N2-1:0] out_router9;
	
	output wire[`N2-1:0] out_router1_buffer;
	output wire[`N2-1:0] out_router2_buffer;
	output wire[`N2-1:0] out_router3_buffer;
	output wire[`N2-1:0] out_router4_buffer;
	output wire[`N2-1:0] out_router5_buffer;
	output wire[`N2-1:0] out_router6_buffer;
	output wire[`N2-1:0] out_router7_buffer;
	output wire[`N2-1:0] out_router8_buffer;
	output wire[`N2-1:0] out_router9_buffer;

	// Новый вход для роутера
//	wire[`N2-1:0] out_router10;


	wire[`N2-1:0] r_minR[0:`N_COUNT];// размерности элементов из массива количеством
	wire[`N2-1:0] r_maxR[0:`N_COUNT];
	wire[`N2-1:0] r_minL[0:`N_COUNT];
	wire[`N2-1:0] r_maxL[0:`N_COUNT];
	my_nios_2 core_1(.clk_clk(clk), .pinsines_export(sw_in_data), .pinsoutes_export(ledr_out_data1), .reset_reset_n(1'b1));
	my_nios_2 core_2(.clk_clk(clk), .pinsines_export(sw_in_data), .pinsoutes_export(ledr_out_data2), .reset_reset_n(1'b1));
	my_nios_2 core_3(.clk_clk(clk), .pinsines_export(sw_in_data), .pinsoutes_export(ledr_out_data3), .reset_reset_n(1'b1));
	my_nios_2 core_4(.clk_clk(clk), .pinsines_export(sw_in_data), .pinsoutes_export(ledr_out_data4), .reset_reset_n(1'b1));
	my_nios_2 core_5(.clk_clk(clk), .pinsines_export(sw_in_data), .pinsoutes_export(ledr_out_data5), .reset_reset_n(1'b1));
	my_nios_2 core_6(.clk_clk(clk), .pinsines_export(sw_in_data), .pinsoutes_export(ledr_out_data6), .reset_reset_n(1'b1));
	my_nios_2 core_7(.clk_clk(clk), .pinsines_export(sw_in_data), .pinsoutes_export(ledr_out_data7), .reset_reset_n(1'b1));
	my_nios_2 core_8(.clk_clk(clk), .pinsines_export(sw_in_data), .pinsoutes_export(ledr_out_data8), .reset_reset_n(1'b1));
	my_nios_2 core_9(.clk_clk(clk), .pinsines_export(sw_in_data), .pinsoutes_export(ledr_out_data9), .reset_reset_n(1'b1));
	
	select_data_9 sel (.clk(clk), .sw_on(sw_on), .sw_sel_data(sw_sel_data), .sw_sel_router(sw_sel_router), .key_inc(key_inc), .key_dec(key_dec),
							.out_router1(out_router1), .out_router2(out_router2), .out_router3(out_router3), .out_router4(out_router4), .out_router5(out_router5),
							.out_router6(out_router6), .out_router7(out_router7), .out_router8(out_router8), .out_router9(out_router9),
							.hex_data(hex_data), .hex_router(hex_router));

	
	apo_router_9_nodes r1  ( .clk(clk), .router_name(4'b0000), .in_free(out_router1), .in_r1R(r_minL[2]), .in_r2R(r_maxL[3]), .in_r1L(r_minR[7]), .in_r2L(r_maxR[6]), .out_r1R(r_minR[0]), .out_r2R(r_maxR[0]), .out_r1L(r_minL[0]), .out_r2L(r_maxL[0]), .out_data(out_data[0]), .out_data_buffer(out_router1_buffer));
	apo_router_9_nodes r2  ( .clk(clk), .router_name(4'b0001), .in_free(out_router2), .in_r1R(r_minL[3]), .in_r2R(r_maxL[4]), .in_r1L(r_minR[8]), .in_r2L(r_maxR[7]), .out_r1R(r_minR[1]), .out_r2R(r_maxR[1]), .out_r1L(r_minL[1]), .out_r2L(r_maxL[1]), .out_data(out_data[1]), .out_data_buffer(out_router2_buffer));
	apo_router_9_nodes r3  ( .clk(clk), .router_name(4'b0010), .in_free(out_router3), .in_r1R(r_minL[4]), .in_r2R(r_maxL[5]), .in_r1L(r_minR[0]), .in_r2L(r_maxR[8]), .out_r1R(r_minR[2]), .out_r2R(r_maxR[2]), .out_r1L(r_minL[2]), .out_r2L(r_maxL[2]), .out_data(out_data[2]), .out_data_buffer(out_router3_buffer));
	apo_router_9_nodes r4  ( .clk(clk), .router_name(4'b0011), .in_free(out_router4), .in_r1R(r_minL[5]), .in_r2R(r_maxL[6]), .in_r1L(r_minR[1]), .in_r2L(r_maxR[0]), .out_r1R(r_minR[3]), .out_r2R(r_maxR[3]), .out_r1L(r_minL[3]), .out_r2L(r_maxL[3]), .out_data(out_data[3]), .out_data_buffer(out_router4_buffer));
	apo_router_9_nodes r5  ( .clk(clk), .router_name(4'b0100), .in_free(out_router5), .in_r1R(r_minL[6]), .in_r2R(r_maxL[7]), .in_r1L(r_minR[2]), .in_r2L(r_maxR[1]), .out_r1R(r_minR[4]), .out_r2R(r_maxR[4]), .out_r1L(r_minL[4]), .out_r2L(r_maxL[4]), .out_data(out_data[4]), .out_data_buffer(out_router5_buffer));
	apo_router_9_nodes r6  ( .clk(clk), .router_name(4'b0101), .in_free(out_router6), .in_r1R(r_minL[7]), .in_r2R(r_maxL[8]), .in_r1L(r_minR[3]), .in_r2L(r_maxR[2]), .out_r1R(r_minR[5]), .out_r2R(r_maxR[5]), .out_r1L(r_minL[5]), .out_r2L(r_maxL[5]), .out_data(out_data[5]), .out_data_buffer(out_router6_buffer));
	apo_router_9_nodes r7  ( .clk(clk), .router_name(4'b0110), .in_free(out_router7), .in_r1R(r_minL[8]), .in_r2R(r_maxL[0]), .in_r1L(r_minR[4]), .in_r2L(r_maxR[3]), .out_r1R(r_minR[6]), .out_r2R(r_maxR[6]), .out_r1L(r_minL[6]), .out_r2L(r_maxL[6]), .out_data(out_data[6]), .out_data_buffer(out_router7_buffer));
	apo_router_9_nodes r8  ( .clk(clk), .router_name(4'b0111), .in_free(out_router8), .in_r1R(r_minL[0]), .in_r2R(r_maxL[1]), .in_r1L(r_minR[5]), .in_r2L(r_maxR[4]), .out_r1R(r_minR[7]), .out_r2R(r_maxR[7]), .out_r1L(r_minL[7]), .out_r2L(r_maxL[7]), .out_data(out_data[7]), .out_data_buffer(out_router8_buffer));
	apo_router_9_nodes r9  ( .clk(clk), .router_name(4'b1000), .in_free(out_router9), .in_r1R(r_minL[1]), .in_r2R(r_maxL[2]), .in_r1L(r_minR[6]), .in_r2L(r_maxR[5]), .out_r1R(r_minR[8]), .out_r2R(r_maxR[8]), .out_r1L(r_minL[8]), .out_r2L(r_maxL[8]), .out_data(out_data[8]), .out_data_buffer(out_router9_buffer));

	wire [3:0] r_name;
	wire [31:0] cpu_c;
	wire [31:0] c_cpu;
	wire [16:0] c_r;
	wire [16:0] r_c;
	converter converter(
		.clk(clk),
		.rst(!rst_n),
		.f_c(cpu_c),
		.to_r(c_r),
		.f_r(r_c),
		.to_c(c_cpu),
		.r_name(r_name)
	);
	sm_cpu ext_ip_10 (.clk(clk), .rst_n(rst_n), .inject(c_cpu), eject(cpu_c), .router_name(r_name));

	ext_r r10 (.clk(clk), .rst_n(rst_n), .router_name(4'b1001), .in_free(c_r), .in_r1R(r_minL[2]), .in_r2R(r_maxL[3]), .in_r1L(r_minR[9]), .in_r2L(r_maxR[8]), .out_r1R(r_minR[10]), .out_r2R(r_maxR[10]), .out_r1L(r_minL[10]), .out_r2L(r_maxL[10]), .out_data(r_c));

	wire [3:0] r_name;
	wire [31:0] cpu_c;
	wire [31:0] c_cpu;
	wire [16:0] c_r;
	wire [16:0] r_c;
	converter converter(
		.clk(clk),
		.rst(!rst_n),
		.f_c(cpu_c),
		.to_r(c_r),
		.f_r(r_c),
		.to_c(c_cpu),
		.r_name(r_name)
	);
	sm_cpu ext_ip_10 (.clk(clk), .rst_n(rst_n), .inject(c_cpu), eject(cpu_c), .router_name(r_name));

	ext_r r10 (.clk(clk), .rst_n(rst_n), .router_name(4'b1001), .in_free(c_r), .in_r1R(r_minL[2]), .in_r2R(r_maxL[3]), .in_r1L(r_minR[8]), .in_r2L(r_maxR[7]), .out_r1R(r_minR[9]), .out_r2R(r_maxR[9]), .out_r1L(r_minL[9]), .out_r2L(r_maxL[9]), .out_data(r_c));

	wire [3:0] r_name;
	wire [31:0] cpu_c;
	wire [31:0] c_cpu;
	wire [16:0] c_r;
	wire [16:0] r_c;
	converter converter(
		.clk(clk),
		.rst(!rst_n),
		.f_c(cpu_c),
		.to_r(c_r),
		.f_r(r_c),
		.to_c(c_cpu),
		.r_name(r_name)
	);
	sm_cpu ext_ip_10 (.clk(clk), .rst_n(rst_n), .inject(c_cpu), eject(cpu_c), .router_name(r_name));

	ext_r r10 (.clk(clk), .rst_n(rst_n), .router_name(4'b1001), .in_free(c_r), .in_r1R(r_minL[1]), .in_r2R(r_maxL[2]), .in_r1L(r_minR[7]), .in_r2L(r_maxR[6]), .out_r1R(r_minR[9]), .out_r2R(r_maxR[9]), .out_r1L(r_minL[9]), .out_r2L(r_maxL[9]), .out_data(r_c));

	wire [3:0] r_name;
	wire [31:0] cpu_c;
	wire [31:0] c_cpu;
	wire [16:0] c_r;
	wire [16:0] r_c;
	converter converter(
		.clk(clk),
		.rst(!rst_n),
		.f_c(cpu_c),
		.to_r(c_r),
		.f_r(r_c),
		.to_c(c_cpu),
		.r_name(r_name)
	);
	sm_cpu ext_ip_10 (.clk(clk), .rst_n(rst_n), .inject(c_cpu), eject(cpu_c), .router_name(r_name));

	ext_r r10 (.clk(clk), .rst_n(rst_n), .router_name(4'b1001), .in_free(c_r), .in_r1R(r_minL[1]), .in_r2R(r_maxL[2]), .in_r1L(r_minR[7]), .in_r2L(r_maxR[6]), .out_r1R(r_minR[9]), .out_r2R(r_maxR[9]), .out_r1L(r_minL[9]), .out_r2L(r_maxL[9]), .out_data(r_c));

	wire [3:0] r_name;
	wire [31:0] cpu_c;
	wire [31:0] c_cpu;
	wire [16:0] c_r;
	wire [16:0] r_c;
	test_noc test_noc_inst (
		.clk(clk),
		.rst(!rst_n),
		.f_c(cpu_c),
		.to_r(c_r),
		.f_r(r_c),
		.to_c(c_cpu),
		.r_name(r_name)
	);
	sm_cpu ext_ip_10 (.clk(clk), .rst_n(rst_n), .inject(c_cpu), eject(cpu_c), .router_name(r_name));

	ext_r r10 (.clk(clk), .rst_n(rst_n), .router_name(4'b1001), .in_free(c_r), .in_r1R(r_minL[1]), .in_r2R(r_maxL[2]), .in_r1L(r_minR[7]), .in_r2L(r_maxR[6]), .out_r1R(r_minR[9]), .out_r2R(r_maxR[9]), .out_r1L(r_minL[9]), .out_r2L(r_maxL[9]), .out_data(r_c));

	wire [3:0] r_name;
	wire [31:0] cpu_c;
	wire [31:0] c_cpu;
	wire [16:0] c_r;
	wire [16:0] r_c;
	adapter adapter_inst (
		.clk(clk),
		.rst(!rst_n),
		.f_c(cpu_c),
		.to_r(c_r),
		.f_r(r_c),
		.to_c(c_cpu),
		.r_name(r_name)
	);
	sm_cpu ext_ip_10 (.clk(clk), .rst_n(rst_n), .inject(c_cpu), eject(cpu_c), .router_name(r_name));

	ext_r r10 (.clk(clk), .rst_n(rst_n), .router_name(4'b1001), .in_free(c_r), .in_r1R(r_minL[1]), .in_r2R(r_maxL[2]), .in_r1L(r_minR[7]), .in_r2L(r_maxR[6]), .out_r1R(r_minR[9]), .out_r2R(r_maxR[9]), .out_r1L(r_minL[9]), .out_r2L(r_maxL[9]), .out_data(r_c));
endmodule
