//
// Created by docto on 28/01/2019.
//

#include "apu.h"

/**
 * Links the APU's registers to the CPU's memory map.
 *
 * If write is true, then the third parameter
 * @param addr
 * @param write
 * @param data
 * @return
 */
uint8_t APU::access_registers(uint16_t addr, uint8_t data) {
    switch(addr){
        case 0x4000: pulse1_ctrl = data ; break;
        case 0x4001: pulse1_ramp_ctrl = data; break;
        case 0x4002: pulse1_fine_tune = data; break;
        case 0x4003: pulse1_coarse_tune = data; break;
        case 0x4004: pulse2_ctrl = data; break;
        case 0x4005: pulse2_ramp_ctrl = data; break;
        case 0x4006: pulse2_fine_tune = data; break;
        case 0x4007: pulse2_coarse_tune = data; break;
        case 0x4008: tri_ctrl1 = data; break;
        case 0x4009: tri_ctrl2 = data; break;
        case 0x400A: tri_freq1 = data; break;
        case 0x400B: tri_freq2 = data; break;
        case 0x400C: noise_ctrl = data; break;
        case 0x400E: noise_freq1 = data; break;
        case 0x400F: noise_freq2 = data; break;
        case 0x4010: delta_ctrl = data; break;
        case 0x4011: delta_da = data; break;
        case 0x4012: delta_addr = data; break;
        case 0x4013: delta_data_len = data; break;
        case 0x4015: mstrctrl = data; break;
        case 0x4017: delta_frame_ctr = data; break;
        default: ;
    }
    return 0;
}

/**
 *
 * @return
 */
uint8_t APU::read_mstrctrl() const {
    return mstrctrl;
}
