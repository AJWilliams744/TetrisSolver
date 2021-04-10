############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
############################################################
open_project TetrisSolverCode
set_top tetrissolver
add_files TetrisSolverCode/tetrissolver.cpp
add_files TetrisSolverCode/tetrissolver.h
add_files -tb TetrisSolverCode/testbench.cpp
open_solution "solution1"
set_part {xc7z010-clg400-1} -tool vivado
create_clock -period 10 -name default
#source "./TetrisSolverCode/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
