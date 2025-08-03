/* This file was generated from the templator_front.org org-mode file.
   To generate it, open templator_front.org in Emacs and execute
   M-x org-babel-tangle
*/

#ifndef TREXIO_H
#define TREXIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/* JSON configuration
{

"metadata": {
	   "code_num" : [ "dim", []                        ]
  ,            "code" : [ "str", [ "metadata.code_num" ]   ]
  ,      "author_num" : [ "dim", []                        ]
  ,          "author" : [ "str", [ "metadata.author_num" ] ]
  , "package_version" : [ "str", []                        ]
  ,     "description" : [ "str", []                        ]
  ,          "unsafe" : [ "int", []                        ]
} ,

"nucleus": {
	    "num" : [ "dim"  , []                     ]
  ,      "charge" : [ "float", [ "nucleus.num" ]      ]
  ,       "coord" : [ "float", [ "nucleus.num", "3" ] ]
  ,       "label" : [ "str"  , [ "nucleus.num" ]      ]
  , "point_group" : [ "str"  , []                     ]
  ,   "repulsion" : [ "float", []                     ]
} ,

"cell": {
	 "a" : [ "float", [ "3" ] ]
  ,      "b" : [ "float", [ "3" ] ]
  ,      "c" : [ "float", [ "3" ] ]
  ,    "g_a" : [ "float", [ "3" ] ]
  ,    "g_b" : [ "float", [ "3" ] ]
  ,    "g_c" : [ "float", [ "3" ] ]
  , "two_pi" : [ "int"  , []      ]
} ,

"pbc": {
	  "periodic" : [ "int"  , []                    ]
  ,    "k_point_num" : [ "dim"  , []                    ]
  ,        "k_point" : [ "float", [ "3" ]               ]
  , "k_point_weight" : [ "float", [ "pbc.k_point_num" ] ]
  ,       "madelung" : [ "float", []                    ]
} ,

"electron": {
       "num" : [ "dim", []  ]
  , "up_num" : [ "int", []  ]
  , "dn_num" : [ "int", []  ]
} ,

"state": {
	      "num" : [ "dim"  , []              ]
  ,            "id" : [ "index", []              ]
  ,        "energy" : [ "float", []              ]
  , "current_label" : [ "str"  , []              ]
  ,         "label" : [ "str"  , [ "state.num" ] ]
  ,     "file_name" : [ "str"  , [ "state.num" ] ]
} ,

"basis": {
		 "type" : [ "str"  , []                                                 ]
  ,          "prim_num" : [ "dim"  , []                                                 ]
  ,         "shell_num" : [ "dim"  , []                                                 ]
  ,      "nao_grid_num" : [ "dim"  , []                                                 ]
  ,  "interp_coeff_cnt" : [ "dim"  , []                                                 ]
  ,     "nucleus_index" : [ "index", [ "basis.shell_num" ]                              ]
  ,     "shell_ang_mom" : [ "int"  , [ "basis.shell_num" ]                              ]
  ,      "shell_factor" : [ "float", [ "basis.shell_num" ]                              ]
  ,           "r_power" : [ "int"  , [ "basis.shell_num" ]                              ]
  ,    "nao_grid_start" : [ "index", [ "basis.shell_num" ]                              ]
  ,     "nao_grid_size" : [ "dim"  , [ "basis.shell_num" ]                              ]
  ,       "shell_index" : [ "index", [ "basis.prim_num" ]                               ]
  ,          "exponent" : [ "float", [ "basis.prim_num" ]                               ]
  ,       "exponent_im" : [ "float", [ "basis.prim_num" ]                               ]
  ,       "coefficient" : [ "float", [ "basis.prim_num" ]                               ]
  ,    "coefficient_im" : [ "float", [ "basis.prim_num" ]                               ]
  ,   "oscillation_arg" : [ "float", [ "basis.prim_num" ]                               ]
  ,  "oscillation_kind" : [ "str"  , []                                                 ]
  ,       "prim_factor" : [ "float", [ "basis.prim_num" ]                               ]
  ,             "e_cut" : [ "float", []                                                 ]
  ,   "nao_grid_radius" : [ "float", [ "basis.nao_grid_num" ]                           ]
  ,      "nao_grid_phi" : [ "float", [ "basis.nao_grid_num" ]                           ]
  ,     "nao_grid_grad" : [ "float", [ "basis.nao_grid_num" ]                           ]
  ,      "nao_grid_lap" : [ "float", [ "basis.nao_grid_num" ]                           ]
  , "interpolator_kind" : [ "str"  , []                                                 ]
  ,  "interpolator_phi" : [ "float", [ "basis.nao_grid_num", "basis.interp_coeff_cnt" ] ]
  , "interpolator_grad" : [ "float", [ "basis.nao_grid_num", "basis.interp_coeff_cnt" ] ]
  ,  "interpolator_lap" : [ "float", [ "basis.nao_grid_num", "basis.interp_coeff_cnt" ] ]
} ,

"ecp": {
    "max_ang_mom_plus_1" : [ "int"  , [ "nucleus.num" ] ]
  ,             "z_core" : [ "int"  , [ "nucleus.num" ] ]
  ,                "num" : [ "dim"  , []                ]
  ,            "ang_mom" : [ "int"  , [ "ecp.num" ]     ]
  ,      "nucleus_index" : [ "index", [ "ecp.num" ]     ]
  ,           "exponent" : [ "float", [ "ecp.num" ]     ]
  ,        "coefficient" : [ "float", [ "ecp.num" ]     ]
  ,              "power" : [ "int"  , [ "ecp.num" ]     ]
} ,

"grid": {
      "description" : [ "str"  , []                 ]
  , "rad_precision" : [ "float", []                 ]
  ,           "num" : [ "dim"  , []                 ]
  ,   "max_ang_num" : [ "int"  , []                 ]
  ,   "min_ang_num" : [ "int"  , []                 ]
  ,         "coord" : [ "float", [ "grid.num" ]     ]
  ,        "weight" : [ "float", [ "grid.num" ]     ]
  ,       "ang_num" : [ "dim"  , []                 ]
  ,     "ang_coord" : [ "float", [ "grid.ang_num" ] ]
  ,    "ang_weight" : [ "float", [ "grid.ang_num" ] ]
  ,       "rad_num" : [ "dim"  , []                 ]
  ,     "rad_coord" : [ "float", [ "grid.rad_num" ] ]
  ,    "rad_weight" : [ "float", [ "grid.rad_num" ] ]
} ,

"ao": {
	"cartesian" : [ "int"  , []           ]
  ,           "num" : [ "dim"  , []           ]
  ,         "shell" : [ "index", [ "ao.num" ] ]
  , "normalization" : [ "float", [ "ao.num" ] ]
} ,

"ao_1e_int": {
		"overlap" : [ "float", [ "ao.num", "ao.num" ] ]
  ,             "kinetic" : [ "float", [ "ao.num", "ao.num" ] ]
  ,       "potential_n_e" : [ "float", [ "ao.num", "ao.num" ] ]
  ,                 "ecp" : [ "float", [ "ao.num", "ao.num" ] ]
  ,    "core_hamiltonian" : [ "float", [ "ao.num", "ao.num" ] ]
  ,          "overlap_im" : [ "float", [ "ao.num", "ao.num" ] ]
  ,          "kinetic_im" : [ "float", [ "ao.num", "ao.num" ] ]
  ,    "potential_n_e_im" : [ "float", [ "ao.num", "ao.num" ] ]
  ,              "ecp_im" : [ "float", [ "ao.num", "ao.num" ] ]
  , "core_hamiltonian_im" : [ "float", [ "ao.num", "ao.num" ] ]
} ,

"ao_2e_int": {
		    "eri" : [ "float sparse", [ "ao.num", "ao.num", "ao.num", "ao.num" ]              ]
  ,              "eri_lr" : [ "float sparse", [ "ao.num", "ao.num", "ao.num", "ao.num" ]              ]
  ,    "eri_cholesky_num" : [ "dim"         , []                                                      ]
  ,        "eri_cholesky" : [ "float sparse", [ "ao_2e_int.eri_cholesky_num", "ao.num", "ao.num" ]    ]
  , "eri_lr_cholesky_num" : [ "dim"         , []                                                      ]
  ,     "eri_lr_cholesky" : [ "float sparse", [ "ao_2e_int.eri_lr_cholesky_num", "ao.num", "ao.num" ] ]
} ,

"mo": {
	      "type" : [ "str"  , []                     ]
  ,            "num" : [ "dim"  , []                     ]
  ,    "coefficient" : [ "float", [ "mo.num", "ao.num" ] ]
  , "coefficient_im" : [ "float", [ "mo.num", "ao.num" ] ]
  ,          "class" : [ "str"  , [ "mo.num" ]           ]
  ,       "symmetry" : [ "str"  , [ "mo.num" ]           ]
  ,     "occupation" : [ "float", [ "mo.num" ]           ]
  ,         "energy" : [ "float", [ "mo.num" ]           ]
  ,           "spin" : [ "int"  , [ "mo.num" ]           ]
  ,        "k_point" : [ "index", [ "mo.num" ]           ]
} ,

"mo_1e_int": {
		"overlap" : [ "float", [ "mo.num", "mo.num" ] ]
  ,             "kinetic" : [ "float", [ "mo.num", "mo.num" ] ]
  ,       "potential_n_e" : [ "float", [ "mo.num", "mo.num" ] ]
  ,                 "ecp" : [ "float", [ "mo.num", "mo.num" ] ]
  ,    "core_hamiltonian" : [ "float", [ "mo.num", "mo.num" ] ]
  ,          "overlap_im" : [ "float", [ "mo.num", "mo.num" ] ]
  ,          "kinetic_im" : [ "float", [ "mo.num", "mo.num" ] ]
  ,    "potential_n_e_im" : [ "float", [ "mo.num", "mo.num" ] ]
  ,              "ecp_im" : [ "float", [ "mo.num", "mo.num" ] ]
  , "core_hamiltonian_im" : [ "float", [ "mo.num", "mo.num" ] ]
} ,

"mo_2e_int": {
		    "eri" : [ "float sparse", [ "mo.num", "mo.num", "mo.num", "mo.num" ]              ]
  ,              "eri_lr" : [ "float sparse", [ "mo.num", "mo.num", "mo.num", "mo.num" ]              ]
  ,    "eri_cholesky_num" : [ "dim"         , []                                                      ]
  ,        "eri_cholesky" : [ "float sparse", [ "mo_2e_int.eri_cholesky_num", "mo.num", "mo.num" ]    ]
  , "eri_lr_cholesky_num" : [ "dim"         , []                                                      ]
  ,     "eri_lr_cholesky" : [ "float sparse", [ "mo_2e_int.eri_lr_cholesky_num", "mo.num", "mo.num" ] ]
} ,

"determinant": {
	    "num" : [ "dim readonly"  , []                    ]
  ,        "list" : [ "int special"   , [ "determinant.num" ] ]
  , "coefficient" : [ "float buffered", [ "determinant.num" ] ]
} ,

"csf": {
		"num" : [ "dim"           , []                               ]
  ,     "coefficient" : [ "float buffered", [ "csf.num" ]                    ]
  , "det_coefficient" : [ "float sparse"  , [ "csf.num", "determinant.num" ] ]
} ,

"amplitude": {
	   "single" : [ "float sparse", [ "mo.num", "mo.num" ]                                                             ]
  ,    "single_exp" : [ "float sparse", [ "mo.num", "mo.num" ]                                                             ]
  ,        "double" : [ "float sparse", [ "mo.num", "mo.num", "mo.num", "mo.num" ]                                         ]
  ,    "double_exp" : [ "float sparse", [ "mo.num", "mo.num", "mo.num", "mo.num" ]                                         ]
  ,        "triple" : [ "float sparse", [ "mo.num", "mo.num", "mo.num", "mo.num", "mo.num", "mo.num" ]                     ]
  ,    "triple_exp" : [ "float sparse", [ "mo.num", "mo.num", "mo.num", "mo.num", "mo.num", "mo.num" ]                     ]
  ,     "quadruple" : [ "float sparse", [ "mo.num", "mo.num", "mo.num", "mo.num", "mo.num", "mo.num", "mo.num", "mo.num" ] ]
  , "quadruple_exp" : [ "float sparse", [ "mo.num", "mo.num", "mo.num", "mo.num", "mo.num", "mo.num", "mo.num", "mo.num" ] ]
} ,

"rdm": {
		      "1e" : [ "float"       , [ "mo.num", "mo.num" ]                                               ]
  ,                "1e_up" : [ "float"       , [ "mo.num", "mo.num" ]                                               ]
  ,                "1e_dn" : [ "float"       , [ "mo.num", "mo.num" ]                                               ]
  ,        "1e_transition" : [ "float"       , [ "state.num", "state.num", "mo.num", "mo.num" ]                     ]
  ,                   "2e" : [ "float sparse", [ "mo.num", "mo.num", "mo.num", "mo.num" ]                           ]
  ,              "2e_upup" : [ "float sparse", [ "mo.num", "mo.num", "mo.num", "mo.num" ]                           ]
  ,              "2e_dndn" : [ "float sparse", [ "mo.num", "mo.num", "mo.num", "mo.num" ]                           ]
  ,              "2e_updn" : [ "float sparse", [ "mo.num", "mo.num", "mo.num", "mo.num" ]                           ]
  ,        "2e_transition" : [ "float sparse", [ "state.num", "state.num", "mo.num", "mo.num", "mo.num", "mo.num" ] ]
  ,      "2e_cholesky_num" : [ "dim"         , []                                                                   ]
  ,          "2e_cholesky" : [ "float sparse", [ "rdm.2e_cholesky_num", "mo.num", "mo.num" ]                        ]
  , "2e_upup_cholesky_num" : [ "dim"         , []                                                                   ]
  ,     "2e_upup_cholesky" : [ "float sparse", [ "rdm.2e_upup_cholesky_num", "mo.num", "mo.num" ]                   ]
  , "2e_dndn_cholesky_num" : [ "dim"         , []                                                                   ]
  ,     "2e_dndn_cholesky" : [ "float sparse", [ "rdm.2e_dndn_cholesky_num", "mo.num", "mo.num" ]                   ]
  , "2e_updn_cholesky_num" : [ "dim"         , []                                                                   ]
  ,     "2e_updn_cholesky" : [ "float sparse", [ "rdm.2e_updn_cholesky_num", "mo.num", "mo.num" ]                   ]
} ,

"jastrow": {
	   "type" : [ "str"  , []                    ]
  ,      "en_num" : [ "dim"  , []                    ]
  ,      "ee_num" : [ "dim"  , []                    ]
  ,     "een_num" : [ "dim"  , []                    ]
  ,          "en" : [ "float", [ "jastrow.en_num" ]  ]
  ,          "ee" : [ "float", [ "jastrow.ee_num" ]  ]
  ,         "een" : [ "float", [ "jastrow.een_num" ] ]
  ,  "en_nucleus" : [ "index", [ "jastrow.en_num" ]  ]
  , "een_nucleus" : [ "index", [ "jastrow.een_num" ] ]
  ,  "ee_scaling" : [ "float", []                    ]
  ,  "en_scaling" : [ "float", [ "nucleus.num" ]     ]
} ,

"qmc": {
      "num" : [ "dim"  , []                                 ]
  , "point" : [ "float", [ "qmc.num", "electron.num", "3" ] ]
  ,   "psi" : [ "float", [ "qmc.num" ]                      ]
  , "e_loc" : [ "float", [ "qmc.num" ]                      ]
}

}
*/
typedef int32_t trexio_exit_code;

#define TREXIO_FAILURE                 ((trexio_exit_code) -1)
#define TREXIO_SUCCESS                 ((trexio_exit_code) 0)
#define TREXIO_INVALID_ARG_1           ((trexio_exit_code) 1)
#define TREXIO_INVALID_ARG_2           ((trexio_exit_code) 2)
#define TREXIO_INVALID_ARG_3           ((trexio_exit_code) 3)
#define TREXIO_INVALID_ARG_4           ((trexio_exit_code) 4)
#define TREXIO_INVALID_ARG_5           ((trexio_exit_code) 5)
#define TREXIO_END                     ((trexio_exit_code) 6)
#define TREXIO_READONLY                ((trexio_exit_code) 7)
#define TREXIO_ERRNO                   ((trexio_exit_code) 8)
#define TREXIO_INVALID_ID              ((trexio_exit_code) 9)
#define TREXIO_ALLOCATION_FAILED       ((trexio_exit_code) 10)
#define TREXIO_HAS_NOT                 ((trexio_exit_code) 11)
#define TREXIO_INVALID_NUM             ((trexio_exit_code) 12)
#define TREXIO_ATTR_ALREADY_EXISTS     ((trexio_exit_code) 13)
#define TREXIO_DSET_ALREADY_EXISTS     ((trexio_exit_code) 14)
#define TREXIO_OPEN_ERROR              ((trexio_exit_code) 15)
#define TREXIO_LOCK_ERROR              ((trexio_exit_code) 16)
#define TREXIO_UNLOCK_ERROR            ((trexio_exit_code) 17)
#define TREXIO_FILE_ERROR              ((trexio_exit_code) 18)
#define TREXIO_GROUP_READ_ERROR        ((trexio_exit_code) 19)
#define TREXIO_GROUP_WRITE_ERROR       ((trexio_exit_code) 20)
#define TREXIO_ELEM_READ_ERROR         ((trexio_exit_code) 21)
#define TREXIO_ELEM_WRITE_ERROR        ((trexio_exit_code) 22)
#define TREXIO_UNSAFE_ARRAY_DIM        ((trexio_exit_code) 23)
#define TREXIO_ATTR_MISSING            ((trexio_exit_code) 24)
#define TREXIO_DSET_MISSING            ((trexio_exit_code) 25)
#define TREXIO_BACK_END_MISSING        ((trexio_exit_code) 26)
#define TREXIO_INVALID_ARG_6           ((trexio_exit_code) 27)
#define TREXIO_INVALID_ARG_7           ((trexio_exit_code) 28)
#define TREXIO_INVALID_ARG_8           ((trexio_exit_code) 29)
#define TREXIO_INVALID_STR_LEN         ((trexio_exit_code) 30)
#define TREXIO_INT_SIZE_OVERFLOW       ((trexio_exit_code) 31)
#define TREXIO_SAFE_MODE               ((trexio_exit_code) 32)
#define TREXIO_INVALID_ELECTRON_NUM    ((trexio_exit_code) 33)
#define TREXIO_INVALID_DETERMINANT_NUM ((trexio_exit_code) 34)
#define TREXIO_INVALID_STATE           ((trexio_exit_code) 35)
#define TREXIO_VERSION_PARSING_ISSUE   ((trexio_exit_code) 36)
#define TREXIO_PHASE_CHANGE            ((trexio_exit_code) 37)
#define TREXIO_INVALID_MO_INDEX        ((trexio_exit_code) 38)
#define TREXIO_INVALID_ARG_9           ((trexio_exit_code) 39)
#define TREXIO_INVALID_ARG_10          ((trexio_exit_code) 40)
#define TREXIO_INVALID_ARG_11          ((trexio_exit_code) 41)
#define TREXIO_INVALID_ARG_12          ((trexio_exit_code) 42)
#define TREXIO_INVALID_ARG_13          ((trexio_exit_code) 43)
#define TREXIO_INVALID_ARG_14          ((trexio_exit_code) 44)
#define TREXIO_CORRUPTION_ATTEMPT      ((trexio_exit_code) 45)

const char* trexio_string_of_error(const trexio_exit_code error);
void trexio_string_of_error_f(const trexio_exit_code error, const int32_t size_string, char* const result);

typedef int32_t back_end_t;

#define TREXIO_HDF5             ( (back_end_t) 0 )
#define TREXIO_TEXT             ( (back_end_t) 1 )
#define TREXIO_INVALID_BACK_END ( (back_end_t) 2 )
#define TREXIO_AUTO             TREXIO_INVALID_BACK_END
/*#define TREXIO_JSON             ( (back_end_t) 2 )*/

#define TREXIO_DELIM            "\n"

bool trexio_has_backend(back_end_t back_end);
bool trexio_has_back_end(back_end_t back_end);

typedef struct trexio_s trexio_t;

trexio_t* trexio_open(const char* file_name, const char mode,
                      const back_end_t back_end, trexio_exit_code* const rc_open);

trexio_exit_code trexio_set_one_based(trexio_t* file);

trexio_exit_code trexio_close(trexio_t* file);

trexio_exit_code trexio_flush(trexio_t* file);

trexio_exit_code trexio_inquire(const char* file_name);

trexio_exit_code trexio_cp(const char* source_file_name, const char* dest_file_name);

trexio_exit_code trexio_set_state(trexio_t* file, const int32_t num);
trexio_exit_code trexio_get_state(trexio_t* file, int32_t* const num);

trexio_exit_code trexio_info(void);
trexio_exit_code trexio_mark_safety(trexio_t* const file, const int32_t safety_flag);

typedef int64_t  bitfield_t;

#define TREXIO_ORBITAL_SHIFT      1
#define TREXIO_INT_SIZE           64
#define TREXIO_NORB_PER_INT       ( 8*sizeof(bitfield_t) )
#define TREXIO_NORB_PER_INT_SHIFT ( trailz( TREXIO_NORB_PER_INT ) )

trexio_exit_code trexio_to_orbital_list (const int32_t N_int, const bitfield_t* d1, int32_t* const list, int32_t* const occupied_num);
trexio_exit_code trexio_to_orbital_list_up_dn (const int32_t N_int, const bitfield_t* d1, int32_t* const list_up, int32_t* const list_dn, int32_t* const occ_num_up, int32_t* const occ_num_dn);
trexio_exit_code trexio_safe_to_orbital_list (const int32_t N_int, const bitfield_t* dset_in, const int64_t dim_in, int32_t* const dset_out, const int64_t dim_out, int32_t* const num);
trexio_exit_code trexio_safe_to_orbital_list_up_dn (const int32_t N_int, const bitfield_t* dset_in, const int64_t dim_in, int32_t* const dset_up_out, const int64_t dim_up_out, int32_t* const dset_dn_out, const int64_t dim_dn_out, int32_t* const num_up, int32_t* const num_dn);
trexio_exit_code trexio_to_bitfield_list (const int32_t* orb_list, const int32_t occupied_num, bitfield_t* const bit_list, const int32_t N_int);

trexio_exit_code trexio_convert_nao_radius_32 (const float r,
  const float* const grid_r, float* const log_r_out);
trexio_exit_code trexio_convert_nao_radius_64 (const double r,
  const double* const grid_r, double* const log_r_out);
trexio_exit_code trexio_convert_nao_radius_py (const double r,
  double* grid_r, int32_t n_grid_r, double* const log_r_out);
trexio_exit_code trexio_evaluate_nao_radial (const int32_t shell_index,
  const double r, const int32_t* const grid_start, const int32_t* const grid_size,
  const double* const grid_r, const double* const interpolator,
  const double* const normalization, double* const amplitude);

trexio_exit_code trexio_evaluate_nao_radial_all (const int32_t shell_num,
  const int32_t* const nucleus_index, const double* const nucleus_coords,
  const int32_t* const grid_start, const int32_t* const grid_size,
  const double* const grid_r, const double* const interpolator, const double* const normalization,
  const double rx, const double ry, const double rz, double* const amplitude);

trexio_exit_code trexio_evaluate_nao_radial_py (const int shell_index,
  const double r, int64_t* grid_start, int n_grid_st, int64_t* grid_size,
  int n_grid_si, double* grid_r, int n_grid_r, double* interpolator,
  int n_interp, double* normalization, int n_norm, double* const amplitude);

trexio_exit_code trexio_evaluate_nao_radial_all_py (const int32_t shell_num,
  int64_t* nucleus_index, int n_nuc_id, double* nucleus_coords, int n_nuc_co,
  int64_t* grid_start, int n_grid_st, int64_t* grid_size, int n_grid_si,
  double* grid_r, int n_grid_r, double* interpolator, int n_interp, double* normalization, int n_norm,
  const double rx, const double ry, const double rz, double* const amplitudes, int amplitude_cnt);

#define TREXIO_PACKAGE_VERSION "2.5.2"
#define TREXIO_VERSION_MAJOR 2
#define TREXIO_VERSION_MINOR 5
#define TREXIO_VERSION_PATCH 2
#define TREXIO_GIT_HASH "7226acee17fc7562649931807143795c2f9af893"

trexio_exit_code trexio_delete_metadata(trexio_t* const file);

trexio_exit_code trexio_delete_nucleus(trexio_t* const file);

trexio_exit_code trexio_delete_cell(trexio_t* const file);

trexio_exit_code trexio_delete_pbc(trexio_t* const file);

trexio_exit_code trexio_delete_electron(trexio_t* const file);

trexio_exit_code trexio_delete_state(trexio_t* const file);

trexio_exit_code trexio_delete_basis(trexio_t* const file);

trexio_exit_code trexio_delete_ecp(trexio_t* const file);

trexio_exit_code trexio_delete_grid(trexio_t* const file);

trexio_exit_code trexio_delete_ao(trexio_t* const file);

trexio_exit_code trexio_delete_ao_1e_int(trexio_t* const file);

trexio_exit_code trexio_delete_ao_2e_int(trexio_t* const file);

trexio_exit_code trexio_delete_mo(trexio_t* const file);

trexio_exit_code trexio_delete_mo_1e_int(trexio_t* const file);

trexio_exit_code trexio_delete_mo_2e_int(trexio_t* const file);

trexio_exit_code trexio_delete_determinant(trexio_t* const file);

trexio_exit_code trexio_delete_csf(trexio_t* const file);

trexio_exit_code trexio_delete_amplitude(trexio_t* const file);

trexio_exit_code trexio_delete_rdm(trexio_t* const file);

trexio_exit_code trexio_delete_jastrow(trexio_t* const file);

trexio_exit_code trexio_delete_qmc(trexio_t* const file);

trexio_exit_code trexio_has_metadata_code_num(trexio_t* const file);
trexio_exit_code trexio_read_metadata_code_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_metadata_code_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_metadata_code_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_metadata_code_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_metadata_code_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_metadata_code_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_metadata_author_num(trexio_t* const file);
trexio_exit_code trexio_read_metadata_author_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_metadata_author_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_metadata_author_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_metadata_author_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_metadata_author_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_metadata_author_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_metadata_unsafe(trexio_t* const file);
trexio_exit_code trexio_read_metadata_unsafe(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_metadata_unsafe(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_metadata_unsafe_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_metadata_unsafe_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_metadata_unsafe_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_metadata_unsafe_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_nucleus_num(trexio_t* const file);
trexio_exit_code trexio_read_nucleus_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_nucleus_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_nucleus_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_nucleus_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_nucleus_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_nucleus_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_nucleus_repulsion(trexio_t* const file);
trexio_exit_code trexio_read_nucleus_repulsion(trexio_t* const file, double* const num);
trexio_exit_code trexio_write_nucleus_repulsion(trexio_t* const file, const double num);
trexio_exit_code trexio_read_nucleus_repulsion_32(trexio_t* const file, float* const num);
trexio_exit_code trexio_write_nucleus_repulsion_32(trexio_t* const file, const float num);
trexio_exit_code trexio_read_nucleus_repulsion_64(trexio_t* const file, double* const num);
trexio_exit_code trexio_write_nucleus_repulsion_64(trexio_t* const file, const double num);

trexio_exit_code trexio_has_cell_two_pi(trexio_t* const file);
trexio_exit_code trexio_read_cell_two_pi(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_cell_two_pi(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_cell_two_pi_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_cell_two_pi_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_cell_two_pi_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_cell_two_pi_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_pbc_periodic(trexio_t* const file);
trexio_exit_code trexio_read_pbc_periodic(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_pbc_periodic(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_pbc_periodic_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_pbc_periodic_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_pbc_periodic_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_pbc_periodic_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_pbc_k_point_num(trexio_t* const file);
trexio_exit_code trexio_read_pbc_k_point_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_pbc_k_point_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_pbc_k_point_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_pbc_k_point_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_pbc_k_point_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_pbc_k_point_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_pbc_madelung(trexio_t* const file);
trexio_exit_code trexio_read_pbc_madelung(trexio_t* const file, double* const num);
trexio_exit_code trexio_write_pbc_madelung(trexio_t* const file, const double num);
trexio_exit_code trexio_read_pbc_madelung_32(trexio_t* const file, float* const num);
trexio_exit_code trexio_write_pbc_madelung_32(trexio_t* const file, const float num);
trexio_exit_code trexio_read_pbc_madelung_64(trexio_t* const file, double* const num);
trexio_exit_code trexio_write_pbc_madelung_64(trexio_t* const file, const double num);

trexio_exit_code trexio_has_electron_num(trexio_t* const file);
trexio_exit_code trexio_read_electron_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_electron_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_electron_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_electron_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_electron_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_electron_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_electron_up_num(trexio_t* const file);
trexio_exit_code trexio_read_electron_up_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_electron_up_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_electron_up_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_electron_up_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_electron_up_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_electron_up_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_electron_dn_num(trexio_t* const file);
trexio_exit_code trexio_read_electron_dn_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_electron_dn_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_electron_dn_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_electron_dn_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_electron_dn_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_electron_dn_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_state_num(trexio_t* const file);
trexio_exit_code trexio_read_state_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_state_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_state_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_state_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_state_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_state_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_state_id(trexio_t* const file);
trexio_exit_code trexio_read_state_id(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_state_id(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_state_id_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_state_id_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_state_id_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_state_id_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_state_energy(trexio_t* const file);
trexio_exit_code trexio_read_state_energy(trexio_t* const file, double* const num);
trexio_exit_code trexio_write_state_energy(trexio_t* const file, const double num);
trexio_exit_code trexio_read_state_energy_32(trexio_t* const file, float* const num);
trexio_exit_code trexio_write_state_energy_32(trexio_t* const file, const float num);
trexio_exit_code trexio_read_state_energy_64(trexio_t* const file, double* const num);
trexio_exit_code trexio_write_state_energy_64(trexio_t* const file, const double num);

trexio_exit_code trexio_has_basis_prim_num(trexio_t* const file);
trexio_exit_code trexio_read_basis_prim_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_basis_prim_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_basis_prim_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_basis_prim_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_basis_prim_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_basis_prim_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_basis_shell_num(trexio_t* const file);
trexio_exit_code trexio_read_basis_shell_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_basis_shell_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_basis_shell_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_basis_shell_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_basis_shell_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_basis_shell_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_basis_nao_grid_num(trexio_t* const file);
trexio_exit_code trexio_read_basis_nao_grid_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_basis_nao_grid_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_basis_nao_grid_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_basis_nao_grid_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_basis_nao_grid_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_basis_nao_grid_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_basis_interp_coeff_cnt(trexio_t* const file);
trexio_exit_code trexio_read_basis_interp_coeff_cnt(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_basis_interp_coeff_cnt(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_basis_interp_coeff_cnt_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_basis_interp_coeff_cnt_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_basis_interp_coeff_cnt_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_basis_interp_coeff_cnt_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_basis_e_cut(trexio_t* const file);
trexio_exit_code trexio_read_basis_e_cut(trexio_t* const file, double* const num);
trexio_exit_code trexio_write_basis_e_cut(trexio_t* const file, const double num);
trexio_exit_code trexio_read_basis_e_cut_32(trexio_t* const file, float* const num);
trexio_exit_code trexio_write_basis_e_cut_32(trexio_t* const file, const float num);
trexio_exit_code trexio_read_basis_e_cut_64(trexio_t* const file, double* const num);
trexio_exit_code trexio_write_basis_e_cut_64(trexio_t* const file, const double num);

trexio_exit_code trexio_has_ecp_num(trexio_t* const file);
trexio_exit_code trexio_read_ecp_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_ecp_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_ecp_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_ecp_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_ecp_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_ecp_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_grid_rad_precision(trexio_t* const file);
trexio_exit_code trexio_read_grid_rad_precision(trexio_t* const file, double* const num);
trexio_exit_code trexio_write_grid_rad_precision(trexio_t* const file, const double num);
trexio_exit_code trexio_read_grid_rad_precision_32(trexio_t* const file, float* const num);
trexio_exit_code trexio_write_grid_rad_precision_32(trexio_t* const file, const float num);
trexio_exit_code trexio_read_grid_rad_precision_64(trexio_t* const file, double* const num);
trexio_exit_code trexio_write_grid_rad_precision_64(trexio_t* const file, const double num);

trexio_exit_code trexio_has_grid_num(trexio_t* const file);
trexio_exit_code trexio_read_grid_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_grid_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_grid_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_grid_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_grid_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_grid_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_grid_max_ang_num(trexio_t* const file);
trexio_exit_code trexio_read_grid_max_ang_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_grid_max_ang_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_grid_max_ang_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_grid_max_ang_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_grid_max_ang_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_grid_max_ang_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_grid_min_ang_num(trexio_t* const file);
trexio_exit_code trexio_read_grid_min_ang_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_grid_min_ang_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_grid_min_ang_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_grid_min_ang_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_grid_min_ang_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_grid_min_ang_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_grid_ang_num(trexio_t* const file);
trexio_exit_code trexio_read_grid_ang_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_grid_ang_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_grid_ang_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_grid_ang_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_grid_ang_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_grid_ang_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_grid_rad_num(trexio_t* const file);
trexio_exit_code trexio_read_grid_rad_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_grid_rad_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_grid_rad_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_grid_rad_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_grid_rad_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_grid_rad_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_ao_cartesian(trexio_t* const file);
trexio_exit_code trexio_read_ao_cartesian(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_ao_cartesian(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_ao_cartesian_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_ao_cartesian_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_ao_cartesian_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_ao_cartesian_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_ao_num(trexio_t* const file);
trexio_exit_code trexio_read_ao_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_ao_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_ao_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_ao_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_ao_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_ao_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_ao_2e_int_eri_cholesky_num(trexio_t* const file);
trexio_exit_code trexio_read_ao_2e_int_eri_cholesky_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_ao_2e_int_eri_cholesky_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_ao_2e_int_eri_cholesky_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_ao_2e_int_eri_cholesky_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_ao_2e_int_eri_cholesky_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_ao_2e_int_eri_cholesky_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_ao_2e_int_eri_lr_cholesky_num(trexio_t* const file);
trexio_exit_code trexio_read_ao_2e_int_eri_lr_cholesky_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_ao_2e_int_eri_lr_cholesky_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_ao_2e_int_eri_lr_cholesky_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_ao_2e_int_eri_lr_cholesky_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_ao_2e_int_eri_lr_cholesky_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_ao_2e_int_eri_lr_cholesky_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_mo_num(trexio_t* const file);
trexio_exit_code trexio_read_mo_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_mo_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_mo_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_mo_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_mo_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_mo_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_mo_2e_int_eri_cholesky_num(trexio_t* const file);
trexio_exit_code trexio_read_mo_2e_int_eri_cholesky_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_mo_2e_int_eri_cholesky_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_mo_2e_int_eri_cholesky_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_mo_2e_int_eri_cholesky_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_mo_2e_int_eri_cholesky_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_mo_2e_int_eri_cholesky_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_mo_2e_int_eri_lr_cholesky_num(trexio_t* const file);
trexio_exit_code trexio_read_mo_2e_int_eri_lr_cholesky_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_mo_2e_int_eri_lr_cholesky_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_mo_2e_int_eri_lr_cholesky_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_mo_2e_int_eri_lr_cholesky_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_mo_2e_int_eri_lr_cholesky_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_mo_2e_int_eri_lr_cholesky_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_determinant_num(trexio_t* const file);
trexio_exit_code trexio_read_determinant_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_read_determinant_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_read_determinant_num_64(trexio_t* const file, int64_t* const num);

trexio_exit_code trexio_has_csf_num(trexio_t* const file);
trexio_exit_code trexio_read_csf_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_csf_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_csf_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_csf_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_csf_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_csf_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_rdm_2e_cholesky_num(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e_cholesky_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_rdm_2e_cholesky_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_rdm_2e_cholesky_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_rdm_2e_cholesky_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_rdm_2e_cholesky_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_rdm_2e_cholesky_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_rdm_2e_upup_cholesky_num(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e_upup_cholesky_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_rdm_2e_upup_cholesky_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_rdm_2e_upup_cholesky_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_rdm_2e_upup_cholesky_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_rdm_2e_upup_cholesky_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_rdm_2e_upup_cholesky_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_rdm_2e_dndn_cholesky_num(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e_dndn_cholesky_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_rdm_2e_dndn_cholesky_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_rdm_2e_dndn_cholesky_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_rdm_2e_dndn_cholesky_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_rdm_2e_dndn_cholesky_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_rdm_2e_dndn_cholesky_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_rdm_2e_updn_cholesky_num(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e_updn_cholesky_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_rdm_2e_updn_cholesky_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_rdm_2e_updn_cholesky_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_rdm_2e_updn_cholesky_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_rdm_2e_updn_cholesky_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_rdm_2e_updn_cholesky_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_jastrow_en_num(trexio_t* const file);
trexio_exit_code trexio_read_jastrow_en_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_jastrow_en_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_jastrow_en_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_jastrow_en_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_jastrow_en_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_jastrow_en_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_jastrow_ee_num(trexio_t* const file);
trexio_exit_code trexio_read_jastrow_ee_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_jastrow_ee_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_jastrow_ee_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_jastrow_ee_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_jastrow_ee_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_jastrow_ee_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_jastrow_een_num(trexio_t* const file);
trexio_exit_code trexio_read_jastrow_een_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_jastrow_een_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_jastrow_een_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_jastrow_een_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_jastrow_een_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_jastrow_een_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_jastrow_ee_scaling(trexio_t* const file);
trexio_exit_code trexio_read_jastrow_ee_scaling(trexio_t* const file, double* const num);
trexio_exit_code trexio_write_jastrow_ee_scaling(trexio_t* const file, const double num);
trexio_exit_code trexio_read_jastrow_ee_scaling_32(trexio_t* const file, float* const num);
trexio_exit_code trexio_write_jastrow_ee_scaling_32(trexio_t* const file, const float num);
trexio_exit_code trexio_read_jastrow_ee_scaling_64(trexio_t* const file, double* const num);
trexio_exit_code trexio_write_jastrow_ee_scaling_64(trexio_t* const file, const double num);

trexio_exit_code trexio_has_qmc_num(trexio_t* const file);
trexio_exit_code trexio_read_qmc_num(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_qmc_num(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_qmc_num_32(trexio_t* const file, int32_t* const num);
trexio_exit_code trexio_write_qmc_num_32(trexio_t* const file, const int32_t num);
trexio_exit_code trexio_read_qmc_num_64(trexio_t* const file, int64_t* const num);
trexio_exit_code trexio_write_qmc_num_64(trexio_t* const file, const int64_t num);

trexio_exit_code trexio_has_metadata_package_version(trexio_t* const file);
trexio_exit_code trexio_read_metadata_package_version(trexio_t* const file, char* const str_out, const int32_t max_str_len);
trexio_exit_code trexio_write_metadata_package_version(trexio_t* const file, const char* str, const int32_t max_str_len);

trexio_exit_code trexio_has_metadata_description(trexio_t* const file);
trexio_exit_code trexio_read_metadata_description(trexio_t* const file, char* const str_out, const int32_t max_str_len);
trexio_exit_code trexio_write_metadata_description(trexio_t* const file, const char* str, const int32_t max_str_len);

trexio_exit_code trexio_has_nucleus_point_group(trexio_t* const file);
trexio_exit_code trexio_read_nucleus_point_group(trexio_t* const file, char* const str_out, const int32_t max_str_len);
trexio_exit_code trexio_write_nucleus_point_group(trexio_t* const file, const char* str, const int32_t max_str_len);

trexio_exit_code trexio_has_state_current_label(trexio_t* const file);
trexio_exit_code trexio_read_state_current_label(trexio_t* const file, char* const str_out, const int32_t max_str_len);
trexio_exit_code trexio_write_state_current_label(trexio_t* const file, const char* str, const int32_t max_str_len);

trexio_exit_code trexio_has_basis_type(trexio_t* const file);
trexio_exit_code trexio_read_basis_type(trexio_t* const file, char* const str_out, const int32_t max_str_len);
trexio_exit_code trexio_write_basis_type(trexio_t* const file, const char* str, const int32_t max_str_len);

trexio_exit_code trexio_has_basis_oscillation_kind(trexio_t* const file);
trexio_exit_code trexio_read_basis_oscillation_kind(trexio_t* const file, char* const str_out, const int32_t max_str_len);
trexio_exit_code trexio_write_basis_oscillation_kind(trexio_t* const file, const char* str, const int32_t max_str_len);

trexio_exit_code trexio_has_basis_interpolator_kind(trexio_t* const file);
trexio_exit_code trexio_read_basis_interpolator_kind(trexio_t* const file, char* const str_out, const int32_t max_str_len);
trexio_exit_code trexio_write_basis_interpolator_kind(trexio_t* const file, const char* str, const int32_t max_str_len);

trexio_exit_code trexio_has_grid_description(trexio_t* const file);
trexio_exit_code trexio_read_grid_description(trexio_t* const file, char* const str_out, const int32_t max_str_len);
trexio_exit_code trexio_write_grid_description(trexio_t* const file, const char* str, const int32_t max_str_len);

trexio_exit_code trexio_has_mo_type(trexio_t* const file);
trexio_exit_code trexio_read_mo_type(trexio_t* const file, char* const str_out, const int32_t max_str_len);
trexio_exit_code trexio_write_mo_type(trexio_t* const file, const char* str, const int32_t max_str_len);

trexio_exit_code trexio_has_jastrow_type(trexio_t* const file);
trexio_exit_code trexio_read_jastrow_type(trexio_t* const file, char* const str_out, const int32_t max_str_len);
trexio_exit_code trexio_write_jastrow_type(trexio_t* const file, const char* str, const int32_t max_str_len);

trexio_exit_code trexio_has_determinant_coefficient(trexio_t* const file);
trexio_exit_code trexio_read_determinant_coefficient(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, double* const dset);
trexio_exit_code trexio_read_safe_determinant_coefficient(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_determinant_coefficient(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const double* dset);
trexio_exit_code trexio_write_safe_determinant_coefficient(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_determinant_coefficient_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_has_csf_coefficient(trexio_t* const file);
trexio_exit_code trexio_read_csf_coefficient(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, double* const dset);
trexio_exit_code trexio_read_safe_csf_coefficient(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_csf_coefficient(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const double* dset);
trexio_exit_code trexio_write_safe_csf_coefficient(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_csf_coefficient_size(trexio_t* const file, int64_t* const size_max);

trexio_exit_code trexio_has_nucleus_charge(trexio_t* const file);
trexio_exit_code trexio_read_nucleus_charge(trexio_t* const file, double* const nucleus_charge);
trexio_exit_code trexio_write_nucleus_charge(trexio_t* const file, const double* nucleus_charge);
trexio_exit_code trexio_read_nucleus_charge_32(trexio_t* const file, float* const nucleus_charge);
trexio_exit_code trexio_write_nucleus_charge_32(trexio_t* const file, const float* nucleus_charge);
trexio_exit_code trexio_read_nucleus_charge_64(trexio_t* const file, double* const nucleus_charge);
trexio_exit_code trexio_write_nucleus_charge_64(trexio_t* const file, const double* nucleus_charge);
trexio_exit_code trexio_read_safe_nucleus_charge(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_nucleus_charge(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_nucleus_charge_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_nucleus_charge_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_nucleus_charge_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_nucleus_charge_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_nucleus_coord(trexio_t* const file);
trexio_exit_code trexio_read_nucleus_coord(trexio_t* const file, double* const nucleus_coord);
trexio_exit_code trexio_write_nucleus_coord(trexio_t* const file, const double* nucleus_coord);
trexio_exit_code trexio_read_nucleus_coord_32(trexio_t* const file, float* const nucleus_coord);
trexio_exit_code trexio_write_nucleus_coord_32(trexio_t* const file, const float* nucleus_coord);
trexio_exit_code trexio_read_nucleus_coord_64(trexio_t* const file, double* const nucleus_coord);
trexio_exit_code trexio_write_nucleus_coord_64(trexio_t* const file, const double* nucleus_coord);
trexio_exit_code trexio_read_safe_nucleus_coord(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_nucleus_coord(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_nucleus_coord_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_nucleus_coord_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_nucleus_coord_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_nucleus_coord_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_cell_a(trexio_t* const file);
trexio_exit_code trexio_read_cell_a(trexio_t* const file, double* const cell_a);
trexio_exit_code trexio_write_cell_a(trexio_t* const file, const double* cell_a);
trexio_exit_code trexio_read_cell_a_32(trexio_t* const file, float* const cell_a);
trexio_exit_code trexio_write_cell_a_32(trexio_t* const file, const float* cell_a);
trexio_exit_code trexio_read_cell_a_64(trexio_t* const file, double* const cell_a);
trexio_exit_code trexio_write_cell_a_64(trexio_t* const file, const double* cell_a);
trexio_exit_code trexio_read_safe_cell_a(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_a(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_cell_a_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_a_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_cell_a_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_a_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_cell_b(trexio_t* const file);
trexio_exit_code trexio_read_cell_b(trexio_t* const file, double* const cell_b);
trexio_exit_code trexio_write_cell_b(trexio_t* const file, const double* cell_b);
trexio_exit_code trexio_read_cell_b_32(trexio_t* const file, float* const cell_b);
trexio_exit_code trexio_write_cell_b_32(trexio_t* const file, const float* cell_b);
trexio_exit_code trexio_read_cell_b_64(trexio_t* const file, double* const cell_b);
trexio_exit_code trexio_write_cell_b_64(trexio_t* const file, const double* cell_b);
trexio_exit_code trexio_read_safe_cell_b(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_b(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_cell_b_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_b_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_cell_b_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_b_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_cell_c(trexio_t* const file);
trexio_exit_code trexio_read_cell_c(trexio_t* const file, double* const cell_c);
trexio_exit_code trexio_write_cell_c(trexio_t* const file, const double* cell_c);
trexio_exit_code trexio_read_cell_c_32(trexio_t* const file, float* const cell_c);
trexio_exit_code trexio_write_cell_c_32(trexio_t* const file, const float* cell_c);
trexio_exit_code trexio_read_cell_c_64(trexio_t* const file, double* const cell_c);
trexio_exit_code trexio_write_cell_c_64(trexio_t* const file, const double* cell_c);
trexio_exit_code trexio_read_safe_cell_c(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_c(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_cell_c_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_c_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_cell_c_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_c_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_cell_g_a(trexio_t* const file);
trexio_exit_code trexio_read_cell_g_a(trexio_t* const file, double* const cell_g_a);
trexio_exit_code trexio_write_cell_g_a(trexio_t* const file, const double* cell_g_a);
trexio_exit_code trexio_read_cell_g_a_32(trexio_t* const file, float* const cell_g_a);
trexio_exit_code trexio_write_cell_g_a_32(trexio_t* const file, const float* cell_g_a);
trexio_exit_code trexio_read_cell_g_a_64(trexio_t* const file, double* const cell_g_a);
trexio_exit_code trexio_write_cell_g_a_64(trexio_t* const file, const double* cell_g_a);
trexio_exit_code trexio_read_safe_cell_g_a(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_g_a(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_cell_g_a_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_g_a_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_cell_g_a_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_g_a_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_cell_g_b(trexio_t* const file);
trexio_exit_code trexio_read_cell_g_b(trexio_t* const file, double* const cell_g_b);
trexio_exit_code trexio_write_cell_g_b(trexio_t* const file, const double* cell_g_b);
trexio_exit_code trexio_read_cell_g_b_32(trexio_t* const file, float* const cell_g_b);
trexio_exit_code trexio_write_cell_g_b_32(trexio_t* const file, const float* cell_g_b);
trexio_exit_code trexio_read_cell_g_b_64(trexio_t* const file, double* const cell_g_b);
trexio_exit_code trexio_write_cell_g_b_64(trexio_t* const file, const double* cell_g_b);
trexio_exit_code trexio_read_safe_cell_g_b(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_g_b(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_cell_g_b_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_g_b_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_cell_g_b_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_g_b_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_cell_g_c(trexio_t* const file);
trexio_exit_code trexio_read_cell_g_c(trexio_t* const file, double* const cell_g_c);
trexio_exit_code trexio_write_cell_g_c(trexio_t* const file, const double* cell_g_c);
trexio_exit_code trexio_read_cell_g_c_32(trexio_t* const file, float* const cell_g_c);
trexio_exit_code trexio_write_cell_g_c_32(trexio_t* const file, const float* cell_g_c);
trexio_exit_code trexio_read_cell_g_c_64(trexio_t* const file, double* const cell_g_c);
trexio_exit_code trexio_write_cell_g_c_64(trexio_t* const file, const double* cell_g_c);
trexio_exit_code trexio_read_safe_cell_g_c(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_g_c(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_cell_g_c_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_g_c_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_cell_g_c_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_cell_g_c_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_pbc_k_point(trexio_t* const file);
trexio_exit_code trexio_read_pbc_k_point(trexio_t* const file, double* const pbc_k_point);
trexio_exit_code trexio_write_pbc_k_point(trexio_t* const file, const double* pbc_k_point);
trexio_exit_code trexio_read_pbc_k_point_32(trexio_t* const file, float* const pbc_k_point);
trexio_exit_code trexio_write_pbc_k_point_32(trexio_t* const file, const float* pbc_k_point);
trexio_exit_code trexio_read_pbc_k_point_64(trexio_t* const file, double* const pbc_k_point);
trexio_exit_code trexio_write_pbc_k_point_64(trexio_t* const file, const double* pbc_k_point);
trexio_exit_code trexio_read_safe_pbc_k_point(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_pbc_k_point(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_pbc_k_point_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_pbc_k_point_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_pbc_k_point_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_pbc_k_point_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_pbc_k_point_weight(trexio_t* const file);
trexio_exit_code trexio_read_pbc_k_point_weight(trexio_t* const file, double* const pbc_k_point_weight);
trexio_exit_code trexio_write_pbc_k_point_weight(trexio_t* const file, const double* pbc_k_point_weight);
trexio_exit_code trexio_read_pbc_k_point_weight_32(trexio_t* const file, float* const pbc_k_point_weight);
trexio_exit_code trexio_write_pbc_k_point_weight_32(trexio_t* const file, const float* pbc_k_point_weight);
trexio_exit_code trexio_read_pbc_k_point_weight_64(trexio_t* const file, double* const pbc_k_point_weight);
trexio_exit_code trexio_write_pbc_k_point_weight_64(trexio_t* const file, const double* pbc_k_point_weight);
trexio_exit_code trexio_read_safe_pbc_k_point_weight(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_pbc_k_point_weight(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_pbc_k_point_weight_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_pbc_k_point_weight_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_pbc_k_point_weight_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_pbc_k_point_weight_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_nucleus_index(trexio_t* const file);
trexio_exit_code trexio_read_basis_nucleus_index(trexio_t* const file, int32_t* const basis_nucleus_index);
trexio_exit_code trexio_write_basis_nucleus_index(trexio_t* const file, const int32_t* basis_nucleus_index);
trexio_exit_code trexio_read_basis_nucleus_index_32(trexio_t* const file, int32_t* const basis_nucleus_index);
trexio_exit_code trexio_write_basis_nucleus_index_32(trexio_t* const file, const int32_t* basis_nucleus_index);
trexio_exit_code trexio_read_basis_nucleus_index_64(trexio_t* const file, int64_t* const basis_nucleus_index);
trexio_exit_code trexio_write_basis_nucleus_index_64(trexio_t* const file, const int64_t* basis_nucleus_index);
trexio_exit_code trexio_read_safe_basis_nucleus_index(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nucleus_index(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nucleus_index_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nucleus_index_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nucleus_index_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nucleus_index_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_shell_ang_mom(trexio_t* const file);
trexio_exit_code trexio_read_basis_shell_ang_mom(trexio_t* const file, int32_t* const basis_shell_ang_mom);
trexio_exit_code trexio_write_basis_shell_ang_mom(trexio_t* const file, const int32_t* basis_shell_ang_mom);
trexio_exit_code trexio_read_basis_shell_ang_mom_32(trexio_t* const file, int32_t* const basis_shell_ang_mom);
trexio_exit_code trexio_write_basis_shell_ang_mom_32(trexio_t* const file, const int32_t* basis_shell_ang_mom);
trexio_exit_code trexio_read_basis_shell_ang_mom_64(trexio_t* const file, int64_t* const basis_shell_ang_mom);
trexio_exit_code trexio_write_basis_shell_ang_mom_64(trexio_t* const file, const int64_t* basis_shell_ang_mom);
trexio_exit_code trexio_read_safe_basis_shell_ang_mom(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_shell_ang_mom(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_shell_ang_mom_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_shell_ang_mom_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_shell_ang_mom_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_shell_ang_mom_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_shell_factor(trexio_t* const file);
trexio_exit_code trexio_read_basis_shell_factor(trexio_t* const file, double* const basis_shell_factor);
trexio_exit_code trexio_write_basis_shell_factor(trexio_t* const file, const double* basis_shell_factor);
trexio_exit_code trexio_read_basis_shell_factor_32(trexio_t* const file, float* const basis_shell_factor);
trexio_exit_code trexio_write_basis_shell_factor_32(trexio_t* const file, const float* basis_shell_factor);
trexio_exit_code trexio_read_basis_shell_factor_64(trexio_t* const file, double* const basis_shell_factor);
trexio_exit_code trexio_write_basis_shell_factor_64(trexio_t* const file, const double* basis_shell_factor);
trexio_exit_code trexio_read_safe_basis_shell_factor(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_shell_factor(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_shell_factor_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_shell_factor_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_shell_factor_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_shell_factor_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_r_power(trexio_t* const file);
trexio_exit_code trexio_read_basis_r_power(trexio_t* const file, int32_t* const basis_r_power);
trexio_exit_code trexio_write_basis_r_power(trexio_t* const file, const int32_t* basis_r_power);
trexio_exit_code trexio_read_basis_r_power_32(trexio_t* const file, int32_t* const basis_r_power);
trexio_exit_code trexio_write_basis_r_power_32(trexio_t* const file, const int32_t* basis_r_power);
trexio_exit_code trexio_read_basis_r_power_64(trexio_t* const file, int64_t* const basis_r_power);
trexio_exit_code trexio_write_basis_r_power_64(trexio_t* const file, const int64_t* basis_r_power);
trexio_exit_code trexio_read_safe_basis_r_power(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_r_power(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_r_power_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_r_power_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_r_power_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_r_power_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_nao_grid_start(trexio_t* const file);
trexio_exit_code trexio_read_basis_nao_grid_start(trexio_t* const file, int32_t* const basis_nao_grid_start);
trexio_exit_code trexio_write_basis_nao_grid_start(trexio_t* const file, const int32_t* basis_nao_grid_start);
trexio_exit_code trexio_read_basis_nao_grid_start_32(trexio_t* const file, int32_t* const basis_nao_grid_start);
trexio_exit_code trexio_write_basis_nao_grid_start_32(trexio_t* const file, const int32_t* basis_nao_grid_start);
trexio_exit_code trexio_read_basis_nao_grid_start_64(trexio_t* const file, int64_t* const basis_nao_grid_start);
trexio_exit_code trexio_write_basis_nao_grid_start_64(trexio_t* const file, const int64_t* basis_nao_grid_start);
trexio_exit_code trexio_read_safe_basis_nao_grid_start(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_start(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nao_grid_start_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_start_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nao_grid_start_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_start_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_nao_grid_size(trexio_t* const file);
trexio_exit_code trexio_read_basis_nao_grid_size(trexio_t* const file, int32_t* const basis_nao_grid_size);
trexio_exit_code trexio_write_basis_nao_grid_size(trexio_t* const file, const int32_t* basis_nao_grid_size);
trexio_exit_code trexio_read_basis_nao_grid_size_32(trexio_t* const file, int32_t* const basis_nao_grid_size);
trexio_exit_code trexio_write_basis_nao_grid_size_32(trexio_t* const file, const int32_t* basis_nao_grid_size);
trexio_exit_code trexio_read_basis_nao_grid_size_64(trexio_t* const file, int64_t* const basis_nao_grid_size);
trexio_exit_code trexio_write_basis_nao_grid_size_64(trexio_t* const file, const int64_t* basis_nao_grid_size);
trexio_exit_code trexio_read_safe_basis_nao_grid_size(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_size(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nao_grid_size_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_size_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nao_grid_size_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_size_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_shell_index(trexio_t* const file);
trexio_exit_code trexio_read_basis_shell_index(trexio_t* const file, int32_t* const basis_shell_index);
trexio_exit_code trexio_write_basis_shell_index(trexio_t* const file, const int32_t* basis_shell_index);
trexio_exit_code trexio_read_basis_shell_index_32(trexio_t* const file, int32_t* const basis_shell_index);
trexio_exit_code trexio_write_basis_shell_index_32(trexio_t* const file, const int32_t* basis_shell_index);
trexio_exit_code trexio_read_basis_shell_index_64(trexio_t* const file, int64_t* const basis_shell_index);
trexio_exit_code trexio_write_basis_shell_index_64(trexio_t* const file, const int64_t* basis_shell_index);
trexio_exit_code trexio_read_safe_basis_shell_index(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_shell_index(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_shell_index_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_shell_index_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_shell_index_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_shell_index_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_exponent(trexio_t* const file);
trexio_exit_code trexio_read_basis_exponent(trexio_t* const file, double* const basis_exponent);
trexio_exit_code trexio_write_basis_exponent(trexio_t* const file, const double* basis_exponent);
trexio_exit_code trexio_read_basis_exponent_32(trexio_t* const file, float* const basis_exponent);
trexio_exit_code trexio_write_basis_exponent_32(trexio_t* const file, const float* basis_exponent);
trexio_exit_code trexio_read_basis_exponent_64(trexio_t* const file, double* const basis_exponent);
trexio_exit_code trexio_write_basis_exponent_64(trexio_t* const file, const double* basis_exponent);
trexio_exit_code trexio_read_safe_basis_exponent(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_exponent(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_exponent_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_exponent_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_exponent_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_exponent_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_exponent_im(trexio_t* const file);
trexio_exit_code trexio_read_basis_exponent_im(trexio_t* const file, double* const basis_exponent_im);
trexio_exit_code trexio_write_basis_exponent_im(trexio_t* const file, const double* basis_exponent_im);
trexio_exit_code trexio_read_basis_exponent_im_32(trexio_t* const file, float* const basis_exponent_im);
trexio_exit_code trexio_write_basis_exponent_im_32(trexio_t* const file, const float* basis_exponent_im);
trexio_exit_code trexio_read_basis_exponent_im_64(trexio_t* const file, double* const basis_exponent_im);
trexio_exit_code trexio_write_basis_exponent_im_64(trexio_t* const file, const double* basis_exponent_im);
trexio_exit_code trexio_read_safe_basis_exponent_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_exponent_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_exponent_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_exponent_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_exponent_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_exponent_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_coefficient(trexio_t* const file);
trexio_exit_code trexio_read_basis_coefficient(trexio_t* const file, double* const basis_coefficient);
trexio_exit_code trexio_write_basis_coefficient(trexio_t* const file, const double* basis_coefficient);
trexio_exit_code trexio_read_basis_coefficient_32(trexio_t* const file, float* const basis_coefficient);
trexio_exit_code trexio_write_basis_coefficient_32(trexio_t* const file, const float* basis_coefficient);
trexio_exit_code trexio_read_basis_coefficient_64(trexio_t* const file, double* const basis_coefficient);
trexio_exit_code trexio_write_basis_coefficient_64(trexio_t* const file, const double* basis_coefficient);
trexio_exit_code trexio_read_safe_basis_coefficient(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_coefficient(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_coefficient_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_coefficient_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_coefficient_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_coefficient_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_coefficient_im(trexio_t* const file);
trexio_exit_code trexio_read_basis_coefficient_im(trexio_t* const file, double* const basis_coefficient_im);
trexio_exit_code trexio_write_basis_coefficient_im(trexio_t* const file, const double* basis_coefficient_im);
trexio_exit_code trexio_read_basis_coefficient_im_32(trexio_t* const file, float* const basis_coefficient_im);
trexio_exit_code trexio_write_basis_coefficient_im_32(trexio_t* const file, const float* basis_coefficient_im);
trexio_exit_code trexio_read_basis_coefficient_im_64(trexio_t* const file, double* const basis_coefficient_im);
trexio_exit_code trexio_write_basis_coefficient_im_64(trexio_t* const file, const double* basis_coefficient_im);
trexio_exit_code trexio_read_safe_basis_coefficient_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_coefficient_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_coefficient_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_coefficient_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_coefficient_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_coefficient_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_oscillation_arg(trexio_t* const file);
trexio_exit_code trexio_read_basis_oscillation_arg(trexio_t* const file, double* const basis_oscillation_arg);
trexio_exit_code trexio_write_basis_oscillation_arg(trexio_t* const file, const double* basis_oscillation_arg);
trexio_exit_code trexio_read_basis_oscillation_arg_32(trexio_t* const file, float* const basis_oscillation_arg);
trexio_exit_code trexio_write_basis_oscillation_arg_32(trexio_t* const file, const float* basis_oscillation_arg);
trexio_exit_code trexio_read_basis_oscillation_arg_64(trexio_t* const file, double* const basis_oscillation_arg);
trexio_exit_code trexio_write_basis_oscillation_arg_64(trexio_t* const file, const double* basis_oscillation_arg);
trexio_exit_code trexio_read_safe_basis_oscillation_arg(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_oscillation_arg(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_oscillation_arg_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_oscillation_arg_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_oscillation_arg_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_oscillation_arg_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_prim_factor(trexio_t* const file);
trexio_exit_code trexio_read_basis_prim_factor(trexio_t* const file, double* const basis_prim_factor);
trexio_exit_code trexio_write_basis_prim_factor(trexio_t* const file, const double* basis_prim_factor);
trexio_exit_code trexio_read_basis_prim_factor_32(trexio_t* const file, float* const basis_prim_factor);
trexio_exit_code trexio_write_basis_prim_factor_32(trexio_t* const file, const float* basis_prim_factor);
trexio_exit_code trexio_read_basis_prim_factor_64(trexio_t* const file, double* const basis_prim_factor);
trexio_exit_code trexio_write_basis_prim_factor_64(trexio_t* const file, const double* basis_prim_factor);
trexio_exit_code trexio_read_safe_basis_prim_factor(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_prim_factor(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_prim_factor_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_prim_factor_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_prim_factor_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_prim_factor_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_nao_grid_radius(trexio_t* const file);
trexio_exit_code trexio_read_basis_nao_grid_radius(trexio_t* const file, double* const basis_nao_grid_radius);
trexio_exit_code trexio_write_basis_nao_grid_radius(trexio_t* const file, const double* basis_nao_grid_radius);
trexio_exit_code trexio_read_basis_nao_grid_radius_32(trexio_t* const file, float* const basis_nao_grid_radius);
trexio_exit_code trexio_write_basis_nao_grid_radius_32(trexio_t* const file, const float* basis_nao_grid_radius);
trexio_exit_code trexio_read_basis_nao_grid_radius_64(trexio_t* const file, double* const basis_nao_grid_radius);
trexio_exit_code trexio_write_basis_nao_grid_radius_64(trexio_t* const file, const double* basis_nao_grid_radius);
trexio_exit_code trexio_read_safe_basis_nao_grid_radius(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_radius(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nao_grid_radius_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_radius_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nao_grid_radius_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_radius_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_nao_grid_phi(trexio_t* const file);
trexio_exit_code trexio_read_basis_nao_grid_phi(trexio_t* const file, double* const basis_nao_grid_phi);
trexio_exit_code trexio_write_basis_nao_grid_phi(trexio_t* const file, const double* basis_nao_grid_phi);
trexio_exit_code trexio_read_basis_nao_grid_phi_32(trexio_t* const file, float* const basis_nao_grid_phi);
trexio_exit_code trexio_write_basis_nao_grid_phi_32(trexio_t* const file, const float* basis_nao_grid_phi);
trexio_exit_code trexio_read_basis_nao_grid_phi_64(trexio_t* const file, double* const basis_nao_grid_phi);
trexio_exit_code trexio_write_basis_nao_grid_phi_64(trexio_t* const file, const double* basis_nao_grid_phi);
trexio_exit_code trexio_read_safe_basis_nao_grid_phi(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_phi(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nao_grid_phi_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_phi_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nao_grid_phi_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_phi_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_nao_grid_grad(trexio_t* const file);
trexio_exit_code trexio_read_basis_nao_grid_grad(trexio_t* const file, double* const basis_nao_grid_grad);
trexio_exit_code trexio_write_basis_nao_grid_grad(trexio_t* const file, const double* basis_nao_grid_grad);
trexio_exit_code trexio_read_basis_nao_grid_grad_32(trexio_t* const file, float* const basis_nao_grid_grad);
trexio_exit_code trexio_write_basis_nao_grid_grad_32(trexio_t* const file, const float* basis_nao_grid_grad);
trexio_exit_code trexio_read_basis_nao_grid_grad_64(trexio_t* const file, double* const basis_nao_grid_grad);
trexio_exit_code trexio_write_basis_nao_grid_grad_64(trexio_t* const file, const double* basis_nao_grid_grad);
trexio_exit_code trexio_read_safe_basis_nao_grid_grad(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_grad(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nao_grid_grad_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_grad_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nao_grid_grad_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_grad_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_nao_grid_lap(trexio_t* const file);
trexio_exit_code trexio_read_basis_nao_grid_lap(trexio_t* const file, double* const basis_nao_grid_lap);
trexio_exit_code trexio_write_basis_nao_grid_lap(trexio_t* const file, const double* basis_nao_grid_lap);
trexio_exit_code trexio_read_basis_nao_grid_lap_32(trexio_t* const file, float* const basis_nao_grid_lap);
trexio_exit_code trexio_write_basis_nao_grid_lap_32(trexio_t* const file, const float* basis_nao_grid_lap);
trexio_exit_code trexio_read_basis_nao_grid_lap_64(trexio_t* const file, double* const basis_nao_grid_lap);
trexio_exit_code trexio_write_basis_nao_grid_lap_64(trexio_t* const file, const double* basis_nao_grid_lap);
trexio_exit_code trexio_read_safe_basis_nao_grid_lap(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_lap(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nao_grid_lap_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_lap_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_nao_grid_lap_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_nao_grid_lap_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_interpolator_phi(trexio_t* const file);
trexio_exit_code trexio_read_basis_interpolator_phi(trexio_t* const file, double* const basis_interpolator_phi);
trexio_exit_code trexio_write_basis_interpolator_phi(trexio_t* const file, const double* basis_interpolator_phi);
trexio_exit_code trexio_read_basis_interpolator_phi_32(trexio_t* const file, float* const basis_interpolator_phi);
trexio_exit_code trexio_write_basis_interpolator_phi_32(trexio_t* const file, const float* basis_interpolator_phi);
trexio_exit_code trexio_read_basis_interpolator_phi_64(trexio_t* const file, double* const basis_interpolator_phi);
trexio_exit_code trexio_write_basis_interpolator_phi_64(trexio_t* const file, const double* basis_interpolator_phi);
trexio_exit_code trexio_read_safe_basis_interpolator_phi(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_interpolator_phi(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_interpolator_phi_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_interpolator_phi_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_interpolator_phi_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_interpolator_phi_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_interpolator_grad(trexio_t* const file);
trexio_exit_code trexio_read_basis_interpolator_grad(trexio_t* const file, double* const basis_interpolator_grad);
trexio_exit_code trexio_write_basis_interpolator_grad(trexio_t* const file, const double* basis_interpolator_grad);
trexio_exit_code trexio_read_basis_interpolator_grad_32(trexio_t* const file, float* const basis_interpolator_grad);
trexio_exit_code trexio_write_basis_interpolator_grad_32(trexio_t* const file, const float* basis_interpolator_grad);
trexio_exit_code trexio_read_basis_interpolator_grad_64(trexio_t* const file, double* const basis_interpolator_grad);
trexio_exit_code trexio_write_basis_interpolator_grad_64(trexio_t* const file, const double* basis_interpolator_grad);
trexio_exit_code trexio_read_safe_basis_interpolator_grad(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_interpolator_grad(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_interpolator_grad_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_interpolator_grad_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_interpolator_grad_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_interpolator_grad_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_basis_interpolator_lap(trexio_t* const file);
trexio_exit_code trexio_read_basis_interpolator_lap(trexio_t* const file, double* const basis_interpolator_lap);
trexio_exit_code trexio_write_basis_interpolator_lap(trexio_t* const file, const double* basis_interpolator_lap);
trexio_exit_code trexio_read_basis_interpolator_lap_32(trexio_t* const file, float* const basis_interpolator_lap);
trexio_exit_code trexio_write_basis_interpolator_lap_32(trexio_t* const file, const float* basis_interpolator_lap);
trexio_exit_code trexio_read_basis_interpolator_lap_64(trexio_t* const file, double* const basis_interpolator_lap);
trexio_exit_code trexio_write_basis_interpolator_lap_64(trexio_t* const file, const double* basis_interpolator_lap);
trexio_exit_code trexio_read_safe_basis_interpolator_lap(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_interpolator_lap(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_interpolator_lap_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_interpolator_lap_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_basis_interpolator_lap_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_basis_interpolator_lap_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ecp_max_ang_mom_plus_1(trexio_t* const file);
trexio_exit_code trexio_read_ecp_max_ang_mom_plus_1(trexio_t* const file, int32_t* const ecp_max_ang_mom_plus_1);
trexio_exit_code trexio_write_ecp_max_ang_mom_plus_1(trexio_t* const file, const int32_t* ecp_max_ang_mom_plus_1);
trexio_exit_code trexio_read_ecp_max_ang_mom_plus_1_32(trexio_t* const file, int32_t* const ecp_max_ang_mom_plus_1);
trexio_exit_code trexio_write_ecp_max_ang_mom_plus_1_32(trexio_t* const file, const int32_t* ecp_max_ang_mom_plus_1);
trexio_exit_code trexio_read_ecp_max_ang_mom_plus_1_64(trexio_t* const file, int64_t* const ecp_max_ang_mom_plus_1);
trexio_exit_code trexio_write_ecp_max_ang_mom_plus_1_64(trexio_t* const file, const int64_t* ecp_max_ang_mom_plus_1);
trexio_exit_code trexio_read_safe_ecp_max_ang_mom_plus_1(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_max_ang_mom_plus_1(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_max_ang_mom_plus_1_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_max_ang_mom_plus_1_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_max_ang_mom_plus_1_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_max_ang_mom_plus_1_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ecp_z_core(trexio_t* const file);
trexio_exit_code trexio_read_ecp_z_core(trexio_t* const file, int32_t* const ecp_z_core);
trexio_exit_code trexio_write_ecp_z_core(trexio_t* const file, const int32_t* ecp_z_core);
trexio_exit_code trexio_read_ecp_z_core_32(trexio_t* const file, int32_t* const ecp_z_core);
trexio_exit_code trexio_write_ecp_z_core_32(trexio_t* const file, const int32_t* ecp_z_core);
trexio_exit_code trexio_read_ecp_z_core_64(trexio_t* const file, int64_t* const ecp_z_core);
trexio_exit_code trexio_write_ecp_z_core_64(trexio_t* const file, const int64_t* ecp_z_core);
trexio_exit_code trexio_read_safe_ecp_z_core(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_z_core(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_z_core_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_z_core_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_z_core_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_z_core_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ecp_ang_mom(trexio_t* const file);
trexio_exit_code trexio_read_ecp_ang_mom(trexio_t* const file, int32_t* const ecp_ang_mom);
trexio_exit_code trexio_write_ecp_ang_mom(trexio_t* const file, const int32_t* ecp_ang_mom);
trexio_exit_code trexio_read_ecp_ang_mom_32(trexio_t* const file, int32_t* const ecp_ang_mom);
trexio_exit_code trexio_write_ecp_ang_mom_32(trexio_t* const file, const int32_t* ecp_ang_mom);
trexio_exit_code trexio_read_ecp_ang_mom_64(trexio_t* const file, int64_t* const ecp_ang_mom);
trexio_exit_code trexio_write_ecp_ang_mom_64(trexio_t* const file, const int64_t* ecp_ang_mom);
trexio_exit_code trexio_read_safe_ecp_ang_mom(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_ang_mom(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_ang_mom_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_ang_mom_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_ang_mom_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_ang_mom_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ecp_nucleus_index(trexio_t* const file);
trexio_exit_code trexio_read_ecp_nucleus_index(trexio_t* const file, int32_t* const ecp_nucleus_index);
trexio_exit_code trexio_write_ecp_nucleus_index(trexio_t* const file, const int32_t* ecp_nucleus_index);
trexio_exit_code trexio_read_ecp_nucleus_index_32(trexio_t* const file, int32_t* const ecp_nucleus_index);
trexio_exit_code trexio_write_ecp_nucleus_index_32(trexio_t* const file, const int32_t* ecp_nucleus_index);
trexio_exit_code trexio_read_ecp_nucleus_index_64(trexio_t* const file, int64_t* const ecp_nucleus_index);
trexio_exit_code trexio_write_ecp_nucleus_index_64(trexio_t* const file, const int64_t* ecp_nucleus_index);
trexio_exit_code trexio_read_safe_ecp_nucleus_index(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_nucleus_index(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_nucleus_index_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_nucleus_index_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_nucleus_index_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_nucleus_index_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ecp_exponent(trexio_t* const file);
trexio_exit_code trexio_read_ecp_exponent(trexio_t* const file, double* const ecp_exponent);
trexio_exit_code trexio_write_ecp_exponent(trexio_t* const file, const double* ecp_exponent);
trexio_exit_code trexio_read_ecp_exponent_32(trexio_t* const file, float* const ecp_exponent);
trexio_exit_code trexio_write_ecp_exponent_32(trexio_t* const file, const float* ecp_exponent);
trexio_exit_code trexio_read_ecp_exponent_64(trexio_t* const file, double* const ecp_exponent);
trexio_exit_code trexio_write_ecp_exponent_64(trexio_t* const file, const double* ecp_exponent);
trexio_exit_code trexio_read_safe_ecp_exponent(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_exponent(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_exponent_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_exponent_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_exponent_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_exponent_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ecp_coefficient(trexio_t* const file);
trexio_exit_code trexio_read_ecp_coefficient(trexio_t* const file, double* const ecp_coefficient);
trexio_exit_code trexio_write_ecp_coefficient(trexio_t* const file, const double* ecp_coefficient);
trexio_exit_code trexio_read_ecp_coefficient_32(trexio_t* const file, float* const ecp_coefficient);
trexio_exit_code trexio_write_ecp_coefficient_32(trexio_t* const file, const float* ecp_coefficient);
trexio_exit_code trexio_read_ecp_coefficient_64(trexio_t* const file, double* const ecp_coefficient);
trexio_exit_code trexio_write_ecp_coefficient_64(trexio_t* const file, const double* ecp_coefficient);
trexio_exit_code trexio_read_safe_ecp_coefficient(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_coefficient(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_coefficient_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_coefficient_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_coefficient_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_coefficient_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ecp_power(trexio_t* const file);
trexio_exit_code trexio_read_ecp_power(trexio_t* const file, int32_t* const ecp_power);
trexio_exit_code trexio_write_ecp_power(trexio_t* const file, const int32_t* ecp_power);
trexio_exit_code trexio_read_ecp_power_32(trexio_t* const file, int32_t* const ecp_power);
trexio_exit_code trexio_write_ecp_power_32(trexio_t* const file, const int32_t* ecp_power);
trexio_exit_code trexio_read_ecp_power_64(trexio_t* const file, int64_t* const ecp_power);
trexio_exit_code trexio_write_ecp_power_64(trexio_t* const file, const int64_t* ecp_power);
trexio_exit_code trexio_read_safe_ecp_power(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_power(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_power_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_power_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ecp_power_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ecp_power_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_grid_coord(trexio_t* const file);
trexio_exit_code trexio_read_grid_coord(trexio_t* const file, double* const grid_coord);
trexio_exit_code trexio_write_grid_coord(trexio_t* const file, const double* grid_coord);
trexio_exit_code trexio_read_grid_coord_32(trexio_t* const file, float* const grid_coord);
trexio_exit_code trexio_write_grid_coord_32(trexio_t* const file, const float* grid_coord);
trexio_exit_code trexio_read_grid_coord_64(trexio_t* const file, double* const grid_coord);
trexio_exit_code trexio_write_grid_coord_64(trexio_t* const file, const double* grid_coord);
trexio_exit_code trexio_read_safe_grid_coord(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_coord(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_grid_coord_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_coord_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_grid_coord_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_coord_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_grid_weight(trexio_t* const file);
trexio_exit_code trexio_read_grid_weight(trexio_t* const file, double* const grid_weight);
trexio_exit_code trexio_write_grid_weight(trexio_t* const file, const double* grid_weight);
trexio_exit_code trexio_read_grid_weight_32(trexio_t* const file, float* const grid_weight);
trexio_exit_code trexio_write_grid_weight_32(trexio_t* const file, const float* grid_weight);
trexio_exit_code trexio_read_grid_weight_64(trexio_t* const file, double* const grid_weight);
trexio_exit_code trexio_write_grid_weight_64(trexio_t* const file, const double* grid_weight);
trexio_exit_code trexio_read_safe_grid_weight(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_weight(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_grid_weight_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_weight_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_grid_weight_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_weight_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_grid_ang_coord(trexio_t* const file);
trexio_exit_code trexio_read_grid_ang_coord(trexio_t* const file, double* const grid_ang_coord);
trexio_exit_code trexio_write_grid_ang_coord(trexio_t* const file, const double* grid_ang_coord);
trexio_exit_code trexio_read_grid_ang_coord_32(trexio_t* const file, float* const grid_ang_coord);
trexio_exit_code trexio_write_grid_ang_coord_32(trexio_t* const file, const float* grid_ang_coord);
trexio_exit_code trexio_read_grid_ang_coord_64(trexio_t* const file, double* const grid_ang_coord);
trexio_exit_code trexio_write_grid_ang_coord_64(trexio_t* const file, const double* grid_ang_coord);
trexio_exit_code trexio_read_safe_grid_ang_coord(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_ang_coord(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_grid_ang_coord_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_ang_coord_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_grid_ang_coord_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_ang_coord_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_grid_ang_weight(trexio_t* const file);
trexio_exit_code trexio_read_grid_ang_weight(trexio_t* const file, double* const grid_ang_weight);
trexio_exit_code trexio_write_grid_ang_weight(trexio_t* const file, const double* grid_ang_weight);
trexio_exit_code trexio_read_grid_ang_weight_32(trexio_t* const file, float* const grid_ang_weight);
trexio_exit_code trexio_write_grid_ang_weight_32(trexio_t* const file, const float* grid_ang_weight);
trexio_exit_code trexio_read_grid_ang_weight_64(trexio_t* const file, double* const grid_ang_weight);
trexio_exit_code trexio_write_grid_ang_weight_64(trexio_t* const file, const double* grid_ang_weight);
trexio_exit_code trexio_read_safe_grid_ang_weight(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_ang_weight(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_grid_ang_weight_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_ang_weight_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_grid_ang_weight_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_ang_weight_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_grid_rad_coord(trexio_t* const file);
trexio_exit_code trexio_read_grid_rad_coord(trexio_t* const file, double* const grid_rad_coord);
trexio_exit_code trexio_write_grid_rad_coord(trexio_t* const file, const double* grid_rad_coord);
trexio_exit_code trexio_read_grid_rad_coord_32(trexio_t* const file, float* const grid_rad_coord);
trexio_exit_code trexio_write_grid_rad_coord_32(trexio_t* const file, const float* grid_rad_coord);
trexio_exit_code trexio_read_grid_rad_coord_64(trexio_t* const file, double* const grid_rad_coord);
trexio_exit_code trexio_write_grid_rad_coord_64(trexio_t* const file, const double* grid_rad_coord);
trexio_exit_code trexio_read_safe_grid_rad_coord(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_rad_coord(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_grid_rad_coord_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_rad_coord_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_grid_rad_coord_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_rad_coord_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_grid_rad_weight(trexio_t* const file);
trexio_exit_code trexio_read_grid_rad_weight(trexio_t* const file, double* const grid_rad_weight);
trexio_exit_code trexio_write_grid_rad_weight(trexio_t* const file, const double* grid_rad_weight);
trexio_exit_code trexio_read_grid_rad_weight_32(trexio_t* const file, float* const grid_rad_weight);
trexio_exit_code trexio_write_grid_rad_weight_32(trexio_t* const file, const float* grid_rad_weight);
trexio_exit_code trexio_read_grid_rad_weight_64(trexio_t* const file, double* const grid_rad_weight);
trexio_exit_code trexio_write_grid_rad_weight_64(trexio_t* const file, const double* grid_rad_weight);
trexio_exit_code trexio_read_safe_grid_rad_weight(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_rad_weight(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_grid_rad_weight_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_rad_weight_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_grid_rad_weight_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_grid_rad_weight_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_shell(trexio_t* const file);
trexio_exit_code trexio_read_ao_shell(trexio_t* const file, int32_t* const ao_shell);
trexio_exit_code trexio_write_ao_shell(trexio_t* const file, const int32_t* ao_shell);
trexio_exit_code trexio_read_ao_shell_32(trexio_t* const file, int32_t* const ao_shell);
trexio_exit_code trexio_write_ao_shell_32(trexio_t* const file, const int32_t* ao_shell);
trexio_exit_code trexio_read_ao_shell_64(trexio_t* const file, int64_t* const ao_shell);
trexio_exit_code trexio_write_ao_shell_64(trexio_t* const file, const int64_t* ao_shell);
trexio_exit_code trexio_read_safe_ao_shell(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_shell(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_shell_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_shell_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_shell_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_shell_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_normalization(trexio_t* const file);
trexio_exit_code trexio_read_ao_normalization(trexio_t* const file, double* const ao_normalization);
trexio_exit_code trexio_write_ao_normalization(trexio_t* const file, const double* ao_normalization);
trexio_exit_code trexio_read_ao_normalization_32(trexio_t* const file, float* const ao_normalization);
trexio_exit_code trexio_write_ao_normalization_32(trexio_t* const file, const float* ao_normalization);
trexio_exit_code trexio_read_ao_normalization_64(trexio_t* const file, double* const ao_normalization);
trexio_exit_code trexio_write_ao_normalization_64(trexio_t* const file, const double* ao_normalization);
trexio_exit_code trexio_read_safe_ao_normalization(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_normalization(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_normalization_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_normalization_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_normalization_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_normalization_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_1e_int_overlap(trexio_t* const file);
trexio_exit_code trexio_read_ao_1e_int_overlap(trexio_t* const file, double* const ao_1e_int_overlap);
trexio_exit_code trexio_write_ao_1e_int_overlap(trexio_t* const file, const double* ao_1e_int_overlap);
trexio_exit_code trexio_read_ao_1e_int_overlap_32(trexio_t* const file, float* const ao_1e_int_overlap);
trexio_exit_code trexio_write_ao_1e_int_overlap_32(trexio_t* const file, const float* ao_1e_int_overlap);
trexio_exit_code trexio_read_ao_1e_int_overlap_64(trexio_t* const file, double* const ao_1e_int_overlap);
trexio_exit_code trexio_write_ao_1e_int_overlap_64(trexio_t* const file, const double* ao_1e_int_overlap);
trexio_exit_code trexio_read_safe_ao_1e_int_overlap(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_overlap(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_overlap_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_overlap_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_overlap_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_overlap_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_1e_int_kinetic(trexio_t* const file);
trexio_exit_code trexio_read_ao_1e_int_kinetic(trexio_t* const file, double* const ao_1e_int_kinetic);
trexio_exit_code trexio_write_ao_1e_int_kinetic(trexio_t* const file, const double* ao_1e_int_kinetic);
trexio_exit_code trexio_read_ao_1e_int_kinetic_32(trexio_t* const file, float* const ao_1e_int_kinetic);
trexio_exit_code trexio_write_ao_1e_int_kinetic_32(trexio_t* const file, const float* ao_1e_int_kinetic);
trexio_exit_code trexio_read_ao_1e_int_kinetic_64(trexio_t* const file, double* const ao_1e_int_kinetic);
trexio_exit_code trexio_write_ao_1e_int_kinetic_64(trexio_t* const file, const double* ao_1e_int_kinetic);
trexio_exit_code trexio_read_safe_ao_1e_int_kinetic(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_kinetic(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_kinetic_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_kinetic_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_kinetic_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_kinetic_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_1e_int_potential_n_e(trexio_t* const file);
trexio_exit_code trexio_read_ao_1e_int_potential_n_e(trexio_t* const file, double* const ao_1e_int_potential_n_e);
trexio_exit_code trexio_write_ao_1e_int_potential_n_e(trexio_t* const file, const double* ao_1e_int_potential_n_e);
trexio_exit_code trexio_read_ao_1e_int_potential_n_e_32(trexio_t* const file, float* const ao_1e_int_potential_n_e);
trexio_exit_code trexio_write_ao_1e_int_potential_n_e_32(trexio_t* const file, const float* ao_1e_int_potential_n_e);
trexio_exit_code trexio_read_ao_1e_int_potential_n_e_64(trexio_t* const file, double* const ao_1e_int_potential_n_e);
trexio_exit_code trexio_write_ao_1e_int_potential_n_e_64(trexio_t* const file, const double* ao_1e_int_potential_n_e);
trexio_exit_code trexio_read_safe_ao_1e_int_potential_n_e(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_potential_n_e(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_potential_n_e_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_potential_n_e_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_potential_n_e_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_potential_n_e_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_1e_int_ecp(trexio_t* const file);
trexio_exit_code trexio_read_ao_1e_int_ecp(trexio_t* const file, double* const ao_1e_int_ecp);
trexio_exit_code trexio_write_ao_1e_int_ecp(trexio_t* const file, const double* ao_1e_int_ecp);
trexio_exit_code trexio_read_ao_1e_int_ecp_32(trexio_t* const file, float* const ao_1e_int_ecp);
trexio_exit_code trexio_write_ao_1e_int_ecp_32(trexio_t* const file, const float* ao_1e_int_ecp);
trexio_exit_code trexio_read_ao_1e_int_ecp_64(trexio_t* const file, double* const ao_1e_int_ecp);
trexio_exit_code trexio_write_ao_1e_int_ecp_64(trexio_t* const file, const double* ao_1e_int_ecp);
trexio_exit_code trexio_read_safe_ao_1e_int_ecp(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_ecp(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_ecp_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_ecp_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_ecp_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_ecp_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_1e_int_core_hamiltonian(trexio_t* const file);
trexio_exit_code trexio_read_ao_1e_int_core_hamiltonian(trexio_t* const file, double* const ao_1e_int_core_hamiltonian);
trexio_exit_code trexio_write_ao_1e_int_core_hamiltonian(trexio_t* const file, const double* ao_1e_int_core_hamiltonian);
trexio_exit_code trexio_read_ao_1e_int_core_hamiltonian_32(trexio_t* const file, float* const ao_1e_int_core_hamiltonian);
trexio_exit_code trexio_write_ao_1e_int_core_hamiltonian_32(trexio_t* const file, const float* ao_1e_int_core_hamiltonian);
trexio_exit_code trexio_read_ao_1e_int_core_hamiltonian_64(trexio_t* const file, double* const ao_1e_int_core_hamiltonian);
trexio_exit_code trexio_write_ao_1e_int_core_hamiltonian_64(trexio_t* const file, const double* ao_1e_int_core_hamiltonian);
trexio_exit_code trexio_read_safe_ao_1e_int_core_hamiltonian(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_core_hamiltonian(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_core_hamiltonian_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_core_hamiltonian_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_core_hamiltonian_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_core_hamiltonian_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_1e_int_overlap_im(trexio_t* const file);
trexio_exit_code trexio_read_ao_1e_int_overlap_im(trexio_t* const file, double* const ao_1e_int_overlap_im);
trexio_exit_code trexio_write_ao_1e_int_overlap_im(trexio_t* const file, const double* ao_1e_int_overlap_im);
trexio_exit_code trexio_read_ao_1e_int_overlap_im_32(trexio_t* const file, float* const ao_1e_int_overlap_im);
trexio_exit_code trexio_write_ao_1e_int_overlap_im_32(trexio_t* const file, const float* ao_1e_int_overlap_im);
trexio_exit_code trexio_read_ao_1e_int_overlap_im_64(trexio_t* const file, double* const ao_1e_int_overlap_im);
trexio_exit_code trexio_write_ao_1e_int_overlap_im_64(trexio_t* const file, const double* ao_1e_int_overlap_im);
trexio_exit_code trexio_read_safe_ao_1e_int_overlap_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_overlap_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_overlap_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_overlap_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_overlap_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_overlap_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_1e_int_kinetic_im(trexio_t* const file);
trexio_exit_code trexio_read_ao_1e_int_kinetic_im(trexio_t* const file, double* const ao_1e_int_kinetic_im);
trexio_exit_code trexio_write_ao_1e_int_kinetic_im(trexio_t* const file, const double* ao_1e_int_kinetic_im);
trexio_exit_code trexio_read_ao_1e_int_kinetic_im_32(trexio_t* const file, float* const ao_1e_int_kinetic_im);
trexio_exit_code trexio_write_ao_1e_int_kinetic_im_32(trexio_t* const file, const float* ao_1e_int_kinetic_im);
trexio_exit_code trexio_read_ao_1e_int_kinetic_im_64(trexio_t* const file, double* const ao_1e_int_kinetic_im);
trexio_exit_code trexio_write_ao_1e_int_kinetic_im_64(trexio_t* const file, const double* ao_1e_int_kinetic_im);
trexio_exit_code trexio_read_safe_ao_1e_int_kinetic_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_kinetic_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_kinetic_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_kinetic_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_kinetic_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_kinetic_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_1e_int_potential_n_e_im(trexio_t* const file);
trexio_exit_code trexio_read_ao_1e_int_potential_n_e_im(trexio_t* const file, double* const ao_1e_int_potential_n_e_im);
trexio_exit_code trexio_write_ao_1e_int_potential_n_e_im(trexio_t* const file, const double* ao_1e_int_potential_n_e_im);
trexio_exit_code trexio_read_ao_1e_int_potential_n_e_im_32(trexio_t* const file, float* const ao_1e_int_potential_n_e_im);
trexio_exit_code trexio_write_ao_1e_int_potential_n_e_im_32(trexio_t* const file, const float* ao_1e_int_potential_n_e_im);
trexio_exit_code trexio_read_ao_1e_int_potential_n_e_im_64(trexio_t* const file, double* const ao_1e_int_potential_n_e_im);
trexio_exit_code trexio_write_ao_1e_int_potential_n_e_im_64(trexio_t* const file, const double* ao_1e_int_potential_n_e_im);
trexio_exit_code trexio_read_safe_ao_1e_int_potential_n_e_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_potential_n_e_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_potential_n_e_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_potential_n_e_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_potential_n_e_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_potential_n_e_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_1e_int_ecp_im(trexio_t* const file);
trexio_exit_code trexio_read_ao_1e_int_ecp_im(trexio_t* const file, double* const ao_1e_int_ecp_im);
trexio_exit_code trexio_write_ao_1e_int_ecp_im(trexio_t* const file, const double* ao_1e_int_ecp_im);
trexio_exit_code trexio_read_ao_1e_int_ecp_im_32(trexio_t* const file, float* const ao_1e_int_ecp_im);
trexio_exit_code trexio_write_ao_1e_int_ecp_im_32(trexio_t* const file, const float* ao_1e_int_ecp_im);
trexio_exit_code trexio_read_ao_1e_int_ecp_im_64(trexio_t* const file, double* const ao_1e_int_ecp_im);
trexio_exit_code trexio_write_ao_1e_int_ecp_im_64(trexio_t* const file, const double* ao_1e_int_ecp_im);
trexio_exit_code trexio_read_safe_ao_1e_int_ecp_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_ecp_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_ecp_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_ecp_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_ecp_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_ecp_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_1e_int_core_hamiltonian_im(trexio_t* const file);
trexio_exit_code trexio_read_ao_1e_int_core_hamiltonian_im(trexio_t* const file, double* const ao_1e_int_core_hamiltonian_im);
trexio_exit_code trexio_write_ao_1e_int_core_hamiltonian_im(trexio_t* const file, const double* ao_1e_int_core_hamiltonian_im);
trexio_exit_code trexio_read_ao_1e_int_core_hamiltonian_im_32(trexio_t* const file, float* const ao_1e_int_core_hamiltonian_im);
trexio_exit_code trexio_write_ao_1e_int_core_hamiltonian_im_32(trexio_t* const file, const float* ao_1e_int_core_hamiltonian_im);
trexio_exit_code trexio_read_ao_1e_int_core_hamiltonian_im_64(trexio_t* const file, double* const ao_1e_int_core_hamiltonian_im);
trexio_exit_code trexio_write_ao_1e_int_core_hamiltonian_im_64(trexio_t* const file, const double* ao_1e_int_core_hamiltonian_im);
trexio_exit_code trexio_read_safe_ao_1e_int_core_hamiltonian_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_core_hamiltonian_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_core_hamiltonian_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_core_hamiltonian_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_ao_1e_int_core_hamiltonian_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_ao_1e_int_core_hamiltonian_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_coefficient(trexio_t* const file);
trexio_exit_code trexio_read_mo_coefficient(trexio_t* const file, double* const mo_coefficient);
trexio_exit_code trexio_write_mo_coefficient(trexio_t* const file, const double* mo_coefficient);
trexio_exit_code trexio_read_mo_coefficient_32(trexio_t* const file, float* const mo_coefficient);
trexio_exit_code trexio_write_mo_coefficient_32(trexio_t* const file, const float* mo_coefficient);
trexio_exit_code trexio_read_mo_coefficient_64(trexio_t* const file, double* const mo_coefficient);
trexio_exit_code trexio_write_mo_coefficient_64(trexio_t* const file, const double* mo_coefficient);
trexio_exit_code trexio_read_safe_mo_coefficient(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_coefficient(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_coefficient_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_coefficient_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_coefficient_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_coefficient_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_coefficient_im(trexio_t* const file);
trexio_exit_code trexio_read_mo_coefficient_im(trexio_t* const file, double* const mo_coefficient_im);
trexio_exit_code trexio_write_mo_coefficient_im(trexio_t* const file, const double* mo_coefficient_im);
trexio_exit_code trexio_read_mo_coefficient_im_32(trexio_t* const file, float* const mo_coefficient_im);
trexio_exit_code trexio_write_mo_coefficient_im_32(trexio_t* const file, const float* mo_coefficient_im);
trexio_exit_code trexio_read_mo_coefficient_im_64(trexio_t* const file, double* const mo_coefficient_im);
trexio_exit_code trexio_write_mo_coefficient_im_64(trexio_t* const file, const double* mo_coefficient_im);
trexio_exit_code trexio_read_safe_mo_coefficient_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_coefficient_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_coefficient_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_coefficient_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_coefficient_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_coefficient_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_occupation(trexio_t* const file);
trexio_exit_code trexio_read_mo_occupation(trexio_t* const file, double* const mo_occupation);
trexio_exit_code trexio_write_mo_occupation(trexio_t* const file, const double* mo_occupation);
trexio_exit_code trexio_read_mo_occupation_32(trexio_t* const file, float* const mo_occupation);
trexio_exit_code trexio_write_mo_occupation_32(trexio_t* const file, const float* mo_occupation);
trexio_exit_code trexio_read_mo_occupation_64(trexio_t* const file, double* const mo_occupation);
trexio_exit_code trexio_write_mo_occupation_64(trexio_t* const file, const double* mo_occupation);
trexio_exit_code trexio_read_safe_mo_occupation(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_occupation(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_occupation_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_occupation_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_occupation_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_occupation_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_energy(trexio_t* const file);
trexio_exit_code trexio_read_mo_energy(trexio_t* const file, double* const mo_energy);
trexio_exit_code trexio_write_mo_energy(trexio_t* const file, const double* mo_energy);
trexio_exit_code trexio_read_mo_energy_32(trexio_t* const file, float* const mo_energy);
trexio_exit_code trexio_write_mo_energy_32(trexio_t* const file, const float* mo_energy);
trexio_exit_code trexio_read_mo_energy_64(trexio_t* const file, double* const mo_energy);
trexio_exit_code trexio_write_mo_energy_64(trexio_t* const file, const double* mo_energy);
trexio_exit_code trexio_read_safe_mo_energy(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_energy(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_energy_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_energy_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_energy_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_energy_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_spin(trexio_t* const file);
trexio_exit_code trexio_read_mo_spin(trexio_t* const file, int32_t* const mo_spin);
trexio_exit_code trexio_write_mo_spin(trexio_t* const file, const int32_t* mo_spin);
trexio_exit_code trexio_read_mo_spin_32(trexio_t* const file, int32_t* const mo_spin);
trexio_exit_code trexio_write_mo_spin_32(trexio_t* const file, const int32_t* mo_spin);
trexio_exit_code trexio_read_mo_spin_64(trexio_t* const file, int64_t* const mo_spin);
trexio_exit_code trexio_write_mo_spin_64(trexio_t* const file, const int64_t* mo_spin);
trexio_exit_code trexio_read_safe_mo_spin(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_spin(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_spin_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_spin_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_spin_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_spin_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_k_point(trexio_t* const file);
trexio_exit_code trexio_read_mo_k_point(trexio_t* const file, int32_t* const mo_k_point);
trexio_exit_code trexio_write_mo_k_point(trexio_t* const file, const int32_t* mo_k_point);
trexio_exit_code trexio_read_mo_k_point_32(trexio_t* const file, int32_t* const mo_k_point);
trexio_exit_code trexio_write_mo_k_point_32(trexio_t* const file, const int32_t* mo_k_point);
trexio_exit_code trexio_read_mo_k_point_64(trexio_t* const file, int64_t* const mo_k_point);
trexio_exit_code trexio_write_mo_k_point_64(trexio_t* const file, const int64_t* mo_k_point);
trexio_exit_code trexio_read_safe_mo_k_point(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_k_point(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_k_point_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_k_point_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_k_point_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_k_point_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_1e_int_overlap(trexio_t* const file);
trexio_exit_code trexio_read_mo_1e_int_overlap(trexio_t* const file, double* const mo_1e_int_overlap);
trexio_exit_code trexio_write_mo_1e_int_overlap(trexio_t* const file, const double* mo_1e_int_overlap);
trexio_exit_code trexio_read_mo_1e_int_overlap_32(trexio_t* const file, float* const mo_1e_int_overlap);
trexio_exit_code trexio_write_mo_1e_int_overlap_32(trexio_t* const file, const float* mo_1e_int_overlap);
trexio_exit_code trexio_read_mo_1e_int_overlap_64(trexio_t* const file, double* const mo_1e_int_overlap);
trexio_exit_code trexio_write_mo_1e_int_overlap_64(trexio_t* const file, const double* mo_1e_int_overlap);
trexio_exit_code trexio_read_safe_mo_1e_int_overlap(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_overlap(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_overlap_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_overlap_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_overlap_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_overlap_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_1e_int_kinetic(trexio_t* const file);
trexio_exit_code trexio_read_mo_1e_int_kinetic(trexio_t* const file, double* const mo_1e_int_kinetic);
trexio_exit_code trexio_write_mo_1e_int_kinetic(trexio_t* const file, const double* mo_1e_int_kinetic);
trexio_exit_code trexio_read_mo_1e_int_kinetic_32(trexio_t* const file, float* const mo_1e_int_kinetic);
trexio_exit_code trexio_write_mo_1e_int_kinetic_32(trexio_t* const file, const float* mo_1e_int_kinetic);
trexio_exit_code trexio_read_mo_1e_int_kinetic_64(trexio_t* const file, double* const mo_1e_int_kinetic);
trexio_exit_code trexio_write_mo_1e_int_kinetic_64(trexio_t* const file, const double* mo_1e_int_kinetic);
trexio_exit_code trexio_read_safe_mo_1e_int_kinetic(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_kinetic(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_kinetic_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_kinetic_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_kinetic_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_kinetic_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_1e_int_potential_n_e(trexio_t* const file);
trexio_exit_code trexio_read_mo_1e_int_potential_n_e(trexio_t* const file, double* const mo_1e_int_potential_n_e);
trexio_exit_code trexio_write_mo_1e_int_potential_n_e(trexio_t* const file, const double* mo_1e_int_potential_n_e);
trexio_exit_code trexio_read_mo_1e_int_potential_n_e_32(trexio_t* const file, float* const mo_1e_int_potential_n_e);
trexio_exit_code trexio_write_mo_1e_int_potential_n_e_32(trexio_t* const file, const float* mo_1e_int_potential_n_e);
trexio_exit_code trexio_read_mo_1e_int_potential_n_e_64(trexio_t* const file, double* const mo_1e_int_potential_n_e);
trexio_exit_code trexio_write_mo_1e_int_potential_n_e_64(trexio_t* const file, const double* mo_1e_int_potential_n_e);
trexio_exit_code trexio_read_safe_mo_1e_int_potential_n_e(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_potential_n_e(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_potential_n_e_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_potential_n_e_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_potential_n_e_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_potential_n_e_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_1e_int_ecp(trexio_t* const file);
trexio_exit_code trexio_read_mo_1e_int_ecp(trexio_t* const file, double* const mo_1e_int_ecp);
trexio_exit_code trexio_write_mo_1e_int_ecp(trexio_t* const file, const double* mo_1e_int_ecp);
trexio_exit_code trexio_read_mo_1e_int_ecp_32(trexio_t* const file, float* const mo_1e_int_ecp);
trexio_exit_code trexio_write_mo_1e_int_ecp_32(trexio_t* const file, const float* mo_1e_int_ecp);
trexio_exit_code trexio_read_mo_1e_int_ecp_64(trexio_t* const file, double* const mo_1e_int_ecp);
trexio_exit_code trexio_write_mo_1e_int_ecp_64(trexio_t* const file, const double* mo_1e_int_ecp);
trexio_exit_code trexio_read_safe_mo_1e_int_ecp(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_ecp(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_ecp_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_ecp_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_ecp_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_ecp_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_1e_int_core_hamiltonian(trexio_t* const file);
trexio_exit_code trexio_read_mo_1e_int_core_hamiltonian(trexio_t* const file, double* const mo_1e_int_core_hamiltonian);
trexio_exit_code trexio_write_mo_1e_int_core_hamiltonian(trexio_t* const file, const double* mo_1e_int_core_hamiltonian);
trexio_exit_code trexio_read_mo_1e_int_core_hamiltonian_32(trexio_t* const file, float* const mo_1e_int_core_hamiltonian);
trexio_exit_code trexio_write_mo_1e_int_core_hamiltonian_32(trexio_t* const file, const float* mo_1e_int_core_hamiltonian);
trexio_exit_code trexio_read_mo_1e_int_core_hamiltonian_64(trexio_t* const file, double* const mo_1e_int_core_hamiltonian);
trexio_exit_code trexio_write_mo_1e_int_core_hamiltonian_64(trexio_t* const file, const double* mo_1e_int_core_hamiltonian);
trexio_exit_code trexio_read_safe_mo_1e_int_core_hamiltonian(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_core_hamiltonian(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_core_hamiltonian_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_core_hamiltonian_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_core_hamiltonian_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_core_hamiltonian_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_1e_int_overlap_im(trexio_t* const file);
trexio_exit_code trexio_read_mo_1e_int_overlap_im(trexio_t* const file, double* const mo_1e_int_overlap_im);
trexio_exit_code trexio_write_mo_1e_int_overlap_im(trexio_t* const file, const double* mo_1e_int_overlap_im);
trexio_exit_code trexio_read_mo_1e_int_overlap_im_32(trexio_t* const file, float* const mo_1e_int_overlap_im);
trexio_exit_code trexio_write_mo_1e_int_overlap_im_32(trexio_t* const file, const float* mo_1e_int_overlap_im);
trexio_exit_code trexio_read_mo_1e_int_overlap_im_64(trexio_t* const file, double* const mo_1e_int_overlap_im);
trexio_exit_code trexio_write_mo_1e_int_overlap_im_64(trexio_t* const file, const double* mo_1e_int_overlap_im);
trexio_exit_code trexio_read_safe_mo_1e_int_overlap_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_overlap_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_overlap_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_overlap_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_overlap_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_overlap_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_1e_int_kinetic_im(trexio_t* const file);
trexio_exit_code trexio_read_mo_1e_int_kinetic_im(trexio_t* const file, double* const mo_1e_int_kinetic_im);
trexio_exit_code trexio_write_mo_1e_int_kinetic_im(trexio_t* const file, const double* mo_1e_int_kinetic_im);
trexio_exit_code trexio_read_mo_1e_int_kinetic_im_32(trexio_t* const file, float* const mo_1e_int_kinetic_im);
trexio_exit_code trexio_write_mo_1e_int_kinetic_im_32(trexio_t* const file, const float* mo_1e_int_kinetic_im);
trexio_exit_code trexio_read_mo_1e_int_kinetic_im_64(trexio_t* const file, double* const mo_1e_int_kinetic_im);
trexio_exit_code trexio_write_mo_1e_int_kinetic_im_64(trexio_t* const file, const double* mo_1e_int_kinetic_im);
trexio_exit_code trexio_read_safe_mo_1e_int_kinetic_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_kinetic_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_kinetic_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_kinetic_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_kinetic_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_kinetic_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_1e_int_potential_n_e_im(trexio_t* const file);
trexio_exit_code trexio_read_mo_1e_int_potential_n_e_im(trexio_t* const file, double* const mo_1e_int_potential_n_e_im);
trexio_exit_code trexio_write_mo_1e_int_potential_n_e_im(trexio_t* const file, const double* mo_1e_int_potential_n_e_im);
trexio_exit_code trexio_read_mo_1e_int_potential_n_e_im_32(trexio_t* const file, float* const mo_1e_int_potential_n_e_im);
trexio_exit_code trexio_write_mo_1e_int_potential_n_e_im_32(trexio_t* const file, const float* mo_1e_int_potential_n_e_im);
trexio_exit_code trexio_read_mo_1e_int_potential_n_e_im_64(trexio_t* const file, double* const mo_1e_int_potential_n_e_im);
trexio_exit_code trexio_write_mo_1e_int_potential_n_e_im_64(trexio_t* const file, const double* mo_1e_int_potential_n_e_im);
trexio_exit_code trexio_read_safe_mo_1e_int_potential_n_e_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_potential_n_e_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_potential_n_e_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_potential_n_e_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_potential_n_e_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_potential_n_e_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_1e_int_ecp_im(trexio_t* const file);
trexio_exit_code trexio_read_mo_1e_int_ecp_im(trexio_t* const file, double* const mo_1e_int_ecp_im);
trexio_exit_code trexio_write_mo_1e_int_ecp_im(trexio_t* const file, const double* mo_1e_int_ecp_im);
trexio_exit_code trexio_read_mo_1e_int_ecp_im_32(trexio_t* const file, float* const mo_1e_int_ecp_im);
trexio_exit_code trexio_write_mo_1e_int_ecp_im_32(trexio_t* const file, const float* mo_1e_int_ecp_im);
trexio_exit_code trexio_read_mo_1e_int_ecp_im_64(trexio_t* const file, double* const mo_1e_int_ecp_im);
trexio_exit_code trexio_write_mo_1e_int_ecp_im_64(trexio_t* const file, const double* mo_1e_int_ecp_im);
trexio_exit_code trexio_read_safe_mo_1e_int_ecp_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_ecp_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_ecp_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_ecp_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_ecp_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_ecp_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_mo_1e_int_core_hamiltonian_im(trexio_t* const file);
trexio_exit_code trexio_read_mo_1e_int_core_hamiltonian_im(trexio_t* const file, double* const mo_1e_int_core_hamiltonian_im);
trexio_exit_code trexio_write_mo_1e_int_core_hamiltonian_im(trexio_t* const file, const double* mo_1e_int_core_hamiltonian_im);
trexio_exit_code trexio_read_mo_1e_int_core_hamiltonian_im_32(trexio_t* const file, float* const mo_1e_int_core_hamiltonian_im);
trexio_exit_code trexio_write_mo_1e_int_core_hamiltonian_im_32(trexio_t* const file, const float* mo_1e_int_core_hamiltonian_im);
trexio_exit_code trexio_read_mo_1e_int_core_hamiltonian_im_64(trexio_t* const file, double* const mo_1e_int_core_hamiltonian_im);
trexio_exit_code trexio_write_mo_1e_int_core_hamiltonian_im_64(trexio_t* const file, const double* mo_1e_int_core_hamiltonian_im);
trexio_exit_code trexio_read_safe_mo_1e_int_core_hamiltonian_im(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_core_hamiltonian_im(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_core_hamiltonian_im_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_core_hamiltonian_im_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_mo_1e_int_core_hamiltonian_im_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_mo_1e_int_core_hamiltonian_im_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_rdm_1e(trexio_t* const file);
trexio_exit_code trexio_read_rdm_1e(trexio_t* const file, double* const rdm_1e);
trexio_exit_code trexio_write_rdm_1e(trexio_t* const file, const double* rdm_1e);
trexio_exit_code trexio_read_rdm_1e_32(trexio_t* const file, float* const rdm_1e);
trexio_exit_code trexio_write_rdm_1e_32(trexio_t* const file, const float* rdm_1e);
trexio_exit_code trexio_read_rdm_1e_64(trexio_t* const file, double* const rdm_1e);
trexio_exit_code trexio_write_rdm_1e_64(trexio_t* const file, const double* rdm_1e);
trexio_exit_code trexio_read_safe_rdm_1e(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_rdm_1e(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_rdm_1e_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_rdm_1e_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_rdm_1e_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_rdm_1e_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_rdm_1e_up(trexio_t* const file);
trexio_exit_code trexio_read_rdm_1e_up(trexio_t* const file, double* const rdm_1e_up);
trexio_exit_code trexio_write_rdm_1e_up(trexio_t* const file, const double* rdm_1e_up);
trexio_exit_code trexio_read_rdm_1e_up_32(trexio_t* const file, float* const rdm_1e_up);
trexio_exit_code trexio_write_rdm_1e_up_32(trexio_t* const file, const float* rdm_1e_up);
trexio_exit_code trexio_read_rdm_1e_up_64(trexio_t* const file, double* const rdm_1e_up);
trexio_exit_code trexio_write_rdm_1e_up_64(trexio_t* const file, const double* rdm_1e_up);
trexio_exit_code trexio_read_safe_rdm_1e_up(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_rdm_1e_up(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_rdm_1e_up_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_rdm_1e_up_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_rdm_1e_up_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_rdm_1e_up_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_rdm_1e_dn(trexio_t* const file);
trexio_exit_code trexio_read_rdm_1e_dn(trexio_t* const file, double* const rdm_1e_dn);
trexio_exit_code trexio_write_rdm_1e_dn(trexio_t* const file, const double* rdm_1e_dn);
trexio_exit_code trexio_read_rdm_1e_dn_32(trexio_t* const file, float* const rdm_1e_dn);
trexio_exit_code trexio_write_rdm_1e_dn_32(trexio_t* const file, const float* rdm_1e_dn);
trexio_exit_code trexio_read_rdm_1e_dn_64(trexio_t* const file, double* const rdm_1e_dn);
trexio_exit_code trexio_write_rdm_1e_dn_64(trexio_t* const file, const double* rdm_1e_dn);
trexio_exit_code trexio_read_safe_rdm_1e_dn(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_rdm_1e_dn(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_rdm_1e_dn_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_rdm_1e_dn_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_rdm_1e_dn_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_rdm_1e_dn_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_rdm_1e_transition(trexio_t* const file);
trexio_exit_code trexio_read_rdm_1e_transition(trexio_t* const file, double* const rdm_1e_transition);
trexio_exit_code trexio_write_rdm_1e_transition(trexio_t* const file, const double* rdm_1e_transition);
trexio_exit_code trexio_read_rdm_1e_transition_32(trexio_t* const file, float* const rdm_1e_transition);
trexio_exit_code trexio_write_rdm_1e_transition_32(trexio_t* const file, const float* rdm_1e_transition);
trexio_exit_code trexio_read_rdm_1e_transition_64(trexio_t* const file, double* const rdm_1e_transition);
trexio_exit_code trexio_write_rdm_1e_transition_64(trexio_t* const file, const double* rdm_1e_transition);
trexio_exit_code trexio_read_safe_rdm_1e_transition(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_rdm_1e_transition(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_rdm_1e_transition_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_rdm_1e_transition_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_rdm_1e_transition_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_rdm_1e_transition_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_jastrow_en(trexio_t* const file);
trexio_exit_code trexio_read_jastrow_en(trexio_t* const file, double* const jastrow_en);
trexio_exit_code trexio_write_jastrow_en(trexio_t* const file, const double* jastrow_en);
trexio_exit_code trexio_read_jastrow_en_32(trexio_t* const file, float* const jastrow_en);
trexio_exit_code trexio_write_jastrow_en_32(trexio_t* const file, const float* jastrow_en);
trexio_exit_code trexio_read_jastrow_en_64(trexio_t* const file, double* const jastrow_en);
trexio_exit_code trexio_write_jastrow_en_64(trexio_t* const file, const double* jastrow_en);
trexio_exit_code trexio_read_safe_jastrow_en(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_en(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_jastrow_en_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_en_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_jastrow_en_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_en_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_jastrow_ee(trexio_t* const file);
trexio_exit_code trexio_read_jastrow_ee(trexio_t* const file, double* const jastrow_ee);
trexio_exit_code trexio_write_jastrow_ee(trexio_t* const file, const double* jastrow_ee);
trexio_exit_code trexio_read_jastrow_ee_32(trexio_t* const file, float* const jastrow_ee);
trexio_exit_code trexio_write_jastrow_ee_32(trexio_t* const file, const float* jastrow_ee);
trexio_exit_code trexio_read_jastrow_ee_64(trexio_t* const file, double* const jastrow_ee);
trexio_exit_code trexio_write_jastrow_ee_64(trexio_t* const file, const double* jastrow_ee);
trexio_exit_code trexio_read_safe_jastrow_ee(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_ee(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_jastrow_ee_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_ee_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_jastrow_ee_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_ee_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_jastrow_een(trexio_t* const file);
trexio_exit_code trexio_read_jastrow_een(trexio_t* const file, double* const jastrow_een);
trexio_exit_code trexio_write_jastrow_een(trexio_t* const file, const double* jastrow_een);
trexio_exit_code trexio_read_jastrow_een_32(trexio_t* const file, float* const jastrow_een);
trexio_exit_code trexio_write_jastrow_een_32(trexio_t* const file, const float* jastrow_een);
trexio_exit_code trexio_read_jastrow_een_64(trexio_t* const file, double* const jastrow_een);
trexio_exit_code trexio_write_jastrow_een_64(trexio_t* const file, const double* jastrow_een);
trexio_exit_code trexio_read_safe_jastrow_een(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_een(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_jastrow_een_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_een_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_jastrow_een_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_een_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_jastrow_en_nucleus(trexio_t* const file);
trexio_exit_code trexio_read_jastrow_en_nucleus(trexio_t* const file, int32_t* const jastrow_en_nucleus);
trexio_exit_code trexio_write_jastrow_en_nucleus(trexio_t* const file, const int32_t* jastrow_en_nucleus);
trexio_exit_code trexio_read_jastrow_en_nucleus_32(trexio_t* const file, int32_t* const jastrow_en_nucleus);
trexio_exit_code trexio_write_jastrow_en_nucleus_32(trexio_t* const file, const int32_t* jastrow_en_nucleus);
trexio_exit_code trexio_read_jastrow_en_nucleus_64(trexio_t* const file, int64_t* const jastrow_en_nucleus);
trexio_exit_code trexio_write_jastrow_en_nucleus_64(trexio_t* const file, const int64_t* jastrow_en_nucleus);
trexio_exit_code trexio_read_safe_jastrow_en_nucleus(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_en_nucleus(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_jastrow_en_nucleus_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_en_nucleus_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_jastrow_en_nucleus_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_en_nucleus_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_jastrow_een_nucleus(trexio_t* const file);
trexio_exit_code trexio_read_jastrow_een_nucleus(trexio_t* const file, int32_t* const jastrow_een_nucleus);
trexio_exit_code trexio_write_jastrow_een_nucleus(trexio_t* const file, const int32_t* jastrow_een_nucleus);
trexio_exit_code trexio_read_jastrow_een_nucleus_32(trexio_t* const file, int32_t* const jastrow_een_nucleus);
trexio_exit_code trexio_write_jastrow_een_nucleus_32(trexio_t* const file, const int32_t* jastrow_een_nucleus);
trexio_exit_code trexio_read_jastrow_een_nucleus_64(trexio_t* const file, int64_t* const jastrow_een_nucleus);
trexio_exit_code trexio_write_jastrow_een_nucleus_64(trexio_t* const file, const int64_t* jastrow_een_nucleus);
trexio_exit_code trexio_read_safe_jastrow_een_nucleus(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_een_nucleus(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_jastrow_een_nucleus_32(trexio_t* const file, int32_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_een_nucleus_32(trexio_t* const file, const int32_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_jastrow_een_nucleus_64(trexio_t* const file, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_een_nucleus_64(trexio_t* const file, const int64_t* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_jastrow_en_scaling(trexio_t* const file);
trexio_exit_code trexio_read_jastrow_en_scaling(trexio_t* const file, double* const jastrow_en_scaling);
trexio_exit_code trexio_write_jastrow_en_scaling(trexio_t* const file, const double* jastrow_en_scaling);
trexio_exit_code trexio_read_jastrow_en_scaling_32(trexio_t* const file, float* const jastrow_en_scaling);
trexio_exit_code trexio_write_jastrow_en_scaling_32(trexio_t* const file, const float* jastrow_en_scaling);
trexio_exit_code trexio_read_jastrow_en_scaling_64(trexio_t* const file, double* const jastrow_en_scaling);
trexio_exit_code trexio_write_jastrow_en_scaling_64(trexio_t* const file, const double* jastrow_en_scaling);
trexio_exit_code trexio_read_safe_jastrow_en_scaling(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_en_scaling(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_jastrow_en_scaling_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_en_scaling_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_jastrow_en_scaling_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_jastrow_en_scaling_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_qmc_point(trexio_t* const file);
trexio_exit_code trexio_read_qmc_point(trexio_t* const file, double* const qmc_point);
trexio_exit_code trexio_write_qmc_point(trexio_t* const file, const double* qmc_point);
trexio_exit_code trexio_read_qmc_point_32(trexio_t* const file, float* const qmc_point);
trexio_exit_code trexio_write_qmc_point_32(trexio_t* const file, const float* qmc_point);
trexio_exit_code trexio_read_qmc_point_64(trexio_t* const file, double* const qmc_point);
trexio_exit_code trexio_write_qmc_point_64(trexio_t* const file, const double* qmc_point);
trexio_exit_code trexio_read_safe_qmc_point(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_qmc_point(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_qmc_point_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_qmc_point_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_qmc_point_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_qmc_point_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_qmc_psi(trexio_t* const file);
trexio_exit_code trexio_read_qmc_psi(trexio_t* const file, double* const qmc_psi);
trexio_exit_code trexio_write_qmc_psi(trexio_t* const file, const double* qmc_psi);
trexio_exit_code trexio_read_qmc_psi_32(trexio_t* const file, float* const qmc_psi);
trexio_exit_code trexio_write_qmc_psi_32(trexio_t* const file, const float* qmc_psi);
trexio_exit_code trexio_read_qmc_psi_64(trexio_t* const file, double* const qmc_psi);
trexio_exit_code trexio_write_qmc_psi_64(trexio_t* const file, const double* qmc_psi);
trexio_exit_code trexio_read_safe_qmc_psi(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_qmc_psi(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_qmc_psi_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_qmc_psi_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_qmc_psi_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_qmc_psi_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_qmc_e_loc(trexio_t* const file);
trexio_exit_code trexio_read_qmc_e_loc(trexio_t* const file, double* const qmc_e_loc);
trexio_exit_code trexio_write_qmc_e_loc(trexio_t* const file, const double* qmc_e_loc);
trexio_exit_code trexio_read_qmc_e_loc_32(trexio_t* const file, float* const qmc_e_loc);
trexio_exit_code trexio_write_qmc_e_loc_32(trexio_t* const file, const float* qmc_e_loc);
trexio_exit_code trexio_read_qmc_e_loc_64(trexio_t* const file, double* const qmc_e_loc);
trexio_exit_code trexio_write_qmc_e_loc_64(trexio_t* const file, const double* qmc_e_loc);
trexio_exit_code trexio_read_safe_qmc_e_loc(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_qmc_e_loc(trexio_t* const file, const double* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_qmc_e_loc_32(trexio_t* const file, float* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_qmc_e_loc_32(trexio_t* const file, const float* dset_in, const int64_t dim_in);
trexio_exit_code trexio_read_safe_qmc_e_loc_64(trexio_t* const file, double* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_safe_qmc_e_loc_64(trexio_t* const file, const double* dset_in, const int64_t dim_in);

trexio_exit_code trexio_has_ao_2e_int_eri(trexio_t* const file);
trexio_exit_code trexio_read_ao_2e_int_eri(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_ao_2e_int_eri_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_ao_2e_int_eri(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_ao_2e_int_eri(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_ao_2e_int_eri(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_ao_2e_int_eri_lr(trexio_t* const file);
trexio_exit_code trexio_read_ao_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_ao_2e_int_eri_lr_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_ao_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_ao_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_ao_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_ao_2e_int_eri_cholesky(trexio_t* const file);
trexio_exit_code trexio_read_ao_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_ao_2e_int_eri_cholesky_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_ao_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_ao_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_ao_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_ao_2e_int_eri_lr_cholesky(trexio_t* const file);
trexio_exit_code trexio_read_ao_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_ao_2e_int_eri_lr_cholesky_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_ao_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_ao_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_ao_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_mo_2e_int_eri(trexio_t* const file);
trexio_exit_code trexio_read_mo_2e_int_eri(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_mo_2e_int_eri_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_mo_2e_int_eri(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_mo_2e_int_eri(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_mo_2e_int_eri(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_mo_2e_int_eri_lr(trexio_t* const file);
trexio_exit_code trexio_read_mo_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_mo_2e_int_eri_lr_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_mo_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_mo_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_mo_2e_int_eri_lr(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_mo_2e_int_eri_cholesky(trexio_t* const file);
trexio_exit_code trexio_read_mo_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_mo_2e_int_eri_cholesky_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_mo_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_mo_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_mo_2e_int_eri_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_mo_2e_int_eri_lr_cholesky(trexio_t* const file);
trexio_exit_code trexio_read_mo_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_mo_2e_int_eri_lr_cholesky_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_mo_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_mo_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_mo_2e_int_eri_lr_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_csf_det_coefficient(trexio_t* const file);
trexio_exit_code trexio_read_csf_det_coefficient(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_csf_det_coefficient_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_csf_det_coefficient(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_csf_det_coefficient(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_csf_det_coefficient(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_amplitude_single(trexio_t* const file);
trexio_exit_code trexio_read_amplitude_single(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_amplitude_single_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_amplitude_single(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_amplitude_single(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_amplitude_single(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_amplitude_single_exp(trexio_t* const file);
trexio_exit_code trexio_read_amplitude_single_exp(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_amplitude_single_exp_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_amplitude_single_exp(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_amplitude_single_exp(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_amplitude_single_exp(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_amplitude_double(trexio_t* const file);
trexio_exit_code trexio_read_amplitude_double(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_amplitude_double_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_amplitude_double(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_amplitude_double(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_amplitude_double(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_amplitude_double_exp(trexio_t* const file);
trexio_exit_code trexio_read_amplitude_double_exp(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_amplitude_double_exp_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_amplitude_double_exp(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_amplitude_double_exp(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_amplitude_double_exp(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_amplitude_triple(trexio_t* const file);
trexio_exit_code trexio_read_amplitude_triple(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_amplitude_triple_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_amplitude_triple(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_amplitude_triple(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_amplitude_triple(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_amplitude_triple_exp(trexio_t* const file);
trexio_exit_code trexio_read_amplitude_triple_exp(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_amplitude_triple_exp_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_amplitude_triple_exp(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_amplitude_triple_exp(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_amplitude_triple_exp(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_amplitude_quadruple(trexio_t* const file);
trexio_exit_code trexio_read_amplitude_quadruple(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_amplitude_quadruple_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_amplitude_quadruple(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_amplitude_quadruple(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_amplitude_quadruple(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_amplitude_quadruple_exp(trexio_t* const file);
trexio_exit_code trexio_read_amplitude_quadruple_exp(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_amplitude_quadruple_exp_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_amplitude_quadruple_exp(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_amplitude_quadruple_exp(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_amplitude_quadruple_exp(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_rdm_2e(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_rdm_2e_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_rdm_2e(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_rdm_2e(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_rdm_2e(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_rdm_2e_upup(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e_upup(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_rdm_2e_upup_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_rdm_2e_upup(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_rdm_2e_upup(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_rdm_2e_upup(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_rdm_2e_dndn(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e_dndn(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_rdm_2e_dndn_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_rdm_2e_dndn(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_rdm_2e_dndn(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_rdm_2e_dndn(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_rdm_2e_updn(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e_updn(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_rdm_2e_updn_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_rdm_2e_updn(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_rdm_2e_updn(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_rdm_2e_updn(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_rdm_2e_transition(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e_transition(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_rdm_2e_transition_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_rdm_2e_transition(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_rdm_2e_transition(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_rdm_2e_transition(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_rdm_2e_cholesky(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_rdm_2e_cholesky_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_rdm_2e_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_rdm_2e_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_rdm_2e_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_rdm_2e_upup_cholesky(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e_upup_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_rdm_2e_upup_cholesky_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_rdm_2e_upup_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_rdm_2e_upup_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_rdm_2e_upup_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_rdm_2e_dndn_cholesky(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e_dndn_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_rdm_2e_dndn_cholesky_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_rdm_2e_dndn_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_rdm_2e_dndn_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_rdm_2e_dndn_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_rdm_2e_updn_cholesky(trexio_t* const file);
trexio_exit_code trexio_read_rdm_2e_updn_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int32_t* const index_sparse, double* const value_sparse);
trexio_exit_code trexio_read_rdm_2e_updn_cholesky_size(trexio_t* const file, int64_t* const size_max);
trexio_exit_code trexio_write_rdm_2e_updn_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse, const double* value_sparse);
trexio_exit_code trexio_read_safe_rdm_2e_updn_cholesky(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int32_t* const index_sparse_read, const int64_t size_index_read, double* const value_sparse_read, const int64_t size_value_read);
trexio_exit_code trexio_write_safe_rdm_2e_updn_cholesky(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int32_t* index_sparse_write, const int64_t size_index_write, const double* value_sparse_write, const int64_t size_value_write);

trexio_exit_code trexio_has_metadata_code(trexio_t* const file);
trexio_exit_code trexio_read_metadata_code_low(trexio_t* const file, char* dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_metadata_code_low(trexio_t* const file, char* dset_in, const int32_t max_str_len);
trexio_exit_code trexio_read_metadata_code(trexio_t* const file, char** dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_metadata_code(trexio_t* const file, const char** dset_in, const int32_t max_str_len);

trexio_exit_code trexio_has_metadata_author(trexio_t* const file);
trexio_exit_code trexio_read_metadata_author_low(trexio_t* const file, char* dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_metadata_author_low(trexio_t* const file, char* dset_in, const int32_t max_str_len);
trexio_exit_code trexio_read_metadata_author(trexio_t* const file, char** dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_metadata_author(trexio_t* const file, const char** dset_in, const int32_t max_str_len);

trexio_exit_code trexio_has_nucleus_label(trexio_t* const file);
trexio_exit_code trexio_read_nucleus_label_low(trexio_t* const file, char* dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_nucleus_label_low(trexio_t* const file, char* dset_in, const int32_t max_str_len);
trexio_exit_code trexio_read_nucleus_label(trexio_t* const file, char** dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_nucleus_label(trexio_t* const file, const char** dset_in, const int32_t max_str_len);

trexio_exit_code trexio_has_state_label(trexio_t* const file);
trexio_exit_code trexio_read_state_label_low(trexio_t* const file, char* dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_state_label_low(trexio_t* const file, char* dset_in, const int32_t max_str_len);
trexio_exit_code trexio_read_state_label(trexio_t* const file, char** dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_state_label(trexio_t* const file, const char** dset_in, const int32_t max_str_len);

trexio_exit_code trexio_has_state_file_name(trexio_t* const file);
trexio_exit_code trexio_read_state_file_name_low(trexio_t* const file, char* dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_state_file_name_low(trexio_t* const file, char* dset_in, const int32_t max_str_len);
trexio_exit_code trexio_read_state_file_name(trexio_t* const file, char** dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_state_file_name(trexio_t* const file, const char** dset_in, const int32_t max_str_len);

trexio_exit_code trexio_has_mo_class(trexio_t* const file);
trexio_exit_code trexio_read_mo_class_low(trexio_t* const file, char* dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_mo_class_low(trexio_t* const file, char* dset_in, const int32_t max_str_len);
trexio_exit_code trexio_read_mo_class(trexio_t* const file, char** dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_mo_class(trexio_t* const file, const char** dset_in, const int32_t max_str_len);

trexio_exit_code trexio_has_mo_symmetry(trexio_t* const file);
trexio_exit_code trexio_read_mo_symmetry_low(trexio_t* const file, char* dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_mo_symmetry_low(trexio_t* const file, char* dset_in, const int32_t max_str_len);
trexio_exit_code trexio_read_mo_symmetry(trexio_t* const file, char** dset_out, const int32_t max_str_len);
trexio_exit_code trexio_write_mo_symmetry(trexio_t* const file, const char** dset_in, const int32_t max_str_len);

trexio_exit_code trexio_has_metadata(trexio_t* const file);

trexio_exit_code trexio_has_nucleus(trexio_t* const file);

trexio_exit_code trexio_has_cell(trexio_t* const file);

trexio_exit_code trexio_has_pbc(trexio_t* const file);

trexio_exit_code trexio_has_electron(trexio_t* const file);

trexio_exit_code trexio_has_state(trexio_t* const file);

trexio_exit_code trexio_has_basis(trexio_t* const file);

trexio_exit_code trexio_has_ecp(trexio_t* const file);

trexio_exit_code trexio_has_grid(trexio_t* const file);

trexio_exit_code trexio_has_ao(trexio_t* const file);

trexio_exit_code trexio_has_ao_1e_int(trexio_t* const file);

trexio_exit_code trexio_has_ao_2e_int(trexio_t* const file);

trexio_exit_code trexio_has_mo(trexio_t* const file);

trexio_exit_code trexio_has_mo_1e_int(trexio_t* const file);

trexio_exit_code trexio_has_mo_2e_int(trexio_t* const file);

trexio_exit_code trexio_has_determinant(trexio_t* const file);

trexio_exit_code trexio_has_csf(trexio_t* const file);

trexio_exit_code trexio_has_amplitude(trexio_t* const file);

trexio_exit_code trexio_has_rdm(trexio_t* const file);

trexio_exit_code trexio_has_jastrow(trexio_t* const file);

trexio_exit_code trexio_has_qmc(trexio_t* const file);

trexio_exit_code trexio_has_determinant_list(trexio_t* const file);
trexio_exit_code trexio_read_determinant_list(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size, int64_t* const dset);
trexio_exit_code trexio_read_safe_determinant_list(trexio_t* const file, const int64_t offset_file, int64_t* const buffer_size_read, int64_t* const dset_out, const int64_t dim_out);
trexio_exit_code trexio_write_determinant_list(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int64_t* dset);
trexio_exit_code trexio_write_safe_determinant_list(trexio_t* const file, const int64_t offset_file, const int64_t buffer_size, const int64_t* dset_in, const int64_t dim_in);
trexio_exit_code trexio_get_int64_num(trexio_t* const file, int32_t* const num);
#ifdef __cplusplus
}
#endif

#endif
