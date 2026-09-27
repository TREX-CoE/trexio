# Checks the one thing the TREXIO Fortran interface depends on: that a Fortran
# procedure declared with ISO_C_BINDING can call a C function and be linked with
# it. Mangling plays no part, because bind(C, name="...") states the symbol name.
cmake_minimum_required(VERSION 3.16)
project(TrexioBindC C Fortran)

add_executable(bind_c_check bind_c_check.c bind_c_check.f90)
