module ext_adapter1 (
	clk,
	rst,
	f_c,
	to_c,
	f_r,
	to_r,
	r_name
);

	input clk, rst;
	reg wr_en, rd_en;
	input [31:0] f_c; 
	input [8:0] f_r;
	input [3:0] r_name;
	output reg[31:0] to_c; 
	output reg[16:0] to_r;
	reg empty, full;
	reg [2:0] counter;
	reg [2:0] rd_ptr_r;
	reg [16:0] mem[3:0];
	reg [31:0] suppl_data;
	reg [2:0] suppl_counter;
	always @(counter) begin
		empty <= (counter == 0);
		full <= (counter == 4);
	end

	always @(posedge clk) begin
		if (f_c != 0 && empty) begin
			empty <= 0;
			counter <= 4;
			mem[3] <= {1'b1, 4'b0, r_name, f_c[7:0] }; 
			mem[2] <= {1'b1, 4'b0, r_name, f_c[15:8] }; 
			mem[1] <= {1'b1, 4'b0, r_name, f_c[23:16] }; 
			mem[0] <= {1'b1, 4'b0, r_name, f_c[31:24] }; 
		end
	end

	always @(posedge clk) begin
		if (!empty) begin
			to_r <= mem[rd_ptr_r];
			rd_ptr_r <= rd_ptr_r + 1;
			counter <= counter - 1;
		end
		else begin
			to_r <= 0;
			rd_ptr_r <= 0;
		end
	end
	always @(posedge clk) begin
		if (f_r != 0) begin
			suppl_data <= (suppl_data << 8) + f_r[7:0]; 
			suppl_counter <= suppl_counter + 1;
		end
		if (suppl_counter == 4)begin
			suppl_counter <= 0;
			suppl_data <= 0;
			to_c <= suppl_data;
		end else begin
			to_c <= 0;
		end
	end

endmodule
