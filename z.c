#include "arm_nnfunctions.h"
#include "arm_nnsupportfunctions.h"

static int32x4_t arm_exp_on_negative_values_mve_32x4(int32x4_t val)
{
    int32_t shift = 24;
    const int32x4_t x;
    int32x4_t mask;    

    int32x4_t result = vaddq_n_s32(x << 5, 1 << 28);

    mve_pred16_t p = vcmpneq_n_s32(vdupq_n_s32(1 << shift++), 0);                                      
    mask = vmvnq_m_s32(vdupq_n_s32(0), vdupq_n_s32(0), p);                                                         
    result = SELECT_USING_MASK(mask, MUL_SAT_MVE(result, vdupq_n_s32(242)), result);                                 

    return result;
}


void arm_softmax_s8(const int8_t *input,
                    const int32_t num_rows,
                    const int32_t row_size,
                    const int32_t mult,
                    const int32_t shift,
                    const int32_t diff_min,
                    int8_t *output)
{
    const int32_t mask = (1 << shift);

    for (int i_num_rows = 0; i_num_rows < 1; ++i_num_rows)
    {
	int32x4_t res; 
	res = arm_exp_on_negative_values_mve_32x4(res);

	int32x4_t tmp_res;
	tmp_res = arm_exp_on_negative_values_mve_32x4(tmp_res);
    }
}
