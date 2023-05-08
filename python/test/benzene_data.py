
# for the nucleus group
nucleus_num    = 12

point_group    = 'D6h'

nucleus_label  = ['C', 'C', 'C', 'C', 'C', 'C', 'H', 'H', 'H', 'H', 'H', 'H']

nucleus_charge = [6., 6., 6., 6., 6., 6., 1., 1., 1., 1., 1., 1.]

nucleus_coord  = [
[ 0.00000000 ,  1.39250319 ,  0.00000000 ],
[-1.20594314 ,  0.69625160 ,  0.00000000 ],
[-1.20594314 , -0.69625160 ,  0.00000000 ],
[ 0.00000000 , -1.39250319 ,  0.00000000 ],
[ 1.20594314 , -0.69625160 ,  0.00000000 ],
[ 1.20594314 ,  0.69625160 ,  0.00000000 ],
[-2.14171677 ,  1.23652075 ,  0.00000000 ],
[-2.14171677 , -1.23652075 ,  0.00000000 ],
[ 0.00000000 , -2.47304151 ,  0.00000000 ],
[ 2.14171677 , -1.23652075 ,  0.00000000 ],
[ 2.14171677 ,  1.23652075 ,  0.00000000 ],
[ 0.00000000 ,  2.47304151 ,  0.00000000 ],
]

# for the basis_nucleus_index
basis_shell_num = 24
nucleus_index   = [i for i in range(basis_shell_num)]

# for sparse AO_INT_2E
ao_num = 600
# prepare the sparse data representation
num_integrals = 100
indices       = [i for i in range(num_integrals*4)]
values        = [(3.14 + float(i)) for i in range(num_integrals)]

# for determinants
mo_num    = 150
int64_num = int((mo_num - 1)/64 + 1)
# prepate the CI data
det_num   = 2000
dets      = [i for i in range(det_num * int64_num * 2)]
coeffs    = [float(i/det_num)   for i in range(det_num)]
coeffs_s2 = [float(i*2/det_num) for i in range(det_num)]

det_test  = [1, 2, 3, 2, 1, 3]

orb_up_test = [0, 65, 128, 129]
orb_dn_test = [1, 64, 128, 129]

external_2Dfloat_name = "test external float matrix"
external_1Dint32_name = "test external int32 vector"
