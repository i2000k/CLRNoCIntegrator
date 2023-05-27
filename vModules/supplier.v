module supplier(
    clk,
    rst,
    wr_en,
    rd_en,
    data_in,
    data_out,
    buf_empty,
    buf_full,
    fifo_counter,
);

  parameter IN_SIZE = 21;
  parameter DATA_SIZE = 32;
  input clk;
  input rst;
  input wr_en;
  input rd_en;
  input [IN_SIZE - 1:0] data_in;
  // Регистр для хранения объединения data
  output reg [DATA_SIZE-1:0] data_out;

  output reg buf_empty, buf_full;
  output reg [6:0] fifo_counter;

  localparam NUM_CHUNKS = IN_SIZE / DATA_SIZE;

  reg [3:0] rd_ptr, wr_ptr;
  reg [IN_SIZE-1:0] buf_mem [3 : 0];

  reg [IN_SIZE-1:0] data_chunk0;
  reg [IN_SIZE-1:0] data_chunk1;
  reg [IN_SIZE-1:0] data_chunk2;
  reg [IN_SIZE-1:0] data_chunk3;


  always @(fifo_counter) begin
    buf_empty = (fifo_counter == 0);
    buf_full = (fifo_counter == 4);
  end
  // fifo counter
  always @(posedge clk or posedge rst) begin
    if (rst)
      fifo_counter <= 0;
    else if ( (!buf_full && wr_en) && (!buf_empty && rd_en))
      fifo_counter <= fifo_counter;
    else if (!buf_full && wr_en)
      fifo_counter <= fifo_counter + 1;
    else if (!buf_empty && rd_en)
      fifo_counter <= fifo_counter - 4;
    else
      fifo_counter <= fifo_counter;
  end
    //read from buffer
    always @(posedge clk or posedge rst) begin
        if (rst)
            data_out <= 0;
        else begin
            if (rd_en && buf_full)begin
              data_chunk0 = buf_mem[rd_ptr];
              rd_ptr = rd_ptr + 1;
              data_chunk1 = buf_mem[rd_ptr];
              rd_ptr = rd_ptr + 1;
              data_chunk2 = buf_mem[rd_ptr];
              rd_ptr = rd_ptr + 1;
              data_chunk3 = buf_mem[rd_ptr];
              rd_ptr = rd_ptr + 1;

              // sort data buckets
              if (data_chunk0[11:8] > data_chunk1[11:8]) begin
                data_chunk0 = data_chunk0 + data_chunk1;
                data_chunk1 = data_chunk0 - data_chunk1;
                data_chunk0 = data_chunk0 - data_chunk1;
              end

              if (data_chunk1[11:8] > data_chunk2[11:8]) begin
                data_chunk1 = data_chunk1 + data_chunk2;
                data_chunk2 = data_chunk1 - data_chunk2;
                data_chunk1 = data_chunk1 - data_chunk2;
              end

              if (data_chunk2[11:8] > data_chunk3[11:8]) begin
                data_chunk2 = data_chunk2 + data_chunk3;
                data_chunk3 = data_chunk2 - data_chunk3;
                data_chunk2 = data_chunk2 - data_chunk3;
              end

              if (data_chunk0[11:8] > data_chunk1[11:8]) begin
                data_chunk0 = data_chunk0 + data_chunk1;
                data_chunk1 = data_chunk0 - data_chunk1;
                data_chunk0 = data_chunk0 - data_chunk1;
              end

              if (data_chunk1[11:8] > data_chunk2[11:8]) begin
                data_chunk1 = data_chunk1 + data_chunk2;
                data_chunk2 = data_chunk1 - data_chunk2;
                data_chunk1 = data_chunk1 - data_chunk2;
              end

              if (data_chunk0[11:8] > data_chunk1[11:8]) begin
                data_chunk0 = data_chunk0 + data_chunk1;
                data_chunk1 = data_chunk0 - data_chunk1;
                data_chunk0 = data_chunk0 - data_chunk1;
              end

              //store buckets to bus
              data_out = {data_chunk3[7:0], data_chunk2[7:0], data_chunk1[7:0], data_chunk0[7:0]};
              $display("data: %b", data_out);
            end
            else
                data_out <= data_out;
        end
    end
    //write to buffer
    always @(posedge clk) begin
        if (wr_en && !buf_full)
            buf_mem[wr_ptr] <= data_in;
        else
            buf_mem[wr_ptr] <= buf_mem[wr_ptr];
    end

    // pointer management
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            wr_ptr <= 0;
            rd_ptr <= 0;
        end
        else begin
            if (!buf_full && wr_en)
                wr_ptr <= wr_ptr + 1;
            else
                wr_ptr <= wr_ptr;

            // if (!buf_empty && rd_en)
            //     rd_ptr <= rd_ptr + 1;
            // else
            //     rd_ptr <= rd_ptr;
        end
    end
endmodule